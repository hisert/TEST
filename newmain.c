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
void REG_PROCESS(char *msg);
void TASK_UART_1_RX_FUNCT(byte taskIndex);
void TASK_UART_0_RX_FUNCT(byte taskIndex);
void TASK_MENU_PROCESS_FUNCT(byte taskIndex);
#define HU PINB & 2 
#define HV PINB & 16 
#define HW PINB & 32 
#define RX_ENABLE UCSR0B = UCSR0B | (1 << RXEN0)
#define RX_DISABLE UCSR0B = UCSR0B  & ~(1 << RXEN0)

void RS_WRITE(const char *msg)
  {
  RX_DISABLE;
  PIN_SET_IO('D', 'O', 'B', 0, 'H'); //RS485 
  UART_0_STRING(msg);
  PIN_SET_IO('D', 'O', 'B', 0, 'L'); //RS485 
  RX_ENABLE;
  }

void RS_DEC(word data)
  {
  RX_DISABLE;
  PIN_SET_IO('D', 'O', 'B', 0, 'H'); //RS485 
  UART_0_DECIMAL(data);
  PIN_SET_IO('D', 'O', 'B', 0, 'L'); //RS485 
  RX_ENABLE;
  }

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
  {.text = "FIX A COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_A_FIX, .max = 0xFFFF, .min = 0},
  {.text = "FIX B COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_B_FIX, .max = 0xFFFF, .min = 0},
  {.text = "TEMP A COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_A_TEMP, .max = 0xFFFF, .min = 0},
  {.text = "TEMP B COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_B_TEMP, .max = 0xFFFF, .min = 0},
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
    if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&MENU_OK) >= 25) if ((BUTON_GET_TIME(&MENU_OK) % 40) == 0) MENU_BUTON_ADD('B');
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
  THREAD_DEBUG,
  THREAD_MOTOR,
  THREAD_INPUT,
  THREAD_DONE,
  } THREADS_tt;

void LED_THREAD(byte threadIndex)
  {
  static THREAD_DELAY timer;
  THREAD_TIME_START(&timer);
  if (THREAD_TIME_WAIT(&timer, 95)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('C', 0);
  if (THREAD_TIME_WAIT(&timer, 5)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('C', 0);
  if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);

  }

void INPUT_THREAD(byte threadIndex)
  {
  MENU_BUTON_READ();
  }

void DEBUG_THREAD(byte threadIndex)
  {
  // UART_0_DECIMAL(MOTOR_GET_INDEX());
  }

void MOTOR_THREAD(byte threadIndex)
  {
  byte state = MOTOR_PROCESS(0);
  if (state == MOTOR_BASARILI_DURDU) RS_WRITE("MOTOR SUCCESS");
  if (state == MOTOR_TIME_OUT_DURDU) RS_WRITE("MOTOR TIME OUT");
  if (state == MOTOR_TORK_DURDU) RS_WRITE("MOTOR TORK");
  if (state == MOTOR_MAS12_READ_ERROR) RS_WRITE("MAS12 ERROR");
  if (state == MOTOR_KOL_TOPLAMA) RS_WRITE("MOTOR KOL TOPLUYOR");
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TASK FUNCT     ">

typedef enum
  {
  TASK_UART_0_RX,
  TASK_UART_1_RX,
  TASK_REG_RANDCODE,
  TASK_MENU_PROCESS,
  TASK_DONE,
  } TASK_tt;

void TASK_UART_1_RX_FUNCT(byte taskIndex)
  {
  REG_PROCESS(UART_1_MSG);
  TASK_STOP(taskIndex);
  }

void TASK_UART_0_RX_FUNCT(byte taskIndex)
  {
  //  REG_PROCESS(UART_0_MSG);
  MOTOR_START(atoi(UART_0_MSG));
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
  if (x == '(') counter = 0;
  else if (x == ')')
    {
    UART_0_MSG[counter] = 0;
    TASK_START(TASK_UART_0_RX);
    }
  else if (counter < 20) UART_0_MSG[counter++] = x;
  }
// </editor-fold>


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

  PIN_SET_LAT('C', 6, 'H');
  if (REG_GET_FLAG(KOMUT) & RG_EN) UART_0_STRING(TX);
  //  if (REG_GET_FLAG(KOMUT) & RG_EN) UART_1_STRING(TX);
  PIN_SET_LAT('C', 6, 'L');
  }

void REG_SERI_NUM_FUNCT(byte regId, byte komut)
  {
  if (komut == ':');
  if (komut == '?');
  }

void INIT_REG()
  {
  REG_CREATE(REGx_ADDR, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
  REG_CREATE(REGx_RAND_CODE, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD, 0, 0xFFFF, 0);
  REG_CREATE(REGx_SERI_NO, REG_SERI_NUM_FUNCT, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV | RG_FNC | RG_MAIN, 0, 0xFFFF, 0);
  REG_CREATE(REGx_VERSION, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_RD, 0x10, 0xFFFF, 0);
  REG_CREATE(REGx_SLAVE_ADRESS, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_2 | RG_WR | RG_RD | RG_NV, 0, 0xFF, 0);
  REGISTER_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PROJE FUNCT    ">



// </editor-fold>

int main(void)
  {
  //   MCU_INIT(64);
  // PIN_SET_IO('D', 'I', 'B', 5, 'H');
  // PIN_SET_IO('D', 'I', 'B', 6, 'H');
  //  PIN_SET_IO('D', 'I', 'B', 7, 'H');
  //  PIN_SET_IO('D', 'O', 'C', 6, 'L'); //RS485
  //  PIN_SET_IO('D', 'O', 'B', 4, 'L'); //CANLI 

  PIN_SET_IO('D', 'O', 'C', 0, 'L'); //CANLI 
  PIN_SET_IO('D', 'O', 'B', 0, 'L'); //RS485 

  //INIT_REG();
  TIMER_1_INIT(1);
  UART_0_INIT(19200);
  // UART_1_INIT(9600);
  // SOFT_I2C_INIT(&DDRD, &PORTD, &PIND, 1, &DDRD, &PORTD, &PIND, 0);
  // SSH1106_OLED_INIT(SOFT_I2C_START, SOFT_I2C_WRITE, SOFT_I2C_STOP);

  I2C_1_INIT(100);
  MAS12_INIT(I2C_1_START, I2C_1_WRITE, I2C_1_READ_ACK, I2C_1_READ_NACK, I2C_1_STOP);
  //  SSH1106_OLED_INIT(I2C_1_START, I2C_1_WRITE, I2C_1_STOP);
  //  MENU_INIT(SSH1106_OLED_ClearDisplay, SSH1106_OLED_Update, SSH1106_OLED_Write_Text, SSH1106_OLED_Write_Dec);
  //  MENU_ANA_INIT(ANA_MENU);

  THREAD_CREATE(THREAD_LED_CANLI, THREAD_FLG_START | THREAD_FLG_LOOP | THREAD_FLG_WORK_ON_BACK_PROCESS, 10, LED_THREAD);
  //THREAD_CREATE(THREAD_INPUT, THREAD_FLG_START | THREAD_FLG_LOOP | THREAD_FLG_WORK_ON_BACK_PROCESS, 20, INPUT_THREAD);
  THREAD_CREATE(THREAD_DEBUG, THREAD_FLG_START | THREAD_FLG_LOOP, 100, DEBUG_THREAD);
  THREAD_CREATE(THREAD_MOTOR, THREAD_FLG_START | THREAD_FLG_LOOP, 5, MOTOR_THREAD);

  TASK_CREATE(TASK_UART_0_RX, 0, TASK_UART_0_RX_FUNCT);
  // TASK_CREATE(TASK_UART_1_RX, 0, TASK_UART_1_RX_FUNCT);
  TASK_CREATE(TASK_REG_RANDCODE, THREAD_FLG_START, REG_CHANGE_RANDCODE);
  //TASK_CREATE(TASK_MENU_PROCESS, THREAD_FLG_START, TASK_MENU_PROCESS_FUNCT);
  INTERRUPT_ALL(1);

  PIN_SET_IO('D', 'O', 'D', 6, 'L'); //PWM PWM W
  PIN_SET_IO('D', 'O', 'D', 5, 'L'); //PWM PWM V
  PIN_SET_IO('D', 'O', 'D', 3, 'L'); //PWM PWM U

  PIN_SET_IO('D', 'O', 'D', 7, 'H'); //PWM ENALBE W
  PIN_SET_IO('D', 'O', 'D', 4, 'H'); //PWM ENABLE V
  PIN_SET_IO('D', 'O', 'D', 2, 'H'); //PWM ENABLE U

  PIN_SET_IO('D', 'I', 'B', 4, 'H'); //SENSOR W READ
  PIN_SET_IO('D', 'I', 'B', 5, 'H'); //SENSOR V READ
  PIN_SET_IO('D', 'I', 'B', 1, 'H'); //SENSOR U READ

  PWM_0_INIT(SYSTEM_PWM_PRESCALE_0, SYSTEM_PWM_DUTY_SLOW, 8);
  PWM_2_INIT(SYSTEM_PWM_PRESCALE_0, SYSTEM_PWM_DUTY_SLOW, 8);

  PWM_0_INIT(SYSTEM_PWM_PRESCALE_0, SYSTEM_PWM_DUTY_SLOW, 8);
  PWM_2_INIT(SYSTEM_PWM_PRESCALE_0, SYSTEM_PWM_DUTY_SLOW, 8);
  PWM_0A_SET(1);
  PWM_0B_SET(1);
  PWM_2B_SET(1);
  PIN_SET_IOC(1, 1);
  PIN_SET_IOC(4, 1);
  PIN_SET_IOC(5, 1);

  MOTOR_SET_MODE(MOTOR_MODE_FIRCASIZ);
  MOTOR_PWM_INIT(PWM_0A_DUTY, PWM_0B_DUTY, PWM_2B_DUTY);
  MOTOR_SET_Z_POINT(MAS12_READ_HAL_DATA());
  MOTOR_SET_KOL_TOPLAMA_TOLERANS(250);
  MOTOR_PID_INIT(0.2, 0.1);
  MOTOR_INIT_MAX_HIZ(16);
  MOTOR_TIME_OUT_SET(3000);

  MOTOR_START(1047);
  WAIT_INTERRUPT(1000);

  MOTOR_START(3047);
  WAIT_INTERRUPT(1000);
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
    UART_0_INTERRUPT_FUNCT(RCREG1);
    }
  else if (PIR3bits.RC2IF)
    { // UART1 al?c? interrupt'?
    PIR3bits.RC2IF = 0;
    UART_1_INTERRUPT_FUNCT(RCREG2);
    }
  }
#endif

// </editor-fold>