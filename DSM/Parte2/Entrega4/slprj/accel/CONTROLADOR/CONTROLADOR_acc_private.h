#ifndef RTW_HEADER_CONTROLADOR_acc_private_h_
#define RTW_HEADER_CONTROLADOR_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "CONTROLADOR_acc.h"
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
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr ,
int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay ,
int_T * maxNewBufSzPtr ) ; real_T CONTROLADOR_acc_rt_TDelayInterpolate (
real_T tMinusDelay , real_T tStart , real_T * uBuf , int_T bufSz , int_T *
lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T
discrete , boolean_T minorStepAndTAtLastMajorOutput ) ; void
CONTROLADOR_RMS_Init ( SimStruct * S , B_RMS_CONTROLADOR_T * localB ,
DW_RMS_CONTROLADOR_T * localDW , P_RMS_CONTROLADOR_T * localP ,
X_RMS_CONTROLADOR_T * localX ) ; void CONTROLADOR_RMS_Deriv ( SimStruct * S ,
B_RMS_CONTROLADOR_T * localB , DW_RMS_CONTROLADOR_T * localDW ,
XDot_RMS_CONTROLADOR_T * localXdot ) ; void CONTROLADOR_RMS_ForcingFunction (
SimStruct * S , B_RMS_CONTROLADOR_T * localB , DW_RMS_CONTROLADOR_T * localDW
, XDot_RMS_CONTROLADOR_T * localXdot ) ; void CONTROLADOR_RMS_Disable (
SimStruct * S , DW_RMS_CONTROLADOR_T * localDW ) ; void
CONTROLADOR_RMS_Update ( SimStruct * S , B_RMS_CONTROLADOR_T * localB ,
DW_RMS_CONTROLADOR_T * localDW , P_RMS_CONTROLADOR_T * localP ) ; void
CONTROLADOR_RMS ( SimStruct * S , boolean_T rtu_Enable , real_T rtu_In ,
B_RMS_CONTROLADOR_T * localB , DW_RMS_CONTROLADOR_T * localDW ,
P_RMS_CONTROLADOR_T * localP , X_RMS_CONTROLADOR_T * localX ,
XDis_RMS_CONTROLADOR_T * localXdis ) ; void CONTROLADOR_TrueRMS_Init (
SimStruct * S , B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T *
localDW , P_TrueRMS_CONTROLADOR_T * localP , X_TrueRMS_CONTROLADOR_T * localX
) ; void CONTROLADOR_TrueRMS_Deriv ( SimStruct * S , B_TrueRMS_CONTROLADOR_T
* localB , DW_TrueRMS_CONTROLADOR_T * localDW , XDot_TrueRMS_CONTROLADOR_T *
localXdot ) ; void CONTROLADOR_TrueRMS_ForcingFunction ( SimStruct * S ,
B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T * localDW ,
XDot_TrueRMS_CONTROLADOR_T * localXdot ) ; void CONTROLADOR_TrueRMS_ZC (
SimStruct * S , B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T *
localDW , P_TrueRMS_CONTROLADOR_T * localP , ZCV_TrueRMS_CONTROLADOR_T *
localZCSV ) ; void CONTROLADOR_TrueRMS_Disable ( SimStruct * S ,
DW_TrueRMS_CONTROLADOR_T * localDW ) ; void CONTROLADOR_TrueRMS_Update (
SimStruct * S , B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T *
localDW , P_TrueRMS_CONTROLADOR_T * localP ) ; void CONTROLADOR_TrueRMS (
SimStruct * S , boolean_T rtu_Enable , real_T rtu_In ,
B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T * localDW ,
P_TrueRMS_CONTROLADOR_T * localP , X_TrueRMS_CONTROLADOR_T * localX ,
XDis_TrueRMS_CONTROLADOR_T * localXdis ) ; void CONTROLADOR_RMS_m_Init (
SimStruct * S , B_RMS_CONTROLADOR_o_T * localB , DW_RMS_CONTROLADOR_m_T *
localDW , P_RMS_CONTROLADOR_d_T * localP , X_RMS_CONTROLADOR_e_T * localX ) ;
void CONTROLADOR_RMS_k_Deriv ( SimStruct * S , B_RMS_CONTROLADOR_o_T * localB
, DW_RMS_CONTROLADOR_m_T * localDW , XDot_RMS_CONTROLADOR_g_T * localXdot ) ;
void CONTROLADOR_RMS_p_ForcingFunction ( SimStruct * S ,
B_RMS_CONTROLADOR_o_T * localB , DW_RMS_CONTROLADOR_m_T * localDW ,
XDot_RMS_CONTROLADOR_g_T * localXdot ) ; void CONTROLADOR_RMS_k_Disable (
SimStruct * S , DW_RMS_CONTROLADOR_m_T * localDW ) ; void
CONTROLADOR_RMS_c_Update ( SimStruct * S , B_RMS_CONTROLADOR_o_T * localB ,
DW_RMS_CONTROLADOR_m_T * localDW , P_RMS_CONTROLADOR_d_T * localP ) ; void
CONTROLADOR_RMS_c ( SimStruct * S , boolean_T rtu_Enable , real_T rtu_In ,
B_RMS_CONTROLADOR_o_T * localB , DW_RMS_CONTROLADOR_m_T * localDW ,
P_RMS_CONTROLADOR_d_T * localP , X_RMS_CONTROLADOR_e_T * localX ,
XDis_RMS_CONTROLADOR_k_T * localXdis ) ; void CONTROLADOR_TrueRMS_g_Init (
SimStruct * S , B_TrueRMS_CONTROLADOR_j_T * localB ,
DW_TrueRMS_CONTROLADOR_o_T * localDW , P_TrueRMS_CONTROLADOR_n_T * localP ,
X_TrueRMS_CONTROLADOR_c_T * localX ) ; void CONTROLADOR_TrueRMS_c_Deriv (
SimStruct * S , B_TrueRMS_CONTROLADOR_j_T * localB ,
DW_TrueRMS_CONTROLADOR_o_T * localDW , XDot_TrueRMS_CONTROLADOR_c_T *
localXdot ) ; void CONTROLADOR_TrueRMS_i_ForcingFunction ( SimStruct * S ,
B_TrueRMS_CONTROLADOR_j_T * localB , DW_TrueRMS_CONTROLADOR_o_T * localDW ,
XDot_TrueRMS_CONTROLADOR_c_T * localXdot ) ; void CONTROLADOR_TrueRMS_j_ZC (
SimStruct * S , B_TrueRMS_CONTROLADOR_j_T * localB ,
DW_TrueRMS_CONTROLADOR_o_T * localDW , P_TrueRMS_CONTROLADOR_n_T * localP ,
ZCV_TrueRMS_CONTROLADOR_g_T * localZCSV ) ; void
CONTROLADOR_TrueRMS_j_Disable ( SimStruct * S , DW_TrueRMS_CONTROLADOR_o_T *
localDW ) ; void CONTROLADOR_TrueRMS_m_Update ( SimStruct * S ,
B_TrueRMS_CONTROLADOR_j_T * localB , DW_TrueRMS_CONTROLADOR_o_T * localDW ,
P_TrueRMS_CONTROLADOR_n_T * localP ) ; void CONTROLADOR_TrueRMS_i ( SimStruct
* S , boolean_T rtu_Enable , real_T rtu_In , B_TrueRMS_CONTROLADOR_j_T *
localB , DW_TrueRMS_CONTROLADOR_o_T * localDW , P_TrueRMS_CONTROLADOR_n_T *
localP , X_TrueRMS_CONTROLADOR_c_T * localX , XDis_TrueRMS_CONTROLADOR_o_T *
localXdis ) ; void CONTROLADOR_RMS_Term ( SimStruct * const S ) ; void
CONTROLADOR_TrueRMS_Term ( SimStruct * const S ) ; void
CONTROLADOR_RMS_n_Term ( SimStruct * const S ) ; void
CONTROLADOR_TrueRMS_p_Term ( SimStruct * const S ) ;
#endif
