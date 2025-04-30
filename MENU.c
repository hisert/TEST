#include "MENU.h"

extern void MENU_UST_DATA_GETIR();
extern void WAIT_INTERRUPT(word ms);

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

void MENU_BUTON_ADD(char process)
  {
  if (process == 'U') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_UP;
  if (process == 'O') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_OK;
  if (process == 'D') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_DOWN;
  if (process == 'B') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_BACK;
  }

// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT">

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

void MENU_TEXT_ORTALA(const char* input, char* output, byte maxLen)
  {
  byte inputLen = strlen(input);
  if (inputLen >= maxLen)
    {
    strncpy(output, input, maxLen);
    output[maxLen] = '\0';
    return;
    }
  byte totalSpaces = maxLen - inputLen;
  byte leftSpaces = totalSpaces / 2;
  byte rightSpaces = totalSpaces - leftSpaces;
  byte i = 0;
  for (i = 0; i < leftSpaces; i++) output[i] = ' ';
  for (byte j = 0; j < inputLen; j++) output[i++] = input[j];
  for (byte j = 0; j < rightSpaces; j++)output[i++] = ' ';
  output[i] = '\0'; // Null-terminator
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

void MENU_TEXT_SAVED()
  {
  char msg[30];
  MENU_CLEAR();
  MENU_TEXT_ORTALA("SAVED", msg, 16);
  MENU_WRITE_TEXT(0, 24, msg); //0,14
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
          if (MENU_POINTER[MENU_INDEX_COUNTER].Funct != 0)
            {
            MENU_POINTER[MENU_INDEX_COUNTER].Funct(1, MENU_TEMP_VAL);
            MENU_TEXT_SAVED();
            WAIT_INTERRUPT(500);
            }
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

// </editor-fold>
