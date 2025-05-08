#include "PIC_18F67K40.h"

#ifdef PIC_18F67K40
float calculator;

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
    Port = (Port - 'A');
    if (Port == 'A') work_adress = (&ANSELA);
    else if (Port == 'B') work_adress = (&ANSELB);
    else if (Port == 'C') return;
    else if (Port == 'D') work_adress = (&ANSELD);
    else if (Port == 'E') work_adress = (&ANSELE);
    work_adress = work_adress + Port;
    if ((AnalogOrDijital == 'D') || (AnalogOrDijital == 'd') || (AnalogOrDijital == 0)) *work_adress = *work_adress & ~hex;
    else if ((AnalogOrDijital == 'A') || (AnalogOrDijital == 'a') || (AnalogOrDijital == 1)) *work_adress = *work_adress | hex;

}

void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow)
{
    PIN_SET_LAT(Port, Pin, HighOrLow);
    PIN_SET_TRIS(Port, Pin, InputOrOutput);
    PIN_SET_ANSEL(Port, Pin, AnalogOrDijital);
}

byte PIN_INIT_PPS(char port, byte pin)
{
    byte temp;
    if (port == 'A') temp = 0;
    else if (port == 'B') temp = 1;
    else if (port == 'C') temp = 2;
    else if (port == 'D') temp = 3;
    else if (port == 'E') temp = 4;
    else if (port == 'F') temp = 5;
    else if (port == 'G') temp = 6;
    else if (port == 'H') temp = 7;
    else return 0;
    temp = (byte) (temp << 3);
    temp = temp + pin;
    return temp;
}

void PIN_INIT_IOC(char Port, byte Pin, char proity, byte openOrClose)
{
    byte hex;
    hex = 1;
    for (byte i = 0; i < Pin; i++) hex *= 2;
    if (proity == 'P') {
        if (Port == 'B') {
            if (openOrClose == open) IOCBP = IOCBP | hex;
            else if (openOrClose == close) IOCBP = IOCBP & ~hex;
        } else if (Port == 'C') {
            if (openOrClose == open) IOCCP = IOCCP | hex;
            else if (openOrClose == close) IOCCP = IOCCP & ~hex;
        } else if (Port == 'E') {
            if (openOrClose == open) IOCEP = IOCEP | hex;
            else if (openOrClose == close) IOCEP = IOCEP & ~hex;
        } else if (Port == 'G') {
            if (openOrClose == open) IOCGP = IOCGP | hex;
            else if (openOrClose == close) IOCGP = IOCGP & ~hex;
        }
    } else if (proity == 'N') {
        if (Port == 'B') {
            if (openOrClose == open) IOCBN = IOCBN | hex;
            else if (openOrClose == close) IOCBN = IOCBN & ~hex;
        } else if (Port == 'C') {
            if (openOrClose == open) IOCCN = IOCCN | hex;
            else if (openOrClose == close) IOCCN = IOCCN & ~hex;
        } else if (Port == 'E') {
            if (openOrClose == open) IOCEN = IOCEN | hex;
            else if (openOrClose == close) IOCEN = IOCEN & ~hex;
        } else if (Port == 'G') {
            if (openOrClose == open) IOCGN = IOCGN | hex;
            else if (openOrClose == close) IOCGN = IOCGN & ~hex;
        }
    }
    if (PIE0bits.IOCIE == close) PIE0bits.IOCIE = open;
}

void PIN_INIT_WPU(char Port, byte Pin, byte openOrClose)
{
    byte hex;
    hex = 1;
    for (byte i = 0; i < Pin; i++) hex *= 2;
    if (Port == 'A') {
        if (openOrClose == open) WPUA = WPUA | hex;
        else if (openOrClose == close) WPUA = WPUA & ~hex;
    } else if (Port == 'B') {
        if (openOrClose == open) WPUB = WPUB | hex;
        else if (openOrClose == close) WPUB = WPUB & ~hex;
    } else if (Port == 'C') {
        if (openOrClose == open) WPUC = WPUC | hex;
        else if (openOrClose == close) WPUC = WPUC & ~hex;
    } else if (Port == 'D') {
        if (openOrClose == open) WPUD = WPUD | hex;
        else if (openOrClose == close) WPUD = WPUD & ~hex;
    } else if (Port == 'E') {
        if (openOrClose == open) WPUE = WPUE | hex;
        else if (openOrClose == close) WPUE = WPUE & ~hex;
    } else if (Port == 'F') {
        if (openOrClose == open) WPUF = WPUF | hex;
        else if (openOrClose == close) WPUF = WPUF & ~hex;
    } else if (Port == 'G') {
        if (openOrClose == open) WPUG = WPUG | hex;
        else if (openOrClose == close) WPUG = WPUG & ~hex;
    } else if (Port == 'H') {
        if (openOrClose == open) WPUH = WPUH | hex;
        else if (openOrClose == close) WPUH = WPUH & ~hex;
    }
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="SYSTEM         ">

void MCU_INIT(byte Mhz)
{
    __delay_ms(50);
    OSCFRQ = 0b00001000;
}

void INTERRUPT_ALL(byte OpenOrClose)
{
    INTCONbits.PEIE = 1;
    if (OpenOrClose == 1) INTCONbits.GIE = 1;
    else if (OpenOrClose == 0) INTCONbits.GIE = 0;
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER1">
word TIMER_1_TICKS;

void TIMER_1_INTERRUPT_FUNCT()
{
    TMR1 = TIMER_1_TICKS;
}

void TIMER_1_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE5bits.TMR1IE = 1;
    else if (OpenOrClose == 0) PIE5bits.TMR1IE = 0;
}

void TIMER_1_DUTY(byte startOrStop)
{
    if (startOrStop == 1) T1CONbits.TMR1ON = 1;
    else if (startOrStop == 0) T1CONbits.TMR1ON = 0;
}

void TIMER_1_INIT(byte ms)
{
    byte prescale;
    prescale = 1;
    word temp;
    T1CON = 0x00;
    T1CONbits.RD16 = 1;
    T1CLK = 0x01;
    for (byte x = 0; x < 4; x++) {
        calculator = ((CRYSTAL_FREKANS / 1000) / (4 * prescale));
        calculator = 1 / calculator;
        calculator = (ms) / calculator;
        if (calculator < 65536) break;
        else {
            prescale *= 2;
            T1CON += 0x10;
        }
    }
    temp = (word) calculator;
    temp = (word) (65536 - temp);
    PIR5bits.TMR1IF = 0;
    TMR1 = temp;
    TIMER_1_TICKS = temp;
    TIMER_1_DUTY(open);
    TIMER_1_INTERRUPT(open);
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER3">
word TIMER_3_TICKS;

void TIMER_3_INTERRUPT_FUNCT()
{
    TMR3 = TIMER_3_TICKS;
}

void TIMER_3_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE5bits.TMR3IE = 1;
    else if (OpenOrClose == 0) PIE5bits.TMR3IE = 0;
}

void TIMER_3_DUTY(byte startOrStop)
{
    if (startOrStop == 1) T3CONbits.TMR3ON = 1;
    else if (startOrStop == 0) T3CONbits.TMR3ON = 0;
}

void TIMER_3_INIT(byte ms)
{
    byte prescale;
    prescale = 1;
    word temp;
    T3CON = 0x00;
    T3CONbits.RD16 = 1;
    T3CLK = 0x01;
    for (byte x = 0; x < 4; x++) {
        calculator = ((CRYSTAL_FREKANS / 1000) / (4 * prescale));
        calculator = 1 / calculator;
        calculator = (ms) / calculator;
        if (calculator < 65536) break;
        else {
            prescale *= 2;
            T3CON += 0x10;
        }
    }
    temp = (word) calculator;
    temp = (word) (65536 - temp);
    PIR5bits.TMR3IF = 0;
    TMR3 = temp;
    TIMER_3_TICKS = temp;
    TIMER_3_DUTY(open);
    TIMER_3_INTERRUPT(open);
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TIMER5">
word TIMER_5_TICKS;

void TIMER_5_INTERRUPT_FUNCT()
{
    TMR5 = TIMER_5_TICKS;
}

void TIMER_5_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE5bits.TMR5IE = 1;
    else if (OpenOrClose == 0) PIE5bits.TMR5IE = 0;
}

void TIMER_5_DUTY(byte startOrStop)
{
    if (startOrStop == 1) T5CONbits.TMR5ON = 1;
    else if (startOrStop == 0) T5CONbits.TMR5ON = 0;
}

void TIMER_5_INIT(byte ms)
{
    byte prescale;
    prescale = 1;
    word temp;
    T5CON = 0x00;
    T5CONbits.RD16 = 1;
    T5CLK = 0x01;
    for (byte x = 0; x < 4; x++) {
        calculator = ((CRYSTAL_FREKANS / 1000) / (4 * prescale));
        calculator = 1 / calculator;
        calculator = (ms) / calculator;
        if (calculator < 65536) break;
        else {
            prescale *= 2;
            T5CON += 0x10;
        }
    }
    temp = (word) calculator;
    temp = (word) (65536 - temp);
    PIR5bits.TMR5IF = 0;
    TMR5 = temp;
    TIMER_5_TICKS = temp;
    TIMER_5_DUTY(open);
    TIMER_5_INTERRUPT(open);
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TIMER7">
word TIMER_7_TICKS;

void TIMER_7_INTERRUPT_FUNCT()
{
    TMR7 = TIMER_7_TICKS;
}

void TIMER_7_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE5bits.TMR7IE = 1;  // Not: PIC18F67K40'da Timer7 yok
    else if (OpenOrClose == 0) PIE5bits.TMR7IE = 0;
}

void TIMER_7_DUTY(byte startOrStop)
{
    if (startOrStop == 1) T7CONbits.TMR7ON = 1;
    else if (startOrStop == 0) T7CONbits.TMR7ON = 0;
}

void TIMER_7_INIT(byte ms)
{
    byte prescale;
    prescale = 1;
    word temp;
    T7CON = 0x00;
    T7CONbits.RD16 = 1;
    T7CLK = 0x01;
    for (byte x = 0; x < 4; x++) {
        calculator = ((CRYSTAL_FREKANS / 1000) / (4 * prescale));
        calculator = 1 / calculator;
        calculator = (ms) / calculator;
        if (calculator < 65536) break;
        else {
            prescale *= 2;
            T7CON += 0x10;
        }
    }
    temp = (word) calculator;
    temp = (word) (65536 - temp);
    PIR5bits.TMR7IF = 0;
    TMR7 = temp;
    TIMER_7_TICKS = temp;
    TIMER_7_DUTY(open);
    TIMER_7_INTERRUPT(open);
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EEPROM           ">

void EEPROM_B_WRITE(word address, byte data)
{
    byte GIEBitValue = INTCONbits.GIE; // Save interrupt enable
    NVMADRH = ((address >> 8) & 0x03);
    NVMADRL = (address & 0xFF);
    NVMDAT = data;
    NVMCON1bits.NVMREG = 0;
    NVMCON1bits.WREN = 1;
    INTCONbits.GIE = 0; // Disable interrupts
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    __delay_ms(5);
    while (NVMCON1bits.WR);
    NVMCON1bits.WR = 0;
    INTCONbits.GIE = GIEBitValue; // Restore interrupt enable
}

byte EEPROM_B_READ(word address)
{
    NVMADRH = ((address >> 8) & 0x03);
    NVMADRL = (address & 0xFF);
    NVMCON1bits.NVMREG = 0;
    NVMCON1bits.RD = 1;
    __delay_ms(5);
    NOP(); // NOPs may be required for latency at high frequencies
    NOP();
    return (NVMDAT);
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="ADC              ">

void ADC_INIT()
{
    ADRESH, ADRESL = 0;
    ADCON0bits.ADFM = 1; //right justify
    ADCON0bits.ADCS = 1; //FRC Clock
    ADCON0bits.ADON = 1; //Turn ADC On
}

word ADC_READ(byte channel)
{
    word temp;
    ADRESH, ADRESL = 0;
    ADPCH = channel;
    ADCON0bits.GO = 1; //Start conversion

    while (ADCON0bits.GO); //Wait for conversion done
    temp = ADRESH * 256 + ADRESL;
    return temp;
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="PWM              ">

void PWM_1_INIT(dword Hz)
{//PORT C & E
    byte prescale;
    PIN_SET_IO('D', 'O', 'E', 6, 'L');
    RE6PPS = PPS_CCP1;
    T2CON = 0b00000000;
    T2CLKCON = 0x01;
    T2HLT = 0x20;
    PIR5bits.TMR2IF = 0;
    CCP1CON = 0x8C;
    CCPTMRS0bits.C1TSEL1 = 0;
    CCPTMRS0bits.C1TSEL0 = 0;
    prescale = 1;
    for (byte x = 0; x < 8; x++) {

        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T2CON += 0x10;
        }
    }
    T2PR = (byte) (calculator - 1);
}//TMR2

void PWM_1_DUTY(byte duty)
{
    word temp;
    if (duty == 100) duty = 99;
    calculator = duty;
    calculator = calculator * 4 * (T2PR + 1);
    calculator /= 100;
    temp = (word) calculator;
    CCPR1H = (byte) ((temp) >> 8);
    CCPR1L = (byte) (temp & 0xFF);
    if (T2CONbits.TMR2ON == 0) T2CONbits.TMR2ON = 1;

}

void PWM_2_INIT(dword Hz)
{//PORT C & E
    byte prescale;
    PIN_SET_IO('D', 'O', 'E', 6, 'L');
    RE6PPS = PPS_CCP2;
    T4CON = 0b00000000;
    T4CLKCON = 0x01;
    T4HLT = 0x20;
    PIR5bits.TMR4IF = 0;
    CCP2CON = 0x8C;
    CCPTMRS0bits.C2TSEL1 = 0;
    CCPTMRS0bits.C2TSEL0 = 1;
    prescale = 1;
    for (byte x = 0; x < 8; x++) {

        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T4CON += 0x10;
        }
    }
    T4PR = (byte) (calculator - 1);
}//TMR4

void PWM_2_DUTY(byte duty)
{
    word temp;
    if (duty == 100) duty = 99;
    calculator = duty;
    calculator = calculator * 4 * (T4PR + 1);
    calculator /= 100;
    temp = (word) calculator;
    CCPR2H = (byte) ((temp) >> 8);
    CCPR2L = (byte) (temp & 0xFF);
    if (T4CONbits.TMR4ON == 0) T4CONbits.TMR4ON = 1;

}

void PWM_3_INIT(dword Hz)
{//PORT C & E
    byte prescale;
    PIN_SET_IO('D', 'O', 'C', 6, 'L');
    RC6PPS = PPS_CCP3;
    T6CON = 0b00000000;
    T6CLKCON = 0x01;
    T6HLT = 0x20;
    PIR5bits.TMR2IF = 0;
    CCP3CON = 0x8C;
    CCPTMRS0bits.C3TSEL1 = 1;
    CCPTMRS0bits.C3TSEL0 = 0;
    prescale = 1;
    for (byte x = 0; x < 8; x++) {

        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T6CON += 0x10;
        }
    }
    T6PR = (byte) (calculator - 1);
}//TMR6

void PWM_3_DUTY(byte duty)
{
    word temp;
    if (duty == 100) duty = 99;
    calculator = duty;
    calculator = calculator * 4 * (T6PR + 1);
    calculator /= 100;
    temp = (word) calculator;
    CCPR3H = (byte) ((temp) >> 8);
    CCPR3L = (byte) (temp & 0xFF);
    if (T6CONbits.TMR6ON == 0) T6CONbits.TMR6ON = 1;

}

void PWM_4_INIT(dword Hz)
{//PORT E & G
    byte prescale;
    PIN_SET_IO('D', 'O', 'E', 6, 'L');
    RE6PPS = PPS_CCP4;
    T8CON = 0b00000000;
    T8CLKCON = 0x01;
    T8HLT = 0x20;
    PIR5bits.TMR8IF = 0;
    CCP4CON = 0x8C;
    CCPTMRS0bits.C4TSEL1 = 1;
    CCPTMRS0bits.C4TSEL0 = 1;
    prescale = 1;
    for (byte x = 0; x < 8; x++) {

        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T8CON += 0x10;
        }
    }
    T8PR = (byte) (calculator - 1);
}//TMR8

void PWM_4_DUTY(byte duty)
{
    word temp;
    if (duty == 100) duty = 99;
    calculator = duty;
    calculator = calculator * 4 * (T8PR + 1);
    calculator /= 100;
    temp = (word) calculator;
    CCPR4H = (byte) ((temp) >> 8);
    CCPR4L = (byte) (temp & 0xFF);
    if (T8CONbits.TMR8ON == 0) T8CONbits.TMR8ON = 1;

}

void PWM_5_INIT(dword Hz)
{//PORT E & G
    byte prescale;
    PIN_SET_IO('D', 'O', 'G', 0, 'L');
    RG0PPS = PPS_CCP5;
    T8CON = 0b00000000;
    T8CLKCON = 0x01;
    T8HLT = 0x20;
    PIR5bits.TMR8IF = 0;
    CCP5CON = 0x8C;
    CCPTMRS1bits.C5TSEL1 = 1;
    CCPTMRS1bits.C5TSEL0 = 1;
    prescale = 1;
    for (byte x = 0; x < 8; x++) {

        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256) break;
        else {
            prescale *= 2;
            T8CON += 0x10;
        }
    }
    T8PR = (byte) (calculator - 1);
}//TMR8

void PWM_5_DUTY(byte duty)
{
    word temp;
    if (duty == 100) duty = 99;
    calculator = duty;
    calculator = calculator * 4 * (T8PR + 1);
    calculator /= 100;
    temp = (word) calculator;
    CCPR5H = (byte) ((temp) >> 8);
    CCPR5L = (byte) (temp & 0xFF);
    if (T8CONbits.TMR8ON == 0) T8CONbits.TMR8ON = 1;
}

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="USART            ">


// <editor-fold defaultstate="collapsed" desc="USART 1 ">

void UART_1_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE3bits.RC1IE = 1;
    else if (OpenOrClose == 0) PIE3bits.RC1IE = 0;
}

void UART_1_INIT(word baudRate)
{
    byte bitLong = 8;
    qword calculater;
    RX1PPS = PIN_INIT_PPS('C', 6); // PORT C & D
    RC7PPS = PPS_EUSART1_TX; // PORT C & D
    PIN_SET_IO('D', 'I', 'C', 6, 'H');
    PIN_SET_IO('D', 'O', 'C', 7, 'H');
    if (bitLong == 8) {
        RCSTA1bits.RX9 = 0;
        TXSTA1bits.TX9 = 0;
    } else {

        RCSTA1bits.RX9 = 1;
        TXSTA1bits.TX9 = 1;
        RCSTA1bits.CREN = 1;
    }

    calculater = CRYSTAL_FREKANS / 64;
    calculater = calculater / (baudRate);
    SP1BRG = (byte) (calculater - 1);
    TXSTA1bits.TXEN = 1;
    RCSTA1bits.CREN = 1;
    RCSTA1bits.SPEN = 1;
    UART_1_INTERRUPT(open);
}

void UART_1_BYTE(byte out)
{
    while (TX1IF == 0) continue;
    TXREG1 = out;
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
// <editor-fold defaultstate="collapsed" desc="USART 2 ">

void UART_2_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE3bits.RC2IE = 1;
    else if (OpenOrClose == 0) PIE3bits.RC2IE = 0;
}

void UART_2_INIT(word baudRate)
{
    byte bitLong = 0;
    qword calculater;
    RX2PPS = PIN_INIT_PPS('G', 2); // PORT D & G
    RG1PPS = PPS_EUSART2_TX; // PORT D & G
    PIN_SET_IO('D', 'I', 'G', 2, 'H');
    PIN_SET_IO('D', 'O', 'G', 1, 'H');
    if (bitLong == 8) {
        RCSTA2bits.RX9 = 0;
        TXSTA2bits.TX9 = 0;
    } else {
        RCSTA2bits.RX9 = 1;
        TXSTA2bits.TX9 = 1;
    }

    calculater = CRYSTAL_FREKANS / 64;
    calculater = calculater / (baudRate);
    SP2BRG = (byte) (calculater - 1);
    TXSTA2bits.TXEN = 1;
    RCSTA2bits.CREN = 1;
    RCSTA2bits.SPEN = 1;
    UART_2_INTERRUPT(open);
}

void UART_2_BYTE(byte out)
{
    while (TX2IF == 0) continue;
    TXREG2 = out;
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
// <editor-fold defaultstate="collapsed" desc="USART 3 ">

void UART_3_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE4bits.RC3IE = 1;
    else if (OpenOrClose == 0) PIE4bits.RC3IE = 0;
}

void UART_3_INIT(word baudRate)
{
    byte bitLong = 0;
    qword calculater;
    RX3PPS = PIN_INIT_PPS('E', 0); // PORT B & E
    //  RD4PPS = PPS_EUSART3_TX; // PORT B & E
    PIN_SET_IO('D', 'I', 'E', 0, 'H');
    //  PIN_SET_IO('D' , 'O' , 'D' , 4);
    if (bitLong == 8) {
        RCSTA3bits.RX9 = 0;
        TXSTA3bits.TX9 = 0;
    } else {

        RCSTA3bits.RX9 = 1;
        TXSTA3bits.TX9 = 1;
    }

    calculater = CRYSTAL_FREKANS / 64;
    calculater = calculater / (baudRate);
    SP3BRG = (byte) (calculater - 1);
    TXSTA3bits.TXEN = 1;
    RCSTA3bits.CREN = 1;
    RCSTA3bits.SPEN = 1;
    UART_3_INTERRUPT(open);
}

void UART_3_BYTE(byte out)
{

    while (TX3IF == 0) continue;
    TXREG3 = out;
}

void UART_3_STRING(char* text)
{
    while (*text) {
        UART_3_BYTE(*text); // Her karakteri gönder
        text++;
    }
}

void UART_3_DECIMAL(dword val)
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
        UART_3_BYTE(basamak[ i ]);
        i--;
    }
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USART 4 ">

void UART_4_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE4bits.RC4IE = 1;
    else if (OpenOrClose == 0) PIE4bits.RC4IE = 0;
}

void UART_4_INIT(word baudRate)
{
    byte bitLong = 0;
    qword calculater;
    RX4PPS = PIN_INIT_PPS('B', 2); // PORT B & C
    RB4PPS = PPS_EUSART4_TX; // PORT B & C
    PIN_SET_IO('D', 'I', 'B', 2, 'H');
    PIN_SET_IO('D', 'O', 'B', 4, 'H');
    if (bitLong == 8) {
        RCSTA4bits.RX9 = 0;
        TXSTA4bits.TX9 = 0;
    } else {

        RCSTA4bits.RX9 = 1;
        TXSTA4bits.TX9 = 1;
    }

    calculater = CRYSTAL_FREKANS / 64;
    calculater = calculater / (baudRate);
    SP4BRG = (byte) (calculater - 1);
    TXSTA4bits.TXEN = 1;
    RCSTA4bits.CREN = 1;
    RCSTA4bits.SPEN = 1;
    UART_4_INTERRUPT(open);
}

void UART_4_BYTE(byte out)
{

    while (TX4IF == 0) continue;
    TXREG4 = out;
}

void UART_4_STRING(char* text)
{
    while (*text) {
        UART_4_BYTE(*text); // Her karakteri gönder
        text++;
    }
}

void UART_4_DECIMAL(dword val)
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
        UART_4_BYTE(basamak[ i ]);
        i--;
    }
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USART 5 ">

void UART_5_INTERRUPT(byte OpenOrClose)
{
    if (OpenOrClose == 1) PIE4bits.RC5IE = 1;
    else if (OpenOrClose == 0) PIE4bits.RC5IE = 0;
}

void UART_5_INIT(word baudRate)
{
    byte bitLong = 0;
    qword calculater;
    RX5PPS = PIN_INIT_PPS('E', 4); // PORT E & G
    RE6PPS = PPS_EUSART5_TX; // PORT E & G
    PIN_SET_IO('D', 'I', 'E', 4, 'H');
    PIN_SET_IO('D', 'O', 'E', 6, 'H');
    if (bitLong == 8) {
        RCSTA5bits.RX9 = 0;
        TXSTA5bits.TX9 = 0;
    } else {

        RCSTA5bits.RX9 = 1;
        TXSTA5bits.TX9 = 1;
    }

    calculater = CRYSTAL_FREKANS / 64;
    calculater = calculater / (baudRate);
    SP5BRG = (byte) (calculater - 1);
    TXSTA5bits.TXEN = 1;
    RCSTA5bits.CREN = 1;
    RCSTA5bits.SPEN = 1;
    UART_5_INTERRUPT(open);
}

void UART_5_BYTE(byte out)
{

    while (TX5IF == 0) continue;
    TXREG5 = out;
}

void UART_5_STRING(char* text)
{
    while (*text) {
        UART_5_BYTE(*text); // Her karakteri gönder
        text++;
    }
}

void UART_5_DECIMAL(dword val)
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
        UART_5_BYTE(basamak[ i ]);
        i--;
    }
}
// </editor-fold> 

// </editor-fold> 


#endif
