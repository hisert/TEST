#include "PIC_18F87K22.h"
#include <xc.h>

// <editor-fold defaultstate="collapsed" desc="PIN IO">

byte PIN_GET_PORT(byte Port, byte Pin)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&PORTA) + (Port - 'A');
    if (Port == 'J') work_adress = (&PORTJ);
    if (Port == 'F') work_adress = (&PORTF);
    if ((*work_adress) & hex) return 1;
    else return 0;
}

void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&LATA) + (Port - 'A');
    if (Port == 'J') work_adress = (&LATJ);
    if (Port == 'F') work_adress = (&LATF);
    if ((HighOrLow == 'L') || (HighOrLow == 'l') || (HighOrLow == 0)) *work_adress = *work_adress & ~hex;
    else if ((HighOrLow == 'H') || (HighOrLow == 'h') || (HighOrLow == 1)) *work_adress = *work_adress | hex;
}

void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&TRISA) + (Port - 'A');
    if (Port == 'J') work_adress = (&TRISJ);
    if (Port == 'F') work_adress = (&TRISF);
    if ((InputOrOutput == 'O') || (InputOrOutput == 'o') || (InputOrOutput == 0)) *work_adress = *work_adress & ~hex;
    else if ((InputOrOutput == 'I') || (InputOrOutput == 'i') || (InputOrOutput == 1)) *work_adress = *work_adress | hex;

}

void PIN_SET_LAT_TOGGLE(byte Port, byte Pin)
{
    byte hex = (byte) (1 << Pin);
    volatile byte *work_adress;
    work_adress = (&LATA) + (Port - 'A');
    if (Port == 'J') work_adress = (&LATJ);
    if (Port == 'F') work_adress = (&LATF);
    *work_adress ^= hex; // XOR i?lemi ile pini toggle et
}

void PIN_SET_ANSEL(byte Pin, byte OnOFF)
{
    if (Pin == 0xFF) {
        ANCON0 = 0;
        ANCON1 = 0;
        ANCON2 = 0;
        return;
    }
    if (Pin == 0) ANSEL0 = OnOFF;
    else if (Pin == 0) ANSEL0 = OnOFF;
    else if (Pin == 1) ANSEL1 = OnOFF;
    else if (Pin == 2) ANSEL2 = OnOFF;
    else if (Pin == 3) ANSEL3 = OnOFF;
    else if (Pin == 1) ANSEL1 = OnOFF;
    else if (Pin == 4) ANSEL4 = OnOFF;
    else if (Pin == 5) ANSEL5 = OnOFF;
    else if (Pin == 6) ANSEL6 = OnOFF;
    else if (Pin == 7) ANSEL7 = OnOFF;
    else if (Pin == 8) ANSEL8 = OnOFF;
    else if (Pin == 9) ANSEL9 = OnOFF;
    else if (Pin == 10) ANSEL10 = OnOFF;
    else if (Pin == 11) ANSEL11 = OnOFF;
    else if (Pin == 16) ANSEL16 = OnOFF;
    else if (Pin == 17) ANSEL17 = OnOFF;
    else if (Pin == 18) ANSEL18 = OnOFF;
    else if (Pin == 19) ANSEL19 = OnOFF;
}

void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow)
{
    PIN_SET_LAT(Port, Pin, HighOrLow);
    PIN_SET_TRIS(Port, Pin, InputOrOutput);
}

void PIN_IOC_INTERRUPT(byte Pin, byte openOrClose)
{
    if (openOrClose) INTCONbits.RBIE = 1;
    else INTCONbits.RBIE = 0;
}
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
    if (openOrClose) PIE1bits.TMR1IE = 1;
    else PIE1bits.TMR1IE = 0;
}

void TIMER_1_SET(byte startOrStop)
{
    if (startOrStop) T1CONbits.TMR1ON = 1;
    else T1CONbits.TMR1ON = 0;
}

word TIMER_1_INIT(byte ms)
{
    unsigned long Fosc = _XTAL_FREQ; // Sistem frekans?
    unsigned long Fcy = Fosc / 4; // Timer kaynak frekans? (Fosc/4)
    byte Prescalers[] = {1, 2, 4, 8}; // Mümkün olan prescaler de?erleri
    word TMR1_Tick = 0;

    for (int i = 0; i < 4; i++) {
        unsigned long TimerFreq = Fcy / Prescalers[i]; // Timer1 frekans?
        unsigned long TickValue = (TimerFreq / 1000) * ms; // Gerekli say?m de?eri

        if (TickValue <= 65536) // 16-bit Timer1 s?n?r?nda m??
        {
            T1CONbits.T1CKPS = i; // Prescaler de?erini ayarla
            TMR1_Tick = 65536 - TickValue; // TMR1'e yükleme de?eri
            break;
        }
    }
    TIMER_1_SET(1);
    TIMER_1_INTERRUPT(1);
    TIMER_1_TICK = TMR1_Tick;
    TMR1 = TIMER_1_TICK;
    return TMR1_Tick;
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
    if (openOrClose) PIE2bits.TMR3IE = 1;
    else PIE2bits.TMR3IE = 0;
}

void TIMER_3_SET(byte startOrStop)
{
    if (startOrStop) T3CONbits.TMR3ON = 1;
    else T3CONbits.TMR3ON = 0;
}

word TIMER_3_INIT(byte ms)
{
    unsigned long Fosc = _XTAL_FREQ; // Sistem frekans?
    unsigned long Fcy = Fosc / 4; // Timer kaynak frekans? (Fosc/4)
    byte Prescalers[] = {1, 2, 4, 8}; // Mümkün olan prescaler de?erleri
    word TMR3_Tick = 0;

    for (int i = 0; i < 4; i++) {
        unsigned long TimerFreq = Fcy / Prescalers[i]; // Timer3 frekans?
        unsigned long TickValue = (TimerFreq / 1000) * ms; // Gerekli say?m de?eri

        if (TickValue <= 65536) // 16-bit Timer3 s?n?r?nda m??
        {
            T3CONbits.T3CKPS = i; // Prescaler de?erini ayarla
            TMR3_Tick = 65536 - TickValue; // TMR3'e yükleme de?eri
            break;
        }
    }
    TIMER_3_SET(1); // Timer3'ü ba?lat
    TIMER_3_INTERRUPT(1); // Kesme aç
    TIMER_3_TICK = TMR3_Tick;
    TMR3 = TIMER_3_TICK; // Timer3'e de?er yükle
    return TMR3_Tick;
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
    if (openOrClose) PIE5bits.TMR5IE = 1;
    else PIE5bits.TMR5IE = 0;
}

void TIMER_5_SET(byte startOrStop)
{
    if (startOrStop) T5CONbits.TMR5ON = 1;
    else T5CONbits.TMR5ON = 0;
}

word TIMER_5_INIT(byte ms)
{
    unsigned long Fosc = _XTAL_FREQ; // Sistem frekans?
    unsigned long Fcy = Fosc / 4; // Timer kaynak frekans? (Fosc/4)
    byte Prescalers[] = {1, 2, 4, 8}; // Mümkün olan prescaler de?erleri
    word TMR5_Tick = 0;

    for (int i = 0; i < 4; i++) {
        unsigned long TimerFreq = Fcy / Prescalers[i]; // Timer5 frekans?
        unsigned long TickValue = (TimerFreq / 1000) * ms; // Gerekli say?m de?eri

        if (TickValue <= 65536) // 16-bit Timer5 s?n?r?nda m??
        {
            T5CONbits.T5CKPS = i; // Prescaler de?erini ayarla
            TMR5_Tick = 65536 - TickValue; // TMR5'e yükleme de?eri
            break;
        }
    }
    TIMER_5_SET(1); // Timer5'i ba?lat
    TIMER_5_INTERRUPT(1); // Kesme aç
    TIMER_5_TICK = TMR5_Tick;
    TMR5 = TIMER_5_TICK; // Timer5'e de?er yükle
    return TMR5_Tick;
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="UART 1">

void UART_1_INTERRUPT(byte openOrClose)
{
    //   PIE1bits.TXIE = 1; // Verici interrupt'?n? aç
    if (openOrClose) PIE1bits.RCIE = 1;
    else PIE1bits.RCIE = 0;
}

void UART_1_INIT(unsigned long baudrate)
{
    PIN_SET_IO('D', 'O', 'C', 6, 'H');
    PIN_SET_IO('D', 'I', 'C', 7, 'H');
    unsigned int spbrg_value = (_XTAL_FREQ / (16 * baudrate)) - 1; // 16 ile bölme yaparak daha yüksek baud h?zlar?n? elde edebilirsiniz.
    TXSTA1bits.SYNC = 0; // Asenkron mod
    TXSTA1bits.TX9 = 0; // 8-bit veri
    RCSTA1bits.RX9 = 0; // 8-bit veri
    RCSTA1bits.SPEN = 1; // Serbest Port
    TXSTA1bits.TXEN = 1; // TX aktif
    RCSTA1bits.CREN = 1; // RX aktif
    TXSTA1bits.BRGH = 1; // Yüksek baud rate kullan?m? (BRGH bitini 1 yap)
    SPBRG1 = spbrg_value;
    UART_1_INTERRUPT(1);
}

void UART_1_BYTE(char data)
{
    while (!TXSTA1bits.TRMT); // E?er veri gönderecek yer yoksa bekle
    TXREG1 = data; // Veriyi gönder
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
// <editor-fold defaultstate="collapsed" desc="UART 2">

void UART_2_INTERRUPT(byte openOrClose)
{
    // PIE3bits.TX2IE = 1; // Verici interrupt'?n? aç
    if (openOrClose) PIE3bits.RC2IE = 1; // UART2 al?c? interrupt'?
    else PIE3bits.RC2IE = 0; // UART2 al?c? interrupt'? kapal?
}

void UART_2_INIT(unsigned long baudrate)
{
    PIN_SET_IO('D', 'O', 'G', 1, 'H');
    PIN_SET_IO('D', 'I', 'G', 2, 'H');
    PIN_SET_ANSEL(18, 0);
    unsigned int spbrg_value = (_XTAL_FREQ / (16 * baudrate)) - 1; // 16 ile bölme yaparak daha yüksek baud h?zlar?n? elde edebilirsiniz.

    TXSTA2bits.SYNC = 0; // Asenkron mod
    TXSTA2bits.TX9 = 0; // 8-bit veri
    RCSTA2bits.RX9 = 0; // 8-bit veri
    RCSTA2bits.SPEN = 1; // Serbest Port
    TXSTA2bits.TXEN = 1; // TX aktif
    RCSTA2bits.CREN = 1; // RX aktif
    TXSTA2bits.BRGH = 1; // Yüksek baud rate kullan?m? (BRGH bitini 1 yap)

    // UART2 için baudrate hesaplama
    SPBRG2 = spbrg_value;

    // UART2 interruptlar?n? aktif et
    UART_2_INTERRUPT(1); // Al?c? interrupt'?n? aç

}

void UART_2_BYTE(char data)
{
    while (!TXSTA2bits.TRMT); // E?er veri gönderecek yer yoksa bekle
    TXREG2 = data; // Veriyi UART2 üzerinden gönder
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
// <editor-fold defaultstate="collapsed" desc="SYSTEM">

void SET_OSC(byte MHz)
{
    if (MHz > 16) {
        MHz = MHz / 4;
        OSCTUNEbits.PLLEN = 1; // 4x PLL'i etkinle?tir
    }
    OSCCON = (MHz == 16) ? 0b01110000 :
            (MHz == 8) ? 0b01101000 :
            (MHz == 4) ? 0b01100000 :
            (MHz == 2) ? 0b01011000 :
            0b01110000; // Varsay?lan: 16 MHz

    while (!OSCCONbits.HFIOFS); // Osilatör stabil olana kadar bekle
}

void INTERRUPT_ALL(byte openOrClose)
{
    INTCONbits.PEIE = 1;
    if (openOrClose) INTCONbits.GIE = 1;
    else INTCONbits.GIE = 0;
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="ADC ">

void ADC_INIT()
{
    ADCON0bits.ADON = 0;
    ADCON1bits.VCFG1 = 0; // Vref- = VSS
    ADCON1bits.VCFG0 = 0; // Vref+ = VDD
    ADCON2bits.ADCS = 0b010; // ADC frekans?n? Fosc/32 yap
    ADCON2bits.ACQT = 0b010; // 4 Tad (Tad = 32 Fosc)
    ADCON0bits.ADON = 1;
}

unsigned int ADC_READ(unsigned char channel)
{
    ADCON0bits.CHS = channel; // Kanal numaras?n? seç (0-13 aras?nda)
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ((ADRESH << 4) + (ADRESL >> 4)); // 12-bit de?er için do?ru ?ekilde birle?tir
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="I2C 1">

void I2C_1_INIT(unsigned long baudrate)
{
    PIN_SET_IO('D', 'I', 'C', 3, 'L');
    PIN_SET_IO('D', 'I', 'C', 4, 'L');
    SSP1ADD = ((_XTAL_FREQ / 4) / baudrate) - 1; // H?z hesaplama
    SSP1CON1bits.SSPM = 0b1000; // Master mode, I2C Clock = Fosc/4 (Fosc = sistem saati)
    SSP1CON1bits.SSPEN = 1; // Seri portu etkinle?tir
}

void I2C_1_ACK(void)
{
    SSP1CON2bits.ACKDT = 0; /* Acknowledge data 1:NACK,0:ACK */
    SSP1CON2bits.ACKEN = 1; /* Enable ACK to send */
    while (SSP1CON2bits.ACKEN);
}

void I2C_1_NACK(void)
{
    SSP1CON2bits.ACKDT = 1; /* Acknowledge data 1:NACK,0:ACK */
    SSP1CON2bits.ACKEN = 1; /* Enable ACK to send */
    while (SSP1CON2bits.ACKEN);
}

void I2C_1_READY(void)
{
    byte temp = 0;
    while (SSP1STATbits.BF || (SSP1STATbits.R_nW)) {
        temp++;
        NOP();
        if (temp == 255) break;
    }
    PIR1bits.SSP1IF = 0; /* Clear SSPIF interrupt flag*/
}

byte I2C_1_WRITE(byte data)
{
    SSP1BUF = data; /* Write data to SSPBUF */
    // for (byte x = 0; x < 8; x++) NOP();
    I2C_1_READY(); /* Wait for data transmission to complete */

    if (SSP1CON2bits.ACKSTAT) return 1; /* No ACK received */
    else return 0; /* ACK received */
}

void I2C_1_START(void)
{
    SSP1CON2bits.SEN = 1; /* Send start pulse */
    while (SSP1CON2bits.SEN); /* Wait for completion of start pulse */
    PIR1bits.SSP1IF = 0;
}

byte I2C_1_STOP(void)
{
    I2C_1_READY();
    SSP1CON2bits.PEN = 1; /* Send stop pulse */
    while (SSP1CON2bits.PEN); /* Wait for stop pulse to complete */
    PIR1bits.SSP1IF = 0;
    if (!SSP1STATbits.P) return 0; /* If not successful, return 0 */
    return 1; /* Success */
}

byte I2C_1_READ(byte flag)
{
    byte buffer = 0;
    SSP1CON2bits.RCEN = 1; /* Enable receive */

    /* Wait for buffer full flag (byte received) */
    while (!SSP1STATbits.BF);
    buffer = SSP1BUF; /* Copy received byte to buffer */

    /* Send acknowledgment or negative acknowledgment */
    if (flag == 0) I2C_1_ACK(); /* ACK */
    else I2C_1_NACK(); /* NACK */
    I2C_1_READY(); /* Wait for ready state */
    return buffer;
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="I2C 2">

void I2C_2_INIT(unsigned long baudrate)
{
    PIN_SET_IO('D', 'I', 'D', 6, 'L'); // SDA2
    PIN_SET_IO('D', 'I', 'D', 5, 'L'); // SCL2
    SSP2ADD = ((_XTAL_FREQ / 4) / baudrate) - 1; // H?z hesaplama
    SSP2CON1bits.SSPM = 0b1000; // Master mode, I2C Clock = Fosc/4 (Fosc = sistem saati)
    SSP2CON1bits.SSPEN = 1; // Seri portu etkinle?tir
}

void I2C_2_ACK(void)
{
    SSP2CON2bits.ACKDT = 0; /* Acknowledge data 1:NACK,0:ACK */
    SSP2CON2bits.ACKEN = 1; /* Enable ACK to send */
    while (SSP2CON2bits.ACKEN);
}

void I2C_2_NACK(void)
{
    SSP2CON2bits.ACKDT = 1; /* Acknowledge data 1:NACK,0:ACK */
    SSP2CON2bits.ACKEN = 1; /* Enable ACK to send */
    while (SSP2CON2bits.ACKEN);
}

void I2C_2_READY(void)
{
    byte temp = 0;
    while (SSP2STATbits.BF || (SSP2STATbits.R_nW)) {
        temp++;
        __delay_us(1);
        if (temp == 255) break;
    }
    PIR2bits.SSP2IF = 0; /* Clear SSPIF interrupt flag*/
}

byte I2C_2_WRITE(byte data)
{
    SSP2BUF = data; /* Write data to SSPBUF */
    for (byte x = 0; x < 8; x++) NOP();
    I2C_2_READY(); /* Wait for data transmission to complete */

    if (SSP2CON2bits.ACKSTAT) return 1; /* No ACK received */
    else return 0; /* ACK received */
}

void I2C_2_START(void)
{
    SSP2CON2bits.SEN = 1; /* Send start pulse */
    while (SSP2CON2bits.SEN); /* Wait for completion of start pulse */
    PIR2bits.SSP2IF = 0;
}

byte I2C_2_STOP(void)
{
    I2C_2_READY();
    SSP2CON2bits.PEN = 1; /* Send stop pulse */
    while (SSP2CON2bits.PEN); /* Wait for stop pulse to complete */
    PIR2bits.SSP2IF = 0;
    if (!SSP2STATbits.P) return 0; /* If not successful, return 0 */
    return 1; /* Success */
}

byte I2C_2_READ(byte flag)
{
    byte buffer = 0;
    SSP2CON2bits.RCEN = 1; /* Enable receive */

    /* Wait for buffer full flag (byte received) */
    while (!SSP2STATbits.BF);
    buffer = SSP2BUF; /* Copy received byte to buffer */

    /* Send acknowledgment or negative acknowledgment */
    if (flag == 0) I2C_2_ACK(); /* ACK */
    else I2C_2_NACK(); /* NACK */
    I2C_2_READY(); /* Wait for ready state */
    return buffer;
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM ALL">

void PWM_TIMER_CHOOSE(byte Channel, byte timer)
{
    if (Channel == 1) {
        if (timer == 2) CCPTMRS0bits.C1TSEL = 0b00;
        if (timer == 4) CCPTMRS0bits.C1TSEL = 0b01;
        if (timer == 6) CCPTMRS0bits.C1TSEL = 0b10;
        if (timer == 8) CCPTMRS0bits.C1TSEL = 0b11;
    }
    if (Channel == 2) {
        if (timer == 2) CCPTMRS0bits.C2TSEL = 0b000;
        if (timer == 4) CCPTMRS0bits.C2TSEL = 0b001;
        if (timer == 6) CCPTMRS0bits.C2TSEL = 0b010;
        if (timer == 8) CCPTMRS0bits.C2TSEL = 0b011;
    }
    if (Channel == 3) {
        if (timer == 2) CCPTMRS0bits.C3TSEL = 0b00;
        if (timer == 4) CCPTMRS0bits.C3TSEL = 0b01;
        if (timer == 6) CCPTMRS0bits.C3TSEL = 0b10;
        if (timer == 8) CCPTMRS0bits.C3TSEL = 0b11;
    }
    if (Channel == 4) {
        if (timer == 2) CCPTMRS1bits.C4TSEL = 0b00;
        if (timer == 4) CCPTMRS1bits.C4TSEL = 0b01;
        if (timer == 6) CCPTMRS1bits.C4TSEL = 0b10;
        if (timer == 8) CCPTMRS1bits.C4TSEL = 0b11;
    }
    if (Channel == 5) {
        if (timer == 2) CCPTMRS1bits.C5TSEL0 = 0;
        if (timer == 4) CCPTMRS1bits.C5TSEL0 = 1;
    }
    if (Channel == 6) {
        if (timer == 2) CCPTMRS1bits.C5TSEL0 = 0;
        if (timer == 2) CCPTMRS1bits.C5TSEL0 = 1;
    }
    if (Channel == 7) {
        if (timer == 2) CCPTMRS1bits.C7TSEL = 0b00;
        if (timer == 4) CCPTMRS1bits.C7TSEL = 0b01;
        if (timer == 6) CCPTMRS1bits.C7TSEL = 0b10;
        if (timer == 8) CCPTMRS1bits.C7TSEL = 0b11;
    }
    if (Channel == 8) {
        if (timer == 2) CCPTMRS2bits.C8TSEL = 0b00;
        if (timer == 4) CCPTMRS2bits.C8TSEL = 0b01;
        if (timer == 6) CCPTMRS2bits.C8TSEL = 0b10;
        if (timer == 8) CCPTMRS2bits.C8TSEL = 0b11;
    }
    if (Channel == 9) {
        if (timer == 2) CCPTMRS2bits.C9TSEL0 = 0;
        if (timer == 4) CCPTMRS2bits.C9TSEL0 = 1;
    }
    if (Channel == 10) {
        if (timer == 2) CCPTMRS2bits.C10TSEL0 = 0;
        if (timer == 2) CCPTMRS2bits.C10TSEL0 = 1;
    }
}

void PWM_TIMER_DIVIDE(byte timer, byte Prescale)
{
    if (timer == 2) T2CONbits.T2CKPS = Prescale;
    if (timer == 4) T4CONbits.T4CKPS = Prescale;
    if (timer == 6) T6CONbits.T6CKPS = Prescale;
    if (timer == 8) T8CONbits.T8CKPS = Prescale;
}

void PWM_TIMER_PR_LOAD(byte timer, byte period)
{
    if (timer == 2) PR2 = period;
    if (timer == 4) PR4 = period;
    if (timer == 6) PR6 = period;
    if (timer == 8) PR8 = period;
}
// <editor-fold defaultstate="collapsed" desc="PWM 1">

byte PWM_1_TIMER_SELECT = 0;

void PWM_1_INIT(unsigned long freq, unsigned char timer)
{
    PWM_1_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(1, PWM_1_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'C', 2, 'L'); // PWM1 ç?k??? için pin ayar? (RC0)
    CCP1CONbits.CCP1M = 0b1100; // PWM modunu ayarla

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_1_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_1_TIMER_SELECT, pwmPeriod);
}

void PWM_1_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_1_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_1_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_1_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_1_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR8'e göre duty hesapla
    CCPR1L = dutyValue >> 2; // ?lk 8 bit CCPR1L'ye yaz?l?r
    CCP1CONbits.DC1B = dutyValue & 0x03; // Son 2 bit (DC1B1 ve DC1B0)
}

void PWM_1_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_1_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_1_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_1_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_1_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_1_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_1_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_1_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_1_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC2 = 0; // PWM1 ç?k???n? s?f?rla (RC0)
    }
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 2">

byte PWM_2_TIMER_SELECT = 0;

void PWM_2_INIT(unsigned long freq, unsigned char timer)
{
    PWM_2_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(2, PWM_2_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'E', 7, 'L');
    CCP2CONbits.CCP2M = 0b1100;

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_2_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_2_TIMER_SELECT, pwmPeriod);

}

void PWM_2_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_2_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_2_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_2_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_2_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    CCPR2L = dutyValue >> 2; // ?lk 8 bit CCPR2L'ye yaz?l?r
    CCP2CONbits.DC2B = dutyValue & 0x03; // Son 2 bit (DC2B1 ve DC2B0)
}

void PWM_2_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_2_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_2_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_2_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_2_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_2_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_2_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_2_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_2_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC1 = 0;
    }
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 3">

byte PWM_3_TIMER_SELECT = 0;

void PWM_3_INIT(unsigned long freq, unsigned char timer)
{
    PWM_3_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(3, PWM_3_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'G', 0, 'L');
    CCP3CONbits.CCP3M = 0b1100;

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_3_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_3_TIMER_SELECT, pwmPeriod);

}

void PWM_3_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_3_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_3_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_3_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_3_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR8'e göre duty hesapla
    CCPR3L = dutyValue >> 2; // ?lk 8 bit CCPR3L'ye yaz?l?r
    CCP3CONbits.DC3B = dutyValue & 0x03; // Son 2 bit (DC3B1 ve DC3B0)
}

void PWM_3_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_3_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_3_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_3_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_3_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_3_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_3_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_3_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_3_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC2 = 0;
    }
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 4">

byte PWM_4_TIMER_SELECT = 0;

void PWM_4_INIT(unsigned long freq, unsigned char timer)
{
    PWM_4_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(4, PWM_4_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'G', 3, 'L');
    CCP4CONbits.CCP4M = 0b1100;

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_4_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_4_TIMER_SELECT, pwmPeriod);

}

void PWM_4_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_4_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_4_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_4_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_4_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR8'e göre duty hesapla
    CCPR4L = dutyValue >> 2; // ?lk 8 bit CCPR4L'ye yaz?l?r
    CCP4CONbits.DC4B = dutyValue & 0x03; // Son 2 bit (DC4B1 ve DC4B0)
}

void PWM_4_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_4_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_4_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_4_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_4_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_4_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_4_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_4_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_4_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC3 = 0;
    }
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 5">

byte PWM_5_TIMER_SELECT = 0;

void PWM_5_INIT(unsigned long freq, unsigned char timer)
{
    PWM_5_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(5, PWM_5_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'G', 4, 'L');
    CCP5CONbits.CCP5M = 0b1100;

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_5_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_5_TIMER_SELECT, pwmPeriod);

}

void PWM_5_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_5_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_5_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_5_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_5_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR8'e göre duty hesapla
    CCPR5L = dutyValue >> 2; // ?lk 8 bit CCPR5L'ye yaz?l?r
    CCP5CONbits.DC5B = dutyValue & 0x03; // Son 2 bit (DC5B1 ve DC5B0)
}

void PWM_5_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_5_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_5_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_5_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_5_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_5_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_5_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_5_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_5_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC4 = 0;
    }
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 6">

byte PWM_6_TIMER_SELECT = 0;

void PWM_6_INIT(unsigned long freq, unsigned char timer)
{
    PWM_6_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(6, PWM_6_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'E', 6, 'L');
    CCP6CONbits.CCP6M = 0b1100;

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_6_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_6_TIMER_SELECT, pwmPeriod);

}

void PWM_6_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_6_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_6_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_6_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_6_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR8'e göre duty hesapla
    CCPR6L = dutyValue >> 2; // ?lk 8 bit CCPR6L'ye yaz?l?r
    CCP6CONbits.DC6B = dutyValue & 0x03; // Son 2 bit (DC6B1 ve DC6B0)
}

void PWM_6_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_6_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_6_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_6_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_6_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_6_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_6_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_6_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_6_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC5 = 0;
    }
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 7">

byte PWM_7_TIMER_SELECT = 0;

void PWM_7_INIT(unsigned long freq, unsigned char timer)
{
    PWM_7_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(7, PWM_7_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'E', 5, 'L');
    CCP7CONbits.CCP7M = 0b1100;

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_7_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_7_TIMER_SELECT, pwmPeriod);

}

void PWM_7_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_7_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_7_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_7_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_7_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR8'e göre duty hesapla
    CCPR7L = dutyValue >> 2; // ?lk 8 bit CCPR7L'ye yaz?l?r
    CCP7CONbits.DC7B = dutyValue & 0x03; // Son 2 bit (DC7B1 ve DC7B0)
}

void PWM_7_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_7_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_7_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_7_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_7_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_7_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_7_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_7_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_7_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC6 = 0;
    }
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 8">

byte PWM_8_TIMER_SELECT = 0;

void PWM_8_INIT(unsigned long freq, unsigned char timer)
{
    PWM_8_TIMER_SELECT = timer;
    PWM_TIMER_CHOOSE(8, PWM_8_TIMER_SELECT);
    PIN_SET_IO('D', 'O', 'E', 4, 'L');
    CCP8CONbits.CCP8M = 0b1100;

    unsigned long pwmPeriod = (_XTAL_FREQ / (freq * 4)) - 1;
    byte divide = 0;
    if (pwmPeriod > 255) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 16)) - 1;
        divide = 0b11;
    } else if (pwmPeriod > 63) {
        pwmPeriod = (_XTAL_FREQ / (freq * 4 * 4)) - 1;
        divide = 0b10;
    } else divide = 0b00;
    PWM_TIMER_DIVIDE(PWM_8_TIMER_SELECT, divide);
    if (pwmPeriod > 255) pwmPeriod = 255;
    PWM_TIMER_PR_LOAD(PWM_8_TIMER_SELECT, pwmPeriod);

}

void PWM_8_DUTY(unsigned int duty)
{
    if (duty > 100) duty = 100; // Maksimum %100 duty
    unsigned int dutyValue;
    if (PWM_8_TIMER_SELECT == 2) dutyValue = ((PR2 + 1) * 4 * duty) / 100; // PR2'ye göre duty hesapla
    else if (PWM_8_TIMER_SELECT == 4) dutyValue = ((PR4 + 1) * 4 * duty) / 100; // PR4'e göre duty hesapla
    else if (PWM_8_TIMER_SELECT == 6) dutyValue = ((PR6 + 1) * 4 * duty) / 100; // PR6'ya göre duty hesapla
    else if (PWM_8_TIMER_SELECT == 8) dutyValue = ((PR8 + 1) * 4 * duty) / 100; // PR8'e göre duty hesapla
    CCPR8L = dutyValue >> 2; // ?lk 8 bit CCPR8L'ye yaz?l?r
    CCP8CONbits.DC8B = dutyValue & 0x03; // Son 2 bit (DC8B1 ve DC8B0)
}

void PWM_8_SET(unsigned char enable)
{
    if (enable) {
        if (PWM_8_TIMER_SELECT == 2) T2CONbits.TMR2ON = 1;
        else if (PWM_8_TIMER_SELECT == 4) T4CONbits.TMR4ON = 1;
        else if (PWM_8_TIMER_SELECT == 6) T6CONbits.TMR6ON = 1;
        else if (PWM_8_TIMER_SELECT == 8) T8CONbits.TMR8ON = 1;
    } else {
        if (PWM_8_TIMER_SELECT == 2) T2CONbits.TMR2ON = 0;
        else if (PWM_8_TIMER_SELECT == 4) T4CONbits.TMR4ON = 0;
        else if (PWM_8_TIMER_SELECT == 6) T6CONbits.TMR6ON = 0;
        else if (PWM_8_TIMER_SELECT == 8) T8CONbits.TMR8ON = 0;
        LATCbits.LATC7 = 0;
    }
}
// </editor-fold>

// </editor-fold>
