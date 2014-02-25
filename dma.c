#include "dma.h"
#include "adc.h"
#include "flowcontrol.h"
#include <stdint.h>

#define SAMP_BUFF_SIZE  8   // Size of the input buffer per analog input
#define NUM_CHS2SCAN    2   // Number of channels enabled for channel scan

// Number of locations for ADC buffer = 2 (AN0 and AN1) x 8 = 16 words
// Align the buffer to 16 words or 32 bytes. This is needed for peripheral indirect mode
int  BufferA[NUM_CHS2SCAN][SAMP_BUFF_SIZE] __attribute__((space(dma),aligned(32)));
int  BufferB[NUM_CHS2SCAN][SAMP_BUFF_SIZE] __attribute__((space(dma),aligned(32)));

uint8_t bufferDMA = 0;

void dma0Config() {
    // DMAXCON: DMA Channel X Control Register
    DMA0CONbits.AMODE = 2;      // 10 = Peripheral Indirect Addressing mode
    DMA0CONbits.MODE = 2;       // 10 = Continuous, Ping-Pong modes enabled

    // DMAXPAD: DMA Channel X Peripheral Address Register
    DMA0PAD = (volatile unsigned int)&ADC1BUF0;   // ADC1

    // DMAXCNT: DMA Channel X Transfer Count Register
    DMA0CNT = (SAMP_BUFF_SIZE*NUM_CHS2SCAN)-1;

    // DMAXREQ: DMA Channel X IRQ Select Register
    DMA0REQ = 13;     // 0001101 = ADC1 Convert Done (ADC1)

    // DMAXSTA: DMA Channel X DPSRAM Start Address Offset Register A
    DMA0STA = __builtin_dmaoffset(BufferA);

    // DMAXSTB: DMA Channel X DPSRAM Start Address Offset Register B
    DMA0STB = __builtin_dmaoffset(BufferB);


    IFS0bits.DMA0IF = 0;    // Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = 1;    // Set the DMA interrupt enable bit

    DMA0CONbits.CHEN = 0;   // Disable DMA
}


void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void) {

    if (bufferDMA == 0) {
//        adcComputeCurrent(0, &BufferA[0][0] );
//        adcComputeCurrent(1, &BufferA[1][0] );
        isrVar.adcSampleAdrr[0] = &BufferA[0][0];   // Store buffer adress for later computation
        isrVar.adcSampleAdrr[1] = &BufferA[1][0];
    }
    else {
//        adcComputeCurrent(0, &BufferB[0][0] );
//        adcComputeCurrent(1, &BufferB[1][0] );
        isrVar.adcSampleAdrr[0] = &BufferB[0][0];
        isrVar.adcSampleAdrr[1] = &BufferB[1][0];
    }

    bufferDMA ^= 1;
    IFS0bits.DMA0IF = 0;    // Clear the DMA0 Interrupt Flag
}
