#include <xc.h>
#include "config.h"
#include <string.h>
#include <stdio.h>

//#include "PIC_18F87K22.h"
//#include "ssd1306_oled.h"
#include "input_debounce.h"
#include "buton_debounce.h"
#include "thread.h"
#include "soft_i2c.h"
#include "task.h"
//#include "MENU.h"
#include "ATMEGA_64.h"

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
#define SET_BIT(reg,bit) (reg = reg | (1 << bit))
#define CLR_BIT(reg,bit) (reg = reg & ~(1 << bit))
#define TOGGLE_BIT(reg,bit) (reg = reg ^ (1 << bit))
#define CHECK_BIT(reg,bit) ((reg & (1 << bit)) / (1 << bit))
void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);

// </editor-fold>

void LED_THREAD(byte threadIndex)
  {
  static THREAD_DELAY timer;
  THREAD_TIME_START(&timer);
  if (THREAD_TIME_WAIT(&timer, 950)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('E', 2);
  if (THREAD_TIME_WAIT(&timer, 50)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('E', 2);
  if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);
  }

int main(void)
  {
  TIMER_3_INIT(1);
  PIN_SET_IO('D', 'O', 'E', 2, 'H');
  // SOFT_I2C_INIT(&TRISC, &LATC, &PORTC, 4, &TRISC, &LATC, &PORTC, 3);
  //    OLED_Init(I2C_1_START, I2C_1_WRITE, I2C_1_STOP);
  //    OLED_Write_Dec(0, 0, 1253);
  //    OLED_Update();
  //    INIT_ROLE();
  //    ROLE_OUTPUT(ROLE_CIKIS_AB);
  //    ROLE_OUTPUT(ROLE_CIKIS_BA);
  //    ROLE_OUTPUT(ROLE_CIKIS_BUSY);
  //    ROLE_OUTPUT(ROLE_CIKIS_ALARM);

  THREAD_CREATE(0, THREAD_FLG_START | THREAD_FLG_LOOP, 1, LED_THREAD);
  INTERRUPT_ALL(1);
  UART_0_INIT(9600);
  UART_0_STRING("HELLO");
  UART_1_INIT(9600);
  UART_1_STRING("WORLD");
  while (1)
    {
    THREAD_MAIN();
    }
  }

//void __interrupt() _ISR(void)
//{
//    if (INTCONbits.RBIF) {
//        byte x = PORTB;
//        INTCONbits.RBIF = 0;
//        PIN_SET_LAT_TOGGLE('A', 3);
//    } else if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
//    {
//        TIMER_1_INTERRUPT_FUNCT();
//        THREAD_INTERRUPT();
//    } else if (PIR2bits.TMR3IF) // Timer1 kesmesi olu?tu mu?
//    {
//        TIMER_3_INTERRUPT_FUNCT();
//    } else if (PIR5bits.TMR5IF) // Timer1 kesmesi olu?tu mu?
//    {
//        TIMER_5_INTERRUPT_FUNCT();
//    } else if (PIR1bits.RC1IF) { // UART1 al?c? interrupt'?
//        PIR1bits.RC1IF = 0;
//        UART_1_BYTE(RCREG1);
//        if (RCREG1 == '+') MENU_BUTON_ADD('U');
//        if (RCREG1 == '-') MENU_BUTON_ADD('D');
//        if (RCREG1 == '*') MENU_BUTON_ADD('O');
//        if (RCREG1 == '/') MENU_BUTON_ADD('B');
//    } else if (PIR3bits.RC2IF) { // UART1 al?c? interrupt'?
//        PIR3bits.RC2IF = 0;
//        UART_2_BYTE(RCREG2);
//    }
//}

ISR(TIMER3_OVF_vect)
  {
  TIMER_3_INTERRUPT_FUNCT();
  THREAD_INTERRUPT();
  }

