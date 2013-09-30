/*
 * cost_volume.c
 *
 * Code generation for function 'cost_volume'
 *
 * C source code generated on: Wed Sep 11 07:29:22 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "main.h"
#include "cost_volume.h"
#include "sum.h"
#include "abs.h"
#include "imshift.h"
#include "sqrt.h"
#include "power.h"

/* Variable Definitions */
static emlrtRSInfo b_emlrtRSI = { 5, "cost_volume",
  "C:/Users/spas/Desktop/matlab/cost_volume.m" };

static emlrtRSInfo c_emlrtRSI = { 11, "cost_volume",
  "C:/Users/spas/Desktop/matlab/cost_volume.m" };

/* Function Definitions */
void cost_volume(mainStackData *SD, const uint8_T I_left[270000], const uint8_T
                 I_right[270000], const uint8_T G_left[270000], uint8_T G_right
                 [270000], const real_T disparity[2], const real_T T_c[90000],
                 const real_T T_g[90000], real_T result[90000])
{
  int32_T i0;
  int32_T k;
  uint32_T qY;

  /*  Calculate gradient: */
  emlrtPushRtStackR2012b(&b_emlrtRSI, emlrtRootTLSGlobal);
  imshift(G_right, disparity);
  emlrtPopRtStackR2012b(&b_emlrtRSI, emlrtRootTLSGlobal);

  /*  G matrix */
  for (i0 = 0; i0 < 270000; i0++) {
    k = G_left[i0];
    qY = (uint32_T)k - G_right[i0];
    if (qY > (uint32_T)k) {
      qY = 0U;
    }

    k = (int32_T)qY;
    SD->f0.G_left[i0] = (uint8_T)k;
  }

  power(SD->f0.G_left, SD->f0.uv0);
  sum(SD->f0.uv0, SD->f0.aG);
  b_sqrt(SD->f0.aG);

  /*  M matrix */
  emlrtPushRtStackR2012b(&c_emlrtRSI, emlrtRootTLSGlobal);
  memcpy(&SD->f0.uv1[0], &I_right[0], 270000U * sizeof(uint8_T));
  imshift(SD->f0.uv1, disparity);
  for (i0 = 0; i0 < 270000; i0++) {
    k = I_left[i0];
    qY = (uint32_T)k - SD->f0.uv1[i0];
    if (qY > (uint32_T)k) {
      qY = 0U;
    }

    k = (int32_T)qY;
    SD->f0.G_left[i0] = (uint8_T)k;
  }

  b_abs(SD->f0.G_left, SD->f0.uv2);
  sum(SD->f0.uv2, SD->f0.aM);
  emlrtPopRtStackR2012b(&c_emlrtRSI, emlrtRootTLSGlobal);

  /*  result */
  for (k = 0; k < 90000; k++) {
    result[k] = 0.9 * muDoubleScalarMin(T_c[k], SD->f0.aM[k]) +
      0.099999999999999978 * muDoubleScalarMin(T_g[k], SD->f0.aG[k]);
  }
}

/* End of code generation (cost_volume.c) */
