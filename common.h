#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "config.h"
#include <string.h>
#include <stdio.h>

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ATMEGA_64

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
#define F_CPU 8000000UL
#define CRYSTAL_FREKANS 16000000UL

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

