/*
 * imshift.c
 *
 * Code generation for function 'imshift'
 *
 * C source code generated on: Wed Sep 11 07:29:22 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "main.h"
#include "imshift.h"
#include "main_emxutil.h"

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 1, 23, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m" };

static emlrtBCInfo emlrtBCI = { 1, 400, 20, 13, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtBCInfo b_emlrtBCI = { 1, 225, 15, 11, "I", "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m", 0 };

static emlrtECInfo emlrtECI = { -1, 13, 5, "imshift",
  "C:/Users/spas/Desktop/matlab/imshift.m" };

/* Function Definitions */
void imshift(uint8_T I[270000], const real_T disparity[2])
{
  real_T xStart2;
  real_T yStart2;
  real_T xEnd2;
  real_T yEnd2;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T i5;
  int32_T tmp_size_idx_0;
  int32_T loop_ub;
  int32_T i6;
  int32_T tmp_data[225];
  int32_T b_tmp_size_idx_0;
  int32_T b_tmp_data[400];
  emxArray_uint8_T *b_I;
  int32_T iv3[3];
  int32_T i7;
  int32_T b_loop_ub;
  int32_T i8;
  int32_T c_I[3];
  int32_T c_tmp_data[400];
  int32_T d_tmp_data[225];
  emxArray_uint8_T *d_I;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  xStart2 = muDoubleScalarMax(1.0, 1.0 + disparity[0]);
  yStart2 = muDoubleScalarMax(1.0, 1.0 + disparity[1]);
  xEnd2 = muDoubleScalarMin(225.0, 225.0 + disparity[0]);
  yEnd2 = muDoubleScalarMin(400.0, 400.0 + disparity[1]);
  i2 = (int32_T)muDoubleScalarMax(1.0, 1.0 - disparity[0]) - 1;
  i3 = (int32_T)muDoubleScalarMin(225.0, 225.0 - disparity[0]);
  i4 = (int32_T)muDoubleScalarMax(1.0, 1.0 - disparity[1]) - 1;
  i5 = (int32_T)muDoubleScalarMin(400.0, 400.0 - disparity[1]);
  tmp_size_idx_0 = ((int32_T)xEnd2 - (int32_T)xStart2) + 1;
  loop_ub = (int32_T)xEnd2 - (int32_T)xStart2;
  for (i6 = 0; i6 <= loop_ub; i6++) {
    tmp_data[i6] = ((int32_T)xStart2 + i6) - 1;
  }

  b_tmp_size_idx_0 = ((int32_T)yEnd2 - (int32_T)yStart2) + 1;
  loop_ub = (int32_T)yEnd2 - (int32_T)yStart2;
  for (i6 = 0; i6 <= loop_ub; i6++) {
    b_tmp_data[i6] = ((int32_T)yStart2 + i6) - 1;
  }

  emxInit_uint8_T(&b_I, 3, &emlrtRTEI, TRUE);
  iv3[0] = tmp_size_idx_0;
  iv3[1] = b_tmp_size_idx_0;
  iv3[2] = 3;
  i6 = b_I->size[0] * b_I->size[1] * b_I->size[2];
  b_I->size[0] = i3 - i2;
  b_I->size[1] = i5 - i4;
  b_I->size[2] = 3;
  emxEnsureCapacity((emxArray__common *)b_I, i6, (int32_T)sizeof(uint8_T),
                    &emlrtRTEI);
  for (i6 = 0; i6 < 3; i6++) {
    loop_ub = i5 - i4;
    for (i7 = 0; i7 < loop_ub; i7++) {
      b_loop_ub = i3 - i2;
      for (i8 = 0; i8 < b_loop_ub; i8++) {
        b_I->data[(i8 + b_I->size[0] * i7) + b_I->size[0] * b_I->size[1] * i6] =
          I[((i2 + i8) + 225 * (i4 + i7)) + 90000 * i6];
      }
    }
  }

  for (i6 = 0; i6 < 3; i6++) {
    c_I[i6] = b_I->size[i6];
  }

  emxFree_uint8_T(&b_I);
  emlrtSubAssignSizeCheckR2012b(iv3, 3, c_I, 3, &emlrtECI, emlrtRootTLSGlobal);
  for (i6 = 0; i6 < b_tmp_size_idx_0; i6++) {
    c_tmp_data[i6] = b_tmp_data[i6];
  }

  for (i6 = 0; i6 < tmp_size_idx_0; i6++) {
    d_tmp_data[i6] = tmp_data[i6];
  }

  emxInit_uint8_T(&d_I, 3, &emlrtRTEI, TRUE);
  i6 = d_I->size[0] * d_I->size[1] * d_I->size[2];
  d_I->size[0] = i3 - i2;
  d_I->size[1] = i5 - i4;
  d_I->size[2] = 3;
  emxEnsureCapacity((emxArray__common *)d_I, i6, (int32_T)sizeof(uint8_T),
                    &emlrtRTEI);
  for (i6 = 0; i6 < 3; i6++) {
    loop_ub = i5 - i4;
    for (i7 = 0; i7 < loop_ub; i7++) {
      b_loop_ub = i3 - i2;
      for (i8 = 0; i8 < b_loop_ub; i8++) {
        d_I->data[(i8 + d_I->size[0] * i7) + d_I->size[0] * d_I->size[1] * i6] =
          I[((i2 + i8) + 225 * (i4 + i7)) + 90000 * i6];
      }
    }
  }

  for (i2 = 0; i2 < 3; i2++) {
    loop_ub = d_I->size[1];
    for (i3 = 0; i3 < loop_ub; i3++) {
      b_loop_ub = d_I->size[0];
      for (i4 = 0; i4 < b_loop_ub; i4++) {
        I[(d_tmp_data[i4] + 225 * c_tmp_data[i3]) + 90000 * i2] = d_I->data[(i4
          + d_I->size[0] * i3) + d_I->size[0] * d_I->size[1] * i2];
      }
    }
  }

  emxFree_uint8_T(&d_I);
  if (xStart2 == 1.0) {
    if (xEnd2 + 1.0 > 225.0) {
      i2 = 0;
      i3 = 0;
    } else {
      i2 = (int32_T)(xEnd2 + 1.0);
      i2 = emlrtDynamicBoundsCheckFastR2012b(i2, 1, 225, &b_emlrtBCI,
        emlrtRootTLSGlobal) - 1;
      i3 = 225;
    }

    tmp_size_idx_0 = i3 - i2;
    for (i3 = 0; i3 < 3; i3++) {
      for (i4 = 0; i4 < 400; i4++) {
        for (i5 = 0; i5 < tmp_size_idx_0; i5++) {
          I[((i2 + i5) + 225 * i4) + 90000 * i3] = 0;
        }
      }
    }
  } else {
    for (i2 = 0; i2 < 3; i2++) {
      for (i3 = 0; i3 < 400; i3++) {
        loop_ub = (int32_T)(xStart2 - 1.0);
        for (i4 = 0; i4 < loop_ub; i4++) {
          I[(i4 + 225 * i3) + 90000 * i2] = 0;
        }
      }
    }
  }

  if (yStart2 == 1.0) {
    if (yEnd2 + 1.0 > 400.0) {
      i2 = 0;
      i3 = 0;
    } else {
      i2 = (int32_T)(yEnd2 + 1.0);
      i2 = emlrtDynamicBoundsCheckFastR2012b(i2, 1, 400, &emlrtBCI,
        emlrtRootTLSGlobal) - 1;
      i3 = 400;
    }

    tmp_size_idx_0 = i3 - i2;
    for (i3 = 0; i3 < 3; i3++) {
      for (i4 = 0; i4 < tmp_size_idx_0; i4++) {
        for (i5 = 0; i5 < 225; i5++) {
          I[(i5 + 225 * (i2 + i4)) + 90000 * i3] = 0;
        }
      }
    }
  } else {
    for (i2 = 0; i2 < 3; i2++) {
      loop_ub = (int32_T)(yStart2 - 1.0);
      for (i3 = 0; i3 < loop_ub; i3++) {
        for (i4 = 0; i4 < 225; i4++) {
          I[(i4 + 225 * i3) + 90000 * i2] = 0;
        }
      }
    }
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (imshift.c) */
