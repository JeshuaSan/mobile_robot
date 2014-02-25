 #include "ic.h"
#include "interrupts.h"
#include "include/chip.h"
#include "flowcontrol.h"

#include "ic.h"
#include "interrupts.h"


void ic1Config(){
    // Pin configuration
    CONFIG_RB2_AS_DIG_INPUT();
    CONFIG_IC1_TO_RP(2);

    // IC2CON: Input Capture 2 Control Register
    IC1CONbits.ICM = ICMconfig.MODULE_OFF;
    IC1CONbits.ICTMR = ICTMRconfig.USE_TMR2;
    IC1CONbits.ICI = ICIconfig.EVERY_SECOND_CAPTURE;
    IC1CONbits.ICM = ICMconfig.EVERY_RISING_EDGE;

    // Interrupt registers
    IPC0bits.IC1IP = 4; // Priority
    IC1IFclearFlag();   // Clear Interrupt flag
    IC1IEenable();      // Enable interrupt

}

void ic2Config(){
    // Pin configuration
    CONFIG_RB4_AS_DIG_INPUT();
    CONFIG_IC2_TO_RP(4);

    IC2CONbits.ICM = ICMconfig.MODULE_OFF;
    IC2CONbits.ICTMR = ICTMRconfig.USE_TMR2;
    IC2CONbits.ICI = ICIconfig.EVERY_SECOND_CAPTURE;
    IC2CONbits.ICM = ICMconfig.EVERY_RISING_EDGE;

    // Interrupt registers
    IPC1bits.IC2IP = 4; // Priority
    IC2IFclearFlag();   // Clear Interrupt flag
    IC2IEenable();      // Enable interrupt
}


void _ISRFAST _IC1Interrupt() {
    uint16_t tempPeriod[2];
    tempPeriod[0] = IC1BUF;
    tempPeriod[1] = IC1BUF;

    IC1IFclearFlag();

    if(tempPeriod[1] > tempPeriod[0]) {
        isrVar.icPeriod[L] = tempPeriod[1] - tempPeriod[0];
    }
    else {
        isrVar.icPeriod[L] = (PR2 - tempPeriod[0]) + tempPeriod[1];
    }
}

void _ISRFAST _IC2Interrupt() {
    uint16_t tempPeriod[2];
    tempPeriod[0] = IC2BUF;
    tempPeriod[1] = IC2BUF;

    IC2IFclearFlag();

    if(tempPeriod[1] > tempPeriod[0]) {
        isrVar.icPeriod[R] = tempPeriod[1] - tempPeriod[0];
    }
    else {
        isrVar.icPeriod[R] = (PR2 - tempPeriod[0]) + tempPeriod[1];
    }
}
