/*
 * main.c
 *
 * Code generation for function 'main'
 *
 * C source code generated on: Wed Sep 11 07:29:22 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "main.h"
#include "cost_volume.h"
#include "main_data.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 28, "main",
  "C:/Users/spas/Desktop/matlab/main.m" };

/* Function Definitions */
real_T main(mainStackData *SD, const uint8_T Il[270000], const uint8_T Ir[270000],
            const uint8_T Gl[270000], const uint8_T Gr[270000])
{
  real_T result;
  int32_T i;
  int32_T j;
  real_T b_i[2];

  /*  Il = ones([5 5 3]); */
  /*  Ir = repmat([[1, 2, 3, 4, 5] */
  /*               [6, 7, 8, 9, 10] */
  /*               [11,12,13,14,15] */
  /*               [16,17,18,19,20] */
  /*               [21,22,23,24,25]]', [1 1 3]); */
  /*           Il=Ir; */
  /*  Ir(:,:,2) = Ir(:,:,2) + 25; */
  /*  Ir(:,:,3) = Ir(:,:,3) + 50; */
  for (i = 0; i < 90000; i++) {
    SD->f1.T_c[i] = 0.028;
    SD->f1.T_g[i] = 0.008;
  }

  for (i = 0; i < 21; i++) {
    for (j = 0; j < 21; j++) {
      emlrtPushRtStackR2012b(&emlrtRSI, emlrtRootTLSGlobal);
      memcpy(&SD->f1.Gr[0], &Gr[0], 270000U * sizeof(uint8_T));
      b_i[0] = (real_T)i - 10.0;
      b_i[1] = (real_T)j - 10.0;
      cost_volume(SD, Il, Ir, Gl, SD->f1.Gr, b_i, SD->f1.T_c, SD->f1.T_g,
                  SD->f1.unusedExpr);
      emlrtPopRtStackR2012b(&emlrtRSI, emlrtRootTLSGlobal);
      emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, emlrtRootTLSGlobal);
    }

    emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, emlrtRootTLSGlobal);
  }

  result = 1.0;

  /*  close all */
  /*  figure */
  /*  hold on */
  /*  subplot(2, 2, 1); */
  /*  imshow(Il); */
  /*  subplot(2, 2, 2); */
  /*  imshow(Ir); */
  /*  subplot(2, 2, [3 4]); */
  /*  imshow(C1, []) */
  /*  hold off */
  return result;
}

/* End of code generation (main.c) */
