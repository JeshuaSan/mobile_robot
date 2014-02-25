#ifndef CHIP_H
#define	CHIP_H

#include "p33Fxxxx.h"


#ifdef _ISR
#undef _ISR
/// Override the standard Microchip ISR definition, since it produces the
/// following warning:
/// warning:  PSV model not specified for '_DefaultInterrupt';
///   assuming 'auto_psv' this may affect latency
/// This definition adds the auto_psv specifier, which produces
/// a bit of extra code but allow accessing constant data
/// (data stored in program memory).
#define _ISR __attribute__((interrupt)) __attribute__ ((auto_psv))
#endif

#ifdef _ISRFAST
#undef _ISRFAST
/// Unlike \ref _ISR, this definition does not allow the ISR to access
/// constant data (data stored in program memory). This saves some
/// clock cycles. Unlike the Microchip definition, it does NOT use
/// shadow registers as well.
#define _ISRFAST __attribute__((interrupt)) __attribute__ ((no_auto_psv))
#endif


/// Place the processor in sleep mode.
#define SLEEP()  Sleep()

/// Place the processor in idle mode.
#define IDLE()   Idle()

/// Clear the watch-dog timer.
#define CLRWDT() ClrWdt()

/// Insert a one-cycle nop instruction.
#define NOP() Nop()

/// Enable the watchdog timer.
#define ENABLEWDT() (_SWDTEN = 1)

/// Disable the watchdog timer.
#define DISABLEWDT() (_SWDTEN = 0)

/// \name Peripheral identification
//@{
/** Define the number of UART modules supported by this chip.
 *  NOTE: this only works when testing \#defines, not
 *  testing variable. So, don't test UxSTA; instead,
 *  test _UxRXIF which is uniquely defined for each
 *  UART. (Idea taken from the C30 peripheral library,
 *  in uart.h.)
 */
#if   defined(_U4RXIF)
#define NUM_UART_MODS 4
#elif defined(_U3RXIF)
#define NUM_UART_MODS 3
#elif defined(_U2RXIF)
#define NUM_UART_MODS 2
#elif defined(_U1RXIF)
#define NUM_UART_MODS 1
#else
//#error UxRXIF flag not defined!
#endif

/** Define the number of I2C modules supported by this chip.
 *  See \ref NUM_UART_MODS for details on this methodology.
 */
#if   defined(_SI2C2IF)
#define NUM_I2C_MODS 2
#elif defined(_SI2C1IF)
#define NUM_I2C_MODS 1
#else
//#error SI2CxIF flag not defined!
#endif

/** Define the number of SPI modules supported by this chip.
 *  See \ref NUM_UART_MODS for details on this methodology.
 */
#if   defined(_SPI2IF)
#define NUM_SPI_MODS 2
#elif defined(_SPI1IF)
#define NUM_SPI_MODS 1
#else
//#error SPIxIF flag not defined!
#endif


#if   defined(_C2IF)
#define NUM_ECAN_MODS 2
#elif defined(_C1IF)
#define NUM_ECAN_MODS 1
#else
#define NUM_ECAN_MODS 0
#endif

/** \name Chip identification
 *  These routines assist in identifying the device and revision
 *  of the PIC in use. See checkDeviceAndRevision() for a usage
 *  example.
 */
//@{
/** The location in program memory of the device ID.
 *  Revision information is found in the Silicon Errata
 *  sheet for the device. The Device ID is contained
 * in the datasheet for the target device.
 */
#define DEV_ID_LOCATION 0xFF0000
/** The location in program memory of the revision. */
#define REVISION_LOCATION 0xFF0002

#ifdef __PIC24HJ64GP502__
#define DEV_ID 0x000675
#define DEV_ID_STR "PIC24HJ64GP502"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
#define EXPECTED_REVISION2 0x003002
#define EXPECTED_REVISION2_STR "A2"
#define EXPECTED_REVISION3 0x003003
#define EXPECTED_REVISION3_STR "A3"
#endif


//dsPIC33 CPUS
#ifdef __dsPIC33FJ64MC802__
#define DEV_ID 0x000619
#define DEV_ID_STR "dsPIC33FJ64MC802"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
//#define EXPECTED_REVISION2 0x003002
//#define EXPECTED_REVISION2_STR "A2"
#define EXPECTED_REVISION3 0x003002
#define EXPECTED_REVISION3_STR "A3"
#define EXPECTED_REVISION4 0x003003
#define EXPECTED_REVISION4_STR "A4"
#define EXPECTED_REVISION5 0x003004
#define EXPECTED_REVISION5_STR "A5"
#endif

#ifdef __dsPIC33FJ128MC802__
#define DEV_ID 0x000629
#define DEV_ID_STR "dsPIC33FJ128MC802"
#define EXPECTED_REVISION1 0x003001
#define EXPECTED_REVISION1_STR "A1"
//#define EXPECTED_REVISION2 0x003002
//#define EXPECTED_REVISION2_STR "A2"
#define EXPECTED_REVISION3 0x003002
#define EXPECTED_REVISION3_STR "A3"
#define EXPECTED_REVISION4 0x003003
#define EXPECTED_REVISION4_STR "A4"
#define EXPECTED_REVISION5 0x003004
#define EXPECTED_REVISION5_STR "A5"
#endif

#endif	/* CHIP_H */

