/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Wed Sep 11 07:11:46 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "cost_volume.h"
#include "abs.h"

/* Function Definitions */
void b_abs(const uint8_T x[270000], uint8_T y[270000])
{
  memcpy(&y[0], &x[0], 270000U * sizeof(uint8_T));
}

/* End of code generation (abs.c) */
