/*
 * imshift.c
 *
 * Code generation for function 'imshift'
 *
 * C source code generated on: Wed Sep 11 07:52:15 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "imshift.h"
#include "imshift_emxutil.h"

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 1, 23, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m" };

static emlrtDCInfo emlrtDCI = { 13, 42, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo emlrtBCI = { 1, 225, 13, 42, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtDCInfo b_emlrtDCI = { 13, 56, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo b_emlrtBCI = { 1, 400, 13, 56, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtDCInfo c_emlrtDCI = { 13, 7, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo c_emlrtBCI = { 1, 225, 13, 7, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtDCInfo d_emlrtDCI = { 13, 21, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo d_emlrtBCI = { 1, 400, 13, 21, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtECInfo emlrtECI = { -1, 13, 5, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m" };

static emlrtDCInfo e_emlrtDCI = { 15, 11, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo e_emlrtBCI = { 1, 225, 15, 11, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtDCInfo f_emlrtDCI = { 17, 11, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo f_emlrtBCI = { 1, 225, 17, 11, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtDCInfo g_emlrtDCI = { 20, 13, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo g_emlrtBCI = { 1, 400, 20, 13, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtDCInfo h_emlrtDCI = { 22, 13, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 1 };

static emlrtBCInfo h_emlrtBCI = { 1, 400, 22, 13, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

/* Function Definitions */
void imshift(uint8_T I[270000], const real_T disparity[2], uint8_T result[270000])
{
  real_T xStart1;
  real_T yStart1;
  real_T xStart2;
  real_T yStart2;
  real_T xEnd1;
  real_T yEnd1;
  real_T xEnd2;
  real_T yEnd2;
  int32_T i0;
  int32_T i1;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T i5;
  int32_T i6;
  int32_T unnamed_idx_0;
  int32_T loop_ub;
  int32_T i7;
  int32_T tmp_data[225];
  int32_T b_tmp_data[400];
  emxArray_uint8_T *b_I;
  int32_T iv0[3];
  int32_T c_I[3];
  emxArray_uint8_T *d_I;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  xStart1 = muDoubleScalarMax(1.0, 1.0 - disparity[0]);
  yStart1 = muDoubleScalarMax(1.0, 1.0 - disparity[1]);
  xStart2 = muDoubleScalarMax(1.0, 1.0 + disparity[0]);
  yStart2 = muDoubleScalarMax(1.0, 1.0 + disparity[1]);
  xEnd1 = muDoubleScalarMin(225.0, 225.0 - disparity[0]);
  yEnd1 = muDoubleScalarMin(400.0, 400.0 - disparity[1]);
  xEnd2 = muDoubleScalarMin(225.0, 225.0 + disparity[0]);
  yEnd2 = muDoubleScalarMin(400.0, 400.0 + disparity[1]);
  if (xStart1 > xEnd1) {
    i0 = 0;
    i1 = 0;
  } else {
    i0 = (int32_T)emlrtIntegerCheckFastR2012b(xStart1, &emlrtDCI,
      emlrtRootTLSGlobal);
    i0 = emlrtDynamicBoundsCheckFastR2012b(i0, 1, 225, &emlrtBCI,
      emlrtRootTLSGlobal) - 1;
    i1 = (int32_T)emlrtIntegerCheckFastR2012b(xEnd1, &emlrtDCI,
      emlrtRootTLSGlobal);
    i1 = emlrtDynamicBoundsCheckFastR2012b(i1, 1, 225, &emlrtBCI,
      emlrtRootTLSGlobal);
  }

  if (yStart1 > yEnd1) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = (int32_T)emlrtIntegerCheckFastR2012b(yStart1, &b_emlrtDCI,
      emlrtRootTLSGlobal);
    i2 = emlrtDynamicBoundsCheckFastR2012b(i2, 1, 400, &b_emlrtBCI,
      emlrtRootTLSGlobal) - 1;
    i3 = (int32_T)emlrtIntegerCheckFastR2012b(yEnd1, &b_emlrtDCI,
      emlrtRootTLSGlobal);
    i3 = emlrtDynamicBoundsCheckFastR2012b(i3, 1, 400, &b_emlrtBCI,
      emlrtRootTLSGlobal);
  }

  if (xStart2 > xEnd2) {
    i4 = 0;
    i5 = 0;
  } else {
    i4 = (int32_T)emlrtIntegerCheckFastR2012b(xStart2, &c_emlrtDCI,
      emlrtRootTLSGlobal);
    i4 = emlrtDynamicBoundsCheckFastR2012b(i4, 1, 225, &c_emlrtBCI,
      emlrtRootTLSGlobal) - 1;
    i5 = (int32_T)emlrtIntegerCheckFastR2012b(xEnd2, &c_emlrtDCI,
      emlrtRootTLSGlobal);
    i5 = emlrtDynamicBoundsCheckFastR2012b(i5, 1, 225, &c_emlrtBCI,
      emlrtRootTLSGlobal);
  }

  if (yStart2 > yEnd2) {
    i6 = 0;
    unnamed_idx_0 = 0;
  } else {
    i6 = (int32_T)emlrtIntegerCheckFastR2012b(yStart2, &d_emlrtDCI,
      emlrtRootTLSGlobal);
    i6 = emlrtDynamicBoundsCheckFastR2012b(i6, 1, 400, &d_emlrtBCI,
      emlrtRootTLSGlobal) - 1;
    unnamed_idx_0 = (int32_T)emlrtIntegerCheckFastR2012b(yEnd2, &d_emlrtDCI,
      emlrtRootTLSGlobal);
    unnamed_idx_0 = emlrtDynamicBoundsCheckFastR2012b(unnamed_idx_0, 1, 400,
      &d_emlrtBCI, emlrtRootTLSGlobal);
  }

  loop_ub = i5 - i4;
  for (i7 = 0; i7 < loop_ub; i7++) {
    tmp_data[i7] = i4 + i7;
  }

  loop_ub = unnamed_idx_0 - i6;
  for (i7 = 0; i7 < loop_ub; i7++) {
    b_tmp_data[i7] = i6 + i7;
  }

  emxInit_uint8_T(&b_I, 3, &emlrtRTEI, TRUE);
  iv0[0] = i5 - i4;
  iv0[1] = unnamed_idx_0 - i6;
  iv0[2] = 3;
  i4 = b_I->size[0] * b_I->size[1] * b_I->size[2];
  b_I->size[0] = i1 - i0;
  b_I->size[1] = i3 - i2;
  b_I->size[2] = 3;
  emxEnsureCapacity((emxArray__common *)b_I, i4, (int32_T)sizeof(uint8_T),
                    &emlrtRTEI);
  for (i4 = 0; i4 < 3; i4++) {
    loop_ub = i3 - i2;
    for (i5 = 0; i5 < loop_ub; i5++) {
      unnamed_idx_0 = i1 - i0;
      for (i6 = 0; i6 < unnamed_idx_0; i6++) {
        b_I->data[(i6 + b_I->size[0] * i5) + b_I->size[0] * b_I->size[1] * i4] =
          I[((i0 + i6) + 225 * (i2 + i5)) + 90000 * i4];
      }
    }
  }

  for (i4 = 0; i4 < 3; i4++) {
    c_I[i4] = b_I->size[i4];
  }

  emxFree_uint8_T(&b_I);
  emxInit_uint8_T(&d_I, 3, &emlrtRTEI, TRUE);
  emlrtSubAssignSizeCheckR2012b(iv0, 3, c_I, 3, &emlrtECI, emlrtRootTLSGlobal);
  i4 = d_I->size[0] * d_I->size[1] * d_I->size[2];
  d_I->size[0] = i1 - i0;
  d_I->size[1] = i3 - i2;
  d_I->size[2] = 3;
  emxEnsureCapacity((emxArray__common *)d_I, i4, (int32_T)sizeof(uint8_T),
                    &emlrtRTEI);
  for (i4 = 0; i4 < 3; i4++) {
    loop_ub = i3 - i2;
    for (i5 = 0; i5 < loop_ub; i5++) {
      unnamed_idx_0 = i1 - i0;
      for (i6 = 0; i6 < unnamed_idx_0; i6++) {
        d_I->data[(i6 + d_I->size[0] * i5) + d_I->size[0] * d_I->size[1] * i4] =
          I[((i0 + i6) + 225 * (i2 + i5)) + 90000 * i4];
      }
    }
  }

  for (i0 = 0; i0 < 3; i0++) {
    loop_ub = d_I->size[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      unnamed_idx_0 = d_I->size[0];
      for (i2 = 0; i2 < unnamed_idx_0; i2++) {
        I[(tmp_data[i2] + 225 * b_tmp_data[i1]) + 90000 * i0] = d_I->data[(i2 +
          d_I->size[0] * i1) + d_I->size[0] * d_I->size[1] * i0];
      }
    }
  }

  emxFree_uint8_T(&d_I);
  if (xStart2 == 1.0) {
    if (xEnd2 + 1.0 > 225.0) {
      i0 = 1;
      i1 = 1;
    } else {
      i0 = (int32_T)emlrtIntegerCheckFastR2012b(xEnd2 + 1.0, &e_emlrtDCI,
        emlrtRootTLSGlobal);
      i0 = emlrtDynamicBoundsCheckFastR2012b(i0, 1, 225, &e_emlrtBCI,
        emlrtRootTLSGlobal);
      i1 = 226;
    }

    unnamed_idx_0 = i1 - i0;
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < 400; i2++) {
        for (i3 = 0; i3 < unnamed_idx_0; i3++) {
          I[(((i0 + i3) + 225 * i2) + 90000 * i1) - 1] = 0;
        }
      }
    }
  } else {
    if (1.0 > xStart2 - 1.0) {
      loop_ub = 0;
    } else {
      xStart1 = xStart2 - 1.0;
      i0 = (int32_T)emlrtIntegerCheckFastR2012b(xStart1, &f_emlrtDCI,
        emlrtRootTLSGlobal);
      loop_ub = emlrtDynamicBoundsCheckFastR2012b(i0, 1, 225, &f_emlrtBCI,
        emlrtRootTLSGlobal);
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i1 = 0; i1 < 400; i1++) {
        for (i2 = 0; i2 < loop_ub; i2++) {
          I[(i2 + 225 * i1) + 90000 * i0] = 0;
        }
      }
    }
  }

  if (yStart2 == 1.0) {
    if (yEnd2 + 1.0 > 400.0) {
      i0 = 1;
      i1 = 1;
    } else {
      i0 = (int32_T)emlrtIntegerCheckFastR2012b(yEnd2 + 1.0, &g_emlrtDCI,
        emlrtRootTLSGlobal);
      i0 = emlrtDynamicBoundsCheckFastR2012b(i0, 1, 400, &g_emlrtBCI,
        emlrtRootTLSGlobal);
      i1 = 401;
    }

    unnamed_idx_0 = i1 - i0;
    for (i1 = 0; i1 < 3; i1++) {
      for (i2 = 0; i2 < unnamed_idx_0; i2++) {
        memset(&I[225 * ((i0 + i2) - 1) + 90000 * i1], 0, 225U * sizeof(uint8_T));
      }
    }
  } else {
    if (1.0 > yStart2 - 1.0) {
      loop_ub = 0;
    } else {
      xStart1 = yStart2 - 1.0;
      i0 = (int32_T)emlrtIntegerCheckFastR2012b(xStart1, &h_emlrtDCI,
        emlrtRootTLSGlobal);
      loop_ub = emlrtDynamicBoundsCheckFastR2012b(i0, 1, 400, &h_emlrtBCI,
        emlrtRootTLSGlobal);
    }

    for (i0 = 0; i0 < 3; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        memset(&I[225 * i1 + 90000 * i0], 0, 225U * sizeof(uint8_T));
      }
    }
  }

  memcpy(&result[0], &I[0], 270000U * sizeof(uint8_T));
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (imshift.c) */
