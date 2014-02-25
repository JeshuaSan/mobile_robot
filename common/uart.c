#include "../include/clockfreq.h"
#include "../include/uart.h"
#include "../include/ports.h"
#include "../include/unittest.h"
#include "../include/delay.h"

// Only include if this UART exists.
#if (NUM_UART_MODS >= 1)


// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_UART_MODS so Doxygen
// will only see it once.
/** \file
*  UART support functions.
*  \par Interrupt-driven TX/RX
*  By default, the UART functions use polling for both RX and TX.
*  Define the macro UARTx_TX_INTERRUPT (i.e., UART1_TX_INTERRUPT) in your project file if you want interrupt-driven TX for the UARTx (i.e., UART1) module.
*  For interrupt-driven TX, macro UARTx_TX_FIFO_SIZE sets the TX software FIFO size (default 32), and UARTx_TX_INTERRUPT_PRIORITY  sets the priority (default 1).
* \par
*  Define the macro UARTx_RX_INTERRUPT (i.e., UART1_RX_INTERRUPT) in your project file if you want interrupt-driven RX for the UARTx (i.e., UART1) module.
*  For interrupt-driven RX, macro UARTx_RX_FIFO_SIZE sets the RX software FIFO size (default 32), and UARTx_RX_INTERRUPT_PRIORITY  sets the priority (default 1).
*/


/*********************************************************
 * Public functions intended to be called by other files *
 *********************************************************/
/**
* Check UART1 RX for error, call \em reportError() if error found.
*
*/
void checkRxErrorUART1(void) {
  uint8_t u8_c;
  //check for errors, reset if detected.
  if (U1STAbits.PERR) {
    u8_c = U1RXREG; //clear error
    reportError("UART1 parity error\n");
  }
  if (U1STAbits.FERR) {
    u8_c = U1RXREG; //clear error
    reportError("UART1 framing error\n");
  }
  if (U1STAbits.OERR) {
    U1STAbits.OERR = 0; //clear error
    reportError("UART1 overrun error\n");
  }
}




#ifdef UART1_TX_INTERRUPT
/**

*/
#ifndef UART1_TX_FIFO_SIZE
#define UART1_TX_FIFO_SIZE 32  //choose a size
#endif

#ifndef UART1_TX_INTERRUPT_PRIORITY
#define UART1_TX_INTERRUPT_PRIORITY 1
#endif

volatile uint8_t au8_txFifo1[UART1_TX_FIFO_SIZE];
volatile uint16_t u16_txFifo1Head = 0;
volatile uint16_t u16_txFifo1Tail = 0;

/**
* Output \em u8_c to UART1 TX.
* \param u8_c Character to write
*/
void outChar1(uint8_t u8_c) {
  uint16_t u16_tmp;

  u16_tmp = u16_txFifo1Head;
  u16_tmp++;
  if (u16_tmp == UART1_TX_FIFO_SIZE) u16_tmp = 0; //wrap if needed
  while (u16_tmp == u16_txFifo1Tail)
    doHeartbeat();

  au8_txFifo1[u16_tmp] = u8_c; //write to buffer
  u16_txFifo1Head = u16_tmp;  //update head
  _U1TXIE = 1;               //enable interrupt
}

void _ISR _U1TXInterrupt (void) {
  if (u16_txFifo1Head == u16_txFifo1Tail) {
    //empty TX buffer, disable the interrupt, do not clear the flag
    _U1TXIE = 0;
  } else {
    //at least one free spot in the TX buffer!
    u16_txFifo1Tail++;   //increment tail pointer
    if (u16_txFifo1Tail == UART1_TX_FIFO_SIZE)
      u16_txFifo1Tail = 0; //wrap if needed
    _U1TXIF = 0; //clear the interrupt flag
    //transfer character from software buffer to transmit buffer
    U1TXREG =  au8_txFifo1[u16_txFifo1Tail];
  }
}


#else
/**
* Output \em u8_c to UART1 TX.
* \param u8_c Character to write
*/
void outChar1(uint8_t u8_c) {
  //wait for transmit buffer to be empty
  while (IS_TRANSMIT_BUFFER_FULL_UART1())
    doHeartbeat();
  U1TXREG = u8_c;
}
#endif

#ifdef UART1_RX_INTERRUPT
//Interrupt driven RX
#ifndef UART1_RX_FIFO_SIZE
#define UART1_RX_FIFO_SIZE 32  //choose a size
#endif

#ifndef UART1_RX_INTERRUPT_PRIORITY
#define UART1_RX_INTERRUPT_PRIORITY 1
#endif

volatile uint8_t au8_rxFifo1[UART1_RX_FIFO_SIZE];
volatile uint16_t u16_rxFifo1Head = 0;
volatile uint16_t u16_rxFifo1Tail = 0;

/**
* Return true if character is ready to be read
*/
uint8_t isCharReady1(void) {
  return(u16_rxFifo1Head != u16_rxFifo1Tail);
}

/**
* Wait for a byte to be available from UART1 RX.
* \return Character read from UART1 RX.
*/
uint8_t inChar1(void) {
  while (u16_rxFifo1Head == u16_rxFifo1Tail)
    doHeartbeat();
  u16_rxFifo1Tail++;
  if (u16_rxFifo1Tail == UART1_RX_FIFO_SIZE) u16_rxFifo1Tail=0; //wrap
  return au8_rxFifo1[u16_rxFifo1Tail]; //return the character
}

void _ISR _U1RXInterrupt (void) {
  int8_t u8_c;

  _U1RXIF = 0;        //clear the UART RX interrupt bit
  checkRxErrorUART1();
  u8_c = U1RXREG;     //read character
  u16_rxFifo1Head++;   //increment head pointer
  if (u16_rxFifo1Head == UART1_RX_FIFO_SIZE)
    u16_rxFifo1Head = 0; //wrap if needed
  if (u16_rxFifo1Head == u16_rxFifo1Tail) {
    //FIFO overrun!, report error
    reportError("UART1 RX Interrupt FIFO overrun!");
  }
  au8_rxFifo1[u16_rxFifo1Head] = u8_c; //place in buffer
}

#else
/**
* Return true if character is ready to be read
*/
uint8_t isCharReady1(void) {
  return(IS_CHAR_READY_UART1());
}

/**
* Wait for a byte to be available from UART1 RX.
* \return Character read from UART1 RX.
*/
uint8_t inChar1(void) {
  //do heartbeat while waiting for character.
  // Use a do-while to insure error checks
  // are always run.
  while (!IS_CHAR_READY_UART1())
  doHeartbeat();
  checkRxErrorUART1();
  return U1RXREG; //read the receive register
}
#endif



/** Chose a default BRGH for UART1, used by
 *  \ref configUART1 to set up UART1.
 */
#ifndef DEFAULT_BRGH1
#define DEFAULT_BRGH1  DEFAULT_BRGH
#endif

#if (DEFAULT_BRGH1 != 0) && (DEFAULT_BRGH1 != 1)
#error Invalid value specified for DEFAULT_BRGH1
#endif


/** Configure the UART. Settings chosen:
 *  - TX is on RP11
 *  - RX is on RP10
 *  - Format is 8 data bits, no parity, 1 stop bit
 *  - CTS, RTS, and BCLK not used
 *
 *  \param u32_baudRate The baud rate to use.
 */
void configUART1(uint32_t u32_baudRate) {
#ifdef _NOFLOAT
  uint32_t u32_brg;
#else
  float f_brg;
#endif

  /*************************  UART config ********************/
  // See comments in the #warning statements below for
  // instructions on how to modify this configuration.
  // More information on each of these board is given
  // in the HARDWARE_PLATFORM section of dspic33_libconfig.h.

 #if (HARDWARE_PLATFORM == DEFAULT_DESIGN)
  #if defined(__dsPIC33F__)
  CONFIG_U1RX_TO_RP(10);               //U1RX <- RP10
  CONFIG_RP11_AS_DIG_PIN();                //TX RP pin must be digital
  CONFIG_U1TX_TO_RP(11);               //U1TX -> RP11
  #endif
  // turn off any analog functionality on these pins
  // (may be needed if pin is hardmapped and RPx does
  // not exist)
  DISABLE_U1TX_ANALOG();
  DISABLE_U1RX_ANALOG();
 #else
  #error Unknown hardware platform.
 #endif

  // First, disable the UART, clearing all errors, terminating
  // any in-progress transmissions/receptions, etc.
  // In particular, this clears UTXEN.
  U1MODE = (0u << 15); // UARTEN = 0 to disable.

  /* Configure UART baud rate, based on \ref FCY.
   *  NOTE: Be careful about using BRGH=1 - this uses only four clock
   *  periods to sample each bit and can be very intolerant of
   *  baud rate % error - you may see framing errors. BRGH is selected
   *  via the DEFAULT_BRGH1 define above.
   */
#ifdef _NOFLOAT
  u32_brg = FCY/u32_baudRate;
#if (DEFAULT_BRGH1 == 0)
  if ((u32_brg & 0x0FL) >= 8) u32_brg = u32_brg/16;
  else u32_brg = u32_brg/16 - 1;
#else
  if ((brg & 0x03L) >= 2) u32_brg = u32_brg/4;
  else u32_brg = u32_brg/4 - 1;
#endif
  ASSERT(u32_brg < 65536);
  U1BRG = u32_brg;
#else
#if (DEFAULT_BRGH1 == 0)
  f_brg = (((float) FCY)/((float) u32_baudRate)/16.0) - 1.0;
#else
  f_brg = (((float) FCY)/((float) u32_baudRate)/4.0) - 1.0;
#endif
  ASSERT(f_brg < 65535.5);
  U1BRG = roundFloatToUint16(f_brg);
#endif

  // Set up the UART mode register
  U1MODE =
    (1u   << 15) |      // UARTEN = 1 (enable the UART)
    (0u   << 13) |      // USIDL = 0  (continue operation in idle mode)
    (0u   << 12) |      // IREN = 0   (IrDA encoder and decoder disabled)
    (0u   << 11) |      // RTSMD = 0  (UxRTS# in flow control mode. Given
                        //  the UEN setting below, this doesn't matter.)
    (0b00 <<  8) |      // UEN = 00   (UxTX and UxRx pins are enabled and used;
                        //  used; UxCTS, UxRTS, and BCLKx pins are
                        //  controlled by port latches)
    (0u   <<  7) |      // WAKE = 0   (Wake-up on start bit detect during
                        //  sleep mode disabled)
    (0u   <<  6) |      // LPBACK = 0 (UARTx loopback mode is disabled)
    (0u   <<  5) |      // ABAUD = 0  (Auto-baud disabled)
    (0u   <<  4) |      // URXINV = 0 (Receve polarity inversion bit:
                        //  UxRX idle state is 1)
    (DEFAULT_BRGH1 << 3) | // BRGH (High/low baud rate select bit:
                        //  1 = high speed, 0 = low speed)
    (0b00 <<  1) |      // PDSEL = 00 (8-bit data, no parity)
    (0u   <<  0);       // STSEL = 0  (1 stop bit)r

  // Set up the UART status and control register
  U1STA =
    (0u   << 15) |      // UTXISEL1 = 0  (See bit 13 below for explanation)
    (0u   << 14) |      // UTXINV = 0    (UxTX idle state is 1 (though docs
                        //  say 0))
    (0u   << 13) |      // UTXISEL0 = 0  (With bit 15 above, UTXISEL = 00:
                        //  Interrupt generated when any character
                        //  is transferred to the Transmit Shift Register).
    (0u   << 11) |      // UTXBRK = 0    (Sync break transmission disabled)
    (1u   << 10) |      // UTXEN = 0     (UARTx transmitter enabled. NOTE: per
                        //  the data sheet, this must be set *AFTER* UARTEN
                        //  is set to 1 (see UxMODE assignment above).
    (0b00 <<  6) |      // URXISEL = 00  (Interrupt flag bit is set when a
                        //  character is received)
    (0u   <<  5) |      // ADDEN = 0     (Address detect mode disabled)
    (0u   <<  1);       // OERR = 0      (Clear any overrun errors)

  // Delay 1 ms (at least one bit time) before beginning transmission,
  // since the UxTX pin is initially configured as an input on device
  // reset. It needs to be high for at least one bit time before
  // a character is sent in order for the start bit to be recognized.
  // See 24H FRM Sec. 17.5 for more details.
  ASSERT(u32_baudRate >= 1000L);
  // Note: If the baud rate is less than 1000, this delay
  // isn't long encough. The alternative is to use floating-point
  // math to compute the correct delay, which seems worse than the
  // problem.
  DELAY_MS(1);

  // Clear any errors
  U1STAbits.OERR = 0;
  while (U1STAbits.PERR || U1STAbits.FERR) {
    U1RXREG; //clear errors by reading RXREG
  }

  // Set up interrupts if requested
#ifdef UART1_RX_INTERRUPT
  _U1RXIF = 0;            //clear the flag
  _U1RXIP = UART1_RX_INTERRUPT_PRIORITY; //choose a priority
  _U1RXIE = 1;            //enable the interrupt
#endif
#ifdef UART1_TX_INTERRUPT
  //do not clear the U1TXIF flag!
  _U1TXIP = UART1_TX_INTERRUPT_PRIORITY; //choose a priority
  //do not enable the interrupt until we try to write to the UART
#endif

}

#endif // #if (NUM_UARTS >= 1)

