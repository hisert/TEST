#include "common.h"

#ifndef ATMEGA_88_H
#define	ATMEGA_88_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef __AVR_ATmega88__
    // <editor-fold defaultstate="collapsed" desc="PWM DEFINE    ">
#define SYSTEM_PWM_PRESCALE_0 1
#define SYSTEM_PWM_PRESCALE_8 2
#define SYSTEM_PWM_PRESCALE_64 3
#define SYSTEM_PWM_PRESCALE_256 4
#define SYSTEM_PWM_PRESCALE_1024 5
#define SYSTEM_PWM_DUTY_FAST 2
#define SYSTEM_PWM_DUTY_SLOW 1
#define SYSTEM_PWM_FREQ 0
    // </editor-fold> //-->>GENERAL

    byte PIN_GET_PORT(byte Port, byte Pin);
    void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow);
    void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput);
    void PIN_SET_LAT_TOGGLE(byte Port, byte Pin);
    void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);

    void TIMER_0_INTERRUPT_FUNCT();
    void TIMER_0_INTERRUPT(byte openOrClose);
    void TIMER_0_SET(byte startOrStop);
    void TIMER_0_INIT(byte ms);

    void TIMER_1_INTERRUPT_FUNCT();
    void TIMER_1_INTERRUPT(byte openOrClose);
    void TIMER_1_SET(byte startOrStop);
    void TIMER_1_INIT(byte ms);

    void TIMER_2_INTERRUPT_FUNCT();
    void TIMER_2_INTERRUPT(byte openOrClose);
    void TIMER_2_SET(byte startOrStop);
    void TIMER_2_INIT(byte ms);

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

    void EEPROM_B_WRITE(word address, byte data);
    byte EEPROM_B_READ(word address);

    void UART_1_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_1_INTERRUPT_FUNCT_POINTER_t)(byte));
    void TIMER_2_INTERRUPT_CONNECT(word ms, void(*TIMER_2_INTERRUPT_FUNCT_POINTER_t)(void));
    void TIMER_1_INTERRUPT_CONNECT(word ms, void(*TIMER_1_INTERRUPT_FUNCT_POINTER_t)(void));
    void TIMER_0_INTERRUPT_CONNECT(word ms, void(*TIMER_0_INTERRUPT_FUNCT_POINTER_t)(void));
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* ATMEGA_88_H */

