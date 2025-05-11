#include <xc.h>
#include "config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

#if defined(__18F67K40) || (__18F65K40) || (__18F46K22) || (__18F87K22)
#include "pic18.h"
#endif
#define USE_REGISTER
#define USE_SOFT_I2C
#define USE_LCD_12C

#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#endif

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FLAG_JOIN(TASK_REG,TASK)      TASK_REG = TASK_REG | TASK
#define FLAG_ERASE(TASK_REG,TASK)     TASK_REG =TASK_REG & ~TASK
#define FLAG_CONTROL(TASK_REG,TASK)     TASK_REG & TASK

#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#define qword unsigned long long

#define open 1
#define close 0
#define TERSLE(DAT) DAT= ~DAT
#define SET_BIT(reg,bit) (reg = reg | (1 << bit))
#define CLR_BIT(reg,bit) (reg = reg & ~(1 << bit))
#define TOGGLE_BIT(reg,bit) (reg = reg ^ (1 << bit))
#define CHECK_BIT(reg,bit) ((reg & (1 << bit)) / (1 << bit))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define _XTAL_FREQ 64000000
#define F_CPU 8000000UL
#define CRYSTAL_FREKANS 8000000UL

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

