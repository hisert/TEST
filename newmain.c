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

// <editor-fold defaultstate="collapsed" desc="MENU ">
// <editor-fold defaultstate="collapsed" desc="LIBRARY VARIABLES">
void (*MENU_CLEAR)(void);
void (*MENU_UPDATE)(void);
void(*MENU_WRITE_DEC)(word x, word y, dword data);
void(*MENU_WRITE_TEXT)(word x, word y, const char *text);

const char **MENU_SELECT_LIST;
Menu_One *MENU_POINTER = 0;
byte MENU_MAX = 0;
const char *SHOW_DATA_TEXT;
const char *MENU_UST_YAZI;
Menu_One * MENU_BACK_POINTER[5];
byte MENU_BACK_INDEX[5];
byte MENU_INDEX_COUNTER = 0;
byte MENU_MENU_COUNTER = 0;
Menu_One *MENU_ANA_MENU_ANA;

byte MENU_BUTON_STATUS = 0;

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT DEFINE">

void MENU_GIR(Menu_One *Menu, byte komut);
void MENU_CIK();
void MENU_TEXT_PRINT(const char *text, byte index);
void MENU_SHOW_DATA_PRINT(const char *text, word data);
void MENU_USE_SELECT(const char *ust_yazi, const char *data[], byte index);
void MENU_USE_VAL(const char *ust_yazi, word data_max, word data_min, word data);
void MENU_WORK(char MENU_MOVEMENT);
void MENU_INIT(void (*MENU_CLEAR_t)(void), void (*MENU_UPDATE_t)(void), void(*MENU_WRITE_TEXT_t)(word, word, const char *), void(*MENU_WRITE_DEC_t)(word, word, dword));
void MENU_ANA_INIT(Menu_One *MENU_ANA_MENU_ANA_t);
void MENU_PROCESS();
void MENU_BUTON_ADD(char process);
// </editor-fold>

typedef enum
  {
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

const char *COUNTER_CANT_ERASE = "CANT ERASE";
const char *COUNTER_ASK_ERASE = "ERASE DATA ?";

word MENU_FUNCT_COUNTER_A_FIX(byte komut, word data)
  {
  if (komut)
    {
    SETTING_VALUES[COUNTER_A_FIX] = data;
    return 0;
    }
  else
    {
    SHOW_DATA_TEXT = COUNTER_CANT_ERASE;
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
    SHOW_DATA_TEXT = COUNTER_CANT_ERASE;
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
    SHOW_DATA_TEXT = COUNTER_ASK_ERASE;
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

// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT">

void MENU_TEXT_ORTALA(const char* input, char* output, unsigned char maxLen)
  {
  unsigned char inputLen = strlen(input);
  if (inputLen >= maxLen)
    {
    strncpy(output, input, maxLen);
    output[maxLen] = '\0';
    return;
    }
  unsigned char totalSpaces = maxLen - inputLen;
  unsigned char leftSpaces = totalSpaces / 2;
  unsigned char rightSpaces = totalSpaces - leftSpaces;
  unsigned char i = 0;
  for (i = 0; i < leftSpaces; i++) output[i] = ' ';
  for (unsigned char j = 0; j < inputLen; j++) output[i++] = input[j];
  for (unsigned char j = 0; j < rightSpaces; j++)output[i++] = ' ';
  output[i] = '\0'; // Null-terminator
  }

void MENU_GIR(Menu_One *Menu, byte komut)
  {
  if (komut)
    {
    MENU_BACK_POINTER[MENU_MENU_COUNTER] = MENU_POINTER;
    MENU_BACK_INDEX[MENU_MENU_COUNTER] = MENU_INDEX_COUNTER;
    MENU_MENU_COUNTER = MENU_MENU_COUNTER + 1;
    MENU_POINTER = Menu;
    MENU_INDEX_COUNTER = 0;
    }
  else
    {
    MENU_INDEX_COUNTER = 0;
    MENU_MENU_COUNTER = 0;
    MENU_POINTER = MENU_ANA_MENU_ANA;
    }

  MENU_UST_DATA_GETIR();
  }

void MENU_CIK()
  {
  if (MENU_MENU_COUNTER)
    {
    MENU_MENU_COUNTER = MENU_MENU_COUNTER - 1;
    MENU_POINTER = MENU_BACK_POINTER[MENU_MENU_COUNTER];
    MENU_INDEX_COUNTER = MENU_BACK_INDEX[MENU_MENU_COUNTER];
    MENU_UST_DATA_GETIR();
    }
  }

void MENU_TEXT_PRINT(const char *text, byte index)
  {
  char msg[30];
  MENU_CLEAR();
  MENU_TEXT_ORTALA(MENU_UST_YAZI, msg, 16);
  MENU_WRITE_TEXT(0, 0, msg); //0,0
  //   OLED_H_Line(0, 128, 8, 1);
  sprintf(msg, "%c) %s", (index + '1'), text);
  MENU_WRITE_TEXT(0, 20, msg); //0,14
  sprintf(msg, "%c/%c", (index + '1'), (MENU_MAX + '1'));
  MENU_WRITE_TEXT(105, 48, msg); //105,24
  MENU_UPDATE();
  }

void MENU_SHOW_DATA_PRINT(const char *text, word data)
  {
  char msg[30];
  MENU_CLEAR();
  MENU_TEXT_ORTALA(text, msg, 16);
  MENU_WRITE_TEXT(0, 0, msg);
  if (data >= 1000) MENU_WRITE_DEC(51, 24, data); //51, 24
  else if (data >= 100) MENU_WRITE_DEC(53, 24, data); //53,24
  else MENU_WRITE_DEC(56, 24, data); //56,24
  MENU_UPDATE();
  }

void MENU_USE_SELECT(const char *ust_yazi, const char *data[], byte index)
  {
  char msg[30];
  MENU_CLEAR();
  MENU_TEXT_ORTALA(ust_yazi, msg, 16);
  MENU_WRITE_TEXT(0, 0, msg); // 0, 0
  sprintf(msg, "%c ) %s", ('a' + index), data[index]);
  MENU_WRITE_TEXT(0, 24, msg); //0 , 16
  sprintf(msg, "%c/%c", (index + 'a'), (MENU_POINTER[MENU_INDEX_COUNTER].max) + 'a');
  MENU_WRITE_TEXT(105, 48, msg); //105,24
  MENU_UPDATE();
  }

void MENU_USE_VAL(const char *ust_yazi, word data_max, word data_min, word data)
  {
  char msg[30];
  MENU_CLEAR();
  MENU_TEXT_ORTALA(ust_yazi, msg, 16);
  MENU_WRITE_TEXT(0, 0, msg); // 0, 0
  MENU_WRITE_TEXT(0, 24, "MAX   NOW    MIN"); //*0 , 16
  MENU_WRITE_DEC(0, 48, data_max); //0,24

  if (data_min >= 1000) MENU_WRITE_DEC(103, 48, data_min); //103,24
  else if (data_min >= 100) MENU_WRITE_DEC(109, 48, data_min); //109,24
  else MENU_WRITE_DEC(116, 48, data_min);

  if (data >= 1000) MENU_WRITE_DEC(51, 48, data); //51 ,24
  else if (data >= 100) MENU_WRITE_DEC(53, 48, data); //53,24
  else MENU_WRITE_DEC(56, 48, data); //56,26
  MENU_UPDATE();
  }

void MENU_WORK(char MENU_MOVEMENT)
  {
  byte temp = 0;
  static word MENU_TEMP_VAL = 0;
  static word VAL_CHANGE_FLAG = 0;
  static byte MENU_SHOW_FLAG = 0;
  if (MENU_SHOW_FLAG == 0)
    {
    if (MENU_MOVEMENT == 'O')
      {
      temp = 1;
      MENU_GIR(MENU_ANA_MENU_ANA, 0);
      }
    else return;
    }
  else
    {
    if (MENU_MOVEMENT == 'U')
      {
      if (VAL_CHANGE_FLAG)
        {
        if (MENU_POINTER[MENU_INDEX_COUNTER].max > MENU_TEMP_VAL) MENU_TEMP_VAL = MENU_TEMP_VAL + 1;
        }
      else if (MENU_MAX > MENU_INDEX_COUNTER) MENU_INDEX_COUNTER = MENU_INDEX_COUNTER + 1;

      }
    if (MENU_MOVEMENT == 'D')
      {
      if (VAL_CHANGE_FLAG)
        {
        if (MENU_POINTER[MENU_INDEX_COUNTER].min < MENU_TEMP_VAL) MENU_TEMP_VAL = MENU_TEMP_VAL - 1;
        }
      else if (MENU_INDEX_COUNTER) MENU_INDEX_COUNTER = MENU_INDEX_COUNTER - 1;
      }
    if (MENU_MOVEMENT == 'B')
      {
      if (MENU_MOVEMENT == 'B')
        {
        if (VAL_CHANGE_FLAG == 1) VAL_CHANGE_FLAG = 0;
        else
          {
          if (MENU_MENU_COUNTER == 0)
            {
            MENU_SHOW_FLAG = 0;
            temp = 2;
            }
          else MENU_CIK();
          }
        }
      }
    if (MENU_MOVEMENT == 'O')
      {
      if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_NEW_MENU)
        {
        MENU_GIR(MENU_POINTER[MENU_INDEX_COUNTER].Funct, 1);
        }
      else if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SHOW_DATA)
        {
        if (VAL_CHANGE_FLAG == 0)
          {
          MENU_TEMP_VAL = 0;
          if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_TEMP_VAL = MENU_POINTER[MENU_INDEX_COUNTER].Funct(0, 9999);
          VAL_CHANGE_FLAG = 1;
          }
        else
          {
          if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_POINTER[MENU_INDEX_COUNTER].Funct(1, MENU_TEMP_VAL);
          VAL_CHANGE_FLAG = 0;
          }
        }
      else if ((MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_VALUE) || (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SELECT))
        {
        if (VAL_CHANGE_FLAG == 0)
          {
          MENU_TEMP_VAL = 0;
          if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_TEMP_VAL = MENU_POINTER[MENU_INDEX_COUNTER].Funct(0, 9999);
          VAL_CHANGE_FLAG = 1;
          }
        else
          {
          if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0) MENU_POINTER[MENU_INDEX_COUNTER].Funct(1, MENU_TEMP_VAL);
          VAL_CHANGE_FLAG = 0;
          }
        }
      }

    }
  if (temp == 1) MENU_SHOW_FLAG = 1;
  if (temp == 2)
    {
    MENU_CLEAR();
    MENU_UPDATE();
    }

  if (MENU_SHOW_FLAG)
    {
    if (VAL_CHANGE_FLAG)
      {
      if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_VALUE) MENU_USE_VAL(MENU_POINTER[MENU_INDEX_COUNTER].text, MENU_POINTER[MENU_INDEX_COUNTER].max, MENU_POINTER[MENU_INDEX_COUNTER].min, MENU_TEMP_VAL);
      else if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SELECT) MENU_USE_SELECT(MENU_POINTER[MENU_INDEX_COUNTER].text, MENU_SELECT_LIST, MENU_TEMP_VAL);
      else if (MENU_POINTER[MENU_INDEX_COUNTER].flag & MENU_FLAG_SHOW_DATA) MENU_SHOW_DATA_PRINT(SHOW_DATA_TEXT, MENU_TEMP_VAL);
      }
    else MENU_TEXT_PRINT(MENU_POINTER[MENU_INDEX_COUNTER].text, MENU_INDEX_COUNTER);
    }
  }

void MENU_INIT(void (*MENU_CLEAR_t)(void), void (*MENU_UPDATE_t)(void), void(*MENU_WRITE_TEXT_t)(word, word, const char *), void(*MENU_WRITE_DEC_t)(word, word, dword))
  {
  MENU_CLEAR = MENU_CLEAR_t;
  MENU_UPDATE = MENU_UPDATE_t;
  MENU_WRITE_DEC = MENU_WRITE_DEC_t;
  MENU_WRITE_TEXT = MENU_WRITE_TEXT_t;
  }

void MENU_ANA_INIT(Menu_One *MENU_ANA_MENU_ANA_t)
  {
  MENU_ANA_MENU_ANA = MENU_ANA_MENU_ANA_t;
  }

void MENU_PROCESS()
  {
  if (MENU_BUTON_STATUS)
    {
    if (MENU_BUTON_STATUS & PRESSED_OK)
      {
      MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_OK;
      MENU_WORK('O');
      }

    if (MENU_BUTON_STATUS & PRESSED_UP)
      {
      MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_UP;
      MENU_WORK('U');
      }

    if (MENU_BUTON_STATUS & PRESSED_DOWN)
      {
      MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_DOWN;
      MENU_WORK('D');
      }
    if (MENU_BUTON_STATUS & PRESSED_BACK)
      {
      MENU_BUTON_STATUS = MENU_BUTON_STATUS & ~PRESSED_BACK;
      MENU_WORK('B');
      }
    }
  }

void MENU_BUTON_ADD(char process)
  {
  if (process == 'U') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_UP;
  if (process == 'O') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_OK;
  if (process == 'D') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_DOWN;
  if (process == 'B') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_BACK;
  }

// </editor-fold>

void MENU_BUTON_READ()
  {
  static Buton_t MENU_OK;
  static Buton_t MENU_DOWN;
  static Buton_t MENU_UP;
  byte temp = 0;

  temp = BUTON_PROCESS(&MENU_UP, PIN_GET_PORT('B', 5), 10, 3);
  if (temp)
    {
    if (temp == BUTON_PRESSING)if (BUTON_GET_TIME(&MENU_UP) > 500) if ((BUTON_GET_TIME(&MENU_UP) % 5) == 0) MENU_BUTON_ADD('U');
    if (temp == BUTON_PRESSED) if (BUTON_GET_TIME(&MENU_UP) < 499) MENU_BUTON_ADD('U');
    }
  temp = BUTON_PROCESS(&MENU_OK, PIN_GET_PORT('B', 6), 10, 3);
  if (temp)
    {
    if (temp == BUTON_PRESSING) if (BUTON_GET_TIME(&MENU_OK) == 500) MENU_BUTON_ADD('B');
    if (temp == BUTON_PRESSED)if (BUTON_GET_TIME(&MENU_OK) < 499) MENU_BUTON_ADD('O');
    }
  temp = BUTON_PROCESS(&MENU_DOWN, PIN_GET_PORT('B', 7), 10, 3);
  if (temp)
    {
    if (temp == BUTON_PRESSING)if (BUTON_GET_TIME(&MENU_DOWN) > 500) if ((BUTON_GET_TIME(&MENU_DOWN) % 5) == 0) MENU_BUTON_ADD('D');
    if (temp == BUTON_PRESSED) if (BUTON_GET_TIME(&MENU_DOWN) < 499) MENU_BUTON_ADD('D');
    }
  }
// </editor-fold>

void LED_THREAD(byte threadIndex)
  {
  static THREAD_DELAY timer;
  THREAD_TIME_START(&timer);
  //if (THREAD_TIME_WAIT(&timer, 95)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('D', 3);
  //if (THREAD_TIME_WAIT(&timer, 5)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('D', 3);
  if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);
  MENU_BUTON_READ();

  }

int main(void)
  {
  PIN_SET_IO('D', 'I', 'B', 5, 'H');
  PIN_SET_IO('D', 'I', 'B', 6, 'H');
  PIN_SET_IO('D', 'I', 'B', 7, 'H');
  THREAD_CREATE(0, THREAD_FLG_START | THREAD_FLG_LOOP, 1, LED_THREAD);
  TIMER_1_INIT(1);
  INTERRUPT_ALL(1);
  I2C_1_INIT();
  SSH1106_OLED_INIT(I2C_1_START, I2C_1_WRITE, I2C_1_STOP);
  MENU_INIT(SSH1106_OLED_ClearDisplay, SSH1106_OLED_Update, SSH1106_OLED_Write_Text, SSH1106_OLED_Write_Dec);
  MENU_ANA_INIT(ANA_MENU);

  //UART_0_STRING("HELLO");
  // EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
  while (1)
    {
    THREAD_MAIN();
    TASK_MAIN();
    MENU_PROCESS();
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
  if (x == '*') MENU_BUTON_ADD('O');
  if (x == '-') MENU_BUTON_ADD('U');
  if (x == '+') MENU_BUTON_ADD('D');
  if (x == '/') MENU_BUTON_ADD('B');
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
