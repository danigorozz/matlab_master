#include <math.h>
#include "main_controlado_examen_acc.h"
#include "main_controlado_examen_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T main_controlado_examen_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T tail = *
tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * uBufPtr + bufSz ;
real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) {
numBuffer = 3 ; xBuf = * uBufPtr + 2 * bufSz ; } testIdx = ( tail < ( bufSz -
1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && !
isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T * tempX = (
NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024 ; if (
newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU = (
real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if ( tempU
== ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * uBufPtr = tempU ; } else { * tailPtr =
testIdx ; } return ( true ) ; } real_T
main_controlado_examen_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T
tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx ,
int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2 , u1 , u2
; real_T * tBuf = uBuf + bufSz ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
void * S , void * diag ) { SimStruct * castedS = ( SimStruct * ) S ; if ( !
_ssIsErrorStatusAslErrMsg ( castedS ) ) { _ssSet_slErrMsg ( castedS , diag )
; } else { _ssDiscardDiagnostic ( castedS , diag ) ; } } void
rt_ssReportDiagnosticAsWarning ( void * S , void * diag ) {
_ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } static void
mdlOutputs ( SimStruct * S , int_T tid ) { B_main_controlado_examen_T * _rtB
; DW_main_controlado_examen_T * _rtDW ; P_main_controlado_examen_T * _rtP ;
X_main_controlado_examen_T * _rtX ; real_T temp ; int32_T isHit ; boolean_T
rtb_B_5_4_0 ; _rtDW = ( ( DW_main_controlado_examen_T * ) ssGetRootDWork ( S
) ) ; _rtX = ( ( X_main_controlado_examen_T * ) ssGetContStates ( S ) ) ;
_rtP = ( ( P_main_controlado_examen_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_main_controlado_examen_T * ) _ssGetModelBlockIO ( S ) ) ; temp = _rtP ->
P_70 * ssGetT ( S ) ; if ( temp - muDoubleScalarFloor ( temp ) >= 0.5 ) {
_rtB -> B_8_0_0 = _rtP -> P_69 ; } else { _rtB -> B_8_0_0 = - _rtP -> P_69 ;
} _rtB -> B_8_1_0 [ 0 ] = _rtB -> B_8_0_0 ; _rtB -> B_8_1_0 [ 1 ] = 0.0 ;
_rtB -> B_8_1_0 [ 2 ] = 0.0 ; _rtB -> B_8_1_0 [ 3 ] = 0.0 ; _rtB -> B_8_2_0 =
_rtP -> P_71 * _rtB -> B_8_0_0 ; _rtB -> B_8_3_0 [ 0 ] = _rtB -> B_8_2_0 ;
_rtB -> B_8_3_0 [ 1 ] = 0.0 ; _rtB -> B_8_3_0 [ 2 ] = 0.0 ; _rtB -> B_8_3_0 [
3 ] = 0.0 ; _rtB -> B_8_4_0 = ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 1 ,
0 ) ; if ( isHit != 0 ) { _rtB -> B_8_5_0 = _rtP -> P_72 ; } _rtB -> B_8_6_0
= _rtX -> Integrator_CSTATE ; ssCallAccelRunBlock ( S , 8 , _rtDW ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 8 , SS_CALL_MDL_OUTPUTS
) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && (
ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB -> B_8_1_0_m ) { if ( ! _rtDW ->
TrueRMS_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } ( (
XDis_main_controlado_examen_T * ) ssGetContStateDisabled ( S ) ) ->
integrator_CSTATE = 0 ; _rtDW -> TrueRMS_MODE = true ; } } else { if (
ssGetTaskTime ( S , 1 ) == ssGetTStart ( S ) ) { ( (
XDis_main_controlado_examen_T * ) ssGetContStateDisabled ( S ) ) ->
integrator_CSTATE = 1 ; } if ( _rtDW -> TrueRMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; ( (
XDis_main_controlado_examen_T * ) ssGetContStateDisabled ( S ) ) ->
integrator_CSTATE = 1 ; _rtDW -> TrueRMS_MODE = false ; } } } if ( _rtDW ->
TrueRMS_MODE ) { _rtB -> B_7_1_0 = _rtX -> integrator_CSTATE ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ]
; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_63
; _rtB -> B_7_2_0 = main_controlado_examen_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Last , _rtDW ->
TransportDelay_IWORK . Tail , _rtDW -> TransportDelay_IWORK . Head , _rtP ->
P_64 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput
( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_7_3_0 = _rtP -> P_65 ; _rtB -> B_7_4_0 = _rtDW ->
Memory_PreviousInput ; } if ( ssGetT ( S ) >= _rtB -> B_7_3_0 ) { _rtB ->
B_6_0_0 = _rtB -> B_7_1_0 - _rtB -> B_7_2_0 ; _rtB -> B_6_1_0 = _rtP -> P_60
* _rtB -> B_6_0_0 ; _rtB -> B_7_7_0 = _rtB -> B_6_1_0 ; } else { _rtB ->
B_7_7_0 = _rtB -> B_7_4_0 ; } _rtB -> B_7_8_0 = _rtB -> B_2_10_0 [ 0 ] * _rtB
-> B_2_10_0 [ 0 ] ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturationtoavoidnegativesqrt_MODE = _rtB -> B_7_7_0 >= _rtP -> P_67 ? 1 :
_rtB -> B_7_7_0 > _rtP -> P_68 ? 0 : - 1 ; } _rtB -> B_7_9_0 = _rtDW ->
Saturationtoavoidnegativesqrt_MODE == 1 ? _rtP -> P_67 : _rtDW ->
Saturationtoavoidnegativesqrt_MODE == - 1 ? _rtP -> P_68 : _rtB -> B_7_7_0 ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( _rtDW -> Sqrt_DWORK1 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtDW -> Sqrt_DWORK1 = 0 ;
} _rtB -> B_7_10_0 = muDoubleScalarSqrt ( _rtB -> B_7_9_0 ) ; srUpdateBC (
_rtDW -> TrueRMS_SubsysRanBC ) ; } else { if ( _rtB -> B_7_9_0 < 0.0 ) { _rtB
-> B_7_10_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( _rtB -> B_7_9_0 ) )
; } else { _rtB -> B_7_10_0 = muDoubleScalarSqrt ( _rtB -> B_7_9_0 ) ; } if (
_rtB -> B_7_9_0 < 0.0 ) { _rtDW -> Sqrt_DWORK1 = 1 ; } } } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { if ( _rtB -> B_8_2_0_c ) { if ( ! _rtDW -> RMS_MODE ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } ( void ) memset ( & ( (
( XDis_main_controlado_examen_T * ) ssGetContStateDisabled ( S ) ) ->
integrator_CSTATE_m ) , 0 , 2 * sizeof ( boolean_T ) ) ; _rtDW -> RMS_MODE =
true ; } } else { if ( ssGetTaskTime ( S , 1 ) == ssGetTStart ( S ) ) { (
void ) memset ( & ( ( ( XDis_main_controlado_examen_T * )
ssGetContStateDisabled ( S ) ) -> integrator_CSTATE_m ) , 1 , 2 * sizeof (
boolean_T ) ) ; } if ( _rtDW -> RMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; ( void ) memset ( & ( ( (
XDis_main_controlado_examen_T * ) ssGetContStateDisabled ( S ) ) ->
integrator_CSTATE_m ) , 1 , 2 * sizeof ( boolean_T ) ) ; _rtDW -> RMS_MODE =
false ; } } } if ( _rtDW -> RMS_MODE ) { _rtB -> B_5_0_0 = _rtX ->
integrator_CSTATE_m ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_42 ; _rtB -> B_5_1_0 =
main_controlado_examen_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
uBuffer , _rtDW -> TransportDelay_IWORK_m . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_m . Last , _rtDW -> TransportDelay_IWORK_m . Tail ,
_rtDW -> TransportDelay_IWORK_m . Head , _rtP -> P_43 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_5_3_0 = _rtP -> P_44 ; } rtb_B_5_4_0 = ( ssGetT ( S ) >= _rtB -> B_5_3_0 )
; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_5_5_0 =
_rtDW -> Memory_PreviousInput_d ; } if ( rtb_B_5_4_0 ) { _rtB -> B_4_0_0 =
_rtB -> B_5_0_0 - _rtB -> B_5_1_0 ; _rtB -> B_4_1_0 = _rtP -> P_39 * _rtB ->
B_4_0_0 ; _rtB -> B_5_7_0 = _rtB -> B_4_1_0 ; } else { _rtB -> B_5_7_0 = _rtB
-> B_5_5_0 ; } _rtB -> B_5_8_0 = _rtX -> integrator_CSTATE_l ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 0
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_47 ; _rtB -> B_5_9_0 = main_controlado_examen_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK_d .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_d . Last , _rtDW ->
TransportDelay_IWORK_d . Tail , _rtDW -> TransportDelay_IWORK_d . Head , _rtP
-> P_48 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_5_11_0 = _rtP -> P_49 ; }
rtb_B_5_4_0 = ( ssGetT ( S ) >= _rtB -> B_5_11_0 ) ; isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_5_13_0 = _rtDW ->
Memory_PreviousInput_e ; } if ( rtb_B_5_4_0 ) { _rtB -> B_3_0_0 = _rtB ->
B_5_8_0 - _rtB -> B_5_9_0 ; _rtB -> B_3_1_0 = _rtP -> P_38 * _rtB -> B_3_0_0
; _rtB -> B_5_15_0 = _rtB -> B_3_1_0 ; } else { _rtB -> B_5_15_0 = _rtB ->
B_5_13_0 ; } _rtB -> B_5_16_0 . re = _rtB -> B_5_7_0 ; _rtB -> B_5_16_0 . im
= _rtB -> B_5_15_0 ; _rtB -> B_5_19_0 = ( muDoubleScalarSin ( _rtP -> P_53 *
ssGetTaskTime ( S , 0 ) + _rtP -> P_54 ) * _rtP -> P_51 + _rtP -> P_52 ) *
_rtB -> B_2_10_0 [ 0 ] ; _rtB -> B_5_21_0 = ( muDoubleScalarSin ( _rtP ->
P_57 * ssGetTaskTime ( S , 0 ) + _rtP -> P_58 ) * _rtP -> P_55 + _rtP -> P_56
) * _rtB -> B_2_10_0 [ 0 ] ; _rtB -> B_5_22_0 = _rtP -> P_59 *
muDoubleScalarHypot ( _rtB -> B_5_16_0 . re , _rtB -> B_5_16_0 . im ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW -> RMS_SubsysRanBC ) ; }
} if ( _rtB -> B_8_1_0_m ) { _rtB -> B_8_11_0 = _rtB -> B_7_10_0 ; } else {
_rtB -> B_8_11_0 = _rtB -> B_5_22_0 ; } ssCallAccelRunBlock ( S , 8 , 12 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_8_13_0 = _rtB -> B_8_11_0 * _rtB ->
B_2_13_0 ; ssCallAccelRunBlock ( S , 8 , 14 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 17 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 18 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 21 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 22 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 31 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 32 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 33 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_8_34_0 =
_rtP -> P_74 * _rtB -> B_2_14_0 ; ssCallAccelRunBlock ( S , 8 , 37 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 39 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 41 ,
SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID2 ( SimStruct * S , int_T tid ) { B_main_controlado_examen_T *
_rtB ; P_main_controlado_examen_T * _rtP ; _rtP = ( (
P_main_controlado_examen_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_main_controlado_examen_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_8_1_0_m
= ( _rtP -> P_75 != 0.0 ) ; _rtB -> B_8_2_0_c = ! _rtB -> B_8_1_0_m ; _rtB ->
B_8_4_0_k = ( _rtP -> P_76 != 0.0 ) ; _rtB -> B_8_5_0_c = ! _rtB -> B_8_4_0_k
; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_main_controlado_examen_T * _rtB ; DW_main_controlado_examen_T * _rtDW ;
P_main_controlado_examen_T * _rtP ; int32_T isHit ; _rtDW = ( (
DW_main_controlado_examen_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_main_controlado_examen_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_main_controlado_examen_T * ) _ssGetModelBlockIO ( S ) ) ;
ssCallAccelRunBlock ( S , 2 , 9 , SS_CALL_MDL_UPDATE ) ; if ( _rtDW ->
RMS_MODE_j ) { { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_l3 . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S )
; _rtDW -> TransportDelay_IWORK_i . Head = ( ( _rtDW ->
TransportDelay_IWORK_i . Head < ( _rtDW -> TransportDelay_IWORK_i .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_i . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_i . Head == _rtDW ->
TransportDelay_IWORK_i . Tail ) { if ( !
main_controlado_examen_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_i . CircularBufSize , & _rtDW -> TransportDelay_IWORK_i
. Tail , & _rtDW -> TransportDelay_IWORK_i . Head , & _rtDW ->
TransportDelay_IWORK_i . Last , simTime - _rtP -> P_2 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay_IWORK_i . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK_i . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_i . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_i . Head ] = _rtB -> B_0_0_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_k = _rtB ->
B_0_8_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_b . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK_c . Head = ( ( _rtDW -> TransportDelay_IWORK_c
. Head < ( _rtDW -> TransportDelay_IWORK_c . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay_IWORK_c . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_c . Head == _rtDW -> TransportDelay_IWORK_c . Tail ) {
if ( ! main_controlado_examen_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_c . CircularBufSize , & _rtDW -> TransportDelay_IWORK_c
. Tail , & _rtDW -> TransportDelay_IWORK_c . Head , & _rtDW ->
TransportDelay_IWORK_c . Last , simTime - _rtP -> P_8 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay_IWORK_c . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK_c . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_c . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_c . Head ] = _rtB -> B_0_9_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_es = _rtB ->
B_0_17_0 ; } } if ( _rtDW -> TrueRMS_MODE_p ) { { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK_p . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_b . Head = ( ( _rtDW
-> TransportDelay_IWORK_b . Head < ( _rtDW -> TransportDelay_IWORK_b .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_b . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_b . Head == _rtDW ->
TransportDelay_IWORK_b . Tail ) { if ( !
main_controlado_examen_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_b . CircularBufSize , & _rtDW -> TransportDelay_IWORK_b
. Tail , & _rtDW -> TransportDelay_IWORK_b . Head , & _rtDW ->
TransportDelay_IWORK_b . Last , simTime - _rtP -> P_24 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_b . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_b . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_b . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_b . Head ] = _rtB -> B_1_1_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_j = _rtB ->
B_1_8_0 ; } } if ( _rtDW -> TrueRMS_MODE ) { { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! main_controlado_examen_acc_rt_TDelayUpdateTailOrGrowBuf ( &
_rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Tail , & _rtDW -> TransportDelay_IWORK . Head , &
_rtDW -> TransportDelay_IWORK . Last , simTime - _rtP -> P_63 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_7_1_0 ; } isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput = _rtB ->
B_7_7_0 ; } } if ( _rtDW -> RMS_MODE ) { { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_m . Head = ( ( _rtDW ->
TransportDelay_IWORK_m . Head < ( _rtDW -> TransportDelay_IWORK_m .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_m . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_m . Head == _rtDW ->
TransportDelay_IWORK_m . Tail ) { if ( !
main_controlado_examen_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_m . CircularBufSize , & _rtDW -> TransportDelay_IWORK_m
. Tail , & _rtDW -> TransportDelay_IWORK_m . Head , & _rtDW ->
TransportDelay_IWORK_m . Last , simTime - _rtP -> P_42 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_m . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_m . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_m . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_m . Head ] = _rtB -> B_5_0_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_d = _rtB ->
B_5_7_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK_d . Head = ( ( _rtDW -> TransportDelay_IWORK_d
. Head < ( _rtDW -> TransportDelay_IWORK_d . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay_IWORK_d . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_d . Head == _rtDW -> TransportDelay_IWORK_d . Tail ) {
if ( ! main_controlado_examen_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_d . CircularBufSize , & _rtDW -> TransportDelay_IWORK_d
. Tail , & _rtDW -> TransportDelay_IWORK_d . Head , & _rtDW ->
TransportDelay_IWORK_d . Last , simTime - _rtP -> P_47 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_d . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_d . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_d . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_d . Head ] = _rtB -> B_5_8_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_e = _rtB ->
B_5_15_0 ; } } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID2 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_main_controlado_examen_T *
_rtB ; DW_main_controlado_examen_T * _rtDW ; XDot_main_controlado_examen_T *
_rtXdot ; _rtDW = ( ( DW_main_controlado_examen_T * ) ssGetRootDWork ( S ) )
; _rtXdot = ( ( XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) ; _rtB = (
( B_main_controlado_examen_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_8_34_0 ; ssCallAccelRunBlock ( S , 2 , 9 ,
SS_CALL_MDL_DERIVATIVES ) ; if ( _rtDW -> RMS_MODE_j ) { _rtXdot ->
integrator_CSTATE_f = _rtB -> B_0_21_0 ; _rtXdot -> integrator_CSTATE_c =
_rtB -> B_0_23_0 ; } else { { real_T * dx ; int_T i ; dx = & ( ( (
XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) -> integrator_CSTATE_f ) ;
for ( i = 0 ; i < 2 ; i ++ ) { dx [ i ] = 0.0 ; } } } if ( _rtDW ->
TrueRMS_MODE_p ) { _rtXdot -> integrator_CSTATE_a = _rtB -> B_1_9_0 ; } else
{ ( ( XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) ->
integrator_CSTATE_a = 0.0 ; } if ( _rtDW -> TrueRMS_MODE ) { _rtXdot ->
integrator_CSTATE = _rtB -> B_7_8_0 ; } else { ( (
XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) -> integrator_CSTATE = 0.0
; } if ( _rtDW -> RMS_MODE ) { _rtXdot -> integrator_CSTATE_m = _rtB ->
B_5_19_0 ; _rtXdot -> integrator_CSTATE_l = _rtB -> B_5_21_0 ; } else { {
real_T * dx ; int_T i ; dx = & ( ( ( XDot_main_controlado_examen_T * )
ssGetdX ( S ) ) -> integrator_CSTATE_m ) ; for ( i = 0 ; i < 2 ; i ++ ) { dx
[ i ] = 0.0 ; } } } }
#define MDL_FORCINGFUNCTION
static void mdlForcingFunction ( SimStruct * S ) { B_main_controlado_examen_T
* _rtB ; DW_main_controlado_examen_T * _rtDW ; XDot_main_controlado_examen_T
* _rtXdot ; _rtDW = ( ( DW_main_controlado_examen_T * ) ssGetRootDWork ( S )
) ; _rtXdot = ( ( XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) ; _rtB =
( ( B_main_controlado_examen_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_8_34_0 ; ssCallAccelRunBlock ( S , 2 , 9 ,
SS_CALL_MDL_FORCINGFUNCTION ) ; if ( _rtDW -> RMS_MODE_j ) { _rtXdot ->
integrator_CSTATE_f = _rtB -> B_0_21_0 ; _rtXdot -> integrator_CSTATE_c =
_rtB -> B_0_23_0 ; } else { { real_T * dx ; int_T i ; dx = & ( ( (
XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) -> integrator_CSTATE_f ) ;
for ( i = 0 ; i < 2 ; i ++ ) { dx [ i ] = 0.0 ; } } } if ( _rtDW ->
TrueRMS_MODE_p ) { _rtXdot -> integrator_CSTATE_a = _rtB -> B_1_9_0 ; } else
{ ( ( XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) ->
integrator_CSTATE_a = 0.0 ; } if ( _rtDW -> TrueRMS_MODE ) { _rtXdot ->
integrator_CSTATE = _rtB -> B_7_8_0 ; } else { ( (
XDot_main_controlado_examen_T * ) ssGetdX ( S ) ) -> integrator_CSTATE = 0.0
; } if ( _rtDW -> RMS_MODE ) { _rtXdot -> integrator_CSTATE_m = _rtB ->
B_5_19_0 ; _rtXdot -> integrator_CSTATE_l = _rtB -> B_5_21_0 ; } else { {
real_T * dx ; int_T i ; dx = & ( ( ( XDot_main_controlado_examen_T * )
ssGetdX ( S ) ) -> integrator_CSTATE_m ) ; for ( i = 0 ; i < 2 ; i ++ ) { dx
[ i ] = 0.0 ; } } } }
#define MDL_MASSMATRIX
static void mdlMassMatrix ( SimStruct * S ) { ssCallAccelRunBlock ( S , 2 , 9
, SS_CALL_MDL_MASSMATRIX ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_main_controlado_examen_T *
_rtB ; DW_main_controlado_examen_T * _rtDW ; P_main_controlado_examen_T *
_rtP ; ZCV_main_controlado_examen_T * _rtZCSV ; _rtDW = ( (
DW_main_controlado_examen_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV = ( (
ZCV_main_controlado_examen_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = (
( P_main_controlado_examen_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_main_controlado_examen_T * ) _ssGetModelBlockIO ( S ) ) ; _rtZCSV ->
Saturation005_UprLim_ZC = _rtB -> B_2_1_0 - _rtP -> P_32 ; _rtZCSV ->
Saturation005_LwrLim_ZC = _rtB -> B_2_1_0 - _rtP -> P_33 ;
ssCallAccelRunBlock ( S , 2 , 9 , SS_CALL_MDL_ZERO_CROSSINGS ) ; if ( _rtDW
-> TrueRMS_MODE_p ) { _rtZCSV -> Saturationtoavoidnegativesqrt_UprLim_ZC_e =
_rtB -> B_1_8_0 - _rtP -> P_29 ; _rtZCSV ->
Saturationtoavoidnegativesqrt_LwrLim_ZC_n = _rtB -> B_1_8_0 - _rtP -> P_30 ;
} else { { real_T * zcsv = & ( ( ( ZCV_main_controlado_examen_T * )
ssGetSolverZcSignalVector ( S ) ) ->
Saturationtoavoidnegativesqrt_UprLim_ZC_e ) ; int_T i ; for ( i = 0 ; i < 2 ;
i ++ ) { zcsv [ i ] = 0.0 ; } } } if ( _rtDW -> TrueRMS_MODE ) { _rtZCSV ->
Saturationtoavoidnegativesqrt_UprLim_ZC = _rtB -> B_7_7_0 - _rtP -> P_67 ;
_rtZCSV -> Saturationtoavoidnegativesqrt_LwrLim_ZC = _rtB -> B_7_7_0 - _rtP
-> P_68 ; } else { { real_T * zcsv = & ( ( ( ZCV_main_controlado_examen_T * )
ssGetSolverZcSignalVector ( S ) ) -> Saturationtoavoidnegativesqrt_UprLim_ZC
) ; int_T i ; for ( i = 0 ; i < 2 ; i ++ ) { zcsv [ i ] = 0.0 ; } } } }
static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
3452224407U ) ; ssSetChecksumVal ( S , 1 , 623340568U ) ; ssSetChecksumVal (
S , 2 , 1618153939U ) ; ssSetChecksumVal ( S , 3 , 4255172646U ) ; { mxArray
* slVerStructMat = ( NULL ) ; mxArray * slStrMat = mxCreateString (
"simulink" ) ; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , &
slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray *
slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == (
NULL ) ) { status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar
, 10 ) ; } } mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat )
; if ( ( status == 1 ) || ( strcmp ( slVerChar , "10.4" ) != 0 ) ) { return ;
} } ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if (
ssGetSizeofDWork ( S ) != sizeof ( DW_main_controlado_examen_T ) ) {
ssSetErrorStatus ( S , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_main_controlado_examen_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_main_controlado_examen_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & main_controlado_examen_rtDefaultP ) ; if ( ssGetSizeofDWork ( S ) ==
sizeof ( DW_main_controlado_examen_T ) ) { { ( ( DW_main_controlado_examen_T
* ) ssGetRootDWork ( S ) ) -> STATE_1_MASS_MATRIX_PR = 4 ; } }
rt_InitInfAndNaN ( sizeof ( real_T ) ) ; ( ( P_main_controlado_examen_T * )
ssGetModelRtp ( S ) ) -> P_29 = rtInf ; ( ( P_main_controlado_examen_T * )
ssGetModelRtp ( S ) ) -> P_67 = rtInf ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn ( S ,
mdlOutputsTID2 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
