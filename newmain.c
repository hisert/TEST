#include "ATMEGA_64.h"
#include "ATMEGA_328.h"
#include "PIC_18F87K22.h"

#include "input_debounce.h"
#include "buton_debounce.h"
#include "thread.h"
#include "soft_i2c.h"
#include "task.h"
#include "eeprom.h"
//#include "MENU.h"
#include "ssd1306_oled.h"
#include "ssh1106_oled.h"
#include "AS5600_MAS.h"
#include "ws2812b.h"



void LED_THREAD(byte threadIndex)
{
    static THREAD_DELAY timer;
    THREAD_TIME_START(&timer);
    if (THREAD_TIME_WAIT(&timer, 10)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('F', 0);
    if (THREAD_TIME_WAIT(&timer, 10)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('F', 0);
    if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);
    EEPROM_SET(0, EEPROM_GET(0) + 1);
}

int main(void)
{
    PIN_SET_IO('D', 'O', 'F', 0, 'H'); //LED
    PIN_SET_IO('D', 'O', 'D', 5, 'L'); //RS45
    PIN_SET_IO('D', 'O', 'D', 6, 'L'); //RS45

    THREAD_CREATE(0, THREAD_FLG_START | THREAD_FLG_LOOP, 10, LED_THREAD);
    TIMER_1_INIT(1);
    INTERRUPT_ALL(1);
    EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
    EEPROM_SET(0, 0xFFFFFF00);
    EEPROM_SET(1, 0x11223344);

    while (1) {
        THREAD_MAIN();
        TASK_MAIN();
    }
}

#ifdef ATMEGA_64

ISR(TIMER1_OVF_vect)
{
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
}

ISR(TIMER3_OVF_vect)
{
    TIMER_3_INTERRUPT_FUNCT();
}

ISR(USART0_TX_vect)
{
}

ISR(USART0_RX_vect)
{
    byte x = UDR0;
}

ISR(USART1_RX_vect)
{
    byte x = UDR1;
}

ISR(USART1_TX_vect)
{
}

#endif
#ifdef ATMEGA_328

ISR(TIMER1_OVF_vect)
{
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
}

ISR(USART_RX_vect)
{

}

ISR(USART_TX_vect)
{

}

ISR(PCINT0_vect)
{

}

#endif
#ifdef PIC_18F87K22

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
        if (RCREG1 == '+') MENU_BUTON_ADD('U');
        if (RCREG1 == '-') MENU_BUTON_ADD('D');
        if (RCREG1 == '*') MENU_BUTON_ADD('O');
        if (RCREG1 == '/') MENU_BUTON_ADD('B');
    } else if (PIR3bits.RC2IF) { // UART1 al?c? interrupt'?
        PIR3bits.RC2IF = 0;
        UART_2_BYTE(RCREG2);
    }
}
#endif
