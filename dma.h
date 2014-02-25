/* 
 * File:   dma.h
 * Author: Jesus
 *
 * Created on April 8, 2013, 4:29 PM
 */

#ifndef DMA_H
#define	DMA_H
typedef enum{
    IRQ_INT0    = 0b0000000,    // External Interrupt 0 (INT0)
    IRQ_IC1     = 0b0000001,    // Input Capture 1 (IC1)
    IRQ_OC1     = 0b0000010,    // Output Compare 1 (OC1)
    IRQ_IC2     = 0b0000101,    // Input Capture 2 (IC2)
    IRQ_OC2     = 0b0000110,    // Output Compare 2 (OC2)
    IRQ_TMR2    = 0b0000111,    // Timer2 (TMR2)
    IRQ_TMR3    = 0b0001000,    // Timer3 (TMR3)
    IRQ_SPI1    = 0b0001010,    // Transfer Done (SPI1)
    IRQ_UART1RX = 0b0001011,    // UART1 Receiver (UART1RX)
    IRQ_UART1TX = 0b0001100,    // UART1 Transmitter (UART1TX)
    IRQ_ADC1    = 0b0001101,    // ADC1 Convert Done (ADC1)
    IRQ_UART2RX = 0b0011110,    // UART2 Receiver (UART2RX)
    IRQ_UART2TX = 0b0011111,    // UART2 Transmitter (UART2TX)
    IRQ_SPI2    = 0b0100001,    // SPI2 Transfer Done (SPI2)
    IRQ_ECAN1RX = 0b0100010,    // RX Data Ready (ECAN1)
    IRQ_PMP     = 0b0101101,    // PMP Master Data Transfer (PMP)
    IRQ_DC1     = 0b0111100,    // CODEC Transfer Done (DCI)
    IRQ_ECAN1TX = 0b1000110,    // TX Data Request (ECAN1)
    IRQ_DAC1L   = 0b1001110,    // DAC1 Right Data Output (DAC1)
    IRQ_DAC1R   = 0b1001111     // DAC1 Left Data Output (DAC1)
}IRQs;


void ConfigDMA0();

#endif	/* DMA_H */

