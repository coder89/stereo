/*
 * imshift_api.c
 *
 * Code generation for function 'imshift_api'
 *
 * C source code generated on: Wed Sep 11 07:52:15 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "imshift.h"
#include "imshift_api.h"

/* Type Definitions */
#ifndef typedef_ResolvedFunctionInfo
#define typedef_ResolvedFunctionInfo

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} ResolvedFunctionInfo;

#endif                                 /*typedef_ResolvedFunctionInfo*/

/* Function Declarations */
static uint8_T (*b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[270000];
static real_T (*c_emlrt_marshallIn(const mxArray *disparity, const char_T
  *identifier))[2];
static real_T (*d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[2];
static uint8_T (*e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId))[270000];
static uint8_T (*emlrt_marshallIn(const mxArray *I, const char_T *identifier))
  [270000];
static const mxArray *emlrt_marshallOut(uint8_T u[270000]);
static real_T (*f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[2];

/* Function Definitions */
static uint8_T (*b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[270000]
{
  uint8_T (*y)[270000];
  y = e_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T (*c_emlrt_marshallIn(const mxArray *disparity, const char_T
  *identifier))[2]
{
  real_T (*y)[2];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(emlrtAlias(disparity), &thisId);
  emlrtDestroyArray(&disparity);
  return y;
}

static real_T (*d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[2]
{
  real_T (*y)[2];
  y = f_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static uint8_T (*e_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[270000]
{
  uint8_T (*ret)[270000];
  int32_T iv4[3];
  int32_T i;
  static const int16_T iv5[3] = { 225, 400, 3 };

  for (i = 0; i < 3; i++) {
    iv4[i] = iv5[i];
  }

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", FALSE, 3U,
    iv4);
  ret = (uint8_T (*)[270000])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static uint8_T (*emlrt_marshallIn(const mxArray *I, const char_T *identifier))
  [270000]
{
  uint8_T (*y)[270000];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(emlrtAlias(I), &thisId);
  emlrtDestroyArray(&I);
  return y;
}
  static const mxArray *emlrt_marshallOut(uint8_T u[270000])
{
  const mxArray *y;
  static const int32_T iv2[3] = { 0, 0, 0 };

  const mxArray *m1;
  static const int32_T iv3[3] = { 225, 400, 3 };

  y = NULL;
  m1 = mxCreateNumericArray(3, (int32_T *)&iv2, mxUINT8_CLASS, mxREAL);
  mxSetData((mxArray *)m1, (void *)u);
  mxSetDimensions((mxArray *)m1, iv3, 3);
  emlrtAssign(&y, m1);
  return y;
}

static real_T (*f_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[2]
{
  real_T (*ret)[2];
  int32_T iv6[2];
  int32_T i8;
  for (i8 = 0; i8 < 2; i8++) {
    iv6[i8] = 1 + i8;
  }

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", FALSE, 2U,
    iv6);
  ret = (real_T (*)[2])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  ResolvedFunctionInfo info[8];
  ResolvedFunctionInfo (*b_info)[8];
  ResolvedFunctionInfo u[8];
  int32_T i;
  const mxArray *y;
  int32_T iv1[1];
  ResolvedFunctionInfo *r0;
  const char * b_u;
  const mxArray *b_y;
  const mxArray *m0;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  uint32_T c_u;
  const mxArray *f_y;
  const mxArray *g_y;
  const mxArray *h_y;
  const mxArray *i_y;
  nameCaptureInfo = NULL;
  b_info = (ResolvedFunctionInfo (*)[8])info;
  (*b_info)[0].context = "[E]C:/Users/spas/Desktop/matlab/imshift.m";
  (*b_info)[0].name = "max";
  (*b_info)[0].dominantType = "double";
  (*b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m";
  (*b_info)[0].fileTimeLo = 1311255316U;
  (*b_info)[0].fileTimeHi = 0U;
  (*b_info)[0].mFileTimeLo = 0U;
  (*b_info)[0].mFileTimeHi = 0U;
  (*b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m";
  (*b_info)[1].name = "eml_min_or_max";
  (*b_info)[1].dominantType = "char";
  (*b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  (*b_info)[1].fileTimeLo = 1334071490U;
  (*b_info)[1].fileTimeHi = 0U;
  (*b_info)[1].mFileTimeLo = 0U;
  (*b_info)[1].mFileTimeHi = 0U;
  (*b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  (*b_info)[2].name = "eml_scalar_eg";
  (*b_info)[2].dominantType = "double";
  (*b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*b_info)[2].fileTimeLo = 1286818796U;
  (*b_info)[2].fileTimeHi = 0U;
  (*b_info)[2].mFileTimeLo = 0U;
  (*b_info)[2].mFileTimeHi = 0U;
  (*b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  (*b_info)[3].name = "eml_scalexp_alloc";
  (*b_info)[3].dominantType = "double";
  (*b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  (*b_info)[3].fileTimeLo = 1352424860U;
  (*b_info)[3].fileTimeHi = 0U;
  (*b_info)[3].mFileTimeLo = 0U;
  (*b_info)[3].mFileTimeHi = 0U;
  (*b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  (*b_info)[4].name = "eml_index_class";
  (*b_info)[4].dominantType = "";
  (*b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  (*b_info)[4].fileTimeLo = 1323170578U;
  (*b_info)[4].fileTimeHi = 0U;
  (*b_info)[4].mFileTimeLo = 0U;
  (*b_info)[4].mFileTimeHi = 0U;
  (*b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  (*b_info)[5].name = "eml_scalar_eg";
  (*b_info)[5].dominantType = "double";
  (*b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*b_info)[5].fileTimeLo = 1286818796U;
  (*b_info)[5].fileTimeHi = 0U;
  (*b_info)[5].mFileTimeLo = 0U;
  (*b_info)[5].mFileTimeHi = 0U;
  (*b_info)[6].context = "[E]C:/Users/spas/Desktop/matlab/imshift.m";
  (*b_info)[6].name = "min";
  (*b_info)[6].dominantType = "double";
  (*b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  (*b_info)[6].fileTimeLo = 1311255318U;
  (*b_info)[6].fileTimeHi = 0U;
  (*b_info)[6].mFileTimeLo = 0U;
  (*b_info)[6].mFileTimeHi = 0U;
  (*b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  (*b_info)[7].name = "eml_min_or_max";
  (*b_info)[7].dominantType = "char";
  (*b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  (*b_info)[7].fileTimeLo = 1334071490U;
  (*b_info)[7].fileTimeHi = 0U;
  (*b_info)[7].mFileTimeLo = 0U;
  (*b_info)[7].mFileTimeHi = 0U;
  for (i = 0; i < 8; i++) {
    u[i] = info[i];
  }

  y = NULL;
  iv1[0] = 8;
  emlrtAssign(&y, mxCreateStructArray(1, iv1, 0, NULL));
  for (i = 0; i < 8; i++) {
    r0 = &u[i];
    b_u = r0->context;
    b_y = NULL;
    m0 = mxCreateString(b_u);
    emlrtAssign(&b_y, m0);
    emlrtAddField(y, b_y, "context", i);
    b_u = r0->name;
    c_y = NULL;
    m0 = mxCreateString(b_u);
    emlrtAssign(&c_y, m0);
    emlrtAddField(y, c_y, "name", i);
    b_u = r0->dominantType;
    d_y = NULL;
    m0 = mxCreateString(b_u);
    emlrtAssign(&d_y, m0);
    emlrtAddField(y, d_y, "dominantType", i);
    b_u = r0->resolved;
    e_y = NULL;
    m0 = mxCreateString(b_u);
    emlrtAssign(&e_y, m0);
    emlrtAddField(y, e_y, "resolved", i);
    c_u = r0->fileTimeLo;
    f_y = NULL;
    m0 = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
    *(uint32_T *)mxGetData(m0) = c_u;
    emlrtAssign(&f_y, m0);
    emlrtAddField(y, f_y, "fileTimeLo", i);
    c_u = r0->fileTimeHi;
    g_y = NULL;
    m0 = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
    *(uint32_T *)mxGetData(m0) = c_u;
    emlrtAssign(&g_y, m0);
    emlrtAddField(y, g_y, "fileTimeHi", i);
    c_u = r0->mFileTimeLo;
    h_y = NULL;
    m0 = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
    *(uint32_T *)mxGetData(m0) = c_u;
    emlrtAssign(&h_y, m0);
    emlrtAddField(y, h_y, "mFileTimeLo", i);
    c_u = r0->mFileTimeHi;
    i_y = NULL;
    m0 = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
    *(uint32_T *)mxGetData(m0) = c_u;
    emlrtAssign(&i_y, m0);
    emlrtAddField(y, i_y, "mFileTimeHi", i);
  }

  emlrtAssign(&nameCaptureInfo, y);
  emlrtNameCapturePostProcessR2012a(emlrtAlias(nameCaptureInfo));
  return nameCaptureInfo;
}

void imshift_api(const mxArray *prhs[2], const mxArray *plhs[1])
{
  uint8_T (*result)[270000];
  uint8_T (*I)[270000];
  real_T (*disparity)[2];
  result = (uint8_T (*)[270000])mxMalloc(sizeof(uint8_T [270000]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, FALSE, -1);

  /* Marshall function inputs */
  I = emlrt_marshallIn(emlrtAlias(prhs[0]), "I");
  disparity = c_emlrt_marshallIn(emlrtAlias(prhs[1]), "disparity");

  /* Invoke the target function */
  imshift(*I, *disparity, *result);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*result);
}

/* End of code generation (imshift_api.c) */
