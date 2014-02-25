/* 
 * File:   Commands.h
 * Author: Jesus
 *
 * Created on April 10, 2013, 10:03 PM
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#define DUMMY 0         // DUMMY constant for when there is no option=0

enum {
    mskSTS = 0x80,     // [0x80]H | [10000000]B = Status
    mskCMD = 0xF0,     // [0xF0]H | [11110000]B = Command
    mskARG = 0x0F      // [0x0F]H | [00001111]B = Argument
};



enum {    // [0xN0]: Command nibble
    CMD_MODE = 0xA0,   // [0xA0]H = Mode
    CMD_MOVE = 0xB0,   // [0xB0]H = Move
    CMD_SET  = 0xC0,   // [0xC0]H = Set
    CMD_GET  = 0xD0,   // [0xD0]H = Get
    CMD_SET_TUNE = 0XE0,   // [0xE0]H = Tune PID gains
                       // [0xF0]H = Error (only on answer)
    CMD_GET_TUNE = 0x90
};


typedef enum {
    MODE_AUTO = 0x01,   // [0x01]H = Auto: PID control on PWM
    MODE_MANUAL,        // [0x02]H = Manual: Direct control on PWM
    MODE_CHARACT,       // [0x03]H = Characteriztion: Motor characterization
    MODE_TUNE           // [0x04]H = Configuration: Parameter configuration
}ModeState;


enum {
    MOVE_FORWARDS = 0x01,   // [0x01]H =
    MOVE_LEFT,              // [0x02]H =
    MOVE_RIGHT,             // [0x03]H =
    MOVE_STOP               // [0x04]H =
};


enum {
    GET_OK = 0x01,  // [0x01]H = OK response
    GET_MODE,       // [0x02]H = Mode
    GET_L_CURR,     // [0x03]H = Left Motor Current
    GET_R_CURR,     // [0x04]H = Right Motor Current
    GET_WL_VEL,     // [0x05]H = Left Wheel Speed
    GET_WL_DESP,    // [0x06]H = Left Wheel Traveled distance
    GET_WR_VEL,     // [0x07]H = Right Wheel Speed
    GET_WR_DESP,    // [0x08]H = Right Wheel Traveled distance
    GET_R_VEL,      // [0x09]H = Robot Speed
    GET_R_X,        // [0x0A]H = Robot X Position
    GET_R_Y,        // [0x0B]H = Robot Y Position
    GET_R_THETA,    // [0x0C]H = Robot Theta
    GET_R_DIST,     // [0x0D]H = Robot Distance
};

enum {
    VEL_PERIOD,
    VEL_WHEEL
};

enum {
    DESP_PULSES,
    DESP_WHEEL_CM,
    DESP_WHEEL_P,
};


enum {
    SET_ROBOT_PARAM = 0x01, // [0x01]H =
    SET_PWM_L,              //
    SET_PWM_R,              //
    SET_FREQ,               // [0x04]H =
    SET_WL_POS_SPEED,       //
    SET_WR_POS_SPEED,       //
    SET_WL_NEG_SPEED,       //
    SET_WR_NEG_SPEED,       //
    SET_USE_RAMP,           //
    SET_ANGLE,              //
    SET_DISTANCE,           //
    SET_FF,
};

enum{
    TUNE_GAIN_LW_P = 0x01,  // [0x01]H =
    TUNE_GAIN_LW_I,         // [0x02]H =
    TUNE_GAIN_LW_D,         // [0x03]H =
    TUNE_GAIN_RW_P,         // [0X04]H =
    TUNE_GAIN_RW_I,         // [0X05]H =
    TUNE_GAIN_RW_D,         // [0x06]H =
    TUNE_GAIN_AN_P,         // [0x07]H =
    TUNE_GAIN_AN_I,         // [0x08]H =
    TUNE_GAIN_AN_D,         // [0x0A]H =
    TUNE_GAIN_DT_P,         // [0x0B]H =
    TUNE_GAIN_DT_I,         // [0x0C]H =
    TUNE_GAIN_DT_D,         // [0x0D]H =
};

enum{
    GET_TUNE_SP_LW = 0x01,  // [0x01]
    GET_TUNE_SP_RW,         // [0x02]
    GET_TUNE_SP_AN,         // [0x03]
    GET_TUNE_SP_DT,         // [0x04]
    GET_TUNE_ER_LW,         // [0x05]
    GET_TUNE_ER_RW,         // [0x06]
    GET_TUNE_ER_AN,         // [0x07]
    GET_TUNE_ER_DT,         // [0x08]
    GET_TUNE_O_LW,          // [0x09]
    GET_TUNE_O_RW,          // [0x0A]
    GET_TUNE_O_AN,          // [0x0B]
    GET_TUNE_O_DT,          // [0x0C]

};


enum {
    ERR = 0xF0,
};

enum {
    ERR_MODE = 0x0A,
    ERR_MOVE = 0x0B,
    ERR_SET = 0x0C,
    ERR_GET = 0x0D,
    ERR_TUNE = 0x0E,
    ERR_BUFF = 0x0F
};

enum {
    ERR_OP  = 0x01,     // [0x01]H = Not a valid option
    ERR_BUFF_SEC,       // [0x02]H = Invalid secuqnce
    ERR_MODE_NOCHANGE,  // [0x03]H = No change in mode
    ERR_MOVE_INV,           // []
    ERR_GET_INV,            //
    ERR_SET_NOTAUTO,            //  Not in AUTO mode
};

#endif	/* COMMANDS_H */

