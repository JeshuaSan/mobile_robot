#ifndef UART_H
#define	UART_H

#include <stdint.h>
#include "chip.h"
#include "libconfig.h"
#include "util.h"
// Only include if this UART module exists.
#if (NUM_UART_MODS >= 1)

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
// Note: place this comment below the #if NUM_UART_MODS so Doxygen
// will only see it once.
/** \file
 *  This file contains routines which configure and
 *  use the UARTs on the PIC. See \ref dspic33_serial.h
 *  for higher-level routines, which should typically
 *  be called by the user rather than these routines.
 */


/** Determine if a character is available in the UART's
 *  receive buffer.
 *  \return True (1) if character is available, 0 if not.
 */
#define IS_CHAR_READY_UART1() U1STAbits.URXDA

/** Determine if a the transmit buffer is full.
 *  \return True (1) if the transmit buffer if full,
 *          false (0) if not.
 */
#define IS_TRANSMIT_BUFFER_FULL_UART1() U1STAbits.UTXBF

/** Determines if all characters placed in the UART have been sent.
 *  Returns 1 if the last transmission has completed, or 0 if a transmission
 *  is in progress or queued in the transmit buffer.
 *  \return True (1) if the last transmission has completed, 0 if not.
 */
#define IS_TRANSMIT_COMPLETE_UART1() U1STAbits.TRMT

/** Waits until all characters placed in the UART have been sent. */
inline static void WAIT_UNTIL_TRANSMIT_COMPLETE_UART1() {
  while (!IS_TRANSMIT_COMPLETE_UART1())
    doHeartbeat();
}

void outChar1(uint8_t u8_c);
uint8_t inChar1(void);
void configUART1(uint32_t u32_baudRate);
uint8_t isCharReady1(void);
void checkRxErrorUART1(void); //check for UART RX error

#endif // #if (NUM_UART_MODS >= 1)
#endif // #ifndef _DSPIC33_UART1_H_
