/* 
 * File:   control.h
 * Author: Jesus
 *
 * Created on April 11, 2013, 2:33 PM
 */

#ifndef CONTROL_H
#define	CONTROL_H

#include <dsp.h>
#include <stdint.h>
#include "flowcontrol.h"

typedef enum{
    kp = 0,
    ki,
    kd
}KCoeffIndex;

typedef struct tagCtrlFlag{
    uint8_t useAccelRamp;
    uint8_t accelRamp[2];
    uint8_t speedDirection[2];
    uint8_t computeAngle;
    uint8_t computeOrientationControl;
    uint8_t computeDistanceControl;
}CtrlFlag;
extern CtrlFlag ctrlFlag;

typedef enum {
    pidLeft = 0,
    pidRight,
    pidOrientation,
    pidDistance
}PIDindex;

void ctrlConfigPID(void);
void ctrlInitPID(PIDindex iPID);
void ctrlResetPID(PIDindex iPID);
void ctrlSetGain(PIDindex iPID, KCoeffIndex kIndex, fractional k);

void ctrlComputeSpeedControl();
void ctrlSetSpeed(PIDindex i, fractional speed);
static void ctrlSetAccelRamp(PIDindex iPID);
static void ctrlComputeAccelRamp(PIDindex iPID);

void ctrlComputeOrientationControl();
void ctrlSetAngle(fractional angle);

void ctrlComputeDistanceControl();
void ctrlSetDistance(fractional distance);

void ctrlGetSetPoint(PIDindex iPID, uint16_t* dataOut);
void ctrlGetMeasuredOutput(PIDindex iPID, uint16_t* dataOut);
void ctrlGetControlOutput(PIDindex iPID, uint16_t* dataOut);

#endif	/* CONTROL_H */

