/* 
 * File:   mcpwm.h
 * Author: Jesus
 *
 * Created on April 6, 2013, 10:41 AM
 */

#ifndef MCPWM_H
#define	MCPWM_H

#include "include/chip.h"
#include "include/ports.h"
#include <stdint.h>

void pwmConfig();
void pwmSetFreq(uint16_t frequency);
void pwmSetDC(uint16_t dutycycleReg, uint16_t dutycycle, uint8_t updatedisable);
void pwmSetDCpc(uint16_t dutycycleReg, uint16_t dutycyclePercentage);
void pwmSetDCfrac(uint16_t dutycycleReg, uint16_t dutycycleFracc);


#endif	/* MCPWM_H */

