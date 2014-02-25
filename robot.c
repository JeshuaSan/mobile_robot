#include "robot.h"
#include <libq.h>
#include <dsp.h>

RobotVars robotVar; // Global robot variables

#define TMR_FREQ    156006          // [hz]: TMR2 frequency = 1/0.00000641 s
#define W_MIN       3
#define V_MIN       3

// Variables
const int8_t speedSign[] = {-1, 1};
uint8_t qeiUPDN[2];

fractional prevSin = 0;             // to hold previous sine value
fractional prevCos = 1;             // to hold previous cosine value

Robot robot = {
    // Physiscal dimensions
    .dimension.axle = 30,            // [cm]
    // Pose vector
    .pose.theta = 0,                // [rad]
    .pose.x = 0,                    // [cm]
    .pose.y = 0,                    // [cm]
    .pose.distance = 0,             // [cm] Toral distance traveled
    // Constants
    .params.pulses2cm = {112,112},  // Pulses needed to travel 1cm (qei_x2)
    .params.maxFFSpeed = 25,        // [] Max forwards speed
    .params.maxRotSpeed = 10        // [] Max rotational speed
};

// Functions
void (*rComputeWheelPosition[])(RWheel wheel, uint16_t* result) = {rDespPulses, rDespWheelCM, rDespWheelP};


void rComputeWheelSpeed(RWheel wheel) {

    int32_t tempPeriod = 0;

    tempPeriod = isrVar.icPeriod[wheel];

    isrVar.icPeriod[wheel] = 0;
    robotVar.wheelSpeed[wheel] = 0;

    qeiUPDN[0] = QEI1CONbits.UPDN;
    qeiUPDN[1] = QEI2CONbits.UPDN;
    
    // Avoid divide by zero
    if(tempPeriod != 0) {
        robotVar.wheelSpeed[wheel] = speedSign[qeiUPDN[wheel]] * (TMR_FREQ / tempPeriod);
    }
    else {
        robotVar.wheelSpeed[wheel] = 0;
    }
}


void rComputeWheelPulses(RWheel wheel) {
    switch(wheel) {
        case L:
            robotVar.wheelPulses[wheel] += POS1CNT;
            robotVar.wheelPositionP[wheel] += POS1CNT;
            POS1CNT = 0;
            break;

        case R:
            robotVar.wheelPulses[wheel] += POS2CNT;
            robotVar.wheelPositionP[wheel] += POS2CNT;
            POS2CNT = 0;
            break;

        default: break;
    }


    if (robotVar.wheelPositionP[wheel] > 0 && robotVar.wheelPositionP[wheel] >= robot.params.pulses2cm[wheel]) {
        robotVar.wheelPositionCM[wheel]++;
        robotVar.wheelPositionP[wheel] = 0;
    }
    else if(robotVar.wheelPositionP[wheel] < 0 && robotVar.wheelPositionP[wheel] <= -robot.params.pulses2cm[wheel]) {
        robotVar.wheelPositionCM[wheel]--;
        robotVar.wheelPositionP[wheel] = 0;
    }
}


void rGetWheelPosition(RWheel wheel, uint8_t mode, uint16_t* result) {
    rComputeWheelPosition[mode](wheel, result);
}


void rDespPulses(RWheel wheel, uint16_t* result) {
    *result =  robotVar.wheelPulses[wheel];
}


void rDespWheelCM(RWheel wheel, uint16_t* result) {
    *result = robotVar.wheelPositionCM[wheel];
    robotVar.wheelPositionCM[wheel] = 0;
}


void rDespWheelP(RWheel wheel, uint16_t* result) {
    *result =  robotVar.wheelPositionP[wheel];
    robotVar.wheelPositionP[wheel] = 0;
}


void rComputeRobotSpeed() {

}


void rComputeRobotPosition() {

}


void rComputeCinematics() {
    int16_t V = 0;;
    int16_t W = 0;
    uint16_t tmpL = 0;
    uint16_t tmpR = 0;
    int16_t tmpX = 0;
    int16_t tmpY = 0;
    uint16_t tmpDist = 0;
    int16_t tmpTheta = 0;
    fractional norm = 8192/robot.dimension.axle;

    rDespWheelCM(L, &tmpL);
    rDespWheelCM(R, &tmpR);

    V = tmpL + tmpR;    // Linear displacement
    W = tmpL - tmpR;    // Angular displacement


    if(abs(W) <= W_MIN ){                // Not turning, compute x,y
        tmpDist = tmpL;
//        tmpX = tmpDist * prevCos;  // v/2 = tempL or tmpR
//        tmpY = tmpDist * prevSin;
        robot.pose.x += tmpDist * prevCos;
        robot.pose.y += tmpDist * prevSin;
    }
    if(abs(V) <= V_MIN){            // Turning, compute theta
//        tmpTheta = W * norm;    // Normalizing W = (vL-vR)/b , b = 0.5 frac
        robot.pose.theta += (W * norm);
//        prevSin = _Q15sinPI(W);
//        prevCos = _Q15cosPI(W);
        prevCos = _Q15cosPI(robot.pose.theta);
        prevSin = _Q15sinPI(robot.pose.theta);
    }
    
//    robot.pose.x += tmpX;
//    robot.pose.y += tmpY;
//    robot.pose.theta += tmpTheta;
    robot.pose.distance += tmpDist;

    
    

//    robot.pose.theta += (W * norm);
//    prevCos = _Q15cosPI(robot.pose.theta);
//    prevSin = _Q15sinPI(robot.pose.theta);
//    robot.pose.distance += tmpDist;

}
