/*
 * power.c
 *
 * Code generation for function 'power'
 *
 * C source code generated on: Wed Sep 11 07:29:22 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "main.h"
#include "power.h"

/* Function Definitions */
void power(const uint8_T a[270000], uint8_T y[270000])
{
  int32_T k;
  uint8_T ak;
  uint8_T bku;
  int32_T exitg1;
  int32_T i1;
  for (k = 0; k < 270000; k++) {
    ak = a[k];
    y[k] = 1;
    bku = 2;
    do {
      exitg1 = 0;
      if ((bku & 1) != 0) {
        i1 = (int32_T)((uint32_T)ak * y[k]);
        if ((uint32_T)i1 > 255U) {
          i1 = 255;
        }

        y[k] = (uint8_T)i1;
      }

      bku = (uint8_T)((uint32_T)bku >> 1);
      if (bku == 0) {
        exitg1 = 1;
      } else {
        i1 = (int32_T)((uint32_T)ak * ak);
        if ((uint32_T)i1 > 255U) {
          i1 = 255;
        }

        ak = (uint8_T)i1;
      }
    } while (exitg1 == 0);
  }
}

/* End of code generation (power.c) */
