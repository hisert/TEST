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
#include "eeprom.h"
#include "MENU.h"
#include "ssd1306_oled.h"
#include "ssh1106_oled.h"
#include "AS5600_MAS.h"
#include "ws2812b.h"
#include "register.h"
#define MOTOR_SYSTEM_FLAG_MAS12_DISCONNECT 0x0001
#define MOTOR_SYSTEM_FLAG_MOTOR_WORKING 0x0002
#define MOTOR_SYSTEM_FLAG_MOTOR_HAS_TORK 0x0004
#define MOTOR_SYSTEM_FLAG_MOTOR_HAS_ZORLANMA 0x0008
#define SYSTEM_FLAG_MOTOR_HAS_TIME_OUT 0x1000
#define MOTOR_SYSTEM_FLAG_MOTOR_HAS_WIRE_CHECK 0x0010
#define MOTOR_SYSTEM_FLAG_MOTOR_HAS_WIRE_CONNEC_ERROR 0x0020
#define MOTOR_SYSTEM_FLAG_MAS12_NOT_SET 0x0040
#define MOTOR_SYSTEM_FLAG_MOTOR_FIRCALI 0x0080
#define MOTOR_SYSTEM_FLAG_KAPI_KONUM_A 0x0100
#define MOTOR_SYSTEM_FLAG_KAPI_KONUM_B 0x0200
#define MOTOR_SYSTEM_FLAG_KAPI_KONUM_0 0x0400
#define SYSTEM_FLAG_KAPI_KONUM_E 0x2000
#define MOTOR_SYSTEM_FLAG_MOTOR_SUCCESS 0x0800

typedef enum
  {
  LED_KAPALI,
  LED_AB_INPUT,
  LED_A_GECIS_START,
  LED_B_GECIS_START,
  LED_KIRMIZI_ALARM,
  LED_A_INPUT_B_SERBEST,
  LED_B_INPUT_A_SERBEST,
  LED_A_INBUT_B_INHIBIT,
  LED_B_INPUT_A_IHHIBIT,
  LED_B_SERBEST_A_INHIBIT,
  LED_A_SERBEST_B_INHIBIT,
  LED_AB_SERBEST,
  LED_AB_INHIBIT,
  LED_A_GECIS_STOP,
  LED_B_GECIS_STOP,
  LED_YESIL_ALARM,
  LED_DIAGNOSTIC_START,
  LED_A_GECIS_START_SARI,
  LED_B_GECIS_START_SARI,
  LED_LAST,
  } LED_PATTERN_TYPES;

typedef enum
  {
  TURNIKE_TYPE_HG04 = 0,
  TURNIKE_TYPE_PG04,
  TURNIKE_TYPE_PG03,
  TURNIKE_TYPE_HG01,
  TURNIKE_TYPE_HG02_DP,
  TURNIKE_TYPE_SG,
  TURNIKE_TYPE_REZ1,
  TURNIKE_TYPE_REZ2,
  TURNIKE_TYPE_REZ3,
  TURNIKE_TYPE_LAST,
  } TURNIKE_TYPES;

typedef enum
  {
  SOUND_START = 1,
  SOUND_INPUT,
  SOUND_ALARM,
  SOUND_EMERGY,
  SOUND_LOW_BATTERY,
  SOUND_COM_ERROR,
  SOUND_GECIS_STAND_WAIT,
  SOUND_HURRA_COUNTER,
  SOUND_LAST,
  } SOUND_TYPES;

byte TURNIKE_MODE = TURNIKE_TYPE_HG04;
byte MP3_SOUND_SELECTED = 0;
byte LED_PATTERN_SELECTED = 0;
word PANEL_MASTER_STATUS = 0;
word PANEL_SLAVE_STATUS = 0;

//// <editor-fold defaultstate="collapsed" desc="PIN DEFINE ISLEMLERI                                                           ">

#define RS485_ENABLE SET_BIT(PORTC,6)
#define RS485_DISABLE CLR_BIT(PORTC,6)
#define RS485_CHECK CHECK_BIT(PORTC,6)
#define RX_ENABLE SET_BIT(UCSR1B,RXEN1)
#define RX_DISABLE CLR_BIT(UCSR1B,RXEN1)
#define RX_CHECK CHECK_BIT(UCSR1B,RXEN1)
//------------------------------------------------------------------------------
#define AKU_ENABLE SET_BIT(PORTF,6)
#define AKU_DISABLE CLR_BIT(PORTF,6)
#define AKU_READ ADC_READ(0)
#define AKU_GET ((32.72* AKU_READ ))
#define AKU_CIKIS_CHECK CHECK_BIT(PORTF,6)
//------------------------------------------------------------------------------
#define SOUND_DISABLE SET_BIT(PORTF,7)
#define SOUND_ENABLE CLR_BIT(PORTF,7)
#define SOUND_READY_CHECK_1 ADC_READ(3) < 500  
#define SOUND_READY_CHECK_2 ADC_READ(3) > 450  
#define SOUND_READY_CHECK SOUND_READY_CHECK_1 && SOUND_READY_CHECK_2
#define SOUND_CHECK (ADC_READ(3) < 300)
//------------------------------------------------------------------------------
#define MENU_BUTON_UP_READ CHECK_BIT(PINB,5)
#define MENU_BUTON_O_READ CHECK_BIT(PINB,6)
#define MENU_BUTON_DOWN_READ CHECK_BIT(PINB,7)
//// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="VARIABLES      ">

typedef enum
  {
  THREAD_LED,
  THREAD_UART_1_RX,
  THREAD_UART_2_RX,
  THREAD_INPUT,
  THREAD_RELAY,
  THREAD_DONE,
  } THREAD_LIST;

THREAD_t THREADS[THREAD_DONE];
THREAD_t THREAD_MCU_ROLE_UPDATE;
THREAD_t THREAD_SI_SENSOR_GET;
THREAD_t THREAD_MOTOR_STATUS_GET;
THREAD_t THREAD_SI_LED_UPDATE;
THREAD_t THREAD_MP3_CHECK;
char UART_2_MSG[20];
char UART_1_MSG[20];

byte UART_2_RX_ARRVIED_FLAG = 0;

word SI_SENSOR_STATUS = 0;
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM FUNCT   ">
byte WAIT_WHILE_FLAG = 0;

void SYSTEM_CONTROL_ALL()
  {
  THREAD_ARRAY_CHECK(THREADS, ARRAY_SIZE(THREADS));
  }

void WAIT_INTERRUPT(word ms)
  {
  static TIME_OUT_t time_out;
  TIME_OUT_RESET(&time_out);
  while (1)
    {
    SYSTEM_CONTROL_ALL();
    if (TIME_OUT_CHECK(&time_out, ms)) break;
    }
  }

void WAIT_WHILE_RESET()
  {
  WAIT_WHILE_FLAG = 1;
  }

void WAIT_WHILE_BREAK()
  {
  WAIT_WHILE_FLAG = 0;
  }

byte WAIT_WHILE()
  {
  SYSTEM_CONTROL_ALL();
  return WAIT_WHILE_FLAG;
  }

void RS485_SEND_MESSAGE(const char *sendData)
  {
  UART_2_RX_ARRVIED_FLAG = 0;
  RX_DISABLE;
  RS485_ENABLE;
  UART_2_STRING(sendData);
  RX_ENABLE;
  RS485_DISABLE;
  }

void RS485_SEND_DECIMAL(dword sendData)
  {
  RX_DISABLE;
  RS485_ENABLE;
  UART_2_DECIMAL(sendData);
  RX_ENABLE;
  RS485_DISABLE;
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
// <editor-fold defaultstate="collapsed" desc="MAIN FUNCT     ">

byte UART_2_CONTROL()
  {
  static TIME_OUT_t time_out;
  TIME_OUT_RESET(&time_out);
  while (1)
    {
    SYSTEM_CONTROL_ALL();
    if (TIME_OUT_CHECK(&time_out, 150)) return 0;
    if (UART_2_RX_ARRVIED_FLAG) return 1;
    }
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PROJE FUNCT    ">
//// <editor-fold defaultstate="collapsed" desc="ROLE FONKSIYONLARI">

typedef enum
  {
  ROLE_CIKIS_AB = 0,
  ROLE_CIKIS_BA,
  ROLE_CIKIS_ALARM,
  ROLE_CIKIS_BUSY,
  ROLE_CIKIS_DONE,
  } ROLE_TYPES;

byte ROLE_CIKIS_MODE[ROLE_CIKIS_DONE];
word ROLE_CIKIS_TIME[ROLE_CIKIS_DONE];
byte ROLE_CIKIS_STATE[ROLE_CIKIS_DONE];
byte ROLE_STATE;

#define ROLE_CIKIS_MODE_NORMALLY_OPEN 0
#define ROLE_CIKIS_MODE_NORMALLY_CLOSE 1

void ROLE_STATE_SET(byte state)
  {
  if (CHECK_BIT(state, ROLE_CIKIS_AB)) PIN_SET_LAT('C', 5, 'H');
  else PIN_SET_LAT('C', 5, 'L');
  if (CHECK_BIT(state, ROLE_CIKIS_BA)) PIN_SET_LAT('C', 4, 'H');
  else PIN_SET_LAT('C', 4, 'L');
  if (CHECK_BIT(state, ROLE_CIKIS_ALARM)) PIN_SET_LAT('C', 2, 'H');
  else PIN_SET_LAT('C', 2, 'L');
  if (CHECK_BIT(state, ROLE_CIKIS_BUSY)) PIN_SET_LAT('C', 3, 'H');
  else PIN_SET_LAT('C', 3, 'L');
  }

void ROLE_MODE_SELECT(byte index, byte mode)
  {
  ROLE_CIKIS_MODE[index] = mode;
  byte state = 0;
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN) state = 'L';
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) state = 'H';
  if (index == ROLE_CIKIS_AB) PIN_SET_LAT('C', 5, state);
  else if (index == ROLE_CIKIS_BA) PIN_SET_LAT('C', 4, state);
  else if (index == ROLE_CIKIS_ALARM) PIN_SET_LAT('C', 2, state);
  else if (index == ROLE_CIKIS_BUSY) PIN_SET_LAT('C', 3, state);
  if (state == 'L') CLR_BIT(ROLE_STATE, index);
  if (state == 'H') SET_BIT(ROLE_STATE, index);
  } //ROLENIN NORMALLY OPEN NORMALLY CLOSE OLACAGINI BELIRLEYEN FONKSIYON.

void ROLE_GO_OUTPUT(byte index, word time)
  {
  ROLE_CIKIS_STATE[index] = 1;
  ROLE_CIKIS_TIME[index] = time;
  byte state = 0;
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) state = 'L';
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN) state = 'H';
  if (index == ROLE_CIKIS_AB) PIN_SET_LAT('C', 5, state);
  else if (index == ROLE_CIKIS_BA) PIN_SET_LAT('C', 4, state);
  else if (index == ROLE_CIKIS_ALARM) PIN_SET_LAT('C', 2, state);
  else if (index == ROLE_CIKIS_BUSY) PIN_SET_LAT('C', 3, state);
  if (state == 'L') CLR_BIT(ROLE_STATE, index);
  if (state == 'H') SET_BIT(ROLE_STATE, index);
  } //ROLEYI CEKME ISLEMINI BASLATAN FONKSIYON.ARKA PLANDA KENDI KENDINE ISLEM TAMAMLANIR.

void ROLE_TIME_KONTROL()
  {
  for (byte x = 0; x < ROLE_CIKIS_DONE; x++)
    {
    if (ROLE_CIKIS_STATE[x] == 0) continue;
    else
      {
      if (ROLE_CIKIS_TIME[x]) ROLE_CIKIS_TIME[x] = ROLE_CIKIS_TIME[x] - 1;
      else
        {
        byte state = 0;
        if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_OPEN) state = 'L';
        if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) state = 'H';
        if (x == ROLE_CIKIS_AB) PIN_SET_LAT('C', 5, state);
        else if (x == ROLE_CIKIS_BA) PIN_SET_LAT('C', 4, state);
        else if (x == ROLE_CIKIS_ALARM) PIN_SET_LAT('C', 2, state);
        else if (x == ROLE_CIKIS_BUSY) PIN_SET_LAT('C', 3, state);
        if (state == 'L') CLR_BIT(ROLE_STATE, x);
        if (state == 'H') SET_BIT(ROLE_STATE, x);
        ROLE_CIKIS_STATE[x] = 0;
        }
      }
    }
  } //ON FONDA BASLANGICI YAPILMIS OLAN ROLE CIKISLARINI NC,NO VE ZAMANINA GORE SAYIP BITIS ISLEMLERINI YAPAN FONKSIYON.

void INIT_ROLE()
  {
  ROLE_MODE_SELECT(ROLE_CIKIS_AB, ROLE_CIKIS_MODE_NORMALLY_OPEN);
  ROLE_MODE_SELECT(ROLE_CIKIS_BA, ROLE_CIKIS_MODE_NORMALLY_OPEN);
  ROLE_MODE_SELECT(ROLE_CIKIS_ALARM, ROLE_CIKIS_MODE_NORMALLY_OPEN);
  ROLE_MODE_SELECT(ROLE_CIKIS_BUSY, ROLE_CIKIS_MODE_NORMALLY_OPEN);

  ROLE_GO_OUTPUT(ROLE_CIKIS_AB, 5);
  ROLE_GO_OUTPUT(ROLE_CIKIS_BA, 10);
  ROLE_GO_OUTPUT(ROLE_CIKIS_ALARM, 15);
  ROLE_GO_OUTPUT(ROLE_CIKIS_BUSY, 20);

  } //ROLE NO NC EPROOMDAKI KAYITLI DURUMA GORE SETLENIYOR.

//// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="INPUT FUNCT     ">
word INPUT_STATE = 0;
byte INPUT_A_COUNTER = 0;
byte INPUT_B_COUNTER = 0;
byte INHIBIT_A_STATE = 0;
byte INHIBIT_B_STATE = 0;
byte EMG_A_STATE = 0;
byte EMG_B_STATE = 0;
byte EMG_STATE = 0;
byte EMG_MUTE_STATE = 0;
byte DIP_SWITH_1_STATE = 0;
byte DIP_SWITH_2_STATE = 0;
// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="MCU FONKSIYONLARI">

byte SLAVE_MCU_KOMUT_STATUS()
  {
  RS485_SEND_MESSAGE("<MMS00R>");
  return UART_2_CONTROL();
  }

byte SLAVE_MCU_KOMUT_OUTPUT()
  {
  char senddata[20];
  sprintf(senddata, "<MMS02W%d>", ROLE_STATE);
  RS485_SEND_MESSAGE(senddata);
  return UART_2_CONTROL();
  }

byte SLAVE_MCU_KOMUT_INPUT_CLEAR()
  {
  RS485_SEND_MESSAGE("<MMS01W00>");
  return UART_2_CONTROL();
  }
//// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="S-I FONKSIYONLARI                                                              ">

byte SI_COMM_KOMUT_A()
  {
  RS485_SEND_MESSAGE("<SIM04R>");
  return UART_2_CONTROL();
  }

byte SI_COMM_KOMUT_B()
  {
  RS485_SEND_MESSAGE("<SIM05R>");
  return UART_2_CONTROL();
  }

byte SI_INPUT_KOMUT_A()
  {
  RS485_SEND_MESSAGE("<SIM02R>");
  return UART_2_CONTROL();
  }

byte SI_INPUT_KOMUT_B()
  {
  RS485_SEND_MESSAGE("<SIM03R>");
  return UART_2_CONTROL();
  }

byte SI_INPUT_KOMUT_AB()
  {
  RS485_SEND_MESSAGE("<SIM01R>");
  return UART_2_CONTROL();
  }

byte SI_LED_KOMUT(byte val)
  {
  char senddata[20];
  sprintf(senddata, "<SIS00W%d>", val);
  RS485_SEND_MESSAGE(senddata);
  return UART_2_CONTROL();
  }

byte SI_LED_PARLAKLIK(byte val)
  {
  char senddata[20];
  sprintf(senddata, "<SIS10W%d>", val);
  RS485_SEND_MESSAGE(senddata);
  return UART_2_CONTROL();
  }

byte SI_TARAMA_KOMUT(byte val)
  {
  char senddata[20];
  sprintf(senddata, "<SIC06W%d>", val);
  RS485_SEND_MESSAGE(senddata);
  return UART_2_CONTROL();
  }

//// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="MP3 FONKSIYONLARI                                                              ">

void SES_PLAY(byte val)
  {
  if (val == SOUND_START); //if (SETTING_VALUES[MP3_SETTING_START_ENABLE] == 0) return;
  if (val == SOUND_INPUT); //if (SETTING_VALUES[MP3_SETTING_INPUT_ENABLE] == 0) return;
  if (val == SOUND_ALARM); //if (SETTING_VALUES[MP3_SETTING_ALARM_ENABLE] == 0) return;
  UART_2_INIT(9600);
  RS485_ENABLE;
  SOUND_ENABLE;
  UART_2_BYTE(0x7E);
  UART_2_BYTE(0x04);
  UART_2_BYTE(0x03);
  UART_2_BYTE(0x00);
  UART_2_BYTE(val);
  UART_2_BYTE(0xEF);
  WAIT_INTERRUPT(8);
  SOUND_DISABLE;
  RS485_DISABLE;
  UART_2_INIT(19200);
  WAIT_INTERRUPT(50);
  }

void SES_SET_VOLUME(byte val)
  {
  UART_2_INIT(9600);
  RS485_ENABLE;
  SOUND_ENABLE;
  UART_2_BYTE(0x7E);
  UART_2_BYTE(0x03);
  UART_2_BYTE(0x06);
  UART_2_BYTE(val);
  UART_2_BYTE(0xEF);
  WAIT_INTERRUPT(40);
  SOUND_DISABLE;
  RS485_DISABLE;
  UART_2_INIT(19200);
  }

//// </editor-fold>

char GENERAL_PANEL_KONUM_FIND()
  {
  char KONUM_NOW = 0;
  if ((FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_A))&&(FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_A))) KONUM_NOW = 'A';
  if ((FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_0))&&(FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_0))) KONUM_NOW = 'O';
  if ((FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_B))&&(FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_B))) KONUM_NOW = 'B';
  return KONUM_NOW;
  }

char GENERAL_PANEL_SUCCESS_FIND()
  {
  char KONUM_NOW = 0;
  if ((FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_MOTOR_SUCCESS)) && (FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_MOTOR_SUCCESS)))
    {
    if ((FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_A))&&(FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_A))) KONUM_NOW = 'A';
    if ((FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_0))&&(FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_0))) KONUM_NOW = 'O';
    if ((FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_B))&&(FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_KAPI_KONUM_B))) KONUM_NOW = 'B';
    }
  return KONUM_NOW;
  }

byte GENERAL_PANEL_WORKING_FIND()
  {
  if (FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_MOTOR_WORKING)) return 1;
  if (FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_MOTOR_WORKING)) return 1;
  return 0;
  }

byte GENERAL_PANEL_TORK_FIND()
  {
  if (FLAG_CONTROL(PANEL_MASTER_STATUS, MOTOR_SYSTEM_FLAG_MOTOR_HAS_TORK)) return 1;
  if (FLAG_CONTROL(PANEL_SLAVE_STATUS, MOTOR_SYSTEM_FLAG_MOTOR_HAS_TORK)) return 1;
  return 0;
  }

byte MOTOR_KAPI_STATE(char MasterSlave)
  {

  char senddata[20];
  sprintf(senddata, "<MT%c20R>", MasterSlave);
  RS485_SEND_MESSAGE(senddata);
  return UART_2_CONTROL();
  }

byte MOTOR_KAPI_KOMUT(char MasterSlave, char Direction)
  {
  if (Direction == 'S') Direction = '0';
  else if (Direction == 'A') Direction = '1';
  else if (Direction == 'B') Direction = '2';
  else if (Direction == 'O') Direction = '3';
  else if (Direction == 'W') Direction = '4';

  else return;
  char senddata[20];
  sprintf(senddata, "<MT%c00W%c>", MasterSlave, Direction);
  RS485_SEND_MESSAGE(senddata);
  return UART_2_CONTROL();
  }

byte MOTOR_HIZ_AYARLA(char MasterSlave, byte val)
  {

  char senddata[20];
  sprintf(senddata, "<MT%c10W%d>", MasterSlave, val);
  RS485_SEND_MESSAGE(senddata);
  return UART_2_CONTROL();
  }

void PANEL_HAREKET(char direction, byte hiz)
  {
  byte master_hiz = 20;
  byte slave_hiz = 20;
  if (hiz != 20)
    {
    master_hiz = hiz;
    slave_hiz = hiz;
    }
  if (MOTOR_HIZ_AYARLA('S', slave_hiz)) WAIT_INTERRUPT(0);
  if (MOTOR_HIZ_AYARLA('M', master_hiz)) WAIT_INTERRUPT(0);
  if (MOTOR_KAPI_KOMUT('S', direction)) WAIT_INTERRUPT(0);

  if (MOTOR_KAPI_KOMUT('M', direction)) WAIT_INTERRUPT(0);

  }

unsigned int myAtoiUnsigned(const char *str)
  {
  unsigned int result = 0; // Sonuç de?i?keni (i?aretsiz tamsay?)
  while (*str >= '0' && *str <= '9')
    {

    result = result * 10 + (*str - '0');
    str++;
    }

  return result; // Sonucu döndür
  }

void PROCESS_MESSAGE_MASTER(char *msg)
  {

  char buffer[20];
  for (byte x = 0; x < 20; x++) buffer[x] = msg[x];
  for (byte x = 0; x < 20; x++) msg[x] = 0;
  char RW = buffer[5];
  char CARD_ID = 'M';
  char regIndex = (buffer[3] - '0')*10 + (buffer[4] - '0');
  word regdata = myAtoiUnsigned(buffer + 7);

  if (RW == 'W')
    {
    }
  else if (RW == 'A')
    {

    if ((buffer[0] == 'S') && (buffer[1] == 'I') && (buffer[2] == 'M'))
      {
      if (regIndex == 1) SI_SENSOR_STATUS = regdata;
      //  if (regIndex == 2) SI_SENSOR_A_STATUS = regdata;
      //  if (regIndex == 3) SI_SENSOR_B_STATUS = regdata;
      //  if (regIndex == 4) SI_SENSOR_ERR_A_STATUS = regdata;
      //  if (regIndex == 5) SI_SENSOR_ERR_B_STATUS = regdata;
      }
    if ((buffer[0] == 'M') && (buffer[1] == 'T') && (buffer[2] == 'M'))
      {
      if (regIndex == 20) PANEL_MASTER_STATUS = regdata;
      }
    if ((buffer[0] == 'M') && (buffer[1] == 'T') && (buffer[2] == 'S'))
      {
      if (regIndex == 20) PANEL_SLAVE_STATUS = regdata;
      }
    //    if ((buffer[0] == 'M') && (buffer[1] == 'T') && (buffer[2] == 'M'))
    //      {
    //      if (regIndex == 20) PANEL_MASTER_STATUS = regdata;
    //      if (regIndex == 1) PANEL_MASTER_MAS12_HAM = regdata;
    //      if (regIndex == 2) for (byte x = 0; x < 6; x++) PANEL_MASTER_MAS12_MAPPED[x] = buffer[x + 7];
    //      if (regIndex == 3) PANEL_MASTER_MAS12_MAGNET = regdata;
    //
    //      }
    //    if ((buffer[0] == 'M') && (buffer[1] == 'T') && (buffer[2] == 'S'))
    //      {
    //      if (regIndex == 20) PANEL_SLAVE_STATUS = regdata;
    //      if (regIndex == 1) PANEL_SLAVE_MAS12_HAM = regdata;
    //      if (regIndex == 2) for (byte x = 0; x < 6; x++) PANEL_SLAVE_MAS12_MAPPED[x] = buffer[x + 7];
    //      if (regIndex == 3) PANEL_SLAVE_MAS12_MAGNET = regdata;
    //      }
    //    if ((buffer[0] == 'M') && (buffer[1] == 'M') && (buffer[2] == 'S'))
    //      {
    //      if (regIndex == 0) SLAVE_MCU_STATUS = regdata;
    //      }

    }

  else return;
  } //RS485 DATALARIN ISLENDIGI FONKSIYON. MASTER ICIN
// </editor-fold>
void PANEL_ORDER_READY();
void PANEL_ORDER(char NIHAI_HEDEF, byte hiz, byte while_flag, byte ats_use_flag);
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT   ">

byte THREAD_UART_1_RX_FUNCT()
  {
  // UART_1_STRING(UART_1_MSG);

  return 1;
  }

byte THREAD_UART_2_RX_FUNCT()
  {

  UART_2_RX_ARRVIED_FLAG = 1;
  PROCESS_MESSAGE_MASTER(UART_2_MSG);
  return 1;
  }

byte THREAD_LED_FUNCT()
  {
  static THREAD_DELAY timer;
  THREAD_TIME_START(&timer);
  if (THREAD_TIME_WAIT(&timer, 10)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT('B', 4, 'L');
  if (THREAD_TIME_WAIT(&timer, 90))

    if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT('B', 4, 'H');
  return 0;
  }

byte THREAD_RELAY_FUNCT()
  {
  static byte ROLE_STATE_OLD = 0;
  ROLE_TIME_KONTROL();
  if (ROLE_STATE_OLD != ROLE_STATE)
    {

    THREAD_START(&THREAD_MCU_ROLE_UPDATE);
    ROLE_STATE_OLD = ROLE_STATE;
    }
  return 0;
  }

byte THREAD_INPUT_FUNCT()
  {
#define DEBOUNCE_X 1

  static Input_t INPUT_A_x;
  static Input_t INPUT_B_x;
  static Input_t INHIBIT_A_x;
  static Input_t INHIBIT_B_x;
  static Input_t EMG_x;
  static Input_t EMG_MUTE_x;
  static Input_t TIME_RESET_x;
  static Input_t DIP_SWITCH_1_x;
  static Input_t DIP_SWITCH_2_x;
  static Input_t EXTERNAL_INPUT_1_x;
  static Input_t EXTERNAL_INPUT_2_x;
  static Input_t EXTERNAL_INPUT_3_x;
  byte temp = 0;

  temp = INPUT_DEBOUNCE(&INPUT_A_x, PIN_GET_PORT('D', 4), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) if (INHIBIT_A_STATE == 0) RS485_SEND_MESSAGE("A CAME");

  temp = INPUT_DEBOUNCE(&INPUT_B_x, PIN_GET_PORT('D', 5), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) if (INHIBIT_B_STATE == 0) RS485_SEND_MESSAGE("B CAME");

  temp = INPUT_DEBOUNCE(&INHIBIT_A_x, PIN_GET_PORT('C', 0), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) SET_BIT(INHIBIT_A_STATE, 0);
  else if (temp == INPUT_RAISE_EDGE) CLR_BIT(INHIBIT_A_STATE, 0);

  temp = INPUT_DEBOUNCE(&INHIBIT_B_x, PIN_GET_PORT('C', 1), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) SET_BIT(INHIBIT_B_STATE, 0);
  else if (temp == INPUT_RAISE_EDGE) CLR_BIT(INHIBIT_B_STATE, 0);

  temp = INPUT_DEBOUNCE(&EMG_x, PIN_GET_PORT('D', 6), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) SET_BIT(EMG_STATE, 0);
  else if (temp == INPUT_RAISE_EDGE) CLR_BIT(EMG_STATE, 0);

  temp = INPUT_DEBOUNCE(&EMG_MUTE_x, PIN_GET_PORT('G', 0), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) SET_BIT(EMG_MUTE_STATE, 0);
  else if (temp == INPUT_RAISE_EDGE) CLR_BIT(EMG_MUTE_STATE, 0);

  temp = INPUT_DEBOUNCE(&TIME_RESET_x, PIN_GET_PORT('G', 1), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE);
  else if (temp == INPUT_RAISE_EDGE);

  temp = INPUT_DEBOUNCE(&DIP_SWITCH_1_x, PIN_GET_PORT('G', 3), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) SET_BIT(DIP_SWITH_1_STATE, 0);
  else if (temp == INPUT_RAISE_EDGE) CLR_BIT(DIP_SWITH_1_STATE, 0);

  temp = INPUT_DEBOUNCE(&DIP_SWITCH_2_x, PIN_GET_PORT('G', 4), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE) SET_BIT(DIP_SWITH_2_STATE, 0);
  else if (temp == INPUT_RAISE_EDGE) CLR_BIT(DIP_SWITH_2_STATE, 0);

  temp = INPUT_DEBOUNCE(&EXTERNAL_INPUT_1_x, PIN_GET_PORT('E', 7), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE);
  else if (temp == INPUT_RAISE_EDGE);

  temp = INPUT_DEBOUNCE(&EXTERNAL_INPUT_2_x, PIN_GET_PORT('E', 6), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE);
  else if (temp == INPUT_RAISE_EDGE);

  temp = INPUT_DEBOUNCE(&EXTERNAL_INPUT_3_x, PIN_GET_PORT('E', 5), DEBOUNCE_X);
  if (temp == INPUT_FALL_EDGE);
  else

    if (temp == INPUT_RAISE_EDGE);

  return 0;
  }

byte THREAD_ALARM_CHECK_FUNCT()
  {
  static TIME_OUT_t time_out;
  if (MP3_SOUND_SELECTED)
    {
    if (TIME_OUT_CHECK(&time_out, 200))
      {
      if (SOUND_CHECK)
        {
        TIME_OUT_RESET(&time_out);
        SES_PLAY(MP3_SOUND_SELECTED);

        if (MP3_SOUND_SELECTED != SOUND_ALARM) MP3_SOUND_SELECTED = 0;
        }
      }
    }
  return 0;
  }

byte THREAD_SI_LED_UPDATE_FUNCT()
  {
  static byte Led_Old = 0;
  if (Led_Old != LED_PATTERN_SELECTED)
    {

    Led_Old = LED_PATTERN_SELECTED;
    SI_LED_KOMUT(LED_PATTERN_SELECTED);
    }
  return 0;
  }

byte THREAD_MOTOR_STATUS_GET_FUNCT()
  {
  MOTOR_KAPI_STATE('M');
  MOTOR_KAPI_STATE('S');
  return 0;
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="INTERRUPT FUNCT">

void UART_2_INTERRUPT_FUNCT(byte data)
  {
  static byte counter = 0;
  byte x = data;
  if (x == '<') counter = 0;
  else if (x == '>')
    {
    UART_2_MSG[counter] = 0;
    THREAD_START(&THREADS[THREAD_UART_2_RX]);
    }
  else

    if (counter < 20) UART_2_MSG[counter++] = x;
  }

void UART_1_INTERRUPT_FUNCT(byte data)
  {
  static byte counter = 0;
  byte x = data;
  if (x == '(') counter = 0;
  else if (x == ')')
    {
    UART_1_MSG[counter] = 0;
    THREAD_START(&THREADS[THREAD_UART_1_RX]);
    }
  else

    if (counter < 20) UART_1_MSG[counter++] = x;
  }

// </editor-fold>

byte HG04_STANDBY_ALARM_KONTROL();

int main(void)
  {
  PIN_SET_IO('D', 'O', 'B', 4, 'H'); //RUN LED 
  PIN_SET_IO('D', 'O', 'C', 6, 'L'); //RS485 
  PIN_SET_IO('D', 'O', 'F', 7, 'L'); //MP3 ENABLE

  PIN_SET_IO('D', 'I', 'D', 4, 'H'); //INPUT A 
  PIN_SET_IO('D', 'I', 'D', 5, 'H'); //INPUT B
  PIN_SET_IO('D', 'I', 'C', 0, 'H'); //INHIBIT A
  PIN_SET_IO('D', 'I', 'C', 1, 'H'); //INHIBIT B
  PIN_SET_IO('D', 'I', 'D', 6, 'H'); //EMG
  PIN_SET_IO('D', 'I', 'G', 0, 'H'); //EMG MUTE
  PIN_SET_IO('D', 'I', 'G', 1, 'H'); //TIME RESET
  PIN_SET_IO('D', 'I', 'G', 3, 'H'); //DIP SWITCH 1
  PIN_SET_IO('D', 'I', 'G', 4, 'H'); //DIP SWITCH  2
  PIN_SET_IO('D', 'I', 'E', 7, 'H'); //EXT IN 1
  PIN_SET_IO('D', 'I', 'E', 6, 'H'); //EXT IN 2
  PIN_SET_IO('D', 'I', 'E', 5, 'H'); //EXT IN 3

  PIN_SET_IO('D', 'O', 'C', 5, 'L'); //ROLE A
  PIN_SET_IO('D', 'O', 'C', 4, 'L'); //ROLE B
  PIN_SET_IO('D', 'O', 'C', 3, 'L'); //ROLE BUSY
  PIN_SET_IO('D', 'O', 'C', 2, 'L'); //ROLE ALARM

  INIT_ROLE();

  TIMER_1_INTERRUPT_CONNECT(1, TIME_OUT_COUNT_INTERRUPT);
  UART_1_INTERRUPT_FUNCT_CONNECT(9600, UART_1_INTERRUPT_FUNCT);
  UART_2_INTERRUPT_FUNCT_CONNECT(19200, UART_2_INTERRUPT_FUNCT);
  ADC_INIT();

  THREAD_INIT(&THREADS[THREAD_LED], THREAD_FLG_START | THREAD_FLG_LOOP, 10, THREAD_LED_FUNCT);
  THREAD_INIT(&THREADS[THREAD_INPUT], THREAD_FLG_START | THREAD_FLG_LOOP, 10, THREAD_INPUT_FUNCT);
  THREAD_INIT(&THREADS[THREAD_RELAY], THREAD_FLG_START | THREAD_FLG_LOOP, 100, THREAD_RELAY_FUNCT);
  THREAD_INIT(&THREADS[THREAD_UART_1_RX], 0, 0, THREAD_UART_1_RX_FUNCT);
  THREAD_INIT(&THREADS[THREAD_UART_2_RX], 0, 0, THREAD_UART_2_RX_FUNCT);

  INTERRUPT_ALL(1);

  THREAD_INIT(&THREAD_MCU_ROLE_UPDATE, 0, 0, SLAVE_MCU_KOMUT_OUTPUT);
  THREAD_INIT(&THREAD_SI_SENSOR_GET, THREAD_FLG_START | THREAD_FLG_LOOP, 0, SI_INPUT_KOMUT_AB);
  THREAD_INIT(&THREAD_MP3_CHECK, THREAD_FLG_START | THREAD_FLG_LOOP, 0, THREAD_ALARM_CHECK_FUNCT);
  THREAD_INIT(&THREAD_SI_LED_UPDATE, THREAD_FLG_START | THREAD_FLG_LOOP, 0, THREAD_SI_LED_UPDATE_FUNCT);
  THREAD_INIT(&THREAD_MOTOR_STATUS_GET, THREAD_FLG_START | THREAD_FLG_LOOP, 0, THREAD_MOTOR_STATUS_GET_FUNCT);

  MP3_SOUND_SELECTED = SOUND_START;
  LED_PATTERN_SELECTED = LED_AB_INPUT;
  WAIT_INTERRUPT(2000);
  PANEL_ORDER_READY();
  PANEL_ORDER('A', 80, 1, 0);
  PANEL_ORDER_READY();
  PANEL_ORDER('O', 80, 1, 0);
  while (1)
    {
    SYSTEM_CONTROL_ALL();
    THREAD_CHECK(&THREAD_MCU_ROLE_UPDATE);
    THREAD_CHECK(&THREAD_SI_SENSOR_GET);
    THREAD_CHECK(&THREAD_MP3_CHECK);
    THREAD_CHECK(&THREAD_SI_LED_UPDATE);
    STANDTBY_KONTROL();
    }
  }

byte HG04_STANDBY_ALARM_KONTROL()
  {
  if (CHECK_BIT(SI_SENSOR_STATUS, 0) > 0) return 1;
  if (CHECK_BIT(SI_SENSOR_STATUS, 1) > 0) return 2;
  if (CHECK_BIT(SI_SENSOR_STATUS, 2) > 0) return 2;
  if (CHECK_BIT(SI_SENSOR_STATUS, 3) > 0) return 2;
  if (CHECK_BIT(SI_SENSOR_STATUS, 4) > 0) return 1;
  return 0;
  }

void STANDTBY_KONTROL()
  {
  static TIME_OUT_t INPUT_WAITING;
  byte state = 0;
  if (TURNIKE_MODE == TURNIKE_TYPE_HG04) state = HG04_STANDBY_ALARM_KONTROL();
  if (state)
    {
    byte alarm_temp = 0;
    if (state == 2) alarm_temp = 1;
    if (TIME_OUT_CHECK(&INPUT_WAITING, 3000)) alarm_temp = 1;
    if (alarm_temp)
      {
      MP3_SOUND_SELECTED = SOUND_ALARM;
      LED_PATTERN_SELECTED = LED_KIRMIZI_ALARM;
      }
    }
  else
    {
    TIME_OUT_RESET(&INPUT_WAITING);
    if (MP3_SOUND_SELECTED == SOUND_ALARM)
      {
      MP3_SOUND_SELECTED = 0;
      LED_PATTERN_SELECTED = LED_AB_INPUT;
      }
    }
  }

byte ATS_KONTROL()
  {
  if (TURNIKE_MODE == TURNIKE_TYPE_HG04) if (CHECK_BIT(SI_SENSOR_STATUS, 2) > 0) return 1;
  return 0;
  }

void PANEL_ORDER_READY()
  {
  PANEL_ORDER(0, 0xFF, 0xFF, 0xFF);
  }

void PANEL_ORDER(char NIHAI_HEDEF, byte hiz, byte while_flag, byte ats_use_flag)
  {
  static byte LED_OLD = 0;
  static byte TORK_COUNTER = 0;
  static byte PANEL_SUCCESS = 'O';
  static byte TORK_HAVE_FLAG = 0;
  static byte TORK_SEKANS_COUNTER = 0;
  static byte PANEL_WORK_STARTED = 0;
  if ((hiz == 0xFF) &&(while_flag == 0xFF) &&(while_flag == 0xFF))
    {
    TORK_COUNTER = 0;
    PANEL_SUCCESS = 'O';
    TORK_HAVE_FLAG = 0;
    TORK_SEKANS_COUNTER = 0;
    PANEL_WORK_STARTED = 0;
    return;
    }
  if (PANEL_WORK_STARTED == 0) WAIT_WHILE_RESET();
  while (WAIT_WHILE())
    {
    THREAD_CHECK(&THREAD_MP3_CHECK);
    THREAD_CHECK(&THREAD_SI_LED_UPDATE);
    THREAD_CHECK(&THREAD_SI_SENSOR_GET);
    THREAD_CHECK(&THREAD_MOTOR_STATUS_GET);
    if (PANEL_WORK_STARTED == 0)
      {
      PANEL_WORK_STARTED = 1;
      LED_OLD = LED_PATTERN_SELECTED;
      if (GENERAL_PANEL_KONUM_FIND()) PANEL_SUCCESS = GENERAL_PANEL_KONUM_FIND();
      }
    if (GENERAL_PANEL_TORK_FIND())
      {
      MP3_SOUND_SELECTED = SOUND_ALARM;
      LED_PATTERN_SELECTED = LED_KIRMIZI_ALARM;
      PANEL_HAREKET('S', 20);
      WAIT_INTERRUPT(200);
      TORK_HAVE_FLAG = 1;
      TORK_COUNTER++;
      if (TORK_COUNTER >= 3)
        {
        TORK_COUNTER = 0;
        TORK_SEKANS_COUNTER++;
        MP3_SOUND_SELECTED = SOUND_ALARM;
        LED_PATTERN_SELECTED = LED_DIAGNOSTIC_START;
        if (TORK_SEKANS_COUNTER >= 3)
          {
          asm volatile ("  jmp 0x00");
          }
        else
          {
          for (byte x = 0; x < 200; x++)
            {
            THREAD_CHECK(&THREAD_MP3_CHECK);
            THREAD_CHECK(&THREAD_SI_LED_UPDATE);
            WAIT_INTERRUPT(30);
            }
          }
        }
      }
    else
      {
      if ((ats_use_flag) && (ATS_KONTROL()))
        {
        if (GENERAL_PANEL_WORKING_FIND())
          {
          PANEL_HAREKET('W', 20);
          MP3_SOUND_SELECTED = SOUND_ALARM;
          LED_PATTERN_SELECTED = LED_KIRMIZI_ALARM;
          }
        }
      else
        {
        if (TORK_HAVE_FLAG == 0)
          {
          if (MP3_SOUND_SELECTED == SOUND_ALARM)
            {
            MP3_SOUND_SELECTED = 0;
            LED_PATTERN_SELECTED = LED_OLD;
            }
          if (GENERAL_PANEL_SUCCESS_FIND() == NIHAI_HEDEF) break;
          else if (GENERAL_PANEL_WORKING_FIND() == 0) PANEL_HAREKET(NIHAI_HEDEF, hiz);
          }
        else
          {
          if (GENERAL_PANEL_SUCCESS_FIND() == PANEL_SUCCESS)
            {
            TORK_HAVE_FLAG = 0;
            if (MP3_SOUND_SELECTED == SOUND_ALARM)
              {
              MP3_SOUND_SELECTED = 0;
              LED_PATTERN_SELECTED = LED_OLD;
              }
            }
          if (GENERAL_PANEL_WORKING_FIND() == 0) PANEL_HAREKET(PANEL_SUCCESS, 20);
          }
        }
      }
    if (while_flag == 0) WAIT_WHILE_BREAK();
    }
  }

// <editor-fold defaultstate="collapsed" desc="INTERRUPT FUNCT">

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

// </editor-fold>

//// <editor-fold defaultstate="collapsed" desc="REG FUNCT      ">
//
//enum REG_NAMES_t {
//    REGx_ADDR = 0, //0 0x00
//    REGx_RAND_CODE, //1 0x01
//    REGx_SERI_NO, //2 0x02
//    REGx_VERSION, //3 0x03
//    REGx_SLAVE_ADRESS, //4 0x04
//    REGx_RAND_CODE_2, //5 0x05
//    REGx_NAMES_NUM,
//};
//
//void REG_PROCESS(char *msg)
//{
//#define TX_LEN 20
//    static byte UNLOCK = 0;
//    static word SECURE_CODE = 1111;
//    dword DATA = 0;
//    word ADRESS = 0;
//    byte SECOND_ADRESS = 0;
//    byte KOMUT = 0;
//
//    word MY_ADRESS = REG_GET(REGx_ADDR);
//    byte MY_SECOND_ADRESS = REG_GET(REGx_SLAVE_ADRESS);
//    char TX[TX_LEN];
//    char DATA_S[10];
//    char SYMBOL_S[3];
//    char ADRESS_S[6];
//    char SECOND_ADRESS_S[3];
//    char KOMUT_S[3];
//    char READ_WRITE[2];
//    char temp[10];
//
//    REG_PARSE_INDEX(msg, SYMBOL_S, 1, 1);
//    REG_PARSE_INDEX(msg, ADRESS_S, 2, 5);
//    REG_PARSE_INDEX(msg, SECOND_ADRESS_S, 6, 7);
//    REG_PARSE_INDEX(msg, KOMUT_S, 8, 9);
//    REG_PARSE_INDEX(msg, READ_WRITE, 10, 10);
//    REG_PARSE_DATA(msg, DATA_S);
//
//    ADRESS = (word) REG_CONVERT_STR_HEX_TO_DWORD(ADRESS_S);
//    SECOND_ADRESS = (byte) REG_CONVERT_STR_HEX_TO_DWORD(SECOND_ADRESS_S);
//    KOMUT = (byte) REG_CONVERT_STR_HEX_TO_DWORD(KOMUT_S);
//
//    DATA = REG_PROCESS_GET_DATA_DEC(KOMUT, DATA_S);
//
//    if (REG_PARSE_COMPARE(SYMBOL_S, "Q")) return;
//    if (ADRESS == 0) {
//        if (KOMUT == REGx_RAND_CODE) goto passed;
//        if (UNLOCK) goto passed;
//        return;
//    }
//    if ((KOMUT == REGx_ADDR) || (KOMUT == REGx_SLAVE_ADRESS)) if (UNLOCK) goto passed;
//    if ((ADRESS == MY_ADRESS) && (SECOND_ADRESS == MY_SECOND_ADRESS)) goto passed;
//    return;
//
//passed:
//    for (byte x = 0; x < TX_LEN; x++) TX[x] = 0x00;
//    if (REG_PARSE_COMPARE(READ_WRITE, ":") == 0) {
//        if ((REG_GET_FLAG(KOMUT) & RG_NV) & (UNLOCK == 0)) return;
//        if (REG_GET_FLAG(KOMUT) & RG_WR) {
//            if (KOMUT == REGx_RAND_CODE) {
//                if (DATA == 0x0000) {
//                    UNLOCK = 0;
//                    REG_SET_UNLOCK_START();
//                    REG_SET(KOMUT, 0);
//                    //task start
//                } else if ((DATA ^SECURE_CODE) == REG_GET(KOMUT)) {
//                    UNLOCK = 0xFF;
//                    REG_SET(KOMUT, DATA);
//                    REG_SET_UNLOCK_STOP();
//                } else {
//                    UNLOCK = 0;
//                    REG_SET(KOMUT, 0);
//                    REG_SET_UNLOCK_STOP();
//                }
//            } else REG_SET(KOMUT, DATA);
//            if (REG_GET_FLAG(KOMUT) & RG_FNC) REG_FUNC(KOMUT, ':');
//        } else return;
//    }
//    if (REG_PARSE_COMPARE(READ_WRITE, "?") == 0) {
//        if (REG_GET_FLAG(KOMUT) & RG_RD) {
//            if (KOMUT == REGx_RAND_CODE) {
//                if (REG_GET_UNLOCK()) {
//                    REG_CHANGE_RANDCODE();
//                    REG_SET(KOMUT, REG_GET_RANDCODE());
//                    REG_SET_UNLOCK_STOP();
//                } else return;
//            }
//            if (REG_GET_FLAG(KOMUT) & RG_FNC) REG_FUNC(KOMUT, '?');
//        } else return;
//    }
//    if (REG_GET_FLAG(KOMUT) & RG_NV) REG_EEPROM_SET(KOMUT);
//
//    REG_PROCESS_GET_DATA_STR(KOMUT, temp);
//    REG_CONVERT_DWORD_TO_STR_HEX(REG_GET(REGx_ADDR), ADRESS_S, 4);
//    REG_CONVERT_DWORD_TO_STR_HEX(REG_GET(REGx_SLAVE_ADRESS), SECOND_ADRESS_S, 2);
//    if (REG_GET_FLAG(KOMUT) & RG_MAIN) REG_TX_ADD(TX, "MAIN1");
//    REG_TX_ADD(TX, "<");
//
//    REG_TX_ADD(TX, SYMBOL_S);
//    REG_TX_ADD(TX, "R");
//    REG_TX_ADD(TX, ADRESS_S);
//    REG_TX_ADD(TX, SECOND_ADRESS_S);
//    REG_TX_ADD(TX, KOMUT_S);
//    REG_TX_ADD(TX, ":");
//    REG_TX_ADD(TX, temp);
//    REG_TX_ADD(TX, ">");
//
//    if (REG_GET_FLAG(KOMUT) & RG_EN); // UART_0_STRING(TX);
//}
//
//void INIT_REG()
//{
//    REG_CREATE(REGx_ADDR, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
//    REG_CREATE(REGx_RAND_CODE, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD, 0, 0xFFFF, 0);
//    REG_CREATE(REGx_SERI_NO, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
//    REG_CREATE(REGx_VERSION, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_RD, 0x10, 0xFFFF, 0);
//    REG_CREATE(REGx_SLAVE_ADRESS, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_2 | RG_WR | RG_RD | RG_NV, 0, 0xFF, 0);
//    REGISTER_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
//}
//
//// </editor-fold>