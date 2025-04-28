#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ATMEGA_64


#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#define qword unsigned long long
    
    
#define _XTAL_FREQ 64000000
#define F_CPU 16000000UL
#define CRYSTAL_FREKANS 16000000

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

