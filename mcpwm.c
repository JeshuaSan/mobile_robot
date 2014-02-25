#include "mcpwm.h"
#include "include/clockfreq.h"

void pwmConfig(void) {

    CONFIG_RB15_AS_DIG_OUTPUT();
    CONFIG_RB14_AS_DIG_OUTPUT();
    CONFIG_RB13_AS_DIG_OUTPUT();
    CONFIG_RB12_AS_DIG_OUTPUT();

    // PxTCON: PWM Time Base Control Register
    P1TCONbits.PTEN = 0;    // 1 = PWM time base is on
    P1TCONbits.PTSIDL = 0;  // 0 = PWM time base runs in CPU Idle mode
    P1TCONbits.PTOPS = 0;   // 0000 = 1:1 postscale
    P1TCONbits.PTCKPS = 0;  // 00 = PWM time base input clock period is TCY (1:1 prescale)
    P1TCONbits.PTMOD = 0;   // 00 = PWM time base operates in Free Running mode

    // PxTPER: PWM Time Base Period Register
//    P1TPERbits.PTPER = 2047;    // 19.5 KHz Frequency => PxTPER = FCY/(Fpwm * PxTMRPS)
    pwmSetFreq(15000);

    // PWMxCON1: PWM Control Register 1
    PWM1CON1bits.PMOD1 = 0; // 0 = PWM I/O pin pair is in the Complementary Output mode
    PWM1CON1bits.PMOD2 = 0; // 0 = PWM I/O pin pair is in the Complementary Output mode
    PWM1CON1bits.PEN1L = 1; // 1 = PWM1L1 pin is enabled for PWM output [RB15]
    PWM1CON1bits.PEN1H = 1; // 1 = PWM1H1 pin is enabled for PWM output [RB14]
    PWM1CON1bits.PEN2L = 1; // 1 = PWM1L2 pin is enabled for PWM output [RB13]
    PWM1CON1bits.PEN2H = 1; // 1 = PWM1H2 pin is enabled for PWM output [RB12]
    PWM1CON1bits.PEN3L = 0; // 0 = PWM1L3 pin disabled; I/O pin becomes general purpose I/O  [RB11:PGEC2]
    PWM1CON1bits.PEN3H = 0; // 0 = PWM1H3 pin disabled; I/O pin becomes general purpose I/O  [RB10:PGED2]

    PWM2CON1bits.PEN1L = 0; // 0 = PWM2L1 pin disabled; I/O pin becomes general purpose I/O  [RB9]
    PWM2CON1bits.PEN1H = 0; // 0 = PWM2H1 pin disabled; I/O pin becomes general purpose I/O  [RB8]

    // PWMxCON2: PWM Control Register 2
    PWM1CON2bits.SEVOPS = 0;    // 0000 = 1:1 postscale
    PWM1CON2bits.IUE = 1;       // 1 = Updates to the active PxDCy(1,2) registers are immediate
    PWM1CON2bits.OSYNC = 1;     // 1 = Output overrides via the PxOVDCON(1) register are synchronized to the PWM time base

    // PxDTCON1: Dead Time Control Register 1
    P1DTCON1bits.DTAPS = 0; // 00 = Clock period for Dead Time Unit A is TCY
    P1DTCON1bits.DTA = 4;   // Dead time: 100ns

    // DutyCycle = 50% = STOP
//    pwmSetDC(1, 2047, 0);
//    pwmSetDC(2, 2047, 0);
//    pwmSetDCfrac(1,0);
//    pwmSetDCfrac(2,0);

    P1TCONbits.PTEN = 1;    // 1 = PWM time base is on

}

// Taken from SetDutyCycleMCPWM1.c
void pwmSetDC(uint16_t dutycycleReg, uint16_t dutycycle, uint8_t updatedisable) {
    PWM1CON2bits.UDIS = updatedisable & 0x1;

    /* Assign dutycycle to the duty cycle register */
    *(&P1DC1 + dutycycleReg - 1) = dutycycle;
}


void pwmSetFreq(uint16_t frequency) {
    // PxTPER = (FCY/(Fpwm * PxTMRPS)) - 1
    uint8_t pwmPTCKPS[] = {0,2,4,6};
    uint8_t pwmTMRPS = pwmPTCKPS[P1TCONbits.PTCKPS];

    uint32_t pwmFreq = (uint32_t)frequency << pwmTMRPS; // Freq * PxTMRPS
    uint16_t ptper = (FCY/pwmFreq) - 1;                 // (FCY/Fpwm)-1

    P1TPERbits.PTPER = ptper;
    pwmSetDC(1, ptper, 0);
    pwmSetDC(2, ptper, 0);
}


void pwmSetDCpc(uint16_t dutycycleReg, uint16_t dutycyclePercentage) {
    uint16_t maxDutyCycle = (P1TPER << 1) + 1;
    uint32_t dutycycle = ((uint32_t)maxDutyCycle * (uint32_t)dutycyclePercentage) / 100;
    pwmSetDC(dutycycleReg, dutycycle, 0);
}


void pwmSetDCfrac(uint16_t dutycycleReg, uint16_t dutycycleFracc) {
    uint16_t maxDutyCycle = (P1TPER << 1) + 1;
    uint32_t dutycycle = ((uint32_t)maxDutyCycle * (uint32_t)(dutycycleFracc + 0x8000)) >> 16;
    pwmSetDC(dutycycleReg, dutycycle, 0);
}