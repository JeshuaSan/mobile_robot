/* 
 * File:   robot.h
 * Author: Jesus
 *
 * Created on April 4, 2013, 11:57 AM
 */

#ifndef ROBOT_H
#define	ROBOT_H
#include "include/chip.h"
#include <stdint.h>

#include "flowcontrol.h"

typedef struct tagRobotVars{
    int16_t wheelSpeed[2];
    int32_t wheelPulses[2];
    int16_t wheelPositionP[2];
    int16_t wheelPositionM[2];
    int16_t wheelPositionCM[2];
    uint16_t motorCurrent[2];
}RobotVars;
extern RobotVars robotVar;

typedef struct{
    uint16_t pulses2cm[2];
    uint16_t maxFFSpeed;
    uint16_t maxRotSpeed;
}Params;

typedef struct{
    int16_t theta;
    int16_t x;
    int16_t y;
    uint16_t distance;
}Pose;

typedef struct{
    uint8_t axle;
}Dimension;

typedef struct{
    Pose pose;
    Dimension dimension;
    Params params;
}Robot;
extern Robot robot;

void rComputeWheelSpeed(RWheel wheel);
void rGetWheelPosition(RWheel wheel, uint8_t mode, uint16_t* result);
void rComputeWheelPulses(RWheel wheel);

void rComputeRobotSpeed();
void rComputeRobotPosition();

static void rDespPulses(RWheel wheel, uint16_t* result);
static void rDespWheelCM(RWheel wheel, uint16_t* result);
static void rDespWheelP(RWheel wheel, uint16_t* result);

#endif	/* ROBOT_H */

