#include "common.h"

#ifndef ATMEGA_64_H
#define	ATMEGA_64_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef ATMEGA_64

    // <editor-fold defaultstate="collapsed" desc="GPIO DEFINE">
#define SYSTEM_IO_OUTPUT 'O'
#define SYSTEM_IO_INPUT 'I'
#define SYSTEM_IO_DIGITAL 'D'
#define SYSTEM_IO_ANALOG 'A'
#define SYSTEM_IO_HIGH 'H'
#define SYSTEM_IO_LOW 'L'
#define SYSTEM_IO_PORT_A 'A'
#define SYSTEM_IO_PORT_B 'B'
#define SYSTEM_IO_PORT_C 'C'
#define SYSTEM_IO_PORT_D 'D'
#define SYSTEM_IO_PORT_E 'E'
#define SYSTEM_IO_PORT_F 'F'
#define SYSTEM_IO_PORT_G 'G'
    // </editor-fold> 

    // <editor-fold defaultstate="collapsed" desc="PWM DEFINE ">
#define SYSTEM_PWM_PRESCALE_0 1
#define SYSTEM_PWM_PRESCALE_8 2
#define SYSTEM_PWM_PRESCALE_32 3
#define SYSTEM_PWM_PRESCALE_64 4
#define SYSTEM_PWM_PRESCALE_128 5
#define SYSTEM_PWM_PRESCALE_256 6
#define SYSTEM_PWM_PRESCALE_1024 7
#define SYSTEM_PWM_FAST 1
#define SYSTEM_PWM_SLOW 0
    // </editor-fold> 

    byte PIN_GET_PORT(byte Port, byte Pin);
    void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow);
    void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput);
    void PIN_SET_LAT_TOGGLE(byte Port, byte Pin);
    void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);


    void TIMER_1_INTERRUPT_FUNCT();
    void TIMER_1_INTERRUPT(byte openOrClose);
    void TIMER_1_SET(byte startOrStop);
    void TIMER_1_INIT(byte ms);

    void TIMER_3_INTERRUPT_FUNCT();
    void TIMER_3_INTERRUPT(byte openOrClose);
    void TIMER_3_SET(byte startOrStop);
    void TIMER_3_INIT(byte ms);

    void UART_0_INTERRUPT(byte openOrClose);
    void UART_0_INIT(unsigned long baudrate);
    void UART_0_BYTE(char data);
    void UART_0_STRING(const char* text);
    void UART_0_DECIMAL(dword val);

    void UART_1_INTERRUPT(byte openOrClose);
    void UART_1_INIT(unsigned long baudrate);
    void UART_1_BYTE(char data);
    void UART_1_STRING(const char* text);
    void UART_1_DECIMAL(dword val);

    void ADC_INIT();
    word ADC_READ(unsigned char channel);

    void I2C_1_INIT();
    byte I2C_1_READ_ACK();
    byte I2C_1_READ_NACK();
    byte I2C_1_WRITE(byte data);
    void I2C_1_START();
    void I2C_1_STOP();

    void INTERRUPT_ALL(byte openOrClose);

#endif

#ifdef	__cplusplus
}
#endif

#endif	/* ATMEGA_64_H */

