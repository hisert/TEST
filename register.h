#include "common.h"
#include "eeprom.h"

#ifndef REGISTER_H
#define	REGISTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RG_IN_HEX 0x0001
#define RG_IN_DEC 0x0002
#define RG_OUT_HEX_2 0x0004
#define RG_OUT_HEX_4 0x0008
#define RG_OUT_DEC_1 0x0010
#define RG_OUT_DEC_2 0x0020
#define RG_OUT_DEC_3 0x0040
#define RG_OUT_DEC_4 0x0080
#define RG_OUT_DEC_5 0x0100
#define RG_WR 0x0200
#define RG_RD 0x0400
#define RG_NV 0x0800
#define RG_FNC 0x1000
#define RG_EN 0x2000
#define RG_MAIN 0x4000

    typedef struct {
        word flag;
        dword val;
        dword max;
        dword min;
        void (*funct)(byte regId, byte komut);
    } REG_t;



    void REGISTER_INIT(void (*eeprom_byte_write_t)(word adress, byte data), byte(*eeprom_byte_read_t)(word adress));
    dword REG_GET(byte regId);
    void REG_SET(byte regId, dword val);
    void REG_EEPROM_SET(byte regId);
    void REG_EEPROM_GET(byte regId);
    word REG_GET_FLAG(byte regId);
    void REG_FUNC(byte regId, byte komut);

    void REG_CREATE(byte regId, void (*funct_t)(byte, byte), word flag_t, dword val_t, dword max_t, dword min_t);
    void REG_TX_ADD(char* input, const char* data);

    void REG_PARSE_DATA(const char* src, char* dst);
    void REG_PARSE_INDEX(const char* src, char* out, byte start, byte stop);
    byte REG_PARSE_COMPARE(const char* str1, const char* str2);

    void REG_CHANGE_RANDCODE();
    word REG_GET_RANDCODE();
    void REG_SET_UNLOCK_START();
    void REG_SET_UNLOCK_STOP();
    byte REG_GET_UNLOCK();

    dword REG_CONVERT_STR_HEX_TO_DWORD(const char* str);
    dword REG_CONVERT_STR_DEC_TO_DWORD(const char* str);
    void REG_CONVERT_DWORD_TO_STR_DEC(dword value, char* out_str, byte length);
    void REG_CONVERT_DWORD_TO_STR_HEX(dword value, char* out_str, byte length);
    void REG_PROCESS_GET_DATA_STR(byte regId, char* out_str);
    dword REG_PROCESS_GET_DATA_DEC(byte regId, const char* str);

#ifdef	__cplusplus
}
#endif

#endif	/* REGISTER_H */

