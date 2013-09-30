/*
 * cost_volume_mex.c
 *
 * Code generation for function 'cost_volume'
 *
 * C source code generated on: Wed Sep 11 07:11:46 2013
 *
 */

/* Include files */
#include "mex.h"
#include "cost_volume_api.h"
#include "cost_volume_initialize.h"
#include "cost_volume_terminate.h"

/* Function Declarations */
static void cost_volume_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
MEXFUNCTION_LINKAGE mxArray *emlrtMexFcnProperties(void);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "cost_volume", NULL, false, {2045744189U,2170104910U,2743257031U,4284093946U}, NULL };
emlrtCTX emlrtRootTLSGlobal = NULL;

/* Function Definitions */
static void cost_volume_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  mxArray *outputs[1];
  mxArray *inputs[8];
  int n = 0;
  int nOutputs = (nlhs < 1 ? 1 : nlhs);
  int nInputs = nrhs;
  cost_volumeStackData* cost_volumeStackDataLocal = (cost_volumeStackData*)mxCalloc(1,sizeof(cost_volumeStackData));
  /* Module initialization. */
  cost_volume_initialize(&emlrtContextGlobal);
  /* Check for proper number of arguments. */
  if (nrhs != 8) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs", 5, mxINT32_CLASS, 8, mxCHAR_CLASS, 11, "cost_volume");
  } else if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:TooManyOutputArguments", 3, mxCHAR_CLASS, 11, "cost_volume");
  }
  /* Temporary copy for mex inputs. */
  for (n = 0; n < nInputs; ++n) {
    inputs[n] = (mxArray *)prhs[n];
  }
  /* Call the function. */
  cost_volume_api(cost_volumeStackDataLocal, (const mxArray**)inputs, (const mxArray**)outputs);
  /* Copy over outputs to the caller. */
  for (n = 0; n < nOutputs; ++n) {
    plhs[n] = emlrtReturnArrayR2009a(outputs[n]);
  }
  /* Module finalization. */
  cost_volume_terminate();
  mxFree(cost_volumeStackDataLocal);
}

void cost_volume_atexit_wrapper(void)
{
   cost_volume_atexit();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  mexAtExit(cost_volume_atexit_wrapper);
  /* Dispatch the entry-point. */
  cost_volume_mexFunction(nlhs, plhs, nrhs, prhs);
}

mxArray *emlrtMexFcnProperties(void)
{
  const char *mexProperties[] = {
    "Version",
    "ResolvedFunctions",
    "EntryPoints"};
  const char *epProperties[] = {
    "Name",
    "NumberOfInputs",
    "NumberOfOutputs",
    "ConstantInputs"};
  mxArray *xResult = mxCreateStructMatrix(1,1,3,mexProperties);
  mxArray *xEntryPoints = mxCreateStructMatrix(1,1,4,epProperties);
  mxArray *xInputs = NULL;
  xInputs = mxCreateLogicalMatrix(1, 8);
  mxSetFieldByNumber(xEntryPoints, 0, 0, mxCreateString("cost_volume"));
  mxSetFieldByNumber(xEntryPoints, 0, 1, mxCreateDoubleScalar(8));
  mxSetFieldByNumber(xEntryPoints, 0, 2, mxCreateDoubleScalar(1));
  mxSetFieldByNumber(xEntryPoints, 0, 3, xInputs);
  mxSetFieldByNumber(xResult, 0, 0, mxCreateString("8.1.0.604 (R2013a)"));
  mxSetFieldByNumber(xResult, 0, 1, (mxArray*)emlrtMexFcnResolvedFunctionsInfo());
  mxSetFieldByNumber(xResult, 0, 2, xEntryPoints);

  return xResult;
}
/* End of code generation (cost_volume_mex.c) */
