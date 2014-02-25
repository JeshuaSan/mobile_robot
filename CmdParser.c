#include "CmdParser.h"
#include "flowcontrol.h"
#include "robot.h"
#include "mcpwm.h"
#include "control.h"


// BUFFER structure to hold the message to parse
BUFFER buffer = {
    .Message = {0,0,0},     // Empty buffer
    .Ready = 0,             // Not ready
    .State = STATE_STATUS,  // Status state
    .Error = 0              // No errors (yet)
};


typedef union{              // Union to acces data as:
    uint16_t asWord;        // a word (2 bytes), or
    uint8_t asByte[2];      // single bytes
}Data;
typedef struct{
    uint8_t Command;
    uint8_t Argument;
    Data Data;
}Message;

Message messageIn = {0,0,0};    // Message to parse
Message messageOut = {0,0,0};   // Mesagge to respond

// Functions to be called by the state machine
void (*messageState[])(uint8_t charToParse) = {cpCheckStatus, cpCheckData1, cpCheckData2, cpBufferError};
void (*getSpeed[])(uint8_t wheel) = {cpSpeedPeriod, cpSpeedWheel};
void (*getDesp[])(uint8_t wheel) = {cpDespPulses, cpDespWheelCM, cpDespWheelP};


/// Main Finite State Machine to get a message
void cpFillBuffer() {
    uint8_t charToParse;
    charToParse = inChar1();
    messageState[buffer.State](charToParse);
}

void cpCheckStatus(uint8_t charToParse){
    if((charToParse & mskSTS) == mskSTS) {      // if MSb set
        buffer.Message[buffer.State] = charToParse;
        buffer.State = STATE_DATA1;                 //  Next state: DATA1
    }
    else {
        buffer.Error = ERR_BUFF_STS;          // Error in STATUS state
        buffer.State = STATE_ERROR;
    }
}

void cpCheckData1(uint8_t charToParse) {
    if((charToParse & mskSTS) != mskSTS) {      // if MSb clear
        buffer.Message[buffer.State] = charToParse;
        buffer.State = STATE_DATA2;                 // Next state: DATA2
    }
    else {
        buffer.Error = ERR_BUFF_DT1;            // Error in DATA1 state
        buffer.State = STATE_ERROR;
    }
}


void cpCheckData2(uint8_t charToParse) {
    if((charToParse & mskSTS) != mskSTS) {      // if MSb clear
        buffer.Message[buffer.State] = charToParse;
        buffer.State = STATE_STATUS;            // Finished, next state: STATUS
        buffer.Ready = 1;                       // Ready to parse message
    }
    else {
        buffer.Error = ERR_BUFF_DT2;            // Error in DATA2 state
        buffer.State = STATE_ERROR;
    }
}

void cpBufferError(uint8_t charToParse) {
    buffer.State = STATE_STATUS;
    messageOut.Command = ERR;                   // Error in:
    messageOut.Argument = ERR_BUFF;             //  - Buffer
    messageOut.Data.asByte[1] = ERR_BUFF_SEC;   // Error description:
    messageOut.Data.asByte[0] = charToParse;    //  - Invalid secuence

    cpResponse();
}


/// Parse functions

void cpParseMessage() {
    messageIn.Command = (buffer.Message[STATE_STATUS] & mskCMD);
    messageIn.Argument = (buffer.Message[STATE_STATUS] & mskARG);
    messageOut = messageIn;

    switch(messageIn.Command) {
        case CMD_MODE:    // Mode:
            cpParseMode(messageIn.Argument);
            break;

        case CMD_MOVE:   // Move:
            cpParseMove(messageIn.Argument);
            break;

        case CMD_GET:   // Get
            cpParseGet(messageIn.Argument);
            break;

        case CMD_SET:   // Set
            cpParseSet(messageIn.Argument);
            break;

        case CMD_SET_TUNE:  // TUne PID
            cpParseSetTune(messageIn.Argument);
            break;

        case CMD_GET_TUNE:
            cpParseGetTune(messageIn.Argument);
            break;

        default:
            break;
    }

    // Clear buffer
    buffer.Message[STATE_STATUS] = 0;
    buffer.Message[STATE_DATA1] = 0;
    buffer.Message[STATE_DATA2]= 0;
    // Update flags
    buffer.Ready = 0;
    buffer.State = STATE_STATUS;
}



void cpParseMode(uint8_t mode) {
    if(mode >= 1 && mode <= 4) {
        uint8_t currentMode = fcGetModeState();

        if(currentMode != mode) {
           fcSetNewModeState(mode);
        }
        messageOut.Data.asByte[0] = currentMode;
        messageOut.Data.asByte[1] = mode;
    }
    else {
        messageOut.Command = ERR;           // Error in:
        messageOut.Argument = ERR_MODE;     //  - MODE
        messageOut.Data.asByte[0] = ERR_MODE_NOCHANGE;   // Error description:
        messageOut.Data.asByte[1] = mode;   //  - Not a valid option
    }
    cpResponse();
}


void cpParseMove(uint8_t move) {
    messageIn.Data.asWord = buffer.Message[STATE_DATA1];
    messageIn.Data.asWord = (messageIn.Data.asWord << 7);
    messageIn.Data.asWord = (messageIn.Data.asWord | buffer.Message[STATE_DATA2]);

    switch(move){
        case MOVE_FORWARDS:
            ctrlSetAngle(0);
            ctrlSetDistance(messageIn.Data.asWord);
            ctrlFlag.computeDistanceControl = 1;
            ctrlFlag.computeAngle = 1;
//            ctrlGetSetPoint(pidDistance, &messageOut.Data.asWord);
//            messageOut.Data.asWord = SetPoint.Distance;
            break;

        case MOVE_LEFT:
            break;

        case MOVE_RIGHT:
            break;

        case MOVE_STOP:
            break;

        default:
            messageOut.Command = ERR;           // Error in:
            messageOut.Argument = ERR_MOVE;     //  - MOVE
            messageOut.Data.asByte[0] = move;   // Error description:
            messageOut.Data.asByte[1] = move;   //  - Not a valid option
            break;
    }
    cpResponse();
}


void cpParseGet(uint8_t get) {
    uint8_t dataType = buffer.Message[STATE_DATA2];

    switch(get) {
        case GET_OK:
            messageOut.Data.asByte[0] = (uint8_t)'O';     // "OK"
            messageOut.Data.asByte[1] = (uint8_t)'K';
            break;

        case GET_MODE: {
            messageOut.Data.asByte[0] = fcGetModeState(); // State
            messageOut.Data.asByte[1] = fcGetModeState();
            break;
        }

        case GET_L_CURR: {     // [0x03]H = Left Motor Current
            messageOut.Data.asWord = robotVar.motorCurrent[wheel.left];
            break;
        }

        case GET_R_CURR: {     // [0x04]H = Right Motor Current
            messageOut.Data.asWord = robotVar.motorCurrent[wheel.right];
            break;
        }

        case GET_WL_VEL: {     // [0x05]H = Left Wheel Speed
            getSpeed[dataType](wheel.left);
            break;
        }

        case GET_WL_DESP: {    // [0x06]H = Left Wheel Traveled distance
            getDesp[dataType](wheel.left);
            break;
        }

        case GET_WR_VEL: {     // [0x07]H = Right Wheel Speed
            getSpeed[dataType](wheel.right);
            break;
        }

        case GET_WR_DESP: {    // [0x08]H = Right Wheel Traveled distance
            getDesp[dataType](wheel.right);
            break;
        }

        case GET_R_VEL: {      // [0x09]H = Robot Speed
            break;
        }

        case GET_R_X: {      // [0x0A]H = Robot Position
            messageOut.Data.asWord = robot.pose.x;
            break;
        }

        case GET_R_Y: {      // [0x0A]H = Robot Position
            messageOut.Data.asWord = robot.pose.y;
            break;
        }

        case GET_R_THETA: {       // [0x0B]H = Robot Orientation
            messageOut.Data.asWord = robot.pose.theta;
            break;
        }

        case GET_R_DIST: {      // [0x0A]H = Robot Position
            messageOut.Data.asWord = robot.pose.distance;
            break;
        }

        default:
            messageOut.Command = ERR;           // Error in:
            messageOut.Argument = ERR_GET;      //  - GET
            messageOut.Data.asByte[0] = ERR_OP; // Error description:
            messageOut.Data.asByte[1] = get;    //  - Not a valid option
            break;
    }
    cpResponse();
}


void cpParseSet(uint8_t set) {
    if (fcGetModeState() != MODE_AUTO) { // Only if not in AUTO mode

        messageIn.Data.asWord = buffer.Message[STATE_DATA1];
        messageIn.Data.asWord = (messageIn.Data.asWord << 7);
        messageIn.Data.asWord = (messageIn.Data.asWord | buffer.Message[STATE_DATA2]);

        switch(set) {
            case SET_ROBOT_PARAM: {
                break;
            }

            case SET_PWM_L: {
                pwmSetDCpc(1, (messageIn.Data.asWord));   // Set PWM on Left wheel (-1,1)
                messageOut.Data = messageIn.Data;
                break;
            }
            case SET_PWM_R: {
                pwmSetDCpc(2, (messageIn.Data.asWord));   // Set PWM on Right wheel (-1,1)
                messageOut.Data = messageIn.Data;
                break;
            }

            case SET_FREQ: {                    // Set PWM Frequency
                pwmSetFreq(messageIn.Data.asWord << 1);   // Freq data received as freq/2
                messageOut.Data.asWord = P1TPERbits.PTPER;
                break;
            }

            case SET_WL_POS_SPEED: {
                ctrlSetSpeed(pidLeft, messageIn.Data.asWord);
                ctrlGetSetPoint(pidLeft, &messageOut.Data.asWord);
                break;
            }


            case SET_WR_POS_SPEED: {
                ctrlSetSpeed(pidRight, messageIn.Data.asWord);
                ctrlGetSetPoint(pidRight, &messageOut.Data.asWord);
                break;
            }


             case SET_WL_NEG_SPEED: {
                ctrlSetSpeed(pidLeft, _Q15neg(messageIn.Data.asWord));    // Make it negative
                ctrlGetSetPoint(pidLeft, &messageOut.Data.asWord);
                break;
            }


            case SET_WR_NEG_SPEED: {
                ctrlSetSpeed(pidRight, _Q15neg(messageIn.Data.asWord));   // Make it negative
                ctrlGetSetPoint(pidRight, &messageOut.Data.asWord);
                break;
            }

            case SET_USE_RAMP:
                ctrlFlag.useAccelRamp = messageIn.Data.asByte[1];
                break;

            case SET_ANGLE: {
                break;
            }


            case SET_DISTANCE: {
                break;
            }

            case SET_FF: {
                ctrlSetSpeed(pidRight, messageIn.Data.asWord);
                ctrlSetSpeed(pidLeft, messageIn.Data.asWord);
                break;
            }


            default:
                messageOut.Command = ERR;           // Error in:
                messageOut.Argument = ERR_SET;      //  - SET
                messageOut.Data.asByte[0] = ERR_OP; // Error description:
                messageOut.Data.asByte[1] = set;    //  - Not a valid option
                break;
        }
    }
    else {
        messageOut.Command = ERR;           // Error:
        messageOut.Argument = ERR_SET;      //  - in SET
        messageOut.Data.asByte[0] = ERR_SET_NOTAUTO;    // Error description:
        messageOut.Data.asByte[1] = fcGetModeState();   //  - Not in AUTO mode
    }

    cpResponse();
}


void cpParseSetTune(uint8_t tune) {
    if (fcGetModeState() == MODE_TUNE) { // Only if in TUNE mode

        messageIn.Data.asWord = buffer.Message[STATE_DATA1];
        messageIn.Data.asWord = (messageIn.Data.asWord << 7);
        messageIn.Data.asWord = (messageIn.Data.asWord | buffer.Message[STATE_DATA2]);

        switch(tune) {
            case TUNE_GAIN_LW_P: {
                ctrlSetGain(pidLeft, kp, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_LW_I: {
                ctrlSetGain(pidLeft, ki, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_LW_D: {
                ctrlSetGain(pidLeft, kd, messageIn.Data.asWord);
                break;
            }


            case TUNE_GAIN_RW_P: {
                ctrlSetGain(pidRight, kp, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_RW_I: {
                ctrlSetGain(pidRight, ki, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_RW_D: {
                ctrlSetGain(pidRight, kd, messageIn.Data.asWord);
                break;
            }


            case TUNE_GAIN_AN_P: {
                ctrlSetGain(pidOrientation, kp, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_AN_I: {
                ctrlSetGain(pidOrientation, ki, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_AN_D: {
                ctrlSetGain(pidOrientation, kd, messageIn.Data.asWord);
                break;
            }


            case TUNE_GAIN_DT_P: {
                ctrlSetGain(pidDistance, kp, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_DT_I: {
                ctrlSetGain(pidDistance, ki, messageIn.Data.asWord);
                break;
            }

            case TUNE_GAIN_DT_D: {
                ctrlSetGain(pidDistance, kd, messageIn.Data.asWord);
                break;
            }


            default:
                messageOut.Command = ERR;            // Error in:
                messageOut.Argument = ERR_TUNE;      //  - TUNE
                messageOut.Data.asByte[0] = ERR_OP;  // Error description:
                messageOut.Data.asByte[1] = tune;    //  - Not a valid option
                break;
        }
    }
    else {
        messageOut.Command = ERR;               // Error:
        messageOut.Argument = ERR_TUNE;         //  - in TUNE
        messageOut.Data.asByte[0] = ERR_TUNE;   // Error description:
        messageOut.Data.asByte[1] = ERR_TUNE;   //
    }

    cpResponse();
}

void cpParseGetTune(uint8_t getTune) {
    if (fcGetModeState() == MODE_TUNE || fcGetModeState() == MODE_AUTO) { // Only if in TUNE mode

        messageIn.Data.asWord = buffer.Message[STATE_DATA1];
        messageIn.Data.asWord = (messageIn.Data.asWord << 7);
        messageIn.Data.asWord = (messageIn.Data.asWord | buffer.Message[STATE_DATA2]);

        switch(getTune) {
            /* Control reference (Set point)*/
            case GET_TUNE_SP_LW: {
                ctrlGetSetPoint(pidLeft, &messageOut.Data.asWord);
                break;
            }

            case GET_TUNE_SP_RW: {
                ctrlGetSetPoint(pidRight, &messageOut.Data.asWord);
                break;
            }

            case GET_TUNE_SP_AN: {
                ctrlGetSetPoint(pidOrientation, &messageOut.Data.asWord);
                break;
            }


            case GET_TUNE_SP_DT: {
                ctrlGetSetPoint(pidDistance, &messageOut.Data.asWord);
                break;
            }

            /* Measured Output (error)*/
            case GET_TUNE_ER_LW: {
                ctrlGetMeasuredOutput(pidLeft, &messageOut.Data.asWord);
                break;
            }

            case GET_TUNE_ER_RW: {
                ctrlGetMeasuredOutput(pidRight, &messageOut.Data.asWord);
                break;
            }


            case GET_TUNE_ER_AN: {
                ctrlGetMeasuredOutput(pidOrientation, &messageOut.Data.asWord);
                break;
            }

            case GET_TUNE_ER_DT: {
                ctrlGetMeasuredOutput(pidDistance, &messageOut.Data.asWord);
                break;
            }

            /* Control Output*/
            case GET_TUNE_O_LW: {
                ctrlGetControlOutput(pidLeft, &messageOut.Data.asWord);
                break;
            }


            case GET_TUNE_O_RW: {
                ctrlGetControlOutput(pidRight, &messageOut.Data.asWord);
                break;
            }

            case GET_TUNE_O_AN: {
                ctrlGetControlOutput(pidOrientation, &messageOut.Data.asWord);
                break;
            }

            case GET_TUNE_O_DT: {
                ctrlGetControlOutput(pidDistance, &messageOut.Data.asWord);
                break;
            }

            default:
                messageOut.Command = ERR;            // Error in:
                messageOut.Argument = ERR_TUNE;      //  - TUNE
                messageOut.Data.asByte[0] = ERR_OP;  // Error description:
                messageOut.Data.asByte[1] = getTune;    //  - Not a valid option
                break;
        }
    }
    else {
        messageOut.Command = ERR;               // Error:
        messageOut.Argument = ERR_TUNE;         //  - in TUNE
        messageOut.Data.asByte[0] = ERR_TUNE;   // Error description:
        messageOut.Data.asByte[1] = ERR_TUNE;   //
    }

    cpResponse();
}

/// Auxiliary functions
uint8_t cpGetBufferState() {
    return buffer.Ready;
}

void cpSpeedPeriod(uint8_t wheel) {
    messageOut.Data.asWord = isrVar.icPeriod[wheel];
}


void cpSpeedWheel(uint8_t wheel) {
    messageOut.Data.asWord = robotVar.wheelSpeed[wheel];
}


void cpDespPulses(uint8_t wheel) {
    rGetWheelPosition(wheel, DESP_PULSES, &messageOut.Data.asWord);
}


void cpDespWheelCM(uint8_t wheel){
    rGetWheelPosition(wheel, DESP_WHEEL_CM, &messageOut.Data.asWord);
}

void cpDespWheelP(uint8_t wheel){
    rGetWheelPosition(wheel, DESP_WHEEL_P, &messageOut.Data.asWord);
}


void cpResponse() {
    uint8_t bufferOut[BUFFER_SIZE];
    bufferOut[0] = (messageOut.Command | messageOut.Argument);
    bufferOut[1] = messageOut.Data.asByte[0];
    bufferOut[2] = messageOut.Data.asByte[1];

    outChar(bufferOut[0]);
    outChar(bufferOut[1]);
    outChar(bufferOut[2]);
}