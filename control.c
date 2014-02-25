#include "control.h"
#include "robot.h"
#include <libq.h>

/** Control
 * 0 = Left wheel speed
 * 1 = Right wheel speed
 * 2 = Orientation
 * 3 = Distance
 */
tPID ctrlPID[4];
fractional abcCoefficient[4][3] __attribute__ ((space(xmemory),far));
fractional controlHistory[4][3] __attribute__ ((space(ymemory),far));
fractional kCoeffs[4][3];

//tPID leftPID;
//fractional abcCoefficient_L[3] __attribute__  ((space(xmemory),far));
//fractional controlHistory_L[3] __attribute__  ((space(ymemory),far));
//fractional kCoeffs_L[] = {0,0,0};

struct {
    fractional Acceleration;
    fractional Deceleration;
    fractional minWheelDC[2];
    fractional maxWheelSpeed;
    fractional maxWheelFFSpeed;
    fractional maxWheelRotSpeed;
    fractional regulatedSpeed;
    fractional minDistance;
    fractional minAngle;
}Limits = {
    .Acceleration = 10,                     //
    .Deceleration = 100,                    //
    .minWheelDC = {Q15(0.2), Q15(0.2)},     // Min wheel Duty cycle
    .maxWheelSpeed = 2450,                  // [Hz] Max wheel overall speed before encoder => 70rpm * 131.25 / 60s * 16ppr = 2450Hz
    .maxWheelFFSpeed = 1050,                // [Hz] Max wheel forward speed before encoder => 30rpm * 131.25 / 60s * 16ppr = 1050Hz
    .maxWheelRotSpeed = 525,                // [Hz] Max wheel rotational speed before encoder => 15rpm * 131.25 / 60s * 16ppr = 525Hz
    .regulatedSpeed = 1,                    // To regulate speed during distance control => actual speed = maxWheelSped / regulatedSpeed
    .minDistance = 10,                      // [cm] Min distante to compute control
    .minAngle = 256,                        // [frac]*pi radians => 0.008 pi radians
};

struct {
    fractional Speed[2];
    fractional Accel[2];
    fractional Distance;
    fractional Angle;
}SetPoint = {
    .Speed = {0,0},
    .Accel = {0,0},
    .Distance = 0,
    .Angle = 0,
};

typedef struct {
    fractional gain[4][3];
}Gain;

Gain gainIn = {
    // Left wheel speed
    .gain[pidLeft][kp]          = Q15(0.1800),
    .gain[pidLeft][ki]          = Q15(0.0090),
    .gain[pidLeft][kd]          = Q15(0.0000),
    // Right wheel speed
    .gain[pidRight][kp]         = Q15(0.1800),
    .gain[pidRight][ki]         = Q15(0.0090),
    .gain[pidRight][kd]         = Q15(0.0000),
    // Orientation
    .gain[pidOrientation][kp]   = Q15(0.1000),
    .gain[pidOrientation][ki]   = Q15(0.0010),
    .gain[pidOrientation][kd]   = Q15(0.0000),
    // Distance
    .gain[pidDistance][kp]      = Q15(0.7850),
    .gain[pidDistance][ki]      = Q15(0.0330),
    .gain[pidDistance][kd]      = Q15(0.0000),
};

Gain gainCurr;
Gain gainNew;

CtrlFlag ctrlFlag = {
    .useAccelRamp = 0,
    .accelRamp = {0,0},
    .speedDirection = {0,0},
    .computeAngle = 0,
    .computeDistanceControl = 0,
    .computeOrientationControl = 0,
};


void ctrlConfigPID() {
    gainCurr = gainIn;
    ctrlInitPID(pidLeft);     // Tune gains first !!
    ctrlInitPID(pidRight);
    ctrlInitPID(pidDistance);
    ctrlInitPID(pidOrientation);
}


void ctrlInitPID(PIDindex iPID) {
    ctrlPID[iPID].abcCoefficients = &abcCoefficient[iPID][0];
    ctrlPID[iPID].controlHistory = &controlHistory[iPID][0];
    PIDInit(&ctrlPID[iPID]);

    kCoeffs[iPID][kp] = gainIn.gain[iPID][kp];
    kCoeffs[iPID][ki] = gainIn.gain[iPID][ki];
    kCoeffs[iPID][kd] = gainIn.gain[iPID][kd];
    PIDCoeffCalc(&kCoeffs[iPID][0], &ctrlPID[iPID]);


//    leftPID.abcCoefficients = &abcCoefficient_L[0];
//    leftPID.controlHistory = &controlHistory_L[0];
//    PIDInit(&leftPID);
//
//    kCoeffs_L[kp] = Q15(0.1800);
//    kCoeffs_L[ki] = Q15(0.0090);
//    kCoeffs_L[kd] = Q15(-0.0090);
//    PIDCoeffCalc(&kCoeffs_L[0], &leftPID);

}


void ctrlResetPID(PIDindex iPID) {
    kCoeffs[iPID][kp] = gainIn.gain[iPID][kp];
    kCoeffs[iPID][ki] = gainIn.gain[iPID][ki];
    kCoeffs[iPID][kd] = gainIn.gain[iPID][kd];

    ctrlPID[iPID].abcCoefficients = &abcCoefficient[iPID][0];
    ctrlPID[iPID].controlHistory = &controlHistory[iPID][0];
    PIDInit(&ctrlPID[iPID]);
    PIDCoeffCalc(&kCoeffs[iPID][0], &ctrlPID[iPID]);

    ctrlPID[iPID].controlReference = 0;
}


void ctrlSetGain(PIDindex iPID, KCoeffIndex iK, fractional k) {
    gainNew = gainCurr;
    gainNew.gain[iPID][iK] = k;

    kCoeffs[iPID][kp] = gainNew.gain[iPID][kp];
    kCoeffs[iPID][ki] = gainNew.gain[iPID][ki];
    kCoeffs[iPID][kd] = gainNew.gain[iPID][kd];

    ctrlPID[iPID].abcCoefficients = &abcCoefficient[iPID][0];
    ctrlPID[iPID].controlHistory = &controlHistory[iPID][0];
    PIDInit(&ctrlPID[iPID]);
    PIDCoeffCalc(&kCoeffs[iPID][0], &ctrlPID[iPID]);

    ctrlPID[iPID].controlReference = 0;

    gainCurr = gainNew;
}


/* Speed control **************************************************************/
void ctrlComputeSpeedControl() {
    PIDindex i = pidLeft;
    for(i; i <= pidRight; i++) {
        if(ctrlFlag.useAccelRamp == 1) {
            ctrlComputeAccelRamp(i);
        }
        else{
            ctrlPID[i].controlReference = SetPoint.Speed[i];
        }

        ctrlPID[i].measuredOutput = 12 * robotVar.wheelSpeed[i];
        PID(&ctrlPID[i]);

        if(ctrlPID[i].controlOutput != 0) {
//            if(_Q15abs(ctrlPID[i].controlOutput) > _Q15abs(Limits.minWheelDC[i])) {                        // -pidOut < -lim ^ lim > pidOut
                pwmSetDCfrac(i+1, ctrlPID[i].controlOutput);   // &P1DC1
//            }
//            else if(ctrlPID[i].controlOutput > 0 && ctrlPID[i].controlOutput <= Limits.minWheelDC[i]){    // 0 < pidout <= lim
//                pwmSetDCfrac(i+1, Limits.minWheelDC[i]);
//            }
//            else {                                                                                          // -lim >= pidout > 0
//                pwmSetDCfrac(i+1, -Limits.minWheelDC[i]);
//            }
        }
        else {
            pwmSetDCfrac(i+1, 0);
        }
    }

//    leftPID.controlReference = SetPoint.Speed[0];
//    leftPID.measuredOutput = 12 * robotVar.wheelSpeed[0];   // Normalizando: 32767 / 2600
//    PID(&leftPID);
//    pwmSetDCfrac(1, leftPID.controlOutput);
}


void ctrlSetSpeed(PIDindex iPID, fractional speed) {
    if(speed != ctrlPID[iPID].controlReference) {
        if(speed > Limits.maxWheelSpeed) {       // Check overflow
            speed = Limits.maxWheelSpeed;
        }
        else if(speed < -Limits.maxWheelSpeed) { // Check underflow
            speed = -Limits.maxWheelSpeed;
        }

        SetPoint.Speed[iPID] = 12 * speed;         // Normalizando: 32767 / 2600

        if(ctrlFlag.useAccelRamp == 1) {             // Ramp path
            ctrlSetAccelRamp(iPID);
        }
    }
}


void ctrlSetAccelRamp(PIDindex iPID) {
    if( ctrlPID[iPID].controlReference >= 0 && SetPoint.Speed[iPID] > ctrlPID[iPID].controlReference ) {
        SetPoint.Accel[iPID] = Limits.Acceleration;
        ctrlFlag.speedDirection[iPID] = 1;
    }
    else if(ctrlPID[iPID].controlReference >= 0 && SetPoint.Speed[iPID] < ctrlPID[iPID].controlReference) {
        SetPoint.Accel[iPID] = -Limits.Deceleration;
        ctrlFlag.speedDirection[iPID] = 0;
    }
    else if(ctrlPID[iPID].controlReference < 0 && SetPoint.Speed[iPID] > ctrlPID[iPID].controlReference) {
        SetPoint.Accel[iPID] = Limits.Deceleration;
        ctrlFlag.speedDirection[iPID] = 1;
    }
    else if(ctrlPID[iPID].controlReference < 0 && SetPoint.Speed[iPID] < ctrlPID[iPID].controlReference) {
        SetPoint.Accel[iPID] = -Limits.Acceleration;
        ctrlFlag.speedDirection[iPID] = 0;
    }

    ctrlFlag.accelRamp[iPID] = 1;
}


void ctrlComputeAccelRamp(PIDindex iPID) {
    if(ctrlFlag.accelRamp[iPID] == 1) {
        ctrlPID[iPID].controlReference += SetPoint.Accel[iPID];
        if(ctrlFlag.speedDirection[iPID] == 1 && ctrlPID[iPID].controlReference >= SetPoint.Speed[iPID]) {
            ctrlPID[iPID].controlReference = SetPoint.Speed[iPID];
            ctrlFlag.accelRamp[iPID] = 0;
        }
        else if(ctrlPID[iPID].controlReference <= SetPoint.Speed[iPID]) {
            ctrlPID[iPID].controlReference = SetPoint.Speed[iPID];
            ctrlFlag.accelRamp[iPID] = 0;
        }
    }
}



/* Orientation control ********************************************************/
void ctrlComputeDistanceControl() {
    if(ctrlFlag.computeDistanceControl == 1) {
        uint16_t error;
        uint16_t errorTreshHold;
        fractional tmpDistance;
        fractional norm = 0x7FFF / Limits.minDistance;

        error = robot.pose.distance - SetPoint.Distance;
        errorTreshHold = SetPoint.Distance - Limits.minDistance;
        if(robot.pose.distance < errorTreshHold){

            Limits.regulatedSpeed = 1;
        }
        else {
            ctrlPID[pidDistance].controlReference = 0;
            ctrlPID[pidDistance].measuredOutput = Q15(error / Limits.minDistance);     // Normilizing
            PID(&ctrlPID[pidDistance]);

            tmpDistance = ctrlPID[pidDistance].controlOutput;
            if(tmpDistance != 0){
                Limits.regulatedSpeed = 0x7FFF / tmpDistance;       // Normalizing
            }
            else {
                ctrlSetSpeed(pidLeft, 0);
                ctrlSetSpeed(pidRight, 0);
                ctrlFlag.computeDistanceControl = 0;
            }
        }


//        error = SetPoint.Distance - robot.pose.distance;
//        if(error < Limits.minDistance){
//            ctrlPID[pidDistance].controlReference = SetPoint.Distance;
//            ctrlPID[pidDistance].measuredOutput = robot.pose.distance;     // Normilizing
//            PID(&ctrlPID[pidDistance]);
//
//            tmpDistance = ctrlPID[pidDistance].controlOutput;
//            if(tmpDistance != 0){
//                Limits.regulatedSpeed = 0x7FFF / tmpDistance;       // Normalizing
//            }
//            else {
//                robot.pose.distance = 0;
//                ctrlSetSpeed(pidLeft, 0);
//                ctrlSetSpeed(pidRight, 0);
//                ctrlFlag.computeDistanceControl = 0;
//            }
//        }
//        else {
//            Limits.regulatedSpeed = 1;
//        }
    }
}


void ctrlSetDistance(fractional distance) {
    SetPoint.Distance = distance;
}


/* Orientation control ********************************************************/
void ctrlComputeOrientationControl() {
    if(ctrlFlag.computeAngle == 1) {
        fractional speed = 0;
        fractional error = 0;
        fractional tmpSpeed = 0;
        fractional newWheelSpeed[] = {0,0};
        fractional norm = 0;

        ctrlFlag.computeOrientationControl = 0;

        error = robot.pose.theta - SetPoint.Angle;

        ctrlPID[pidOrientation].controlReference = 0;
        ctrlPID[pidOrientation].measuredOutput = error;
        PID(&ctrlPID[pidOrientation]);
        tmpSpeed = ctrlPID[pidOrientation].controlOutput;

        if(ctrlFlag.computeDistanceControl == 1) {
            tmpSpeed = tmpSpeed >> 7;                                   //
            if (Limits.regulatedSpeed != 0) {
                speed = Limits.maxWheelFFSpeed / Limits.regulatedSpeed;
            }
            else {
                speed = 0;
            }
            newWheelSpeed[L] = speed - tmpSpeed;
            newWheelSpeed[R] = speed + tmpSpeed;

        }
        else {
            if(error <= Limits.minAngle) {
                newWheelSpeed[L] = 0;
                newWheelSpeed[R] = 0;
                ctrlPID[pidOrientation].measuredOutput = ctrlPID[pidOrientation].controlReference;
                ctrlFlag.computeAngle = 0;
            }
            else {
                tmpSpeed = tmpSpeed >> 1;
                norm = 0x3FFF / tmpSpeed;
                speed = Limits.maxWheelRotSpeed;
                newWheelSpeed[L] = -(speed / norm);
                newWheelSpeed[R] =  (speed / norm);
            }
        }

        ctrlSetSpeed(pidLeft, newWheelSpeed[L]);
        ctrlSetSpeed(pidRight, newWheelSpeed[R]);
    }
}


void ctrlSetAngle(fractional angle) {
    if(angle >= 0xBFFF && angle <= 0x3FFF) {    // angle: [-0.5,0.5] fractional
        SetPoint.Angle = angle;                 // angle*pi radians
    }
}


/* Auxiliary funtions *********************************************************/
void ctrlGetSetPoint(PIDindex iPID, uint16_t* dataOut) {
    *dataOut = ctrlPID[iPID].controlReference;
//    *dataOut = leftPID.controlReference;
}


void ctrlGetMeasuredOutput(PIDindex iPID, uint16_t* dataOut) {
    *dataOut = ctrlPID[iPID].measuredOutput;
//    *dataOut = leftPID.measuredOutput;
}


void ctrlGetControlOutput(PIDindex iPID, uint16_t* dataOut) {
     *dataOut = ctrlPID[iPID].controlOutput;
//    *dataOut = leftPID.controlOutput;
}