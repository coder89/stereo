/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 * C source code generated on: Wed Sep 11 07:11:46 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "cost_volume.h"
#include "sum.h"

/* Function Definitions */
void sum(const uint8_T x[270000], real_T y[90000])
{
  int32_T iy;
  int32_T ixstart;
  int32_T j;
  int32_T ix;
  real_T s;
  int32_T k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 90000; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 2; k++) {
      ix += 90000;
      s += (real_T)x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/* End of code generation (sum.c) */
