/* 
 * File:   global.h
 * Author: Jesus
 *
 * Created on April 3, 2013, 1:33 PM
 */

#ifndef FLOWCONTROL_H
#define	FLOWCONTROL_H

#include "Commands.h"
#include <stdint.h>

// Flow control
//typedef enum{
//    MODE_AUTO = 1,  // 1 = Auto
//    MODE_MANUAL,    // 2 = Manual
//    MODE_CHARACT,   // 3 = Characterization
//    MODE_CONFIG     // 4 = Configuration
//}ModeState;

typedef enum {
    NO_CHANGE,  // 0 = Mode NO change
    CHANGE,    // 1 = Mode change
}Status;


// Wheel constants
typedef enum {
    L = 0,
    R
}RWheel;
typedef struct tagWheel {
    RWheel left;
    RWheel right;
}Wheel;
extern Wheel wheel;

// ISR Flags
typedef struct tagISRFlag {
    uint8_t tmr1overflow;
    uint8_t tmr2overflow;
    uint8_t tPeriod;
    uint8_t tPeriod_x2;
    uint8_t tPeriod_x4;
}ISRFlag;
extern volatile ISRFlag isrFlag;

// ISR Variables
typedef struct tagISRVariable {
    int16_t icPeriod[2];
    uint8_t timePeriod_x2;
    uint8_t timePeriod_x4;
    uint16_t* adcSampleAdrr[2];
    uint16_t adcSample[2];
}ISRVar;
extern volatile ISRVar isrVar;


// Function prototypes
void fcSetNewModeState(ModeState newMode);
ModeState fcGetModeState(void);
Status fcGetModeChange(void);

static void fcSetAuto(void);
static void fcSetManual(void);
static void fcSetCharact(void);
static void fcSetTune(void);

#endif	/* GLOBAL_H */

