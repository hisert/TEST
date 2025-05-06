#include "register.h"
#include "eeprom.h"

#define MAX_REG 10
word RANDCODE = 0;
byte UNLOCK_STARTED = 0;
REG_t REGS[MAX_REG];

void REGISTER_INIT(void (*eeprom_byte_write_t)(word adress, byte data), byte(*eeprom_byte_read_t)(word adress))
  {
  EEPROM_INIT(eeprom_byte_write_t, eeprom_byte_read_t);
  if (EEPROM_GET(MAX_REG + 1) != 0xABCD)
    {
    for (byte regId = 0; regId < MAX_REG; regId++) if ((REGS[regId].flag) & RG_NV) REG_EEPROM_SET(regId);
    EEPROM_SET(MAX_REG + 1, 0xABCD);
    }
  for (byte regId = 0; regId < MAX_REG; regId++) if ((REGS[regId].flag) & RG_NV) REG_EEPROM_GET(regId);
  }

dword REG_GET(byte regId)
  {
  return REGS[regId].val;
  }

void REG_SET(byte regId, dword val)
  {
  if (REGS[regId].val > REGS[regId].max) return;
  else if (REGS[regId].val < REGS[regId].min) return;
  REGS[regId].val = val;
  }

void REG_EEPROM_SET(byte regId)
  {
  EEPROM_SET(regId, REG_GET(regId));
  }

void REG_EEPROM_GET(byte regId)
  {
  REGS[regId].val = EEPROM_GET(regId);
  }

word REG_GET_FLAG(byte regId)
  {
  return REGS[regId].flag;
  }

void REG_FUNC(byte regId, byte komut)
  {
  if (REGS[regId].funct != 0) REGS[regId].funct(regId, komut);
  }

void REG_CREATE(byte regId, void (*funct_t)(byte, byte), word flag_t, dword val_t, dword max_t, dword min_t)
  {
  REGS[regId].funct = funct_t;
  REGS[regId].flag = flag_t;
  REGS[regId].val = val_t;
  REGS[regId].max = max_t;
  REGS[regId].min = min_t;
  }

void REG_PARSE_DATA(const char* src, char* dst)
  {
  const char* start = strchr(src, ':');
  const char* end = strchr(src, '>');

  if (start != NULL && end != NULL && start < end)
    {
    start++; // ':' karakterinden sonraki konuma geç
    while (start < end)
      {
      *dst++ = *start++;
      }
    *dst = '\0'; // sonland?r?c? ekle
    }
  else *dst = '\0'; // hata durumunda dst'yi bo? yaparak
  }

void REG_PARSE_INDEX(const char* src, char* out, byte start, byte stop)
  {
  byte i = 0;
  while (start <= stop && src[start] != '\0') out[i++] = src[start++];
  out[i] = '\0'; // null sonland?r?c?
  }

byte REG_PARSE_COMPARE(const char* str1, const char* str2)
  {
  while (*str1 && *str2)
    {
    if (*str1 != *str2) return 1;
    str1++;
    str2++;
    }
  return (*str1 == '\0' && *str2 == '\0') ? 0 : 1;
  }

void REG_TX_ADD(char* input, const char* data)
  {
  while (*input) input++;
  while (*data) *input++ = *data++;
  *input = '\0';
  }

void REG_CHANGE_RANDCODE()
  {
  if (UNLOCK_STARTED)
    {
    do
      {
      RANDCODE = ((word) (rand())&0xFFFF);
      }
    while (!(RANDCODE));
    }
  }

word REG_GET_RANDCODE()
  {
  return RANDCODE;
  }

void REG_SET_UNLOCK_START()
  {
  UNLOCK_STARTED = 1;
  }

void REG_SET_UNLOCK_STOP()
  {
  UNLOCK_STARTED = 0;
  }

byte REG_GET_UNLOCK()
  {
  return UNLOCK_STARTED;
  }

dword REG_CONVERT_STR_HEX_TO_DWORD(const char* str)
  {
  dword result = 0;
  char c;
  while ((c = *str++) != '\0')
    {
    result <<= 4; // 4 bit sola kayd?r
    if (c >= '0' && c <= '9')
      {
      result |= (c - '0');
      }
    else if (c >= 'A' && c <= 'F')
      {
      result |= (c - 'A' + 10);
      }
    else if (c >= 'a' && c <= 'f')
      {
      result |= (c - 'a' + 10);
      }
    else
      {
      // Geçersiz karakter durumunda burada hata yönetimi ekleyebilirsin
      }
    }
  return result;
  }

dword REG_CONVERT_STR_DEC_TO_DWORD(const char* str)
  {
  dword result = 0;
  char c;

  while ((c = *str++) != '\0')
    {
    if (c >= '0' && c <= '9')
      {
      result = result * 10 + (c - '0');
      }
    else
      {
      // Geçersiz karakter durumunda burada hata yönetimi ekleyebilirsin
      }
    }
  return result;
  }

void REG_CONVERT_DWORD_TO_STR_DEC(dword value, char* out_str, byte length)
  {
  char temp[11];
  byte i, val_len;
  sprintf(temp, "%lu", (unsigned long) value);
  val_len = 0;
  while (temp[val_len] != '\0') val_len++;
  if (length <= val_len)
    {
    for (i = 0; i < val_len; i++) out_str[i] = temp[i];
    out_str[val_len] = '\0';
    }
  else
    {
    byte pad = length - val_len;
    for (i = 0; i < pad; i++) out_str[i] = '0';
    for (i = 0; i < val_len; i++) out_str[pad + i] = temp[i];
    out_str[length] = '\0';
    }
  }

void REG_CONVERT_DWORD_TO_STR_HEX(dword value, char* out_str, byte length)
  {
  char temp[9]; // uint32_t ? max 8 hex digit + null
  byte i, val_len;
  sprintf(temp, "%lX", (unsigned long) value);
  val_len = 0;
  while (temp[val_len] != '\0') val_len++;

  if (length <= val_len)
    {
    for (i = 0; i < val_len; i++) out_str[i] = temp[i];
    out_str[val_len] = '\0';
    }
  else
    {
    byte pad = length - val_len;
    for (i = 0; i < pad; i++) out_str[i] = '0';
    for (i = 0; i < val_len; i++) out_str[pad + i] = temp[i];
    out_str[length] = '\0';
    }
  }

void REG_PROCESS_GET_DATA_STR(byte regId, char* out_str)
  {
  if (REGS[regId].flag & RG_OUT_HEX_2) REG_CONVERT_DWORD_TO_STR_HEX(REGS[regId].val, out_str, 2);
  if (REGS[regId].flag & RG_OUT_HEX_4) REG_CONVERT_DWORD_TO_STR_HEX(REGS[regId].val, out_str, 4);
  if (REGS[regId].flag & RG_OUT_DEC_1) REG_CONVERT_DWORD_TO_STR_DEC(REGS[regId].val, out_str, 1);
  if (REGS[regId].flag & RG_OUT_DEC_2) REG_CONVERT_DWORD_TO_STR_DEC(REGS[regId].val, out_str, 2);
  if (REGS[regId].flag & RG_OUT_DEC_3) REG_CONVERT_DWORD_TO_STR_DEC(REGS[regId].val, out_str, 3);
  if (REGS[regId].flag & RG_OUT_DEC_4) REG_CONVERT_DWORD_TO_STR_DEC(REGS[regId].val, out_str, 4);
  if (REGS[regId].flag & RG_OUT_DEC_5) REG_CONVERT_DWORD_TO_STR_DEC(REGS[regId].val, out_str, 5);
  }

dword REG_PROCESS_GET_DATA_DEC(byte regId, const char* str)
  {
  if (REGS[regId].flag & RG_IN_HEX) return REG_CONVERT_STR_HEX_TO_DWORD(str);
  if (REGS[regId].flag & RG_IN_DEC) return REG_CONVERT_STR_DEC_TO_DWORD(str);
  }