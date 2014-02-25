#ifndef PORTS_H
#define	PORTS_H

#if defined(_INT1R)
/// Maps INT1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#define CONFIG_INT1_TO_RP(pin) _INT1R = pin
#else
#define CONFIG_INT1_TO_RP(pin)
#endif

/// Maps INT2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_INT2R)
#define CONFIG_INT2_TO_RP(pin) _INT2R = pin
#else
#define CONFIG_INT2_TO_RP(pin)
#endif

/// Maps T2CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T2CKR)
#define CONFIG_T2CK_TO_RP(pin) _T2CKR = pin
#else
#define CONFIG_T2CK_TO_RP(pin)
#endif

/// Maps T3CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T3CKR)
#define CONFIG_T3CK_TO_RP(pin) _T3CKR = pin
#else
#define CONFIG_T3CK_TO_RP(pin)
#endif

/// Maps T4CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T4CKR)
#define CONFIG_T4CK_TO_RP(pin) _T4CKR = pin
#else
#define CONFIG_T4CK_TO_RP(pin)
#endif

/// Maps T5CK to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_T5CKR)
#define CONFIG_T5CK_TO_RP(pin) _T5CKR = pin
#else
#define CONFIG_T5CK_TO_RP(pin)
#endif

/// Maps IC1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC1R)
#define CONFIG_IC1_TO_RP(pin) _IC1R = pin
#else
#define CONFIG_IC1_TO_RP(pin)
#endif

/// Maps IC2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC2R)
#define CONFIG_IC2_TO_RP(pin) _IC2R = pin
#else
#define CONFIG_IC2_TO_RP(pin)
#endif

/// Maps IC3 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC3R)
#define CONFIG_IC3_TO_RP(pin) _IC3R = pin
#else
#define CONFIG_IC3_TO_RP(pin)
#endif

/// Maps IC4 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC4R)
#define CONFIG_IC4_TO_RP(pin) _IC4R = pin
#else
#define CONFIG_IC4_TO_RP(pin)
#endif

/// Maps IC5 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC5R)
#define CONFIG_IC5_TO_RP(pin) _IC5R = pin
#else
#define CONFIG_IC5_TO_RP(pin)
#endif

/// Maps IC6 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC6R)
#define CONFIG_IC6_TO_RP(pin) _IC6R = pin
#else
#define CONFIG_IC6_TO_RP(pin)
#endif

/// Maps IC7 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC7R)
#define CONFIG_IC7_TO_RP(pin) _IC7R = pin
#else
#define CONFIG_IC7_TO_RP(pin)
#endif

/// Maps IC8 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_IC8R)
#define CONFIG_IC8_TO_RP(pin) _IC8R = pin
#else
#define CONFIG_IC8_TO_RP(pin)
#endif

/// Maps OCFA to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_OCFAR)
#define CONFIG_OCFA_TO_RP(pin) _OCFAR = pin
#else
#define CONFIG_OCFA_TO_RP(pin)
#endif

/// Maps OCFB to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_OCFBR)
#define CONFIG_OCFB_TO_RP(pin) _OCFBR = pin
#else
#define CONFIG_OCFB_TO_RP(pin)
#endif

/// Maps FLTA1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_FLTA1R)
#define CONFIG_FLTA1_TO_RP(pin) _FLTA1R = pin
#else
#define CONFIG_FLTA1_TO_RP(pin)
#endif

/// Maps FLTA2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_FLTA2R)
#define CONFIG_FLTA2_TO_RP(pin) _FLTA2R = pin
#else
#define CONFIG_FLTA2_TO_RP(pin)
#endif

/// Maps QEA1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_QEA1R)
#define CONFIG_QEA1_TO_RP(pin) _QEA1R = pin
#else
#define CONFIG_QEA1_TO_RP(pin)
#endif

/// Maps QEB1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_QEB1R)
#define CONFIG_QEB1_TO_RP(pin) _QEB1R = pin
#else
#define CONFIG_QEB1_TO_RP(pin)
#endif

/// Maps INDX1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_INDX1R)
#define CONFIG_INDX1_TO_RP(pin) _INDX1R = pin
#else
#define CONFIG_INDX1_TO_RP(pin)
#endif

/// Maps QEA2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_QEA2R)
#define CONFIG_QEA2_TO_RP(pin) _QEA2R = pin
#else
#define CONFIG_QEA2_TO_RP(pin)
#endif

/// Maps QEB1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_QEB2R)
#define CONFIG_QEB2_TO_RP(pin) _QEB2R = pin
#else
#define CONFIG_QEB2_TO_RP(pin)
#endif

/// Maps INDX2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_INDX2R)
#define CONFIG_INDX2_TO_RP(pin) _INDX2R = pin
#else
#define CONFIG_INDX2_TO_RP(pin)
#endif

/// Maps U1RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U1RXR)
#define CONFIG_U1RX_TO_RP(pin) _U1RXR = pin
#else
#define CONFIG_U1RX_TO_RP(pin)
#endif

/// Maps U1CTS to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U1CTSR)
#define CONFIG_U1CTS_TO_RP(pin) _U1CTSR = pin
#else
#define CONFIG_U1CTS_TO_RP(pin)
#endif

/// Maps U2RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U2RXR)
#define CONFIG_U2RX_TO_RP(pin) _U2RXR = pin
#else
#define CONFIG_U2RX_TO_RP(pin)
#endif

/// Maps U2CTS to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_U2CTSR)
#define CONFIG_U2CTS_TO_RP(pin) _U2CTSR = pin
#else
#define CONFIG_U2CTS_TO_RP(pin)
#endif

/// Maps SDI1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SDI1R)
#define CONFIG_SDI1_TO_RP(pin) _SDI1R = pin
#else
#define CONFIG_SDI1_TO_RP(pin)
#endif

/// Maps SCK1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SCK1R)
#define CONFIG_SCK1IN_TO_RP(pin) _SCK1R = pin
#else
#define CONFIG_SCK1IN_TO_RP(pin)
#endif

/// Maps SS1 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SS1R)
#define CONFIG_SS1IN_TO_RP(pin) _SS1R = pin
#else
#define CONFIG_SS1IN_TO_RP(pin)
#endif

/// Maps SDI2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SDI2R)
#define CONFIG_SDI2_TO_RP(pin) _SDI2R = pin
#else
#define CONFIG_SDI2_TO_RP(pin)
#endif

/// Maps SCK2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SCK2R)
#define CONFIG_SCK2IN_TO_RP(pin) _SCK2R = pin
#else
#define CONFIG_SCK2IN_TO_RP(pin)
#endif

/// Maps SS2 to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_SS2R)
#define CONFIG_SS2IN_TO_RP(pin) _SS2R = pin
#else
#define CONFIG_SS2IN_TO_RP(pin)
#endif

/// Maps C1RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_C1RXR)
#define CONFIG_C1RXR_TO_RP(pin) _C1RXR = pin
#else
#define CONFIG_C1RXR_TO_RP(pin)
#endif

/// Maps C2RX to a remappable pin;
/// see <a href="#remappableInputs">remappable peripheral input support</a>
/// for more informatino.
#if defined(_C2RXR)
#define CONFIG_C2RXR_TO_RP(pin) _C2RXR = pin
#else
#define CONFIG_C2RXR_TO_RP(pin)
#endif
//@}


/** \name Remappable peripheral output support
 *  <a name="remappableOutputs">These</a> functions maps an output
 *  internal to the PIC to an output pin.
 *  For example, CONFIG_C1OUT_TO_RP(10) maps the C1OUT comparator
 *  output to port P, pin 10.
 *
 *  Not all devices support remappable peripherals. In these cases,
 *  the macros below evalaute to nothing: CONFIG_C1OUT_TO_RP(10) is
 *  a valid C statement which does nothing.
 */
//@{

/// Define peripheral pins

#define RPMAP_C1OUT 	1
#define RPMAP_C2OUT 	2
#define RPMAP_U1TX 	    3
#define RPMAP_U1RTS 	4
#define RPMAP_U2TX  	5
#define RPMAP_U2RTS 	6
#define RPMAP_SD01  	7
#define RPMAP_SCK1OUT  	8
#define RPMAP_SS1OUT  	9
#define RPMAP_SDO2  	10
#define RPMAP_SCK2OUT  	11
#define RPMAP_SS2OUT  	12
#define RPMAP_C1TX  	16
#define RPMAP_OC1   	18
#define RPMAP_OC2   	19
#define RPMAP_OC3   	20
#define RPMAP_OC4   	21
#define RPMAP_UPDN1   	26
#define RPMAP_UPDN2   	27

///  CONFIG_NULL_TO_RP(n) returns RPn to an 'unmapped' state
/// (i.e, the reset condition).
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_NULL_TO_RP(pin) _RP##pin##R = 0
#else
#define CONFIG_NULL_TO_RP(pin)
#endif

/// Maps C1OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_C1OUT_TO_RP(pin) _RP##pin##R = RPMAP_C1OUT
#else
#define CONFIG_C1OUT_TO_RP(pin)
#endif

/// Maps C2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_C2OUT_TO_RP(pin) _RP##pin##R = RPMAP_C2OUT
#else
#define CONFIG_C2OUT_TO_RP(pin)
#endif

/// Maps U1TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_U1TX_TO_RP(pin) _RP##pin##R = RPMAP_U1TX
#else
#define CONFIG_U1TX_TO_RP(pin)
#endif

/// Maps U1RTS to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_U1RTS_TO_RP(pin) _RP##pin##R = RPMAP_U1RTS
#else
#define CONFIG_U1RTS_TO_RP(pin)
#endif

/// Maps U2TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_U2TX_TO_RP(pin) _RP##pin##R = RPMAP_U2TX
#else
#define CONFIG_U2TX_TO_RP(pin)
#endif

/// Maps U2RTS to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_U2RTS_TO_RP(pin) _RP##pin##R = RPMAP_U2RTS
#else
#define CONFIG_U2RTS_TO_RP(pin)
#endif

/// Maps SDO1 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_SDO1_TO_RP(pin) _RP##pin##R = RPMAP_SD01
#else
#define CONFIG_SDO1_TO_RP(pin)
#endif

/// Maps SCK1OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_SCK1OUT_TO_RP(pin) _RP##pin##R = RPMAP_SCK1OUT
#else
#define CONFIG_SCK1OUT_TO_RP(pin)
#endif

/// Maps SS11OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_SS1OUT_TO_RP(pin) _RP##pin##R = RPMAP_SS1OUT
#else
#define CONFIG_SS1OUT_TO_RP(pin)
#endif

/// Maps SDO2 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_SDO2_TO_RP(pin) _RP##pin##R = RPMAP_SDO2
#else
#define CONFIG_SDO2_TO_RP(pin)
#endif

/// Maps SCK2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_SCK2OUT_TO_RP(pin) _RP##pin##R = RPMAP_SCK2OUT
#else
#define CONFIG_SCK2OUT_TO_RP(pin)
#endif

/// Maps SS2OUT to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_SS2OUT_TO_RP(pin) _RP##pin##R = RPMAP_SS2OUT
#else
#define CONFIG_SS2OUT_TO_RP(pin)
#endif

/// Maps C1TX to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_C1TX_TO_RP(pin) _RP##pin##R = RPMAP_C1TX
#else
#define CONFIG_C1TX_TO_RP(pin)
#endif

/// Maps OC1 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_OC1_TO_RP(pin) _RP##pin##R = RPMAP_OC1
#else
#define CONFIG_OC1_TO_RP(pin)
#endif

/// Maps OC2 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_OC2_TO_RP(pin) _RP##pin##R = RPMAP_OC2
#else
#define CONFIG_OC2_TO_RP(pin)
#endif

/// Maps OC3 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_OC3_TO_RP(pin) _RP##pin##R = RPMAP_OC3
#else
#define CONFIG_OC3_TO_RP(pin)
#endif

/// Maps OC4 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_OC4_TO_RP(pin) _RP##pin##R = RPMAP_OC4
#else
#define CONFIG_OC4_TO_RP(pin)
#endif

/// Maps UPDN1 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_UPDN1_TO_RP(pin) _RP##pin##R = RPMAP_UPDN1
#else
#define CONFIG_UPDN1_TO_RP(pin)
#endif


/// Maps UPDN1 to a remappable pin;
/// see <a href="#remappableOutputs">remappable peripheral output support</a>
/// for more information.
#if defined(_RP0R) || defined(_RP20R)
#define CONFIG_UPDN2_TO_RP(pin) _RP##pin##R = RPMAP_UPDN2
#else
#define CONFIG_UPDN2_TO_RP(pin)
#endif

// Include appropriate ports file for the device in use.


#if defined(__dsPIC33FJ64MC802__)
#include "devices/dspic33fj64mc802_ports.h"
#endif

#if defined(__dsPIC33FJ128MC802__)
#include "devices/dspic33fj128mc802_ports.h"
#endif

#endif	/* PORTS_H */

