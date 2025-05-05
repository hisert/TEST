#include "register.h"
#include "eeprom.h"

#define MAX_REG 10
word RANDCODE = 0;
byte UNLOCK_STARTED = 0;
REG_t REGS[MAX_REG];
//
//byte(*epr_rd)(word);
//void (*epr_wr)(word, byte);
//
//
//// <editor-fold defaultstate="collapsed" desc="LIBRARY CONFIG">
//#define CARD_SYMBOL 'Q'
//#define CARD_RETURN 'R'
//#define EEPROM_OFFSET_VAL        02
//#define CARD_VER                 1
//#define PROTOCOL_START '<'
//#define PROTOCOL_STOP '>'
//
//dword REG_GET(byte regID)
//{
//    return REGS[regID].rg_value;
//}
//
//word REG_GET_MAGIC_NUM()
//{
//    return ( (epr_rd(0)) + (epr_rd(1) * 256));
//}
//
//void REG_SET_MAGIC_NUM()
//{
//    epr_wr(0, 'D');
//    epr_wr(1, 'D');
//}
//
//void REG_RANDCODE()
//{
//    do {
//        REG_DATA.randcode = ((word) (rand())&0xFFFF);
//    } while (!(REG_DATA.randcode));
//}
//// </editor-fold> 
//// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT ">
//
//
////-------------------------------------------------
//
//byte REG_VAL_TO_CHAR(byte val)
//{
//    if (val < 10) return val = '0' + val;
//    else return val = 'A' + val - 10;
//}
//
//byte REG_GET_REG_SIZE(byte regID)
//{
//    byte value = ((REGS[regID].rg_flag & 0b00110000) >> 4) + 1;
//    if (value == 1) return 1;
//    if (value == 2) return 2;
//    if (value == 3) return 4;
//    if (value == 4) return 8;
//    return 0;
//}
//
//void REG_FUCT(byte regID)
//{
//    if (REGS[regID].funct != 0)(REGS[regID].funct(regID));
//}
//
//byte REG_is_flag(byte regID, dword regFlag)
//{
//    if (FLAG_CONTROL(REGS[regID].rg_flag, regFlag)) return 1;
//    else return 0;
//}
//
//dword REG_HEX_TO_VAL(byte*c, byte len)
//{
//    dword val;
//    byte c1;
//    val = 0;
//    while (len--) {
//        c1 = *c;
//        c++;
//        if (c1 >= '0' && c1 <= '9') c1 = c1 - '0';
//        else if (c1 >= 'A' && c1 <= 'F') c1 = c1 - 'A' + 10;
//        else if (c1 >= 'a' && c1 <= 'f') c1 = c1 - 'a' + 10;
//
//        else break;
//        val = (val << 4) | c1;
//    }
//    return val;
//}
//
//dword REG_DEC_TO_VAL(byte *data, byte len)
//{
//    dword value = 0;
//    for (byte x = 0; x < len; x++) {
//        value *= 10;
//        value += ((data[x]) - '0');
//    }
//    return value;
//}
//
//byte REG_GET_REG_OUT_VALUE(byte regID)
//{
//    return ((REGS[regID].rg_flag & 0b00001111) + 1);
//}
//
//void REG_CURRENT_ADD(byte data)
//{
//    REG_DATA.CURRENT.out[REG_DATA.CURRENT.outCounter ] = data;
//    (REG_DATA.CURRENT.outCounter)++;
//}
//
//void REG_EEPROM_WRITE(byte regID)
//{
//    dword value = REGS[regID].rg_value;
//    byte REG_SIZE_Value = REG_GET_REG_SIZE(regID);
//    for (signed char x = (signed char) REG_SIZE_Value; x > 0; x--) {
//
//        epr_wr(((REGS[regID].rg_address) + REG_SIZE_Value - x), (value & 0xFF));
//        value = value >> 8;
//    }
//}
//
//dword REG_EEPROM_READ(byte regID)
//{
//    dword value = 0;
//    byte REG_SIZE_Value = REG_GET_REG_SIZE(regID);
//    for (signed char x = (signed char) REG_SIZE_Value; x > 0; x--) {
//
//        value = value << 8;
//        value |= (epr_rd((word) ((REGS[regID].rg_address + (byte) x) - 1)));
//    }
//    return value;
//}
//
//void REG_GET_FROM_EEPROM(byte regID)
//{
//    REGS[regID].rg_value = REG_EEPROM_READ(regID);
//}
//
//byte REG_INIT(byte(*ep_rd_funct)(word), void (*ep_wr_funct)(word, byte))
//{
//    byte reg_address_counter = EEPROM_OFFSET_VAL;
//    (epr_rd) = (ep_rd_funct);
//    (epr_wr) = (ep_wr_funct);
//    for (byte regID = 0; regID < REGx_NAMES_NUM; regID++) {
//        REGS[regID].rg_address = reg_address_counter;
//        REGS[regID].funct = 0;
//        byte REG_SIZE_Value = REG_GET_REG_SIZE(regID);
//        if (REG_SIZE_Value == 1) reg_address_counter += 1;
//        else if (REG_SIZE_Value == 2) reg_address_counter += 2;
//        else if (REG_SIZE_Value == 4) reg_address_counter += 4;
//        else if (REG_SIZE_Value == 8) reg_address_counter += 8;
//
//    }
//    if (REG_GET_MAGIC_NUM() != 0x4444) {
//        for (byte regID = 0; regID < REGx_NAMES_NUM; regID++) {
//            if (REG_is_flag(regID, REG_NV)) {
//                REG_EEPROM_WRITE(regID); // ILK VE TEK SEFER EEPROM'A YAZ
//            }
//        }
//        REG_SET_MAGIC_NUM();
//        return 1;
//    } else {
//        for (byte regID = 0; regID < REGx_NAMES_NUM; regID++) {
//            if (REG_is_flag(regID, REG_NV)) REG_GET_FROM_EEPROM(regID); // EPROOM KULLANIYORSA OKU VE RAM'E YAZ
//        }
//    }
//    return 0;
//}
//
//void REG_CONNECT_FUNC(byte regID, void(*funct)(byte))
//{
//    (
//            REGS[regID].funct) = (funct);
//}
//
////-------------------------------------------------
//
//// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="USER FUNCT    ">
//
//void REG_CURRENT_DATA_DONE(void)
//{
//
//    REG_DATA.CURRENT.out[REG_DATA.CURRENT.outCounter ] = 0;
//}
//
//void REG_CURRENT_DATA_CLEAR(void)
//{
//    (
//            REG_DATA.CURRENT.outCounter) = 0;
//}
//
//void REG_SET(byte regID, dword val)
//{
//
//    REGS[regID].rg_value = val;
//}
//
//byte *REG_CURRENT_DATA_GET(void)
//{
//
//    return &(REG_DATA.CURRENT.out);
//}
//
//byte REG_CURRENT_MAX_CONTROL(void)
//{
//    if (REG_DATA.CURRENT.giveRegID >= REGx_NAMES_NUM) {
//
//        if (REG_DATA.CURRENT.giveRegID != 0xFF); //BUZZER_PWM_TONE_ENTRY(tone_ERROR, 1);
//        return 0;
//    }
//    return 1;
//}
//
//void REG_CURRENT_DATA_UPDATE(void)
//{
//
//    REG_DATA.CURRENT.giveAdress = (word) REG_HEX_TO_VAL(REG_DATA.CURRENT.data + 2, 4);
//    REG_DATA.CURRENT.giveSlaveVal = (byte) REG_HEX_TO_VAL(REG_DATA.CURRENT.data + 6, 2);
//    REG_DATA.CURRENT.giveRegID = (byte) REG_HEX_TO_VAL(REG_DATA.CURRENT.data + 8, 2);
//    REG_DATA.CURRENT.giveCardSymbol = REG_DATA.CURRENT.data[1];
//    REG_DATA.CURRENT.giveVal = 0;
//    REG_DATA.CURRENT.mySlaveVal = (byte) REG_GET(REGx_SLAVE_ADRESS);
//    REG_DATA.CURRENT.myAdress = (word) REG_GET(REGx_ADDR);
//    REG_DATA.CURRENT.myCardSymbol = CARD_SYMBOL;
//}
//
//byte REG_CURRENT_DATA_CHECK(void)
//{
//    if ((REG_DATA.CURRENT.myCardSymbol) == (REG_DATA.CURRENT.giveCardSymbol)) {
//        if (!(REG_DATA.CURRENT.giveAdress)) {
//            if ((REG_DATA.CURRENT.giveRegID) == (REGx_RAND_CODE)) return 1;
//        }
//        if ((REG_DATA.CURRENT.giveRegID == (REGx_ADDR)) || (REG_DATA.CURRENT.giveRegID == (REGx_SLAVE_ADRESS))) {
//            if ((REG_DATA.UNLOCK)) return 1;
//            else return 0;
//        }
//        if (((REG_DATA.CURRENT.giveAdress) != (REG_DATA.CURRENT.myAdress)));
//        else if (((REG_DATA.CURRENT.mySlaveVal) != (REG_DATA.CURRENT.giveSlaveVal)));
//
//        else return 1;
//        return 0;
//
//    }
//    return 0;
//}
//
//void REG_CURRENT_DATA_CHAR(byte data)
//{
//
//    REG_CURRENT_ADD(data);
//}
//
//void REG_CURRENT_DATA_STR(const char *msg)
//{
//    while ((*msg) != 0) {
//
//        REG_CURRENT_DATA_CHAR(*msg);
//        msg++;
//    }
//}
//
//void REG_CURRENT_DATA_HEX(byte hex)
//{
//
//    char msg[3];
//    sprintf(msg, "%.2X", hex);
//    REG_CURRENT_DATA_STR(msg);
//}
//
//void REG_READ_STRx(byte regID)
//{
//    dword value = REG_GET(regID);
//    byte REG_OUT_Value = REG_GET_REG_OUT_VALUE(regID);
//    byte REG_SIZE_Value = REG_GET_REG_SIZE(regID);
//    byte REG_OUT_Type = ((REGS[regID].rg_flag & 0b10000000) >> 7) + 1; //0 HEX 1 DEC +1 = 1 HEX 2 DEC
//    byte temp[8];
//    char msg[20];
//    if (REG_OUT_Type == 2) {
//        if (REG_OUT_Value == 1) sprintf(msg, "%.1lu", value);
//        else if (REG_OUT_Value == 2) sprintf(msg, "%.2lu", value);
//        else if (REG_OUT_Value == 3) sprintf(msg, "%.3lu", value);
//        else if (REG_OUT_Value == 4) sprintf(msg, "%.4lu", value);
//        else if (REG_OUT_Value == 5) sprintf(msg, "%.5lu", value);
//        else if (REG_OUT_Value == 6) sprintf(msg, "%.6lu", value);
//        else if (REG_OUT_Value == 7) sprintf(msg, "%.7lu", value);
//        else if (REG_OUT_Value == 8) sprintf(msg, "%.8lu", value);
//        else if (REG_OUT_Value == 9) sprintf(msg, "%.9lu", value);
//        else if (REG_OUT_Value == 10) sprintf(msg, "%.10lu", value);
//    } else if (REG_OUT_Type == 1) {
//        if (REG_SIZE_Value == 1) sprintf(msg, "%.2lX", value);
//        else if (REG_SIZE_Value == 2) sprintf(msg, "%.4lX", value);
//        else if (REG_SIZE_Value == 4) sprintf(msg, "%.8lX", value);
//        else
//
//            if (REG_SIZE_Value == 8) sprintf(msg, "%.1l6X", value);
//    }
//    REG_CURRENT_DATA_STR(msg);
//}
//
//// </editor-fold>

void REGISTER_INIT(void (*eeprom_byte_write_t)(word adress, byte data), byte(*eeprom_byte_read_t)(word adress))
{
    EEPROM_INIT(eeprom_byte_write_t, eeprom_byte_read_t);
    if (EEPROM_GET(MAX_REG + 1) != 0xABCD) {
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

void REG_FUNC(byte regId, dword val, byte komut)
{
    REGS[regId].funct(val, komut);
}

void REG_CREATE(byte regId, void (*funct_t)(dword, byte), word flag_t, dword val_t, dword max_t, dword min_t)
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

    if (start != NULL && end != NULL && start < end) {
        start++; // ':' karakterinden sonraki konuma geç
        while (start < end) {
            *dst++ = *start++;
        }
        *dst = '\0'; // sonland?r?c? ekle
    } else *dst = '\0'; // hata durumunda dst'yi bo? yaparak
}

dword REG_CONVERT_STR_HEX_TO_DWORD(const char* str)
{
    dword result = 0;
    char c;
    while ((c = *str++) != '\0') {
        result <<= 4; // 4 bit sola kayd?r
        if (c >= '0' && c <= '9') {
            result |= (c - '0');
        } else if (c >= 'A' && c <= 'F') {
            result |= (c - 'A' + 10);
        } else if (c >= 'a' && c <= 'f') {
            result |= (c - 'a' + 10);
        } else {
            // Geçersiz karakter durumunda burada hata yönetimi ekleyebilirsin
        }
    }
    return result;
}

dword REG_CONVERT_STR_DEC_TO_DWORD(const char* str)
{
    dword result = 0;
    char c;

    while ((c = *str++) != '\0') {
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        } else {
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
    if (length <= val_len) {
        for (i = 0; i < val_len; i++) out_str[i] = temp[i];
        out_str[val_len] = '\0';
    } else {
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

    if (length <= val_len) {
        for (i = 0; i < val_len; i++) out_str[i] = temp[i];
        out_str[val_len] = '\0';
    } else {
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

void REG_PARSE_INDEX(const char* src, char* out, byte start, byte stop)
{
    byte i = 0;
    while (start <= stop && src[start] != '\0') out[i++] = src[start++];
    out[i] = '\0'; // null sonland?r?c?
}

byte REG_PARSE_COMPARE(const char* str1, const char* str2)
{
    while (*str1 && *str2) {
        if (*str1 != *str2) return 1;
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0') ? 0 : 1;
}

word REG_GET_FLAG(byte regId)
{
    return REGS[regId].flag;
}

void REG_TX_ADD(char* input, const char* data)
{
    while (*input) input++;
    while (*data) *input++ = *data++;
    *input = '\0';
}

void REG_CHANGE_RANDCODE()
{
    if (UNLOCK_STARTED) {
        do {
            RANDCODE = ((word) (rand())&0xFFFF);
        } while (!(RANDCODE));
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