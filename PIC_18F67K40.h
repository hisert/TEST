#include "common.h"

#ifndef PIC_18F67K40_H
#define	PIC_18F67K40_H

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef PIC_18F67K40

    // <editor-fold defaultstate="collapsed" desc="CONFIG">

#pragma config FEXTOSC = OFF    // External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_64MHZ// Power-up default value for COSC bits (HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = OFF       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RG5 pin function is MCLR )
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power up timer disabled)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)
#pragma config BORV = VBOR_2P45 // Brown Out Reset Voltage selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = OFF     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = OFF      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)
#pragma config WDTCPS = WDTCPS_4// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF      // WDT operating mode (WDT Disabled)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = LFINTOSC      // WDT input clock selector (Software Control)
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)
#pragma config WRT4 = OFF       // Write Protection Block 3 (Block 4 (010000-013FFFh) not write-protected)
#pragma config WRT5 = OFF       // Write Protection Block 3 (Block 5 (014000-017FFFh) not write-protected)
#pragma config WRT6 = OFF       // Write Protection Block 3 (Block 6 (018000-01BFFFh) not write-protected)
#pragma config WRT7 = OFF       // Write Protection Block 3 (Block 7 (01C000-01FFFFh) not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config SCANE = OFF       // Scanner Enable bit (Scanner module is available for use, SCANMD bit can control the module)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (HV on MCLR/VPP must be used for programming)
#pragma config CP = ON         // UserNVM Program Memory Code Protection bit (UserNVM code protection disabled)
#pragma config CPD = ON        // DataNVM Memory Code Protection bit (DataNVM code protection disabled)
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR4 = OFF      // Table Read Protection Block 4 (Block 4 (010000-013FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR5 = OFF      // Table Read Protection Block 5 (Block 5 (014000-017FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR6 = OFF      // Table Read Protection Block 6 (Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR7 = OFF      // Table Read Protection Block 7 (Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks)#endif
    // </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="ANOTHER DEFINE   ">

    typedef enum {
        PPS_CWG1A = 1,
        PPS_CWG1B,
        PPS_CWG1C,
        PPS_CWG1D,
        PPS_CCP1,
        PPS_CCP2,
        PPS_CCP3,
        PPS_CCP4,
        PPS_CCP5,
        PPS_PWM6,
        PPS_PWM7,
        PPS_EUSART1_TX,
        PPS_EUSART1_DT,
        PPS_EUSART2_TX,
        PPS_EUSART2_DT,
        PPS_EUSART3_TX,
        PPS_EUSART3_DT,
        PPS_EUSART4_TX,
        PPS_EUSART4_DT,
        PPS_EUSART5_TX,
        PPS_EUSART5_DT,
        PPS_CMP1,
        PPS_CMP2,
        PPS_CMP3,
        PPS_MSSP1_SCK,
        PPS_MSSP1_SDO,
        PPS_MSSP2_SCK,
        PPS_MSSP2_SDO,
        PPS_TMR0,
        PPS_CLKR,
        PPS_DSM1,
        PPS_ADGRDA,
        PPS_ADGRDB
    } PPS_MAPS;

    typedef enum {
        ADC_RA0 = 0,
        ADC_RA1,
        ADC_RA2,
        ADC_RA3,
        ADC_RA4,
        ADC_RA5,
        ADC_RA6,
        ADC_RA7,
        ADC_RB0,
        ADC_RB1,
        ADC_RB2,
        ADC_RB3,
        ADC_RB4,
        ADC_RB5,
        ADC_RB6,
        ADC_RB7,
        ADC_RD0 = 24,
        ADC_RD1,
        ADC_RD2,
        ADC_RD3,
        ADC_RD4,
        ADC_RD5,
        ADC_RD6,
        ADC_RD7,
        ADC_RE0,
        ADC_RE1,
        ADC_RE2,
        ADC_RE3,
        ADC_RE4,
        ADC_RE5,
        ADC_RE6,
        ADC_RE7,
        ADC_RF0,
        ADC_RF1,
        ADC_RF2,
        ADC_RF3,
        ADC_RF4,

        ADC_TEMP_IND = 253,
        ADC_DAC1_OUTPUT,
        ADC_FVR,
    } ADC_PINS;

    typedef enum {
        FVR_OFF = 0,
        FVR_1024,
        FVR_2048,
        FVR_4096,
    } FVR_VOLTAGES;
    // </editor-fold>

    void MCU_INIT(byte Mhz);
    void INTERRUPT_ALL(byte OpenOrClose);

    byte PIN_GET_PORT(byte Port, byte Pin);
    void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow);
    void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput);
    void PIN_SET_LAT_TOGGLE(byte Port, byte Pin);
    void PIN_SET_ANSEL(byte Port, byte Pin, byte AnalogOrDijital);
    void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);
    byte PIN_INIT_PPS(char port, byte pin);
    void PIN_INIT_IOC(char Port, byte Pin, char proity, byte openOrClose);
    void PIN_INIT_WPU(char Port, byte Pin, byte openOrClose);

    void TIMER_1_INTERRUPT_FUNCT();
    void TIMER_1_INTERRUPT(byte OpenOrClose);
    void TIMER_1_SET(byte startOrStop);
    void TIMER_1_INIT(byte ms);
    void TIMER_3_INTERRUPT_FUNCT();
    void TIMER_3_INTERRUPT(byte OpenOrClose);
    void TIMER_3_SET(byte startOrStop);
    void TIMER_3_INIT(byte ms);
    void TIMER_5_INTERRUPT_FUNCT();
    void TIMER_5_INTERRUPT(byte OpenOrClose);
    void TIMER_5_SET(byte startOrStop);
    void TIMER_5_INIT(byte ms);
    void TIMER_7_INTERRUPT_FUNCT();
    void TIMER_7_INTERRUPT(byte OpenOrClose);
    void TIMER_7_SET(byte startOrStop);
    void TIMER_7_INIT(byte ms);

    void EEPROM_B_WRITE(word address, byte data);
    byte EEPROM_B_READ(word address);

    void ADC_INIT();
    word ADC_READ(byte channel);

    void PWM_1_INIT(dword Hz);
    void PWM_1_DUTY(byte duty);
    void PWM_2_INIT(dword Hz);
    void PWM_2_DUTY(byte duty);
    void PWM_3_INIT(dword Hz);
    void PWM_3_DUTY(byte duty);
    void PWM_4_INIT(dword Hz);
    void PWM_4_DUTY(byte duty);
    void PWM_5_INIT(dword Hz);
    void PWM_5_DUTY(byte duty);

    void UART_1_INTERRUPT(byte OpenOrClose);
    void UART_1_INIT(word baudRate);
    void UART_1_BYTE(byte out);
    void UART_1_STRING(char* text);
    void UART_1_DECIMAL(dword val);
    void UART_2_INTERRUPT(byte OpenOrClose);
    void UART_2_INIT(word baudRate);
    void UART_2_BYTE(byte out);
    void UART_2_STRING(char* text);
    void UART_2_DECIMAL(dword val);
    void UART_3_INTERRUPT(byte OpenOrClose);
    void UART_3_INIT(word baudRate);
    void UART_3_BYTE(byte out);
    void UART_3_STRING(char* text);
    void UART_3_DECIMAL(dword val);
    void UART_4_INTERRUPT(byte OpenOrClose);
    void UART_4_INIT(word baudRate);
    void UART_4_BYTE(byte out);
    void UART_4_STRING(char* text);
    void UART_4_DECIMAL(dword val);
    void UART_5_INTERRUPT(byte OpenOrClose);
    void UART_5_INIT(word baudRate);
    void UART_5_BYTE(byte out);
    void UART_5_STRING(char* text);
    void UART_5_DECIMAL(dword val);

#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PIC_18F67K40_H */

