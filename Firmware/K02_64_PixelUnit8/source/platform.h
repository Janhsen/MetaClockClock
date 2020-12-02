/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "McuLibConfig.h"
#include "platform_id.h"

/* select the board used: */
#define PL_CONFIG_BOARD_ID            (PL_CONFIG_BOARD_ID_PIXELUNIT_K02FN64)

/* *************************************************************************************** */
/* overwrite settings in platform_common.h */
#define PL_CONFIG_USE_NEO_PIXEL_HW      (1) /* has NeoPixels */
#define PL_CONFIG_IS_ANALOG_CLOCK       (0) /* not an analog clock */
#define PL_CONFIG_USE_DUAL_HANDS        (0) /* disable dual hand */
#define PL_CONFIG_USE_LED_PIXEL         (1) /* enable LED pixel */
#define PL_CONFIG_USE_MOTOR_ON_OFF      (1) /* has on/off function */

#include "platform_common.h"


void PL_InitFromTask(void);
void PL_Init(void);

#endif /* PLATFORM_H_ */