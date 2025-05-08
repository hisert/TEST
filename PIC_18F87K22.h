#include "common.h"
#ifndef PIC_18F87K22_H
#define	PIC_18F87K22_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef __18F87K22

    // <editor-fold defaultstate="collapsed" desc="CONFIG">

#pragma config RETEN = OFF       // VREG Sleep Enable bit (Enabled)
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = HIGH   // SOSC Power Selection and mode Configuration bits (High Power SOSC circuit selected)
#pragma config XINST = OFF       // Extended Instruction Set (Enabled)

    // CONFIG1H
#pragma config FOSC = INTIO2    // Oscillator (Internal RC oscillator)
#pragma config PLLCFG = ON     // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

    // CONFIG2L
#pragma config PWRTEN = OFF     // Power Up Timer (Disabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (1.8V)
#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

    // CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WDTPS = 1048576  // Watchdog Postscaler (1:1048576)

    // CONFIG3L
#pragma config RTCOSC = SOSCREF // RTCC Clock Select (RTCC uses SOSC)

    // CONFIG3H
#pragma config CCP2MX = PORTBE   // CCP2 Mux (RC1)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = OFF      // Master Clear Enable (MCLR Disabled, RG5 Enabled)

    // CONFIG4L
#pragma config STVREN = OFF      // Stack Overflow Reset (Enabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)

    // CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-03FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 04000-07FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 08000-0BFFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 0C000-0FFFF (Disabled)
#pragma config CP4 = OFF        // Code Protect 10000-13FFF (Disabled)
#pragma config CP5 = OFF        // Code Protect 14000-17FFF (Disabled)
#pragma config CP6 = OFF        // Code Protect 18000-1BFFF (Disabled)
#pragma config CP7 = OFF        // Code Protect 1C000-1FFFF (Disabled)

    // CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)

    // CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-03FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 04000-07FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 08000-0BFFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 0C000-0FFFF (Disabled)
#pragma config WRT4 = OFF       // Table Write Protect 10000-13FFF (Disabled)
#pragma config WRT5 = OFF       // Table Write Protect 14000-17FFF (Disabled)
#pragma config WRT6 = OFF       // Table Write Protect 18000-1BFFF (Disabled)
#pragma config WRT7 = OFF       // Table Write Protect 1C000-1FFFF (Disabled)

    // CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

    // CONFIG7L
#pragma config EBRT0 = OFF      // Table Read Protect 00800-03FFF (Disabled)
#pragma config EBRT1 = OFF      // Table Read Protect 04000-07FFF (Disabled)
#pragma config EBRT2 = OFF      // Table Read Protect 08000-0BFFF (Disabled)
#pragma config EBRT3 = OFF      // Table Read Protect 0C000-0FFFF (Disabled)
#pragma config EBRT4 = OFF      // Table Read Protect 10000-13FFF (Disabled)
#pragma config EBRT5 = OFF      // Table Read Protect 14000-17FFF (Disabled)
#pragma config EBRT6 = OFF      // Table Read Protect 18000-1BFFF (Disabled)
#pragma config EBRT7 = OFF      // Table Read Protect 1C000-1FFFF (Disabled)

    // CONFIG7H
#pragma config EBRTB = OFF      // Table Read Protect Boot (Disabled)
    // </editor-fold>
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
    void TIMER_1_INIT(byte ms);

    void TIMER_3_INTERRUPT_FUNCT();
    void TIMER_3_INTERRUPT(byte openOrClose);
    void TIMER_3_SET(byte startOrStop);
    void TIMER_3_INIT(byte ms);

    void TIMER_5_INTERRUPT_FUNCT();
    void TIMER_5_INTERRUPT(byte openOrClose);
    void TIMER_5_SET(byte startOrStop);
    void TIMER_5_INIT(byte ms);

    void UART_0_INTERRUPT(byte openOrClose);
    void UART_0_INIT(unsigned long baudrate);
    void UART_0_BYTE(char data);
    void UART_0_STRING(char* text);
    void UART_0_DECIMAL(dword val);

    void UART_1_INTERRUPT(byte openOrClose);
    void UART_1_INIT(unsigned long baudrate);
    void UART_1_BYTE(char data);
    void UART_1_STRING(char* text);
    void UART_1_DECIMAL(dword val);

    void SET_OSC(byte MHz);
    void INTERRUPT_ALL(byte openOrClose);
    void MCU_INIT(byte MHz);

    void ADC_INIT();
    word ADC_READ(unsigned char channel);

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

    void EEPROM_B_WRITE(word address, byte data);
    byte EEPROM_B_READ(word address);

#endif
#ifdef	__cplusplus
}
#endif

#endif	/* PIC_18F87K22_H */

