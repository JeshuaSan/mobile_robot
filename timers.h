/*
 * File:   timers.h
 * Author: Jesus
 *
 * Created on April 3, 2013, 8:05 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#include "include/chip.h"
#include "include/ports.h"


// Common defines

// TON: Timer On bit
typedef enum TONValues{
    TRM_OFF,  // 0 = Stops 16-bit timer
    TRM_ON  // 1 = Starts 16-bit timer
}TONValues;
typedef struct tagTON{
    TONValues TRM_OFF :1;
    TONValues TRM_ON:1;
}TON;
static TON TONconfig = {TRM_OFF,TRM_ON};


// TSIDL: Stop in Idle Mode bit
typedef enum TSIDLValues{
    TRM_STOP_ON_IDLE,      // 0 = Continue timer operation in Idle mode
    TRM_CONTINUE_ON_IDLE   // 1 = Discontinue timer operation when device enters Idle mode
}TSIDLValues;
typedef struct tagTSIDL{
    TSIDLValues TRM_STOP_ON_IDLE :1;
    TSIDLValues TRM_CONTINUE_ON_IDLE:1;
}TSIDL;
static TSIDL TSIDLconfig = {TRM_STOP_ON_IDLE,TRM_CONTINUE_ON_IDLE};


// TGATE: Timer2 Gated Time Accumulation Enable bit
typedef enum TGATEValues{
    TRM_GATE_OFF, // 0 = Gated time accumulation disabled
    TRM_GATE_ON   // 1 = Gated time accumulation enabled
}TGATEValues;
typedef struct tagTGATE{
    TGATEValues TRM_GATE_OFF :1;
    TGATEValues TRM_GATE_ON:1;
}TGATE;
static TGATE TGATEconfig = {TRM_GATE_OFF,TRM_GATE_ON};


// TCKPS<1:0>: Timerx Input Clock Prescale Select bits
typedef enum TCKPSValues{
    TRM_PS_1,      // 00 = 1:1 prescale value
    TRM_PS_8,      // 01 = 1:8 prescale value
    TRM_PS_64,     // 10 = 1:64 prescale value
    TRM_PS_256     // 11 = 1:256 prescale value
}TCKPSValues;
typedef struct tagTCKPS{
    TCKPSValues TRM_PS_1   :2;
    TCKPSValues TRM_PS_8   :2;
    TCKPSValues TRM_PS_64  :2;
    TCKPSValues TRM_PS_256 :2;
}TCKPS;
static TCKPS TCKPSconfig = {TRM_PS_1,TRM_PS_8,TRM_PS_64,TRM_PS_256};


// TCS: Timerx Clock Source Select bit
typedef enum TCSValues{
    TRM_CLK_INTERNAL,  // 0 = Internal clock (FOSC/2)
    TRM_CLK_EXTERNAL   // 1 = External clock from TxCK pin
}TCSValues;
typedef struct tagTCS{
    TCSValues TRM_CLK_INTERNAL :1;
    TCSValues TRM_CLK_EXTERNAL:1;
}TCS;
static TCS TCSconfig = {TRM_CLK_INTERNAL,TRM_CLK_EXTERNAL};

///
/// T1CON: TIMER1 CONTROL REGISTER
///

// TSYNC: Timer1 External Clock Input Synchronization Select bit
typedef enum TSYNCValues{
    TRM1_SYNC_OFF,  // 0 = Do not synchronize external clock input
    TRM1_SYNC_ON    // 1 = Synchronize external clock input
}TSYNCValues;
typedef struct tagTSYNC{
    TSYNCValues TRM1_SYNC_OFF :1;
    TSYNCValues TRM1_SYNC_ON:1;
}TSYNC;
static TSYNC TSYNCconfig = {TRM1_SYNC_OFF,TRM1_SYNC_ON};

///
/// T2CON: TIMER CONTROL REGISTER
///

// T32: 32-bit Timerx Mode Select bit
typedef enum T32Values{
    TRM2_16_BIT,    // 0 = TMRx and TMRy form separate 16-bit timer
    TRM2_32BIT      // 1 = TMRx and TMRy form a 32-bit timer
}T32Values;
typedef struct tagT32{
    T32Values TRM2_16_BIT :1;
    T32Values TRM2_32BIT:1;
}T32;
static T32 T32config = {TRM2_16_BIT,TRM2_32BIT};


//
void timer1Config();
void timer1Config();
void timer3Config();

#endif	/* TIMERS_H */

