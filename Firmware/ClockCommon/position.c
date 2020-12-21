/*
 * position.c
 *
 * Author: Erich Styger
 * License: PDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "position.h"
#include "matrix.h"
#include <assert.h>

void POS_SetAngle(uint8_t x, uint8_t y, uint8_t z, int16_t angle) {
  assert(x<MATRIX_NOF_STEPPERS_X && y<MATRIX_NOF_STEPPERS_Y && z<MATRIX_NOF_STEPPERS_Z);
#if PL_CONFIG_IS_MASTER
  matrix.angleMap[x][y][z] = angle;
#endif
}

void POS_SetAngleZ0Z1(uint8_t x, uint8_t y, int16_t z0Angle, int16_t z1Angle) {
  POS_SetAngle(x, y, 0, z0Angle);
  POS_SetAngle(x, y, 1, z1Angle);
}

void POS_SetAngleZ0Z1All(int16_t z0Angle, int16_t z1Angle) {
  for(int y=0; y<MATRIX_NOF_STEPPERS_Y; y++) {
    for(int x=0; x<MATRIX_NOF_STEPPERS_X; x++) {
      POS_SetAngleZ0Z1(x, y, z0Angle, z1Angle);
    }
  }
}
