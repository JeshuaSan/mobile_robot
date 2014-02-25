/*
 * File:   interrupts.h
 * Author: Jesus
 *
 * Created on April 1, 2013, 11:23 AM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include "include/chip.h"
#include "include/ports.h"
#include <stdint.h>

enum{
    CLEAR,  // 0 = Interrupt request has not occurred
    SET     // 1 = Interrupt request has occurred
};

///
/// IFS0: INTERRUPT FLAG STATUS REGISTER 0
///

// DMA1IF: DMA Channel 1 Data Transfer Complete Interrupt Flag Status bit
typedef struct tagDMA1IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}DMA1IF;
static DMA1IF DMA1IFconfig = {CLEAR,SET};

void DMA1IFclearFlag();
void DMA1IFsetFlag();
uint8_t DMA1IFgetFlag();

// AD1IF: ADC1 Conversion Complete Interrupt Flag Status bit
typedef struct tagAD1IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}AD1IF;
static AD1IF AD1IFconfig = {CLEAR,SET};

void AD1IFclearFlag();
void AD1IFsetFlag();
uint8_t AD1IFgetFlag();

// U1TXIF: UART1 Transmitter Interrupt Flag Status bit
typedef struct tagU1TXIF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}U1TXIF;
static U1TXIF U1TXIFconfig = {CLEAR,SET};

void U1TXIFclearFlag( );
void U1TXIFsetFlag( );
uint8_t U1TXIFgetFlag();

// U1RXIF: UART1 Receiver Interrupt Flag Status bit
typedef struct tagU1RXIF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}U1RXIF;
static U1RXIF U1RXIFconfig = {CLEAR,SET};

void U1RXIFclearFlag( );
void U1RXIFsetFlag( );
uint8_t U1RXIFgetFlag();

// SPI1IF: SPI1 Event Interrupt Flag Status bit
typedef struct tagSPI1IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}SPI1IF;
static SPI1IF SPI1IFconfig = {CLEAR,SET};

void SPI1IFclearFlag( );
void SPI1IFsetFlag( );
uint8_t SPI1IFgetFlag();

// SPI1EIF: SPI1 Error Interrupt Flag Status bit
typedef struct tagSPI1EIF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}SPI1EIF;
static SPI1EIF SPI1EIFconfig = {CLEAR,SET};

void SPI1EIFclearFlag();
void SPI1EIFsetFlag();
uint8_t SPI1EIFgetFlag();

// T3IF: Timer3 Interrupt Flag Status bit
typedef struct tagT3IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}T3IF;
static T3IF T3IFconfig = {CLEAR,SET};

void T3IFclearFlag();
void T3IFsetFlag();
uint8_t T3IFgetFlag();

// T2IF: Timer2 Interrupt Flag Status bit
typedef struct tagT2IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}T2IF;
static T2IF T2IFconfig = {CLEAR,SET};

void T2IFclearFlag();
void T2IFsetFlag();
uint8_t T2IFgetFlag();

// OC2IF: Output Compare Channel 2 Interrupt Flag Status bit
typedef struct tagOC2IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}OC2IF;
static OC2IF OC2IFconfig = {CLEAR,SET};

void OC2IFclearFlag();
void OC2IFsetFlag();
uint8_t OC2IFgetFlag();

// IC2IF: Input Capture Channel 2 Interrupt Flag Status bit
typedef struct tagIC2IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}IC2IF;
static IC2IF IC2IFconfig = {CLEAR,SET};

void IC2IFclearFlag();
void IC2IFsetFlag();
uint8_t IC2IFgetFlag();

// DMA0IF: DMA Channel 0 Data Transfer Complete Interrupt Flag Status bit
typedef struct tagDMA0IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}DMA0IF;
static DMA0IF DMA0IFconfig = {CLEAR,SET};

void DMA0IFclearFlag( );
void DMA0IFsetFlag( );
uint8_t DMA0IFgetFlag();

// T1IF: Timer1 Interrupt Flag Status bit
typedef struct tagT1IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}T1IF;
static T1IF T1IFconfig = {CLEAR,SET};

void T1IFclearFlag();
void T1IFsetFlag();
uint8_t T1IFgetFlag();

// OC1IF: Output Compare Channel 1 Interrupt Flag Status bit
typedef struct tagOC1IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}OC1IF;
static OC1IF OC1IFconfig = {CLEAR,SET};

void OC1IFclearFlag();
void OC1IFsetFlag();
uint8_t OC1IFgetFlag();

// IC1IF: Input Capture Channel 1 Interrupt Flag Status bit
typedef struct tagIC1IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}IC1IF;
static IC1IF IC1IFconfig = {CLEAR,SET};

void IC1IFclearFlag();
void IC1IFsetFlag();
uint8_t IC1IFgetFlag();

// INT0IF: External Interrupt 0 Flag Status bit
typedef struct tagINT0IF{
    unsigned CLEAR  :1;
    unsigned SET    :1;
}INT0IF;
static INT0IF INT0IFconfig = {CLEAR,SET};

void INT0IFclearFlag( );
void INT0IFsetFlag( );
uint8_t IC1IFgetFlag();

///
///  IFS1: INTERRUPT FLAG STATUS REGISTER 1
///


///
/// IEC0: INTERRUPT ENABLE CONTROL REGISTER 0
///

typedef enum IEC0Values{
    IEC0_DISABLED,    // 0 = Interrupt request not enabled
    IEC0_ENABLED         // 1 = Interrupt request enabled
}IEC0Values;

// DMA1IE: DMA Channel 1 Data Transfer Complete Interrupt Enable bit
typedef struct tagDMA1IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}DMA1IE;
static DMA1IE DMA1IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void DMA1IEdisable();
void DMA1IEenable();

// AD1IE: ADC1 Conversion Complete Interrupt Enable bit
typedef struct tagAD1IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}AD1IE;
static AD1IE AD1IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void AD1IEdisable();
void AD1IEenable();


// U1TXIE: UART1 Transmitter Interrupt Enable bit
typedef struct tagU1TXIE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}U1TXIE;
static U1TXIE U1TXIEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void U1TXIEdisable();
void U1TXIEenable();


// U1RXIE: UART1 Receiver Interrupt Enable bit
typedef struct tagU1RXIE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}U1RXIE;
static U1RXIE U1RXIEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void U1RXIEdisable();
void U1RXIEenable();

// SPI1IE: SPI1 Event Interrupt Enable bit
typedef struct tagSPI1IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}SPI1IE;
static SPI1IE SPI1IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void SPI1IEdisable();
void SPI1IEenable();

// SPI1EIE: SPI1 Error Interrupt Enable bit
typedef struct tagSPI1EIE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}SPI1EIE;
static SPI1EIE SPI1EIEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void SPI1EIEdisable();
void SPI1EIEenable();

// T3IE: Timer3 Interrupt Enable bit
typedef struct tagT3IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}T3IE;
static T3IE T3IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void T3IEdisable();
void T3IEenable();

// T2IE: Timer2 Interrupt Enable bit
typedef struct tagT2IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}T2IE;
static T2IE T2IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void T2IEdisable();
void T2IEenable();

// OC2IE: Output Compare Channel 2 Interrupt Enable bit
typedef struct tagOC2IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}OC2IE;
static OC2IE OC2IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void OC2IEdisable();
void OC2IEenable();

// IC2IE: Input Capture Channel 2 Interrupt Enable bit
typedef struct tagIC2IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}IC2IE;
static IC2IE IC2IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void IC2IEdisable();
void IC2IEenable();

// DMA0IE: DMA Channel 0 Data Transfer Complete Interrupt Enable bit
typedef struct tagDMA0IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}DMA0IE;
static DMA0IE DMA0IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void DMA0IEdisable();
void DMA0IEenable();

// T1IE: Timer1 Interrupt Enable bit
typedef struct tagT1IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}T1IE;
static T1IE T1IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void T1IEdisable();
void T1IEenable();

// OC1IE: Output Compare Channel 1 Interrupt Enable bit
typedef struct tagOC1IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}OC1IE;
static OC1IE OC1IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void OC1IEdisable();
void OC1IEenable();

// IC1IE: Input Capture Channel 1 Interrupt Enable bit
typedef struct tagIC1IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}IC1IE;
static IC1IE IC1IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void IC1IEdisable();
void IC1IEenable();

// INT0IE: External Interrupt 0 Flag Status bit
typedef struct tagINT0IE{
    IEC0Values IEC0_DISABLED :1;
    IEC0Values IEC0_ENABLED  :1;
}INT0IE;
static INT0IE INT0IEconfig = {IEC0_DISABLED,IEC0_ENABLED};

void INT0IEdisable();
void INT0IEenable();


///
/// IPC0: INTERRUPT PRIORITY CONTROL REGISTER 0
///



#endif	/* INTERRUPTS_H */

