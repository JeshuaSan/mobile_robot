#include "config_all.h"
#include "flowcontrol.h"
#include "robot.h"

void confPeripherals() {
    qei1Config();       // Right Encoder
    qei2Config();       // Left Encoder
    ic1Config();        // Left wheel speed
    ic2Config();        // Right wheel speed
    timer1Config();     // 10 ms period
    timer2Config();     // IC module period
    pwmConfig();        // MCPWM
    adcConfig();        // Current
    dma0Config();       // ADC samples
    ctrlConfigPID();    // PID control
}

void confInit() {
    adcOFF();
    confInitISRFlags();
    confInitISRVars();
    confInitRobotVars();
}


void confInitISRFlags() {
    isrFlag.tPeriod = 0;
    isrFlag.tPeriod_x2 = 0;
    isrFlag.tPeriod_x4 = 0;
}

void confInitISRVars() {
    isrVar.timePeriod_x2 = 0;
    isrVar.timePeriod_x4 = 0;
    isrVar.icPeriod[L] = 0;
    isrVar.icPeriod[R] = 0;
}

void confInitRobotVars() {
    robotVar.wheelPositionM[L] = 0;
    robotVar.wheelPositionM[R] = 0;
    robotVar.wheelPositionCM[L] = 0;
    robotVar.wheelPositionCM[R] = 0;
    robotVar.wheelPulses[L] = 0;
    robotVar.wheelPulses[R] = 0;
    robotVar.wheelSpeed[L] = 0;
    robotVar.wheelSpeed[R] = 0;
    robotVar.motorCurrent[L] = 0;
    robotVar.motorCurrent[R] = 0;
}