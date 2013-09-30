/*
 * imshift_initialize.c
 *
 * Code generation for function 'imshift_initialize'
 *
 * C source code generated on: Wed Sep 11 07:52:15 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "imshift.h"
#include "imshift_initialize.h"

/* Variable Definitions */
static const volatile char_T *emlrtBreakCheckR2012bFlagVar;

/* Function Definitions */
void imshift_initialize(emlrtContext *aContext)
{
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, FALSE, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (imshift_initialize.c) */
