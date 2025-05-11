#include "PIC_18F46K22.h"

#ifdef __18F46K22
float calculator;

//// <editor-fold defaultstate="collapsed" desc="PWM              ">
// <editor-fold defaultstate="collapsed" desc="PWM HELPER">
#define PWM_USING_TIMER 2
byte PWM_1_TIMER_SELECT = 0;
byte PWM_2_TIMER_SELECT = 0;
byte PWM_3_TIMER_SELECT = 0;
byte PWM_4_TIMER_SELECT = 0;
byte PWM_5_TIMER_SELECT = 0;

word PWM_DUTY_CALCULATER(word timerVal, byte duty)
{
    if (duty == 100) duty = 99;
    calculator = duty;
    calculator = calculator * 4 * (timerVal + 1);
    calculator /= 100;
    return (word) calculator;
}

void PWM_TIMER_CHOOSE(byte Channel, byte timer)
{
    if (Channel == 1) {
        if (timer == 2) CCPTMRS0bits.C1TSEL = 0b00;
        if (timer == 4) CCPTMRS0bits.C1TSEL = 0b01;
        if (timer == 6) CCPTMRS0bits.C1TSEL = 0b10;
        if (timer == 8) CCPTMRS0bits.C1TSEL = 0b11;
        PWM_1_TIMER_SELECT = timer;
    }
    if (Channel == 2) {
        if (timer == 2) CCPTMRS0bits.C2TSEL = 0b000;
        if (timer == 4) CCPTMRS0bits.C2TSEL = 0b001;
        if (timer == 6) CCPTMRS0bits.C2TSEL = 0b010;
        if (timer == 8) CCPTMRS0bits.C2TSEL = 0b011;
        PWM_2_TIMER_SELECT = timer;
    }
    if (Channel == 3) {
        if (timer == 2) CCPTMRS0bits.C3TSEL = 0b00;
        if (timer == 4) CCPTMRS0bits.C3TSEL = 0b01;
        if (timer == 6) CCPTMRS0bits.C3TSEL = 0b10;
        if (timer == 8) CCPTMRS0bits.C3TSEL = 0b11;
        PWM_3_TIMER_SELECT = timer;
    }
    if (Channel == 4) {
        if (timer == 2) CCPTMRS1bits.C4TSEL = 0b00;
        if (timer == 4) CCPTMRS1bits.C4TSEL = 0b01;
        if (timer == 6) CCPTMRS1bits.C4TSEL = 0b10;
        if (timer == 8) CCPTMRS1bits.C4TSEL = 0b11;
        PWM_4_TIMER_SELECT = timer;
    }
    if (Channel == 5) {
        if (timer == 2) CCPTMRS1bits.C5TSEL0 = 0;
        if (timer == 4) CCPTMRS1bits.C5TSEL0 = 1;
        PWM_5_TIMER_SELECT = timer;
    }
}

word PWM_TIMER_GET(byte Channel)
{
    byte timer = 0;
    if (Channel == 1) timer = PWM_1_TIMER_SELECT;
    if (Channel == 2) timer = PWM_2_TIMER_SELECT;
    if (Channel == 3) timer = PWM_3_TIMER_SELECT;
    if (Channel == 4) timer = PWM_4_TIMER_SELECT;
    if (Channel == 5) timer = PWM_5_TIMER_SELECT;
    if (Channel == 6) timer = PWM_5_TIMER_SELECT;
    if (Channel == 7) timer = PWM_5_TIMER_SELECT;

    if (timer == 2) return PR2;
    if (timer == 4) return PR4;
    if (timer == 6) return PR6;
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER2">

void PWM_TIMER_2_SET(byte openOrClose)
{
    if (openOrClose) T2CONbits.TMR2ON = 1;
    else T2CONbits.TMR2ON = 0;
}

void PWM_TIMER_2_INIT(dword Hz)
{
    byte prescale;
    T2CON = 0b00000000;
    prescale = 1;
    for (byte x = 0; x < 8; x++) {
        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T2CON += 0x10;
        }
    }
    PR2 = (byte) (calculator - 1);
    PWM_TIMER_2_SET(1);
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER4">

void PWM_TIMER_4_SET(byte openOrClose)
{
    if (openOrClose) T4CONbits.TMR4ON = 1;
    else T4CONbits.TMR4ON = 0;
}

void PWM_TIMER_4_INIT(dword Hz)
{
    byte prescale;
    dword calculator;
    T4CON = 0b00000000;
    prescale = 1;

    for (byte x = 0; x < 8; x++) {
        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T4CON += 0x10; // Prescaler bits: T4CKPS<1:0>
        }
    }

    PR4 = (byte) (calculator - 1);
    PWM_TIMER_4_SET(1);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TIMER6">

void PWM_TIMER_6_SET(byte openOrClose)
{
    if (openOrClose) T6CONbits.TMR6ON = 1;
    else T6CONbits.TMR6ON = 0;
}

void PWM_TIMER_6_INIT(dword Hz)
{
    byte prescale;
    dword calculator;
    T6CON = 0b00000000;
    prescale = 1;

    for (byte x = 0; x < 8; x++) {
        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T6CON += 0x10; // Prescaler bits: T6CKPS<1:0>
        }
    }

    PR6 = (byte) (calculator - 1);
    PWM_TIMER_6_SET(1);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM1">

void PWM_1_INIT()
{
    PIN_SET_IO('D', 'O', 'C', 2, 'L'); // PWM1 ç?k??? için pin ayar? (RC0)
    CCP1CONbits.CCP1M = 0b1100; // PWM modunu ayarla
    PWM_TIMER_CHOOSE(1, PWM_USING_TIMER);
}

void PWM_1_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(1), duty);
    CCPR1L = (byte) (temp >> 2 & 0xFF);
    CCP1CONbits.DC1B0 = ((temp >> 8) & 0x01);
    CCP1CONbits.DC1B1 = ((temp >> 9) & 0x01);

}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="PWM2">

void PWM_2_INIT()
{
    PIN_SET_IO('D', 'O', 'B', 3, 'L'); // RC1 ç?k??
    CCP2CONbits.CCP2M = 0b1100; // PWM modu
    PWM_TIMER_CHOOSE(2, PWM_USING_TIMER);
}

void PWM_2_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(2), duty);
    CCPR2L = (byte) (temp >> 2 & 0xFF);
    CCP2CONbits.DC2B0 = ((temp >> 8) & 0x01);
    CCP2CONbits.DC2B1 = ((temp >> 9) & 0x01);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM3">

void PWM_3_INIT()
{
    PIN_SET_IO('D', 'O', 'B', 5, 'L'); // RC6 ç?k??
    CCP3CONbits.CCP3M = 0b1100; // PWM modu
    PWM_TIMER_CHOOSE(3, PWM_USING_TIMER);
}

void PWM_3_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(3), duty);
    CCPR3L = (byte) (temp >> 2 & 0xFF);
    CCP3CONbits.DC3B0 = ((temp >> 8) & 0x01);
    CCP3CONbits.DC3B1 = ((temp >> 9) & 0x01);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM4">

void PWM_4_INIT()
{
    PIN_SET_IO('D', 'O', 'D', 1, 'L'); // RD5 ç?k??
    CCP4CONbits.CCP4M = 0b1100; // PWM modu
    PWM_TIMER_CHOOSE(4, PWM_USING_TIMER);
}

void PWM_4_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(4), duty);
    CCPR4L = (byte) (temp >> 2 & 0xFF);
    CCP4CONbits.DC4B0 = ((temp >> 8) & 0x01);
    CCP4CONbits.DC4B1 = ((temp >> 9) & 0x01);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM5">

void PWM_5_INIT()
{
    PIN_SET_IO('D', 'O', 'E', 2, 'L'); // RD8 ç?k?? (kontrol et)
    CCP5CONbits.CCP5M = 0b1100; // PWM modu
    PWM_TIMER_CHOOSE(5, PWM_USING_TIMER);
}

void PWM_5_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(5), duty);
    CCPR5L = (byte) (temp >> 2 & 0xFF);
    CCP5CONbits.DC5B0 = ((temp >> 8) & 0x01);
    CCP5CONbits.DC5B1 = ((temp >> 9) & 0x01);
}

// </editor-fold>
//// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="ADC              ">

void ADC_INIT()
{
    ADCON1 = 0x00; /* Ref vtg is VDD and Configure pin as analog pin */
    ADCON2 = 0xBE; //0x92; /* Right Justified, 4Tad and Fosc/32. */
    ADRESH = 0; /* Flush ADC output Register */
    ADRESL = 0;
}

word ADC_READ(byte channel)
{
    word digital;

    /* Channel 0 is selected i.e.(CHS3CHS2CHS1CHS0=0000) & ADC is disabled */
    ADCON0 = (ADCON0 & 0b10000011) | ((channel << 2) & 0b00111100);
    ADCON0 |= ((1 << ADON) | (1 << GO)); /*Enable ADC and start conversion*/
    /* Wait for End of conversion i.e. Go/done'=0 conversion completed */
    while (ADCON0bits.GO_nDONE == 1);
    __delay_ms(10);
    digital = (ADRESH * 256) | (ADRESL); /*Combine 8-bit LSB and 2-bit MSB*/
    return (digital);
}

void ADC_FVR_INIT(byte openOrClose)
{
    if (openOrClose == 1) ADCON1 |= 0b00001000;
    else if (openOrClose == 0) ADCON1 &= 0b11110011;
}

void FVR_INIT(byte fixedVoltageName)
{
    VREFCON0 = 0;
    VREFCON0 += fixedVoltageName << 4;
    VREFCON0bits.FVREN = 1;
    while (!VREFCON0bits.FVRST);
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USART            ">
// <editor-fold defaultstate="collapsed" desc="USART 1">

void UART_1_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE1bits.RC1IE = 1;
    else if (OpenOrClose == 0) PIE1bits.RC1IE = 0;
}

void UART_1_INIT(dword baudRate)
{
    qword calculater;
    PIN_SET_IO('D', 'O', 'C', 6, 'H ');
    PIN_SET_IO('D', 'I', 'C', 7, 'H ');
    calculater = (CRYSTAL_FREKANS) / ((64) *(baudRate));
    SPBRG1 = (byte) (calculater - 1);
    TXSTA1 = 0x20;
    RCSTA1 = 0x90;
    TXSTA1bits.BRGH = 0;
    UART_1_INTERRUPT(open);
}

void UART_1_BYTE(byte out)
{
    while (TX1IF == 0) continue; /*wait for transmit interrupt flag*/
    TXREG1 = out; /*transmit data via TXREG register*/
}

void UART_1_STRING(char* text)
{
    while (*text) {
        UART_1_BYTE(*text); // Her karakteri gönder
        text++;
    }
}

void UART_1_DECIMAL(dword val)
{

    byte basamak[10] = {};
    signed char i = 0;
    do {
        basamak[ i ] = (val % 10) + 0x30;
        val /= 10;
        i++;
    } while (val != 0);
    i--;
    while (i >= 0) {
        UART_1_BYTE(basamak[ i ]);
        i--;
    }
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USART 2">

void UART_2_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE3bits.RC2IE = 1;
    else if (OpenOrClose == 0) PIE3bits.RC2IE = 0;
}

void UART_2_INIT(dword baudRate)
{
    dword calculater;
    PIN_SET_IO('D', 'O', 'D', 6, 'H ');
    PIN_SET_IO('D', 'I', 'D', 7, 'H ');
    calculater = (CRYSTAL_FREKANS) / ((64) *(baudRate));
    SPBRG2 = (byte) (calculater - 1);
    TXSTA2 = 0x20;
    RCSTA2 = 0x90;
    UART_2_INTERRUPT(open);
}

void UART_2_BYTE(byte out)
{
    while (TX2IF == 0) continue; /*wait for transmit interrupt flag*/
    TXREG2 = out; /*transmit data via TXREG register*/
}

void UART_2_STRING(char* text)
{
    while (*text) {
        UART_2_BYTE(*text); // Her karakteri gönder
        text++;
    }
}

void UART_2_DECIMAL(dword val)
{

    byte basamak[10] = {};
    signed char i = 0;
    do {
        basamak[ i ] = (val % 10) + 0x30;
        val /= 10;
        i++;
    } while (val != 0);
    i--;
    while (i >= 0) {
        UART_2_BYTE(basamak[ i ]);
        i--;
    }
}
// </editor-fold> 
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER_1">

word TIMER_1_TICK = 0;

void TIMER_1_INTERRUPT_FUNCT()
{
    PIR1bits.TMR1IF = 0;
    TMR1 = TIMER_1_TICK;
}

void TIMER_1_INTERRUPT(byte openOrClose)
{
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = openOrClose ? 1 : 0;
}

void TIMER_1_SET(byte startOrStop)
{
    T1CONbits.TMR1ON = startOrStop ? 1 : 0;
}

void TIMER_1_INIT(byte ms)
{
    unsigned long Fosc = CRYSTAL_FREKANS;
    unsigned long Fcy = Fosc / 4;
    byte Prescalers[] = {1, 2, 4, 8};
    word TMR1_Tick = 0;

    for (int i = 0; i < 4; i++) {
        unsigned long TimerFreq = Fcy / Prescalers[i];
        unsigned long TickValue = (TimerFreq / 1000) * ms;

        if (TickValue <= 65536) {
            T1CONbits.T1CKPS = i;
            TMR1_Tick = 65536 - TickValue;
            break;
        }
    }

    TIMER_1_TICK = TMR1_Tick;
    TMR1 = TIMER_1_TICK;
    TIMER_1_INTERRUPT(1);
    TIMER_1_SET(1);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TIMER_3">

word TIMER_3_TICK = 0;

void TIMER_3_INTERRUPT_FUNCT()
{
    PIR2bits.TMR3IF = 0;
    TMR3 = TIMER_3_TICK;
}

void TIMER_3_INTERRUPT(byte openOrClose)
{
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = openOrClose ? 1 : 0;
}

void TIMER_3_SET(byte startOrStop)
{
    T3CONbits.TMR3ON = startOrStop ? 1 : 0;
}

void TIMER_3_INIT(byte ms)
{
    unsigned long Fosc = CRYSTAL_FREKANS;
    unsigned long Fcy = Fosc / 4;
    byte Prescalers[] = {1, 2, 4, 8};
    word TMR3_Tick = 0;

    for (int i = 0; i < 4; i++) {
        unsigned long TimerFreq = Fcy / Prescalers[i];
        unsigned long TickValue = (TimerFreq / 1000) * ms;

        if (TickValue <= 65536) {
            T3CONbits.T3CKPS = i;
            TMR3_Tick = 65536 - TickValue;
            break;
        }
    }

    TIMER_3_TICK = TMR3_Tick;
    TMR3 = TIMER_3_TICK;
    TIMER_3_INTERRUPT(1);
    TIMER_3_SET(1);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TIMER_5">

word TIMER_5_TICK = 0;

void TIMER_5_INTERRUPT_FUNCT()
{
    PIR5bits.TMR5IF = 0;
    TMR5 = TIMER_5_TICK;
}

void TIMER_5_INTERRUPT(byte openOrClose)
{
    PIR5bits.TMR5IF = 0;
    PIE5bits.TMR5IE = openOrClose ? 1 : 0;
}

void TIMER_5_SET(byte startOrStop)
{
    T5CONbits.TMR5ON = startOrStop ? 1 : 0;
}

void TIMER_5_INIT(byte ms)
{
    unsigned long Fosc = CRYSTAL_FREKANS;
    unsigned long Fcy = Fosc / 4;
    byte Prescalers[] = {1, 2, 4, 8};
    word TMR5_Tick = 0;

    for (int i = 0; i < 4; i++) {
        unsigned long TimerFreq = Fcy / Prescalers[i];
        unsigned long TickValue = (TimerFreq / 1000) * ms;

        if (TickValue <= 65536) {
            T5CONbits.T5CKPS = i;
            TMR5_Tick = 65536 - TickValue;
            break;
        }
    }

    TIMER_5_TICK = TMR5_Tick;
    TMR5 = TIMER_5_TICK;
    TIMER_5_INTERRUPT(1);
    TIMER_5_SET(1);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PIN IO         ">

byte PIN_GET_PORT(byte Port, byte Pin)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&PORTA) + (Port - 'A');
    if ((*work_adress) & hex) return 1;
    else return 0;
}

void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&LATA) + (Port - 'A');
    if ((HighOrLow == 'L') || (HighOrLow == 'l') || (HighOrLow == 0)) *work_adress = *work_adress & ~hex;
    else if ((HighOrLow == 'H') || (HighOrLow == 'h') || (HighOrLow == 1)) *work_adress = *work_adress | hex;
}

void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&TRISA) + (Port - 'A');
    if ((InputOrOutput == 'O') || (InputOrOutput == 'o') || (InputOrOutput == 0)) *work_adress = *work_adress & ~hex;
    else if ((InputOrOutput == 'I') || (InputOrOutput == 'i') || (InputOrOutput == 1)) *work_adress = *work_adress | hex;

}

void PIN_SET_LAT_TOGGLE(byte Port, byte Pin)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&LATA) + (Port - 'A');
    *work_adress = *work_adress ^ hex;
}

void PIN_SET_ANSEL(byte Port, byte Pin, byte AnalogOrDijital)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&ANSELA) + (Port - 'A');
    if ((AnalogOrDijital == 'D') || (AnalogOrDijital == 'd') || (AnalogOrDijital == 0)) *work_adress = *work_adress & ~hex;
    else if ((AnalogOrDijital == 'A') || (AnalogOrDijital == 'a') || (AnalogOrDijital == 1)) *work_adress = *work_adress | hex;

}

void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow)
{
    PIN_SET_LAT(Port, Pin, HighOrLow);
    PIN_SET_TRIS(Port, Pin, InputOrOutput);
    PIN_SET_ANSEL(Port, Pin, AnalogOrDijital);
}

void PIN_INIT_WPU(char Port, byte Pin, byte openOrClose)
{
    byte hex;
    hex = 1;
    for (byte i = 0; i < Pin; i++) hex *= 2;
    if (Port == 'B') {
        if (openOrClose == open) WPUB = WPUB | hex;
        else if (openOrClose == close) WPUB = WPUB & ~hex;
    }
}

void INT_0_INTERRUPT_SET(byte OpenOrClose)
{
    if (OpenOrClose == 1) INTCONbits.INT0IE = 1;
    else if (OpenOrClose == 0) INTCONbits.INT0IE = 0;
}

void INT_1_INTERRUPT_SET(byte OpenOrClose)
{
    if (OpenOrClose == 1) INTCON3bits.INT1IE = 1;
    else if (OpenOrClose == 0) INTCON3bits.INT1IE = 0;
}

void INT_2_INTERRUPT_SET(byte OpenOrClose)
{
    if (OpenOrClose == 1) INTCON3bits.INT2IE = 1;
    else if (OpenOrClose == 0) INTCON3bits.INT2IE = 0;
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="SYSTEM         ">

void MCU_INIT(byte inorEx, byte mhz)
{
    if (inorEx == SYSTEM_FREQ_EXTERNAL) {
        if (mhz == 64) {
            OSCCON = 0x30;
            OSCCON2 = 0x84;
            OSCTUNE = 0x40;
        }
    } else if (inorEx == SYSTEM_FREQ_INTERNAL) {
        if (mhz & 0x02) {
            OSCCON2bits.PLLRDY = 1;
            OSCTUNEbits.PLLEN = 1;
        }
        OSCCON = mhz;
        while (!OSCCONbits.IOFS) continue;
    }

}

void INTERRUPT_ALL(byte OpenOrClose)
{
    INTCONbits.PEIE = 1;
    if (OpenOrClose == 1) INTCONbits.GIE = 1;
    else if (OpenOrClose == 0) INTCONbits.GIE = 0;
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="EEPROM           ">

void EEPROM_B_WRITE(word address, byte data)
{
    byte hold;
    hold = INTCONbits.GIE;
    /*Write Operation*/
    EEADR = (byte) address; /* Write address to the EEADR register*/
    EEDATA = data; /* Copy data to the EEDATA register for write */
    EECON1bits.EEPGD = 0; /* Access data EEPROM memory*/
    EECON1bits.CFGS = 0; /* Access flash program or data memory*/
    EECON1bits.WREN = 1; /* Allow write to the memory*/
    INTCONbits.GIE = 0; /* Disable global interrupt*/

    /* Below sequence in EECON2 Register is necessary 
    to write data to EEPROM memory*/
    EECON2 = 0x55;
    EECON2 = 0xaa;

    EECON1bits.WR = 1; /* Start writing data to EEPROM memory*/
    INTCONbits.GIE = hold; /* Enable interrupt*/
    while (PIR2bits.EEIF == 0); /* Wait for write operation complete */
    PIR2bits.EEIF = 0; /* Reset EEIF for further write operation */

}

byte EEPROM_B_READ(word address)
{
    /*Read operation*/
    EEADR = (byte) address; /* Read data at location 0x00*/
    EECON1bits.WREN = 0; /* WREN bit is clear for Read operation*/
    EECON1bits.EEPGD = 0; /* Access data EEPROM memory*/
    EECON1bits.RD = 1; /* To Read data of EEPROM memory set RD=1*/
    __delay_ms(1);
    return (EEDATA);
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="I2C              ">
// <editor-fold defaultstate="collapsed" desc="I2C 1">

void I2C_1_ACK(void)
{
    SSP1CON2bits.ACKDT1 = 0; /* Acknowledge data 1:NACK,0:ACK */
    SSP1CON2bits.ACKEN1 = 1; /* Enable ACK to send */
    while (SSP1CON2bits.ACKEN1);
}

void I2C_1_NACK(void)
{
    SSP1CON2bits.ACKDT1 = 1; /* Acknowledge data 1:NACK,0:ACK */
    SSP1CON2bits.ACKEN1 = 1; /* Enable ACK to send */
    while (SSP1CON2bits.ACKEN1);
}

void I2C_1_READY(void)
{
    while (PIR2bits.BCL1IF); /* Wait if bit collision interrupt flag is set*/

    /* Wait for Buffer full and read write flag*/
    while (SSP1STATbits.BF || (SSP1STATbits.R_nW));
    PIR1bits.SSP1IF = 0; /* Clear SSPIF interrupt flag*/
}

void I2C_1_INIT(unsigned long baudrate)
{
    PIN_SET_IO('D', 'I', 'C', 3, 'L'); // RD5 ç?k??
    PIN_SET_IO('D', 'I', 'C', 4, 'L'); // RD5 ç?k??
    SSP1STAT = 0x88; /* Slew rate disabled, other bits are cleared */
    SSP1CON1 = 0x28; /* Enable SSP port for I2C Master mode // clock = FOSC / (4 * (SSPADD+1))*/
    SSP1CON2 = 0;
    calculator = (CRYSTAL_FREKANS) / (baudrate);
    SSP1ADD = (byte) (calculator - 1);
    //PIE1bits.SSP1IE = 1; /* Enable SSPIF interrupt */
    PIR1bits.SSP1IF = 0;
}

byte I2C_1_WRITE(byte data)
{
    SSP1BUF = data; /* Write data to SSPBUF*/
    I2C_1_READY();
    if (SSP1CON2bits.ACKSTAT1) /* Check for acknowledge bit*/
        return 1;
    else
        return 2;
}

void I2C_1_START(void)
{
    SSP1CON2bits.SEN = 1; /* Send start pulse */
    while (SSP1CON2bits.SEN); /* Wait for completion of start pulse */
    PIR1bits.SSP1IF = 0;
}

void I2C_1_STOP(void)
{
    I2C_1_READY();
    SSP1CON2bits.PEN1 = 1; /* Stop communication*/
    while (SSP1CON2bits.PEN1); /* Wait for end of stop pulse*/
    PIR1bits.SSP1IF = 0;
}

byte I2C_1_READ_ACK()
{
    byte buffer = 0;
    SSP1CON2bits.RCEN1 = 1; /* Enable receive */
    while (!SSP1STATbits.BF1);
    buffer = SSP1BUF; /* Copy SSPBUF to buffer */
    I2C_1_ACK();
    return buffer;
}

byte I2C_1_READ_NACK()
{
    byte buffer = 0;
    SSP1CON2bits.RCEN1 = 1; /* Enable receive */
    while (!SSP1STATbits.BF1);
    buffer = SSP1BUF; /* Copy SSPBUF to buffer */
    I2C_1_ACK();
    return buffer;
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="I2C 2">

void I2C_2_ACK(void)
{
    SSP2CON2bits.ACKDT = 0;
    SSP2CON2bits.ACKEN = 1;
    while (SSP2CON2bits.ACKEN);
}

void I2C_2_NACK(void)
{
    SSP2CON2bits.ACKDT = 1;
    SSP2CON2bits.ACKEN = 1;
    while (SSP2CON2bits.ACKEN);
}

void I2C_2_READY(void)
{
    while (PIR3bits.BCL2IF); // Bit collision varsa bekle
    while (SSP2STATbits.BF || SSP2STATbits.R_nW);
    PIR3bits.SSP2IF = 0;
}

void I2C_2_INIT(unsigned long baudrate)
{
    PIN_SET_IO('D', 'I', 'D', 0, 'L'); // RD5 = SCL2
    PIN_SET_IO('D', 'I', 'D', 1, 'L'); // RD6 = SDA2

    SSP2STAT = 0x80; // Slew rate disabled
    SSP2CON1 = 0x28; // Master mode
    SSP2CON2 = 0x00;

    SSP2ADD = (CRYSTAL_FREKANS / (4 * baudrate)) - 1;

    PIR3bits.SSP2IF = 0;
}

byte I2C_2_WRITE(byte data)
{
    SSP2BUF = data;
    I2C_2_READY();
    if (SSP2CON2bits.ACKSTAT) return 1; // NACK al?nd?
    return 0; // ACK al?nd?
}

void I2C_2_START(void)
{
    SSP2CON2bits.SEN = 1;
    while (SSP2CON2bits.SEN);
    PIR3bits.SSP2IF = 0;
}

void I2C_2_STOP(void)
{
    I2C_2_READY();
    SSP2CON2bits.PEN = 1;
    while (SSP2CON2bits.PEN);
    PIR3bits.SSP2IF = 0;
}

byte I2C_2_READ_ACK(void)
{
    byte buffer;
    SSP2CON2bits.RCEN = 1;
    while (!SSP2STATbits.BF);
    buffer = SSP2BUF;
    I2C_2_ACK();
    return buffer;
}

byte I2C_2_READ_NACK(void)
{
    byte buffer;
    SSP2CON2bits.RCEN = 1;
    while (!SSP2STATbits.BF);
    buffer = SSP2BUF;
    I2C_2_NACK();
    return buffer;
}

// </editor-fold>

// </editor-fold> 

////// <editor-fold defaultstate="collapsed" desc="SPI              ">
////// <editor-fold defaultstate="collapsed" desc="SPI 1">
////
//
//void SPI1_SET(byte OpenOrClose)
//  {
//  if (OpenOrClose == 1) SSP1CON1bits.SSPEN = 1;
//  else if (OpenOrClose == 0) SSP1CON1bits.SSPEN = 0;
//  }
//
//void SPI1_INIT(byte SpiMode, word clockRate)
//  {
//  qword calculater;
//  ANSELCbits.ANSC3 = 0;
//  ANSELCbits.ANSC4 = 0;
//  ANSELCbits.ANSC5 = 0;
//  TRISCbits.TRISC3 = 0;
//  TRISCbits.TRISC4 = 1;
//  TRISCbits.TRISC5 = 0;
//  SSP1STAT = 0x40;
//  SSP1CON1 = 0x00;
//  calculater = (systemMhz * 250) / (clockRate);
//  SSP1ADD = (byte) (calculater - 1);
//  SSP1CON1bits.SSPEN = 0;
//  PIR1bits.SSP1IF = 0;
//
//  if (SpiMode == 0)
//    {
//    SSP1CON1bits.CKP = 0;
//    SSP1STATbits.CKE = 1;
//    }
//  else if (SpiMode == 1)
//    {
//    SSP1CON1bits.CKP = 0;
//    SSP1STATbits.CKE = 0;
//    }
//  else if (SpiMode == 2)
//    {
//    SSP1CON1bits.CKP = 1;
//    SSP1STATbits.CKE = 1;
//    }
//  else if (SpiMode == 3)
//    {
//    SSP1CON1bits.CKP = 1;
//    SSP1STATbits.CKE = 0;
//    }
//  SPI1_SET(open);
//  }
//
//void SPI1_Write(byte out)
//  {
//  byte data_flush;
//  SSP1BUF = out; /* Copy data in SSBUF to transmit */
//  while (!PIR1bits.SSP1IF); /* Wait for complete 1 byte transmission */
//  PIR1bits.SSP1IF = 0; /* Clear SSPIF flag */
//  data_flush = SSP1BUF; /* Flush the data */
//  }
//
//byte SPI1_Read()
//  {
//  byte data_flush;
//  SSP1BUF = 0x00; //dummy tx
//  while (!PIR1bits.SSP1IF) continue;
//  PIR1bits.SSP1IF = 0;
//  data_flush = SSP1BUF;
//  return data_flush; //read  buffer
//  }
//
//
//
////// </editor-fold> 
//// <editor-fold defaultstate="collapsed" desc="SPI 2">
//
//void SPI2_SET(byte OpenOrClose)
//  {
//  if (OpenOrClose == 1) SSP2CON1bits.SSPEN = 1;
//  else if (OpenOrClose == 0) SSP2CON1bits.SSPEN = 0;
//  }
//
//void SPI2_INIT(byte SpiMode, word clockRate)
//  {
//  qword calculater;
//  ANSELDbits.ANSD3 = 0;
//  ANSELDbits.ANSD4 = 0;
//  ANSELDbits.ANSD5 = 0;
//  TRISDbits.TRISD3 = 0;
//  TRISDbits.TRISD4 = 1;
//  TRISDbits.TRISD5 = 0;
//  SSP2STAT = 0x40;
//  SSP2CON1 = 0x00;
//  calculater = (systemMhz * 250) / (clockRate);
//  SSP2ADD = (byte) (calculater - 1);
//  SSP2CON1bits.SSPEN = 0;
//  PIR3bits.SSP2IF = 0;
//
//  if (SpiMode == 0)
//    {
//    SSP2CON1bits.CKP = 0;
//    SSP2STATbits.CKE = 1;
//    }
//  else if (SpiMode == 1)
//    {
//    SSP2CON1bits.CKP = 0;
//    SSP2STATbits.CKE = 0;
//    }
//  else if (SpiMode == 2)
//    {
//    SSP2CON1bits.CKP = 1;
//    SSP2STATbits.CKE = 1;
//    }
//  else if (SpiMode == 3)
//    {
//    SSP2CON1bits.CKP = 1;
//    SSP2STATbits.CKE = 0;
//    }
//  SPI2_SET(open);
//  }
//
//void SPI2_Write(byte data)
//  {
//  SSP2BUF = data;
//  while (!PIR3bits.SSP2IF) continue; /* Wait for complete 1 byte transmission */
//  PIR3bits.SSP2IF = 0; /* Clear SSPIF flag */
//  }
//
//byte SPI2_Read(void)
//  {
//  byte data_flush;
//  SSP2BUF = 0x00; //dummy tx
//  while (!PIR3bits.SSP2IF) continue;
//  PIR3bits.SSP2IF = 0;
//  data_flush = SSP2BUF;
//  return data_flush; //read  buffer
//  }
//
//
//// </editor-fold> 
////// </editor-fold> 

void(*UART_1_INTERRUPT_FUNCT_POINTER)(byte);
void(*UART_2_INTERRUPT_FUNCT_POINTER)(byte);
void(*TIMER_1_INTERRUPT_FUNCT_POINTER)(void);
void(*TIMER_5_INTERRUPT_FUNCT_POINTER)(void);
void(*TIMER_3_INTERRUPT_FUNCT_POINTER)(void);

void UART_1_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_1_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_1_INIT(baudrate);
    UART_1_INTERRUPT_FUNCT_POINTER = UART_1_INTERRUPT_FUNCT_POINTER_t;
}

void UART_2_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_2_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_2_INIT(baudrate);
    UART_2_INTERRUPT_FUNCT_POINTER = UART_2_INTERRUPT_FUNCT_POINTER_t;
}

void TIMER_1_INTERRUPT_CONNECT(word ms, void(*TIMER_1_INTERRUPT_FUNCT_POINTER_t)(void))
{
    TIMER_1_INIT(ms);
    TIMER_1_INTERRUPT_FUNCT_POINTER = TIMER_1_INTERRUPT_FUNCT_POINTER_t;
}

void TIMER_3_INTERRUPT_CONNECT(word ms, void(*TIMER_3_INTERRUPT_FUNCT_POINTER_t)(void))
{
    TIMER_3_INIT(ms);
    TIMER_3_INTERRUPT_FUNCT_POINTER = TIMER_3_INTERRUPT_FUNCT_POINTER_t;
}

void TIMER_5_INTERRUPT_CONNECT(word ms, void(*TIMER_5_INTERRUPT_FUNCT_POINTER_t)(void))
{
    TIMER_5_INIT(ms);
    TIMER_5_INTERRUPT_FUNCT_POINTER = TIMER_5_INTERRUPT_FUNCT_POINTER_t;
}

void __interrupt(high_priority) _ISR(void)
{
    if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_1_INTERRUPT_FUNCT();
        TIMER_1_INTERRUPT_FUNCT_POINTER();
    } else if (PIR2bits.TMR3IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_3_INTERRUPT_FUNCT();
        TIMER_3_INTERRUPT_FUNCT_POINTER();
    } else if (PIR5bits.TMR5IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_5_INTERRUPT_FUNCT();
        TIMER_5_INTERRUPT_FUNCT_POINTER();
    } else if (PIR1bits.RC1IF) {
        PIR1bits.RC1IF = 0;
        UART_1_INTERRUPT_FUNCT_POINTER(RCREG1);
    } else if (PIR3bits.RC2IF) {
        PIR3bits.RC2IF = 0;
        UART_2_INTERRUPT_FUNCT_POINTER(RCREG2);
    }
}

#endif
