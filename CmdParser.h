/* 
 * File:   CmdParser.h
 * Author: jesus
 *
 * Created on March 27, 2013, 2:02 PM
 */

#ifndef CMDPARSER_H
#define	CMDPARSER_H

#include "Commands.h"
#include <stdint.h>

#define BUFFER_SIZE 3

// Buffer state [S,D1,D2]
typedef enum {
    STATE_STATUS,    // 0 = Status
    STATE_DATA1,     // 1 = Data 1
    STATE_DATA2,     // 2 = Data 2
    STATE_ERROR      // 3 = Error
}BufferState;

typedef enum {
    ERR_BUFF_STS = 1,
    ERR_BUFF_DT1,
    ERR_BUFF_DT2
}BufferError;



typedef struct tagBUFFER {
    uint8_t Message[BUFFER_SIZE];
    uint8_t Ready;
    BufferState State;
    BufferError Error;
}BUFFER;




/**
 * Function prorotypes
 */

//
void cpFillBuffer(void);
static void cpCheckStatus(uint8_t charToParse);
static void cpCheckData1(uint8_t charToParse);
static void cpCheckData2(uint8_t charToParse);
static void cpBufferError(uint8_t charToParse);

void cpParseMessage(void);
static void cpParseMode(uint8_t mode);
static void cpParseMove(uint8_t move);
static void cpParseGet(uint8_t get);
static void cpParseSet(uint8_t set);
static void cpParseSetTune(uint8_t tune);
static void cpParseGetTune(uint8_t tune);
static void cpParseData(void);

static void cpSpeedPeriod(uint8_t wheel);
static void cpSpeedWheel(uint8_t wheel);
static void cpDespPulses(uint8_t wheel);
static void cpDespWheelCM(uint8_t wheel);
static void cpDespWheelP(uint8_t wheel);

uint8_t cpGetBufferState(void);
static void cpResponse(void);


#endif	/* CMDPARSER_H */

