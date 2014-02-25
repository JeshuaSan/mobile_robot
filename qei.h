/* 
 * File:   qei.h
 * Author: Jesus
 *
 * Created on March 30, 2013, 12:35 PM
 */

#ifndef QEI_H
#define	QEI_H

#include "include/chip.h"
#include "include/ports.h"
#include <stdint.h>


#define QEI1GetCNTERR() QEI1CONbits.CNTERR  // CNTERR: Count Error Status Flag bit
#define QEI1GetINDEX()  QEI1CONbits.INDX    // INDEX: Index Pin State Status bit (read-only)
#define QEI1GetUPDN()   QEI1CONbits.UPDN    // UPDN: Position Counter Direction Status bit

#define QEI2GetCNTERR() QEI2CONbits.CNTERR  // CNTERR: Count Error Status Flag bit
#define QEI2GetINDEX()  QEI2CONbits.INDX    // INDEX: Index Pin State Status bit (read-only)
#define QEI2GetUPDN()   QEI2CONbits.UPDN    // UPDN: Position Counter Direction Status bit

// QEIM<2:0>: Quadrature Encoder Interface Mode Select bits
typedef struct tagQEIM{
    unsigned QEI_OFF:3;           // 000 = Quadrature Encoder Interface/Timer off
    unsigned START_16BIT_TIMER:3; // 001 = Starts 16-bit Timer
                                  // 010, 011 = Unused (module disabled)
    unsigned x2_INDEX:3;          // 100 = QEI enabled (x2 mode) with index pulse reset of position counter
    unsigned x2_MATCH:3;          // 101 = QEI enabled (x2 mode) with position counter reset by match (MAXxCNT)
    unsigned x4_INDEX:3;          // 110 = QEI enabled (x4 mode) with index pulse reset of position counter
    unsigned x4_MATCH:3;          // 111 = QEI enabled (x4 mode) with position counter reset by match (MAXxCNT)
}QEIM;
enum {
    QEI_OFF,
    START_16BIT_TIMER,
    x2_INDEX = 4,
    x2_MATCH,
    x4_INDEX,
    x4_MATCH
};
static QEIM QEIMconfig = {QEI_OFF,START_16BIT_TIMER,x2_INDEX,x2_MATCH,x4_INDEX,x4_MATCH};

// TQCKPS<1:0>: Timer Input Clock Prescale Select bits
typedef struct tagTQCKPS{
    unsigned PS_1   :2; // 00 = 1:1 prescale value
    unsigned PS_8   :2; // 01 = 1:8 prescale value
    unsigned PS_64  :2; // 10 = 1:64 prescale value
    unsigned PS_256 :2; // 11 = 1:256 prescale value
}TQCKPS;
enum {
    PS_1,   // 00 = 1:1 prescale value
    PS_8,   // 01 = 1:8 prescale value
    PS_64,  // 10 = 1:64 prescale value
    PS_256  // 11 = 1:256 prescale value
};
static TQCKPS TQCKPSconfig = {PS_1,PS_8,PS_64,PS_256};

//SWPAB: Phase A and Phase B Input Swap Select bit
typedef struct tagSWAPAB{
    unsigned NO_SWAP:1;
    unsigned SWAP   :1;
}SWAPAB;
enum{
    NO_SWAP,
    SWAP
};
static SWAPAB SWAPABconfig = {NO_SWAP,SWAP};

// PCDOUT: Position Counter Direction State Output Enable bit
typedef enum PCDOUT_VALUES{
    DISABLED,
    ENABLED
}PCDOUTvalues;

typedef struct tagPCDOUT{
    PCDOUTvalues DISABLED:1;
    PCDOUTvalues ENABLED :1;
}PCDOUT;
static PCDOUT PCDOUTconfig = {DISABLED,ENABLED};


/* Function declarations*/
void qei1Config();
void qei2Config();


#endif	/* QEI_H */

