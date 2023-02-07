#include <math.h>
#include "CONTROLADOR_acc.h"
#include "CONTROLADOR_acc_private.h"
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
boolean_T CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr ,
int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay ,
int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T
bufSz = * bufSzPtr ; real_T * tBuf = * uBufPtr + bufSz ; real_T * xBuf = (
NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf
= * uBufPtr + 2 * bufSz ; } testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 )
: 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ;
real_T * tempT ; real_T * tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf =
* uBufPtr ; int_T newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr
) { * maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer
* newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false
) ; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
uBufPtr = tempU ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
CONTROLADOR_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart ,
real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx , int_T
newIdx , real_T initOutput , boolean_T discrete , boolean_T
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
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } void
CONTROLADOR_RMS_Init ( SimStruct * S , B_RMS_CONTROLADOR_T * localB ,
DW_RMS_CONTROLADOR_T * localDW , P_RMS_CONTROLADOR_T * localP ,
X_RMS_CONTROLADOR_T * localX ) { localX -> integrator_CSTATE_i = localP ->
P_1 ; localDW -> Memory_PreviousInput = localP -> P_6 ; localX ->
integrator_CSTATE_f = localP -> P_7 ; localDW -> Memory_PreviousInput_f =
localP -> P_12 ; localB -> B_0_24_0 = localP -> P_0 ; } void
CONTROLADOR_RMS_Disable ( SimStruct * S , DW_RMS_CONTROLADOR_T * localDW ) {
localDW -> RMS_MODE = false ; } void CONTROLADOR_RMS ( SimStruct * S ,
boolean_T rtu_Enable , real_T rtu_In , B_RMS_CONTROLADOR_T * localB ,
DW_RMS_CONTROLADOR_T * localDW , P_RMS_CONTROLADOR_T * localP ,
X_RMS_CONTROLADOR_T * localX , XDis_RMS_CONTROLADOR_T * localXdis ) { int32_T
isHit ; boolean_T rtb_B_0_6_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( (
isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( rtu_Enable ) { if (
! localDW -> RMS_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) )
{ ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } ( void ) memset ( & (
localXdis -> integrator_CSTATE_i ) , 0 , 2 * sizeof ( boolean_T ) ) ; localDW
-> RMS_MODE = true ; } } else { if ( ssGetTaskTime ( S , 1 ) == ssGetTStart (
S ) ) { ( void ) memset ( & ( localXdis -> integrator_CSTATE_i ) , 1 , 2 *
sizeof ( boolean_T ) ) ; } if ( localDW -> RMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; ( void ) memset ( & (
localXdis -> integrator_CSTATE_i ) , 1 , 2 * sizeof ( boolean_T ) ) ;
CONTROLADOR_RMS_Disable ( S , localDW ) ; } } } if ( localDW -> RMS_MODE ) {
localB -> B_0_0_0 = localX -> integrator_CSTATE_i ; { real_T * * uBuffer = (
real_T * * ) & localDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - localP -> P_2 ;
localB -> B_0_1_0 = CONTROLADOR_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0
, * uBuffer , localDW -> TransportDelay_IWORK . CircularBufSize , & localDW
-> TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK . Tail ,
localDW -> TransportDelay_IWORK . Head , localP -> P_3 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } localB -> B_0_2_0 = localB -> B_0_0_0 - localB -> B_0_1_0 ; localB ->
B_0_3_0 = localP -> P_4 * localB -> B_0_2_0 ; isHit = ssIsSampleHit ( S , 1 ,
0 ) ; if ( isHit != 0 ) { localB -> B_0_5_0 = localP -> P_5 ; } rtb_B_0_6_0 =
( ssGetT ( S ) >= localB -> B_0_5_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { localB -> B_0_7_0 = localDW -> Memory_PreviousInput ; }
if ( rtb_B_0_6_0 ) { localB -> B_0_8_0 = localB -> B_0_3_0 ; } else { localB
-> B_0_8_0 = localB -> B_0_7_0 ; } localB -> B_0_9_0 = localX ->
integrator_CSTATE_f ; { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK_g . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - localP -> P_8 ; localB -> B_0_10_0 =
CONTROLADOR_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer ,
localDW -> TransportDelay_IWORK_o . CircularBufSize , & localDW ->
TransportDelay_IWORK_o . Last , localDW -> TransportDelay_IWORK_o . Tail ,
localDW -> TransportDelay_IWORK_o . Head , localP -> P_9 , 0 , ( boolean_T )
( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) )
) ) ; } localB -> B_0_11_0 = localB -> B_0_9_0 - localB -> B_0_10_0 ; localB
-> B_0_12_0 = localP -> P_10 * localB -> B_0_11_0 ; isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { localB -> B_0_14_0 = localP -> P_11 ; }
rtb_B_0_6_0 = ( ssGetT ( S ) >= localB -> B_0_14_0 ) ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { localB -> B_0_16_0 = localDW ->
Memory_PreviousInput_f ; } if ( rtb_B_0_6_0 ) { localB -> B_0_17_0 = localB
-> B_0_12_0 ; } else { localB -> B_0_17_0 = localB -> B_0_16_0 ; } localB ->
B_0_18_0 . re = localB -> B_0_8_0 ; localB -> B_0_18_0 . im = localB ->
B_0_17_0 ; localB -> B_0_21_0 = ( muDoubleScalarSin ( localP -> P_15 *
ssGetTaskTime ( S , 0 ) + localP -> P_16 ) * localP -> P_13 + localP -> P_14
) * rtu_In ; localB -> B_0_23_0 = ( muDoubleScalarSin ( localP -> P_19 *
ssGetTaskTime ( S , 0 ) + localP -> P_20 ) * localP -> P_17 + localP -> P_18
) * rtu_In ; localB -> B_0_24_0 = localP -> P_21 * muDoubleScalarHypot (
localB -> B_0_18_0 . re , localB -> B_0_18_0 . im ) ; if ( ssIsMajorTimeStep
( S ) != 0 ) { srUpdateBC ( localDW -> RMS_SubsysRanBC ) ; } } } void
CONTROLADOR_RMS_Update ( SimStruct * S , B_RMS_CONTROLADOR_T * localB ,
DW_RMS_CONTROLADOR_T * localDW , P_RMS_CONTROLADOR_T * localP ) { int32_T
isHit ; if ( localDW -> RMS_MODE ) { { real_T * * uBuffer = ( real_T * * ) &
localDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; localDW -> TransportDelay_IWORK . Head = ( ( localDW ->
TransportDelay_IWORK . Head < ( localDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK . Head + 1 ) : 0
) ; if ( localDW -> TransportDelay_IWORK . Head == localDW ->
TransportDelay_IWORK . Tail ) { if ( !
CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_2 , uBuffer , ( boolean_T
) 0 , false , & localDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + localDW -> TransportDelay_IWORK . CircularBufSize ) [ localDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ localDW ->
TransportDelay_IWORK . Head ] = localB -> B_0_0_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { localDW -> Memory_PreviousInput = localB ->
B_0_8_0 ; } { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK_g . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
localDW -> TransportDelay_IWORK_o . Head = ( ( localDW ->
TransportDelay_IWORK_o . Head < ( localDW -> TransportDelay_IWORK_o .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK_o . Head + 1 ) :
0 ) ; if ( localDW -> TransportDelay_IWORK_o . Head == localDW ->
TransportDelay_IWORK_o . Tail ) { if ( !
CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK_o . CircularBufSize , & localDW ->
TransportDelay_IWORK_o . Tail , & localDW -> TransportDelay_IWORK_o . Head ,
& localDW -> TransportDelay_IWORK_o . Last , simTime - localP -> P_8 ,
uBuffer , ( boolean_T ) 0 , false , & localDW -> TransportDelay_IWORK_o .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * uBuffer + localDW -> TransportDelay_IWORK_o .
CircularBufSize ) [ localDW -> TransportDelay_IWORK_o . Head ] = simTime ; (
* uBuffer ) [ localDW -> TransportDelay_IWORK_o . Head ] = localB -> B_0_9_0
; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localDW ->
Memory_PreviousInput_f = localB -> B_0_17_0 ; } } } void
CONTROLADOR_RMS_Deriv ( SimStruct * S , B_RMS_CONTROLADOR_T * localB ,
DW_RMS_CONTROLADOR_T * localDW , XDot_RMS_CONTROLADOR_T * localXdot ) { if (
localDW -> RMS_MODE ) { localXdot -> integrator_CSTATE_i = localB -> B_0_21_0
; localXdot -> integrator_CSTATE_f = localB -> B_0_23_0 ; } else { { real_T *
dx ; int_T i ; dx = & ( localXdot -> integrator_CSTATE_i ) ; for ( i = 0 ; i
< 2 ; i ++ ) { dx [ i ] = 0.0 ; } } } } void CONTROLADOR_RMS_ForcingFunction
( SimStruct * S , B_RMS_CONTROLADOR_T * localB , DW_RMS_CONTROLADOR_T *
localDW , XDot_RMS_CONTROLADOR_T * localXdot ) { if ( localDW -> RMS_MODE ) {
localXdot -> integrator_CSTATE_i = localB -> B_0_21_0 ; localXdot ->
integrator_CSTATE_f = localB -> B_0_23_0 ; } else { { real_T * dx ; int_T i ;
dx = & ( localXdot -> integrator_CSTATE_i ) ; for ( i = 0 ; i < 2 ; i ++ ) {
dx [ i ] = 0.0 ; } } } } void CONTROLADOR_RMS_Term ( SimStruct * const S ) {
} void CONTROLADOR_TrueRMS_Init ( SimStruct * S , B_TrueRMS_CONTROLADOR_T *
localB , DW_TrueRMS_CONTROLADOR_T * localDW , P_TrueRMS_CONTROLADOR_T *
localP , X_TrueRMS_CONTROLADOR_T * localX ) { localX -> integrator_CSTATE_o =
localP -> P_1 ; localDW -> Memory_PreviousInput = localP -> P_6 ; localB ->
B_2_11_0 = localP -> P_0 ; } void CONTROLADOR_TrueRMS_Disable ( SimStruct * S
, DW_TrueRMS_CONTROLADOR_T * localDW ) { localDW -> TrueRMS_MODE = false ; }
void CONTROLADOR_TrueRMS ( SimStruct * S , boolean_T rtu_Enable , real_T
rtu_In , B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T *
localDW , P_TrueRMS_CONTROLADOR_T * localP , X_TrueRMS_CONTROLADOR_T * localX
, XDis_TrueRMS_CONTROLADOR_T * localXdis ) { int32_T isHit ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { if ( rtu_Enable ) { if ( ! localDW -> TrueRMS_MODE ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localXdis ->
integrator_CSTATE_o = 0 ; localDW -> TrueRMS_MODE = true ; } } else { if (
ssGetTaskTime ( S , 1 ) == ssGetTStart ( S ) ) { localXdis ->
integrator_CSTATE_o = 1 ; } if ( localDW -> TrueRMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; localXdis ->
integrator_CSTATE_o = 1 ; CONTROLADOR_TrueRMS_Disable ( S , localDW ) ; } } }
if ( localDW -> TrueRMS_MODE ) { localB -> B_2_1_0 = localX ->
integrator_CSTATE_o ; { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - localP -> P_2 ; localB -> B_2_2_0 =
CONTROLADOR_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer ,
localDW -> TransportDelay_IWORK . CircularBufSize , & localDW ->
TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK . Tail ,
localDW -> TransportDelay_IWORK . Head , localP -> P_3 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } localB -> B_2_3_0 = localB -> B_2_1_0 - localB -> B_2_2_0 ; localB ->
B_2_4_0 = localP -> P_4 * localB -> B_2_3_0 ; isHit = ssIsSampleHit ( S , 1 ,
0 ) ; if ( isHit != 0 ) { localB -> B_2_5_0 = localP -> P_5 ; localB ->
B_2_6_0 = localDW -> Memory_PreviousInput ; } if ( ssGetT ( S ) >= localB ->
B_2_5_0 ) { localB -> B_2_8_0 = localB -> B_2_4_0 ; } else { localB ->
B_2_8_0 = localB -> B_2_6_0 ; } localB -> B_2_9_0 = rtu_In * rtu_In ; if (
ssIsMajorTimeStep ( S ) != 0 ) { localDW ->
Saturationtoavoidnegativesqrt_MODE = localB -> B_2_8_0 >= localP -> P_7 ? 1 :
localB -> B_2_8_0 > localP -> P_8 ? 0 : - 1 ; } localB -> B_2_10_0 = localDW
-> Saturationtoavoidnegativesqrt_MODE == 1 ? localP -> P_7 : localDW ->
Saturationtoavoidnegativesqrt_MODE == - 1 ? localP -> P_8 : localB -> B_2_8_0
; if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( localDW -> Sqrt_DWORK1 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; localDW -> Sqrt_DWORK1 = 0
; } localB -> B_2_11_0 = muDoubleScalarSqrt ( localB -> B_2_10_0 ) ;
srUpdateBC ( localDW -> TrueRMS_SubsysRanBC ) ; } else { if ( localB ->
B_2_10_0 < 0.0 ) { localB -> B_2_11_0 = - muDoubleScalarSqrt (
muDoubleScalarAbs ( localB -> B_2_10_0 ) ) ; } else { localB -> B_2_11_0 =
muDoubleScalarSqrt ( localB -> B_2_10_0 ) ; } if ( localB -> B_2_10_0 < 0.0 )
{ localDW -> Sqrt_DWORK1 = 1 ; } } } } void CONTROLADOR_TrueRMS_Update (
SimStruct * S , B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T *
localDW , P_TrueRMS_CONTROLADOR_T * localP ) { int32_T isHit ; if ( localDW
-> TrueRMS_MODE ) { { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
localDW -> TransportDelay_IWORK . Head = ( ( localDW -> TransportDelay_IWORK
. Head < ( localDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? (
localDW -> TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( localDW ->
TransportDelay_IWORK . Head == localDW -> TransportDelay_IWORK . Tail ) { if
( ! CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_2 , uBuffer , ( boolean_T
) 0 , false , & localDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + localDW -> TransportDelay_IWORK . CircularBufSize ) [ localDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ localDW ->
TransportDelay_IWORK . Head ] = localB -> B_2_1_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { localDW -> Memory_PreviousInput = localB ->
B_2_8_0 ; } } } void CONTROLADOR_TrueRMS_Deriv ( SimStruct * S ,
B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T * localDW ,
XDot_TrueRMS_CONTROLADOR_T * localXdot ) { if ( localDW -> TrueRMS_MODE ) {
localXdot -> integrator_CSTATE_o = localB -> B_2_9_0 ; } else { localXdot ->
integrator_CSTATE_o = 0.0 ; } } void CONTROLADOR_TrueRMS_ForcingFunction (
SimStruct * S , B_TrueRMS_CONTROLADOR_T * localB , DW_TrueRMS_CONTROLADOR_T *
localDW , XDot_TrueRMS_CONTROLADOR_T * localXdot ) { if ( localDW ->
TrueRMS_MODE ) { localXdot -> integrator_CSTATE_o = localB -> B_2_9_0 ; }
else { localXdot -> integrator_CSTATE_o = 0.0 ; } } void
CONTROLADOR_TrueRMS_ZC ( SimStruct * S , B_TrueRMS_CONTROLADOR_T * localB ,
DW_TrueRMS_CONTROLADOR_T * localDW , P_TrueRMS_CONTROLADOR_T * localP ,
ZCV_TrueRMS_CONTROLADOR_T * localZCSV ) { if ( localDW -> TrueRMS_MODE ) {
localZCSV -> Saturationtoavoidnegativesqrt_UprLim_ZC_p = localB -> B_2_8_0 -
localP -> P_7 ; localZCSV -> Saturationtoavoidnegativesqrt_LwrLim_ZC_b =
localB -> B_2_8_0 - localP -> P_8 ; } else { { real_T * zcsv = & ( localZCSV
-> Saturationtoavoidnegativesqrt_UprLim_ZC_p ) ; int_T i ; for ( i = 0 ; i <
2 ; i ++ ) { zcsv [ i ] = 0.0 ; } } } } void CONTROLADOR_TrueRMS_Term (
SimStruct * const S ) { } void CONTROLADOR_RMS_m_Init ( SimStruct * S ,
B_RMS_CONTROLADOR_o_T * localB , DW_RMS_CONTROLADOR_m_T * localDW ,
P_RMS_CONTROLADOR_d_T * localP , X_RMS_CONTROLADOR_e_T * localX ) { localX ->
integrator_CSTATE_j = localP -> P_3 ; localDW -> Memory_PreviousInput =
localP -> P_7 ; localX -> integrator_CSTATE_g = localP -> P_8 ; localDW ->
Memory_PreviousInput_m = localP -> P_12 ; localB -> B_7_22_0 = localP -> P_2
; } void CONTROLADOR_RMS_k_Disable ( SimStruct * S , DW_RMS_CONTROLADOR_m_T *
localDW ) { localDW -> RMS_MODE = false ; } void CONTROLADOR_RMS_c (
SimStruct * S , boolean_T rtu_Enable , real_T rtu_In , B_RMS_CONTROLADOR_o_T
* localB , DW_RMS_CONTROLADOR_m_T * localDW , P_RMS_CONTROLADOR_d_T * localP
, X_RMS_CONTROLADOR_e_T * localX , XDis_RMS_CONTROLADOR_k_T * localXdis ) {
int32_T isHit ; boolean_T rtb_B_7_4_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( rtu_Enable )
{ if ( ! localDW -> RMS_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart
( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } ( void )
memset ( & ( localXdis -> integrator_CSTATE_j ) , 0 , 2 * sizeof ( boolean_T
) ) ; localDW -> RMS_MODE = true ; } } else { if ( ssGetTaskTime ( S , 1 ) ==
ssGetTStart ( S ) ) { ( void ) memset ( & ( localXdis -> integrator_CSTATE_j
) , 1 , 2 * sizeof ( boolean_T ) ) ; } if ( localDW -> RMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; ( void ) memset ( & (
localXdis -> integrator_CSTATE_j ) , 1 , 2 * sizeof ( boolean_T ) ) ;
CONTROLADOR_RMS_k_Disable ( S , localDW ) ; } } } if ( localDW -> RMS_MODE )
{ localB -> B_7_0_0 = localX -> integrator_CSTATE_j ; { real_T * * uBuffer =
( real_T * * ) & localDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - localP -> P_4
; localB -> B_7_1_0 = CONTROLADOR_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , localDW -> TransportDelay_IWORK . CircularBufSize , &
localDW -> TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK .
Tail , localDW -> TransportDelay_IWORK . Head , localP -> P_5 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { localB -> B_7_3_0 = localP -> P_6 ; } rtb_B_7_4_0 = ( ssGetT ( S ) >=
localB -> B_7_3_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ localB -> B_7_5_0 = localDW -> Memory_PreviousInput ; } if ( rtb_B_7_4_0 )
{ localB -> B_6_0_0 = localB -> B_7_0_0 - localB -> B_7_1_0 ; localB ->
B_6_1_0 = localP -> P_1 * localB -> B_6_0_0 ; localB -> B_7_7_0 = localB ->
B_6_1_0 ; } else { localB -> B_7_7_0 = localB -> B_7_5_0 ; } localB ->
B_7_8_0 = localX -> integrator_CSTATE_g ; { real_T * * uBuffer = ( real_T * *
) & localDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - localP -> P_9 ; localB ->
B_7_9_0 = CONTROLADOR_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , *
uBuffer , localDW -> TransportDelay_IWORK_o . CircularBufSize , & localDW ->
TransportDelay_IWORK_o . Last , localDW -> TransportDelay_IWORK_o . Tail ,
localDW -> TransportDelay_IWORK_o . Head , localP -> P_10 , 0 , ( boolean_T )
( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) )
) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB ->
B_7_11_0 = localP -> P_11 ; } rtb_B_7_4_0 = ( ssGetT ( S ) >= localB ->
B_7_11_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB
-> B_7_13_0 = localDW -> Memory_PreviousInput_m ; } if ( rtb_B_7_4_0 ) {
localB -> B_5_0_0 = localB -> B_7_8_0 - localB -> B_7_9_0 ; localB -> B_5_1_0
= localP -> P_0 * localB -> B_5_0_0 ; localB -> B_7_15_0 = localB -> B_5_1_0
; } else { localB -> B_7_15_0 = localB -> B_7_13_0 ; } localB -> B_7_16_0 .
re = localB -> B_7_7_0 ; localB -> B_7_16_0 . im = localB -> B_7_15_0 ;
localB -> B_7_19_0 = ( muDoubleScalarSin ( localP -> P_15 * ssGetTaskTime ( S
, 0 ) + localP -> P_16 ) * localP -> P_13 + localP -> P_14 ) * rtu_In ;
localB -> B_7_21_0 = ( muDoubleScalarSin ( localP -> P_19 * ssGetTaskTime ( S
, 0 ) + localP -> P_20 ) * localP -> P_17 + localP -> P_18 ) * rtu_In ;
localB -> B_7_22_0 = localP -> P_21 * muDoubleScalarHypot ( localB ->
B_7_16_0 . re , localB -> B_7_16_0 . im ) ; if ( ssIsMajorTimeStep ( S ) != 0
) { srUpdateBC ( localDW -> RMS_SubsysRanBC ) ; } } } void
CONTROLADOR_RMS_c_Update ( SimStruct * S , B_RMS_CONTROLADOR_o_T * localB ,
DW_RMS_CONTROLADOR_m_T * localDW , P_RMS_CONTROLADOR_d_T * localP ) { int32_T
isHit ; if ( localDW -> RMS_MODE ) { { real_T * * uBuffer = ( real_T * * ) &
localDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; localDW -> TransportDelay_IWORK . Head = ( ( localDW ->
TransportDelay_IWORK . Head < ( localDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK . Head + 1 ) : 0
) ; if ( localDW -> TransportDelay_IWORK . Head == localDW ->
TransportDelay_IWORK . Tail ) { if ( !
CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_4 , uBuffer , ( boolean_T
) 0 , false , & localDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + localDW -> TransportDelay_IWORK . CircularBufSize ) [ localDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ localDW ->
TransportDelay_IWORK . Head ] = localB -> B_7_0_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { localDW -> Memory_PreviousInput = localB ->
B_7_7_0 ; } { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
localDW -> TransportDelay_IWORK_o . Head = ( ( localDW ->
TransportDelay_IWORK_o . Head < ( localDW -> TransportDelay_IWORK_o .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK_o . Head + 1 ) :
0 ) ; if ( localDW -> TransportDelay_IWORK_o . Head == localDW ->
TransportDelay_IWORK_o . Tail ) { if ( !
CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK_o . CircularBufSize , & localDW ->
TransportDelay_IWORK_o . Tail , & localDW -> TransportDelay_IWORK_o . Head ,
& localDW -> TransportDelay_IWORK_o . Last , simTime - localP -> P_9 ,
uBuffer , ( boolean_T ) 0 , false , & localDW -> TransportDelay_IWORK_o .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * uBuffer + localDW -> TransportDelay_IWORK_o .
CircularBufSize ) [ localDW -> TransportDelay_IWORK_o . Head ] = simTime ; (
* uBuffer ) [ localDW -> TransportDelay_IWORK_o . Head ] = localB -> B_7_8_0
; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localDW ->
Memory_PreviousInput_m = localB -> B_7_15_0 ; } } } void
CONTROLADOR_RMS_k_Deriv ( SimStruct * S , B_RMS_CONTROLADOR_o_T * localB ,
DW_RMS_CONTROLADOR_m_T * localDW , XDot_RMS_CONTROLADOR_g_T * localXdot ) {
if ( localDW -> RMS_MODE ) { localXdot -> integrator_CSTATE_j = localB ->
B_7_19_0 ; localXdot -> integrator_CSTATE_g = localB -> B_7_21_0 ; } else { {
real_T * dx ; int_T i ; dx = & ( localXdot -> integrator_CSTATE_j ) ; for ( i
= 0 ; i < 2 ; i ++ ) { dx [ i ] = 0.0 ; } } } } void
CONTROLADOR_RMS_p_ForcingFunction ( SimStruct * S , B_RMS_CONTROLADOR_o_T *
localB , DW_RMS_CONTROLADOR_m_T * localDW , XDot_RMS_CONTROLADOR_g_T *
localXdot ) { if ( localDW -> RMS_MODE ) { localXdot -> integrator_CSTATE_j =
localB -> B_7_19_0 ; localXdot -> integrator_CSTATE_g = localB -> B_7_21_0 ;
} else { { real_T * dx ; int_T i ; dx = & ( localXdot -> integrator_CSTATE_j
) ; for ( i = 0 ; i < 2 ; i ++ ) { dx [ i ] = 0.0 ; } } } } void
CONTROLADOR_RMS_n_Term ( SimStruct * const S ) { } void
CONTROLADOR_TrueRMS_g_Init ( SimStruct * S , B_TrueRMS_CONTROLADOR_j_T *
localB , DW_TrueRMS_CONTROLADOR_o_T * localDW , P_TrueRMS_CONTROLADOR_n_T *
localP , X_TrueRMS_CONTROLADOR_c_T * localX ) { localX -> integrator_CSTATE =
localP -> P_2 ; localDW -> Memory_PreviousInput = localP -> P_6 ; localB ->
B_9_10_0 = localP -> P_1 ; } void CONTROLADOR_TrueRMS_j_Disable ( SimStruct *
S , DW_TrueRMS_CONTROLADOR_o_T * localDW ) { localDW -> TrueRMS_MODE = false
; } void CONTROLADOR_TrueRMS_i ( SimStruct * S , boolean_T rtu_Enable ,
real_T rtu_In , B_TrueRMS_CONTROLADOR_j_T * localB ,
DW_TrueRMS_CONTROLADOR_o_T * localDW , P_TrueRMS_CONTROLADOR_n_T * localP ,
X_TrueRMS_CONTROLADOR_c_T * localX , XDis_TrueRMS_CONTROLADOR_o_T * localXdis
) { int32_T isHit ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 )
&& ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( rtu_Enable ) { if ( ! localDW ->
TrueRMS_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localXdis ->
integrator_CSTATE = 0 ; localDW -> TrueRMS_MODE = true ; } } else { if (
ssGetTaskTime ( S , 1 ) == ssGetTStart ( S ) ) { localXdis ->
integrator_CSTATE = 1 ; } if ( localDW -> TrueRMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; localXdis ->
integrator_CSTATE = 1 ; CONTROLADOR_TrueRMS_j_Disable ( S , localDW ) ; } } }
if ( localDW -> TrueRMS_MODE ) { localB -> B_9_1_0 = localX ->
integrator_CSTATE ; { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - localP -> P_3 ; localB -> B_9_2_0 =
CONTROLADOR_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer ,
localDW -> TransportDelay_IWORK . CircularBufSize , & localDW ->
TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK . Tail ,
localDW -> TransportDelay_IWORK . Head , localP -> P_4 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB ->
B_9_3_0 = localP -> P_5 ; localB -> B_9_4_0 = localDW -> Memory_PreviousInput
; } if ( ssGetT ( S ) >= localB -> B_9_3_0 ) { localB -> B_8_0_0 = localB ->
B_9_1_0 - localB -> B_9_2_0 ; localB -> B_8_1_0 = localP -> P_0 * localB ->
B_8_0_0 ; localB -> B_9_7_0 = localB -> B_8_1_0 ; } else { localB -> B_9_7_0
= localB -> B_9_4_0 ; } localB -> B_9_8_0 = rtu_In * rtu_In ; if (
ssIsMajorTimeStep ( S ) != 0 ) { localDW ->
Saturationtoavoidnegativesqrt_MODE = localB -> B_9_7_0 >= localP -> P_7 ? 1 :
localB -> B_9_7_0 > localP -> P_8 ? 0 : - 1 ; } localB -> B_9_9_0 = localDW
-> Saturationtoavoidnegativesqrt_MODE == 1 ? localP -> P_7 : localDW ->
Saturationtoavoidnegativesqrt_MODE == - 1 ? localP -> P_8 : localB -> B_9_7_0
; if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( localDW -> Sqrt_DWORK1 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; localDW -> Sqrt_DWORK1 = 0
; } localB -> B_9_10_0 = muDoubleScalarSqrt ( localB -> B_9_9_0 ) ;
srUpdateBC ( localDW -> TrueRMS_SubsysRanBC ) ; } else { if ( localB ->
B_9_9_0 < 0.0 ) { localB -> B_9_10_0 = - muDoubleScalarSqrt (
muDoubleScalarAbs ( localB -> B_9_9_0 ) ) ; } else { localB -> B_9_10_0 =
muDoubleScalarSqrt ( localB -> B_9_9_0 ) ; } if ( localB -> B_9_9_0 < 0.0 ) {
localDW -> Sqrt_DWORK1 = 1 ; } } } } void CONTROLADOR_TrueRMS_m_Update (
SimStruct * S , B_TrueRMS_CONTROLADOR_j_T * localB ,
DW_TrueRMS_CONTROLADOR_o_T * localDW , P_TrueRMS_CONTROLADOR_n_T * localP ) {
int32_T isHit ; if ( localDW -> TrueRMS_MODE ) { { real_T * * uBuffer = (
real_T * * ) & localDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; localDW -> TransportDelay_IWORK . Head = ( ( localDW
-> TransportDelay_IWORK . Head < ( localDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK . Head + 1 ) : 0
) ; if ( localDW -> TransportDelay_IWORK . Head == localDW ->
TransportDelay_IWORK . Tail ) { if ( !
CONTROLADOR_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_3 , uBuffer , ( boolean_T
) 0 , false , & localDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + localDW -> TransportDelay_IWORK . CircularBufSize ) [ localDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ localDW ->
TransportDelay_IWORK . Head ] = localB -> B_9_1_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { localDW -> Memory_PreviousInput = localB ->
B_9_7_0 ; } } } void CONTROLADOR_TrueRMS_c_Deriv ( SimStruct * S ,
B_TrueRMS_CONTROLADOR_j_T * localB , DW_TrueRMS_CONTROLADOR_o_T * localDW ,
XDot_TrueRMS_CONTROLADOR_c_T * localXdot ) { if ( localDW -> TrueRMS_MODE ) {
localXdot -> integrator_CSTATE = localB -> B_9_8_0 ; } else { localXdot ->
integrator_CSTATE = 0.0 ; } } void CONTROLADOR_TrueRMS_i_ForcingFunction (
SimStruct * S , B_TrueRMS_CONTROLADOR_j_T * localB ,
DW_TrueRMS_CONTROLADOR_o_T * localDW , XDot_TrueRMS_CONTROLADOR_c_T *
localXdot ) { if ( localDW -> TrueRMS_MODE ) { localXdot -> integrator_CSTATE
= localB -> B_9_8_0 ; } else { localXdot -> integrator_CSTATE = 0.0 ; } }
void CONTROLADOR_TrueRMS_j_ZC ( SimStruct * S , B_TrueRMS_CONTROLADOR_j_T *
localB , DW_TrueRMS_CONTROLADOR_o_T * localDW , P_TrueRMS_CONTROLADOR_n_T *
localP , ZCV_TrueRMS_CONTROLADOR_g_T * localZCSV ) { if ( localDW ->
TrueRMS_MODE ) { localZCSV -> Saturationtoavoidnegativesqrt_UprLim_ZC =
localB -> B_9_7_0 - localP -> P_7 ; localZCSV ->
Saturationtoavoidnegativesqrt_LwrLim_ZC = localB -> B_9_7_0 - localP -> P_8 ;
} else { { real_T * zcsv = & ( localZCSV ->
Saturationtoavoidnegativesqrt_UprLim_ZC ) ; int_T i ; for ( i = 0 ; i < 2 ; i
++ ) { zcsv [ i ] = 0.0 ; } } } } void CONTROLADOR_TrueRMS_p_Term ( SimStruct
* const S ) { } static void mdlOutputs ( SimStruct * S , int_T tid ) {
B_CONTROLADOR_T * _rtB ; DW_CONTROLADOR_T * _rtDW ; P_CONTROLADOR_T * _rtP ;
X_CONTROLADOR_T * _rtX ; real_T rtb_B_15_10_0 ; real_T tmp ; _rtDW = ( (
DW_CONTROLADOR_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( ( X_CONTROLADOR_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_CONTROLADOR_T * ) ssGetModelRtp ( S )
) ; _rtB = ( ( B_CONTROLADOR_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB ->
B_15_0_0 = ssGetT ( S ) ; rtb_B_15_10_0 = _rtP -> P_8 * _rtB -> B_15_0_0 ; if
( rtb_B_15_10_0 - muDoubleScalarFloor ( rtb_B_15_10_0 ) >= 0.5 ) { _rtB ->
B_15_1_0 = _rtP -> P_7 ; } else { _rtB -> B_15_1_0 = - _rtP -> P_7 ; } _rtB
-> B_15_2_0 [ 0 ] = _rtB -> B_15_1_0 ; _rtB -> B_15_2_0 [ 1 ] = 0.0 ; _rtB ->
B_15_2_0 [ 2 ] = 0.0 ; _rtB -> B_15_2_0 [ 3 ] = 0.0 ; _rtB -> B_15_3_0 = _rtX
-> Integrator_CSTATE ; _rtB -> B_15_4_0 = _rtP -> P_10 * _rtB -> B_15_1_0 ;
_rtB -> B_15_5_0 [ 0 ] = _rtB -> B_15_4_0 ; _rtB -> B_15_5_0 [ 1 ] = 0.0 ;
_rtB -> B_15_5_0 [ 2 ] = 0.0 ; _rtB -> B_15_5_0 [ 3 ] = 0.0 ;
ssCallAccelRunBlock ( S , 15 , _rtDW ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 15 , 7 ,
SS_CALL_MDL_OUTPUTS ) ; CONTROLADOR_TrueRMS_i ( S , _rtB -> B_15_12_0 , _rtB
-> B_4_12_0 [ 1 ] , & _rtB -> TrueRMS_i , & _rtDW -> TrueRMS_i , & _rtP ->
TrueRMS_i , & _rtX -> TrueRMS_i , & ( ( XDis_CONTROLADOR_T * )
ssGetContStateDisabled ( S ) ) -> TrueRMS_i ) ; CONTROLADOR_RMS_c ( S , _rtB
-> B_15_13_0 , _rtB -> B_4_12_0 [ 1 ] , & _rtB -> RMS_m , & _rtDW -> RMS_m ,
& _rtP -> RMS_m , & _rtX -> RMS_m , & ( ( XDis_CONTROLADOR_T * )
ssGetContStateDisabled ( S ) ) -> RMS_m ) ; if ( _rtB -> B_15_12_0 ) {
rtb_B_15_10_0 = _rtB -> TrueRMS_i . B_9_10_0 ; } else { rtb_B_15_10_0 = _rtB
-> RMS_m . B_7_22_0 ; } CONTROLADOR_TrueRMS_i ( S , _rtB -> B_15_3_0_k , _rtB
-> B_4_12_0 [ 3 ] , & _rtB -> TrueRMS , & _rtDW -> TrueRMS , & _rtP ->
TrueRMS , & _rtX -> TrueRMS , & ( ( XDis_CONTROLADOR_T * )
ssGetContStateDisabled ( S ) ) -> TrueRMS ) ; CONTROLADOR_RMS_c ( S , _rtB ->
B_15_4_0_c , _rtB -> B_4_12_0 [ 3 ] , & _rtB -> RMS , & _rtDW -> RMS , & _rtP
-> RMS , & _rtX -> RMS , & ( ( XDis_CONTROLADOR_T * ) ssGetContStateDisabled
( S ) ) -> RMS ) ; if ( _rtB -> B_15_3_0_k ) { tmp = _rtB -> TrueRMS .
B_9_10_0 ; } else { tmp = _rtB -> RMS . B_7_22_0 ; } _rtB -> B_15_14_0 =
rtb_B_15_10_0 * tmp ; _rtB -> B_15_15_0 = _rtB -> B_4_19_0 / _rtB ->
B_15_14_0 ; ssCallAccelRunBlock ( S , 15 , 16 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 15 , 17 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 15 , 30 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 15 , 31 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 15 , 32 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_15_34_0
= _rtP -> P_11 * _rtB -> B_4_0_0 ; ssCallAccelRunBlock ( S , 15 , 38 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 15 , 40 ,
SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID2 ( SimStruct * S , int_T tid ) { B_CONTROLADOR_T * _rtB ;
P_CONTROLADOR_T * _rtP ; _rtP = ( ( P_CONTROLADOR_T * ) ssGetModelRtp ( S ) )
; _rtB = ( ( B_CONTROLADOR_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB ->
B_15_0_0_m = _rtP -> P_12 ; _rtB -> B_15_1_0_c = _rtP -> P_13 ; _rtB ->
B_15_3_0_k = ( _rtP -> P_14 != 0.0 ) ; _rtB -> B_15_4_0_c = ! _rtB ->
B_15_3_0_k ; _rtB -> B_15_6_0 = ( _rtP -> P_15 != 0.0 ) ; _rtB -> B_15_7_0 =
! _rtB -> B_15_6_0 ; _rtB -> B_15_9_0 = ( _rtP -> P_16 != 0.0 ) ; _rtB ->
B_15_10_0 = ! _rtB -> B_15_9_0 ; _rtB -> B_15_12_0 = ( _rtP -> P_17 != 0.0 )
; _rtB -> B_15_13_0 = ! _rtB -> B_15_12_0 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_CONTROLADOR_T * _rtB
; DW_CONTROLADOR_T * _rtDW ; P_CONTROLADOR_T * _rtP ; _rtDW = ( (
DW_CONTROLADOR_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_CONTROLADOR_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_CONTROLADOR_T * ) _ssGetModelBlockIO ( S
) ) ; ssCallAccelRunBlock ( S , 4 , 11 , SS_CALL_MDL_UPDATE ) ;
CONTROLADOR_RMS_Update ( S , & _rtB -> RMS_c , & _rtDW -> RMS_c , & _rtP ->
RMS_c ) ; CONTROLADOR_TrueRMS_Update ( S , & _rtB -> TrueRMS_g , & _rtDW ->
TrueRMS_g , & _rtP -> TrueRMS_g ) ; CONTROLADOR_RMS_Update ( S , & _rtB ->
RMS_n , & _rtDW -> RMS_n , & _rtP -> RMS_n ) ; CONTROLADOR_TrueRMS_Update ( S
, & _rtB -> TrueRMS_k , & _rtDW -> TrueRMS_k , & _rtP -> TrueRMS_k ) ;
CONTROLADOR_TrueRMS_m_Update ( S , & _rtB -> TrueRMS_i , & _rtDW -> TrueRMS_i
, & _rtP -> TrueRMS_i ) ; CONTROLADOR_RMS_c_Update ( S , & _rtB -> RMS_m , &
_rtDW -> RMS_m , & _rtP -> RMS_m ) ; CONTROLADOR_TrueRMS_m_Update ( S , &
_rtB -> TrueRMS , & _rtDW -> TrueRMS , & _rtP -> TrueRMS ) ;
CONTROLADOR_RMS_c_Update ( S , & _rtB -> RMS , & _rtDW -> RMS , & _rtP -> RMS
) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID2 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_CONTROLADOR_T * _rtB ;
DW_CONTROLADOR_T * _rtDW ; XDot_CONTROLADOR_T * _rtXdot ; _rtDW = ( (
DW_CONTROLADOR_T * ) ssGetRootDWork ( S ) ) ; _rtXdot = ( (
XDot_CONTROLADOR_T * ) ssGetdX ( S ) ) ; _rtB = ( ( B_CONTROLADOR_T * )
_ssGetModelBlockIO ( S ) ) ; _rtXdot -> Integrator_CSTATE = _rtB -> B_15_34_0
; ssCallAccelRunBlock ( S , 4 , 11 , SS_CALL_MDL_DERIVATIVES ) ;
CONTROLADOR_RMS_Deriv ( S , & _rtB -> RMS_c , & _rtDW -> RMS_c , & _rtXdot ->
RMS_c ) ; CONTROLADOR_TrueRMS_Deriv ( S , & _rtB -> TrueRMS_g , & _rtDW ->
TrueRMS_g , & _rtXdot -> TrueRMS_g ) ; CONTROLADOR_RMS_Deriv ( S , & _rtB ->
RMS_n , & _rtDW -> RMS_n , & _rtXdot -> RMS_n ) ; CONTROLADOR_TrueRMS_Deriv (
S , & _rtB -> TrueRMS_k , & _rtDW -> TrueRMS_k , & _rtXdot -> TrueRMS_k ) ;
CONTROLADOR_TrueRMS_c_Deriv ( S , & _rtB -> TrueRMS_i , & _rtDW -> TrueRMS_i
, & _rtXdot -> TrueRMS_i ) ; CONTROLADOR_RMS_k_Deriv ( S , & _rtB -> RMS_m ,
& _rtDW -> RMS_m , & _rtXdot -> RMS_m ) ; CONTROLADOR_TrueRMS_c_Deriv ( S , &
_rtB -> TrueRMS , & _rtDW -> TrueRMS , & _rtXdot -> TrueRMS ) ;
CONTROLADOR_RMS_k_Deriv ( S , & _rtB -> RMS , & _rtDW -> RMS , & _rtXdot ->
RMS ) ; }
#define MDL_FORCINGFUNCTION
static void mdlForcingFunction ( SimStruct * S ) { B_CONTROLADOR_T * _rtB ;
DW_CONTROLADOR_T * _rtDW ; XDot_CONTROLADOR_T * _rtXdot ; _rtDW = ( (
DW_CONTROLADOR_T * ) ssGetRootDWork ( S ) ) ; _rtXdot = ( (
XDot_CONTROLADOR_T * ) ssGetdX ( S ) ) ; _rtB = ( ( B_CONTROLADOR_T * )
_ssGetModelBlockIO ( S ) ) ; _rtXdot -> Integrator_CSTATE = _rtB -> B_15_34_0
; ssCallAccelRunBlock ( S , 4 , 11 , SS_CALL_MDL_FORCINGFUNCTION ) ;
CONTROLADOR_RMS_ForcingFunction ( S , & _rtB -> RMS_c , & _rtDW -> RMS_c , &
_rtXdot -> RMS_c ) ; CONTROLADOR_TrueRMS_ForcingFunction ( S , & _rtB ->
TrueRMS_g , & _rtDW -> TrueRMS_g , & _rtXdot -> TrueRMS_g ) ;
CONTROLADOR_RMS_ForcingFunction ( S , & _rtB -> RMS_n , & _rtDW -> RMS_n , &
_rtXdot -> RMS_n ) ; CONTROLADOR_TrueRMS_ForcingFunction ( S , & _rtB ->
TrueRMS_k , & _rtDW -> TrueRMS_k , & _rtXdot -> TrueRMS_k ) ;
CONTROLADOR_TrueRMS_i_ForcingFunction ( S , & _rtB -> TrueRMS_i , & _rtDW ->
TrueRMS_i , & _rtXdot -> TrueRMS_i ) ; CONTROLADOR_RMS_p_ForcingFunction ( S
, & _rtB -> RMS_m , & _rtDW -> RMS_m , & _rtXdot -> RMS_m ) ;
CONTROLADOR_TrueRMS_i_ForcingFunction ( S , & _rtB -> TrueRMS , & _rtDW ->
TrueRMS , & _rtXdot -> TrueRMS ) ; CONTROLADOR_RMS_p_ForcingFunction ( S , &
_rtB -> RMS , & _rtDW -> RMS , & _rtXdot -> RMS ) ; }
#define MDL_MASSMATRIX
static void mdlMassMatrix ( SimStruct * S ) { ssCallAccelRunBlock ( S , 4 ,
11 , SS_CALL_MDL_MASSMATRIX ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_CONTROLADOR_T * _rtB ;
DW_CONTROLADOR_T * _rtDW ; P_CONTROLADOR_T * _rtP ; ZCV_CONTROLADOR_T *
_rtZCSV ; _rtDW = ( ( DW_CONTROLADOR_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV =
( ( ZCV_CONTROLADOR_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( (
P_CONTROLADOR_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_CONTROLADOR_T * )
_ssGetModelBlockIO ( S ) ) ; _rtZCSV -> Saturation1_UprLim_ZC = _rtB ->
B_4_3_0 - _rtP -> P_2 ; _rtZCSV -> Saturation1_LwrLim_ZC = _rtB -> B_4_3_0 -
_rtP -> P_3 ; ssCallAccelRunBlock ( S , 4 , 11 , SS_CALL_MDL_ZERO_CROSSINGS )
; CONTROLADOR_TrueRMS_ZC ( S , & _rtB -> TrueRMS_g , & _rtDW -> TrueRMS_g , &
_rtP -> TrueRMS_g , & _rtZCSV -> TrueRMS_g ) ; CONTROLADOR_TrueRMS_ZC ( S , &
_rtB -> TrueRMS_k , & _rtDW -> TrueRMS_k , & _rtP -> TrueRMS_k , & _rtZCSV ->
TrueRMS_k ) ; CONTROLADOR_TrueRMS_j_ZC ( S , & _rtB -> TrueRMS_i , & _rtDW ->
TrueRMS_i , & _rtP -> TrueRMS_i , & _rtZCSV -> TrueRMS_i ) ;
CONTROLADOR_TrueRMS_j_ZC ( S , & _rtB -> TrueRMS , & _rtDW -> TrueRMS , &
_rtP -> TrueRMS , & _rtZCSV -> TrueRMS ) ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 289124803U ) ; ssSetChecksumVal
( S , 1 , 2712633737U ) ; ssSetChecksumVal ( S , 2 , 1685115190U ) ;
ssSetChecksumVal ( S , 3 , 426881713U ) ; { mxArray * slVerStructMat = ( NULL
) ; mxArray * slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10
] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat ,
"ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField (
slVerStructMat , 0 , "Version" ) ; if ( slVerMat == ( NULL ) ) { status = 1 ;
} else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.4" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_CONTROLADOR_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_CONTROLADOR_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_CONTROLADOR_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & CONTROLADOR_rtDefaultP ) ; if ( ssGetSizeofDWork ( S ) == sizeof (
DW_CONTROLADOR_T ) ) { { ( ( DW_CONTROLADOR_T * ) ssGetRootDWork ( S ) ) ->
STATE_1_MASS_MATRIX_PR = 7 ; } } rt_InitInfAndNaN ( sizeof ( real_T ) ) ; ( (
P_CONTROLADOR_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_i . P_7 = rtInf ; ( (
P_CONTROLADOR_T * ) ssGetModelRtp ( S ) ) -> TrueRMS . P_7 = rtInf ; ( (
P_CONTROLADOR_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_k . P_7 = rtInf ; ( (
P_CONTROLADOR_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_g . P_7 = rtInf ; }
static void mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn
( S , mdlOutputsTID2 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
