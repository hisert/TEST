#include "common.h"
#ifndef PIC_18F46K22_H
#define	PIC_18F46K22_H

#ifdef	__cplusplus
extern "C" {
#endif
#ifdef __18F46K22


    // <editor-fold defaultstate="collapsed" desc="CONFIG           ">

#pragma config FOSC = HSMP      //INTIO7//HSMP   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = ON      // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = OFF    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)
#pragma config CCP2MX = PORTB3  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = OFF      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = INTMCLR  // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)
#pragma config STVREN = OFF      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)
#pragma config CPB = ON        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = ON        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)
    // </editor-fold> 
    // <editor-fold defaultstate="collapsed" desc="CRYSTAL">
#define SYSTEM_FREQ_INTERNAL_64 0x72
#define SYSTEM_FREQ_INTERNAL_48 0x62
#define SYSTEM_FREQ_INTERNAL_32 0x52
#define SYSTEM_FREQ_INTERNAL_16 0x70
#define SYSTEM_FREQ_INTERNAL_8 0x60
#define SYSTEM_FREQ_INTERNAL_4 0x50
#define SYSTEM_FREQ_INTERNAL_2 0x40
#define SYSTEM_FREQ_INTERNAL_1 0x30
#define SYSTEM_FREQ_INTERNAL 1
#define SYSTEM_FREQ_EXTERNAL 0

    // </editor-fold>


    void MCU_INIT(byte inorEx, byte mhz);
    void INTERRUPT_ALL(byte OpenOrClose);

    void EEPROM_B_WRITE(word address, byte data);
    byte EEPROM_B_READ(word address);

    byte PIN_GET_PORT(byte Port, byte Pin);
    void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow);
    void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput);
    void PIN_SET_LAT_TOGGLE(byte Port, byte Pin);
    void PIN_SET_ANSEL(byte Port, byte Pin, byte AnalogOrDijital);
    void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);
    void PIN_INIT_WPU(char Port, byte Pin, byte openOrClose);
    void INT_0_INTERRUPT_SET(byte OpenOrClose);
    void INT_1_INTERRUPT_SET(byte OpenOrClose);
    void INT_2_INTERRUPT_SET(byte OpenOrClose);

    void TIMER_1_INTERRUPT_FUNCT();
    void TIMER_1_INTERRUPT(byte openOrClose);
    void TIMER_1_SET(byte startOrStop);
    void TIMER_1_INIT(byte ms);

    void TIMER_3_INTERRUPT_FUNCT();
    void TIMER_3_INTERRUPT(byte openOrClose);
    void TIMER_3_SET(byte startOrStop);
    void TIMER_3_INIT(byte ms);

    void TIMER_5_INTERRUPT_FUNCT();
    void TIMER_5_INTERRUPT(byte openOrClose);
    void TIMER_5_SET(byte startOrStop);
    void TIMER_5_INIT(byte ms);

    void UART_1_INTERRUPT(byte OpenOrClose);
    void UART_1_INIT(dword baudRate);
    void UART_1_BYTE(byte out);
    void UART_1_STRING(char* text);
    void UART_1_DECIMAL(dword val);

    void UART_2_INTERRUPT(byte OpenOrClose);
    void UART_2_INIT(dword baudRate);
    void UART_2_BYTE(byte out);
    void UART_2_STRING(char* text);
    void UART_2_DECIMAL(dword val);

    void ADC_INIT();
    word ADC_READ(byte channel);

    void PWM_TIMER_2_INIT(dword Hz);
    void PWM_TIMER_4_INIT(dword Hz);
    void PWM_TIMER_6_INIT(dword Hz);
    void PWM_1_INIT();
    void PWM_1_DUTY(byte duty);
    void PWM_2_INIT();
    void PWM_2_DUTY(byte duty);
    void PWM_3_INIT();
    void PWM_3_DUTY(byte duty);
    void PWM_4_INIT();
    void PWM_4_DUTY(byte duty);
    void PWM_5_INIT();
    void PWM_5_DUTY(byte duty);

    void I2C_1_ACK(void);
    void I2C_1_NACK(void);
    void I2C_1_READY(void);
    void I2C_1_INIT(unsigned long baudrate);
    byte I2C_1_WRITE(byte data);
    void I2C_1_START(void);
    void I2C_1_STOP(void);
    byte I2C_1_READ_ACK();
    byte I2C_1_READ_NACK();

    void I2C_2_ACK(void);
    void I2C_2_NACK(void);
    void I2C_2_READY(void);
    void I2C_2_INIT(unsigned long baudrate);
    byte I2C_2_WRITE(byte data);
    void I2C_2_START(void);
    void I2C_2_STOP(void);
    byte I2C_2_READ_ACK();
    byte I2C_2_READ_NACK();

    void UART_1_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_1_INTERRUPT_FUNCT_POINTER_t)(byte));
    void UART_2_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_2_INTERRUPT_FUNCT_POINTER_t)(byte));
    void TIMER_1_INTERRUPT_CONNECT(word ms, void(*TIMER_1_INTERRUPT_FUNCT_POINTER_t)(void));
    void TIMER_3_INTERRUPT_CONNECT(word ms, void(*TIMER_3_INTERRUPT_FUNCT_POINTER_t)(void));
    void TIMER_5_INTERRUPT_CONNECT(word ms, void(*TIMER_5_INTERRUPT_FUNCT_POINTER_t)(void));
    
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PIC_18F46K22_H */

