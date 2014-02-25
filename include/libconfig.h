#ifndef LIBCONFIG_H
#define	LIBCONFIG_H

#define DEFAULT_DESIGN 3


/** Select one of the hardware platform above to compile for. */
#ifndef HARDWARE_PLATFORM
#define HARDWARE_PLATFORM DEFAULT_DESIGN
#endif


/** Clock configuration for the PIC24 - set \ref CLOCK_CONFIG
 *  to one of the following. Naming convention is
 *  OSCTYPE_[PRIFREQ]_FCYFREQ where OSCTYPE gives the
 *  oscillator type (see \ref FNOSC_SEL for details),
 *  the optional PRIFREQ specifies primary oscillator frequency,
 *  and FCYFREQ determiens the processor clock
 *  (F<sub>CY</sub>) frequency. The "#defines for CLOCK_CONFIG"
 *  section gives the definition of the values below.
 *
 *  \code
 *  Name                            uP
 *  ---------------                 ---
 *  SIM_CLOCK (simulator)           any
 *  FRCPLL_FCY16MHz                 24F
 *  FRC_FCY4MHz                     24F
 *  PRIPLL_8MHzCrystal_16MHzFCY     24F
 *  PRI_NO_PLL_7372KHzCrystal       24F, 24H
 *  FRC_FCY3685KHz                  24H
 *  FRCPLL_FCY40MHz                 24H
 *  PRIPLL_7372KHzCrystal_40MHzFCY  24H
 *  PRIPLL_8MHzCrystal_40MHzFCY     24H
 *  \endcode
 */
// Uncomment one of the #defines below to make
// a clock choice. If all the #defines below
// are commentend, code below
// will pick a default clock choice.
#ifndef CLOCK_CONFIG
//#define CLOCK_CONFIG SIM_CLOCK
//#define CLOCK_CONFIG FRCPLL_FCY16MHz
//#define CLOCK_CONFIG FRC_FCY4MHz
//#define CLOCK_CONFIG PRIPLL_8MHzCrystal_16MHzFCY
//#define CLOCK_CONFIG PRI_NO_PLL_7372KHzCrystal
//#define CLOCK_CONFIG FRC_FCY3685KHz
//#define CLOCK_CONFIG FRCPLL_FCY40MHz
#define CLOCK_CONFIG PRIPLL_7372KHzCrystal_40MHzFCY
//#define CLOCK_CONFIG PRIPLL_8MHzCrystal_40MHzFCY
#endif

// For convenience, choose the fastest
// possible clock depending on which
// processor we're using. If simulation mode is
// selected, then use the simulation clock.
#ifndef CLOCK_CONFIG
#if defined(SIM)
#define CLOCK_CONFIG SIM_CLOCK
#elif defined(__PIC24H__)
#define CLOCK_CONFIG FRCPLL_FCY40MHz
#elif defined(__dsPIC33F__)
#define CLOCK_CONFIG FRCPLL_FCY40MHz
//60MHz clock is conservative max choice for PIC24E, 70MHz has a more limited temp. range.
#endif
#endif

/// @}

/** \name Defines configuring  pic24_delay.h
 *  @{
 */

/** Define a debounce delay for use in reading pushbutton
 *  switches. The value is specified in milliseconds.
 */
#ifndef DEBOUNCE_DLY
#define DEBOUNCE_DLY  15   //in milliseconds
#endif

/// @}



/** \name outString() end-of-line behavior in pic24_serial.h
 *  @{
 */

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  send a CR with every LF in outString.
 *  PuTTY uses this, expects "\n\r".
 */
#define SERIAL_EOL_CR_LF 0

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  send a carriage return only ("\r") to end a line.
 */
#define SERIAL_EOL_CR   1

/** Set \ref SERIAL_EOL_DEFAULT to this value to
 *  sends a new line only ("\n"). This
 *  works for Bully Bootloader, MPLAB SIM, TeraTerm,
 *  RealTerm.
 */
#define SERIAL_EOL_LF   2

/** This macro defines end-of-line output behavior
 *  when the \ref outString() function is passed a new line ("\n").
 *  Set this to either \ref SERIAL_EOL_CR_LF, \ref SERIAL_EOL_CR, or
 *  \ref SERIAL_EOL_LF.
 */
#ifndef SERIAL_EOL_DEFAULT   //can be overridden in project file
#define SERIAL_EOL_DEFAULT SERIAL_EOL_LF
#endif

#if (SERIAL_EOL_DEFAULT != SERIAL_EOL_CR_LF) && \
	  (SERIAL_EOL_DEFAULT != SERIAL_EOL_CR)    && \
    (SERIAL_EOL_DEFAULT != SERIAL_EOL_LF)
#error Invalid choice for SERIAL_EOF_DEFAULT
#endif

/// @}

/** \name Defines from pic24_serial.h
 *  @{
 */
/** Defines the default UART which the configUART() function
 *  initializes and which serial I/O is directed to
 *  until the _C30_UART variable is changed.
 */
#ifndef DEFAULT_UART
#define DEFAULT_UART 1
#endif



/** Default baud rate used by \ref configBasic() to
 * configure the \ref DEFAULT_UART.
 */
#ifndef DEFAULT_BAUDRATE
// For convenience, common baud rates (uncomment one):
//#define DEFAULT_BAUDRATE  230400
#define DEFAULT_BAUDRATE  115200
//#define DEFAULT_BAUDRATE   57600
//#define DEFAULT_BAUDRATE   38400
//#define DEFAULT_BAUDRATE   19200
//#define DEFAULT_BAUDRATE    9600
#endif

/** Default BRGH value used by \ref configUART1 to 4
 *  when configurating a UART. This value may be
 *  overridden on a per-UART basis by \#defineing
 *  \ref DEFAULT_BRGH1 to 4. Allowed values:
 *  - BRGH = 0 - the baud rate divisor is 16
 *  - BRGH = 1 - the baud rate divisor is 4
 */
#ifndef DEFAULT_BRGH
#define DEFAULT_BRGH  0
#endif

#if (DEFAULT_BRGH != 0) && (DEFAULT_BRGH != 1)
#error Invalid value for DEFAULT_BRGH
#endif

/// @}

/** \name Defines configuring pic24_util.h
 *  @{
 */

/** When set to 1, verify that calls to switchClock() do
 *  successfully switch the clock, reporting an error
 *  message on failure. See also checkClockTimeout().
 */
#ifndef USE_CLOCK_TIMEOUT
#ifdef BUILT_ON_ESOS
#define USE_CLOCK_TIMEOUT 0
#else
#define USE_CLOCK_TIMEOUT 1
#endif
#endif

/* \name Heartbeat
 *  These routines provide heartbeat support by blinking a LED
 *  on a regular basis. See doHeartbeat() for more information.
 */
//@{

#ifndef USE_HEARTBEAT
/** If this macro is true, heartbeat functionality is enabled.
 *  If false, heartbeat is disabled.
 */
#define USE_HEARTBEAT 1
#endif


#ifndef HB_LED
#if defined (__PIC24H__)

#define HB_LED _LATB15
#define CONFIG_HB_LED() CONFIG_RB15_AS_DIG_OUTPUT()

#elif defined (__dsPIC33F__)

//#define HB_LED _LATA4
//#define CONFIG_HB_LED() CONFIG_RA4_AS_DIG_OUTPUT()

#define HB_LED _LATA4
#define CONFIG_HB_LED() CONFIG_RA4_AS_DIG_OUTPUT()

#endif
#endif // #ifndef HB_LED

#endif	/* LIBCONFIG_H */

