/*
 * platform_common.h
 *
 * Author: Erich Styger
 * License: PDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_COMMON_H_
#define PLATFORM_COMMON_H_

/* this header file gets included in the project specific platform.h */

#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_LPC845_2X2 || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_LPC845_1X4 || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_LPC845_BRK
  #define PL_CONFIG_BOARD_MCU     PL_CONFIG_BOARD_ID_MCU_LPC845
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512
  #define PL_CONFIG_BOARD_MCU     PL_CONFIG_BOARD_ID_MCU_K22FN512
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN64  || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PIXELUNIT_K02FN64
  #define PL_CONFIG_BOARD_MCU     PL_CONFIG_BOARD_ID_MCU_K02FN64
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN128  || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PIXELUNIT_K02FN128
  #define PL_CONFIG_BOARD_MCU     PL_CONFIG_BOARD_ID_MCU_K02FN128
#endif
/* CPU/Board selection: only one can be active! \todo remove? */
#define PL_CONFIG_IS_LPC845        (PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_LPC845)     /* LPC845 */
#define PL_CONFIG_IS_TINYK22       (PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K22FN512) /* Kinetis K22FN512 */
#define PL_CONFIG_IS_K02           (PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN64 || PL_CONFIG_BOARD_MCU==PL_CONFIG_BOARD_ID_MCU_K02FN128) /* Kinetis K02FN64 or K02FN128 */
/* ********************************************************************************************************** */

/* selection if master or client */
#define PL_CONFIG_IS_MASTER        (PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_LPC845_BRK || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512) /* Master configuration, otherwise it is the client */
#define PL_CONFIG_IS_CLIENT        (!PL_CONFIG_IS_MASTER) /* Client configuration, otherwise it is the master */



/* predefined Matrix configurations: */
#if PL_MATRIX_CONFIGURATION_ID==PL_MATRIX_ID_CLOCK_8x3 /* first small 'meta-clock, 6 LPC845 boards building a 8x3 matrix */
  #define PL_MATRIX_CONFIG_IS_8x3    (1 && PL_CONFIG_IS_MASTER) /* original 8x3 matrix configuration with 24 clocks */
  #define PL_MATRIX_CONFIG_IS_12x5   (0 && PL_CONFIG_IS_MASTER) /* new 8x3 matrix configuration with 60 clocks */
  #define PL_MATRIX_CONFIG_IS_RGB    (0 && PL_CONFIG_IS_MASTER) /* if matrix has RGB rings */
  #define PL_CONFIG_IS_NEW_MODULAR   (0) /* new modular boards with power-off switch */
  #define PL_CONFIG_BOARD_MASTER_K22_WS2812B    (0 && PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512)  /* if it is the K22 master controlling the LEDs directly */
#elif PL_MATRIX_CONFIGURATION_ID==PL_MATRIX_ID_CLOCK_12x5_60B /* McuOneEclipse '60 billion lights' configuration: LPC845 boards (4 clocks), total 60 clocks, with RGB ring controlled by tinyK22 */
  #define PL_MATRIX_CONFIG_IS_8x3    (0 && PL_CONFIG_IS_MASTER) /* original 8x3 matrix configuration with 24 clocks */
  #define PL_MATRIX_CONFIG_IS_12x5   (1 && PL_CONFIG_IS_MASTER) /* new 8x3 matrix configuration with 60 clocks */
  #define PL_MATRIX_CONFIG_IS_RGB    (1 && PL_CONFIG_IS_MASTER) /* if matrix has RGB rings */
  #define PL_CONFIG_IS_NEW_MODULAR   (0) /* new modular boards with power-off switch */
  #define PL_CONFIG_BOARD_MASTER_K22_WS2812B    (1 && PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512)  /* if it is the K22 master controlling the LEDs directly */
#elif PL_MATRIX_CONFIGURATION_ID==PL_MATRIX_ID_CLOCK_12x5_MOD /* new 60 'modular' clock configuration */
  #define PL_MATRIX_CONFIG_IS_8x3    (0 && PL_CONFIG_IS_MASTER) /* original 8x3 matrix configuration with 24 clocks */
  #define PL_MATRIX_CONFIG_IS_12x5   (1 && PL_CONFIG_IS_MASTER) /* new 8x3 matrix configuration with 60 clocks */
  #define PL_MATRIX_CONFIG_IS_RGB    (0 && PL_CONFIG_IS_MASTER) /* if matrix has RGB rings */
  #define PL_CONFIG_IS_NEW_MODULAR   (1) /* new modular boards with power-off switch */
  #define PL_CONFIG_BOARD_MASTER_K22_WS2812B    (0 && PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512)  /* if it is the K22 master controlling the LEDs directly */
#elif PL_MATRIX_CONFIGURATION_ID==PL_MATRIX_ID_CLOCK_12x9_ALEXIS /* 16x9 matrix by Alexis */
  #define PL_MATRIX_CONFIG_IS_8x3    (0 && PL_CONFIG_IS_MASTER) /* original 8x3 matrix configuration with 24 clocks */
  #define PL_MATRIX_CONFIG_IS_12x5   (0 && PL_CONFIG_IS_MASTER) /* new 8x3 matrix configuration with 60 clocks */
  #define PL_MATRIX_CONFIG_IS_16x9   (1 && PL_CONFIG_IS_MASTER) /* new 16x9 matrix configuration with 144 clocks */
  #define PL_MATRIX_CONFIG_IS_RGB    (0 && PL_CONFIG_IS_MASTER) /* if matrix has RGB rings */
  #define PL_CONFIG_IS_NEW_MODULAR   (0) /* new modular boards with power-off switch */
  #define PL_CONFIG_BOARD_MASTER_K22_WS2812B    (0 && PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512)  /* if it is the K22 master controlling the LEDs directly */
#elif PL_MATRIX_CONFIGURATION_ID==PL_MATRIX_ID_SMARTWALL_8x5
  #define PL_MATRIX_CONFIG_IS_8x3    (0 && PL_CONFIG_IS_MASTER) /* original 8x3 matrix configuration with 24 clocks */
  #define PL_MATRIX_CONFIG_IS_12x5   (0 && PL_CONFIG_IS_MASTER) /* new 8x3 matrix configuration with 60 clocks */
  #define PL_MATRIX_CONFIG_IS_RGB    (0 && PL_CONFIG_IS_MASTER) /* if matrix has RGB rings */
  #define PL_CONFIG_IS_NEW_MODULAR   (0) /* new modular boards with power-off switch */
  #define PL_CONFIG_BOARD_MASTER_K22_WS2812B    (0 && PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512)  /* if it is the K22 master controlling the LEDs directly */
#endif

/* hardware versions for boards with LPC845:
 * V0.1: initial version with 2x2 arrangement
 * V1.0: second version with 1x4 arrangement, different pin assignment and better hall sensors */
#if 1
  #define PL_CONFIG_BOARD_VERSION   (10) /* 1: V0.1, 10: V1.0 */
#else
  #define PL_CONFIG_BOARD_VERSION   (1) /* 1: V0.1, 10: V1.0 */
#endif

/* number of clocks/motors on a single (slave) board */
#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN64 || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN128
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD     (2)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_X   (2)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Y   (1)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (2)
  #define PL_CONFIG_BOARD_NOF_MOTOR_DRIVER (1)
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PIXELUNIT_K02FN64 || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_PIXELUNIT_K02FN128
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD     (4)  /* temporary on 4, final board has 8! */
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_X   (4)  /* temporary on 4, final board has 8! */
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Y   (1)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (1)
  #define PL_CONFIG_BOARD_NOF_MOTOR_DRIVER (1) /* temporary 1, final is 2 */
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_LPC845_2X2
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD     (4)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_X   (2)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Y   (2)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (2)
  #define PL_CONFIG_BOARD_NOF_MOTOR_DRIVER (2)
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_LPC845_1X4
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD     (4)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_X   (4)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Y   (1)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (2)
  #define PL_CONFIG_BOARD_NOF_MOTOR_DRIVER (2)
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512 && PL_CONFIG_BOARD_MASTER_K22_WS2812B
  /* virtual steppers for LED rings: settings for a virtual LPC845_Clock4 board */
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD     (4)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_X   (4)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Y   (1)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (2)
  #define PL_CONFIG_BOARD_NOF_MOTOR_DRIVER (2)
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512 /* dummy entries only */
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD     (0)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_X   (0)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Y   (0)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (0)
  #define PL_CONFIG_BOARD_NOF_MOTOR_DRIVER (0)
#elif PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_LPC845_BRK /* dummy entries only */
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD     (0)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_X   (0)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Y   (0)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (0)
  #define PL_CONFIG_NOF_CLOCK_ON_BOARD_Z   (0)
  #define PL_CONFIG_BOARD_NOF_MOTOR_DRIVER (0)
#endif

/* new defines, remove the old ones */
#define PL_CONFIG_NOF_STEPPER_ON_BOARD      PL_CONFIG_NOF_CLOCK_ON_BOARD
#define PL_CONFIG_NOF_STEPPER_ON_BOARD_X    PL_CONFIG_NOF_CLOCK_ON_BOARD_X
#define PL_CONFIG_NOF_STEPPER_ON_BOARD_Y    PL_CONFIG_NOF_CLOCK_ON_BOARD_Y
#define PL_CONFIG_NOF_STEPPER_ON_BOARD_Z    PL_CONFIG_NOF_CLOCK_ON_BOARD_Z

#define PL_CONFIG_WORLD_CLOCK         (0) /* legacy, clock showing different time zones */

#define PL_CONFIG_USE_SHELL           (1) /* use command line shell */
#define PL_CONFIG_USE_RTT             (1 && (PL_CONFIG_IS_CLIENT || PL_CONFIG_IS_TINYK22)) /* use SEGGER RTT (only possible with a J-Link */
#define PL_CONFIG_USE_RTC             (1 && (PL_CONFIG_IS_MASTER || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN128)) /* 1: enable RTC; 0: disable it */
#define PL_CONFIG_USE_RS485           (1 && PL_CONFIG_USE_SHELL) /* RS-485 connection, 1: enabled, 0: disabled: it requires the shell to parse the commands */
#define PL_CONFIG_USE_NVMC            (1) /* using non-volatile configuration memory */
#define PL_CONFIG_USE_WDT             (0) /* if using watchdog timer, disable for easier debugging */
#define PL_CONFIG_USE_DEMOS           (1 && ((PL_CONFIG_IS_MASTER && PL_CONFIG_USE_RS485) || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN128)) /* if using demos or not */
#define PL_CONFIG_USE_BLE             (1 && PL_CONFIG_IS_TINYK22) /* if using BLE or not */
#define PL_CONFIG_USE_BLE_MSG         (1 && PL_CONFIG_USE_BLE) /* if using BLE Bluefuit app messages */
#define PL_CONFIG_USE_ESP32           (0 && PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512) /* if using the ESP32 */
#define PL_CONFIG_USE_SHT31           (1 && PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512 && PL_CONFIG_USE_I2C) /* if using SHT31 sensor */
#define PL_CONFIG_USE_NEO_PIXEL_HW    (0 && (PL_CONFIG_BOARD_MASTER_K22_WS2812B || PL_CONFIG_IS_K02)) /* 1: drives NeoPixels/WS2812B directly on the board */
#define PL_CONFIG_USE_MOTOR_ON_OFF    (1 && (PL_CONFIG_IS_NEW_MODULAR || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN64 || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_CLOCK_K02FN128)) /* using hardware to turn off/on the stepper motors to reduce power */

#define PL_CONFIG_USE_VIRTUAL_STEPPER (PL_CONFIG_BOARD_MASTER_K22_WS2812B)
#define PL_CONFIG_USE_STEPPER         (1 && (PL_CONFIG_IS_CLIENT || PL_CONFIG_USE_VIRTUAL_STEPPER)) /* enable stepper function, both motors and virtual (LED) stepper */
#define PL_CONFIG_USE_LED_RING        (0 && PL_CONFIG_USE_NEO_PIXEL_HW) /* if LED ring is present or available. This is used for showing the hands, etc */
#define PL_CONFIG_USE_LED_STEPPER     (0 && PL_CONFIG_USE_STEPPER && PL_CONFIG_USE_NEO_PIXEL_HW && PL_CONFIG_IS_TINYK22) /* virtual LED Stepper without real stepper motor */
#define PL_CONFIG_USE_X12_STEPPER     (1 && PL_CONFIG_USE_STEPPER && (PL_CONFIG_IS_K02 || PL_CONFIG_IS_LPC845)) /* if X12 stepper motors are used */
#define PL_CONFIG_USE_X12_LED_STEPPER (0 && PL_CONFIG_USE_X12_STEPPER && PL_CONFIG_USE_NEO_PIXEL_HW)  /* real X12 stepper with real LED ring */

#define PL_CONFIG_USE_LOW_POWER       (0)  /* if using low power mode */

/* client only: */
#define PL_CONFIG_USE_MAG_SENSOR      (0 && PL_CONFIG_IS_CLIENT)      /* has magnets and hall sensors */
#define PL_CONFIG_USE_LED_DIMMING     (0 && PL_CONFIG_USE_NEO_PIXEL_HW)
#define PL_CONFIG_USE_DUAL_HANDS      (1 && PL_CONFIG_USE_NEO_PIXEL_HW)   /* dual hand on Z axis */
#define PL_CONFIG_USE_AUTOMATIC_DEMO_MODE  (0 && PL_CONFIG_IS_CLIENT) /* play automatic demo after power-on */

/* master only: */
#define PL_CONFIG_USE_SHELL_UART    (1 && PL_CONFIG_IS_MASTER) /* using UART for USB-CDC to host */
#define PL_CONFIG_USE_I2C           (1 && PL_CONFIG_IS_MASTER) /* use I2C bus */
#define PL_CONFIG_USE_HW_I2C        (CONFIG_USE_HW_I2C) /* this is set in IncludMcuLibConfig.h! */
#define PL_CONFIG_USE_EXT_I2C_RTC   (1 && PL_CONFIG_USE_RTC && PL_CONFIG_USE_I2C) /* DS3231 with AT24C32 */
#define PL_CONFIG_USE_EXT_EEPROM    (1 && PL_CONFIG_USE_I2C) /* AT24C32 */

#define PL_CONFIG_USE_CLOCK         (0 && PL_CONFIG_USE_RTC)  /* 1: application implements a clock */
#define PL_CONFIG_USE_INTERMEZZO    (1 && PL_CONFIG_USE_CLOCK && PL_CONFIG_IS_MASTER && PL_CONFIG_USE_RS485)

#define PL_CONFIG_USE_MCU_LOG       (McuLog_CONFIG_IS_ENABLED) /* configured in IncludeMcuLibConfig.h */

/* NYI or not applicable */
#define PL_CONFIG_USE_KBI           (0)
#define PL_CONFIG_USE_GUI           (0)
#define PL_CONFIG_USE_BUTTON        (0)
#define PL_CONFIG_USE_USB_CDC       (0) /* not supported on LPC845 */
#define PL_CONFIG_USE_I2C_SPY       (0 && PL_CONFIG_USE_I2C) /* using shell component to scan I2C bus */
#define PL_CONFIG_USE_ULN2003       (0 && PL_CONFIG_USE_STEPPER) /* using ULN2003 stepper motors */

#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_MASTER_K22FN512 && McuExtRTC_CONFIG_DEVICE!=3232
  #error "The master board with the tinyK22 uses the DS3232"
#endif


#endif /* PLATFORM_COMMON_H_ */