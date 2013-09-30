/*
 * main_types.h
 *
 * Code generation for function 'main'
 *
 * C source code generated on: Wed Sep 11 07:29:22 2013
 *
 */

#ifndef __MAIN_TYPES_H__
#define __MAIN_TYPES_H__

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_ResolvedFunctionInfo
#define typedef_ResolvedFunctionInfo
typedef struct
{
    const char * context;
    const char * name;
    const char * dominantType;
    const char * resolved;
    uint32_T fileTimeLo;
    uint32_T fileTimeHi;
    uint32_T mFileTimeLo;
    uint32_T mFileTimeHi;
} ResolvedFunctionInfo;
#endif /*typedef_ResolvedFunctionInfo*/
#ifndef struct_emxArray__common
#define struct_emxArray__common
struct emxArray__common
{
    void *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray__common*/
#ifndef typedef_emxArray__common
#define typedef_emxArray__common
typedef struct emxArray__common emxArray__common;
#endif /*typedef_emxArray__common*/
#ifndef struct_emxArray_int32_T_225
#define struct_emxArray_int32_T_225
struct emxArray_int32_T_225
{
    int32_T data[225];
    int32_T size[1];
};
#endif /*struct_emxArray_int32_T_225*/
#ifndef typedef_emxArray_int32_T_225
#define typedef_emxArray_int32_T_225
typedef struct emxArray_int32_T_225 emxArray_int32_T_225;
#endif /*typedef_emxArray_int32_T_225*/
#ifndef struct_emxArray_int32_T_400
#define struct_emxArray_int32_T_400
struct emxArray_int32_T_400
{
    int32_T data[400];
    int32_T size[1];
};
#endif /*struct_emxArray_int32_T_400*/
#ifndef typedef_emxArray_int32_T_400
#define typedef_emxArray_int32_T_400
typedef struct emxArray_int32_T_400 emxArray_int32_T_400;
#endif /*typedef_emxArray_int32_T_400*/
#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T
struct emxArray_uint8_T
{
    uint8_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_uint8_T*/
#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T
typedef struct emxArray_uint8_T emxArray_uint8_T;
#endif /*typedef_emxArray_uint8_T*/
#ifndef typedef_mainStackData
#define typedef_mainStackData
typedef struct
{
    struct
    {
        real_T aG[90000];
        real_T aM[90000];
        uint8_T G_left[270000];
        uint8_T uv0[270000];
        uint8_T uv1[270000];
        uint8_T uv2[270000];
    } f0;
    struct
    {
        real_T T_c[90000];
        real_T T_g[90000];
        real_T unusedExpr[90000];
        uint8_T Gr[270000];
    } f1;
} mainStackData;
#endif /*typedef_mainStackData*/

#endif
/* End of code generation (main_types.h) */
