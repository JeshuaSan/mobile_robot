/* 
 * File:   adc.h
 * Author: Jesus
 *
 * Created on April 8, 2013, 11:11 AM
 */

#ifndef ADC_H
#define	ADC_H

#include "include/chip.h"
#include "include/ports.h"
#include <stdint.h>


void adcConfig();
void adcComputeCurrent(uint8_t nSample, int* adcBuffer);
void adcGetCurrent(void);
void adcON(void);
void adcOFF(void);

#endif	/* ADC_H */

