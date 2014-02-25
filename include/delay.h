#ifndef DELAY_H
#define	DELAY_H

#include <stdint.h>
#include "util.h"  // Need u32_heartbeatCount
#include <libpic30.h>    // Has __delay32



/** Delay the given number of processor clock cycles,
 *  then notify the heartbeat that time passed.
 *  Scale the time added to the heartbeat because
 *  we are not incurring the same
 *  overhead as if we repeatedly called
 *  <code>doHeartbeat()</code>.
 *  \param u32_cyc Number of processor clock cycles
 *                 to delay.
 */
inline static void delayAndUpdateHeartbeatCount(uint32_t u32_cyc) {
  __delay32(u32_cyc);
#if USE_HEARTBEAT
  u32_heartbeatCount += (u32_cyc >> 4);
#endif
}


/** A macro to delay the given number of milliseconds.
 *  The maximum delay is ~ 100+
 *  seconds when FCY = 40 MHz, because the underlying
 *  function \ref delayAndUpdateHeartbeatCount uses
 *  a uint32_t value for the number of processor clocks
 *  to delay.
 * \param ms The number of milliseconds to delay.
 */
#define DELAY_MS(ms)  delayAndUpdateHeartbeatCount(CYCLES_PER_MS * ((uint32_t) ms));

/** A macro to delay the given number of microseconds.
 *  \see \ref DELAY_MS for additional information.
 * \param us The number of microseconds to delay.
 */
#define DELAY_US(us)  delayAndUpdateHeartbeatCount(CYCLES_PER_US * ((uint32_t) us));

#endif	/* DELAY_H */

