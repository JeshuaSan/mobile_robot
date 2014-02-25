#include "../include/serial.h"
#include "../include/uart.h"
#include "../include/unittest.h"
#include <libpic30.h>



void outChar(uint8_t u8_c) {
      outChar1(u8_c);
}


void outString(const char* psz_s) {
  while (*psz_s) {

#if (SERIAL_EOL_DEFAULT==SERIAL_EOL_CR_LF)
    if (*psz_s == '\n') outChar(0x0D);
    outChar(*psz_s);
#endif
#if (SERIAL_EOL_DEFAULT==SERIAL_EOL_CR)
    if (*psz_s == '\n') outChar(0x0D);
    else outChar(*psz_s);
#endif
#if (SERIAL_EOL_DEFAULT==SERIAL_EOL_LF)
//no translation
    outChar(*psz_s);
#endif
    psz_s++;
  }
}




static uint16_t inStringInternal (char *psz_buff, uint16_t u16_maxCount, uint8_t echoFlag) {
  uint8_t u8_c;
  uint16_t u16_i;

  if (!u16_maxCount) return 0;
  u16_i = 0;
  for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
    if (echoFlag) u8_c = inCharEcho();
    else u8_c = inChar();
    if (u8_c == '\n' ||u8_c == '\r' ) break; //terminate loop
    *psz_buff = u8_c; //save character
    psz_buff++;
  }
  //stop reading, terminate, return characters read.
  *psz_buff = 0;
  return(u16_i);
}

/**
Reads a string into psz_buff, assumes psz_buff can
hold at least u16_maxCount+1 characters. String reading
halts when either a newline or carriage return is read, or u16_maxCount
characters is read. The return string is always null-terminated.
The return count does not includes the null terminator.
An input string of just '\n' returns a null string.
\param psz_buff pointer to buffer for storing string read from console
\param u16_maxCount maximum number of characters to read from console.
*/
uint16_t inString (char *psz_buff, int16_t u16_maxCount) {
  return inStringInternal(psz_buff,u16_maxCount,0);
}

/**
Same as inString(), except echoes characters to console as they are read.
*/
uint16_t inStringEcho (char *psz_buff, int16_t u16_maxCount) {
  return inStringInternal(psz_buff,u16_maxCount,1);
}


void outUint8NoLeader(uint8_t u8_x) {
  uint8_t u8_c;
  u8_c = (u8_x>>4)& 0xf;
  if (u8_c > 9) outChar('A'+u8_c-10);
  else outChar('0'+u8_c);
  //LSDigit
  u8_c= u8_x & 0xf;
  if (u8_c > 9) outChar('A'+u8_c-10);
  else outChar('0'+u8_c);
}

/**
Output u8_x as formatted hex value with leading "0x".
\param u8_x value to output.
*/
void outUint8(uint8_t u8_x) {
  outString("0x");
  outUint8NoLeader(u8_x);
}

/**
Output u16_x as formatted hex value with leading "0x".
\param u16_x value to output.
*/
void outUint16(uint16_t u16_x) {
  uint8_t u8_c;

  outString("0x");
  u8_c = (u16_x >> 8);
  outUint8NoLeader(u8_c);
  u8_c = (uint8_t) u16_x;
  outUint8NoLeader(u8_c);
}

/**
Output u32_x as formatted hex value with leading "0x".
\param u32_x value to output.
*/
void outUint32(uint32_t u32_x) {
  uint8_t u8_c;
  outString("0x");
  u8_c = (u32_x >> 24);
  outUint8NoLeader(u8_c);
  u8_c = (u32_x >> 16);
  outUint8NoLeader(u8_c);
  u8_c = (u32_x >> 8);
  outUint8NoLeader(u8_c);
  u8_c = u32_x;
  outUint8NoLeader(u8_c);
}

/**
Output u8_x as decimal value.
\param u8_x value to output.
*/
void outUint8Decimal( uint8_t u8_x ) {
  static const uint8_t  u8_d[]= {50, 30, 20, 10, 5, 3, 2, 1 };
  static const uint8_t  u8_f[]= {5, 3, 2, 1, 5, 3, 2, 1 };

  char      psz_out[5];
  uint8_t     u8_i, u8_destroy;

  u8_i = 0;
  u8_destroy = u8_x;
  psz_out[0] = '0';
  psz_out[1] = '0';
  psz_out[2] = '0';
  psz_out[3] = 0;
  if (u8_destroy >= 200) {
    psz_out[0] += 2;
    u8_destroy -= 200;
  } // end if()
  if (u8_destroy >= 100) {
    psz_out[0] += 1;
    u8_destroy -= 100;
  } // end if()
  for (u8_i=0; u8_i<8; u8_i++) {
    if (u8_destroy >= u8_d[u8_i]) {
      psz_out[1+(u8_i/4)] += u8_f[u8_i];
      u8_destroy -= u8_d[u8_i];
    }
  } //end for()
  psz_out[3] = 0;
  outString( psz_out );
}

/**
Output u16_x as decimal value.
\param u16_x value to output.
*/
void outUint16Decimal( uint16_t u16_x ) {
  static const uint16_t  u16_d[]= {50000, 30000, 20000, 10000, 5000, 3000, 2000, 1000, \
                                   500, 300, 200, 100, 50, 30, 20, 10, 5, 3, 2, 1
                                  };
  static const uint8_t   u8_f[]= {5, 3, 2, 1 };

  uint8_t     u8_i;
  uint16_t    u16_destroy;
  char      psz_out[5];

  u8_i = 0;
  u16_destroy = u16_x;
  psz_out[0] = '0';
  psz_out[1] = '0';
  psz_out[2] = '0';
  psz_out[3] = '0';
  psz_out[4] = '0';

  for (u8_i=0; u8_i<20; u8_i++) {
    if (u16_destroy >= u16_d[u8_i]) {
      psz_out[u8_i/4] += u8_f[u8_i % 4];
      u16_destroy -= u16_d[u8_i];
    }
  } //end for()
  psz_out[5] = 0;
  outString( psz_out );
}

void outInt16( uint16_t u16_x ){
    outChar( u16_x >> 8 );
    outChar( u16_x );
}

/** Read a character from the serial port.
 *  This function blocks until a character is
 *  read.
 *  The serial port used is selected by the
 *  __C30_UART variable, which defaults to 1.
 *  \return Character read from the serial port.
 */
uint8_t inChar(void) {
//  switch (__C30_UART) {
//#if (NUM_UART_MODS >= 1)
//    case 1 :
      return inChar1();
//#endif
//#if (NUM_UART_MODS >= 2)
//    case 2 :
//      return inChar2();
//#endif
//#if (NUM_UART_MODS >= 3)
//    case 3 :
//      return inChar3();
//#endif
//#if (NUM_UART_MODS >= 4)
//    case 4 :
//      return inChar4();
//#endif
//    default :
//      REPORT_ERROR("Invalid UART");
//      return 0;
//  }
}

/**
Same as inChar(), except echo character that is back to console
*/

uint8_t inCharEcho(void) {
  uint8_t u8_c;
  u8_c = inChar(); //get character
  outChar(u8_c);   //echo
  return u8_c;
}

/** Determine if a character is ready to be read
 *  from the serial port.
 *  \return non-zero value if character is ready, zero otherwise..
 */
uint8_t isCharReady(void) {
//  switch (__C30_UART) {
//#if (NUM_UART_MODS >= 1)
//    case 1 :
      return isCharReady1();
//#endif
//#if (NUM_UART_MODS >= 2)
//    case 2 :
//      return isCharReady2();
//#endif
//#if (NUM_UART_MODS >= 3)
//    case 3 :
//      return isCharReady3();
//#endif
//#if (NUM_UART_MODS >= 4)
//    case 4 :
//      return isCharReady4();
//#endif
//    default :
//      REPORT_ERROR("Invalid UART");
//      return 0;
//  }
}



/** Configures a UART based compiler setting of DEFAULT_UART
 *  and sets __C30_UART to the default UART.
 *  If you want to configure a different UART, then call the configUARTx function explicitly.
 *  \param u32_baudRate The baud rate to use.
 */
void configDefaultUART(uint32_t u32_baudRate) {
      __C30_UART = 1;   //this is the default UART
      configUART1(u32_baudRate);
}

/* Cstom*/
//void outResponse(uint8_t command, uint8_t argument, uint8_t data1, uint8_t data2){
//    enum {
//        _status,    // 0 = Status
//        _data1,     // 1 = Data1
//        _data2      // 2 = Data2
//    };
//
//    char bufferOut[3];
//    bufferOut[_status] = (command | argument);    // Status
//    bufferOut[_data1] = data1;
//    bufferOut[_data2] = data2;
//
//    outChar1(bufferOut[_status]);
//    outChar1(bufferOut[_data1]);
//    outChar1(bufferOut[_data2]);
//}

