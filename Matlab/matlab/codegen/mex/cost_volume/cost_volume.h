/*
 * cost_volume.h
 *
 * Code generation for function 'cost_volume'
 *
 * C source code generated on: Wed Sep 11 07:11:46 2013
 *
 */

#ifndef __COST_VOLUME_H__
#define __COST_VOLUME_H__
/* Include files */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "cost_volume_types.h"

/* Function Declarations */
extern void cost_volume(cost_volumeStackData *SD, const uint8_T I_left[270000], const uint8_T I_right[270000], const uint8_T G_left[270000], uint8_T G_right[270000], const real_T disparity[2], real_T alpha, const real_T T_c[90000], const real_T T_g[90000], real_T result[90000]);
#endif
/* End of code generation (cost_volume.h) */
