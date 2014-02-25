#include "adc.h"
#include "flowcontrol.h"
#include "robot.h"

void adcConfig() {
    CONFIG_AN0_AS_ANALOG();
    CONFIG_AN1_AS_ANALOG();

    // ADxCON1: ADCx Control Register 1
    AD1CON1bits.ADON = 0;       // 0= ADC is off
    AD1CON1bits.ADSIDL = 0;     // 0 = Continue module operation in Idle mode
    AD1CON1bits.ADDMABM = 0;    // 0 = DMA buffers are written in Scatter/Gather mode. The module provides a Scatter/Gather address to
                                //      the DMA channel, based on the index of the analog input and the size of the DMA buffer
    AD1CON1bits.AD12B = 0;      // 0 = 10-bit, 4-channel ADC operation
    AD1CON1bits.FORM = 0;       // 00 = Integer (DOUT = 0000 00dd dddd dddd)
    AD1CON1bits.SSRC = 7;       // 111 = Internal counter ends sampling and starts conversion (auto-convert)
    AD1CON1bits.SIMSAM = 0;     // 0 = Samples multiple channels individually in sequence
    AD1CON1bits.ASAM = 1;       // 1 = Sampling begins immediately after last conversion. SAMP bit is auto-set

    // ADxCON2: ADCx Control Register 2
    AD1CON2bits.VCFG = 0;       // 000 = VrefH = Avdd, VrefL = Avss
    AD1CON2bits.CSCNA = 1;      // 0 = Do not scan inputs, 1 = Scan inputs for CH0+ during Sample A bit
    AD1CON2bits.CHPS = 0;       // 00 = Converts CH0
    AD1CON2bits.SMPI = 1;       // 0001 = Increments the DMA address after completion of every 2nd sample/conversion operation
    AD1CON2bits.BUFM = 0;       // 0 = Always starts filling the buffer from the start address
    AD1CON2bits.ALTS = 0;       // 0 = Always uses channel input selects for Sample A

    // ADxCON3: ADCx Control Register 3
    AD1CON3bits.ADRC = 1;       // 1 = ADC Internal RC Clock
    AD1CON3bits.SAMC = 0x1F;    // 11111 = 31 TAD
    AD1CON3bits.ADCS = 63;      // 63 = TCY · (ADCS<7:0> + 1) = 1 · TCY = TAD

    // ADxCON4: ADCx Control Register 4
    AD1CON4bits.DMABL = 3;      // 011 = Allocates 8 words of buffer to each analog input

    // ADxCHS0: ADCx Input Channel 0 Select Register
    AD1CHS0bits.CH0NA = 0;      // 0 = Channel 0 negative input is VREFL
    AD1CHS0bits.CH0SA = 0;      // 00000 = Channel 0 positive input is AN0

    // ADxCHS123: ADCx Input Channel 1, 2, 3 Select Register
    AD1CHS123bits.CH123NA = 0;  // 0x = CH1, CH2, CH3 negative input is VREFL
    AD1CHS123bits.CH123SA = 0;  // 0 = CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2

    // ADxCSSL: ADCx Input Scan Select Register Low
    AD1CSSLbits.CSS0 = 1;       // Use AN0
    AD1CSSLbits.CSS1 = 1;       // Use AN1

    // ADxPCFGL: ADCx Port Configuration Register Low
    AD1PCFGLbits.PCFG0 = 0;     // 0 = Port pin in Analog mode, port read input disabled, ADC samples pin voltage
    AD1PCFGLbits.PCFG1 = 0;     // 0 = Port pin in Analog mode, port read input disabled, ADC samples pin voltage

    IFS0bits.AD1IF   = 0;       // Clear the A/D interrupt flag bit
    IEC0bits.AD1IE   = 0;       // Do Not Enable A/D interrupt

}


void adcComputeCurrent(uint8_t wheel, int* adcBuffer) {
    uint8_t ii = 0;
    uint16_t avSample = 0;

    for(ii=0; ii < 8; ii++) {
        avSample += adcBuffer[ii];
    }

    isrVar.adcSample[wheel] = avSample >> 3;
}


void adcGetCurrent() {
//    robotVar.motorCurrent[0] = isrVar.adcSample[0];
//    robotVar.motorCurrent[1] = isrVar.adcSample[1];
    uint8_t i, j;
    uint16_t sumSample[2] = {0,0};

    for(i=0; i<2; i++) {
        for(j=0; j < 8; j++) {
            sumSample[i] += isrVar.adcSampleAdrr[i][j];      // Sum of 8 samples
        }
        robotVar.motorCurrent[i] = sumSample[i] >> 3;        // Average = Sum/8
    }
}


void adcON() {
    AD1CON1bits.ADON = 1;   // Enable ADC
    DMA0CONbits.CHEN = 1;   // Enable DMA
    T3CONbits.TON = 1;      // Enable Timer3
}


void adcOFF() {
    T3CONbits.TON = 0;      // Disable Timer3
    AD1CON1bits.ADON = 0;   // Diable ADC
    DMA0CONbits.CHEN = 0;   // Disable DMA
    robotVar.motorCurrent[0] = 0;
    robotVar.motorCurrent[1] = 0;
}
