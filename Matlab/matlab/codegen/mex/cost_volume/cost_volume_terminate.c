/*
 * cost_volume_terminate.c
 *
 * Code generation for function 'cost_volume_terminate'
 *
 * C source code generated on: Wed Sep 11 07:11:46 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "cost_volume.h"
#include "cost_volume_terminate.h"

/* Function Definitions */
void cost_volume_atexit(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void cost_volume_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (cost_volume_terminate.c) */
