#include "ATMEGA_64.h"
#include "ATMEGA_328.h"
#include "ATMEGA_88.h"
#include "ATMEGA_8.h"
#include "PIC_18F87K22.h"
#include "PIC_18F67K40.h"
#include "PIC_18F46K22.h"
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

typedef enum
  {
  MAGIC_BYTES,
  SETTINGS_DONE,
  } SETTINGS;

word SETTING_VALUES[SETTINGS_DONE];

void CONFIG_SET(byte index, word data)
  {
  SETTING_VALUES[index] = data;
  }

word CONFIG_GET(byte index)
  {
  return SETTING_VALUES[index];
  }

void EEPROM_START()
  {
  EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
  if (EEPROM_GET(MAGIC_BYTES != 0xAABB))
    {
    for (byte x = 0; x < SETTINGS_DONE; x++) EEPROM_SET(x, 0);
    EEPROM_SET(MAGIC_BYTES, 0xAABB);
    }
  for (byte x = 0; x < SETTINGS_DONE; x++) SETTING_VALUES[x] = EEPROM_GET(x);
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="REG FUNCT      ">

enum REG_NAMES_t
  {
  REGx_ADDR = 0, //0 0x00
  REGx_RAND_CODE, //1 0x01
  REGx_SERI_NO, //2 0x02
  REGx_VERSION, //3 0x03
  REGx_SLAVE_ADRESS, //4 0x04
  REGx_RAND_CODE_2, //5 0x05
  REGx_NAMES_NUM,
  };

void REG_PROCESS(char *msg)
  {
#define TX_LEN 20
  static byte UNLOCK = 0;
  static word SECURE_CODE = 1111;
  dword DATA = 0;
  word ADRESS = 0;
  byte SECOND_ADRESS = 0;
  byte KOMUT = 0;

  word MY_ADRESS = REG_GET(REGx_ADDR);
  byte MY_SECOND_ADRESS = REG_GET(REGx_SLAVE_ADRESS);
  char TX[TX_LEN];
  char DATA_S[10];
  char SYMBOL_S[3];
  char ADRESS_S[6];
  char SECOND_ADRESS_S[3];
  char KOMUT_S[3];
  char READ_WRITE[2];
  char temp[10];

  REG_PARSE_INDEX(msg, SYMBOL_S, 1, 1);
  REG_PARSE_INDEX(msg, ADRESS_S, 2, 5);
  REG_PARSE_INDEX(msg, SECOND_ADRESS_S, 6, 7);
  REG_PARSE_INDEX(msg, KOMUT_S, 8, 9);
  REG_PARSE_INDEX(msg, READ_WRITE, 10, 10);
  REG_PARSE_DATA(msg, DATA_S);

  ADRESS = (word) REG_CONVERT_STR_HEX_TO_DWORD(ADRESS_S);
  SECOND_ADRESS = (byte) REG_CONVERT_STR_HEX_TO_DWORD(SECOND_ADRESS_S);
  KOMUT = (byte) REG_CONVERT_STR_HEX_TO_DWORD(KOMUT_S);

  DATA = REG_PROCESS_GET_DATA_DEC(KOMUT, DATA_S);

  if (REG_PARSE_COMPARE(SYMBOL_S, "Q")) return;
  if (ADRESS == 0)
    {
    if (KOMUT == REGx_RAND_CODE) goto passed;
    if (UNLOCK) goto passed;
    return;
    }
  if ((KOMUT == REGx_ADDR) || (KOMUT == REGx_SLAVE_ADRESS)) if (UNLOCK) goto passed;
  if ((ADRESS == MY_ADRESS) && (SECOND_ADRESS == MY_SECOND_ADRESS)) goto passed;
  return;

passed:
  for (byte x = 0; x < TX_LEN; x++) TX[x] = 0x00;
  if (REG_PARSE_COMPARE(READ_WRITE, ":") == 0)
    {
    if ((REG_GET_FLAG(KOMUT) & RG_NV) & (UNLOCK == 0)) return;
    if (REG_GET_FLAG(KOMUT) & RG_WR)
      {
      if (KOMUT == REGx_RAND_CODE)
        {
        if (DATA == 0x0000)
          {
          UNLOCK = 0;
          REG_SET_UNLOCK_START();
          REG_SET(KOMUT, 0);
          //task start
          }
        else if ((DATA ^SECURE_CODE) == REG_GET(KOMUT))
          {
          UNLOCK = 0xFF;
          REG_SET(KOMUT, DATA);
          REG_SET_UNLOCK_STOP();
          }
        else
          {
          UNLOCK = 0;
          REG_SET(KOMUT, 0);
          REG_SET_UNLOCK_STOP();
          }
        }
      else REG_SET(KOMUT, DATA);
      if (REG_GET_FLAG(KOMUT) & RG_FNC) REG_FUNC(KOMUT, ':');
      }
    else return;
    }
  if (REG_PARSE_COMPARE(READ_WRITE, "?") == 0)
    {
    if (REG_GET_FLAG(KOMUT) & RG_RD)
      {
      if (KOMUT == REGx_RAND_CODE)
        {
        if (REG_GET_UNLOCK())
          {
          REG_CHANGE_RANDCODE();
          REG_SET(KOMUT, REG_GET_RANDCODE());
          REG_SET_UNLOCK_STOP();
          }
        else return;
        }
      if (REG_GET_FLAG(KOMUT) & RG_FNC) REG_FUNC(KOMUT, '?');
      }
    else return;
    }
  if (REG_GET_FLAG(KOMUT) & RG_NV) REG_EEPROM_SET(KOMUT);

  REG_PROCESS_GET_DATA_STR(KOMUT, temp);
  REG_CONVERT_DWORD_TO_STR_HEX(REG_GET(REGx_ADDR), ADRESS_S, 4);
  REG_CONVERT_DWORD_TO_STR_HEX(REG_GET(REGx_SLAVE_ADRESS), SECOND_ADRESS_S, 2);
  if (REG_GET_FLAG(KOMUT) & RG_MAIN) REG_TX_ADD(TX, "MAIN1");
  REG_TX_ADD(TX, "<");

  REG_TX_ADD(TX, SYMBOL_S);
  REG_TX_ADD(TX, "R");
  REG_TX_ADD(TX, ADRESS_S);
  REG_TX_ADD(TX, SECOND_ADRESS_S);
  REG_TX_ADD(TX, KOMUT_S);
  REG_TX_ADD(TX, ":");
  REG_TX_ADD(TX, temp);
  REG_TX_ADD(TX, ">");

  if (REG_GET_FLAG(KOMUT) & RG_EN); // UART_0_STRING(TX);
  }

void INIT_REG()
  {
  REG_CREATE(REGx_ADDR, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
  REG_CREATE(REGx_RAND_CODE, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD, 0, 0xFFFF, 0);
  REG_CREATE(REGx_SERI_NO, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
  REG_CREATE(REGx_VERSION, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_RD, 0x10, 0xFFFF, 0);
  REG_CREATE(REGx_SLAVE_ADRESS, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_2 | RG_WR | RG_RD | RG_NV, 0, 0xFF, 0);
  REGISTER_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MAIN FUNCT     ">


// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PROJE FUNCT    ">



// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TASK FUNCT     ">

typedef enum
  {
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
// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT   ">

typedef enum
  {
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
// <editor-fold defaultstate="collapsed" desc="INTERRUPT FUNCT">

void UART_5_INTERRUPT_FUNCT(byte data)
  {
  }

void UART_4_INTERRUPT_FUNCT(byte data)
  {
  }

void UART_3_INTERRUPT_FUNCT(byte data)
  {
  }

void UART_2_INTERRUPT_FUNCT(byte data)
  {
  static byte counter = 0;
  byte x = data;
  if (x == '<') counter = 0;
  else if (x == '>')
    {
    UART_1_MSG[counter] = 0;
    TASK_START(TASK_UART_1_RX);
    }
  if (counter < 20) UART_1_MSG[counter++] = x;
  }

void UART_1_INTERRUPT_FUNCT(byte data)
  {
  static byte counter = 0;
  byte x = data;
  if (x == '(') counter = 0;
  else if (x == ')')
    {
    UART_0_MSG[counter] = 0;
    TASK_START(TASK_UART_0_RX);
    }
  else if (counter < 20) UART_0_MSG[counter++] = x;
  }
// </editor-fold>

int main(void)
  {
  MCU_INIT(SYSTEM_FREQ_INTERNAL, SYSTEM_FREQ_INTERNAL_64);
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

#ifdef __AVR_ATmega64__

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

  UART_1_INTERRUPT_FUNCT(UDR0);
  }

ISR(USART1_RX_vect)
  {

  UART_2_INTERRUPT_FUNCT(UDR1);
  }

#endif

#ifdef __AVR_ATmega328__

ISR(TIMER1_OVF_vect)
  {
  TIMER_1_INTERRUPT_FUNCT();
  THREAD_INTERRUPT();
  TIME_OUT_COUNT_INTERRUPT();
  if (MOTOR_TIME_OUT_CHECK()) FIRCASIZ_READ(HU, HV, HW);
  }

ISR(USART_RX_vect)
  {
  UART_1_INTERRUPT_FUNCT(UDR0);
  }

ISR(PCINT0_vect)
  {
  FIRCASIZ_READ(HU, HV, HW);
  }

#endif

#ifdef __AVR_ATmega88__

ISR(TIMER1_OVF_vect)
  {

  TIMER_1_INTERRUPT_FUNCT();
  THREAD_INTERRUPT();
  }

#endif

#ifdef __AVR_ATmega8__

ISR(TIMER1_OVF_vect)
  {

  TIMER_1_INTERRUPT_FUNCT();
  THREAD_INTERRUPT();
  }

#endif

#ifdef __18F87K22

void __interrupt() _ISR(void)
  {
  if (INTCONbits.RBIF)
    {
    byte x = PORTB;
    INTCONbits.RBIF = 0;
    }
  else if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
    {
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
    TIME_OUT_COUNT_INTERRUPT();
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
    UART_1_INTERRUPT_FUNCT(RCREG1);
    }
  else if (PIR3bits.RC2IF)
    { // UART1 al?c? interrupt'?
    PIR3bits.RC2IF = 0;
    UART_2_INTERRUPT_FUNCT(RCREG2);
    }
  }

#endif

#ifdef __18F67K40

void __interrupt(high_priority) _ISR(void)
  {
  if (PIR5bits.TMR1IF)
    {
    PIR5bits.TMR1IF = 0;
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
    TIME_OUT_COUNT_INTERRUPT();
    }
  else if (PIR5bits.TMR3IF)
    {
    PIR5bits.TMR3IF = 0;
    TIMER_3_INTERRUPT_FUNCT();
    }
  else if (PIR5bits.TMR5IF)
    {
    PIR5bits.TMR5IF = 0;
    TIMER_5_INTERRUPT_FUNCT();
    }
  else if (PIR5bits.TMR7IF)
    {
    PIR5bits.TMR7IF = 0;
    TIMER_7_INTERRUPT_FUNCT();
    }
  else if (PIR3bits.RC1IF) UART_1_INTERRUPT_FUNCT(RC1REG);
  else if (PIR3bits.RC2IF) UART_2_INTERRUPT_FUNCT(RC2REG);
  else if (PIR4bits.RC3IF) UART_3_INTERRUPT_FUNCT(RC3REG);
  else if (PIR4bits.RC4IF) UART_4_INTERRUPT_FUNCT(RC4REG);
  else if (PIR4bits.RC5IF) UART_5_INTERRUPT_FUNCT(RC5REG);
  else if (PIE0bits.IOCIE)
    {
    // <editor-fold defaultstate="collapsed" desc="IOC B ">
    if (IOCBF)
      {
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
    if (IOCCF)
      {
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
    if (IOCEF)
      {
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
    if (IOCGF)
      {
      if (IOCGFbits.IOCGF5) IOCGFbits.IOCGF5 = 0;
      }
    // </editor-fold> 
    }

  }
#endif

#ifdef __18F46K22

void __interrupt(high_priority) _ISR(void)
  {
  if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
    {
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
    TIME_OUT_COUNT_INTERRUPT();
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
    {
    PIR1bits.RC1IF = 0;
    UART_1_INTERRUPT_FUNCT(RCREG1);
    }
  else if (PIR3bits.RC2IF)
    {
    PIR3bits.RC2IF = 0;
    UART_2_INTERRUPT_FUNCT(RCREG2);
    }
  }

#endif

// </editor-fold>