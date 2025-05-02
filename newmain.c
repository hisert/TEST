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

// <editor-fold defaultstate="collapsed" desc="VARIABLES      ">
char UART_1_MSG[20];
char UART_0_MSG[20];
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM FUNCT   ">

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
  EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
  if (EEPROM_GET(MAGIC_BYTES != 0xAABB))EEPROM_SET_ALL();
  EEPROM_GET_ALL();
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MENU           ">
// <editor-fold defaultstate="collapsed" desc="LIBRARY VARIABLES">

extern const char **MENU_SELECT_LIST;
extern Menu_One *MENU_POINTER;
extern byte MENU_MAX;
extern const char *SHOW_DATA_TEXT;
extern const char *MENU_UST_YAZI;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="RELAY SETTING FUNCT">
const char *SELECT_LIST_RELAY_MODE[] = {"MODE N/O", "MODE N/C"};

word MENU_FUNCT_RELAY_A_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_A_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
    return SETTING_VALUES[ROLE_A_MODE];
    }
  }

word MENU_FUNCT_RELAY_B_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_B_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
    return SETTING_VALUES[ROLE_B_MODE];
    }
  }

word MENU_FUNCT_RELAY_BUSY_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_BUSY_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
    return SETTING_VALUES[ROLE_BUSY_MODE];
    }
  }

word MENU_FUNCT_RELAY_ALARM_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_ALARM_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
    return SETTING_VALUES[ROLE_ALARM_MODE];
    }
  }

word MENU_FUNCT_RELAY_A_TIME(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_A_TIME] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[ROLE_A_TIME];
    }
  }

word MENU_FUNCT_RELAY_B_TIME(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_B_TIME] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[ROLE_B_TIME];
    }
  }

word MENU_FUNCT_RELAY_BUSY_TIME(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_BUSY_TIME] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[ROLE_BUSY_TIME];
    }
  }

word MENU_FUNCT_RELAY_ALARM_TIME(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ROLE_ALARM_TIME] = data;
    return 0;
    }
  else
    {
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

word MENU_FUNCT_COUNTER_A_FIX(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[COUNTER_A_FIX] = data;
    return 0;
    }
  else
    {
    SHOW_DATA_TEXT = "CANT ERASE";
    return SETTING_VALUES[COUNTER_A_FIX];
    }
  }

word MENU_FUNCT_COUNTER_B_FIX(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[COUNTER_B_FIX] = data;
    return 0;
    }
  else
    {
    SHOW_DATA_TEXT = "CANT ERASE";
    return SETTING_VALUES[COUNTER_B_FIX];
    }
  }

word MENU_FUNCT_COUNTER_A_TEMP(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[COUNTER_A_TEMP] = data;
    return 0;
    }
  else
    {
    SHOW_DATA_TEXT = "ERASE DATA ?";
    return SETTING_VALUES[COUNTER_A_TEMP];
    }
  }

word MENU_FUNCT_COUNTER_B_TEMP(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[COUNTER_B_TEMP] = data;
    return 0;
    }
  else
    {
    SHOW_DATA_TEXT = "ERASE DATA ?";
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
  if (komut)
    {
    SETTING_VALUES[RANDOM_A_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_RANDOM_MODE;
    return SETTING_VALUES[RANDOM_A_MODE];
    }
  }

word MENU_FUNCT_RANDOM_B_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[RANDOM_B_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_RANDOM_MODE;
    return SETTING_VALUES[RANDOM_B_MODE];
    }
  }

word MENU_FUNCT_RANDOM_A_AMOUNT(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[RANDOM_A_AMOUNT] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[RANDOM_A_AMOUNT];
    }
  }

word MENU_FUNCT_RANDOM_B_AMOUNT(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[RANDOM_B_AMOUNT] = data;
    return 0;
    }
  else
    {
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
  if (komut)
    {
    SETTING_VALUES[INPUT_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_INPUT_MODE;
    return SETTING_VALUES[INPUT_MODE];
    }
  }

word MENU_FUNCT_INPUT_TIME_OUT(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[INPUT_TIME_OUT] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[INPUT_TIME_OUT];
    }
  }

word MENU_FUNCT_INPUT_BUFFER(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[INPUT_BUFFER] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[INPUT_BUFFER];
    }
  }

word MENU_FUNCT_EMG_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[INPUT_EMG_MODE] = data;
    return 0;
    }
  else
    {
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

const char *SELECT_LIST_DROP_ARM_MODE[] = {"DISABLE", "JUST EMG", "JUST POWER FAIL", "POWER FAIL & EMG"};
const char *SELECT_LIST_ARM_MOTOR_MODE[] = {"PASSIVE", "ACTIVE"};

word MENU_FUNCT_ARM_DROP_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ARM_DROP_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_DROP_ARM_MODE;
    return SETTING_VALUES[ARM_DROP_MODE];
    }
  }

word MENU_FUNCT_ARM_MOTOR_MODE(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ARM_MOTOR_MODE] = data;
    return 0;
    }
  else
    {
    MENU_SELECT_LIST = SELECT_LIST_ARM_MOTOR_MODE;
    return SETTING_VALUES[ARM_MOTOR_MODE];
    }
  }

word MENU_FUNCT_ARM_MOTOR_SPEED(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ARM_MOTOR_SPEED] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[ARM_MOTOR_SPEED];
    }
  }

word MENU_FUNCT_ARM_MOTOR_BREAK_SPEED(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[ARM_MOTOR_BREAK_SPEED] = data;
    return 0;
    }
  else
    {
    return SETTING_VALUES[ARM_MOTOR_BREAK_SPEED];
    }
  }

word MENU_FUNCT_ARM_MAS12(byte komut, word data)
  {
  if (komut == 0) MENU_BUTON_ADD('R');
  static dword x = 0;
  MENU_FUNCT_CLEAR();
  MENU_FUNCT_WRITE_DEC(0, 0, x++);
  MENU_FUNCT_UPDATE();
  return 0;
  }
Menu_One ARM_SETTING_MENU[] = {
  {.text = "DROP ARM MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_ARM_DROP_MODE, .max = 3},
  {.text = "MOTOR MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_ARM_MOTOR_MODE, .max = 3},
  {.text = "MOTOR SPEED", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_ARM_MOTOR_SPEED, .max = 100, .min = 0},
  {.text = "MOTOR BREAK SPEED", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_ARM_MOTOR_BREAK_SPEED, .max = 100, .min = 0},
  {.text = "MAS12 STATUS", .flag = MENU_FLAG_REFRESH_DATA, .Funct = MENU_FUNCT_ARM_MAS12, .max = 0, .min = 0},
  };
// </editor-fold>

Menu_One ANA_MENU[] = {
  {.text = "INPUT SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) INPUT_MENU},
  {.text = "ARM SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) ARM_SETTING_MENU},
  {.text = "RELAY SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) RELAY_MENU},
  {.text = "SYSTEM COUNTER", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) COUNTER_MENU},
  {.text = "RANDOM SORTER", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) RANDOM_MENU},
  };

const char *ANA_MENU_UST_YAZI = "MAIN MENU";
const char *RELAY_MENU_UST_YAZI = "RELAY MENU";
const char *ARM_MENU_UST_YAZI = "ARM MENU";
const char *COUNTER_MENU_UST_YAZI = "COUNTER MENU";
const char *RANDOM_MENU_UST_YAZI = "RANDOM MENU";
const char *INPUT_MENU_UST_YAZI = "INPUT MENU";

void MENU_UST_DATA_GETIR()
  {
  if (MENU_POINTER == ANA_MENU) MENU_MAX = sizeof (ANA_MENU) / sizeof (ANA_MENU[0]) - 1;
  if (MENU_POINTER == RELAY_MENU) MENU_MAX = sizeof (RELAY_MENU) / sizeof (RELAY_MENU[0]) - 1;
  if (MENU_POINTER == COUNTER_MENU) MENU_MAX = sizeof (COUNTER_MENU) / sizeof (COUNTER_MENU[0]) - 1;
  if (MENU_POINTER == RANDOM_MENU) MENU_MAX = sizeof (RANDOM_MENU) / sizeof (RANDOM_MENU[0]) - 1;
  if (MENU_POINTER == INPUT_MENU) MENU_MAX = sizeof (INPUT_MENU) / sizeof (INPUT_MENU[0]) - 1;
  if (MENU_POINTER == ARM_SETTING_MENU) MENU_MAX = sizeof (ARM_SETTING_MENU) / sizeof (ARM_SETTING_MENU[0]) - 1;

  if (MENU_POINTER == ANA_MENU) MENU_UST_YAZI = ANA_MENU_UST_YAZI;
  if (MENU_POINTER == RELAY_MENU) MENU_UST_YAZI = RELAY_MENU_UST_YAZI;
  if (MENU_POINTER == ARM_SETTING_MENU) MENU_UST_YAZI = ARM_MENU_UST_YAZI;
  if (MENU_POINTER == COUNTER_MENU) MENU_UST_YAZI = COUNTER_MENU_UST_YAZI;
  if (MENU_POINTER == RANDOM_MENU) MENU_UST_YAZI = RANDOM_MENU_UST_YAZI;
  if (MENU_POINTER == INPUT_MENU) MENU_UST_YAZI = INPUT_MENU_UST_YAZI;
  }

void MENU_BUTON_READ()
  {
  static Buton_t MENU_OK;
  static Buton_t MENU_DOWN;
  static Buton_t MENU_UP;
  byte temp = 0;

  temp = BUTON_PROCESS(&MENU_UP, PIN_GET_PORT('B', 5), 2, 1);
  if (temp)
    {
    if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&MENU_UP) > 25) if ((BUTON_GET_TIME(&MENU_UP) % 1) == 0) MENU_BUTON_ADD('U');
    if (temp == BUTON_PRESSED) if (BUTON_GET_TIME(&MENU_UP) < 20) MENU_BUTON_ADD('U');
    }
  temp = BUTON_PROCESS(&MENU_OK, PIN_GET_PORT('B', 6), 2, 1);
  if (temp)
    {
    if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&MENU_OK) == 25) MENU_BUTON_ADD('B');
    if (temp == BUTON_PRESSED) if (BUTON_GET_TIME(&MENU_OK) < 20) MENU_BUTON_ADD('O');
    }
  temp = BUTON_PROCESS(&MENU_DOWN, PIN_GET_PORT('B', 7), 2, 1);
  if (temp)
    {
    if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&MENU_DOWN) > 25) if ((BUTON_GET_TIME(&MENU_DOWN) % 1) == 0) MENU_BUTON_ADD('D');
    if (temp == BUTON_PRESSED) if (BUTON_GET_TIME(&MENU_DOWN) < 20) MENU_BUTON_ADD('D');
    }
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT   ">

typedef enum
  {
  THREAD_LED_CANLI,
  THREAD_INPUT,
  THREAD_DONE,
  } THREADS_tt;

void LED_THREAD(byte threadIndex)
  {
  static THREAD_DELAY timer;
  THREAD_TIME_START(&timer);
  if (THREAD_TIME_WAIT(&timer, 95)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('B', 4);
  if (THREAD_TIME_WAIT(&timer, 5)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('B', 4);
  if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);

  }

void INPUT_THREAD(byte threadIndex)
  {
  MENU_BUTON_READ();
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TASK FUNCT     ">

typedef enum
  {
  TASK_UART_0_RX,
  TASK_UART_1_RX,
  TASK_MENU_PROCESS,
  TASK_DONE,
  } TASK_tt;

void TASK_UART_1_RX_FUNCT(byte taskIndex)
  {
  PIN_SET_LAT('C', 6, 'H');
  UART_1_STRING(UART_1_MSG);
  PIN_SET_LAT('C', 6, 'L');
  TASK_STOP(taskIndex);
  }

void TASK_UART_0_RX_FUNCT(byte taskIndex)
  {
  TASK_STOP(taskIndex);
  }

void TASK_MENU_PROCESS_FUNCT(byte taskIndex)
  {
  MENU_PROCESS();
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MAIN FUNCT     ">
// <editor-fold defaultstate="collapsed" desc="UART INTERRUPT FUNCT">

void UART_1_INTERRUPT_FUNCT(byte data)
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

void UART_0_INTERRUPT_FUNCT(byte data)
  {
  static byte counter = 0;
  byte x = data;
  if (x == '<') counter = 0;
  else if (x == '>')
    {
    UART_0_MSG[counter] = 0;
    TASK_START(TASK_UART_0_RX);
    }
  if (counter < 20) UART_0_MSG[counter++] = x;
  }
// </editor-fold>

void SYSTEM_CONTROL_ALL()
  {
  THREAD_MAIN();
  TASK_MAIN();
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PROJE FUNCT    ">


// </editor-fold>

byte PROGRAM_MODE_1(byte flag);
byte PROGRAM_MODE_2(byte flag);

int main(void)
  {
  PIN_SET_IO('D', 'I', 'B', 5, 'H');
  PIN_SET_IO('D', 'I', 'B', 6, 'H');
  PIN_SET_IO('D', 'I', 'B', 7, 'H');
  PIN_SET_IO('D', 'O', 'C', 6, 'H'); //RS485
  PIN_SET_IO('D', 'O', 'B', 4, 'L'); //CANLI

  EEPROM_START();
  TIMER_1_INIT(1);
  UART_1_INIT(19200);

  // SOFT_I2C_INIT(&DDRD, &PORTD, &PIND, 1, &DDRD, &PORTD, &PIND, 0);
  // SSH1106_OLED_INIT(SOFT_I2C_START, SOFT_I2C_WRITE, SOFT_I2C_STOP);

  I2C_1_INIT(100);
  SSH1106_OLED_INIT(I2C_1_START, I2C_1_WRITE, I2C_1_STOP);

  MENU_INIT(SSH1106_OLED_ClearDisplay, SSH1106_OLED_Update, SSH1106_OLED_Write_Text, SSH1106_OLED_Write_Dec);
  MENU_ANA_INIT(ANA_MENU);

  THREAD_CREATE(THREAD_LED_CANLI, THREAD_FLG_START | THREAD_FLG_LOOP | THREAD_FLG_WORK_ON_BACK_PROCESS, 10, LED_THREAD);
  THREAD_CREATE(THREAD_INPUT, THREAD_FLG_START | THREAD_FLG_LOOP | THREAD_FLG_WORK_ON_BACK_PROCESS, 20, INPUT_THREAD);

  TASK_CREATE(TASK_UART_0_RX, 0, TASK_UART_0_RX_FUNCT);
  TASK_CREATE(TASK_UART_1_RX, 0, TASK_UART_1_RX_FUNCT);
  TASK_CREATE(TASK_MENU_PROCESS, THREAD_FLG_START, TASK_MENU_PROCESS_FUNCT);
  INTERRUPT_ALL(1);
  WAIT_INTERRUPT(1000);
  while (1)
    {
    SYSTEM_CONTROL_ALL();
    TIME_OUT_FUNCT(1002, PROGRAM_MODE_1);
    TIME_OUT_FUNCT(1002, PROGRAM_MODE_2);
    }
  }

byte PROGRAM_MODE_1(byte flag)
  {
  static TIME_OUT_t time_out_1;
  if (flag) TIME_OUT_CHECK(&time_out_1, 0);
  if (TIME_OUT_CHECK(&time_out_1, 100))
    {
    UART_1_STRING("HELLO1");
    }

  static TIME_OUT_t time_out_2;
  if (flag) TIME_OUT_CHECK(&time_out_2, 0);
  if (TIME_OUT_CHECK(&time_out_2, 200))
    {
    UART_1_STRING("WORLD1");
    return 1;
    }
  return 0;
  }

byte PROGRAM_MODE_2(byte flag)
  {
  static TIME_OUT_t time_out_1;
  if (flag) TIME_OUT_CHECK(&time_out_1, 0);
  if (TIME_OUT_CHECK(&time_out_1, 100))
    {
    UART_1_STRING("HELLO2");
    }

  static TIME_OUT_t time_out_2;
  if (flag) TIME_OUT_CHECK(&time_out_2, 0);
  if (TIME_OUT_CHECK(&time_out_2, 200))
    {
    UART_1_STRING("WORLD2");
    }
  return 0;
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
  }

ISR(USART_RX_vect)
  {

  }

ISR(PCINT0_vect)
  {

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
  if (INTCONbits.RBIF)
    {
    byte x = PORTB;
    INTCONbits.RBIF = 0;
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


// </editor-fold>