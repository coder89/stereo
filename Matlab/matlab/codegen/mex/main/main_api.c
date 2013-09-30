/*
 * main_api.c
 *
 * Code generation for function 'main_api'
 *
 * C source code generated on: Wed Sep 11 07:29:22 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "main.h"
#include "main_api.h"

/* Function Declarations */
static uint8_T (*b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[270000];
static uint8_T (*c_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId))[270000];
static uint8_T (*emlrt_marshallIn(const mxArray *Il, const char_T *identifier))
  [270000];
static const mxArray *emlrt_marshallOut(real_T u);
static void info_helper(ResolvedFunctionInfo info[55]);

/* Function Definitions */
static uint8_T (*b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[270000]
{
  uint8_T (*y)[270000];
  y = c_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static uint8_T (*c_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[270000]
{
  uint8_T (*ret)[270000];
  int32_T iv1[3];
  int32_T i;
  static const int16_T iv2[3] = { 225, 400, 3 };

  for (i = 0; i < 3; i++) {
    iv1[i] = iv2[i];
  }

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "uint8", FALSE, 3U,
    iv1);
  ret = (uint8_T (*)[270000])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static uint8_T (*emlrt_marshallIn(const mxArray *Il, const char_T *identifier))
  [270000]
{
  uint8_T (*y)[270000];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(emlrtAlias(Il), &thisId);
  emlrtDestroyArray(&Il);
  return y;
}
  static const mxArray *emlrt_marshallOut(real_T u)
{
  const mxArray *y;
  const mxArray *m1;
  y = NULL;
  m1 = mxCreateDoubleScalar(u);
  emlrtAssign(&y, m1);
  return y;
}

static void info_helper(ResolvedFunctionInfo info[55])
{
  info[0].context = "[E]C:/Users/spas/Desktop/matlab/main.m";
  info[0].name = "mtimes";
  info[0].dominantType = "double";
  info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  info[0].fileTimeLo = 1289519692U;
  info[0].fileTimeHi = 0U;
  info[0].mFileTimeLo = 0U;
  info[0].mFileTimeHi = 0U;
  info[1].context = "[E]C:/Users/spas/Desktop/matlab/main.m";
  info[1].name = "cost_volume";
  info[1].dominantType = "uint8";
  info[1].resolved = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[1].fileTimeLo = 1378876141U;
  info[1].fileTimeHi = 0U;
  info[1].mFileTimeLo = 0U;
  info[1].mFileTimeHi = 0U;
  info[2].context = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[2].name = "imshift";
  info[2].dominantType = "uint8";
  info[2].resolved = "[E]C:/Users/spas/Desktop/matlab/imshift.m";
  info[2].fileTimeLo = 1378840875U;
  info[2].fileTimeHi = 0U;
  info[2].mFileTimeLo = 0U;
  info[2].mFileTimeHi = 0U;
  info[3].context = "[E]C:/Users/spas/Desktop/matlab/imshift.m";
  info[3].name = "max";
  info[3].dominantType = "double";
  info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m";
  info[3].fileTimeLo = 1311255316U;
  info[3].fileTimeHi = 0U;
  info[3].mFileTimeLo = 0U;
  info[3].mFileTimeHi = 0U;
  info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m";
  info[4].name = "eml_min_or_max";
  info[4].dominantType = "char";
  info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  info[4].fileTimeLo = 1334071490U;
  info[4].fileTimeHi = 0U;
  info[4].mFileTimeLo = 0U;
  info[4].mFileTimeHi = 0U;
  info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  info[5].name = "eml_scalar_eg";
  info[5].dominantType = "double";
  info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  info[5].fileTimeLo = 1286818796U;
  info[5].fileTimeHi = 0U;
  info[5].mFileTimeLo = 0U;
  info[5].mFileTimeHi = 0U;
  info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  info[6].name = "eml_scalexp_alloc";
  info[6].dominantType = "double";
  info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  info[6].fileTimeLo = 1352424860U;
  info[6].fileTimeHi = 0U;
  info[6].mFileTimeLo = 0U;
  info[6].mFileTimeHi = 0U;
  info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  info[7].name = "eml_index_class";
  info[7].dominantType = "";
  info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[7].fileTimeLo = 1323170578U;
  info[7].fileTimeHi = 0U;
  info[7].mFileTimeLo = 0U;
  info[7].mFileTimeHi = 0U;
  info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  info[8].name = "eml_scalar_eg";
  info[8].dominantType = "double";
  info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  info[8].fileTimeLo = 1286818796U;
  info[8].fileTimeHi = 0U;
  info[8].mFileTimeLo = 0U;
  info[8].mFileTimeHi = 0U;
  info[9].context = "[E]C:/Users/spas/Desktop/matlab/imshift.m";
  info[9].name = "min";
  info[9].dominantType = "double";
  info[9].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  info[9].fileTimeLo = 1311255318U;
  info[9].fileTimeHi = 0U;
  info[9].mFileTimeLo = 0U;
  info[9].mFileTimeHi = 0U;
  info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  info[10].name = "eml_min_or_max";
  info[10].dominantType = "char";
  info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  info[10].fileTimeLo = 1334071490U;
  info[10].fileTimeHi = 0U;
  info[10].mFileTimeLo = 0U;
  info[10].mFileTimeHi = 0U;
  info[11].context = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[11].name = "power";
  info[11].dominantType = "uint8";
  info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  info[11].fileTimeLo = 1348191930U;
  info[11].fileTimeHi = 0U;
  info[11].mFileTimeLo = 0U;
  info[11].mFileTimeHi = 0U;
  info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!intpower";
  info[12].name = "eml_scalar_eg";
  info[12].dominantType = "uint8";
  info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  info[12].fileTimeLo = 1286818796U;
  info[12].fileTimeHi = 0U;
  info[12].mFileTimeLo = 0U;
  info[12].mFileTimeHi = 0U;
  info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!intpower";
  info[13].name = "eml_scalexp_alloc";
  info[13].dominantType = "uint8";
  info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  info[13].fileTimeLo = 1352424860U;
  info[13].fileTimeHi = 0U;
  info[13].mFileTimeLo = 0U;
  info[13].mFileTimeHi = 0U;
  info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!intpower";
  info[14].name = "eml_unsigned_class";
  info[14].dominantType = "char";
  info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  info[14].fileTimeLo = 1323170580U;
  info[14].fileTimeHi = 0U;
  info[14].mFileTimeLo = 0U;
  info[14].mFileTimeHi = 0U;
  info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!intpower";
  info[15].name = "floor";
  info[15].dominantType = "double";
  info[15].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  info[15].fileTimeLo = 1343830380U;
  info[15].fileTimeHi = 0U;
  info[15].mFileTimeLo = 0U;
  info[15].mFileTimeHi = 0U;
  info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  info[16].name = "eml_scalar_floor";
  info[16].dominantType = "double";
  info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  info[16].fileTimeLo = 1286818726U;
  info[16].fileTimeHi = 0U;
  info[16].mFileTimeLo = 0U;
  info[16].mFileTimeHi = 0U;
  info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!intpower";
  info[17].name = "mtimes";
  info[17].dominantType = "uint8";
  info[17].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  info[17].fileTimeLo = 1289519692U;
  info[17].fileTimeHi = 0U;
  info[17].mFileTimeLo = 0U;
  info[17].mFileTimeHi = 0U;
  info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!intpower";
  info[18].name = "intmax";
  info[18].dominantType = "char";
  info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  info[18].fileTimeLo = 1311255316U;
  info[18].fileTimeHi = 0U;
  info[18].mFileTimeLo = 0U;
  info[18].mFileTimeHi = 0U;
  info[19].context = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[19].name = "sum";
  info[19].dominantType = "uint8";
  info[19].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[19].fileTimeLo = 1314736612U;
  info[19].fileTimeHi = 0U;
  info[19].mFileTimeLo = 0U;
  info[19].mFileTimeHi = 0U;
  info[20].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[20].name = "eml_assert_valid_dim";
  info[20].dominantType = "double";
  info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m";
  info[20].fileTimeLo = 1286818694U;
  info[20].fileTimeHi = 0U;
  info[20].mFileTimeLo = 0U;
  info[20].mFileTimeHi = 0U;
  info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m";
  info[21].name = "eml_scalar_floor";
  info[21].dominantType = "double";
  info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  info[21].fileTimeLo = 1286818726U;
  info[21].fileTimeHi = 0U;
  info[21].mFileTimeLo = 0U;
  info[21].mFileTimeHi = 0U;
  info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m";
  info[22].name = "eml_index_class";
  info[22].dominantType = "";
  info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[22].fileTimeLo = 1323170578U;
  info[22].fileTimeHi = 0U;
  info[22].mFileTimeLo = 0U;
  info[22].mFileTimeHi = 0U;
  info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m";
  info[23].name = "intmax";
  info[23].dominantType = "char";
  info[23].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  info[23].fileTimeLo = 1311255316U;
  info[23].fileTimeHi = 0U;
  info[23].mFileTimeLo = 0U;
  info[23].mFileTimeHi = 0U;
  info[24].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[24].name = "eml_index_class";
  info[24].dominantType = "";
  info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[24].fileTimeLo = 1323170578U;
  info[24].fileTimeHi = 0U;
  info[24].mFileTimeLo = 0U;
  info[24].mFileTimeHi = 0U;
  info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[25].name = "eml_scalar_eg";
  info[25].dominantType = "double";
  info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  info[25].fileTimeLo = 1286818796U;
  info[25].fileTimeHi = 0U;
  info[25].mFileTimeLo = 0U;
  info[25].mFileTimeHi = 0U;
  info[26].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[26].name = "eml_matrix_vstride";
  info[26].dominantType = "uint8";
  info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  info[26].fileTimeLo = 1286818788U;
  info[26].fileTimeHi = 0U;
  info[26].mFileTimeLo = 0U;
  info[26].mFileTimeHi = 0U;
  info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  info[27].name = "eml_index_minus";
  info[27].dominantType = "double";
  info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  info[27].fileTimeLo = 1286818778U;
  info[27].fileTimeHi = 0U;
  info[27].mFileTimeLo = 0U;
  info[27].mFileTimeHi = 0U;
  info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  info[28].name = "eml_index_class";
  info[28].dominantType = "";
  info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[28].fileTimeLo = 1323170578U;
  info[28].fileTimeHi = 0U;
  info[28].mFileTimeLo = 0U;
  info[28].mFileTimeHi = 0U;
  info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  info[29].name = "eml_index_class";
  info[29].dominantType = "";
  info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[29].fileTimeLo = 1323170578U;
  info[29].fileTimeHi = 0U;
  info[29].mFileTimeLo = 0U;
  info[29].mFileTimeHi = 0U;
  info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m";
  info[30].name = "eml_size_prod";
  info[30].dominantType = "uint8";
  info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  info[30].fileTimeLo = 1286818798U;
  info[30].fileTimeHi = 0U;
  info[30].mFileTimeLo = 0U;
  info[30].mFileTimeHi = 0U;
  info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  info[31].name = "eml_index_class";
  info[31].dominantType = "";
  info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[31].fileTimeLo = 1323170578U;
  info[31].fileTimeHi = 0U;
  info[31].mFileTimeLo = 0U;
  info[31].mFileTimeHi = 0U;
  info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  info[32].name = "eml_int_forloop_overflow_check";
  info[32].dominantType = "";
  info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  info[32].fileTimeLo = 1346510340U;
  info[32].fileTimeHi = 0U;
  info[32].mFileTimeLo = 0U;
  info[32].mFileTimeHi = 0U;
  info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  info[33].name = "intmax";
  info[33].dominantType = "char";
  info[33].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  info[33].fileTimeLo = 1311255316U;
  info[33].fileTimeHi = 0U;
  info[33].mFileTimeLo = 0U;
  info[33].mFileTimeHi = 0U;
  info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  info[34].name = "eml_index_times";
  info[34].dominantType = "double";
  info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  info[34].fileTimeLo = 1286818780U;
  info[34].fileTimeHi = 0U;
  info[34].mFileTimeLo = 0U;
  info[34].mFileTimeHi = 0U;
  info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  info[35].name = "eml_index_class";
  info[35].dominantType = "";
  info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[35].fileTimeLo = 1323170578U;
  info[35].fileTimeHi = 0U;
  info[35].mFileTimeLo = 0U;
  info[35].mFileTimeHi = 0U;
  info[36].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[36].name = "eml_matrix_npages";
  info[36].dominantType = "uint8";
  info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  info[36].fileTimeLo = 1286818786U;
  info[36].fileTimeHi = 0U;
  info[36].mFileTimeLo = 0U;
  info[36].mFileTimeHi = 0U;
  info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  info[37].name = "eml_index_plus";
  info[37].dominantType = "double";
  info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  info[37].fileTimeLo = 1286818778U;
  info[37].fileTimeHi = 0U;
  info[37].mFileTimeLo = 0U;
  info[37].mFileTimeHi = 0U;
  info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  info[38].name = "eml_index_class";
  info[38].dominantType = "";
  info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[38].fileTimeLo = 1323170578U;
  info[38].fileTimeHi = 0U;
  info[38].mFileTimeLo = 0U;
  info[38].mFileTimeHi = 0U;
  info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  info[39].name = "eml_index_class";
  info[39].dominantType = "";
  info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  info[39].fileTimeLo = 1323170578U;
  info[39].fileTimeHi = 0U;
  info[39].mFileTimeLo = 0U;
  info[39].mFileTimeHi = 0U;
  info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m";
  info[40].name = "eml_size_prod";
  info[40].dominantType = "uint8";
  info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_prod.m";
  info[40].fileTimeLo = 1286818798U;
  info[40].fileTimeHi = 0U;
  info[40].mFileTimeLo = 0U;
  info[40].mFileTimeHi = 0U;
  info[41].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[41].name = "eml_int_forloop_overflow_check";
  info[41].dominantType = "";
  info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  info[41].fileTimeLo = 1346510340U;
  info[41].fileTimeHi = 0U;
  info[41].mFileTimeLo = 0U;
  info[41].mFileTimeHi = 0U;
  info[42].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[42].name = "eml_index_plus";
  info[42].dominantType = "double";
  info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  info[42].fileTimeLo = 1286818778U;
  info[42].fileTimeHi = 0U;
  info[42].mFileTimeLo = 0U;
  info[42].mFileTimeHi = 0U;
  info[43].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m";
  info[43].name = "eml_index_plus";
  info[43].dominantType = "coder.internal.indexInt";
  info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  info[43].fileTimeLo = 1286818778U;
  info[43].fileTimeHi = 0U;
  info[43].mFileTimeLo = 0U;
  info[43].mFileTimeHi = 0U;
  info[44].context = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[44].name = "sqrt";
  info[44].dominantType = "double";
  info[44].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  info[44].fileTimeLo = 1343830386U;
  info[44].fileTimeHi = 0U;
  info[44].mFileTimeLo = 0U;
  info[44].mFileTimeHi = 0U;
  info[45].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  info[45].name = "eml_error";
  info[45].dominantType = "char";
  info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  info[45].fileTimeLo = 1343830358U;
  info[45].fileTimeHi = 0U;
  info[45].mFileTimeLo = 0U;
  info[45].mFileTimeHi = 0U;
  info[46].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  info[46].name = "eml_scalar_sqrt";
  info[46].dominantType = "double";
  info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  info[46].fileTimeLo = 1286818738U;
  info[46].fileTimeHi = 0U;
  info[46].mFileTimeLo = 0U;
  info[46].mFileTimeHi = 0U;
  info[47].context = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[47].name = "abs";
  info[47].dominantType = "uint8";
  info[47].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  info[47].fileTimeLo = 1343830366U;
  info[47].fileTimeHi = 0U;
  info[47].mFileTimeLo = 0U;
  info[47].mFileTimeHi = 0U;
  info[48].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  info[48].name = "eml_scalar_abs";
  info[48].dominantType = "uint8";
  info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  info[48].fileTimeLo = 1286818712U;
  info[48].fileTimeHi = 0U;
  info[48].mFileTimeLo = 0U;
  info[48].mFileTimeHi = 0U;
  info[49].context = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[49].name = "min";
  info[49].dominantType = "double";
  info[49].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  info[49].fileTimeLo = 1311255318U;
  info[49].fileTimeHi = 0U;
  info[49].mFileTimeLo = 0U;
  info[49].mFileTimeHi = 0U;
  info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  info[50].name = "isequal";
  info[50].dominantType = "double";
  info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  info[50].fileTimeLo = 1286818758U;
  info[50].fileTimeHi = 0U;
  info[50].mFileTimeLo = 0U;
  info[50].mFileTimeHi = 0U;
  info[51].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  info[51].name = "eml_isequal_core";
  info[51].dominantType = "double";
  info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  info[51].fileTimeLo = 1286818786U;
  info[51].fileTimeHi = 0U;
  info[51].mFileTimeLo = 0U;
  info[51].mFileTimeHi = 0U;
  info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  info[52].name = "isnan";
  info[52].dominantType = "double";
  info[52].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  info[52].fileTimeLo = 1286818760U;
  info[52].fileTimeHi = 0U;
  info[52].mFileTimeLo = 0U;
  info[52].mFileTimeHi = 0U;
  info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  info[53].name = "eml_int_forloop_overflow_check";
  info[53].dominantType = "";
  info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  info[53].fileTimeLo = 1346510340U;
  info[53].fileTimeHi = 0U;
  info[53].mFileTimeLo = 0U;
  info[53].mFileTimeHi = 0U;
  info[54].context = "[E]C:/Users/spas/Desktop/matlab/cost_volume.m";
  info[54].name = "mtimes";
  info[54].dominantType = "double";
  info[54].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  info[54].fileTimeLo = 1289519692U;
  info[54].fileTimeHi = 0U;
  info[54].mFileTimeLo = 0U;
  info[54].mFileTimeHi = 0U;
}

const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  ResolvedFunctionInfo info[55];
  ResolvedFunctionInfo u[55];
  int32_T i;
  const mxArray *y;
  int32_T iv0[1];
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
  info_helper(info);
  for (i = 0; i < 55; i++) {
    u[i] = info[i];
  }

  y = NULL;
  iv0[0] = 55;
  emlrtAssign(&y, mxCreateStructArray(1, iv0, 0, NULL));
  for (i = 0; i < 55; i++) {
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

void main_api(mainStackData *SD, const mxArray * const prhs[4], const mxArray
              *plhs[1])
{
  uint8_T (*Il)[270000];
  uint8_T (*Ir)[270000];
  uint8_T (*Gl)[270000];
  uint8_T (*Gr)[270000];
  real_T result;

  /* Marshall function inputs */
  Il = emlrt_marshallIn(emlrtAlias(prhs[0]), "Il");
  Ir = emlrt_marshallIn(emlrtAlias(prhs[1]), "Ir");
  Gl = emlrt_marshallIn(emlrtAlias(prhs[2]), "Gl");
  Gr = emlrt_marshallIn(emlrtAlias(prhs[3]), "Gr");

  /* Invoke the target function */
  result = main(SD, *Il, *Ir, *Gl, *Gr);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(result);
}

/* End of code generation (main_api.c) */
