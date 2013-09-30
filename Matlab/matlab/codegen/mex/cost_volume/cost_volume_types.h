/*
 * cost_volume_types.h
 *
 * Code generation for function 'cost_volume'
 *
 * C source code generated on: Wed Sep 11 07:11:45 2013
 *
 */

#ifndef __COST_VOLUME_TYPES_H__
#define __COST_VOLUME_TYPES_H__

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
#ifndef typedef_cost_volumeStackData
#define typedef_cost_volumeStackData
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
} cost_volumeStackData;
#endif /*typedef_cost_volumeStackData*/
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

#endif
/* End of code generation (cost_volume_types.h) */
