/*
 * imshift_emxutil.h
 *
 * Code generation for function 'imshift_emxutil'
 *
 * C source code generated on: Wed Sep 11 07:52:15 2013
 *
 */

#ifndef __IMSHIFT_EMXUTIL_H__
#define __IMSHIFT_EMXUTIL_H__
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
#include "imshift_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize, const emlrtRTEInfo *srcLocation);
extern void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
extern void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int32_T numDimensions, const emlrtRTEInfo *srcLocation, boolean_T doPush);
#endif
/* End of code generation (imshift_emxutil.h) */
