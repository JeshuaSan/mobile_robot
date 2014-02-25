#include "timers.h"
#include "interrupts.h"
#include "flowcontrol.h"

//#define TMR1_PERIOD      10 // [ms]: Timer1 period overflow
#define TMR1_PERIOD_X2   2  // [ms]: (20ms) Timer1 x 2
#define TMR1_PERIOD_X4   2  // [ms]: (40ms) Timer1 x 4

// 10 ms period
void timer1Config() {
     T1CONbits.TON = TONconfig.TRM_OFF;
     T1CONbits.TSIDL = TSIDLconfig.TRM_CONTINUE_ON_IDLE;
     T1CONbits.TGATE = TGATEconfig.TRM_GATE_OFF;
     T1CONbits.TSYNC = TSYNCconfig.TRM1_SYNC_OFF;
     T1CONbits.TCS = TCSconfig.TRM_CLK_INTERNAL;
     T1CONbits.TCKPS = TCKPSconfig.TRM_PS_256;

     PR1 = 1560;        // 10 ms
     TMR1  = 0;         // clear timer2 value
     T1IFclearFlag();   // clear interrupt flag
     T1IEenable();      // Enable interrupts

     T1CONbits.TON = TONconfig.TRM_ON;

}

// IC data period
void timer2Config() {
     T2CONbits.TON = TONconfig.TRM_OFF;
     T2CONbits.TSIDL = TSIDLconfig.TRM_CONTINUE_ON_IDLE;
     T2CONbits.TGATE = TGATEconfig.TRM_GATE_OFF;
     T2CONbits.T32 = T32config.TRM2_16_BIT;
     T2CONbits.TCS = TCSconfig.TRM_CLK_INTERNAL;
     T2CONbits.TCKPS = TCKPSconfig.TRM_PS_256;

     PR2 = 0xFFFF;      // maximum period
     TMR2  = 0;         // clear timer2 value
     T2IFclearFlag();   // clear interrupt flag


     T2CONbits.TON = TONconfig.TRM_ON;
}

// ADC sample period (when activated)
void timer3Config() {
    TMR3 = 0x0000;
    PR3  = 4999;        // Trigger ADC1 every 125usec
    IFS0bits.T3IF = 0;  // Clear Timer 3 interrupt
    IEC0bits.T3IE = 0;  // Disable Timer 3 interrupt
    T3CONbits.TON = 0;  // Start Timer 3
}


void _ISRFAST _T1Interrupt() {
    isrFlag.tmr1overflow = 1;
    isrFlag.tPeriod = 1;            // 10ms

    isrVar.timePeriod_x2++;
    if (isrVar.timePeriod_x2 >= TMR1_PERIOD_X2) {
        isrVar.timePeriod_x2 = 0;
        isrFlag.tPeriod_x2 = 1;     // 20ms

        isrVar.timePeriod_x4++;
        if(isrVar.timePeriod_x4 >= TMR1_PERIOD_X4) {
            isrVar.timePeriod_x4 = 0;
            isrFlag.tPeriod_x4 = 1; // 40ms
        }
    }

    T1IFclearFlag();            // Clear TMR1 Interrupt flag
}

void _ISRFAST _T2Interrupt() {
    isrFlag.tmr2overflow = 1;
    T2IFclearFlag();
}