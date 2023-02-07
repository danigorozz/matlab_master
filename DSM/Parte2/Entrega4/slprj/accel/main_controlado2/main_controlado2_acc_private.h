#ifndef RTW_HEADER_main_controlado2_acc_private_h_
#define RTW_HEADER_main_controlado2_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "main_controlado2_acc.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
#ifndef UCHAR_MAX
#include <limits.h>
#endif
#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T main_controlado2_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) ; real_T
main_controlado2_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T
tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) ; void main_controlado2_RMS_Init ( SimStruct
* S , B_RMS_main_controlado2_T * localB , DW_RMS_main_controlado2_T * localDW
, P_RMS_main_controlado2_T * localP , X_RMS_main_controlado2_T * localX ) ;
void main_controlado2_RMS_Deriv ( SimStruct * S , B_RMS_main_controlado2_T *
localB , DW_RMS_main_controlado2_T * localDW , XDot_RMS_main_controlado2_T *
localXdot ) ; void main_controlado2_RMS_ForcingFunction ( SimStruct * S ,
B_RMS_main_controlado2_T * localB , DW_RMS_main_controlado2_T * localDW ,
XDot_RMS_main_controlado2_T * localXdot ) ; void main_controlado2_RMS_Disable
( SimStruct * S , DW_RMS_main_controlado2_T * localDW ) ; void
main_controlado2_RMS_Update ( SimStruct * S , B_RMS_main_controlado2_T *
localB , DW_RMS_main_controlado2_T * localDW , P_RMS_main_controlado2_T *
localP ) ; void main_controlado2_RMS ( SimStruct * S , boolean_T rtu_Enable ,
real_T rtu_In , B_RMS_main_controlado2_T * localB , DW_RMS_main_controlado2_T
* localDW , P_RMS_main_controlado2_T * localP , X_RMS_main_controlado2_T *
localX , XDis_RMS_main_controlado2_T * localXdis ) ; void
main_controlado2_TrueRMS_Init ( SimStruct * S , B_TrueRMS_main_controlado2_T
* localB , DW_TrueRMS_main_controlado2_T * localDW ,
P_TrueRMS_main_controlado2_T * localP , X_TrueRMS_main_controlado2_T * localX
) ; void main_controlado2_TrueRMS_Deriv ( SimStruct * S ,
B_TrueRMS_main_controlado2_T * localB , DW_TrueRMS_main_controlado2_T *
localDW , XDot_TrueRMS_main_controlado2_T * localXdot ) ; void
main_controlado2_TrueRMS_ForcingFunction ( SimStruct * S ,
B_TrueRMS_main_controlado2_T * localB , DW_TrueRMS_main_controlado2_T *
localDW , XDot_TrueRMS_main_controlado2_T * localXdot ) ; void
main_controlado2_TrueRMS_ZC ( SimStruct * S , B_TrueRMS_main_controlado2_T *
localB , DW_TrueRMS_main_controlado2_T * localDW ,
P_TrueRMS_main_controlado2_T * localP , ZCV_TrueRMS_main_controlado2_T *
localZCSV ) ; void main_controlado2_TrueRMS_Disable ( SimStruct * S ,
DW_TrueRMS_main_controlado2_T * localDW ) ; void
main_controlado2_TrueRMS_Update ( SimStruct * S ,
B_TrueRMS_main_controlado2_T * localB , DW_TrueRMS_main_controlado2_T *
localDW , P_TrueRMS_main_controlado2_T * localP ) ; void
main_controlado2_TrueRMS ( SimStruct * S , boolean_T rtu_Enable , real_T
rtu_In , B_TrueRMS_main_controlado2_T * localB ,
DW_TrueRMS_main_controlado2_T * localDW , P_TrueRMS_main_controlado2_T *
localP , X_TrueRMS_main_controlado2_T * localX ,
XDis_TrueRMS_main_controlado2_T * localXdis ) ; void
main_controlado2_RMS_Term ( SimStruct * const S ) ; void
main_controlado2_TrueRMS_Term ( SimStruct * const S ) ;
#endif
