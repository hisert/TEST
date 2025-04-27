#include <pic18.h>
#include <xc.h>
#include "config.h"
#include <string.h>
#include <stdio.h>
// <editor-fold defaultstate="collapsed" desc="X">
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TYPEDEF DEFINE">
#define FLAG_JOIN(TASK_REG,TASK)      TASK_REG = TASK_REG | TASK
#define FLAG_ERASE(TASK_REG,TASK)     TASK_REG =TASK_REG & ~TASK
#define FLAG_CONTROL(TASK_REG,TASK)     TASK_REG & TASK
#define TERSLE(DAT) DAT= ~DAT
#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#define qword unsigned long long
#define open 1
#define close 0
#define _XTAL_FREQ 64000000
#define SET_BIT(reg,bit) (reg = reg | (1 << bit))
#define CLR_BIT(reg,bit) (reg = reg & ~(1 << bit))
#define TOGGLE_BIT(reg,bit) (reg = reg ^ (1 << bit))
#define CHECK_BIT(reg,bit) ((reg & (1 << bit)) / (1 << bit))
void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM">

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
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="I2C SSD1306 OLED ">
//---------------------------------------------------------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="LIBRARY DEFINE    ">
#define LEFT                  0
#define RIGHT                 254
#define CENTER                255

#define BLACK                 0
#define WHITE                 1
#define INVERSE               2

//#define SSD1306_ADDR        0x3D
#define SSD1306_ADDR          0x3C


#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 32

#define SSD1306_COMMAND                     0x00
#define SSD1306_DATA                        0xC0
#define SSD1306_DATA_CONTINUE               0x40

/* SSD1306 Command Set*/
// Fundamental Commands
#define SSD1306_SET_CONTRAST_CONTROL                    0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME                   0xA4
#define SSD1306_DISPLAY_ALL_ON                          0xA5
#define SSD1306_NORMAL_DISPLAY                          0xA6
#define SSD1306_INVERT_DISPLAY                          0xA7
#define SSD1306_DISPLAY_OFF                             0xAE
#define SSD1306_DISPLAY_ON                              0xAF
#define SSD1306_NOP                                     0xE3
// Scrolling Commands
#define SSD1306_HORIZONTAL_SCROLL_RIGHT                 0x26
#define SSD1306_HORIZONTAL_SCROLL_LEFT                  0x27
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT    0x29
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT     0x2A
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
// Addressing Setting Commands
#define SSD1306_SET_LOWER_COLUMN                        0x00
#define SSD1306_SET_HIGHER_COLUMN                       0x10
#define SSD1306_MEMORY_ADDR_MODE                        0x20
#define SSD1306_SET_COLUMN_ADDR                         0x21
#define SSD1306_SET_PAGE_ADDR                           0x22
// Hardware Configuration Commands
#define SSD1306_SET_START_LINE                          0x40
#define SSD1306_SET_SEGMENT_REMAP                       0xA0
#define SSD1306_SET_MULTIPLEX_RATIO                     0xA8
#define SSD1306_COM_SCAN_DIR_INC                        0xC0
#define SSD1306_COM_SCAN_DIR_DEC                        0xC8
#define SSD1306_SET_DISPLAY_OFFSET                      0xD3
#define SSD1306_SET_COM_PINS                            0xDA
#define SSD1306_CHARGE_PUMP                             0x8D
// Timing & Driving Scheme Setting Commands
#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO             0xD5
#define SSD1306_SET_PRECHARGE_PERIOD                    0xD9
#define SSD1306_SET_VCOM_DESELECT                       0xDB

typedef struct _Current_Font_s {
    const byte *font; // Fonts Stored are Const
    byte x_size;
    byte y_size;
    byte offset;
    byte numchars;
    byte inverted;
} Current_Font_s;

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="LIBRARY CONFIG    ">
const byte SMALL_FONTS[] = {
    0x06, 0x08, 0x20, 0x5f, // x_size, y_size, offset, number of char
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp
    0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, // !
    0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, // #
    0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
    0x00, 0x23, 0x13, 0x08, 0x64, 0x62, // %
    0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, // (
    0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, // )
    0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // *
    0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // ,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /

    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // <
    0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // ?

    0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // @
    0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // D
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // G
    0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
    0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // O

    0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
    0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // W
    0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
    0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // [
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, // Backslash (Checker pattern)
    0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // ]
    0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // _

    0x00, 0x00, 0x03, 0x05, 0x00, 0x00, // `
    0x00, 0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, // b
    0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // c
    0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // d
    0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // f
    0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
    0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // j
    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // m
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // o

    0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // p
    0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // q
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // t
    0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x00, 0x10, 0x7C, 0x82, 0x00, // {
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, // |
    0x00, 0x00, 0x82, 0x7C, 0x10, 0x00, // }
    0x00, 0x00, 0x06, 0x09, 0x09, 0x06 // ~ (Degrees)
};
static Current_Font_s cfont;
byte buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8];
#define DEF_I2C_OLED_START  I2C_1_START()
#define DEF_I2C_OLED_WRITE(data) I2C_1_WRITE(data);
#define DEF_I2C_OLED_STOP I2C_1_STOP()
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT     ">

void ssd1306_command(byte command)
{
    byte controlx = 0x00; // Co=0, D/C=0
    DEF_I2C_OLED_START;
    DEF_I2C_OLED_WRITE(SSD1306_ADDR << 1);
    DEF_I2C_OLED_WRITE(controlx);
    DEF_I2C_OLED_WRITE(command);
    DEF_I2C_OLED_STOP;
}

void ssd1306_data(byte value)
{
    byte controlx = 0x40; // Co = 0, D/C = 1
    DEF_I2C_OLED_START;
    DEF_I2C_OLED_WRITE(SSD1306_ADDR << 1);
    DEF_I2C_OLED_WRITE(controlx);
    DEF_I2C_OLED_WRITE(value);
    DEF_I2C_OLED_STOP;
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USER FUNCT        ">

void OLED_SetFont(const byte *font)
{
    cfont.font = font;
    cfont.x_size = *(font + 0);
    cfont.y_size = *(font + 1);
    cfont.offset = *(font + 2);
    cfont.numchars = *(font + 3);
    cfont.inverted = 0;
}

void OLED_InvertFont(byte invert_status)
{
    if (invert_status) cfont.inverted = 1;
    else cfont.inverted = 0;
}

void OLED_SetContrast(byte contrast)
{
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(contrast);
}

void OLED_ClearDisplay(void)
{
    memset(buffer, 0, (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8));
}

void OLED_FillDisplay(void)
{
    memset(buffer, 0xFF, (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8));
}

void OLED_InvertDisplay(byte value)
{
    if (value) ssd1306_command(SSD1306_INVERT_DISPLAY);
    else ssd1306_command(SSD1306_NORMAL_DISPLAY);
}

void OLED_DrawPixel(word x, word y, byte color)
{
    if ((x < 0) || (x >= SSD1306_LCDWIDTH) || (y < 0) || (y >= SSD1306_LCDHEIGHT)) return;
    switch (color) {
    case WHITE: buffer[x + (y / 8) * SSD1306_LCDWIDTH] |= (1 << (y & 7));
        break;
    case BLACK: buffer[x + (y / 8) * SSD1306_LCDWIDTH] &= ~(1 << (y & 7));
        break;
    case INVERSE: buffer[x + (y / 8) * SSD1306_LCDWIDTH] ^= (1 << (y & 7));
        break;
    }
}

void OLED_Line(word x_start, word y_start, word x_end, word y_end, byte color)
{
    word x, y, addx, addy, dx, dy;
    signed long P;
    word i;
    dx = abs((word) (x_end - x_start));
    dy = abs((word) (y_end - y_start));
    x = x_start;
    y = y_start;

    if (x_start > x_end) addx = -1;
    else addx = 1;
    if (y_start > y_end) addy = -1;
    else addy = 1;
    if (dx >= dy) {
        P = 2 * dy - dx;

        for (i = 0; i <= dx; ++i) {
            OLED_DrawPixel(x, y, color);
            if (P < 0) {
                P += 2 * dy;
                x += addx;
            } else {
                P += 2 * dy - 2 * dx;
                x += addx;
                y += addy;
            }
        }
    } else {
        P = 2 * dx - dy;
        for (i = 0; i <= dy; ++i) {
            OLED_DrawPixel(x, y, color);

            if (P < 0) {
                P += 2 * dx;
                y += addy;
            } else {
                P += 2 * dx - 2 * dy;
                x += addx;
                y += addy;
            }
        }
    }
}

void OLED_V_Line(word y_start, word y_end, word x_pos, byte color)
{
    word temp;
    if (y_start > y_end) {
        temp = y_start;
        y_start = y_end;
        y_end = temp;
    }

    while (y_start <= y_end) {
        OLED_DrawPixel(x_pos, y_start, color);
        y_start++;
    }
}

void OLED_H_Line(word x_start, word x_end, word y_pos, byte color)
{
    word temp;
    if (x_start > x_end) {
        temp = x_start;
        x_start = x_end;
        x_end = temp;
    }

    while (x_start <= x_end) {
        OLED_DrawPixel(x_start, y_pos, color);
        x_start++;
    }
}

void OLED_Rectangle(word x1, word y1, word x2, word y2, byte color)
{
    OLED_H_Line(x1, x2, y1, color);
    OLED_H_Line(x1, x2, y2, color);
    OLED_V_Line(y1, y2, x1, color);
    OLED_V_Line(y1, y2, x2, color);
}

void OLED_FillRectangle(word x1, word y1, word x2, word y2, byte color)
{
    word i;
    for (i = x1; i <= x2; i++) OLED_V_Line(y1, y2, i, color);
}

void OLED_Triangle(word x0, word y0, word x1, word y1, word x2, word y2, byte color)
{
    OLED_Line(x0, y0, x1, y1, color);
    OLED_Line(x1, y1, x2, y2, color);
    OLED_Line(x2, y2, x0, y0, color);
}

void OLED_Image(const byte *image)
{
    word i;
    for (i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++) buffer[i] = *(image + i);
}

void OLED_Circle(word x0, word y0, word r, byte color)
{
    word f = 1 - r;
    word ddF_x = 1;
    word ddF_y = -2 * r;
    word x = 0;
    word y = r;

    OLED_DrawPixel(x0, y0 + r, color);
    OLED_DrawPixel(x0, y0 - r, color);
    OLED_DrawPixel(x0 + r, y0, color);
    OLED_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawPixel(x0 + x, y0 + y, color);
        OLED_DrawPixel(x0 - x, y0 + y, color);
        OLED_DrawPixel(x0 + x, y0 - y, color);
        OLED_DrawPixel(x0 - x, y0 - y, color);
        OLED_DrawPixel(x0 + y, y0 + x, color);
        OLED_DrawPixel(x0 - y, y0 + x, color);
        OLED_DrawPixel(x0 + y, y0 - x, color);
        OLED_DrawPixel(x0 - y, y0 - x, color);
    }
}

void OLED_Write(word x, word y, char value)
{
    word font_idx = 0;
    word rowcnt = 0;
    word cnt = 0;
    byte b;
    word temp = 0;

    word cbyte, cx, cy;
    word cbit;

    if (cfont.y_size % 8 == 0) {
        font_idx = ((value - cfont.offset)*(cfont.x_size * (cfont.y_size / 8))) + 4;
        for (rowcnt = 0; rowcnt < (cfont.y_size / 8); rowcnt++) {
            for (cnt = 0; cnt < cfont.x_size; cnt++) {
                temp = *(cfont.font + font_idx + cnt + (rowcnt * cfont.x_size));
                for (b = 0; b < 8; b++) {
                    if (temp & (1 << b)) {
                        if (cfont.inverted == 0) OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 1);
                        else OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 0);
                    } else {
                        if (cfont.inverted == 0) OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 0);
                        else OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 1);
                    }
                }
            }
        }
    } else {
        font_idx = ((value - cfont.offset)*((cfont.x_size * cfont.y_size) / 8)) + 4;
        cbyte = *(cfont.font + font_idx);
        cbit = 7;
        for (cx = 0; cx < cfont.x_size; cx++) {
            for (cy = 0; cy < cfont.y_size; cy++) {
                if ((cbyte & (1 << cbit)) != 0) {
                    if (cfont.inverted == 0) OLED_DrawPixel(x + cx, y + cy, 1);
                    else OLED_DrawPixel(x + cx, y + cy, 0);
                } else {
                    if (cfont.inverted == 0) OLED_DrawPixel(x + cx, y + cy, 0);
                    else OLED_DrawPixel(x + cx, y + cy, 1);
                }
                cbit--;
                if (cbit < 0) {
                    cbit = 7;
                    font_idx++;
                    cbyte = *(cfont.font + font_idx);
                }
            }
        }
    }
}

void OLED_Write_Text(word x, word y, const char *text)
{
    byte cnt;
    byte length;

    length = strlen((const char*) text);
    // if (x == RIGHT) x = 128 - (length * cfont.x_size);
    // if (x == CENTER) x = (128 - (length * cfont.x_size)) / 2;
    for (cnt = 0; cnt < length; cnt++) OLED_Write(x + (cnt * (cfont.x_size)), y, *text++);
}

void OLED_Write_Dec(word x, word y, dword data)
{
    char text[30];
    byte cnt;
    byte length;
    sprintf(text, "%d", data);
    length = strlen(text);
    // if (x == RIGHT) x = 128 - (length * cfont.x_size);
    // if (x == CENTER) x = (128 - (length * cfont.x_size)) / 2;
    for (cnt = 0; cnt < length; cnt++) OLED_Write(x + (cnt * (cfont.x_size)), y, text[cnt]);
}

void OLED_Init(void)
{
    ssd1306_command(SSD1306_DISPLAY_OFF);
    ssd1306_command(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    ssd1306_command(0x80);
    ssd1306_command(SSD1306_SET_MULTIPLEX_RATIO);
    ssd1306_command(SSD1306_LCDHEIGHT - 1);
    ssd1306_command(SSD1306_SET_DISPLAY_OFFSET);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_SET_START_LINE | 0x00); // Line: 0
    ssd1306_command(SSD1306_CHARGE_PUMP);
    ssd1306_command(0x14);
    ssd1306_command(SSD1306_MEMORY_ADDR_MODE);
    ssd1306_command(0x00); //Horizontal Addressing Mode is Used
    ssd1306_command(SSD1306_SET_SEGMENT_REMAP | 0x01);
    ssd1306_command(SSD1306_COM_SCAN_DIR_DEC);
    ssd1306_command(SSD1306_SET_COM_PINS);
    ssd1306_command(0x02);
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(0x8F);
    ssd1306_command(SSD1306_SET_PRECHARGE_PERIOD);
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_SET_VCOM_DESELECT);
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAY_ALL_ON_RESUME);
    ssd1306_command(SSD1306_NORMAL_DISPLAY);
    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
    ssd1306_command(SSD1306_DISPLAY_ON);

    OLED_SetFont(SMALL_FONTS);
    OLED_ClearDisplay();
}

void OLED_Update(void)
{
    word i = 0;
    byte x = 0;
    ssd1306_command(SSD1306_SET_COLUMN_ADDR);
    ssd1306_command(0); // Column start address (0 = reset)
    ssd1306_command(SSD1306_LCDWIDTH - 1); // Column end address (127 = reset)
    ssd1306_command(SSD1306_SET_PAGE_ADDR);
    ssd1306_command(0); // Page start address (0 = reset)
    ssd1306_command(3); // Page end address
    for (i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++) {
        DEF_I2C_OLED_START;
        DEF_I2C_OLED_WRITE(SSD1306_ADDR << 1);
        DEF_I2C_OLED_WRITE(0x40);
        for (x = 0; x < 16; x++) {
            DEF_I2C_OLED_WRITE(buffer[i]);
            i++;
        }
        i--;
        DEF_I2C_OLED_STOP;
    }
}

// </editor-fold> 
//---------------------------------------------------------------------------------------------------------------------
// </editor-fold> //-->>NEED DATA 
// <editor-fold defaultstate="collapsed" desc="INPUT LIBRARY">

typedef struct {
    byte Temp_Counter;
    byte Old_state;
} Input_t;

#define NO_CHANGEE 0x00
#define INPUT_RAISE_EDGE 0x01
#define IINPUT_FALL_EDGE 0x02

byte INPUT_DEBOUNCE(Input_t *Input, byte Input_Val, byte Debounce)
{
    if (Input->Old_state == Input_Val) Input->Temp_Counter = 0;
    else {
        if (Input->Temp_Counter >= Debounce) {
            Input->Temp_Counter = 0;
            Input->Old_state = Input_Val;
            if (Input_Val == 0) return INPUT_RAISE_EDGE;
            else return IINPUT_FALL_EDGE;
        } else Input->Temp_Counter = Input->Temp_Counter + 1;
    }
    return NO_CHANGEE;
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="BUTON LIBRARY">

typedef struct {
    word PressTime;
    byte Temp_Counter;
    byte Flag;
} Buton_t;

#define BUTON_FREE 0x00
#define BUTON_PRESSING 0x01
#define BUTON_PRESSED 0x02

byte BUTON_PROCESS(Buton_t *Buton, byte Buton_Val, byte Buton_Up_Time, byte Buton_Fall_Time)
{
    if (((Buton->Flag) & BUTON_PRESSED)) {
        Buton->PressTime++;
        if (Buton_Val) {
            if (Buton->Temp_Counter) Buton->Temp_Counter = Buton->Temp_Counter - 1;
            else {
                Buton->Temp_Counter = Buton_Up_Time;
                Buton->Flag = Buton->Flag & ~BUTON_PRESSED;
                return BUTON_PRESSED;
            }
        } else Buton->Temp_Counter = Buton_Fall_Time;
        return BUTON_PRESSING;
    } else {
        if (Buton_Val == 0) {
            if (Buton->Temp_Counter) Buton->Temp_Counter = Buton->Temp_Counter - 1;
            else {
                Buton->Temp_Counter = Buton_Fall_Time;
                Buton->Flag = Buton->Flag | BUTON_PRESSED;
                return BUTON_PRESSING;
            }
        } else Buton->Temp_Counter = Buton_Up_Time;
        return BUTON_FREE;
    }
}

word BUTON_GET_TIME(Buton_t *Buton)
{
    return Buton->PressTime;
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="THREAD LIBRARY">
//---------------------------------------------------------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="LIBRARY DEFINE    ">
#define THREAD_FLG_START 0x01
#define THREAD_FLG_READY 0x04
#define THREAD_FLG_LOOP 0x08

typedef struct {
    byte flag;
    word duty_time;
    word duty_temp_time;
    void (*Funct)(byte threadIndex);
} THREAD_t;

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="LIBRARY CONFIG    ">

enum {
    THREAD_LED = 0,
    THREAD_INPUT,
    THREAD_RELAY,
    THREAD_NUM,
} THREAD_NAME;
extern THREAD_t THREAD_LIST[THREAD_NUM];
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT     ">

void THREAD_INTERRUPT()
{
    for (byte threadIndex = 0; threadIndex < THREAD_NUM; threadIndex++) {
        if (THREAD_LIST[threadIndex].flag & THREAD_FLG_START) {
            if ((THREAD_LIST[threadIndex].flag & THREAD_FLG_READY) == 0) {
                if ((THREAD_LIST[threadIndex].duty_temp_time) > 1) (THREAD_LIST[threadIndex].duty_temp_time)--;
                else {
                    THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag | THREAD_FLG_READY;
                    THREAD_LIST[threadIndex].duty_temp_time = THREAD_LIST[threadIndex].duty_time;
                }
            }
        }
    }
}

void THREAD_MAIN()
{
    for (byte threadIndex = 0; threadIndex < THREAD_NUM; threadIndex++) {
        if ((THREAD_LIST[threadIndex].flag & THREAD_FLG_READY)) {
            THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag &= ~THREAD_FLG_READY;
            THREAD_LIST[threadIndex].Funct(threadIndex);
        }
    }
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USER FUNCT        ">

void THREAD_START(byte threadIndex)
{
    THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag | THREAD_FLG_START;
}

void THREAD_STOP(byte threadIndex)
{
    THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag & ~THREAD_FLG_START;
}

void THREAD_DONE_CONTROL(byte threadIndex)
{
    if ((THREAD_LIST[threadIndex].flag & THREAD_FLG_LOOP) == 0) THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag & ~THREAD_FLG_START;
}

void THREAD_TIME(byte threadIndex, word threadTime)
{
    THREAD_LIST[threadIndex].duty_time = threadTime;
    THREAD_LIST[threadIndex].duty_temp_time = threadTime;
}

// </editor-fold> 
//---------------------------------------------------------------------------------------------------------------------
// </editor-fold> //-->>NEED DATA

typedef enum {
    ROLE_A_MODE,
    ROLE_B_MODE,
    ROLE_BUSY_MODE,
    ROLE_ALARM_MODE,
    ROLE_A_TIME,
    ROLE_B_TIME,
    ROLE_BUSY_TIME,
    ROLE_ALARM_TIME,
    COUNTER_A_FIX,
    COUNTER_B_FIX,
    COUNTER_A_TEMP,
    COUNTER_B_TEMP,
    RANDOM_A_MODE,
    RANDOM_B_MODE,
    RANDOM_A_AMOUNT,
    RANDOM_B_AMOUNT,
    INPUT_MODE,
    INPUT_TIME_OUT,
    INPUT_BUFFER,
    INPUT_EMG_MODE,
    ARM_DROP_MODE,
    ARM_MOTOR_MODE,
    ARM_MOTOR_SPEED,
    ARM_MOTOR_BREAK_SPEED,
    SETTINGS_DONE,
} SETTINGS;

word SETTING_VALUES[SETTINGS_DONE];

void LOG_PRINT(char *msg)
{
    UART_1_STRING(msg);
    UART_1_STRING("\r\n");
}

// <editor-fold defaultstate="collapsed" desc="MENU ">

typedef struct {
    const char *text;
    byte flag;
    word(*Funct)(byte komut, word data);
    word max;
    word min;
} Menu_One;
#define MENU_FLAG_NEW_MENU 0x01
#define MENU_FLAG_VALUE 0x02
#define MENU_FLAG_SELECT 0x04
#define MENU_FLAG_SHOW_DATA 0x08
#define MENU_FLAG_REFRESH_DATA 0x10
Menu_One * MENU_BACK_POINTER[5];
char *MENU_SELECT_LIST;
byte MENU_BACK_INDEX[5];
Menu_One *MENU_POINTER = 0;
byte MENU_INDEX_COUNTER = 0;
byte MENU_MENU_COUNTER = 0;
byte MENU_MAX = 0;
char *SHOW_DATA_TEXT = 0;
char *MENU_UST_YAZI = 0;

// <editor-fold defaultstate="collapsed" desc="RELAY SETTING FUNCT">
const char *SELECT_LIST_RELAY_MODE[] = {"MODE N/O", "MODE N/C"};

word MENU_FUNCT_RELAY_A_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_A_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_A_MODE];
    }
}

word MENU_FUNCT_RELAY_B_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_B_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_B_MODE];
    }
}

word MENU_FUNCT_RELAY_BUSY_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_BUSY_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_BUSY_MODE];
    }
}

word MENU_FUNCT_RELAY_ALARM_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_ALARM_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_ALARM_MODE];
    }
}

word MENU_FUNCT_RELAY_A_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_A_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_A_TIME];
    }
}

word MENU_FUNCT_RELAY_B_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_B_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_B_TIME];
    }
}

word MENU_FUNCT_RELAY_BUSY_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_BUSY_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_BUSY_TIME];
    }
}

word MENU_FUNCT_RELAY_ALARM_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_ALARM_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_ALARM_TIME];
    }
}

Menu_One RELAY_MENU[] = {
    {.text = "RELAY A MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_A_MODE, .max = 1},
    {.text = "RELAY B MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_B_MODE, .max = 1},
    {.text = "RELAY BUSY MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_BUSY_MODE, .max = 1},
    {.text = "RELAY ALARM MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_ALARM_MODE, .max = 1},
    {.text = "RELAY A TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_A_TIME, .max = 100, .min = 0},
    {.text = "RELAY B TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_B_TIME, .max = 100, .min = 0},
    {.text = "RELAY BUSY TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_BUSY_TIME, .max = 100, .min = 0},
    {.text = "RELAY ALARM TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_ALARM_TIME, .max = 100, .min = 0},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM COUNTER FUNCT">

char *COUNTER_CANT_ERASE = "CANT ERASE";
char *COUNTER_ASK_ERASE = "ERASE DATA ?";

word MENU_FUNCT_COUNTER_A_FIX(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_A_FIX] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_CANT_ERASE;
        return SETTING_VALUES[COUNTER_A_FIX];
    }
}

word MENU_FUNCT_COUNTER_B_FIX(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_B_FIX] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_CANT_ERASE;
        return SETTING_VALUES[COUNTER_B_FIX];
    }
}

word MENU_FUNCT_COUNTER_A_TEMP(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_A_TEMP] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_ASK_ERASE;
        return SETTING_VALUES[COUNTER_A_TEMP];
    }
}

word MENU_FUNCT_COUNTER_B_TEMP(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_B_TEMP] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_ASK_ERASE;
        return SETTING_VALUES[COUNTER_B_TEMP];
    }
}

Menu_One COUNTER_MENU[] = {
    {.text = "FIX A COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_A_FIX, .max = 65536, .min = 0},
    {.text = "FIX B COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_B_FIX, .max = 65536, .min = 0},
    {.text = "TEMP A COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_A_TEMP, .max = 65536, .min = 0},
    {.text = "TEMP B COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_B_TEMP, .max = 65536, .min = 0},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="RANDOM SORTER FUNCT">
const char *SELECT_LIST_RANDOM_MODE[] = {"MODE DISABLE", "MODE ENABLE"};

word MENU_FUNCT_RANDOM_A_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_A_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RANDOM_MODE;
        return SETTING_VALUES[RANDOM_A_MODE];
    }
}

word MENU_FUNCT_RANDOM_B_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_B_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RANDOM_MODE;
        return SETTING_VALUES[RANDOM_B_MODE];
    }
}

word MENU_FUNCT_RANDOM_A_AMOUNT(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_A_AMOUNT] = data;
        return 0;
    } else {
        return SETTING_VALUES[RANDOM_A_AMOUNT];
    }
}

word MENU_FUNCT_RANDOM_B_AMOUNT(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_B_AMOUNT] = data;
        return 0;
    } else {
        return SETTING_VALUES[RANDOM_B_AMOUNT];
    }
}

Menu_One RANDOM_MENU[] = {
    {.text = "RANDOM A MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RANDOM_A_MODE, .max = 1},
    {.text = "RANDOM B MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RANDOM_B_MODE, .max = 1},
    {.text = "RELAY A AMOUNT", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RANDOM_A_AMOUNT, .max = 250, .min = 0},
    {.text = "RELAY B AMOUNT", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RANDOM_B_AMOUNT, .max = 250, .min = 0},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="INPUT FUNCT">
const char *SELECT_LIST_INPUT_MODE[] = {"FREE", "CONTROL"};
const char *SELECT_LIST_EMG_MODE[] = {"N/O", "N/C"};

word MENU_FUNCT_INPUT_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_INPUT_MODE;
        return SETTING_VALUES[INPUT_MODE];
    }
}

word MENU_FUNCT_INPUT_TIME_OUT(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_TIME_OUT] = data;
        return 0;
    } else {
        return SETTING_VALUES[INPUT_TIME_OUT];
    }
}

word MENU_FUNCT_INPUT_BUFFER(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_BUFFER] = data;
        return 0;
    } else {
        return SETTING_VALUES[INPUT_BUFFER];
    }
}

word MENU_FUNCT_EMG_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_EMG_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_EMG_MODE;
        return SETTING_VALUES[INPUT_EMG_MODE];
    }
}

Menu_One INPUT_MENU[] = {
    {.text = "INPUT MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_INPUT_MODE, .max = 1},
    {.text = "INPUT TIME OUT", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_INPUT_TIME_OUT, .max = 100, .min = 0},
    {.text = "INPUT BUFFER", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_INPUT_BUFFER, .max = 20, .min = 0},
    {.text = "EMG MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_EMG_MODE, .max = 1},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="ARM SETTUNG FUNCT">

const char *SELECT_LIST_DROP_ARM_MODE[] = {"DISABLE", "JUST EMG", "JUST POWER FAIL", "POWER FAIL & MDG"};
const char *SELECT_LIST_ARM_MOTOR_MODE[] = {"PASSIVE", "ACTIVE"};

word MENU_FUNCT_ARM_DROP_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_DROP_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_DROP_ARM_MODE;
        return SETTING_VALUES[ARM_DROP_MODE];
    }
}

word MENU_FUNCT_ARM_MOTOR_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_MOTOR_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_ARM_MOTOR_MODE;
        return SETTING_VALUES[ARM_MOTOR_MODE];
    }
}

word MENU_FUNCT_ARM_MOTOR_SPEED(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_MOTOR_SPEED] = data;
        return 0;
    } else {
        return SETTING_VALUES[ARM_MOTOR_SPEED];
    }
}

word MENU_FUNCT_ARM_MOTOR_BREAK_SPEED(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_MOTOR_BREAK_SPEED] = data;
        return 0;
    } else {
        return SETTING_VALUES[ARM_MOTOR_BREAK_SPEED];
    }
}

Menu_One ARM_SETTING_MENU[] = {
    {.text = "DROP ARM MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_ARM_DROP_MODE, .max = 3},
    {.text = "MOTOR MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_ARM_MOTOR_MODE, .max = 3},
    {.text = "MOTOR SPEED", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_ARM_MOTOR_SPEED, .max = 100, .min = 0},
    {.text = "MOTOR BREAK SPEED", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_ARM_MOTOR_BREAK_SPEED, .max = 100, .min = 0},
    {.text = "MAS12 STATUS", .flag = MENU_FLAG_REFRESH_DATA, .Funct = 0, .max = 0, .min = 0},
};
// </editor-fold>

Menu_One ANA_MENU[] = {
    {.text = "INPUT SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) INPUT_MENU},
    {.text = "ARM SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) ARM_SETTING_MENU},
    {.text = "RELAY SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) RELAY_MENU},
    {.text = "SYSTEM COUNTER", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) COUNTER_MENU},
    {.text = "RANDOM SORTER", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) RANDOM_MENU},
};
char *ANA_MENU_UST_YAZI = "   >> MAIN MENU <<";
char *RELAY_MENU_UST_YAZI = "  >> RELAY MENU <<";
char *ARM_MENU_UST_YAZI = "    >> ARM MENU <<";
char *COUNTER_MENU_UST_YAZI = " >> COUNTER MENU <<";
char *RANDOM_MENU_UST_YAZI = "  >> RANDOM MENU <<";
char *INPUT_MENU_UST_YAZI = "  >> INPUT MENU <<";

void MENU_UST_DATA_GETIR()
{
    if (MENU_POINTER == ANA_MENU) MENU_MAX = sizeof (ANA_MENU) / sizeof (ANA_MENU[0]) - 1;
    if (MENU_POINTER == RELAY_MENU) MENU_MAX = sizeof (RELAY_MENU) / sizeof (RELAY_MENU[0]) - 1;
    if (MENU_POINTER == COUNTER_MENU) MENU_MAX = sizeof (COUNTER_MENU) / sizeof (COUNTER_MENU[0]) - 1;
    if (MENU_POINTER == RANDOM_MENU) MENU_MAX = sizeof (RANDOM_MENU) / sizeof (RANDOM_MENU[0]) - 1;
    if (MENU_POINTER == INPUT_MENU) MENU_MAX = sizeof (INPUT_MENU) / sizeof (INPUT_MENU[0]) - 1;
    if (MENU_POINTER == ARM_SETTING_MENU) sizeof (ARM_SETTING_MENU) / sizeof (ARM_SETTING_MENU[0]) - 1;

    if (MENU_POINTER == ANA_MENU) MENU_UST_YAZI = ANA_MENU_UST_YAZI;
    if (MENU_POINTER == RELAY_MENU) MENU_UST_YAZI = MENU_UST_YAZI = RELAY_MENU_UST_YAZI;
    if (MENU_POINTER == ARM_SETTING_MENU) MENU_UST_YAZI = ARM_MENU_UST_YAZI;
    if (MENU_POINTER == COUNTER_MENU) MENU_UST_YAZI = COUNTER_MENU_UST_YAZI;
    if (MENU_POINTER == RANDOM_MENU) MENU_UST_YAZI = RANDOM_MENU_UST_YAZI;
    if (MENU_POINTER == INPUT_MENU) MENU_UST_YAZI = INPUT_MENU_UST_YAZI;
}

void MENU_GIR(Menu_One *Menu, byte komut)
{
    if (komut) {
        MENU_BACK_POINTER[MENU_MENU_COUNTER] = MENU_POINTER;
        MENU_BACK_INDEX[MENU_MENU_COUNTER] = MENU_INDEX_COUNTER;
        MENU_MENU_COUNTER = MENU_MENU_COUNTER + 1;
        MENU_POINTER = Menu;
        MENU_INDEX_COUNTER = 0;
    } else {
        MENU_INDEX_COUNTER = 0;
        MENU_MENU_COUNTER = 0;
        MENU_POINTER = ANA_MENU;
    }

    MENU_UST_DATA_GETIR();
}

void MENU_CIK()
{
    if (MENU_MENU_COUNTER) {
        MENU_MENU_COUNTER = MENU_MENU_COUNTER - 1;
        MENU_POINTER = MENU_BACK_POINTER[MENU_MENU_COUNTER];
        MENU_INDEX_COUNTER = MENU_BACK_INDEX[MENU_MENU_COUNTER];
        MENU_UST_DATA_GETIR();
    }

}

void MENU_TEXT_PRINT(char *text, byte index)
{
    char msg[30];
    OLED_ClearDisplay();
    OLED_Write_Text(0, 0, MENU_UST_YAZI);
    OLED_H_Line(0, 128, 8, 1);
    sprintf(msg, "%c) %s", (index + '1'), text);
    OLED_Write_Text(0, 14, msg);
    sprintf(msg, "%c/%c", (index + '1'), (MENU_MAX + '1'), text);
    OLED_Write_Text(105, 24, msg);
    OLED_Update();
}

void MENU_SHOW_DATA_PRINT(char *text, word data)
{
    OLED_ClearDisplay();
    OLED_Write_Text(0, 0, text);
    if (data >= 1000) OLED_Write_Dec(51, 24, data);
    else if (data >= 100) OLED_Write_Dec(53, 24, data);
    else OLED_Write_Dec(56, 24, data);
    OLED_Update();
}

void MENU_USE_SELECT(char *ust_yazi, char *data[], byte index)
{
    char msg[30];
    OLED_ClearDisplay();
    OLED_Write_Text(0, 0, ust_yazi);
    sprintf(msg, "%c ) %s", ('a' + index), data[index]);
    OLED_Write_Text(0, 16, msg);
    OLED_Update();
}

void MENU_USE_VAL(char *ust_yazi, word data_max, word data_min, word data)
{
    OLED_ClearDisplay();
    OLED_Write_Text(0, 0, ust_yazi);
    OLED_Write_Text(0, 16, "MAX      NOW      MIN");
    OLED_Write_Dec(0, 24, data_max);

    if (data_min >= 1000) OLED_Write_Dec(103, 24, data_min);
    else if (data_min >= 100) OLED_Write_Dec(109, 24, data_min);
    else OLED_Write_Dec(116, 24, data_min);

    if (data >= 1000) OLED_Write_Dec(51, 24, data);
    else if (data >= 100) OLED_Write_Dec(53, 24, data);
    else OLED_Write_Dec(56, 24, data);
    OLED_Update();
}

void MENU_WORK(char MENU_MOVEMENT)
{
    byte temp = 0;
    static word MENU_TEMP_VAL = 0;
    static word VAL_CHANGE_FLAG = 0;
    static byte MENU_SHOW_FLAG = 0;
    if (MENU_SHOW_FLAG == 0) {
        if (MENU_MOVEMENT == 'O') {
            temp = 1;
            MENU_GIR(ANA_MENU, 0);
        } else return;
    } else {
        if (MENU_MOVEMENT == 'U') {
            if (VAL_CHANGE_FLAG) {
                if (MENU_POINTER[MENU_INDEX_COUNTER].max > MENU_TEMP_VAL) MENU_TEMP_VAL = MENU_TEMP_VAL + 1;
            } else if (MENU_MAX > MENU_INDEX_COUNTER) MENU_INDEX_COUNTER = MENU_INDEX_COUNTER + 1;

        }
        if (MENU_MOVEMENT == 'D') {
            if (VAL_CHANGE_FLAG) {
                if (MENU_POINTER[MENU_INDEX_COUNTER].min < MENU_TEMP_VAL) MENU_TEMP_VAL = MENU_TEMP_VAL - 1;
            } else if (MENU_INDEX_COUNTER) MENU_INDEX_COUNTER = MENU_INDEX_COUNTER - 1;
        }
        if (MENU_MOVEMENT == 'B') {
            if (MENU_MOVEMENT == 'B') {
                if (VAL_CHANGE_FLAG == 1) VAL_CHANGE_FLAG = 0;
                else {
                    if (MENU_MENU_COUNTER == 0) {
                        MENU_SHOW_FLAG = 0;
                        temp = 2;
                    } else MENU_CIK();
                }
            }
        }
        if (MENU_MOVEMENT == 'O') {
            if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_NEW_MENU) {
                MENU_GIR(MENU_POINTER[MENU_INDEX_COUNTER].Funct, 1);
            } else if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SHOW_DATA) {
                if (VAL_CHANGE_FLAG == 0) {
                    MENU_TEMP_VAL = 0;
                    if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_TEMP_VAL = MENU_POINTER[MENU_INDEX_COUNTER].Funct(0, 9999);
                    VAL_CHANGE_FLAG = 1;
                } else {
                    if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_POINTER[MENU_INDEX_COUNTER].Funct(1, MENU_TEMP_VAL);
                    VAL_CHANGE_FLAG = 0;
                }
            } else if ((MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_VALUE) || (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SELECT)) {
                if (VAL_CHANGE_FLAG == 0) {
                    MENU_TEMP_VAL = 0;
                    if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_TEMP_VAL = MENU_POINTER[MENU_INDEX_COUNTER].Funct(0, 9999);
                    VAL_CHANGE_FLAG = 1;
                } else {
                    if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_POINTER[MENU_INDEX_COUNTER].Funct(1, MENU_TEMP_VAL);
                    VAL_CHANGE_FLAG = 0;
                }
            }
        }

    }
    if (temp == 1) MENU_SHOW_FLAG = 1;
    if (temp == 2) {
        OLED_ClearDisplay();
        OLED_Update();
    }

    if (MENU_SHOW_FLAG) {
        if (VAL_CHANGE_FLAG) {
            if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_VALUE) MENU_USE_VAL(MENU_POINTER[MENU_INDEX_COUNTER].text, MENU_POINTER[MENU_INDEX_COUNTER].max, MENU_POINTER[MENU_INDEX_COUNTER].min, MENU_TEMP_VAL);
            else if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SELECT) MENU_USE_SELECT(MENU_POINTER[MENU_INDEX_COUNTER].text, MENU_SELECT_LIST, MENU_TEMP_VAL);
            else if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SHOW_DATA) MENU_SHOW_DATA_PRINT(SHOW_DATA_TEXT, MENU_TEMP_VAL);
        } else MENU_TEXT_PRINT(MENU_POINTER[MENU_INDEX_COUNTER].text, MENU_INDEX_COUNTER);
    }
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MENU BUTONLARI">

#define PRESSED_OK 0x01
#define PRESSED_UP 0x02
#define PRESSED_DOWN 0x04
#define PRESSED_BACK 0x08
byte MENU_BUTON_STATUS = 0;

void MENU_BUTON_READ()
{
    static Buton_t MENU_OK;
    static Buton_t MENU_DOWN;
    static Buton_t MENU_UP;
    byte temp = 0;

    temp = BUTON_PROCESS(&MENU_UP, PIN_GET_PORT('B', 0), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            // if (BUTON_GET_TIME(&MENU_UP));
        }
        if (temp == BUTON_PRESSED) {
            MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_UP;
        }
    }


    temp = BUTON_PROCESS(&MENU_OK, PIN_GET_PORT('B', 1), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            //  if (BUTON_GET_TIME(&MENU_OK));
        }
        if (temp == BUTON_PRESSED) {
            if (BUTON_GET_TIME(&MENU_OK) > 1000) MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_BACK;
            else MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_OK;
        }
    }


    temp = BUTON_PROCESS(&MENU_DOWN, PIN_GET_PORT('B', 2), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            //      if (BUTON_GET_TIME(&MENU_DOWN));
        }
        if (temp == BUTON_PRESSED) {

            MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_DOWN;
        }
    }
}

void MENU_BUTON_PROCESS()
{
    if (MENU_BUTON_STATUS) {
        if (MENU_BUTON_STATUS & PRESSED_UP) {
            MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_UP;
            MENU_WORK('U');
        }
        if (MENU_BUTON_STATUS & PRESSED_OK) {
            MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_OK;
            MENU_WORK('O');
        }

        if (MENU_BUTON_STATUS & PRESSED_DOWN) {
            MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_DOWN;
            MENU_WORK('D');
        }
        if (MENU_BUTON_STATUS & PRESSED_BACK) {

            MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_BACK;
            MENU_WORK('B');
        }
    }
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="INPUT ENTER">
#define IN_INPUT_A_PRESSED 0x0001
#define IN_INPUT_A_RELEASED 0x0002
#define IN_INPUT_B_PRESSED 0x0004
#define IN_INPUT_B_RELEASED 0x0008
#define IN_INHIBIT_A_PRESSED 0x0010
#define IN_INHIBIT_A_RELEASED 0x0020
#define IN_INHIBIT_B_PRESSED 0x0040
#define IN_INHIBIT_B_RELEASED 0x0080
#define IN_INPUT_EMG_PRESSED 0x0100
#define IN_INPUT_EMG_RELEASED 0x0200
#define IN_INPUT_EMG_MUTE_PRESSED 0x0400
#define IN_INPUT_EMG_MUTE_RELEASED 0x0800
#define IN_INPUT_RES_PRESSED 0x1000
#define IN_INPUT_RES_RELEASED 0x2000

#define IN_A_READ CHECK_BIT(PORTF,1) 
#define IN_B_READ CHECK_BIT(PORTF,2) 
#define IN_INHIBIT_A_READ CHECK_BIT(PORTF,3) 
#define IN_INHIBIT_B_READ CHECK_BIT(PORTF,4) 
#define IN_EMG_READ CHECK_BIT(PORTF,5) 
#define IN_EMG_MUTE_READ CHECK_BIT(PORTF,6) 
#define IN_RES_READ CHECK_BIT(PORTF,7) 

word IN_STATUS = 0;

void INPUT_READ()
{
#define DEBOUNCE_TIME 4
    byte temp = 0;
    static Input_t INPUT_A;
    temp = INPUT_DEBOUNCE(&INPUT_A, IN_A_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_A_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_A_RELEASED;
    }
    static Input_t INPUT_B;
    temp = INPUT_DEBOUNCE(&INPUT_B, IN_B_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_B_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_B_RELEASED;
    }
    static Input_t INHIBIT_A;
    temp = INPUT_DEBOUNCE(&INHIBIT_A, IN_INHIBIT_A_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_A_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_A_RELEASED;
    }
    static Input_t INHIBIT_B;
    temp = INPUT_DEBOUNCE(&INHIBIT_B, IN_INHIBIT_B_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_B_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_B_RELEASED;
    }
    static Input_t INPUT_EMG;
    temp = INPUT_DEBOUNCE(&INPUT_EMG, IN_EMG_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_RELEASED;
    }

    static Input_t INPUT_EMG_MUTE;
    temp = INPUT_DEBOUNCE(&INPUT_EMG_MUTE, IN_EMG_MUTE_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_MUTE_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_MUTE_RELEASED;
    }
    static Input_t RES;
    temp = INPUT_DEBOUNCE(&RES, IN_RES_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_RES_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_RES_RELEASED;
    }
}

void INPUT_PROCESS()
{
    if (IN_STATUS) {
        if (IN_STATUS & IN_INPUT_A_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_A_PRESSED;
            LOG_PRINT("INPUT A PRESSED");
        }
        if (IN_STATUS & IN_INPUT_A_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_A_RELEASED;
            LOG_PRINT("INPUT A RELEASED");
        }
        if (IN_STATUS & IN_INPUT_B_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_B_PRESSED;
            LOG_PRINT("INPUT B PRESSED");
        }
        if (IN_STATUS & IN_INPUT_B_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_B_RELEASED;
            LOG_PRINT("INPUT B RELEASED");
        }
        if (IN_STATUS & IN_INHIBIT_A_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_A_PRESSED;
            LOG_PRINT("INHIBIT A PRESSED");
        }
        if (IN_STATUS & IN_INHIBIT_A_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_A_RELEASED;
            LOG_PRINT("INHIBIT A RELEASED");
        }
        if (IN_STATUS & IN_INHIBIT_B_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_B_PRESSED;
            LOG_PRINT("INHIBIT B PRESSED");
        }
        if (IN_STATUS & IN_INHIBIT_B_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_B_RELEASED;
            LOG_PRINT("INHIBIT B RELEASED");
        }
        if (IN_STATUS & IN_INPUT_EMG_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_PRESSED;
            LOG_PRINT("INPUT EMG PRESSED");
        }
        if (IN_STATUS & IN_INPUT_EMG_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_RELEASED;
            LOG_PRINT("INPUT EMG RELEASED");
        }
        if (IN_STATUS & IN_INPUT_EMG_MUTE_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_MUTE_PRESSED;
            LOG_PRINT("INPUT EMG MUTE PRESSED");
        }
        if (IN_STATUS & IN_INPUT_EMG_MUTE_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_MUTE_RELEASED;
            LOG_PRINT("INPUT EMG MUTE RELEASED");
        }
        if (IN_STATUS & IN_INPUT_RES_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_RES_PRESSED;
            LOG_PRINT("INPUT RES PRESSED");
        }
        if (IN_STATUS & IN_INPUT_RES_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_RES_RELEASED;
            LOG_PRINT("INPUT RES RELEASED");
        }
    }
}

// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="ROLE FONKSIYONLARI">
#define ROLE_CIKIS_AB_ENABLE SET_BIT(LATD,1)
#define ROLE_CIKIS_AB_DISABLE CLR_BIT(LATD,1)
#define ROLE_CIKIS_AB_CHECK CHECK_BIT(LATD,1)
#define ROLE_CIKIS_BA_ENABLE SET_BIT(LATD,2)
#define ROLE_CIKIS_BA_DISABLE CLR_BIT(LATD,2)
#define ROLE_CIKIS_BA_CHECK CHECK_BIT(LATD,2)
#define ROLE_CIKIS_ALARM_ENABLE SET_BIT(LATD,3)
#define ROLE_CIKIS_ALARM_DISABLE CLR_BIT(LATD,3)
#define ROLE_CIKIS_ALARM_CHECK CHECK_BIT(LATD,3)
#define ROLE_CIKIS_BUSY_ENABLE SET_BIT(LATD,4)
#define ROLE_CIKIS_BUSY_DISABLE CLR_BIT(LATD,4)
#define ROLE_CIKIS_BUSY_CHECK CHECK_BIT(LATD,4)
#define ROLE_CIKIS_MODE_NORMALLY_OPEN 0
#define ROLE_CIKIS_MODE_NORMALLY_CLOSE 1

typedef enum {
    ROLE_CIKIS_AB = 0,
    ROLE_CIKIS_BA,
    ROLE_CIKIS_ALARM,
    ROLE_CIKIS_BUSY,
    ROLE_CIKIS_DONE,
} ROLE_TYPES;
byte ROLE_CIKIS_MODE[ROLE_CIKIS_DONE];
word ROLE_CIKIS_TIME[ROLE_CIKIS_DONE];
byte ROLE_CIKIS_STATE[ROLE_CIKIS_DONE];

void ROLE_MODE_SELECT(byte index, byte mode)
{
    ROLE_CIKIS_MODE[index] = mode;
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
        else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
    }
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
        else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
    }
} //ROLENIN NORMALLY OPEN NORMALLY CLOSE OLACAGINI BELIRLEYEN FONKSIYON.

void ROLE_GO_OUTPUT(byte index, byte time)
{
    ROLE_CIKIS_STATE[index] = 1;
    ROLE_CIKIS_TIME[index] = ((time));
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
        else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
    }
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
        else

            if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
    }
} //ROLEYI CEKME ISLEMINI BASLATAN FONKSIYON.ARKA PLANDA KENDI KENDINE ISLEM TAMAMLANIR.

void ROLE_OUTPUT(byte index)
{
    if (index == ROLE_CIKIS_AB)ROLE_GO_OUTPUT(ROLE_CIKIS_AB, SETTING_VALUES[ROLE_A_TIME]);
    if (index == ROLE_CIKIS_BA)ROLE_GO_OUTPUT(ROLE_CIKIS_BA, SETTING_VALUES[ROLE_B_TIME]);
    if (index == ROLE_CIKIS_BUSY)ROLE_GO_OUTPUT(ROLE_CIKIS_BUSY, SETTING_VALUES[ROLE_BUSY_TIME]);
    if (index == ROLE_CIKIS_ALARM)ROLE_GO_OUTPUT(ROLE_CIKIS_ALARM, SETTING_VALUES[ROLE_ALARM_TIME]);
}

void INTERRUPT_KONTROL_ROLE_TIME()
{
    for (byte x = 0; x < 4; x++) {
        if (ROLE_CIKIS_STATE[x] == 0) continue;
        else {
            if (ROLE_CIKIS_TIME[x]) ROLE_CIKIS_TIME[x] = ROLE_CIKIS_TIME[x] - 1;
            else {
                if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_OPEN) {
                    if (x == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
                    else if (x == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
                    else if (x == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
                    else if (x == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
                }
                if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) {
                    if (x == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
                    else if (x == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
                    else if (x == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
                    else if (x == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
                }
                ROLE_CIKIS_STATE[x] = 0;
            }
        }
    }
} //ON FONDA BASLANGICI YAPILMIS OLAN ROLE CIKISLARINI NC,NO VE ZAMANINA GORE SAYIP BITIS ISLEMLERINI YAPAN FONKSIYON.

void INIT_ROLE()
{
    SETTING_VALUES[ROLE_A_TIME] = 5;
    SETTING_VALUES[ROLE_B_TIME] = 10;
    SETTING_VALUES[ROLE_BUSY_TIME] = 15;
    SETTING_VALUES[ROLE_ALARM_TIME] = 20;

    SETTING_VALUES[ROLE_A_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;
    SETTING_VALUES[ROLE_B_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;
    SETTING_VALUES[ROLE_ALARM_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;
    SETTING_VALUES[ROLE_BUSY_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;

    ROLE_MODE_SELECT(ROLE_CIKIS_AB, SETTING_VALUES[ROLE_A_MODE]);
    ROLE_MODE_SELECT(ROLE_CIKIS_BA, SETTING_VALUES[ROLE_B_MODE]);
    ROLE_MODE_SELECT(ROLE_CIKIS_ALARM, SETTING_VALUES[ROLE_ALARM_MODE]);
    ROLE_MODE_SELECT(ROLE_CIKIS_BUSY, SETTING_VALUES[ROLE_BUSY_MODE]);
} //ROLE NO NC EPROOMDAKI KAYITLI DURUMA GORE SETLENIYOR.

//// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="THREAD      ">
//---------------------------------------------------------------------------------------------------------------------
// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT">

void LED_THREAD(byte threadIndex)
{

}

void INPUT_THREAD(byte threadIndex)
{
    MENU_BUTON_READ();
    MENU_BUTON_PROCESS();
    INPUT_READ();
    INPUT_PROCESS();
}

void ROLE_THREAD(byte threadIndex)
{
    INTERRUPT_KONTROL_ROLE_TIME();
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="CONFIG      ">

THREAD_t THREAD_LIST[THREAD_NUM] = {
    {.flag = THREAD_FLG_START | THREAD_FLG_LOOP, .duty_time = 1, .Funct = &LED_THREAD},
    {.flag = THREAD_FLG_START | THREAD_FLG_LOOP, .duty_time = 10, .Funct = &INPUT_THREAD},
    {.flag = THREAD_FLG_START | THREAD_FLG_LOOP, .duty_time = 100, .Funct = &ROLE_THREAD},
};
// </editor-fold> 
//---------------------------------------------------------------------------------------------------------------------
// </editor-fold>

void main(void)
{
    SET_OSC(64);
    //    PIN_SET_IO('D', 'I', 'B', 0, 'L');
    //    PIN_SET_IO('D', 'I', 'B', 1, 'L');
    //    PIN_SET_IO('D', 'I', 'B', 2, 'L');
    PIN_SET_ANSEL(0xFF, 0xFF);
    PIN_SET_IO('D', 'O', 'A', 3, 'L');

    PIN_SET_IO('D', 'I', 'B', 4, 'L'); //SENSOR 1
    PIN_SET_IO('D', 'I', 'B', 5, 'L'); //SENSOR 2
    PIN_SET_IO('D', 'I', 'B', 6, 'L'); //SENSOR 3

    PIN_SET_IO('D', 'O', 'D', 1, 'L'); //ROLE 1
    PIN_SET_IO('D', 'O', 'D', 2, 'L'); //ROLE 2
    PIN_SET_IO('D', 'O', 'D', 3, 'L'); //ROLE 3
    PIN_SET_IO('D', 'O', 'D', 4, 'L'); //ROLE 4

    PIN_SET_IO('D', 'I', 'F', 1, 'L'); //INPUT A
    PIN_SET_IO('D', 'I', 'F', 2, 'L'); //INPUT B
    PIN_SET_IO('D', 'I', 'F', 3, 'L'); //INHIBIT A
    PIN_SET_IO('D', 'I', 'F', 4, 'L'); //INHIBIT B
    PIN_SET_IO('D', 'I', 'F', 5, 'L'); //INPUT EMG
    PIN_SET_IO('D', 'I', 'F', 6, 'L'); //INPUT EMG MUTE
    PIN_SET_IO('D', 'I', 'F', 7, 'L'); //INPUT RES

    PWM_6_INIT(10000, 2); //MOTOR FAZ1
    PWM_7_INIT(10000, 2); //MOTOR FAZ2
    PWM_8_INIT(10000, 2); //MOTOR FAZ3
    PWM_6_SET(1);
    PWM_7_SET(1);
    PWM_8_SET(1);
    PWM_6_DUTY(10);
    PWM_7_DUTY(20);
    PWM_8_DUTY(30);

    PWM_4_INIT(10000, 4); //MOSFET 1 
    PWM_5_INIT(10000, 4); //MOSFET 2
    PWM_4_SET(1);
    PWM_5_SET(1);
    PWM_4_DUTY(80);
    PWM_5_DUTY(90);


    I2C_1_INIT(100000);
    // I2C_2_INIT(100000);
    UART_1_INIT(38400);
    TIMER_1_INIT(1);
    PIN_IOC_INTERRUPT(1, 1);
    INTERRUPT_ALL(1);
    OLED_Init();
    INIT_ROLE();
    ROLE_OUTPUT(ROLE_CIKIS_AB);
    ROLE_OUTPUT(ROLE_CIKIS_BA);
    ROLE_OUTPUT(ROLE_CIKIS_BUSY);
    ROLE_OUTPUT(ROLE_CIKIS_ALARM);
    

    
    while (1) {

        THREAD_MAIN();
    }
}

void __interrupt() _ISR(void)
{
    if (INTCONbits.RBIF) {
        byte x = PORTB;
        INTCONbits.RBIF = 0;
        PIN_SET_LAT_TOGGLE('A', 3);
    } else if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_1_INTERRUPT_FUNCT();
        THREAD_INTERRUPT();
    } else if (PIR2bits.TMR3IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_3_INTERRUPT_FUNCT();
    } else if (PIR5bits.TMR5IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_5_INTERRUPT_FUNCT();
    } else if (PIR1bits.RC1IF) { // UART1 al?c? interrupt'?
        PIR1bits.RC1IF = 0;
        UART_1_BYTE(RCREG1);
        if (RCREG1 == '+') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_UP;
        if (RCREG1 == '-') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_DOWN;
        if (RCREG1 == '*') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_OK;
        if (RCREG1 == '/') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_BACK;
    } else if (PIR3bits.RC2IF) { // UART1 al?c? interrupt'?
        PIR3bits.RC2IF = 0;
        UART_2_BYTE(RCREG2);
    }
}


