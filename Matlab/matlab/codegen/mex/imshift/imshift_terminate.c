/*
 * imshift_terminate.c
 *
 * Code generation for function 'imshift_terminate'
 *
 * C source code generated on: Wed Sep 11 07:52:15 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "imshift.h"
#include "imshift_terminate.h"

/* Function Definitions */
void imshift_atexit(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void imshift_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (imshift_terminate.c) */
