#ifndef UTIL_H
#define	UTIL_H

#include <stdint.h>
#include "chip.h"
#include "libconfig.h"

/** \name Bitfield to struct conversion
 *  <a name="bitfieldMacros">Given</a> a bitfield struct representing an SFR,
 *  convert this to a word (uint16_t) or to the
 *  high and low bytes (uint8_t) of that word.
 *  Note: though this looks ugly, it introduces
 *  no unexpected compiler overhead at -O1. See
 *  \ref u16_INTTREGlast for an example.
 */
//@{
/// Convert a bitfield to a word (uint16_t).
#define BITS2WORD(sfrBitfield)  ( *((uint16_t*) &sfrBitfield) )
/// Return the low byte (as a uint8_t) of a bitfield.
#define BITS2BYTEL(sfrBitfield) ( ((uint8_t*)  &sfrBitfield)[0] )
/// Return the high byte (as a uint8_t) of a bitfield.
#define BITS2BYTEH(sfrBitfield) ( ((uint8_t*)  &sfrBitfield)[1] )
//@}

/** Report an error on reset via \ref reportError,
 *  also printing the file and
 *  line number where this macro was called via
 *  a call to \ref ERROR_FILE_LINE.
 *  \param msg Error message to report
 */
#define REPORT_ERROR(msg) reportError(ERROR_FILE_LINE(msg))

#ifdef SIM
#define HELLO_MSG "****************************************************\n" \
                  "*    SIMULATION MODE - DO NOT RUN ON A REAL PIC!   *\n" \
                  "****************************************************\n" \
                  "\n" __FILE__ ", built on " __DATE__ " at " __TIME__ "\n"
// Output a warning during compilation also
#warning ***********************************************
#warning * SIMULATION MODE - DO NOT RUN ON A REAL PIC! *
#warning ***********************************************
#else
#define HELLO_MSG "\n" __FILE__ ", built on " __DATE__ " at " __TIME__ "\n"
#endif


void reportError(const char* szErrorMessage);
uint32_t readProgramMemory(uint32_t u32_address);
void checkDeviceAndRevision(void);
void checkOscOption(void);
void printResetCause(void);
void configPinsForLowPower(void);
void configBasic(const char* psz_helloMsg);
uint32_t roundFloatToUint32(float f_x);
uint16_t roundFloatToUint16(float f_x);

extern _PERSISTENT const char* sz_lastTimeoutError;

#if USE_HEARTBEAT
extern uint32_t u32_heartbeatCount;
#endif

void configHeartbeat(void);
void doHeartbeat(void);
void toggleHeartbeat(void);

#endif	/* UTIL_H */

