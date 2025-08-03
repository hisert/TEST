#include "PIC_18F67K40.h"

#ifdef __18F67K40
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
    else if (Port == 'F') work_adress = (&ANSELF);
    else if (Port == 'G') work_adress = (&ANSELG);
    work_adress = work_adress + Port;
    if ((AnalogOrDijital == 'D')) *work_adress = *work_adress & ~hex;
    if ((AnalogOrDijital == 'A')) *work_adress = *work_adress | hex;

}

void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow)
{
    PIN_SET_LAT(Port, Pin, HighOrLow);
    PIN_SET_TRIS(Port, Pin, InputOrOutput);
    //   PIN_SET_ANSEL(Port, Pin, AnalogOrDijital);
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
    byte hex = (byte) (1 << Pin);
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
    byte hex = (byte) (1 << Pin);
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
    PIE0bits.IOCIE = open;
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="SYSTEM         ">

void MCU_INIT(byte Mhz)
{
    __delay_ms(50);
    OSCFRQ = 0b00001000;
    ANSELA = 0;
    ANSELB = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;
    ANSELG = 0;
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

void TIMER_1_INIT(word ms)
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

void TIMER_3_INIT(word ms)
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

void TIMER_5_INIT(word ms)
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
    if (OpenOrClose == 1) PIE5bits.TMR7IE = 1; // Not: PIC18F67K40'da Timer7 yok
    else if (OpenOrClose == 0) PIE5bits.TMR7IE = 0;
}

void TIMER_7_DUTY(byte startOrStop)
{
    if (startOrStop == 1) T7CONbits.TMR7ON = 1;
    else if (startOrStop == 0) T7CONbits.TMR7ON = 0;
}

void TIMER_7_INIT(word ms)
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
// <editor-fold defaultstate="collapsed" desc="PWM HELPER             ">
#define PWM_USING_TIMER 2
byte PWM_1_TIMER_SELECT = 0;
byte PWM_2_TIMER_SELECT = 0;
byte PWM_3_TIMER_SELECT = 0;
byte PWM_4_TIMER_SELECT = 0;
byte PWM_5_TIMER_SELECT = 0;
byte PWM_6_TIMER_SELECT = 0;
byte PWM_7_TIMER_SELECT = 0;

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
        if (timer == 2) CCPTMRS0bits.C4TSEL = 0b00;
        if (timer == 4) CCPTMRS0bits.C4TSEL = 0b01;
        if (timer == 6) CCPTMRS0bits.C4TSEL = 0b10;
        if (timer == 8) CCPTMRS0bits.C4TSEL = 0b11;
        PWM_4_TIMER_SELECT = timer;
    }
    if (Channel == 5) {
        if (timer == 2) CCPTMRS1bits.C5TSEL = 0b00;
        if (timer == 4) CCPTMRS1bits.C5TSEL = 0b01;
        if (timer == 6) CCPTMRS1bits.C5TSEL = 0b10;
        if (timer == 8) CCPTMRS1bits.C5TSEL = 0b11;
        PWM_5_TIMER_SELECT = timer;
    }
    if (Channel == 6) {
        if (timer == 2) CCPTMRS1bits.P6TSEL = 0b00;
        if (timer == 4) CCPTMRS1bits.P6TSEL = 0b01;
        if (timer == 6) CCPTMRS1bits.P6TSEL = 0b10;
        if (timer == 8) CCPTMRS1bits.P6TSEL = 0b11;
        PWM_6_TIMER_SELECT = timer;
    }
    if (Channel == 7) {
        if (timer == 2) CCPTMRS1bits.P7TSEL = 0b00;
        if (timer == 4) CCPTMRS1bits.P7TSEL = 0b01;
        if (timer == 6) CCPTMRS1bits.P7TSEL = 0b10;
        if (timer == 8) CCPTMRS1bits.P7TSEL = 0b11;
        PWM_7_TIMER_SELECT = timer;
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

    if (timer == 2) return T2PR;
    if (timer == 4) return T4PR;
    if (timer == 6) return T6PR;
    if (timer == 8) return T8PR;
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER2            ">

void PWM_TIMER_2_SET(byte openOrClose)
{
    if (openOrClose) T2CONbits.TMR2ON = 1;
    else T2CONbits.TMR2ON = 0;
}

void PWM_TIMER_2_INIT(dword Hz)
{
    byte prescale;
    T2CON = 0b00000000;
    T2CLKCON = 0x01;
    T2HLT = 0x20;
    PIR5bits.TMR2IF = 0;
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
    PWM_TIMER_2_SET(1);
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER4            ">

void PWM_TIMER_4_SET(byte openOrClose)
{
    if (openOrClose) T4CONbits.ON = 1; // Timer4'ü ba?lat
    else T4CONbits.ON = 0; // Timer4'ü durdur
}

void PWM_TIMER_4_INIT(dword Hz)
{
    byte prescale;
    dword calculator;

    T4CON = 0x00; // Timer4'ü kapat
    T4CLKCON = 0x01; // Timer4 için saat kayna??n? LFINTOSC (31 kHz) olarak ayarla
    T4HLT = 0x20; // Timer4'ü "Roll over pulse" modunda ayarla
    PIR5bits.TMR4IF = 0; // Timer4 kesilme bayra??n? temizle

    prescale = 1;
    for (byte x = 0; x < 8; x++) {
        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256)
            break;
        else {
            prescale *= 2;
            T4CONbits.CKPS = x; // Prescaler'? ayarla
        }
    }

    T4PR = (byte) (calculator - 1); // Timer4 periyodunu ayarla
    PWM_TIMER_4_SET(1); // Timer4'ü ba?lat
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER6            ">

void PWM_TIMER_6_SET(byte openOrClose)
{
    if (openOrClose) T6CONbits.ON = 1; // Timer6'y? ba?lat
    else T6CONbits.ON = 0; // Timer6'y? durdur
}

void PWM_TIMER_6_INIT(dword Hz)
{
    byte prescale;
    dword calculator;

    T6CON = 0x00; // Timer6'y? kapat
    T6CLKCON = 0x01; // Timer6 için saat kayna??n? LFINTOSC (31 kHz) olarak ayarla
    T6HLT = 0x20; // Timer6'y? "Roll over pulse" modunda ayarla
    PIR5bits.TMR6IF = 0; // Timer6 kesilme bayra??n? temizle

    prescale = 1;
    for (byte x = 0; x < 8; x++) {
        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256)
            break;
        else {
            prescale *= 2;
            T6CONbits.CKPS = x; // Prescaler'? ayarla
        }
    }

    T6PR = (byte) (calculator - 1); // Timer6'n?n periyodunu ayarla
    PWM_TIMER_6_SET(1); // Timer6'y? ba?lat
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER8            ">

void PWM_TIMER_8_SET(byte openOrClose)
{
    if (openOrClose) T8CONbits.ON = 1; // Timer8'i ba?lat
    else T8CONbits.ON = 0; // Timer8'i durdur
}

void PWM_TIMER_8_INIT(dword Hz)
{
    byte prescale;
    dword calculator;

    T8CON = 0x00; // Timer8'i kapat
    T8CLKCON = 0x01; // Timer8 için saat kayna??n? LFINTOSC (31 kHz) olarak ayarla
    T8HLT = 0x20; // Timer8'i "Roll over pulse" modunda ayarla
    PIR5bits.TMR8IF = 0; // Timer8 kesilme bayra??n? temizle

    prescale = 1;
    for (byte x = 0; x < 8; x++) {
        calculator = CRYSTAL_FREKANS / (prescale * Hz);
        if ((word) (calculator) <= 256)
            break;
        else {
            prescale *= 2;
            T8CONbits.CKPS = x; // Prescaler'? ayarla
        }
    }

    T8PR = (byte) (calculator - 1); // Timer8'in periyodunu ayarla
    PWM_TIMER_8_SET(1); // Timer8'i ba?lat
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="PWM1           ">

void PWM_1_INIT()
{//PORT C & E
    PIN_SET_IO('D', 'O', 'C', 2, 'L');
    RC2PPS = PPS_CCP1;
    CCP1CON = 0x8C;
    PWM_TIMER_CHOOSE(1, PWM_USING_TIMER);
}

void PWM_1_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(1), duty);
    CCPR1H = (byte) ((temp) >> 8);
    CCPR1L = (byte) (temp & 0xFF);
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="PWM2           ">

void PWM_2_INIT()
{//PORT C & E
    PIN_SET_IO('D', 'O', 'C', 3, 'L');
    RC3PPS = PPS_CCP2;
    CCP2CON = 0x8C;
    PWM_TIMER_CHOOSE(2, PWM_USING_TIMER);
}

void PWM_2_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(2), duty);
    CCPR2H = (byte) ((temp) >> 8);
    CCPR2L = (byte) (temp & 0xFF);
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="PWM3           ">

void PWM_3_INIT()
{//PORT C & E
    PIN_SET_IO('D', 'O', 'E', 2, 'L');
    RE2PPS = PPS_CCP3;
    CCP3CON = 0x8C;
    PWM_TIMER_CHOOSE(3, PWM_USING_TIMER);
}

void PWM_3_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(3), duty);
    CCPR3H = (byte) ((temp) >> 8);
    CCPR3L = (byte) (temp & 0xFF);
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="PWM4           ">

void PWM_4_INIT()
{//PORT G & E
    PIN_SET_IO('D', 'O', 'E', 3, 'L');
    RE3PPS = PPS_CCP4;
    CCP4CON = 0x8C;
    PWM_TIMER_CHOOSE(4, PWM_USING_TIMER);
}

void PWM_4_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(4), duty);
    CCPR4H = (byte) ((temp) >> 8);
    CCPR4L = (byte) (temp & 0xFF);
}
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="PWM5           ">

void PWM_5_INIT()
{//PORT G & E
    PIN_SET_IO('D', 'O', 'E', 4, 'L');
    RE4PPS = PPS_CCP5;
    CCP5CON = 0x8C;
    PWM_TIMER_CHOOSE(5, PWM_USING_TIMER);
}

void PWM_5_DUTY(byte duty)
{
    word temp = PWM_DUTY_CALCULATER(PWM_TIMER_GET(5), duty);
    CCPR5H = (byte) ((temp) >> 8);
    CCPR5L = (byte) (temp & 0xFF);
}
// </editor-fold> 

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
    RCSTA1bits.RX9 = 0;
    TXSTA1bits.TX9 = 0;

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
    qword calculater;
    RX2PPS = PIN_INIT_PPS('G', 2); // PORT D & G
    RG1PPS = PPS_EUSART2_TX; // PORT D & G
    PIN_SET_IO('D', 'I', 'G', 2, 'H');
    PIN_SET_IO('D', 'O', 'G', 1, 'H');
    RCSTA2bits.RX9 = 0;
    TXSTA2bits.TX9 = 0;
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

    qword calculater;
    RX3PPS = PIN_INIT_PPS('E', 3); // PORT B & E
    RE7PPS = PPS_EUSART3_TX; // PORT B & E
  //  PIN_SET_IO('D', 'I', 'E', 3, 'H');
 //   PIN_SET_IO('D', 'O', 'E', 7, 'H');
    RCSTA3bits.RX9 = 0;
    TXSTA3bits.TX9 = 0;

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
    while (!TX3STAbits.TRMT);
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
    qword calculater;
    RX4PPS = PIN_INIT_PPS('B', 2); // PORT B & C
    RB4PPS = PPS_EUSART4_TX; // PORT B & C
    PIN_SET_IO('D', 'I', 'B', 2, 'H');
    PIN_SET_IO('D', 'O', 'B', 4, 'H');
    RCSTA4bits.RX9 = 0;
    TXSTA4bits.TX9 = 0;

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
    qword calculater;

    RX5PPS = PIN_INIT_PPS('E', 4); // PORT E & G
    RE6PPS = PPS_EUSART5_TX; // PORT E & G
    PIN_SET_IO('D', 'I', 'E', 4, 'H');
    PIN_SET_IO('D', 'O', 'E', 6, 'H');
    RCSTA5bits.RX9 = 0;
    TXSTA5bits.TX9 = 0;

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

void(*UART_1_INTERRUPT_FUNCT_POINTER)(byte);
void(*UART_2_INTERRUPT_FUNCT_POINTER)(byte);
void(*UART_3_INTERRUPT_FUNCT_POINTER)(byte);
void(*UART_4_INTERRUPT_FUNCT_POINTER)(byte);
void(*UART_5_INTERRUPT_FUNCT_POINTER)(byte);
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

void UART_3_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_3_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_3_INIT(baudrate);
    UART_3_INTERRUPT_FUNCT_POINTER = UART_3_INTERRUPT_FUNCT_POINTER_t;
}

void UART_4_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_4_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_4_INIT(baudrate);
    UART_4_INTERRUPT_FUNCT_POINTER = UART_4_INTERRUPT_FUNCT_POINTER_t;
}

void UART_5_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_5_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_5_INIT(baudrate);
    UART_5_INTERRUPT_FUNCT_POINTER = UART_5_INTERRUPT_FUNCT_POINTER_t;
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
    if (PIR5bits.TMR1IF) {
        PIR5bits.TMR1IF = 0;
        TIMER_1_INTERRUPT_FUNCT();
        TIMER_1_INTERRUPT_FUNCT_POINTER();
    } else if (PIR5bits.TMR3IF) {
        PIR5bits.TMR3IF = 0;
        TIMER_3_INTERRUPT_FUNCT();
        TIMER_3_INTERRUPT_FUNCT_POINTER();
        TIMER_3_INTERRUPT_FUNCT();
    } else if (PIR5bits.TMR5IF) {
        PIR5bits.TMR5IF = 0;
        TIMER_5_INTERRUPT_FUNCT();
        TIMER_5_INTERRUPT_FUNCT_POINTER();
        TIMER_5_INTERRUPT_FUNCT();
    } else if (PIR5bits.TMR7IF) {
        PIR5bits.TMR7IF = 0;
    } else if (PIR3bits.RC1IF) UART_1_INTERRUPT_FUNCT_POINTER(RC1REG);
    else if (PIR3bits.RC2IF) UART_2_INTERRUPT_FUNCT_POINTER(RC2REG);
    else if (PIR4bits.RC3IF) UART_3_INTERRUPT_FUNCT_POINTER(RC3REG);
    else if (PIR4bits.RC4IF) UART_4_INTERRUPT_FUNCT_POINTER(RC4REG);
    else if (PIR4bits.RC5IF) UART_5_INTERRUPT_FUNCT_POINTER(RC5REG);
    else if (PIE0bits.IOCIE) {
        // <editor-fold defaultstate="collapsed" desc="IOC B ">
        if (IOCBF) {
            if (IOCBFbits.IOCBF0) IOCBFbits.IOCBF0 = 0;
            else if (IOCBFbits.IOCBF1) IOCBFbits.IOCBF1 = 0;
            else if (IOCBFbits.IOCBF2) IOCBFbits.IOCBF2 = 0;
            else if (IOCBFbits.IOCBF3) IOCBFbits.IOCBF3 = 0;
            else if (IOCBFbits.IOCBF4) IOCBFbits.IOCBF4 = 0;
            else if (IOCBFbits.IOCBF5) IOCBFbits.IOCBF5 = 0;
            else if (IOCBFbits.IOCBF6) IOCBFbits.IOCBF6 = 0;
            else if (IOCBFbits.IOCBF7) IOCBFbits.IOCBF7 = 0;
        }
        // </editor-fold> 
        // <editor-fold defaultstate="collapsed" desc="IOC C ">
        if (IOCCF) {
            if (IOCEFbits.IOCEF0)IOCEFbits.IOCEF0 = 0;
            else if (IOCEFbits.IOCEF1) IOCEFbits.IOCEF1 = 0;
            else if (IOCEFbits.IOCEF2) IOCEFbits.IOCEF2 = 0;
            else if (IOCEFbits.IOCEF3) IOCEFbits.IOCEF3 = 0;
            else if (IOCEFbits.IOCEF4) IOCEFbits.IOCEF4 = 0;
            else if (IOCEFbits.IOCEF5) IOCEFbits.IOCEF5 = 0;
            else if (IOCEFbits.IOCEF6) IOCEFbits.IOCEF6 = 0;
            else if (IOCEFbits.IOCEF7) IOCEFbits.IOCEF7 = 0;
        }
        // </editor-fold> 
        // <editor-fold defaultstate="collapsed" desc="IOC E ">
        if (IOCEF) {
            if (IOCEFbits.IOCEF0)IOCEFbits.IOCEF0 = 0;
            else if (IOCEFbits.IOCEF1) IOCEFbits.IOCEF1 = 0;
            else if (IOCEFbits.IOCEF2) IOCEFbits.IOCEF2 = 0;
            else if (IOCEFbits.IOCEF3) IOCEFbits.IOCEF3 = 0;
            else if (IOCEFbits.IOCEF4) IOCEFbits.IOCEF4 = 0;
            else if (IOCEFbits.IOCEF5) IOCEFbits.IOCEF5 = 0;
            else if (IOCEFbits.IOCEF6) IOCEFbits.IOCEF6 = 0;
            else if (IOCEFbits.IOCEF7) IOCEFbits.IOCEF7 = 0;
        }
        // </editor-fold> 
        // <editor-fold defaultstate="collapsed" desc="IOC G ">
        if (IOCGF) {
            if (IOCGFbits.IOCGF5) IOCGFbits.IOCGF5 = 0;
        }
        // </editor-fold> 
    }

}


#endif
