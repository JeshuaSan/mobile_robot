#include "../include/clockfreq.h"


//default config bits, use these if a processor is not defined.
#ifndef CONFIG_BITS_DEFINED
#ifdef __PIC24H__
_FBS(BWRP_WRPROTECT_OFF);
_FGS(GSS_OFF & GCP_OFF & GWRP_OFF);

#ifdef RSS_NO_RAM
_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF);
#endif

#ifdef IOL1WAY_OFF
_FOSC(FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_SEL);
#else
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_SEL);
#endif
_FOSCSEL(FNOSC_FRC & IESO_OFF);
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS512);
_FPOR(FPWRT_PWR16);
_FICD(JTAGEN_OFF & ICS_PGD1);

#warning Using default config bit settings for the PIC24H family.
#warning Edit this file to define bits for your processor!
///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond
#endif


#ifdef __dsPIC33F__
_FBS(BWRP_WRPROTECT_OFF);
_FGS(GSS_OFF & GCP_OFF & GWRP_OFF);
_FOSCSEL(FNOSC_FRC & IESO_OFF);
#ifdef RSS_NO_RAM
_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF);
#endif
#ifdef IOL1WAY_OFF
_FOSC(FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_SEL);
#else
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_SEL);
#endif
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS512);
_FPOR(FPWRT_PWR64 & PWMPIN_ON & HPOL_ON & LPOL_ON);
_FICD(JTAGEN_OFF & ICS_PGD1 & 0xFFEF);
//#warning Using default config bit settings for the dsPIC33F family.
//#warning Edit this file to define bits for your processor!

#define CONFIG_BITS_DEFINED

#endif



#endif


#ifndef CONFIG_BITS_DEFINED
#error Edit 'common/dspic33_configbits.c' to add config bits for your processor!
#endif
