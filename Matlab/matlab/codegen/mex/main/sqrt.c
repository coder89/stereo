/*
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 * C source code generated on: Wed Sep 11 07:29:22 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "main.h"
#include "sqrt.h"

/* Function Definitions */
void b_sqrt(real_T x[90000])
{
  int32_T k;
  for (k = 0; k < 90000; k++) {
    x[k] = muDoubleScalarSqrt(x[k]);
  }
}

/* End of code generation (sqrt.c) */
