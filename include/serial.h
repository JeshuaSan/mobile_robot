#ifndef SERIAL_H
#define	SERIAL_H

#include <stdint.h>
#include "chip.h"
#include "libconfig.h"



// Consistency check
#if (DEFAULT_UART > NUM_UART_MODS) || (DEFAULT_UART < 1)
#error Invalid choice of DEFAULT_UART
#endif



uint8_t inChar(void);  //blocking single character input
void outString(const char* psz_s);
uint16_t inString (char *psz_buff, int16_t u16_maxCount);
uint16_t inStringEcho (char *psz_buff, int16_t u16_maxCount);
void outChar(uint8_t u8_c);
void outUint8NoLeader (uint8_t u8_x);
void outUint8 (uint8_t u8_x);
void outUint16(uint16_t u16_x);
void outUint32(uint32_t u32_x);
void outUint8Decimal(uint8_t u8_x);
void outUint16Decimal(uint16_t u16_x);
void outInt16( uint16_t u16_x );

void outResponse(uint8_t command, uint8_t argument, uint8_t data1, uint8_t data2);

uint8_t isCharReady(void); //determine if character is available to be read

uint8_t inCharEcho(void);
void configDefaultUART(uint32_t u32_baudRate);

#endif	/* SERIAL_H */

