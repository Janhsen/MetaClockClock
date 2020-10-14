/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuI2CSpy.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : I2CSpy
**     Version     : Component 01.016, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-04-15, 12:58, # CodeGen: 596
**     Abstract    :
**          This component implements a utility to inspect devices on the I2C bus.
**     Settings    :
**          Component name                                 : McuI2CSpy
**          I2C                                            : McuGenericI2C
**          Default Address                                : 0x0
**          Default Address Size                           : 1
**          Default Bytes per Line                         : 8
**          Shell                                          : Enabled
**            Shell                                        : McuShell
**            Utility                                      : McuUtility
**     Contents    :
**         SetDeviceAddress - uint8_t McuI2CSpy_SetDeviceAddress(uint8_t addr);
**         GetDeviceAddress - uint8_t McuI2CSpy_GetDeviceAddress(void);
**         SetAddressSize   - uint8_t McuI2CSpy_SetAddressSize(uint8_t size);
**         SetBytesPerLine  - uint8_t McuI2CSpy_SetBytesPerLine(uint8_t nofBytesPerLine);
**         ReadRegData      - uint8_t McuI2CSpy_ReadRegData(uint32_t addr, uint8_t *data, size_t dataSize);
**         WriteRegData     - uint8_t McuI2CSpy_WriteRegData(uint32_t addr, uint8_t *data, uint16_t dataSize);
**         ParseCommand     - uint8_t McuI2CSpy_ParseCommand(const unsigned char *cmd, bool *handled, const...
**         Deinit           - void McuI2CSpy_Deinit(void);
**         Init             - uint8_t McuI2CSpy_Init(void);
**
** * Copyright (c) 2013-2019, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file McuI2CSpy.h
** @version 01.00
** @brief
**          This component implements a utility to inspect devices on the I2C bus.
*/         
/*!
**  @addtogroup McuI2CSpy_module McuI2CSpy module documentation
**  @{
*/         

/* MODULE McuI2CSpy. */

#include "McuI2CSpy.h"

#define McuI2CSpy_DEFAULT_I2C_ADDR        0
#define McuI2CSpy_DEFAULT_ADDR_SIZE       1
#define McuI2CSpy_DEFAULT_BYTES_PER_LINE  8

typedef struct {
  uint8_t deviceAddr; /* I2C 7bit device address */
  uint8_t addrSize; /* number of address bytes, e.g. 1, 2, 3 or 4 bytes */
  uint8_t bytesPerLine; /* number of bytes per line for dump */
} McuI2CSpy_TDataState;

static McuI2CSpy_TDataState McuI2CSpy_deviceData;

#define MAX_NOF_BYTES_PER_LINE 32 /* maximum number of bytes per line */

static uint8_t Read(uint32_t addr, const McuShell_StdIOType *io) {
  uint8_t val;
  uint8_t hexBuf[3];

  if (McuI2CSpy_ReadRegData(addr, &val, 1)!=ERR_OK) {
    McuShell_SendStr((unsigned char*)"\r\n*** read failed!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  McuShell_SendStr((unsigned char*)"value: 0x", io->stdOut);
  hexBuf[0] = '\0';
  McuUtility_strcatNum8Hex(hexBuf, sizeof(hexBuf), val);
  McuShell_SendStr(hexBuf, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t ReadData(void *hndl, uint32_t addr, uint8_t *buf, size_t bufSize) {
  (void)hndl; /* not used */
  if (McuI2CSpy_ReadRegData(addr, buf, bufSize)!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

static void ScanDevices(const McuShell_StdIOType *io) {
  uint8_t addr, oldAddr;
  uint8_t buf[3], res;

  oldAddr = McuI2CSpy_GetDeviceAddress();
  for (addr=0; addr<0x7f; addr++) {
    McuShell_SendStr((unsigned char*)"scan of I2C device addr 0x", io->stdOut);
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), addr);
    McuShell_SendStr(buf, io->stdOut);
    if (McuI2CSpy_SetDeviceAddress(addr)!=ERR_OK) {
      McuShell_SendStr((unsigned char*)": failed selecting device\r\n", io->stdErr);
      break; /* get out of for loop */
    }
    res = McuGenericI2C_ScanDevice(addr);
    if (res==ERR_NOTAVAIL) {
      McuShell_SendStr((unsigned char*)": no ACK\r\n", io->stdErr);
    } else if (res==ERR_OK) {
      McuShell_SendStr((unsigned char*)": Device responded!\r\n", io->stdErr);
    } else {
      McuShell_SendStr((unsigned char*)": *** failed! ***\r\n", io->stdErr);
    }
  } /* for */
  (void)McuI2CSpy_SetDeviceAddress(oldAddr); /* restore old device address */
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[3];

  McuShell_SendStatusStr((unsigned char*)"McuI2CSpy", (unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  deviceAddr", (unsigned char*)"0x", io->stdOut);
  buf[0] = '\0';
  McuUtility_strcatNum8Hex(buf, sizeof(buf), McuI2CSpy_GetDeviceAddress());
  McuShell_SendStr(buf, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  addrSize", (unsigned char*)"", io->stdOut);
  McuShell_SendNum8u(McuI2CSpy_deviceData.addrSize, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  McuShell_SendStatusStr((unsigned char*)"  bytes/Line", (unsigned char*)"", io->stdOut);
  McuShell_SendNum8u(McuI2CSpy_deviceData.bytesPerLine, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuI2CSpy", (unsigned char*)"Group of McuI2CSpy commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  bytesPerLine <number>", (unsigned char*)"Number of bytes per line for dump command (1..32)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  scan", (unsigned char*)"Scans device addresses\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  device 0x<addr>", (unsigned char*)"Set the I2C device address\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  addrSize <size>", (unsigned char*)"Address size used for device memory map (1, 2, 3 or 4)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  read 0x<addr>", (unsigned char*)"Read a byte from an address\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  write 0x<addr> 0x<data>", (unsigned char*)"Write a data to an address. 0x<data> can be multiple items.\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  dump 0x<start>..0x<end>", (unsigned char*)"Read data from an address range\r\n", io->stdOut);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  ParseCommand (component I2CSpy)
**
**     Description :
**         Shell Command Line parser
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to command string
**       * handled         - Pointer to variable which tells if
**                           the command has been handled or not
**         io              - Pointer to I/O structure
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t McuI2CSpy_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io)
{
  uint8_t addr8, value8;
  uint32_t addr32, end32;
  const unsigned char *p;
  uint8_t cnt;
  uint8_t buf[16];

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuI2CSpy help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuI2CSpy status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "McuI2CSpy bytesPerLine ", sizeof("McuI2CSpy bytesPerLine ")-1)==0) {
    p = cmd+sizeof("McuI2CSpy bytesPerLine ")-1;
    if (McuUtility_ScanDecimal8uNumber(&p, &value8)==ERR_OK && value8>=1 && value8<=MAX_NOF_BYTES_PER_LINE) {
      (void)McuI2CSpy_SetBytesPerLine(value8);
    } else {
      McuShell_SendStr((unsigned char*)"**** wrong bytes per line, must be 1..32\r\n", io->stdErr);
    }
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, "McuI2CSpy device ", sizeof("McuI2CSpy device ")-1)==0) {
    p = cmd+sizeof("McuI2CSpy device ")-1;
    if (McuUtility_ScanHex8uNumber(&p, &addr8)==ERR_OK && addr8<=0x7F) {
      (void)McuI2CSpy_SetDeviceAddress(addr8);
    } else {
      McuShell_SendStr((unsigned char*)"**** wrong device address\r\n", io->stdErr);
    }
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, "McuI2CSpy read ", sizeof("McuI2CSpy read ")-1)==0) {
    p = cmd+sizeof("McuI2CSpy read ")-1;
    if (McuUtility_ScanHex32uNumber(&p, &addr32)==ERR_OK) {
      (void)Read(addr32, io);
    } else {
      McuShell_SendStr((unsigned char*)"**** wrong address\r\n", io->stdErr);
    }
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, "McuI2CSpy addrSize ", sizeof("McuI2CSpy addrSize ")-1)==0) {
    p = cmd+sizeof("McuI2CSpy addrSize ")-1;
    if (McuUtility_ScanDecimal8uNumber(&p, &value8)==ERR_OK && value8>=1 && value8<=4) {
      (void)McuI2CSpy_SetAddressSize(value8);
    } else {
      McuShell_SendStr((unsigned char*)"**** addrSize of range (1-4)\r\n", io->stdErr);
    }
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, "McuI2CSpy write ", sizeof("McuI2CSpy write ")-1)==0) {
    p = cmd+sizeof("McuI2CSpy write ")-1;
    if (McuUtility_ScanHex32uNumber(&p, &addr32)==ERR_OK) {
      for(cnt=0; cnt<sizeof(buf) && *p!='\0'; cnt++) { /* breaks */
        if (McuUtility_ScanHex8uNumber(&p, &buf[cnt])!=ERR_OK) {
          McuShell_SendStr((unsigned char*)"**** wrong data format\r\n", io->stdErr);
          cnt = 0;
          break;
        }
      } /* for */
      if (cnt>=1) {
        (void)McuI2CSpy_WriteRegData(addr32, &buf[0], cnt);
      }
    } /* if */
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, "McuI2CSpy dump ", sizeof("McuI2CSpy dump ")-1)==0) {
    p = cmd+sizeof("McuI2CSpy dump ")-1;
    if (McuUtility_ScanHex32uNumber(&p, &addr32)==ERR_OK) {
      if (McuUtility_strncmp((char*)p, "..", sizeof("..")-1)==0) {
        p = p+sizeof("..")-1;
        if (McuUtility_ScanHex32uNumber(&p, &end32)==ERR_OK) {
          (void)McuShell_PrintMemory(NULL, addr32, end32, McuI2CSpy_deviceData.addrSize, McuI2CSpy_deviceData.bytesPerLine, ReadData, io);
        } else {
          McuShell_SendStr((unsigned char*)"**** wrong end address\r\n", io->stdErr);
        }
      } else {
        McuShell_SendStr((unsigned char*)"**** wrong format, '..' expected.\r\n", io->stdErr);
      }
    } else {
      McuShell_SendStr((unsigned char*)"**** wrong start address\r\n", io->stdErr);
    }
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "McuI2CSpy scan")==0) {
    ScanDevices(io);
    *handled = TRUE;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SetDeviceAddress (component I2CSpy)
**
**     Description :
**         Sets the I2C Device address to be used
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - I2C 7bit address
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t McuI2CSpy_SetDeviceAddress(uint8_t addr)
{
  McuI2CSpy_deviceData.deviceAddr = addr;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  GetDeviceAddress (component I2CSpy)
**
**     Description :
**         Returns the current I2C Device address used
**     Parameters  : None
**     Returns     :
**         ---             - 7bit Device Address
** ===================================================================
*/
uint8_t McuI2CSpy_GetDeviceAddress(void)
{
  return McuI2CSpy_deviceData.deviceAddr;
}

/*
** ===================================================================
**     Method      :  SetAddressSize (component I2CSpy)
**
**     Description :
**         Specifies the address size of the I2C device memory
**     Parameters  :
**         NAME            - DESCRIPTION
**         size            - Either 1 (8bit), 2 (16bit), 3 (24bit),
**                           or 4 (32bit)
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t McuI2CSpy_SetAddressSize(uint8_t size)
{
  McuI2CSpy_deviceData.addrSize = size;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SetBytesPerLine (component I2CSpy)
**
**     Description :
**         Sets the number of bytes per line for the Dump shell command
**     Parameters  :
**         NAME            - DESCRIPTION
**         nofBytesPerLine - Number of bytes
**                           per line
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t McuI2CSpy_SetBytesPerLine(uint8_t nofBytesPerLine)
{
  McuI2CSpy_deviceData.bytesPerLine = nofBytesPerLine;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Init (component I2CSpy)
**
**     Description :
**         Initialization method
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t McuI2CSpy_Init(void)
{
  if (McuI2CSpy_SetDeviceAddress(McuI2CSpy_DEFAULT_I2C_ADDR)!=ERR_OK) {
    return ERR_FAILED;
  }
  if (McuI2CSpy_SetBytesPerLine(McuI2CSpy_DEFAULT_BYTES_PER_LINE)!=ERR_OK) {
    return ERR_FAILED;
  }
  if (McuI2CSpy_SetAddressSize(McuI2CSpy_DEFAULT_ADDR_SIZE)!=ERR_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Deinit (component I2CSpy)
**
**     Description :
**         Deinitialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuI2CSpy_Deinit(void)
{
  /* nothing to do */
}

/*
** ===================================================================
**     Method      :  McuI2CSpy_OnRequestBus (component I2CSpy)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void McuGenericI2C_OnRequestBus(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Method      :  McuI2CSpy_OnReleaseBus (component I2CSpy)
**
**     Description :
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void McuGenericI2C_OnReleaseBus(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Method      :  ReadRegData (component I2CSpy)
**
**     Description :
**         Reads data starting from a register address from the current
**         device
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - Device address
**       * data            - Pointer to data buffer where read data
**                           is stored
**         dataSize        - size of data buffer in bytes
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t McuI2CSpy_ReadRegData(uint32_t addr, uint8_t *data, size_t dataSize)
{
  uint8_t addrBuf[4];

  addrBuf[3] = (uint8_t)(addr&0xff);
  addrBuf[2] = (uint8_t)((addr&0xff00)>>8);
  addrBuf[1] = (uint8_t)((addr&0xff0000)>>16);
  addrBuf[0] = (uint8_t)((addr&0xff000000)>>24);
  return McuGenericI2C_ReadAddress(McuI2CSpy_deviceData.deviceAddr, &addrBuf[4-McuI2CSpy_deviceData.addrSize],
     McuI2CSpy_deviceData.addrSize, data, dataSize);
}

/*
** ===================================================================
**     Method      :  WriteRegData (component I2CSpy)
**
**     Description :
**         Writes data starting from a register address to the current
**         device
**     Parameters  :
**         NAME            - DESCRIPTION
**         addr            - Address in device
**       * data            - Pointer to data to write
**         dataSize        - Size of data in bytes
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t McuI2CSpy_WriteRegData(uint32_t addr, uint8_t *data, uint16_t dataSize)
{
  uint8_t addrBuf[4];

  addrBuf[3] = (uint8_t)(addr&0xff);
  addrBuf[2] = (uint8_t)((addr&0xff00)>>8);
  addrBuf[1] = (uint8_t)((addr&0xff0000)>>16);
  addrBuf[0] = (uint8_t)((addr&0xff000000)>>24);
  return McuGenericI2C_WriteAddress(McuI2CSpy_deviceData.deviceAddr, &addrBuf[4-McuI2CSpy_deviceData.addrSize],
     McuI2CSpy_deviceData.addrSize, data, dataSize);
}

/* END McuI2CSpy. */

/*!
** @}
*/
