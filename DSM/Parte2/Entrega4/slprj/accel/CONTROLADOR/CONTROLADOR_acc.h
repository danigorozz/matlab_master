#ifndef RTW_HEADER_CONTROLADOR_acc_h_
#define RTW_HEADER_CONTROLADOR_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef CONTROLADOR_acc_COMMON_INCLUDES_
#define CONTROLADOR_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn
#define S_FUNCTION_LEVEL 2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "CONTROLADOR_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { creal_T B_0_18_0 ; real_T B_0_0_0 ; real_T B_0_1_0 ; real_T
B_0_2_0 ; real_T B_0_3_0 ; real_T B_0_5_0 ; real_T B_0_7_0 ; real_T B_0_8_0 ;
real_T B_0_9_0 ; real_T B_0_10_0 ; real_T B_0_11_0 ; real_T B_0_12_0 ; real_T
B_0_14_0 ; real_T B_0_16_0 ; real_T B_0_17_0 ; real_T B_0_21_0 ; real_T
B_0_23_0 ; real_T B_0_24_0 ; } B_RMS_CONTROLADOR_T ; typedef struct { real_T
Memory_PreviousInput ; real_T Memory_PreviousInput_f ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_a ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_g ; int32_T RMS_sysIdxToRun ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_o ; int8_T
RMS_SubsysRanBC ; boolean_T RMS_MODE ; char_T pad_RMS_MODE [ 2 ] ; }
DW_RMS_CONTROLADOR_T ; typedef struct { real_T integrator_CSTATE_i ; real_T
integrator_CSTATE_f ; } X_RMS_CONTROLADOR_T ; typedef struct { real_T
integrator_CSTATE_i ; real_T integrator_CSTATE_f ; } XDot_RMS_CONTROLADOR_T ;
typedef struct { boolean_T integrator_CSTATE_i ; boolean_T
integrator_CSTATE_f ; } XDis_RMS_CONTROLADOR_T ; typedef struct { real_T
integrator_CSTATE_i ; real_T integrator_CSTATE_f ; }
XAbsTol_RMS_CONTROLADOR_T ; typedef struct { real_T integrator_CSTATE_i ;
real_T integrator_CSTATE_f ; } XPtMin_RMS_CONTROLADOR_T ; typedef struct {
real_T integrator_CSTATE_i ; real_T integrator_CSTATE_f ; }
XPtMax_RMS_CONTROLADOR_T ; typedef struct { real_T B_2_1_0 ; real_T B_2_2_0 ;
real_T B_2_3_0 ; real_T B_2_4_0 ; real_T B_2_5_0 ; real_T B_2_6_0 ; real_T
B_2_8_0 ; real_T B_2_9_0 ; real_T B_2_10_0 ; real_T B_2_11_0 ; }
B_TrueRMS_CONTROLADOR_T ; typedef struct { real_T Memory_PreviousInput ;
struct { real_T modelTStart ; } TransportDelay_RWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; int32_T TrueRMS_sysIdxToRun ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK ; int_T
Saturationtoavoidnegativesqrt_MODE ; int8_T TrueRMS_SubsysRanBC ; int8_T
Sqrt_DWORK1 ; boolean_T TrueRMS_MODE ; char_T pad_TrueRMS_MODE [ 1 ] ; }
DW_TrueRMS_CONTROLADOR_T ; typedef struct { real_T integrator_CSTATE_o ; }
X_TrueRMS_CONTROLADOR_T ; typedef struct { real_T integrator_CSTATE_o ; }
XDot_TrueRMS_CONTROLADOR_T ; typedef struct { boolean_T integrator_CSTATE_o ;
} XDis_TrueRMS_CONTROLADOR_T ; typedef struct { real_T integrator_CSTATE_o ;
} XAbsTol_TrueRMS_CONTROLADOR_T ; typedef struct { real_T integrator_CSTATE_o
; } XPtMin_TrueRMS_CONTROLADOR_T ; typedef struct { real_T
integrator_CSTATE_o ; } XPtMax_TrueRMS_CONTROLADOR_T ; typedef struct {
real_T Saturationtoavoidnegativesqrt_UprLim_ZC_p ; real_T
Saturationtoavoidnegativesqrt_LwrLim_ZC_b ; } ZCV_TrueRMS_CONTROLADOR_T ;
typedef struct { ZCSigState Saturationtoavoidnegativesqrt_UprLim_ZCE_m ;
ZCSigState Saturationtoavoidnegativesqrt_LwrLim_ZCE_p ; }
ZCE_TrueRMS_CONTROLADOR_T ; typedef struct { creal_T B_7_16_0 ; real_T
B_7_0_0 ; real_T B_7_1_0 ; real_T B_7_3_0 ; real_T B_7_5_0 ; real_T B_7_7_0 ;
real_T B_7_8_0 ; real_T B_7_9_0 ; real_T B_7_11_0 ; real_T B_7_13_0 ; real_T
B_7_15_0 ; real_T B_7_19_0 ; real_T B_7_21_0 ; real_T B_7_22_0 ; real_T
B_6_0_0 ; real_T B_6_1_0 ; real_T B_5_0_0 ; real_T B_5_1_0 ; }
B_RMS_CONTROLADOR_o_T ; typedef struct { real_T Memory_PreviousInput ; real_T
Memory_PreviousInput_m ; struct { real_T modelTStart ; } TransportDelay_RWORK
; struct { real_T modelTStart ; } TransportDelay_RWORK_k ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * TUbufferPtrs [
2 ] ; } TransportDelay_PWORK_h ; int32_T RMS_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_j ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_o ; int8_T
RMS_SubsysRanBC ; boolean_T RMS_MODE ; char_T pad_RMS_MODE [ 2 ] ; }
DW_RMS_CONTROLADOR_m_T ; typedef struct { real_T integrator_CSTATE_j ; real_T
integrator_CSTATE_g ; } X_RMS_CONTROLADOR_e_T ; typedef struct { real_T
integrator_CSTATE_j ; real_T integrator_CSTATE_g ; } XDot_RMS_CONTROLADOR_g_T
; typedef struct { boolean_T integrator_CSTATE_j ; boolean_T
integrator_CSTATE_g ; } XDis_RMS_CONTROLADOR_k_T ; typedef struct { real_T
integrator_CSTATE_j ; real_T integrator_CSTATE_g ; }
XAbsTol_RMS_CONTROLADOR_m_T ; typedef struct { real_T integrator_CSTATE_j ;
real_T integrator_CSTATE_g ; } XPtMin_RMS_CONTROLADOR_g_T ; typedef struct {
real_T integrator_CSTATE_j ; real_T integrator_CSTATE_g ; }
XPtMax_RMS_CONTROLADOR_a_T ; typedef struct { real_T B_9_1_0 ; real_T B_9_2_0
; real_T B_9_3_0 ; real_T B_9_4_0 ; real_T B_9_7_0 ; real_T B_9_8_0 ; real_T
B_9_9_0 ; real_T B_9_10_0 ; real_T B_8_0_0 ; real_T B_8_1_0 ; }
B_TrueRMS_CONTROLADOR_j_T ; typedef struct { real_T Memory_PreviousInput ;
struct { real_T modelTStart ; } TransportDelay_RWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; int32_T TrueRMS_sysIdxToRun ;
int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; int_T Saturationtoavoidnegativesqrt_MODE ; int8_T
TrueRMS_SubsysRanBC ; int8_T Sqrt_DWORK1 ; boolean_T TrueRMS_MODE ; char_T
pad_TrueRMS_MODE [ 5 ] ; } DW_TrueRMS_CONTROLADOR_o_T ; typedef struct {
real_T integrator_CSTATE ; } X_TrueRMS_CONTROLADOR_c_T ; typedef struct {
real_T integrator_CSTATE ; } XDot_TrueRMS_CONTROLADOR_c_T ; typedef struct {
boolean_T integrator_CSTATE ; } XDis_TrueRMS_CONTROLADOR_o_T ; typedef struct
{ real_T integrator_CSTATE ; } XAbsTol_TrueRMS_CONTROLADOR_j_T ; typedef
struct { real_T integrator_CSTATE ; } XPtMin_TrueRMS_CONTROLADOR_h_T ;
typedef struct { real_T integrator_CSTATE ; } XPtMax_TrueRMS_CONTROLADOR_m_T
; typedef struct { real_T Saturationtoavoidnegativesqrt_UprLim_ZC ; real_T
Saturationtoavoidnegativesqrt_LwrLim_ZC ; } ZCV_TrueRMS_CONTROLADOR_g_T ;
typedef struct { ZCSigState Saturationtoavoidnegativesqrt_UprLim_ZCE ;
ZCSigState Saturationtoavoidnegativesqrt_LwrLim_ZCE ; }
ZCE_TrueRMS_CONTROLADOR_h_T ; typedef struct { real_T B_15_0_0 ; real_T
B_15_1_0 ; real_T B_15_2_0 [ 4 ] ; real_T B_15_3_0 ; real_T B_15_4_0 ; real_T
B_15_5_0 [ 4 ] ; real_T B_15_14_0 ; real_T B_15_15_0 ; real_T B_15_34_0 ;
real_T B_15_0_0_m ; real_T B_15_1_0_c ; real_T B_4_0_0 ; real_T B_4_1_0 ;
real_T B_4_2_0 ; real_T B_4_3_0 ; real_T B_4_4_0 ; real_T B_4_5_0 ; real_T
B_4_6_0 ; real_T B_4_7_0 ; real_T B_4_8_0 ; real_T B_4_9_0 [ 4 ] ; real_T
B_4_10_0 [ 4 ] ; real_T B_4_11_0 [ 51 ] ; real_T B_4_12_0 [ 5 ] ; real_T
B_4_15_0 ; real_T B_4_18_0 ; real_T B_4_19_0 ; boolean_T B_15_3_0_k ;
boolean_T B_15_4_0_c ; boolean_T B_15_6_0 ; boolean_T B_15_7_0 ; boolean_T
B_15_9_0 ; boolean_T B_15_10_0 ; boolean_T B_15_12_0 ; boolean_T B_15_13_0 ;
B_TrueRMS_CONTROLADOR_j_T TrueRMS_i ; B_RMS_CONTROLADOR_o_T RMS_m ;
B_TrueRMS_CONTROLADOR_j_T TrueRMS ; B_RMS_CONTROLADOR_o_T RMS ;
B_TrueRMS_CONTROLADOR_T TrueRMS_k ; B_TrueRMS_CONTROLADOR_T TrueRMS_g ;
B_RMS_CONTROLADOR_T RMS_n ; B_RMS_CONTROLADOR_T RMS_c ; } B_CONTROLADOR_T ;
typedef struct { real_T INPUT_1_1_1_Discrete [ 2 ] ; real_T
INPUT_4_1_1_Discrete [ 2 ] ; real_T INPUT_3_1_1_Discrete [ 2 ] ; real_T
INPUT_2_1_1_Discrete [ 2 ] ; real_T STATE_1_Discrete ; real_T
OUTPUT_1_0_Discrete ; void * EvaluarVI_PWORK [ 2 ] ; void * Potencia1_PWORK ;
void * ScopeRectificador1_PWORK ; void * ScopeInversor1_PWORK ; void *
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_AlgLoopData ; void *
STATE_1_Simulator ; void * STATE_1_SimData ; void * STATE_1_DiagMgr ; void *
STATE_1_ZcLogger ; void * STATE_1_TsIndex ; void * OUTPUT_1_0_Simulator ;
void * OUTPUT_1_0_SimData ; void * OUTPUT_1_0_DiagMgr ; void *
OUTPUT_1_0_ZcLogger ; void * OUTPUT_1_0_TsIndex ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_sysIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_parentSysIdxToRun ; int_T
STATE_1_Modes [ 16 ] ; int_T OUTPUT_1_0_Modes ; int_T Saturation1_MODE ;
int32_T STATE_1_MASS_MATRIX_PR ; boolean_T STATE_1_FirstOutput ; boolean_T
OUTPUT_1_0_FirstOutput ; char_T pad_OUTPUT_1_0_FirstOutput [ 6 ] ;
DW_TrueRMS_CONTROLADOR_o_T TrueRMS_i ; DW_RMS_CONTROLADOR_m_T RMS_m ;
DW_TrueRMS_CONTROLADOR_o_T TrueRMS ; DW_RMS_CONTROLADOR_m_T RMS ;
DW_TrueRMS_CONTROLADOR_T TrueRMS_k ; DW_TrueRMS_CONTROLADOR_T TrueRMS_g ;
DW_RMS_CONTROLADOR_T RMS_n ; DW_RMS_CONTROLADOR_T RMS_c ; } DW_CONTROLADOR_T
; typedef struct { real_T Integrator_CSTATE ; X_TrueRMS_CONTROLADOR_c_T
TrueRMS_i ; X_RMS_CONTROLADOR_e_T RMS_m ; X_TrueRMS_CONTROLADOR_c_T TrueRMS ;
X_RMS_CONTROLADOR_e_T RMS ; real_T
CONTROLADORRECTIFICADOR1Diode1privateCjunctionvc [ 35 ] ;
X_TrueRMS_CONTROLADOR_T TrueRMS_k ; X_TrueRMS_CONTROLADOR_T TrueRMS_g ;
X_RMS_CONTROLADOR_T RMS_n ; X_RMS_CONTROLADOR_T RMS_c ; } X_CONTROLADOR_T ;
typedef struct { real_T Integrator_CSTATE ; XDot_TrueRMS_CONTROLADOR_c_T
TrueRMS_i ; XDot_RMS_CONTROLADOR_g_T RMS_m ; XDot_TrueRMS_CONTROLADOR_c_T
TrueRMS ; XDot_RMS_CONTROLADOR_g_T RMS ; real_T
CONTROLADORRECTIFICADOR1Diode1privateCjunctionvc [ 35 ] ;
XDot_TrueRMS_CONTROLADOR_T TrueRMS_k ; XDot_TrueRMS_CONTROLADOR_T TrueRMS_g ;
XDot_RMS_CONTROLADOR_T RMS_n ; XDot_RMS_CONTROLADOR_T RMS_c ; }
XDot_CONTROLADOR_T ; typedef struct { boolean_T Integrator_CSTATE ;
XDis_TrueRMS_CONTROLADOR_o_T TrueRMS_i ; XDis_RMS_CONTROLADOR_k_T RMS_m ;
XDis_TrueRMS_CONTROLADOR_o_T TrueRMS ; XDis_RMS_CONTROLADOR_k_T RMS ;
boolean_T CONTROLADORRECTIFICADOR1Diode1privateCjunctionvc [ 35 ] ;
XDis_TrueRMS_CONTROLADOR_T TrueRMS_k ; XDis_TrueRMS_CONTROLADOR_T TrueRMS_g ;
XDis_RMS_CONTROLADOR_T RMS_n ; XDis_RMS_CONTROLADOR_T RMS_c ; }
XDis_CONTROLADOR_T ; typedef struct { real_T Integrator_CSTATE ;
XAbsTol_TrueRMS_CONTROLADOR_j_T TrueRMS_i ; XAbsTol_RMS_CONTROLADOR_m_T RMS_m
; XAbsTol_TrueRMS_CONTROLADOR_j_T TrueRMS ; XAbsTol_RMS_CONTROLADOR_m_T RMS ;
real_T CONTROLADORRECTIFICADOR1Diode1privateCjunctionvc [ 35 ] ;
XAbsTol_TrueRMS_CONTROLADOR_T TrueRMS_k ; XAbsTol_TrueRMS_CONTROLADOR_T
TrueRMS_g ; XAbsTol_RMS_CONTROLADOR_T RMS_n ; XAbsTol_RMS_CONTROLADOR_T RMS_c
; } CStateAbsTol_CONTROLADOR_T ; typedef struct { real_T Integrator_CSTATE ;
XPtMin_TrueRMS_CONTROLADOR_h_T TrueRMS_i ; XPtMin_RMS_CONTROLADOR_g_T RMS_m ;
XPtMin_TrueRMS_CONTROLADOR_h_T TrueRMS ; XPtMin_RMS_CONTROLADOR_g_T RMS ;
real_T CONTROLADORRECTIFICADOR1Diode1privateCjunctionvc [ 35 ] ;
XPtMin_TrueRMS_CONTROLADOR_T TrueRMS_k ; XPtMin_TrueRMS_CONTROLADOR_T
TrueRMS_g ; XPtMin_RMS_CONTROLADOR_T RMS_n ; XPtMin_RMS_CONTROLADOR_T RMS_c ;
} CXPtMin_CONTROLADOR_T ; typedef struct { real_T Integrator_CSTATE ;
XPtMax_TrueRMS_CONTROLADOR_m_T TrueRMS_i ; XPtMax_RMS_CONTROLADOR_a_T RMS_m ;
XPtMax_TrueRMS_CONTROLADOR_m_T TrueRMS ; XPtMax_RMS_CONTROLADOR_a_T RMS ;
real_T CONTROLADORRECTIFICADOR1Diode1privateCjunctionvc [ 35 ] ;
XPtMax_TrueRMS_CONTROLADOR_T TrueRMS_k ; XPtMax_TrueRMS_CONTROLADOR_T
TrueRMS_g ; XPtMax_RMS_CONTROLADOR_T RMS_n ; XPtMax_RMS_CONTROLADOR_T RMS_c ;
} CXPtMax_CONTROLADOR_T ; typedef struct { ZCV_TrueRMS_CONTROLADOR_g_T
TrueRMS_i ; ZCV_TrueRMS_CONTROLADOR_g_T TrueRMS ; real_T
Saturation1_UprLim_ZC ; real_T Saturation1_LwrLim_ZC ; real_T
STATE_1_INVERSOR1MOSFETdiodezc_1_ZC ; real_T
STATE_1_INVERSOR1MOSFET1diodezc_1_ZC ; real_T
STATE_1_INVERSOR1MOSFET2diodezc_1_ZC ; real_T
STATE_1_INVERSOR1MOSFET3diodezc_1_ZC ; real_T
STATE_1_RECTIFICADOR1Diodezc_1_ZC ; real_T STATE_1_RECTIFICADOR1Diode1zc_1_ZC
; real_T STATE_1_RECTIFICADOR1Diode2zc_1_ZC ; real_T
STATE_1_RECTIFICADOR1Diode3zc_1_ZC ; real_T STATE_1_RECTIFICADOR_Diodezc_1_ZC
; real_T STATE_1_RECTIFICADOR_Diode1zc_1_ZC ; real_T
STATE_1_RECTIFICADOR_Diode2zc_1_ZC ; real_T
STATE_1_RECTIFICADOR_Diode3zc_1_ZC ; real_T
STATE_1_INVERSOR1MOSFETmosfet_equationzc_2_ZC ; real_T
STATE_1_INVERSOR1MOSFET1mosfet_equationzc_2_ZC ; real_T
STATE_1_INVERSOR1MOSFET2mosfet_equationzc_2_ZC ; real_T
STATE_1_INVERSOR1MOSFET3mosfet_equationzc_2_ZC ; ZCV_TrueRMS_CONTROLADOR_T
TrueRMS_k ; ZCV_TrueRMS_CONTROLADOR_T TrueRMS_g ; } ZCV_CONTROLADOR_T ;
typedef struct { ZCE_TrueRMS_CONTROLADOR_h_T TrueRMS_i ;
ZCE_TrueRMS_CONTROLADOR_h_T TrueRMS ; ZCSigState Saturation1_UprLim_ZCE ;
ZCSigState Saturation1_LwrLim_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFETdiodezc_1_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFET1diodezc_1_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFET2diodezc_1_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFET3diodezc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR1Diodezc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR1Diode1zc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR1Diode2zc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR1Diode3zc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR_Diodezc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR_Diode1zc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR_Diode2zc_1_ZCE ; ZCSigState
STATE_1_RECTIFICADOR_Diode3zc_1_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFETmosfet_equationzc_2_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFET1mosfet_equationzc_2_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFET2mosfet_equationzc_2_ZCE ; ZCSigState
STATE_1_INVERSOR1MOSFET3mosfet_equationzc_2_ZCE ; ZCE_TrueRMS_CONTROLADOR_T
TrueRMS_k ; ZCE_TrueRMS_CONTROLADOR_T TrueRMS_g ; } PrevZCX_CONTROLADOR_T ;
typedef struct { int_T ir [ 29 ] ; int_T jc [ 49 ] ; real_T pr [ 29 ] ; }
MassMatrix_CONTROLADOR_T ; struct P_RMS_CONTROLADOR_T_ { real_T P_0 ; real_T
P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T
P_7 ; real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ;
real_T P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T
P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ; } ; struct
P_TrueRMS_CONTROLADOR_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3
; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; } ; struct
P_RMS_CONTROLADOR_d_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ;
real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9 ;
real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ; real_T
P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T P_20 ;
real_T P_21 ; } ; struct P_TrueRMS_CONTROLADOR_n_T_ { real_T P_0 ; real_T P_1
; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7
; real_T P_8 ; } ; struct P_CONTROLADOR_T_ { real_T P_0 ; real_T P_1 ; real_T
P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T
P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ;
real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ;
P_TrueRMS_CONTROLADOR_n_T TrueRMS_i ; P_RMS_CONTROLADOR_d_T RMS_m ;
P_TrueRMS_CONTROLADOR_n_T TrueRMS ; P_RMS_CONTROLADOR_d_T RMS ;
P_TrueRMS_CONTROLADOR_T TrueRMS_k ; P_TrueRMS_CONTROLADOR_T TrueRMS_g ;
P_RMS_CONTROLADOR_T RMS_n ; P_RMS_CONTROLADOR_T RMS_c ; } ; extern
P_CONTROLADOR_T CONTROLADOR_rtDefaultP ;
#endif
