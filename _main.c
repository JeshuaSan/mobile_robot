
#include "include/all.h"
#include "CmdParser.h"
#include "flowcontrol.h"
#include "process.h"
#include "robot.h"
#include "control.h"


int16_t main(void) {
    configBasic(HELLO_MSG);

    confPeripherals();
    confInit();

    void (*modeProcess[])() = {DUMMY, ProcessAuto, ProcessManual, ProcessCharact, ProcessTune};
    uint8_t currentMode = fcGetModeState();

    /* Infinite loop*/
     while (1) {
        if(isCharReady1()) {
            cpFillBuffer();
        }

        if(cpGetBufferState()) {
            cpParseMessage();
        }

        if(fcGetModeChange()) {
            fcChangeMode();
            currentMode = fcGetModeState();
        }

        modeProcess[currentMode]();

        doHeartbeat();

        NOP();

      } // end while (1)
}   // end main

