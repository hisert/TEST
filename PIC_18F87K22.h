/* 
 * File:   PIC_18F87K22.h
 * Author: SERT
 *
 * Created on 27 Nisan 2025 Pazar, 22:44
 */

#ifndef PIC_18F87K22_H
#define	PIC_18F87K22_H

#ifdef	__cplusplus
extern "C" {
#endif

#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#define qword unsigned long long
#define _XTAL_FREQ 64000000

    byte PIN_GET_PORT(byte Port, byte Pin);
    void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow);
    void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput);
    void PIN_SET_LAT_TOGGLE(byte Port, byte Pin);
    void PIN_SET_ANSEL(byte Pin, byte OnOFF);
    void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);
    void PIN_IOC_INTERRUPT(byte Pin, byte openOrClose);

    void TIMER_1_INTERRUPT_FUNCT();
    void TIMER_1_INTERRUPT(byte openOrClose);
    void TIMER_1_SET(byte startOrStop);
    word TIMER_1_INIT(byte ms);

    void TIMER_3_INTERRUPT_FUNCT();
    void TIMER_3_INTERRUPT(byte openOrClose);
    void TIMER_3_SET(byte startOrStop);
    word TIMER_3_INIT(byte ms);

    void TIMER_5_INTERRUPT_FUNCT();
    void TIMER_5_INTERRUPT(byte openOrClose);
    void TIMER_5_SET(byte startOrStop);
    word TIMER_5_INIT(byte ms);

    void UART_1_INTERRUPT(byte openOrClose);
    void UART_1_INIT(unsigned long baudrate);
    void UART_1_BYTE(char data);
    void UART_1_STRING(char* text);
    void UART_1_DECIMAL(dword val);

    void UART_2_INTERRUPT(byte openOrClose);
    void UART_2_INIT(unsigned long baudrate);
    void UART_2_BYTE(char data);
    void UART_2_STRING(char* text);
    void UART_2_DECIMAL(dword val);

    void SET_OSC(byte MHz);
    void INTERRUPT_ALL(byte openOrClose);

    void ADC_INIT();
    unsigned int ADC_READ(unsigned char channel);

    void I2C_1_INIT(unsigned long baudrate);
    void I2C_1_ACK(void);
    void I2C_1_NACK(void);
    void I2C_1_READY(void);
    byte I2C_1_WRITE(byte data);
    void I2C_1_START(void);
    byte I2C_1_STOP(void);
    byte I2C_1_READ(byte flag);

    void I2C_2_INIT(unsigned long baudrate);
    void I2C_2_ACK(void);
    void I2C_2_NACK(void);
    void I2C_2_READY(void);
    byte I2C_2_WRITE(byte data);
    void I2C_2_START(void);
    byte I2C_2_STOP(void);
    byte I2C_2_READ(byte flag);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC_18F87K22_H */

