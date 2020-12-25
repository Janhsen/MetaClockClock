/*
 * matrixpixel.c
 *
 * Author: Erich Styger
 * License: PDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "matrixpixel.h"
#include "matrix.h"

#if PL_CONFIG_USE_LED_PIXEL
// old MATRIX_SetLEDPixelColor
void MPIXEL_SetColor(int32_t x, int32_t y, int32_t z, uint8_t red, uint8_t green, uint8_t blue) {
  /* \todo assuming 8x2 pixels in line */
  NEO_SetPixelRGB(NEOC_LANE_START, x*2, red, green, blue); /* pixel one */
  NEO_SetPixelRGB(NEOC_LANE_START, (x*2)+1, red, green, blue); /* pixel two */
}

#endif /* PL_CONFIG_USE_LED_PIXEL */