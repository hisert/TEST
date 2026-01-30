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
#include "lcd_16x2.h"
#include "ds1307.h"
#include "lc_512.h"
#include "hc595.h"

void REG_PROCESS(char *msg);
void INIT_REG();
word tempcounter = 0;
word counter = 0;
//// <editor-fold defaultstate="collapsed" desc="PIN DEFINE ISLEMLERI                                                           ">
//// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="VARIABLES      ">

typedef enum
  {
  THREAD_LED,
  THREAD_UART_1_RX,
  THREAD_UART_2_RX,
  THREAD_BUZZER,
  THREAD_RELAYS,
  THREAD_INPUTS,
  THREAD_ADC_OKUMA,
  THREAD_MENU_BUTON,
  THREAD_SERVICE_MODE,
  THREAD_MOTOR,
  THREAD_SELENOID_A,
  THREAD_SELENOID_B,
  THREAD_INDIKASYON_TEST,
  THREAD_DONE,
  } THREAD_LIST;

THREAD_t THREADS[THREAD_DONE];
char UART_2_MSG[20];
char UART_1_MSG[20];
word INPUT_VOLTAGE = 0;
word TORK_VALUE_1 = 0;
word TORK_VALUE_2 = 0;
word TORK_TOTAL = 0;
byte ADC_READ_READY = 0;
byte SELENOID_A_MAX_PWM = 80;
byte SELENOID_A_MIN_PWM = 40;
byte SELENOID_B_MAX_PWM = 80;
byte SELENOID_B_MIN_PWM = 40;
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM FUNCT   ">

void SYSTEM_CONTROL_ALL()
  {
  THREAD_ARRAY_CHECK(THREADS, ARRAY_SIZE(THREADS));
  }

byte WAIT_WHILE()
  {
  SYSTEM_CONTROL_ALL();
  return 1;
  }

void WAIT_INTERRUPT(word ms)
  {
  static TIME_OUT_t time_out;
  TIME_OUT_RESET(&time_out);
  while (WAIT_WHILE()) if (TIME_OUT_CHECK(&time_out, ms)) break;
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="EEPROM FUNCT   ">

typedef enum
  {
  MAGIC_BYTES,
  TIME_SEL,
  PROG_SEL,
  MAGNET_SEL,
  INDIKASYON_SEL,
  INDIKASYON_TYPE,
  INPUT_FREE,
  RELAY_SEL,
  EMG_SEL,
  FOTOSEL_SEL,
  ARM_DROP_MODE,
  MOTOR_CONTROL_SEL,
  RANDOM_SEL,
  EXT_RELAY_MODE,
  MOTOR_SPEED,
  MOTOR_TORQUE,
  TIME_OUT,
  INPUT_BUFFER,
  ID_NUM_SELECT,
  RANDOM_A,
  RANDOM_B,
  RELAY_TIME,
  COUNTER_A,
  COUNTER_B,
  FIX_COUNTER_A,
  FIX_COUNTER_B,
  MOTOR_BREAK_SPEED,
  SETTINGS_DONE,
  } SETTINGS;

word SETTING_VALUES[SETTINGS_DONE];

void CONFIG_RAM_SET(byte index, word data)
  {
  SETTING_VALUES[index] = data;
  }

word CONFIG_RAM_GET(byte index)
  {
  return SETTING_VALUES[index];
  }

void CONFIG_SET_RAM_AND_EEPROM(byte index, word data)
  {
  CONFIG_RAM_SET(index, data);
  EEPROM_SET(index, data);
  }

void EEPROM_DEFAULT_SET()
  {
  CONFIG_RAM_SET(TIME_SEL, 0);
  CONFIG_RAM_SET(PROG_SEL, 0);
  CONFIG_RAM_SET(MAGNET_SEL, 0);
  CONFIG_RAM_SET(INDIKASYON_SEL, 0);
  CONFIG_RAM_SET(INDIKASYON_TYPE, 0);
  CONFIG_RAM_SET(INPUT_FREE, 0);
  CONFIG_RAM_SET(RELAY_SEL, 0);
  CONFIG_RAM_SET(EMG_SEL, 0);
  CONFIG_RAM_SET(FOTOSEL_SEL, 0);
  CONFIG_RAM_SET(ARM_DROP_MODE, 0);
  CONFIG_RAM_SET(MOTOR_CONTROL_SEL, 0);
  CONFIG_RAM_SET(RANDOM_SEL, 0);
  CONFIG_RAM_SET(EXT_RELAY_MODE, 1);
  CONFIG_RAM_SET(MOTOR_SPEED, 50);
  CONFIG_RAM_SET(MOTOR_TORQUE, 350);
  CONFIG_RAM_SET(TIME_OUT, 0);
  CONFIG_RAM_SET(EXT_RELAY_MODE, 1);
  CONFIG_RAM_SET(INPUT_BUFFER, 1);
  CONFIG_RAM_SET(ID_NUM_SELECT, 1);
  CONFIG_RAM_SET(RANDOM_A, 5);
  CONFIG_RAM_SET(RANDOM_B, 5);
  CONFIG_RAM_SET(COUNTER_A, 15);
  CONFIG_RAM_SET(COUNTER_B, 12);
  CONFIG_RAM_SET(FIX_COUNTER_A, 10);
  CONFIG_RAM_SET(FIX_COUNTER_B, 10);
  CONFIG_RAM_SET(MOTOR_BREAK_SPEED, 90);
  }

void EEPROM_START()
  {
  EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
  EEPROM_DEFAULT_SET();
  for (byte x = 0; x < SETTINGS_DONE; x++)
    {
    word temp = EEPROM_GET(x);
    if (temp != 0xFFFF) CONFIG_RAM_SET(x, temp);
    }
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MAIN FUNCT     ">
//// <editor-fold defaultstate="collapsed" desc="ROLE FONKSIYONLARI                                                             ">

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
#define ROLE_CIKIS_MODE_NORMALLY_OPEN 0
#define ROLE_CIKIS_MODE_NORMALLY_CLOSE 1
#define  ROLE_CIKIS_AB_DISABLE  PIN_SET_LAT('C',4, 'L')
#define  ROLE_CIKIS_BA_DISABLE PIN_SET_LAT('C', 3, 'L')
#define  ROLE_CIKIS_ALARM_DISABLE PIN_SET_LAT('C', 2, 'L')
#define  ROLE_CIKIS_AB_ENABLE PIN_SET_LAT('C', 4, 'H')
#define  ROLE_CIKIS_BA_ENABLE PIN_SET_LAT('C', 3, 'H')
#define  ROLE_CIKIS_ALARM_ENABLE PIN_SET_LAT('C', 2, 'H')
#define  ROLE_CIKIS_BUSY_DISABLE PIN_SET_LAT('A', 3, 'L')
#define  ROLE_CIKIS_BUSY_ENABLE PIN_SET_LAT('A', 3, 'H')

void ROLE_MODE_SELECT(byte index, byte mode)
  {
  ROLE_CIKIS_MODE[index] = mode;
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN)
    {
    if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
    else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
    else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
    else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
    }
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE)
    {
    if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
    else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
    else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
    else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
    }
  } //ROLENIN NORMALLY OPEN NORMALLY CLOSE OLACAGINI BELIRLEYEN FONKSIYON.

void ROLE_GO_OUTPUT(byte index, byte time)
  {
  ROLE_CIKIS_STATE[index] = 1;
  ROLE_CIKIS_TIME[index] = (time * 100);
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN)
    {
    if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
    else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
    else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
    else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
    }
  if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE)
    {
    if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
    else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
    else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
    else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
    }
  } //ROLEYI CEKME ISLEMINI BASLATAN FONKSIYON.ARKA PLANDA KENDI KENDINE ISLEM TAMAMLANIR.

void RELAY_KONTROL_FUNCT()
  {
  for (byte x = 0; x < ROLE_CIKIS_DONE; x++)
    {
    if (ROLE_CIKIS_STATE[x] == 0) continue;
    else
      {
      if (ROLE_CIKIS_TIME[x]) ROLE_CIKIS_TIME[x] = ROLE_CIKIS_TIME[x] - 1;
      else
        {
        if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_OPEN)
          {
          if (x == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
          else if (x == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
          else if (x == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
          else if (x == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
          }
        if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_CLOSE)
          {
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
  ROLE_MODE_SELECT(ROLE_CIKIS_AB, ROLE_CIKIS_MODE_NORMALLY_OPEN);
  ROLE_MODE_SELECT(ROLE_CIKIS_BA, ROLE_CIKIS_MODE_NORMALLY_OPEN);
  ROLE_MODE_SELECT(ROLE_CIKIS_ALARM, ROLE_CIKIS_MODE_NORMALLY_OPEN);
  ROLE_MODE_SELECT(ROLE_CIKIS_BUSY, ROLE_CIKIS_MODE_NORMALLY_OPEN);
  ROLE_GO_OUTPUT(ROLE_CIKIS_AB, 1);
  ROLE_GO_OUTPUT(ROLE_CIKIS_BA, 2);
  ROLE_GO_OUTPUT(ROLE_CIKIS_ALARM, 3);
  ROLE_GO_OUTPUT(ROLE_CIKIS_BUSY, 4);
  } //ROLE NO NC EPROOMDAKI KAYITLI DURUMA GORE SETLENIYOR.
//// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MENU ">
// <editor-fold defaultstate="collapsed" desc="SWITCH AYARLARI">

word MENU_FUNCT_TIME_SEL(byte komut, word data)
  {
  static const char *temp[] = {"6 Sn", "12 Sn", "18 Sn", "Infinite"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(TIME_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(TIME_SEL);
    }
  }

word MENU_FUNCT_PROG_SEL(byte komut, word data)
  {
  static const char *temp[] = {"A - B Locked", "B -- A Single", "B << A Free", "A << B Free"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(PROG_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(PROG_SEL);
    }
  }

word MENU_FUNCT_MAGNET_SEL(byte komut, word data)
  {
  static const char *temp[] = {"A:Norm. B:Norm.", "A:Revrs B:Norm.", "A:Norm. B:Revrs", "A:Revrs B:Revrs"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(MAGNET_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(MAGNET_SEL);
    }
  }

word MENU_FUNCT_INDIKASYON_SEL(byte komut, word data)
  {
  static const char *temp[] = {"On", "Off"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(INDIKASYON_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(INDIKASYON_SEL);
    }
  }

word MENU_FUNCT_INDIKASYON_TYPE(byte komut, word data)
  {
  static const char *temp[] = {"Standart", "Double Type"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(INDIKASYON_TYPE, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(INDIKASYON_TYPE);
    }
  }

word MENU_FUNCT_INPUT_FREE(byte komut, word data)
  {
  static const char *temp[] = {"On", "Off"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(INPUT_FREE, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(INPUT_FREE);
    }
  }

word MENU_FUNCT_RELAY_SEL(byte komut, word data)
  {
  static const char *temp[] = {"A: N-O B: N-O", "A: N-O B: N-C", "A: N-C B: N-O", "A: N-C B: N-C"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(RELAY_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(RELAY_SEL);
    }
  }

word MENU_FUNCT_EMG_SELECT(byte komut, word data)
  {
  static const char *temp[] = {"N-O", "N-C"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(EMG_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(EMG_SEL);
    }
  }

word MENU_FUNCT_FOTOSEL_ALARM(byte komut, word data)
  {
  static const char *temp[] = {"F1 & F2", "Not Used", "F1 or F2", "System Passive"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(FOTOSEL_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(FOTOSEL_SEL);
    }
  }

word MENU_FUNCT_ARM_DROP_MODE(byte komut, word data)
  {
  static const char *temp[] = {"Disable", "Just Emg", "Just Power Fail", "Power Fail & Emg"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(ARM_DROP_MODE, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(ARM_DROP_MODE);
    }
  }

word MENU_FUNCT_MOTOR_CONTROL(byte komut, word data)
  {
  static const char *temp[] = {"Active", "Passive"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(MOTOR_CONTROL_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(MOTOR_CONTROL_SEL);
    }
  }

word MENU_FUNCT_RANDOM_CONTROL(byte komut, word data)
  {
  static const char *temp[] = {"A: Off B: Off", "A: Off B: On", "A: On B: Off", "A: On B: On"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(RANDOM_SEL, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(RANDOM_SEL);
    }
  }

word MENU_FUNCT_EXT_RELAY_MODE(byte komut, word data)
  {
  static const char *temp[] = {"F1 & F2", "All Alarms", "Only Busy Out", "All Alarms"};
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(EXT_RELAY_MODE, data);
    return 0;
    }
  else
    {
    MENU_SELECT_LIST_SET(temp);
    return CONFIG_RAM_GET(EXT_RELAY_MODE);
    }
  }
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DIGITAL AYARLAR FUNCT">

word MENU_FUNCT_MOTOR_SPEED(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("%");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(MOTOR_SPEED, data);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(MOTOR_SPEED);
    }
  }

word MENU_FUNCT_MOTOR_TORQUE(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("%");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(MOTOR_TORQUE, data);
    MOTOR_TORK_SET(CONFIG_RAM_GET(MOTOR_TORQUE));
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(MOTOR_TORQUE);
    }
  }

word MENU_FUNCT_TIME_OUT(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("Sec.");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(TIME_OUT, data);
    }
  else
    {
    return CONFIG_RAM_GET(TIME_OUT);
    }
  }

word MENU_FUNCT_INPUT_BUFFER(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("Per.");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(INPUT_BUFFER, data);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(INPUT_BUFFER);
    }
  }

word MENU_FUNCT_ID_NUM_SELECT(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(ID_NUM_SELECT, data);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(ID_NUM_SELECT);
    }
  }

word MENU_FUNCT_RANDOM_A(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("Per.");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(RANDOM_A, data);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(RANDOM_A);
    }
  }

word MENU_FUNCT_RANDOM_B(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("Per.");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(RANDOM_B, data);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(RANDOM_B);
    }
  }

word MENU_FUNCT_RELAY_TIME(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("1/10s");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(RELAY_TIME, data);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(RELAY_TIME);
    }
  }

word MENU_FUNCT_COUNTER_A(byte komut, word data)
  {
  MENU_SHOW_DATA_TEXT_SET("PUSH OK FOR CLEAR");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(COUNTER_A, 0);
    MENU_PRINT_MSG("COUNTER A CLEARED");
    WAIT_INTERRUPT(1000);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(COUNTER_A);
    }
  }

word MENU_FUNCT_COUNTER_B(byte komut, word data)
  {
  MENU_SHOW_DATA_TEXT_SET("PUSH OK FOR CLEAR");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(COUNTER_B, 0);
    MENU_PRINT_MSG("COUNTER B CLEARED");
    WAIT_INTERRUPT(1000);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(COUNTER_B);
    }
  }

word MENU_FUNCT_FIX_COUNTER_A(byte komut, word data)
  {
  MENU_SHOW_DATA_TEXT_SET("Not resettable");
  if (komut)
    {
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(FIX_COUNTER_A);
    }
  }

word MENU_FUNCT_FIX_COUNTER_B(byte komut, word data)
  {
  MENU_SHOW_DATA_TEXT_SET("Not resettable");
  if (komut)
    {
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(FIX_COUNTER_B);
    }
  }

word MENU_FUNCT_MAS12_STATUS(byte komut, word data)
  {
  if (komut)
    {
    return 0;
    }
  else
    {
    char msg1[30];
    char msg2[30];
    WAIT_INTERRUPT(100);
    MENU_FUNCT_CLEAR();
    sprintf(msg1, "Pos : %d", MAS12_READ_HAL_DATA());
    MENU_TEXT_ORTALA(msg1, msg2, 21);
    MENU_FUNCT_WRITE_TEXT(0, 8, msg2);
    sprintf(msg1, "Mag Field : %d", MAS12_READ_MAG_DATA());
    MENU_TEXT_ORTALA(msg1, msg2, 21);
    MENU_FUNCT_WRITE_TEXT(0, 20, msg2);
    MENU_FUNCT_UPDATE();
    MENU_BUTON_ADD('R');
    return 0;
    }
  }

word MENU_FUNCT_MOTOR_BREAK_SPEED(byte komut, word data)
  {
  MENU_VAL_YAN_YAZI_SET("Val");
  if (komut)
    {
    CONFIG_SET_RAM_AND_EEPROM(MOTOR_BREAK_SPEED, data);
    return 0;
    }
  else
    {
    return CONFIG_RAM_GET(MOTOR_BREAK_SPEED);
    }
  }

word MENU_FUNCT_DIAGNOSTIC(byte komut, word data)
  {
  MENU_SHOW_DATA_TEXT_SET("System Diagnostic");
  if (komut)
    {
    return 0;
    }
  else
    {
    return 0;
    }
  }

word MENU_FUNCT_INPUT_VOLTAGE(byte komut, word data)
  {
  if (komut)
    {
    return 0;
    }
  else
    {
    char msg1[30];
    char msg2[30];
    WAIT_INTERRUPT(100);
    MENU_FUNCT_CLEAR();
    sprintf(msg1, "Voltage : %d", INPUT_VOLTAGE);
    MENU_TEXT_ORTALA(msg1, msg2, 21);
    MENU_FUNCT_WRITE_TEXT(0, 8, msg2);
    sprintf(msg1, "Torque : %d", TORK_TOTAL);
    MENU_TEXT_ORTALA(msg1, msg2, 21);
    MENU_FUNCT_WRITE_TEXT(0, 20, msg2);
    MENU_FUNCT_UPDATE();
    MENU_BUTON_ADD('R');
    return 0;
    }
  }
// </editor-fold>
Menu_One USER_SETTINGS_MENU[] = {
  {.text = "Time Select", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_TIME_SEL, .max = 3},
  {.text = "Program Select", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_PROG_SEL, .max = 3},
  {.text = "Input Free", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_INPUT_FREE, .max = 1},
  {.text = "Relay Select", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_SEL, .max = 3},
  {.text = "Emg Select", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_EMG_SELECT, .max = 1},
  {.text = "Fotosel Alarm", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_FOTOSEL_ALARM, .max = 3},
  {.text = "Drop Arm Mode", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_ARM_DROP_MODE, .max = 3},
  };
Menu_One SYSTEM_SETTINGS_MENU[] = {
  {.text = "Magnet Select", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_MAGNET_SEL, .max = 3},
  {.text = "Indikasyon Select", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_INDIKASYON_SEL, .max = 1},
  {.text = "Indikasyon Type", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_INDIKASYON_TYPE, .max = 1},
  {.text = "Motor Control Mode", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_MOTOR_CONTROL, .max = 1},
  {.text = "Random Control Mode", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RANDOM_CONTROL, .max = 3},
  {.text = "Ext Relay Mode", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_EXT_RELAY_MODE, .max = 3},
  };
Menu_One ANA_MENU[] = {
  {.text = "User Settings", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) USER_SETTINGS_MENU},
  {.text = "System Settings", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) SYSTEM_SETTINGS_MENU},
  {.text = "Motor Speed", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_MOTOR_SPEED, .max = 100, .min = 0},
  {.text = "Motor Torque", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_MOTOR_TORQUE, .max = 350, .min = 250},
  {.text = "Input Buffer", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_INPUT_BUFFER, .max = 20, .min = 1},
  {.text = "ID Num Select", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_ID_NUM_SELECT, .max = 99, .min = 1},
  {.text = "Random Sorter A", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RANDOM_A, .max = 99, .min = 1},
  {.text = "Relay Time", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_TIME, .max = 30, .min = 5},
  {.text = "Counter A", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_A, .max = 0, .min = 0},
  {.text = "Counter B", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_B, .max = 0, .min = 0},
  {.text = "Fix Counter A", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_FIX_COUNTER_A, .max = 0, .min = 0},
  {.text = "Fix Counter B", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_FIX_COUNTER_B, .max = 0, .min = 0},
  {.text = "MAS12 Status", .flag = MENU_FLAG_REFRESH_DATA, .Funct = MENU_FUNCT_MAS12_STATUS, .max = 0, .min = 0},
  {.text = "Motor Break Speed", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_MOTOR_BREAK_SPEED, .max = 100, .min = 50},
  {.text = "System Diagnostic", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_DIAGNOSTIC, .max = 0, .min = 0},
  {.text = "Input Voltage", .flag = MENU_FLAG_REFRESH_DATA, .Funct = MENU_FUNCT_INPUT_VOLTAGE, .max = 0, .min = 0},
  };

void MENU_UST_DATA_GETIR()
  {
  static const char *ANA_MENU_UST_YAZI = ">> MAIN MENU <<";
  static const char *USER_MENU_UST_YAZI = ">> USER SETTINGS <<";
  static const char *SYSTEM_MENU_UST_YAZI = ">> SYSTEM SETTINGS <<";

  if (MENU_POINTER_GET() == ANA_MENU) MENU_MAX_SET(sizeof (ANA_MENU) / sizeof (ANA_MENU[0]) - 1);
  if (MENU_POINTER_GET() == USER_SETTINGS_MENU) MENU_MAX_SET(sizeof (USER_SETTINGS_MENU) / sizeof (USER_SETTINGS_MENU[0]) - 1);
  if (MENU_POINTER_GET() == SYSTEM_SETTINGS_MENU) MENU_MAX_SET(sizeof (SYSTEM_SETTINGS_MENU) / sizeof (SYSTEM_SETTINGS_MENU[0]) - 1);

  if (MENU_POINTER_GET() == ANA_MENU) MENU_UST_YAZI_SET(ANA_MENU_UST_YAZI);
  if (MENU_POINTER_GET() == USER_SETTINGS_MENU) MENU_UST_YAZI_SET(USER_MENU_UST_YAZI);
  if (MENU_POINTER_GET() == SYSTEM_SETTINGS_MENU) MENU_UST_YAZI_SET(SYSTEM_MENU_UST_YAZI);
  }

byte BUTON_WORKS()
  {
  static Buton_t BUTON_OK;
  static Buton_t BUTON_UP;
  static Buton_t BUTON_DOWN;
  byte temp;
  byte buton_used = 0;
  static TIME_OUT_t time_out;
  if (TIME_OUT_CHECK(&time_out, 1))
    {
    temp = (BUTON_PROCESS(&BUTON_OK, PIN_GET_PORT('F', 0), 10, 0));
    if (temp)
      {
      if (temp == BUTON_PRESSING)
        {
        if (BUTON_GET_TIME(&BUTON_OK) == 350)
          {
          MENU_BUTON_ADD('O');
          buton_used = 1;
          }
        }
      if (temp == BUTON_PRESSED)
        {
        if (BUTON_GET_TIME(&BUTON_OK) < 350)
          {
          MENU_BUTON_ADD('B');
          buton_used = 1;
          }
        }
      }

    temp = (BUTON_PROCESS(&BUTON_UP, PIN_GET_PORT('E', 5), 10, 0));
    if (temp)
      {
      if (temp == BUTON_PRESSING)
        {
        if (BUTON_GET_TIME(&BUTON_UP) > 350)
          {
          MENU_BUTON_ADD('U');
          buton_used = 1;
          }
        }
      if (temp == BUTON_PRESSED)
        {
        if (BUTON_GET_TIME(&BUTON_UP) < 350)
          {
          MENU_BUTON_ADD('U');
          buton_used = 1;
          }
        }
      }
    temp = (BUTON_PROCESS(&BUTON_DOWN, PIN_GET_PORT('E', 2), 10, 0));
    if (temp)
      {
      if (temp == BUTON_PRESSING)
        {
        if (BUTON_GET_TIME(&BUTON_DOWN) > 350)
          {
          MENU_BUTON_ADD('D');
          buton_used = 1;
          }
        }
      if (temp == BUTON_PRESSED)
        {
        if (BUTON_GET_TIME(&BUTON_DOWN) < 350)
          {
          MENU_BUTON_ADD('D');
          buton_used = 1;
          }
        }
      }
    }
  return buton_used;
  }

byte BUTON_SERVICE_MODE(word LongTime, word shortTime)
  {
  static Buton_t BUTON_OK;
  static Buton_t BUTON_UP;
  static Buton_t BUTON_DOWN;
  byte temp;
  static TIME_OUT_t time_out;
  if (TIME_OUT_CHECK(&time_out, 1))
    {
    temp = (BUTON_PROCESS(&BUTON_OK, PIN_GET_PORT('F', 0), 10, 0));
    if (temp)
      {
      if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&BUTON_OK) == LongTime) return 'O';
      // if (temp == BUTON_PRESSED) if (BUTON_GET_TIME(&BUTON_OK) < 350) return 'B';
      }

    temp = (BUTON_PROCESS(&BUTON_UP, PIN_GET_PORT('E', 5), 10, 0));
    if (temp)
      {
      if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&BUTON_UP) == shortTime) return 'U';
      }
    temp = (BUTON_PROCESS(&BUTON_DOWN, PIN_GET_PORT('E', 2), 10, 0));
    if (temp)
      {
      if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&BUTON_DOWN) == shortTime) return 'D';
      }
    }
  return 0;
  }
// </editor-fold>

byte OZAK_PROTOCOL(const char* msg)
  {
  byte id_arrived = ((msg[0] - '0')*10) + ((msg[1] - '0')*1);
  byte my_id = 1;
  byte data = 0;
  byte parametre_error = 0;
  byte ayarlandi_donusu_var = 1;
  char TX_BUFFER[25];
  byte TX_BUFFER_COUNTER = 0;
  if (id_arrived == 0);
  else if (id_arrived == my_id);
  else return 0;
  TX_BUFFER[TX_BUFFER_COUNTER++] = '(';
  sprintf(TX_BUFFER + TX_BUFFER_COUNTER, "%.2d", my_id);
  TX_BUFFER_COUNTER = TX_BUFFER_COUNTER + 2;
  TX_BUFFER[TX_BUFFER_COUNTER++] = msg[2];
  TX_BUFFER[TX_BUFFER_COUNTER++] = msg[3];
  TX_BUFFER[TX_BUFFER_COUNTER++] = msg[4];
  if ((msg[2] == 'I') && (msg[3] == 'D') && (msg[4] == 'N'))//---------------IDN
    {
    data = ((msg[5] - '0')*10) + ((msg[6] - '0')*1);
    }
  else if ((msg[2] == 'G') && (msg[3] == 'O') && (msg[4] == 'N'))//----------GON
    {
    data = msg[5];
    if (data == '0'); //A YONU INPUT
    else if (data == '1'); //B YONU INPUT
    else parametre_error = 1;
    }
  else if ((msg[2] == 'P') && (msg[3] == 'M') && (msg[4] == 'S'))//----------PMS
    {
    data = msg[6];
    if (msg[5] == 'A')
      {
      if (data == '0'); //KONTROL ANA KARTTA DIP SWITCH ILE
      else if (data == '1'); //A B KONTROLLU
      else if (data == '2'); //CIFT YON SERBEST
      else if (data == '3'); //B KONTROLLU
      else if (data == '4'); //A KONTROLLU
      }
    else if (msg[5] == 'O')
      {
      ayarlandi_donusu_var = 0;
      }
    else parametre_error = 1;
    }
  else if ((msg[2] == 'E') && (msg[3] == 'M') && (msg[4] == 'G'))//----------EMG
    {
    data = msg[5];
    if (data == '0'); //EMG DURUMU KAPALI
    else if (data == '1'); //EMG DURUMU ACIK
    else parametre_error = 1;
    }
  else if ((msg[2] == 'T') && (msg[3] == 'O') && (msg[4] == 'A'))//----------TOA
    {
    data = msg[6];
    if (msg[5] == 'A')
      {
      if (data == '0'); //KONTROL ANA KARTTA
      else if (data == '1'); //6 SANIYE BEKLE
      else if (data == '2'); //12 SANIYE BEKLE
      else if (data == '3'); //18 SANIYE BEKLE
      else if (data == '4'); //SONSUZ BEKLE
      }
    else if (msg[5] == 'O')
      {
      ayarlandi_donusu_var = 0;
      }
    else parametre_error = 1;
    }
  else if ((msg[2] == 'T') && (msg[3] == 'E') && (msg[4] == 'N'))//----------TEN
    {
    data = msg[6];
    if (msg[5] == 'A')
      {
      if (data == 'E'); //A YONU ENABLE
      else if (data == 'D'); //A YONU DISABLE
      }
    else if (msg[5] == 'B')
      {
      if (data == 'E'); //B YONU ENABLE
      else if (data == 'D'); //B YONU DISABLE
      }
    else if (msg[5] == 'O')
      {
      if (data == 'E'); //KONTROL ANA KARTTA
      else if (data == 'D'); //KONTROL YAZILIMDA
      }
    else parametre_error = 1;
    }
  else if ((msg[2] == 'C') && (msg[3] == 'N') && (msg[4] == 'T'))//----------CNT
    {
    data = msg[6];
    if (msg[5] == 'C')
      {
      if (data == 'A'); //A YONU GECIS BILGISI SIL
      else if (data == 'B'); //B YONU GECIS BILGISI SIL
      else if (data == 0); //A VE B YONU GECIS BILGISI SIL
      else parametre_error = 1;
      }
    else if (msg[5] == 'O')
      {
      ayarlandi_donusu_var = 0;
      if (data == 'A'); //A YONU GECIS BILGISI OGREN
      else if (data == 'B'); //B YONU GECIS BILGISI OGREN
      else if (data == 0); //A VE B YONU GECIS BILGISI OGREN
      else parametre_error = 1;
      }
    else parametre_error = 1;
    }
    //--------------------------------------------------------------------------
  else parametre_error = 1;
  //----------------------------------------------------------------------------
  if (parametre_error) TX_BUFFER[TX_BUFFER_COUNTER++] = '1';
  else if (ayarlandi_donusu_var) TX_BUFFER[TX_BUFFER_COUNTER++] = '0';
  TX_BUFFER[TX_BUFFER_COUNTER++] = ')';
  TX_BUFFER[TX_BUFFER_COUNTER++] = 0x00;
  UART_2_STRING(TX_BUFFER);
  }
#define SELENOID_A_CEK 0x01
#define SELENOID_A_BIRAK 0x02
#define SELENOID_B_CEK 0x04
#define SELENOID_B_BIRAK 0x08

void SELENOID_FUNCT(byte flag)
  {
  if (flag & SELENOID_A_CEK) THREAD_START(&THREADS[THREAD_SELENOID_A]);
  if (flag & SELENOID_B_CEK) THREAD_START(&THREADS[THREAD_SELENOID_B]);
  if (flag & SELENOID_A_BIRAK)
    {
    THREAD_STOP(&THREADS[THREAD_SELENOID_A]);
    PWM_1A_DUTY(0);
    }
  if (flag & SELENOID_B_BIRAK)
    {
    THREAD_STOP(&THREADS[THREAD_SELENOID_B]);
    PWM_1B_DUTY(0);
    }
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PROJE FUNCT    ">

void RS485_SEND(char *msg)
  {

  // PIN_SET_LAT('E', 5, 'H');
  //UART_2_STRING(msg);
  // PIN_SET_LAT('E', 5, 'L');
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DIGITAL BUZZER ">

typedef struct
  {
  byte State;
  word Time;
  } Tone_t;
Tone_t MENU_BUTON_PRESSED_TONE[] = {
  {.State = 1, .Time = 10},
  {.State = 0, .Time = 10},
  {.State = 1, .Time = 10},
  {.State = 0, .Time = 0},
  };
Tone_t TONE_START[] = {
  {.State = 1, .Time = 80},
  {.State = 0, .Time = 50},
  {.State = 1, .Time = 80},
  {.State = 0, .Time = 50},
  {.State = 1, .Time = 80},
  {.State = 0, .Time = 50},
  {.State = 1, .Time = 80},
  {.State = 0, .Time = 50},
  {.State = 0, .Time = 0},
  };
Tone_t TONE_MOTOR_SUCCESS[] = {
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 1, .Time = 20},
  {.State = 0, .Time = 20},
  {.State = 0, .Time = 0},
  };
Tone_t TONE_MOTOR_TORK[] = {
  {.State = 1, .Time = 1000},
  {.State = 0, .Time = 100},
  {.State = 1, .Time = 100},
  {.State = 0, .Time = 100},
  {.State = 0, .Time = 0},
  };
Tone_t TONE_MOTOR_TIME_OUT[] = {
  {.State = 1, .Time = 1000},
  {.State = 0, .Time = 100},
  {.State = 1, .Time = 100},
  {.State = 0, .Time = 100},
  {.State = 1, .Time = 100},
  {.State = 0, .Time = 100},
  {.State = 0, .Time = 0},
  };
Tone_t *PLAY_TONE = 0;
byte BUZZER_PLAYING = 0;

void DIGITAL_BUZZER_PLAY(Tone_t * tone)
  {

  PLAY_TONE = tone;
  BUZZER_PLAYING = 1;
  }

void DIGITAL_BUZZER_PROCESS()
  {
  static TIME_OUT_t time_out;
  static byte temp_flag = 0;
  if (BUZZER_PLAYING)
    {
    if (temp_flag == 0)
      {
      temp_flag = 1;
      TIME_OUT_RESET(&time_out);
      if ((PLAY_TONE->State) == 1)PIN_SET_LAT('A', 2, 'H');
      else PIN_SET_LAT('A', 2, 'L');
      }
    if (TIME_OUT_CHECK(&time_out, PLAY_TONE->Time))
      {
      temp_flag = 0;
      PLAY_TONE++;
      if (((PLAY_TONE->State) == 0) && ((PLAY_TONE->Time) == 0))
        {

        PIN_SET_LAT('A', 2, 'L');
        BUZZER_PLAYING = 0;
        }
      }
    }
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT   ">

byte THREAD_UART_1_RX_FUNCT()
  {
  // REG_PROCESS(UART_1_MSG);
  // RS485_SEND(UART_1_MSG);
  return THREAD_RETURN_STOP;
  }

byte THREAD_UART_2_RX_FUNCT()
  {
  OZAK_PROTOCOL(UART_2_MSG);
  if (strcmp(UART_2_MSG, "YON_A") == 0) MOTOR_START(1047);
  if (strcmp(UART_2_MSG, "YON_B") == 0) MOTOR_START(3047);
  return THREAD_RETURN_STOP;
  }

byte THREAD_LED_FUNCT()
  {
  static SIRALI_TIME_OUT_t timer;
  SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_CLEAN);
  if (SYSTEM_FUNCT(&timer, 900, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('B', 7, 'H');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK))
    {
    if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST)
      {
      PIN_SET_LAT('B', 7, 'L');
      counter = tempcounter;
      tempcounter = 0;
      SSH1306_OLED_ClearDisplay();
      SSH1306_OLED_Write_Dec(0, 0, counter);
      SSH1306_OLED_Update();
      }
    }
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_BUZZER_FUNCT()
  {
  DIGITAL_BUZZER_PROCESS();
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_RELAYS_FUNCT()
  {
  RELAY_KONTROL_FUNCT();
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_INPUTS_FUNCT()
  {
  byte temp = 0;
  word DEBOUNCE_TIME = 100;
  //----------------------------------------------------------------------------
  static Input_t INPUT_A = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_A, PIN_GET_PORT('D', 5), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("INPUT A PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("INPUT A RELEASE\r\n");
    if (temp == INPUT_FALL_EDGE) MOTOR_START(1047);
    }
  //----------------------------------------------------------------------------
  static Input_t INPUT_B = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_B, PIN_GET_PORT('D', 6), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("INPUT B PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("INPUT B RELEASE\r\n");
    if (temp == INPUT_FALL_EDGE) MOTOR_START(3047);
    }
  //----------------------------------------------------------------------------
  static Input_t INPUT_EMG = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_EMG, PIN_GET_PORT('G', 0), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("INPUT EMG PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("INPUT EMG RELEASE\r\n");
    }
  //----------------------------------------------------------------------------
  static Input_t INPUT_RES = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_RES, PIN_GET_PORT('G', 1), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("INPUT RES PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("INPUT RES RELEASE\r\n");
    }
  //----------------------------------------------------------------------------
  static Input_t INPUT_INHIBIT_A = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_INHIBIT_A, PIN_GET_PORT('C', 0), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("INHIBIT A PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("INHIBIT A RELEASE\r\n");
    }
  //----------------------------------------------------------------------------
  static Input_t INPUT_INHIBIT_B = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_INHIBIT_B, PIN_GET_PORT('C', 1), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("INHIBIT B PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("INHIBIT B RELEASE\r\n");
    }
  //----------------------------------------------------------------------------
  static Input_t INPUT_EXT_1 = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_EXT_1, PIN_GET_PORT('E', 6), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("EXT_1 PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("EXT_1 RELEASE\r\n");
    }
  //----------------------------------------------------------------------------
  static Input_t INPUT_EXT_2 = {.Old_state = 0xFF};
  temp = INPUT_DEBOUNCE(&INPUT_EXT_2, PIN_GET_PORT('E', 7), DEBOUNCE_TIME);
  if (temp)
    {
    if (temp == INPUT_FALL_EDGE) UART_2_STRING("EXT_2 PRESS\r\n");
    if (temp == INPUT_RAISE_EDGE) UART_2_STRING("EXT_2 RELEASE\r\n");
    }
  //----------------------------------------------------------------------------
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_ADC_OKUMA_FUNCT()
  {
  static byte counter = 0;
  if (ADC_INTERRUPT_is_FREE())
    {
    if (counter == 0)
      {
      ADC_INTERRUPT_READ(6);
      counter = 1;
      }
    else if (counter == 1)
      {
      ADC_INTERRUPT_READ(7);
      counter = 2;
      }
    else if (counter == 2)
      {
      ADC_INTERRUPT_READ(5);
      counter = 0;
      }
    }
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_MENU_BUTON_FUNCT()
  {
  if (BUTON_WORKS())DIGITAL_BUZZER_PLAY(MENU_BUTON_PRESSED_TONE);
  MENU_PROCESS();
  return THREAD_RETURN_CONTINUE;
  }

void SERVICE_MODE_VALUE(const char* ust_yazi, const char* orta_yazi, const char* alt_yazi)
  {
  char msg1[30];
  char msg2[30];
  MENU_FUNCT_CLEAR();
  sprintf(msg1, ust_yazi);
  MENU_TEXT_ORTALA(msg1, msg2, 21);
  MENU_FUNCT_WRITE_TEXT(0, 0, msg2);
  MENU_TEXT_ORTALA(orta_yazi, msg2, 21);
  MENU_FUNCT_WRITE_TEXT(0, 12, msg2);
  MENU_TEXT_ORTALA(alt_yazi, msg2, 21);
  MENU_FUNCT_WRITE_TEXT(0, 24, msg2);
  MENU_FUNCT_UPDATE();
  }

byte THREAD_SERVICE_MODE_FUNCT()
  {
  static byte counter = 0;
  static byte_menu_counter = 0;
  static byte menu_counter_max = 0;
  static byte selected_settings[5];
  char msg1[30];
  char msg2[30];
  if (counter == 0)
    {
    counter = 1;
    SERVICE_MODE_VALUE("<<  SERVICE MODE   >>", "[Push Enter Bt. for]", "2 sec for auto config]");
    byte_menu_counter = 0;
    }
  byte temp = BUTON_SERVICE_MODE(1000, 50);
  if (temp)
    {
    DIGITAL_BUZZER_PLAY(MENU_BUTON_PRESSED_TONE);
    if (temp == 'U') if (menu_counter_max > byte_menu_counter) byte_menu_counter++;
    if (temp == 'D') if (byte_menu_counter) byte_menu_counter--;
    if (counter == 1)
      {
      if (temp == 'O')
        {
        counter = 2;
        byte_menu_counter = 0;
        menu_counter_max = 3;
        }
      temp = 0;
      }
    if (counter == 2)
      {
      if (byte_menu_counter == 0) SERVICE_MODE_VALUE("SELECT MAG TYPE", "A:Norm B:Norm", "[2 sec for set]");
      if (byte_menu_counter == 1) SERVICE_MODE_VALUE("SELECT MAG TYPE", "A:Revrs B:Norm", "[2 sec for set]");
      if (byte_menu_counter == 2) SERVICE_MODE_VALUE("SELECT MAG TYPE", "A:Norm B:Revrs", "[2 sec for set]");
      if (byte_menu_counter == 3) SERVICE_MODE_VALUE("SELECT MAG TYPE", "A:Revrs B:Revrs", "[2 sec for set]");
      if (temp == 'O')
        {
        counter = 3;
        selected_settings[0] = byte_menu_counter;
        MENU_PRINT_MSG("SELECTED");
        THREAD_STOP(&THREADS[THREAD_SERVICE_MODE]);
        WAIT_INTERRUPT(500);
        THREAD_START(&THREADS[THREAD_SERVICE_MODE]);
        byte_menu_counter = 0;
        menu_counter_max = 1;
        }
      temp = 0;
      }
    if (counter == 3)
      {
      if (byte_menu_counter == 0) SERVICE_MODE_VALUE("SELECT MOTOR TYPE", "Active", "[2 sec for set]");
      if (byte_menu_counter == 1) SERVICE_MODE_VALUE("SELECT MOTOR TYPE", "Passive", "[2 sec for set]");
      if (temp == 'O')
        {
        counter = 4;
        selected_settings[1] = byte_menu_counter;
        MENU_PRINT_MSG("SELECTED");
        THREAD_STOP(&THREADS[THREAD_SERVICE_MODE]);
        WAIT_INTERRUPT(500);
        THREAD_START(&THREADS[THREAD_SERVICE_MODE]);
        byte_menu_counter = 0;
        menu_counter_max = 2;
        }
      temp = 0;
      }
    if (counter == 4)
      {
      if (byte_menu_counter == 0) SERVICE_MODE_VALUE("SELECT DROP MODE", "System Passive", "[2 sec for set]");
      if (byte_menu_counter == 1) SERVICE_MODE_VALUE("SELECT DROP MODE", "Only Emg.", "[2 sec for set]");
      if (byte_menu_counter == 2) SERVICE_MODE_VALUE("SELECT DROP MODE", "Pwr. Fail & Emg.", "[2 sec for set]");
      if (temp == 'O')
        {
        counter = 5;
        selected_settings[2] = byte_menu_counter;
        MENU_PRINT_MSG("SELECTED");
        THREAD_STOP(&THREADS[THREAD_SERVICE_MODE]);
        WAIT_INTERRUPT(500);
        THREAD_START(&THREADS[THREAD_SERVICE_MODE]);
        byte_menu_counter = 0;
        menu_counter_max = 1;
        }
      temp = 0;
      }
    if (counter == 5)
      {
      if (byte_menu_counter == 0) SERVICE_MODE_VALUE("POSITION SETTINGS", "P(1) P(2) P(3) P(4)", "");
      if (temp == 'O')
        {
        }
      temp = 0;
      }
    }
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_MOTOR_FUNCT()
  {
  static byte MOTOR_TORK_COUNTER = 0;
  static word STOP_INDEX = 2047;
  static word START_INDEX = 2047;
  static byte temp_oled = 1;
  static byte KOL_TOPLAMA_STARTED = 0;
  byte temp = MOTOR_PROCESS(TORK_TOTAL);
  byte temp_success = 1;
  byte temp_bekleme = 0;
  if (temp)
    {
    if (temp == MOTOR_MAS12_READ_ERROR)
      {
      MENU_PRINT_MSG_INFO("MAS12 ERROR");
      }
    if (temp == MOTOR_BASARILI_DURDU)
      {
      if (KOL_TOPLAMA_STARTED)
        {
        KOL_TOPLAMA_STARTED = 0;
        MOTOR_MODULE_INIT_2();
        }
      if (MOTOR_TORK_COUNTER)
        {
        if (MOTOR_STOP_INDEX_GET() == START_INDEX)
          {
          MOTOR_START(STOP_INDEX);
          temp_success = 0;
          temp_bekleme = 1;
          }
        }
      if (temp_success)
        {
        MENU_PRINT_MSG_INFO("SUCESS");
        MOTOR_TORK_COUNTER = 0;
        }
      }
    if (temp == MOTOR_WORKING)
      {
      if (temp_oled) MENU_PRINT_MSG_INFO("WORKING");
      temp_oled = 0;
      }
    else temp_oled = 1;
    if (temp == MOTOR_TIME_OUT_DURDU)
      {
      MENU_PRINT_MSG_INFO("TIME OUT");
      }
    if (temp == MOTOR_TORK_DURDU)
      {
      MENU_PRINT_MSG_INFO("TORQUE");
      if (MOTOR_TORK_COUNTER == 0)
        {
        STOP_INDEX = MOTOR_STOP_INDEX_GET();
        START_INDEX = MOTOR_START_INDEX_GET();
        }
      MOTOR_TORK_COUNTER++;
      if (MOTOR_TORK_COUNTER == 3)
        {
        MENU_PRINT_MSG_INFO("TORQUE RESET");
        MOTOR_TORK_COUNTER = 0;
        }
      else
        {
        temp_bekleme = 1;
        if (MOTOR_STOP_INDEX_GET() == STOP_INDEX) MOTOR_START(START_INDEX);
        else if (MOTOR_STOP_INDEX_GET() == START_INDEX) MOTOR_START(STOP_INDEX);
        }
      }
    if (temp == MOTOR_KOL_TOPLAMA)
      {
      if (MOTOR_STOP_INDEX_GET() == 2047)
        {
        MENU_PRINT_MSG_INFO("ARM BACK");
        KOL_TOPLAMA_STARTED = 1;
        MOTOR_TORK_SET(1000);
        MOTOR_TIME_OUT_SET(60000);
        MOTOR_START(2047);
        MOTOR_PID_INIT(0.75, 0.75);
        }
      }
    }
  if (temp_bekleme) WAIT_INTERRUPT(1000);
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_INDIKASYON_TEST_FUNCT()
  {
  static SIRALI_TIME_OUT_t timer;
  SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_CLEAN);
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'H');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'L');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'H');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'L');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'H');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'L');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'H');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'L');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'H');
  if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('G', 3, 'L');
  if (SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_WORK)) return THREAD_RETURN_STOP;
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_SELENOID_A_FUNCT()
  {
  static SIRALI_TIME_OUT_t timer;
  SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_CLEAN);
  if (SYSTEM_FUNCT(&timer, 1000, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PWM_1A_DUTY(SELENOID_A_MAX_PWM);
  if (SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PWM_1A_DUTY(SELENOID_A_MIN_PWM);
  if (SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_WORK))
    {
    if (SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_CLEAN));
    return THREAD_RETURN_STOP;
    }
  return THREAD_RETURN_CONTINUE;
  }

byte THREAD_SELENOID_B_FUNCT()
  {
  static SIRALI_TIME_OUT_t timer;
  SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_CLEAN);
  if (SYSTEM_FUNCT(&timer, 1000, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PWM_1B_DUTY(SELENOID_B_MAX_PWM);
  if (SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PWM_1B_DUTY(SELENOID_B_MIN_PWM);
  if (SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_WORK))
    {
    if (SYSTEM_FUNCT(&timer, 1, SYSTEM_FUNCT_KOMUT_CLEAN));
    return THREAD_RETURN_STOP;
    }
  return THREAD_RETURN_CONTINUE;
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="INTERRUPT FUNCT">


void UART_2_INTERRUPT_FUNCT(byte data)
  {
  static byte counter = 0;
  byte x = data;
  if (x == '(') counter = 0;
  else if (x == ')')
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
    UART_1_MSG[counter++] = x;
    UART_1_MSG[counter] = 0;
    THREAD_START(&THREADS[THREAD_UART_1_RX]);
    }

  if (counter < 20) UART_1_MSG[counter++] = x;
  }

void ADC_INTERRUPT_FUNCT(byte channel, word data)
  {
  if (channel == 5) INPUT_VOLTAGE = data;
  if (channel == 6) TORK_VALUE_1 = data;
  if (channel == 7)
    {
    TORK_VALUE_2 = data;
    TORK_TOTAL = (TORK_VALUE_1 + TORK_VALUE_2) / 2;
    }
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
  REGx_MAS_HAM, //6 0x06
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

  if (REG_GET_FLAG(KOMUT) & RG_EN) RS485_SEND(TX);
  }

void REG_FUNCT_MAS_HAM(byte regId, byte komut)
  {
  if (komut == '?');
  }

void INIT_REG()
  {
  REG_CREATE(REGx_ADDR, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
  REG_CREATE(REGx_RAND_CODE, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD, 0, 0xFFFF, 0);
  REG_CREATE(REGx_SERI_NO, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
  REG_CREATE(REGx_VERSION, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_RD, 0x01, 0xFFFF, 0);
  REG_CREATE(REGx_SLAVE_ADRESS, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_2 | RG_WR | RG_RD | RG_NV, 0, 0xFF, 0);

  REG_CREATE(REGx_MAS_HAM, REG_FUNCT_MAS_HAM, RG_EN | RG_IN_DEC | RG_OUT_DEC_4 | RG_RD | RG_FNC, 0, 0xFFFF, 0);
  REGISTER_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
  }

// </editor-fold>

void INTERNAL_MODULS_INIT()
  {
  EEPROM_START();
  TIMER_2_INTERRUPT_CONNECT(1, TIME_OUT_COUNT_INTERRUPT);
  UART_2_INTERRUPT_FUNCT_CONNECT(9600, UART_2_INTERRUPT_FUNCT);
  ADC_INTERRUPT_FUNCT_CONNECT(ADC_INTERRUPT_FUNCT);
  //  SOFT_I2C_INIT(&DDRD, &PORTD, &PIND, 1, &DDRD, &PORTD, &PIND, 0);
  I2C_1_INIT(400);
  ADC_INIT();
  ADC_INTERRUPT(1);
  PWM_3_INIT(SYSTEM_PWM_PRESCALE_0, SYSTEM_PWM_SLOW);
  PWM_3B_DUTY(0);
  PWM_3A_DUTY(0);
  PWM_3B_START();
  PWM_3A_START();

  PWM_1_INIT(SYSTEM_PWM_PRESCALE_0, SYSTEM_PWM_SLOW);
  PWM_1B_DUTY(0);
  PWM_1A_DUTY(0);
  PWM_1B_START();
  PWM_1A_START();
  }

void EXTERNAL_MODULS_INIT()
  {
  SSH1306_OLED_Init(&I2C_1_START, &I2C_1_WRITE, &I2C_1_STOP);
  MAS12_INIT(&I2C_1_START, &I2C_1_WRITE, &I2C_1_READ_ACK, &I2C_1_READ_NACK, &I2C_1_STOP);
  LC512_Init(&I2C_1_START, &I2C_1_WRITE, &I2C_1_READ_ACK, &I2C_1_READ_NACK, &I2C_1_STOP);
  LC512_Adress(0x50);
  MENU_INIT(SSH1306_OLED_ClearDisplay, SSH1306_OLED_Update, SSH1306_OLED_Write_Text, SSH1306_OLED_Write_Dec);
  MENU_ANA_INIT(ANA_MENU);
  }

void THREADS_INIT()
  {
  THREAD_INIT(&THREADS[THREAD_LED], THREAD_FLG_START | THREAD_FLG_LOOP, 1, THREAD_LED_FUNCT);
  THREAD_INIT(&THREADS[THREAD_UART_1_RX], 0, 0, THREAD_UART_1_RX_FUNCT);
  THREAD_INIT(&THREADS[THREAD_UART_2_RX], 0, 0, THREAD_UART_2_RX_FUNCT);
  THREAD_INIT(&THREADS[THREAD_BUZZER], THREAD_FLG_START | THREAD_FLG_LOOP, 0, THREAD_BUZZER_FUNCT);
  THREAD_INIT(&THREADS[THREAD_RELAYS], THREAD_FLG_START | THREAD_FLG_LOOP, 1, THREAD_RELAYS_FUNCT);
  THREAD_INIT(&THREADS[THREAD_INPUTS], THREAD_FLG_START | THREAD_FLG_LOOP, 1, THREAD_INPUTS_FUNCT);
  THREAD_INIT(&THREADS[THREAD_ADC_OKUMA], THREAD_FLG_START | THREAD_FLG_LOOP, 50, THREAD_ADC_OKUMA_FUNCT);
  THREAD_INIT(&THREADS[THREAD_MENU_BUTON], THREAD_FLG_START | THREAD_FLG_LOOP, 1, THREAD_MENU_BUTON_FUNCT);
  THREAD_INIT(&THREADS[THREAD_MOTOR], THREAD_FLG_START | THREAD_FLG_LOOP, 10, THREAD_MOTOR_FUNCT);
  THREAD_INIT(&THREADS[THREAD_SERVICE_MODE], THREAD_FLG_START | THREAD_FLG_LOOP, 1, THREAD_SERVICE_MODE_FUNCT);
  THREAD_INIT(&THREADS[THREAD_INDIKASYON_TEST], THREAD_FLG_START, 1, THREAD_INDIKASYON_TEST_FUNCT);
  THREAD_INIT(&THREADS[THREAD_SELENOID_A], 0, 1, THREAD_SELENOID_A_FUNCT);
  THREAD_INIT(&THREADS[THREAD_SELENOID_B], 0, 1, THREAD_SELENOID_B_FUNCT);

  if (PIN_GET_PORT('F', 0)) THREAD_STOP(&THREADS[THREAD_SERVICE_MODE]);
  else THREAD_STOP(&THREADS[THREAD_MENU_BUTON]);
  SELENOID_FUNCT(SELENOID_A_BIRAK || SELENOID_B_BIRAK);
  }

void MOTOR_MODULE_INIT()
  {
  MOTOR_SET_MODE(MOTOR_MODE_FIRCALI);
  MOTOR_PWM_INIT(0, PWM_3A_DUTY, PWM_3B_DUTY);
  MOTOR_SET_Z_POINT(1681);
  MOTOR_SET_KOL_TOPLAMA_TOLERANS(50);
  MOTOR_MODULE_INIT_2();
  }

void MOTOR_MODULE_INIT_2()
  {
  MOTOR_PID_INIT(0.25, 0.25);
  MOTOR_SET_MAX_MIN_PWM(50, 0);
  MOTOR_INIT_MAX_HIZ(20);
  MOTOR_TIME_OUT_SET(5000);
  MOTOR_TORK_SET(CONFIG_RAM_GET(MOTOR_TORQUE));
  }

void PIN_INIT()
  {
  PIN_SET_IO('D', 'O', 'B', 7, 'L'); //LED 
  PIN_SET_IO('D', 'O', 'A', 2, 'L'); //BUZZER

  PIN_SET_IO('D', 'I', 'D', 5, 'H'); //INPUT A
  PIN_SET_IO('D', 'I', 'D', 6, 'H'); //INPUT B
  PIN_SET_IO('D', 'I', 'G', 0, 'H'); //INPUT EMG
  PIN_SET_IO('D', 'I', 'G', 1, 'H'); //INPUT RES
  PIN_SET_IO('D', 'I', 'C', 0, 'H'); //INHIBIT A
  PIN_SET_IO('D', 'I', 'C', 1, 'H'); //INHIBIT B
  PIN_SET_IO('D', 'I', 'E', 6, 'H'); //EXT 1
  PIN_SET_IO('D', 'I', 'E', 7, 'H'); //EXT 2
  PIN_SET_IO('D', 'I', 'F', 0, 'H'); //BUTON 1
  PIN_SET_IO('D', 'I', 'E', 2, 'H'); //BUTON 2
  PIN_SET_IO('D', 'I', 'E', 5, 'H'); //BUTON 3
  PIN_SET_IO('A', 'I', 'F', 5, 'L'); //VOLTAJ OKUMA
  PIN_SET_IO('A', 'I', 'F', 6, 'L'); //A YONU TORK
  PIN_SET_IO('A', 'I', 'F', 7, 'L'); //B YONU TORK

  PIN_SET_IO('D', 'O', 'C', 2, 'L'); //RELAY ALARM
  PIN_SET_IO('D', 'O', 'C', 3, 'L'); //RELAY BA
  PIN_SET_IO('D', 'O', 'C', 4, 'L'); //RELAY AB
  PIN_SET_IO('D', 'O', 'A', 3, 'L'); //RELAY BUSY
  PIN_SET_IO('D', 'O', 'F', 1, 'L'); //DROP ARM
  PIN_SET_IO('D', 'O', 'C', 6, 'L'); //POWER RELAY

  PIN_SET_IO('D', 'O', 'E', 3, 'L'); //MOTOR PWM 3A
  PIN_SET_IO('D', 'O', 'E', 4, 'L'); //MOTOR PWM 3B
  PIN_SET_IO('D', 'O', 'A', 6, 'H'); //MOTOR ENABLE

  PIN_SET_IO('D', 'O', 'B', 5, 'L'); //SELENOID A PWM
  PIN_SET_IO('D', 'O', 'B', 6, 'L'); //SELENOID B PWM

  PIN_SET_IO('D', 'I', 'D', 1, 'L'); //SCL
  PIN_SET_IO('D', 'I', 'D', 0, 'H'); //SDA

  PIN_SET_IO('D', 'O', 'G', 3, 'L'); //YAN IND A
  PIN_SET_IO('D', 'O', 'G', 4, 'L'); //YAN IND B
  }

int main(void)
  {
  // MCU_INIT(1, 16);
  // INIT_REG();
  PIN_INIT();
  INIT_ROLE();
  INTERNAL_MODULS_INIT();
  EXTERNAL_MODULS_INIT();
  THREADS_INIT();
  INTERRUPT_ALL(1);
  WAIT_INTERRUPT(500);
  MOTOR_MODULE_INIT();
  MOTOR_START(2047);
  while (1) SYSTEM_CONTROL_ALL();
  }