#ifndef RTW_HEADER_main_controlado2_acc_h_
#define RTW_HEADER_main_controlado2_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef main_controlado2_acc_COMMON_INCLUDES_
#define main_controlado2_acc_COMMON_INCLUDES_
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
#include "main_controlado2_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { creal_T B_0_18_0 ; real_T B_0_0_0 ; real_T B_0_1_0 ; real_T
B_0_2_0 ; real_T B_0_3_0 ; real_T B_0_5_0 ; real_T B_0_7_0 ; real_T B_0_8_0 ;
real_T B_0_9_0 ; real_T B_0_10_0 ; real_T B_0_11_0 ; real_T B_0_12_0 ; real_T
B_0_14_0 ; real_T B_0_16_0 ; real_T B_0_17_0 ; real_T B_0_21_0 ; real_T
B_0_23_0 ; real_T B_0_24_0 ; } B_RMS_main_controlado2_T ; typedef struct {
real_T Memory_PreviousInput ; real_T Memory_PreviousInput_e ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_d ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_b ; int32_T RMS_sysIdxToRun ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_c ; int8_T
RMS_SubsysRanBC ; boolean_T RMS_MODE ; char_T pad_RMS_MODE [ 2 ] ; }
DW_RMS_main_controlado2_T ; typedef struct { real_T integrator_CSTATE_f ;
real_T integrator_CSTATE_c ; } X_RMS_main_controlado2_T ; typedef struct {
real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c ; }
XDot_RMS_main_controlado2_T ; typedef struct { boolean_T integrator_CSTATE_f
; boolean_T integrator_CSTATE_c ; } XDis_RMS_main_controlado2_T ; typedef
struct { real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c ; }
XAbsTol_RMS_main_controlado2_T ; typedef struct { real_T integrator_CSTATE_f
; real_T integrator_CSTATE_c ; } XPtMin_RMS_main_controlado2_T ; typedef
struct { real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c ; }
XPtMax_RMS_main_controlado2_T ; typedef struct { real_T B_2_1_0 ; real_T
B_2_2_0 ; real_T B_2_3_0 ; real_T B_2_4_0 ; real_T B_2_5_0 ; real_T B_2_6_0 ;
real_T B_2_8_0 ; real_T B_2_9_0 ; real_T B_2_10_0 ; real_T B_2_11_0 ; }
B_TrueRMS_main_controlado2_T ; typedef struct { real_T Memory_PreviousInput ;
struct { real_T modelTStart ; } TransportDelay_RWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; int32_T TrueRMS_sysIdxToRun ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK ; int_T
Saturationtoavoidnegativesqrt_MODE ; int8_T TrueRMS_SubsysRanBC ; int8_T
Sqrt_DWORK1 ; boolean_T TrueRMS_MODE ; char_T pad_TrueRMS_MODE [ 1 ] ; }
DW_TrueRMS_main_controlado2_T ; typedef struct { real_T integrator_CSTATE ; }
X_TrueRMS_main_controlado2_T ; typedef struct { real_T integrator_CSTATE ; }
XDot_TrueRMS_main_controlado2_T ; typedef struct { boolean_T
integrator_CSTATE ; } XDis_TrueRMS_main_controlado2_T ; typedef struct {
real_T integrator_CSTATE ; } XAbsTol_TrueRMS_main_controlado2_T ; typedef
struct { real_T integrator_CSTATE ; } XPtMin_TrueRMS_main_controlado2_T ;
typedef struct { real_T integrator_CSTATE ; }
XPtMax_TrueRMS_main_controlado2_T ; typedef struct { real_T
Saturationtoavoidnegativesqrt_UprLim_ZC ; real_T
Saturationtoavoidnegativesqrt_LwrLim_ZC ; } ZCV_TrueRMS_main_controlado2_T ;
typedef struct { ZCSigState Saturationtoavoidnegativesqrt_UprLim_ZCE ;
ZCSigState Saturationtoavoidnegativesqrt_LwrLim_ZCE ; }
ZCE_TrueRMS_main_controlado2_T ; typedef struct { real_T B_5_0_0 ; real_T
B_5_1_0 [ 4 ] ; real_T B_5_2_0 ; real_T B_5_3_0 [ 4 ] ; real_T B_5_4_0 ;
real_T B_5_5_0 ; real_T B_5_25_0 ; real_T B_4_0_0 ; real_T B_4_1_0 ; real_T
B_4_2_0 ; real_T B_4_3_0 ; real_T B_4_4_0 ; real_T B_4_5_0 ; real_T B_4_6_0 ;
real_T B_4_7_0 [ 4 ] ; real_T B_4_8_0 ; real_T B_4_9_0 [ 4 ] ; real_T
B_4_10_0 [ 43 ] ; real_T B_4_11_0 [ 5 ] ; real_T B_4_15_0 ; real_T B_4_17_0 ;
real_T B_4_18_0 ; boolean_T B_5_1_0_m ; boolean_T B_5_2_0_c ; boolean_T
B_5_4_0_k ; boolean_T B_5_5_0_c ; char_T pad_B_5_5_0_c [ 4 ] ;
B_TrueRMS_main_controlado2_T TrueRMS_e ; B_TrueRMS_main_controlado2_T TrueRMS
; B_RMS_main_controlado2_T RMS_a ; B_RMS_main_controlado2_T RMS ; }
B_main_controlado2_T ; typedef struct { real_T INPUT_2_1_1_Discrete [ 2 ] ;
real_T INPUT_1_1_1_Discrete [ 2 ] ; real_T INPUT_4_1_1_Discrete [ 2 ] ;
real_T INPUT_3_1_1_Discrete [ 2 ] ; real_T nextTime ; real_T nextTime_p ;
real_T STATE_1_Discrete ; real_T OUTPUT_1_0_Discrete ; int64_T
numCompleteCycles ; int64_T numCompleteCycles_k ; struct { real_T modelTStart
; } VariableTimeDelay1_RWORK ; struct { real_T modelTStart ; }
VariableTimeDelay_RWORK ; void * Pout_PWORK ; void * Scope_PWORK ; void *
Scope1_PWORK ; void * Scope2_PWORK ; void *
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_AlgLoopData ; struct {
void * TUbufferPtrs [ 2 ] ; } VariableTimeDelay1_PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } VariableTimeDelay_PWORK ; void * STATE_1_Simulator ;
void * STATE_1_SimData ; void * STATE_1_DiagMgr ; void * STATE_1_ZcLogger ;
void * STATE_1_TsIndex ; void * OUTPUT_1_0_Simulator ; void *
OUTPUT_1_0_SimData ; void * OUTPUT_1_0_DiagMgr ; void * OUTPUT_1_0_ZcLogger ;
void * OUTPUT_1_0_TsIndex ; int32_T justEnabled ; int32_T currentValue ;
int32_T justEnabled_i ; int32_T currentValue_h ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_sysIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_parentSysIdxToRun ; struct
{ int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } VariableTimeDelay1_IWORK ; struct { int_T Tail ; int_T Head
; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
VariableTimeDelay_IWORK ; int_T STATE_1_Modes [ 12 ] ; int_T OUTPUT_1_0_Modes
; int_T Saturation1_MODE ; int32_T STATE_1_MASS_MATRIX_PR ; boolean_T
STATE_1_FirstOutput ; boolean_T OUTPUT_1_0_FirstOutput ; char_T
pad_OUTPUT_1_0_FirstOutput [ 6 ] ; DW_TrueRMS_main_controlado2_T TrueRMS_e ;
DW_TrueRMS_main_controlado2_T TrueRMS ; DW_RMS_main_controlado2_T RMS_a ;
DW_RMS_main_controlado2_T RMS ; } DW_main_controlado2_T ; typedef struct {
real_T Integrator_CSTATE ; real_T
main_controlado2RectificadorINDiodeprivateCjunctionvc [ 31 ] ;
X_TrueRMS_main_controlado2_T TrueRMS_e ; X_TrueRMS_main_controlado2_T TrueRMS
; X_RMS_main_controlado2_T RMS_a ; X_RMS_main_controlado2_T RMS ; }
X_main_controlado2_T ; typedef struct { real_T Integrator_CSTATE ; real_T
main_controlado2RectificadorINDiodeprivateCjunctionvc [ 31 ] ;
XDot_TrueRMS_main_controlado2_T TrueRMS_e ; XDot_TrueRMS_main_controlado2_T
TrueRMS ; XDot_RMS_main_controlado2_T RMS_a ; XDot_RMS_main_controlado2_T RMS
; } XDot_main_controlado2_T ; typedef struct { boolean_T Integrator_CSTATE ;
boolean_T main_controlado2RectificadorINDiodeprivateCjunctionvc [ 31 ] ;
XDis_TrueRMS_main_controlado2_T TrueRMS_e ; XDis_TrueRMS_main_controlado2_T
TrueRMS ; XDis_RMS_main_controlado2_T RMS_a ; XDis_RMS_main_controlado2_T RMS
; } XDis_main_controlado2_T ; typedef struct { real_T Integrator_CSTATE ;
real_T main_controlado2RectificadorINDiodeprivateCjunctionvc [ 31 ] ;
XAbsTol_TrueRMS_main_controlado2_T TrueRMS_e ;
XAbsTol_TrueRMS_main_controlado2_T TrueRMS ; XAbsTol_RMS_main_controlado2_T
RMS_a ; XAbsTol_RMS_main_controlado2_T RMS ; }
CStateAbsTol_main_controlado2_T ; typedef struct { real_T Integrator_CSTATE ;
real_T main_controlado2RectificadorINDiodeprivateCjunctionvc [ 31 ] ;
XPtMin_TrueRMS_main_controlado2_T TrueRMS_e ;
XPtMin_TrueRMS_main_controlado2_T TrueRMS ; XPtMin_RMS_main_controlado2_T
RMS_a ; XPtMin_RMS_main_controlado2_T RMS ; } CXPtMin_main_controlado2_T ;
typedef struct { real_T Integrator_CSTATE ; real_T
main_controlado2RectificadorINDiodeprivateCjunctionvc [ 31 ] ;
XPtMax_TrueRMS_main_controlado2_T TrueRMS_e ;
XPtMax_TrueRMS_main_controlado2_T TrueRMS ; XPtMax_RMS_main_controlado2_T
RMS_a ; XPtMax_RMS_main_controlado2_T RMS ; } CXPtMax_main_controlado2_T ;
typedef struct { real_T Saturation1_UprLim_ZC ; real_T Saturation1_LwrLim_ZC
; real_T STATE_1_InversorMOSFET_Ideal_Switching4mosfet_equationzc_1_ZC ;
real_T STATE_1_InversorMOSFET_Ideal_Switching5mosfet_equationzc_1_ZC ; real_T
STATE_1_InversorMOSFET_Ideal_Switching6mosfet_equationzc_1_ZC ; real_T
STATE_1_InversorMOSFET_Ideal_Switching7mosfet_equationzc_1_ZC ; real_T
STATE_1_RectificadorINDiodezc_1_ZC ; real_T
STATE_1_RectificadorINDiode1zc_1_ZC ; real_T
STATE_1_RectificadorINDiode2zc_1_ZC ; real_T
STATE_1_RectificadorINDiode3zc_1_ZC ; real_T
STATE_1_RectificadorOUTDiodezc_1_ZC ; real_T
STATE_1_RectificadorOUTDiode1zc_1_ZC ; real_T
STATE_1_RectificadorOUTDiode2zc_1_ZC ; real_T
STATE_1_RectificadorOUTDiode3zc_1_ZC ; ZCV_TrueRMS_main_controlado2_T
TrueRMS_e ; ZCV_TrueRMS_main_controlado2_T TrueRMS ; } ZCV_main_controlado2_T
; typedef struct { ZCSigState Saturation1_UprLim_ZCE ; ZCSigState
Saturation1_LwrLim_ZCE ; ZCSigState
STATE_1_InversorMOSFET_Ideal_Switching4mosfet_equationzc_1_ZCE ; ZCSigState
STATE_1_InversorMOSFET_Ideal_Switching5mosfet_equationzc_1_ZCE ; ZCSigState
STATE_1_InversorMOSFET_Ideal_Switching6mosfet_equationzc_1_ZCE ; ZCSigState
STATE_1_InversorMOSFET_Ideal_Switching7mosfet_equationzc_1_ZCE ; ZCSigState
STATE_1_RectificadorINDiodezc_1_ZCE ; ZCSigState
STATE_1_RectificadorINDiode1zc_1_ZCE ; ZCSigState
STATE_1_RectificadorINDiode2zc_1_ZCE ; ZCSigState
STATE_1_RectificadorINDiode3zc_1_ZCE ; ZCSigState
STATE_1_RectificadorOUTDiodezc_1_ZCE ; ZCSigState
STATE_1_RectificadorOUTDiode1zc_1_ZCE ; ZCSigState
STATE_1_RectificadorOUTDiode2zc_1_ZCE ; ZCSigState
STATE_1_RectificadorOUTDiode3zc_1_ZCE ; ZCE_TrueRMS_main_controlado2_T
TrueRMS_e ; ZCE_TrueRMS_main_controlado2_T TrueRMS ; }
PrevZCX_main_controlado2_T ; typedef struct { int_T ir [ 23 ] ; int_T jc [ 39
] ; real_T pr [ 23 ] ; } MassMatrix_main_controlado2_T ; struct
P_RMS_main_controlado2_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3
; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9
; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ;
real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T
P_20 ; real_T P_21 ; } ; struct P_TrueRMS_main_controlado2_T_ { real_T P_0 ;
real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ;
real_T P_7 ; real_T P_8 ; } ; struct P_main_controlado2_T_ { real_T P_0 ;
real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ;
real_T P_7 ; real_T P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T
P_12 ; real_T P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ;
real_T P_18 ; real_T P_19 ; real_T P_20 ; real_T P_21 ;
P_TrueRMS_main_controlado2_T TrueRMS_e ; P_TrueRMS_main_controlado2_T TrueRMS
; P_RMS_main_controlado2_T RMS_a ; P_RMS_main_controlado2_T RMS ; } ; extern
P_main_controlado2_T main_controlado2_rtDefaultP ;
#endif
