#ifndef RTW_HEADER_main_controlado_examen_acc_h_
#define RTW_HEADER_main_controlado_examen_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef main_controlado_examen_acc_COMMON_INCLUDES_
#define main_controlado_examen_acc_COMMON_INCLUDES_
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
#include "main_controlado_examen_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { creal_T B_5_16_0 ; creal_T B_0_18_0 ; real_T B_8_0_0 ;
real_T B_8_1_0 [ 4 ] ; real_T B_8_2_0 ; real_T B_8_3_0 [ 4 ] ; real_T B_8_4_0
; real_T B_8_5_0 ; real_T B_8_6_0 ; real_T B_8_11_0 ; real_T B_8_13_0 ;
real_T B_8_34_0 ; real_T B_7_1_0 ; real_T B_7_2_0 ; real_T B_7_3_0 ; real_T
B_7_4_0 ; real_T B_7_7_0 ; real_T B_7_8_0 ; real_T B_7_9_0 ; real_T B_7_10_0
; real_T B_6_0_0 ; real_T B_6_1_0 ; real_T B_5_0_0 ; real_T B_5_1_0 ; real_T
B_5_3_0 ; real_T B_5_5_0 ; real_T B_5_7_0 ; real_T B_5_8_0 ; real_T B_5_9_0 ;
real_T B_5_11_0 ; real_T B_5_13_0 ; real_T B_5_15_0 ; real_T B_5_19_0 ;
real_T B_5_21_0 ; real_T B_5_22_0 ; real_T B_4_0_0 ; real_T B_4_1_0 ; real_T
B_3_0_0 ; real_T B_3_1_0 ; real_T B_2_0_0 ; real_T B_2_1_0 ; real_T B_2_2_0 ;
real_T B_2_3_0 ; real_T B_2_4_0 ; real_T B_2_5_0 ; real_T B_2_6_0 [ 4 ] ;
real_T B_2_7_0 ; real_T B_2_8_0 [ 4 ] ; real_T B_2_9_0 [ 43 ] ; real_T
B_2_10_0 [ 5 ] ; real_T B_2_13_0 ; real_T B_2_14_0 ; real_T B_1_1_0 ; real_T
B_1_2_0 ; real_T B_1_3_0 ; real_T B_1_4_0 ; real_T B_1_5_0 ; real_T B_1_6_0 ;
real_T B_1_8_0 ; real_T B_1_9_0 ; real_T B_1_10_0 ; real_T B_1_11_0 ; real_T
B_0_0_0 ; real_T B_0_1_0 ; real_T B_0_2_0 ; real_T B_0_3_0 ; real_T B_0_5_0 ;
real_T B_0_7_0 ; real_T B_0_8_0 ; real_T B_0_9_0 ; real_T B_0_10_0 ; real_T
B_0_11_0 ; real_T B_0_12_0 ; real_T B_0_14_0 ; real_T B_0_16_0 ; real_T
B_0_17_0 ; real_T B_0_21_0 ; real_T B_0_23_0 ; real_T B_0_24_0 ; boolean_T
B_8_1_0_m ; boolean_T B_8_2_0_c ; boolean_T B_8_4_0_k ; boolean_T B_8_5_0_c ;
char_T pad_B_8_5_0_c [ 4 ] ; } B_main_controlado_examen_T ; typedef struct {
real_T INPUT_2_1_1_Discrete [ 2 ] ; real_T INPUT_1_1_1_Discrete [ 2 ] ;
real_T INPUT_3_1_1_Discrete [ 2 ] ; real_T INPUT_4_1_1_Discrete [ 2 ] ;
real_T Memory_PreviousInput ; real_T Memory_PreviousInput_d ; real_T
Memory_PreviousInput_e ; real_T STATE_1_Discrete ; real_T OUTPUT_1_0_Discrete
; real_T Memory_PreviousInput_j ; real_T Memory_PreviousInput_k ; real_T
Memory_PreviousInput_es ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay_RWORK_f
; struct { real_T modelTStart ; } TransportDelay_RWORK_m ; struct { real_T
modelTStart ; } TransportDelay_RWORK_n ; struct { real_T modelTStart ; }
TransportDelay_RWORK_a ; struct { real_T modelTStart ; }
TransportDelay_RWORK_d ; void * ToWorkspace1_PWORK ; void *
ToWorkspace3_PWORK ; void * ToWorkspace_PWORK ; void * ToWorkspace2_PWORK ;
void * Pout_PWORK ; void * Scope3_PWORK ; void * Scope_PWORK ; void *
Scope1_PWORK ; void * Scope2_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_l ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_h ; void *
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_AlgLoopData ; void *
STATE_1_Simulator ; void * STATE_1_SimData ; void * STATE_1_DiagMgr ; void *
STATE_1_ZcLogger ; void * STATE_1_TsIndex ; void * OUTPUT_1_0_Simulator ;
void * OUTPUT_1_0_SimData ; void * OUTPUT_1_0_DiagMgr ; void *
OUTPUT_1_0_ZcLogger ; void * OUTPUT_1_0_TsIndex ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_p ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay_PWORK_l3 ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK_b ; int32_T TrueRMS_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T RMS_sysIdxToRun ;
int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_f ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_m ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_sysIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_parentSysIdxToRun ;
int32_T TrueRMS_sysIdxToRun_i ; int32_T RMS_sysIdxToRun_a ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_m ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_d ; int_T STATE_1_Modes [ 12 ] ; int_T
OUTPUT_1_0_Modes ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_b ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_i ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_c ; int_T Saturationtoavoidnegativesqrt_MODE ; int_T
Saturation005_MODE ; int_T Saturationtoavoidnegativesqrt_MODE_k ; int32_T
STATE_1_MASS_MATRIX_PR ; int8_T TrueRMS_SubsysRanBC ; int8_T Sqrt_DWORK1 ;
int8_T RMS_SubsysRanBC ; int8_T TrueRMS_SubsysRanBC_f ; int8_T Sqrt_DWORK1_k
; int8_T RMS_SubsysRanBC_b ; boolean_T STATE_1_FirstOutput ; boolean_T
OUTPUT_1_0_FirstOutput ; boolean_T TrueRMS_MODE ; boolean_T RMS_MODE ;
boolean_T TrueRMS_MODE_p ; boolean_T RMS_MODE_j ; }
DW_main_controlado_examen_T ; typedef struct { real_T Integrator_CSTATE ;
real_T integrator_CSTATE ; real_T integrator_CSTATE_m ; real_T
integrator_CSTATE_l ; real_T
main_controlado_examenRectificadorINDiodeprivateCjunctionvc [ 31 ] ; real_T
integrator_CSTATE_a ; real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c
; } X_main_controlado_examen_T ; typedef struct { real_T Integrator_CSTATE ;
real_T integrator_CSTATE ; real_T integrator_CSTATE_m ; real_T
integrator_CSTATE_l ; real_T
main_controlado_examenRectificadorINDiodeprivateCjunctionvc [ 31 ] ; real_T
integrator_CSTATE_a ; real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c
; } XDot_main_controlado_examen_T ; typedef struct { boolean_T
Integrator_CSTATE ; boolean_T integrator_CSTATE ; boolean_T
integrator_CSTATE_m ; boolean_T integrator_CSTATE_l ; boolean_T
main_controlado_examenRectificadorINDiodeprivateCjunctionvc [ 31 ] ;
boolean_T integrator_CSTATE_a ; boolean_T integrator_CSTATE_f ; boolean_T
integrator_CSTATE_c ; } XDis_main_controlado_examen_T ; typedef struct {
real_T Integrator_CSTATE ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_m ; real_T integrator_CSTATE_l ; real_T
main_controlado_examenRectificadorINDiodeprivateCjunctionvc [ 31 ] ; real_T
integrator_CSTATE_a ; real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c
; } CStateAbsTol_main_controlado_examen_T ; typedef struct { real_T
Integrator_CSTATE ; real_T integrator_CSTATE ; real_T integrator_CSTATE_m ;
real_T integrator_CSTATE_l ; real_T
main_controlado_examenRectificadorINDiodeprivateCjunctionvc [ 31 ] ; real_T
integrator_CSTATE_a ; real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c
; } CXPtMin_main_controlado_examen_T ; typedef struct { real_T
Integrator_CSTATE ; real_T integrator_CSTATE ; real_T integrator_CSTATE_m ;
real_T integrator_CSTATE_l ; real_T
main_controlado_examenRectificadorINDiodeprivateCjunctionvc [ 31 ] ; real_T
integrator_CSTATE_a ; real_T integrator_CSTATE_f ; real_T integrator_CSTATE_c
; } CXPtMax_main_controlado_examen_T ; typedef struct { real_T
Saturationtoavoidnegativesqrt_UprLim_ZC ; real_T
Saturationtoavoidnegativesqrt_LwrLim_ZC ; real_T Saturation005_UprLim_ZC ;
real_T Saturation005_LwrLim_ZC ; real_T
STATE_1_InversorMOSFET_Ideal_Switching4mosfet_equationzc_1_ZC ; real_T
STATE_1_InversorMOSFET_Ideal_Switching5mosfet_equationzc_1_ZC ; real_T
STATE_1_InversorMOSFET_Ideal_Switching6mosfet_equationzc_1_ZC ; real_T
STATE_1_InversorMOSFET_Ideal_Switching7mosfet_equationzc_1_ZC ; real_T
STATE_1_RectificadorINDiodezc_1_ZC ; real_T
STATE_1_RectificadorINDiode1zc_1_ZC ; real_T
STATE_1_RectificadorINDiode2zc_1_ZC ; real_T
STATE_1_RectificadorINDiode3zc_1_ZC ; real_T
STATE_1_RectificadorOUTDiodezc_1_ZC ; real_T
STATE_1_RectificadorOUTDiode1zc_1_ZC ; real_T
STATE_1_RectificadorOUTDiode2zc_1_ZC ; real_T
STATE_1_RectificadorOUTDiode3zc_1_ZC ; real_T
Saturationtoavoidnegativesqrt_UprLim_ZC_e ; real_T
Saturationtoavoidnegativesqrt_LwrLim_ZC_n ; } ZCV_main_controlado_examen_T ;
typedef struct { ZCSigState Saturationtoavoidnegativesqrt_UprLim_ZCE ;
ZCSigState Saturationtoavoidnegativesqrt_LwrLim_ZCE ; ZCSigState
Saturation005_UprLim_ZCE ; ZCSigState Saturation005_LwrLim_ZCE ; ZCSigState
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
STATE_1_RectificadorOUTDiode3zc_1_ZCE ; ZCSigState
Saturationtoavoidnegativesqrt_UprLim_ZCE_h ; ZCSigState
Saturationtoavoidnegativesqrt_LwrLim_ZCE_c ; }
PrevZCX_main_controlado_examen_T ; typedef struct { int_T ir [ 23 ] ; int_T
jc [ 39 ] ; real_T pr [ 23 ] ; } MassMatrix_main_controlado_examen_T ; struct
P_main_controlado_examen_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T
P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T
P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ;
real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T
P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ; real_T P_25 ;
real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T P_30 ; real_T
P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ; real_T P_36 ;
real_T P_37 ; real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T P_41 ; real_T
P_42 ; real_T P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 ;
real_T P_48 ; real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T P_52 ; real_T
P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ; real_T P_58 ;
real_T P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T
P_64 ; real_T P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T P_69 ;
real_T P_70 ; real_T P_71 ; real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T
P_75 ; real_T P_76 ; } ; extern P_main_controlado_examen_T
main_controlado_examen_rtDefaultP ;
#endif
