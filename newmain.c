#include "ATMEGA_64.h"
#include "ATMEGA_328.h"
#include "ATMEGA_88.h"
#include "ATMEGA_8.h"
#include "PIC_18F87K22.h"

#include "input_debounce.h"
#include "buton_debounce.h"
#include "thread.h"
#include "soft_i2c.h"
#include "task.h"
#include "eeprom.h"
#include "MENU.h"
#include "ssd1306_oled.h"
#include "ssh1106_oled.h"
#include "AS5600_MAS.h"
#include "ws2812b.h"
#include "time_out.h"
#include "register.h"
#include "PIC_18F67K40.h"

void TASK_UART_1_RX_FUNCT(byte taskIndex);
void TASK_UART_0_RX_FUNCT(byte taskIndex);

// <editor-fold defaultstate="collapsed" desc="VARIABLES      ">
char UART_1_MSG[20];
char UART_0_MSG[20];
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM FUNCT   ">

void SYSTEM_CONTROL_ALL()
{
    THREAD_MAIN();
    TASK_MAIN();
}

byte WAIT_WHILE(word ms)
{
    static TIME_OUT_t time_out;
    SYSTEM_CONTROL_ALL();
    return TIME_OUT_CHECK(&time_out, ms);
}

void WAIT_INTERRUPT(word ms)
{
    WAIT_WHILE(0);
    while (WAIT_WHILE(ms) == 0);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="EEPROM FUNCT   ">

typedef enum {
    MAGIC_BYTES,
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

void EEPROM_GET_ALL()
{
    for (byte x = 0; x < SETTINGS_DONE; x++) SETTING_VALUES[x] = EEPROM_GET(x);
}

void EEPROM_SET_ALL()
{
    for (byte x = 0; x < SETTINGS_DONE; x++) EEPROM_SET(x, 0);
    EEPROM_SET(MAGIC_BYTES, 0xAABB);
}

void EEPROM_START()
{
    //    EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
    //  if (EEPROM_GET(MAGIC_BYTES != 0xAABB))EEPROM_SET_ALL();
    //  EEPROM_GET_ALL();
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT   ">

typedef enum {
    THREAD_LED_CANLI,
    THREAD_DEBUG,
    THREAD_MOTOR,
    THREAD_INPUT,
    THREAD_DONE,
} THREADS_tt;

void LED_THREAD(byte threadIndex)
{
    static THREAD_DELAY timer;
    THREAD_TIME_START(&timer);
    if (THREAD_TIME_WAIT(&timer, 95)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('B', 6);
    if (THREAD_TIME_WAIT(&timer, 5)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('B', 6);
    if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);

}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TASK FUNCT     ">

typedef enum {
    TASK_UART_0_RX,
    TASK_UART_1_RX,
    TASK_DONE,
} TASK_tt;

void TASK_UART_1_RX_FUNCT(byte taskIndex)
{
    TASK_STOP(taskIndex);
}

void TASK_UART_0_RX_FUNCT(byte taskIndex)
{
    TASK_STOP(taskIndex);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MAIN FUNCT     ">
// <editor-fold defaultstate="collapsed" desc="UART INTERRUPT FUNCT">

void UART_5_INTERRUPT_FUNCT(byte data)
{
}

void UART_4_INTERRUPT_FUNCT(byte data)
{
}

void UART_3_INTERRUPT_FUNCT(byte data)
{
}

void UART_1_INTERRUPT_FUNCT(byte data)
{
    static byte counter = 0;
    byte x = data;
    if (x == '<') counter = 0;
    else if (x == '>') {
        UART_1_MSG[counter] = 0;
        TASK_START(TASK_UART_1_RX);
    }
    if (counter < 20) UART_1_MSG[counter++] = x;
}

void UART_0_INTERRUPT_FUNCT(byte data)
{
    static byte counter = 0;
    byte x = data;
    if (x == '(') counter = 0;
    else if (x == ')') {
        UART_0_MSG[counter] = 0;
        TASK_START(TASK_UART_0_RX);
    } else if (counter < 20) UART_0_MSG[counter++] = x;
}
// </editor-fold>

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PROJE FUNCT    ">



// </editor-fold>

int main(void)
{
    MCU_INIT(64);

    PIN_SET_IO('D', 'O', 'B', 6, 'H '); //CANLI 
    TIMER_1_INIT(1);
    THREAD_CREATE(THREAD_LED_CANLI, THREAD_FLG_START | THREAD_FLG_LOOP, 10, LED_THREAD);

    // TASK_CREATE(TASK_UART_0_RX, 0, TASK_UART_0_RX_FUNCT);
    // TASK_CREATE(TASK_UART_1_RX, 0, TASK_UART_1_RX_FUNCT);
    // TASK_CREATE(TASK_REG_RANDCODE, THREAD_FLG_START, REG_CHANGE_RANDCODE);
    INTERRUPT_ALL(1);
    while (1) SYSTEM_CONTROL_ALL();

}

// <editor-fold defaultstate="collapsed" desc="INTERRUPT FUNCT">

#ifdef ATMEGA_64

ISR(TIMER1_OVF_vect)
{

    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
    TIME_OUT_COUNT_INTERRUPT();
}

ISR(TIMER3_OVF_vect)
{

    TIMER_3_INTERRUPT_FUNCT();
}

ISR(USART0_RX_vect)
{

    UART_0_INTERRUPT_FUNCT(UDR0);
}

ISR(USART1_RX_vect)
{

    UART_1_INTERRUPT_FUNCT(UDR1);
}

#endif

#ifdef ATMEGA_328

ISR(TIMER1_OVF_vect)
{
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
    TIME_OUT_COUNT_INTERRUPT();
    if (MOTOR_TIME_OUT_CHECK()) FIRCASIZ_READ(HU, HV, HW);
}

ISR(USART_RX_vect)
{
    UART_0_INTERRUPT_FUNCT(UDR0);
}

ISR(PCINT0_vect)
{
    FIRCASIZ_READ(HU, HV, HW);
}

#endif

#ifdef ATMEGA_88

ISR(TIMER1_OVF_vect)
{

    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
}

#endif

#ifdef ATMEGA_8

ISR(TIMER1_OVF_vect)
{

    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
}

#endif

#ifdef PIC_18F87K22

void __interrupt() _ISR(void)
{
    if (INTCONbits.RBIF) {
        byte x = PORTB;
        INTCONbits.RBIF = 0;
    } else if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_1_INTERRUPT_FUNCT();
        THREAD_INTERRUPT();
        TIME_OUT_COUNT_INTERRUPT();
    } else if (PIR2bits.TMR3IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_3_INTERRUPT_FUNCT();
    } else if (PIR5bits.TMR5IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_5_INTERRUPT_FUNCT();
    } else if (PIR1bits.RC1IF) { // UART1 al?c? interrupt'?
        PIR1bits.RC1IF = 0;
        UART_0_INTERRUPT_FUNCT(RCREG1);
    } else if (PIR3bits.RC2IF) { // UART1 al?c? interrupt'?
        PIR3bits.RC2IF = 0;
        UART_1_INTERRUPT_FUNCT(RCREG2);
    }
}

#endif

#ifdef PIC_18F67K40

void __interrupt(high_priority) _ISR(void)
{
    if (PIR5bits.TMR1IF) {
        PIR5bits.TMR1IF = 0;
        TIMER_1_INTERRUPT_FUNCT();
        THREAD_INTERRUPT();
        TIME_OUT_COUNT_INTERRUPT();
    } else if (PIR5bits.TMR3IF) {
        PIR5bits.TMR3IF = 0;
        TIMER_3_INTERRUPT_FUNCT();
    } else if (PIR5bits.TMR5IF) {
        PIR5bits.TMR5IF = 0;
        TIMER_5_INTERRUPT_FUNCT();
    } else if (PIR5bits.TMR7IF) {
        PIR5bits.TMR7IF = 0;
        TIMER_7_INTERRUPT_FUNCT();
    } else if (PIR3bits.RC1IF) UART_0_INTERRUPT_FUNCT(RC1REG);
    else if (PIR3bits.RC2IF) UART_1_INTERRUPT_FUNCT(RC2REG);
    else if (PIR4bits.RC3IF) UART_3_INTERRUPT_FUNCT(RC3REG);
    else if (PIR4bits.RC4IF) UART_4_INTERRUPT_FUNCT(RC4REG);
    else if (PIR4bits.RC5IF) UART_5_INTERRUPT_FUNCT(RC5REG);
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

// </editor-fold>