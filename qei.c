#include "qei.h"

void qei1Config() {
    CONFIG_RB2_AS_DIG_INPUT();
    CONFIG_RB3_AS_DIG_INPUT();

    CONFIG_QEA1_TO_RP(2);
    CONFIG_QEB1_TO_RP(3);

    QEI1CONbits.QEIM = QEIMconfig.x2_MATCH;    //      QEI_MODE_x2_MATCH
    QEI1CONbits.SWPAB = SWAPABconfig.SWAP;    //      QEI_INPUTS_SWAP
    QEI1CONbits.QEISIDL     = 0;    //      QEI_IDLE_STOP
    QEI1CONbits.POSRES      = 0;    //      QEI_INDEX_RESET_DISABLE
    QEI1CONbits.PCDOUT = PCDOUTconfig.DISABLED;    //      QEI_NORMAL_IO
    QEI1CONbits.POSRES      = 0;    //      POS_CNT_ERR_INT_DISABLE

    DFLT1CONbits.QECK       = 6;    //      QEI_QE_CLK_DIVIDE_1_128
    DFLT1CONbits.QEOUT      = 1;    //      QEI_QE_OUT_ENABLE

    MAX1CNT = 0xFFFF;
    POS1CNT = 0;
}

void qei2Config() {
    CONFIG_RB4_AS_DIG_INPUT();
    CONFIG_RB5_AS_DIG_INPUT();

    CONFIG_QEA2_TO_RP(4);
    CONFIG_QEB2_TO_RP(5);

    QEI2CONbits.QEIM = QEIMconfig.x2_MATCH;    //      QEI_MODE_x2_MATCH
    QEI2CONbits.SWPAB = SWAPABconfig.NO_SWAP;    //      QEI_INPUTS_SWAP    !!!!!!!!!! no_swap only ON MICROSTICK !!!!!!!!!!!!!!
    QEI2CONbits.QEISIDL     = 0;    //      QEI_IDLE_STOP
    QEI2CONbits.POSRES      = 0;    //      QEI_INDEX_RESET_DISABLE
    QEI2CONbits.PCDOUT = PCDOUTconfig.DISABLED;    //      QEI_NORMAL_IO
    QEI2CONbits.POSRES      = 0;    //      POS_CNT_ERR_INT_DISABLE

    DFLT2CONbits.QECK       = 6;    //      QEI_QE_CLK_DIVIDE_1_128
    DFLT2CONbits.QEOUT      = 1;    //      QEI_QE_OUT_ENABLE

    MAX2CNT = 0xFFFF;
    POS2CNT = 0;
}
