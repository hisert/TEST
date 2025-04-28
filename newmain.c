#include "ATMEGA_64.h"
#include "ATMEGA_328.h"
#include "PIC_18F87K22.h"
#include "ssd1306_oled.h"
#include "input_debounce.h"
#include "buton_debounce.h"
#include "thread.h"
#include "soft_i2c.h"
#include "task.h"
//#include "MENU.h"

#include "ssh1106_oled.h"
#include "AS5600_MAS.h"

void LED_THREAD(byte threadIndex)
  {
  static THREAD_DELAY timer;
  THREAD_TIME_START(&timer);
  if (THREAD_TIME_WAIT(&timer, 50)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('C', 0);
  if (THREAD_TIME_WAIT(&timer, 950)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('C', 0);
  if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);
  }

int main(void)
  {

  PIN_SET_IO('D', 'O', 'C', 0, 'H'); //LED
  PIN_SET_IO('D', 'O', 'B', 0, 'H'); //RS45
  // SOFT_I2C_INIT(&TRISC, &LATC, &PORTC, 4, &TRISC, &LATC, &PORTC, 3);
  //    OLED_Init(I2C_1_START, I2C_1_WRITE, I2C_1_STOP);
  //    OLED_Write_Dec(0, 0, 1253);
  //    OLED_Update();
  //    INIT_ROLE();

  THREAD_CREATE(0, THREAD_FLG_START | THREAD_FLG_LOOP, 1, LED_THREAD);
  I2C_1_INIT();
  MAS12_INIT(I2C_1_START,I2C_1_WRITE,I2C_1_READ_ACK,I2C_1_READ_NACK,I2C_1_STOP);
  TIMER_1_INIT(1);
  INTERRUPT_ALL(1);
  UART_0_INIT(19200);
  UART_0_DECIMAL(MAS12_READ_HAL_DATA());

  while (1)
    {
    THREAD_MAIN();
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

#ifdef PIC_18F87K22

void __interrupt() _ISR(void)
  {
  if (INTCONbits.RBIF)
    {
    byte x = PORTB;
    INTCONbits.RBIF = 0;
    PIN_SET_LAT_TOGGLE('A', 3);
    }
  else if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
    {
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
    }
  else if (PIR2bits.TMR3IF) // Timer1 kesmesi olu?tu mu?
    {
    TIMER_3_INTERRUPT_FUNCT();
    }
  else if (PIR5bits.TMR5IF) // Timer1 kesmesi olu?tu mu?
    {
    TIMER_5_INTERRUPT_FUNCT();
    }
  else if (PIR1bits.RC1IF)
    { // UART1 al?c? interrupt'?
    PIR1bits.RC1IF = 0;
    UART_1_BYTE(RCREG1);
    if (RCREG1 == '+') MENU_BUTON_ADD('U');
    if (RCREG1 == '-') MENU_BUTON_ADD('D');
    if (RCREG1 == '*') MENU_BUTON_ADD('O');
    if (RCREG1 == '/') MENU_BUTON_ADD('B');
    }
  else if (PIR3bits.RC2IF)
    { // UART1 al?c? interrupt'?
    PIR3bits.RC2IF = 0;
    UART_2_BYTE(RCREG2);
    }
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
