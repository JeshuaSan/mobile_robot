#include "flowcontrol.h"
#include "adc.h"
#include "control.h"


// Global varaibles
Wheel wheel = {L,R};

// ISR variables
volatile ISRFlag isrFlag;
volatile ISRVar isrVar;

// Local variables
typedef struct tagMode {
    ModeState currenMode;
    ModeState newMode;
    Status status;
}Mode;

Mode fcMode = {
    .status = NO_CHANGE,
    .currenMode = MODE_AUTO,
    .newMode = MODE_AUTO
};

void (*setNewMode[])() = {DUMMY, fcSetAuto, fcSetManual, fcSetCharact, fcSetTune};

void fcChangeMode() {

//    switch(newState){
//        case Auto: {
//            adcOFF();
//            break;
//        }
//
//        case Manual: {
//            adcOFF();
//            break;
//        }
//
//        case Charact: {
//            adcON();
//            break;
//        }
//
//        case Config: {
//            adcOFF();
//            break;
//        }
//
//        default: break;
//    }
    
    setNewMode[fcMode.newMode]();

    fcMode.currenMode = fcMode.newMode;
    fcMode.status = NO_CHANGE;
}

void fcSetAuto() {
    pwmSetDCfrac(1, 0);
    pwmSetDCfrac(2, 0);
    adcOFF();
}


void fcSetManual() {
    pwmSetDCfrac(1, 0);
    pwmSetDCfrac(2, 0);
    adcOFF();

}


void fcSetCharact() {
    pwmSetDCfrac(1, 0);
    pwmSetDCfrac(2, 0);
    adcON();
}


void fcSetTune() {
    adcON();
    ctrlSetSpeed(pidLeft, 0);
    ctrlSetSpeed(pidRight, 0);
}


ModeState fcGetModeState() {
    return fcMode.currenMode;
}


Status fcGetModeChange() {
    return fcMode.status;
}


void fcSetNewModeState(ModeState newMode) {
    fcMode.newMode = newMode;
    fcMode.status = CHANGE;
}