#include "process.h"
#include "flowcontrol.h"
#include "robot.h"

void ProcessAuto() {
    if(isrFlag.tPeriod) {
        rComputeWheelSpeed(wheel.left);
        rComputeWheelSpeed(wheel.right);
        
        rComputeWheelPulses(wheel.left);
        rComputeWheelPulses(wheel.right);

        ctrlComputeSpeedControl();
        
        isrFlag.tPeriod = 0;
    }


    if(isrFlag.tPeriod_x2) {
        rComputeCinematics();
        ctrlComputeOrientationControl();
        adcGetCurrent();
        
        isrFlag.tPeriod_x2 = 0;
    }


    if(isrFlag.tPeriod_x4) {
        ctrlComputeDistanceControl();

        isrFlag.tPeriod_x4 = 0;
    }
}


void ProcessManual() {
    if(isrFlag.tPeriod) {
        rComputeWheelSpeed(wheel.left);
        rComputeWheelSpeed(wheel.right);

        rComputeWheelPulses(wheel.left);
        rComputeWheelPulses(wheel.right);

        isrFlag.tPeriod = 0;
    }

    if(isrFlag.tPeriod_x2) {
        rComputeCinematics();

        isrFlag.tPeriod_x2 = 0;
    }
}


void ProcessCharact() {
    if(isrFlag.tPeriod_x2) {
        adcGetCurrent();
        isrFlag.tPeriod_x2 = 0;
    }

}


void ProcessTune() {
    if(isrFlag.tPeriod) {
        rComputeWheelSpeed(wheel.left);
        rComputeWheelSpeed(wheel.right);

        ctrlComputeSpeedControl();
        isrFlag.tPeriod = 0;
    }

   if(isrFlag.tPeriod_x2) {
        adcGetCurrent();
        isrFlag.tPeriod_x2 = 0;
    }
}
