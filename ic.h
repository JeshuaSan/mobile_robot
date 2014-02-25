/* 
 * File:   ic.h
 * Author: Jesus
 *
 * Created on March 31, 2013, 5:54 PM
 */

#ifndef IC_H
#define	IC_H

#include "include/chip.h"
#include "include/ports.h"
#include <stdint.h>

/// ICxCON: Input Capture x Control Register

// ICSIDL: Input Capture x Stop in Idle Control bit
typedef struct tagICSIDL{
    unsigned CONTINUE_ON_IDLE   :1;
    unsigned HALT_ON_IDLE       :1;
}ICSIDL;
enum{
    CONTINUE_ON_IDLE,   // 0 = Input capture continues to operate in CPU Idle mode
    HALT_ON_IDLE        // 1 = Input capture halts in CPU Idle mode
};
static ICSIDL ICSIDLconfig = {CONTINUE_ON_IDLE,HALT_ON_IDLE};

// ICTMR: Input Capture x Timer Select bit
typedef struct tagICTMR{
    unsigned USE_TMR3   :1;
    unsigned USE_TMR2   :1;
}ICTMR;
enum{
    USE_TMR3,   // 0 = TMR3 contents are captured on capture event
    USE_TMR2    // 1 = TMR2 contents are captured on capture event
};
static ICTMR ICTMRconfig = {USE_TMR3,USE_TMR2};

// ICI<1:0>: Select Number of Captures per Interrupt bits
typedef struct tagICI{
    unsigned EVERY_CAPTURE          :2;
    unsigned EVERY_SECOND_CAPTURE   :2;
    unsigned EVERY_THIRD_CAPTURE    :2;
    unsigned EVERY_FOURTH_CAPTURE   :2;
}ICI;
enum{
    EVERY_CAPTURE,          // 00 = Interrupt on every capture event
    EVERY_SECOND_CAPTURE,   // 01 = Interrupt on every second capture event
    EVERY_THIRD_CAPTURE,    // 10 = Interrupt on every third capture event
    EVERY_FOURTH_CAPTURE    // 11 = Interrupt on every fourth capture event
};
static ICI ICIconfig = {EVERY_CAPTURE,EVERY_SECOND_CAPTURE,EVERY_THIRD_CAPTURE,EVERY_FOURTH_CAPTURE};

// ICOV: Input Capture x Overflow Status Flag bit (read-only)
#define IC1GetOverflowStatus()  IC1CONbits.ICOV
#define IC2GetOverflowStatus()  IC2CONbits.ICOV

// ICBNE: Input Capture x Buffer Empty Status Flag bit (read-only)
#define IC1GetBufferStatus()    IC1CONbits.ICBNE
#define IC2GetBufferStatus()    IC2CONbits.ICBNE

// ICM<2:0>: Input Capture x Mode Select bits
typedef struct tagICM{
    unsigned MODULE_OFF             :3;
    unsigned EVERY_EDGE             :3;
    unsigned EVERY_FALLING_EDGE     :3;
    unsigned EVERY_RISING_EDGE      :3;
    unsigned EVERY_4TH_RISING_EDGE  :3;
    unsigned EVERY_16TH_RISING_EDGE :3;
    unsigned IC_AS_INTERRUPT_PIN    :3;
}ICM;
enum{
    MODULE_OFF,             // 000 = Input Capture module turned off
    EVERY_EDGE,             // 001 = Capture mode, every edge ? rising and falling (ICI<1:0> bits do not control interrupt generation for this mode)
    EVERY_FALLING_EDGE,     // 010 = Capture mode, every falling edge
    EVERY_RISING_EDGE,      // 011 = Capture mode, every rising edge
    EVERY_4TH_RISING_EDGE,  // 100 = Capture mode, every 4th rising edge
    EVERY_16TH_RISING_EDGE, // 101 = Capture mode, every 16th rising edge
                            // 110 = Unused (Input Capture module disabled)
    IC_AS_INTERRUPT_PIN = 7 // 111 = Input capture functions as interrupt pin only when device is in Sleep or Idle mode (rising edge detect only, all other control bits are not applicable)
};
static ICM ICMconfig = {MODULE_OFF,EVERY_EDGE,EVERY_FALLING_EDGE,EVERY_RISING_EDGE,EVERY_4TH_RISING_EDGE,EVERY_16TH_RISING_EDGE,IC_AS_INTERRUPT_PIN};


/* Function prototypes */
void ic1Config();
void ic2Config();

#endif	/* IC_H */

