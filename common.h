#define PIC_18F87K22
#define PIC

#include <xc.h>
#include "config.h"
#include <string.h>
#include <stdio.h>

#ifdef PIC
#include "pic18.h"
#endif

#ifdef ATMEGA
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

#define _XTAL_FREQ 64000000
#define F_CPU 16000000UL
#define CRYSTAL_FREKANS 64000000UL

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

