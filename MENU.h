#include "common.h"

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        const char *text;
        byte flag;
        word(*Funct)(byte komut, word data);
        word max;
        word min;
    } Menu_One;

#define MENU_FLAG_NEW_MENU 0x01
#define MENU_FLAG_VALUE 0x02
#define MENU_FLAG_SELECT 0x04
#define MENU_FLAG_SHOW_DATA 0x08
#define MENU_FLAG_REFRESH_DATA 0x10

#define PRESSED_OK 0x01
#define PRESSED_UP 0x02
#define PRESSED_DOWN 0x04
#define PRESSED_BACK 0x08
#define PRESSED_REFRESH 0x10


    // <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT DEFINE">

    void MENU_GIR(Menu_One *Menu, byte komut);
    void MENU_CIK();
    void MENU_PRINT_MSG(const char *datas);
    void MENU_SHOW_DATA_PRINT(const char *text, word data);
    void MENU_USE_SELECT(const char *ust_yazi, const char *data[], byte index);
    void MENU_USE_VAL(const char *ust_yazi, word data_max, word data_min, word data);
    void MENU_WORK(char MENU_MOVEMENT);
    void MENU_INIT(void (*MENU_CLEAR_t)(void), void (*MENU_UPDATE_t)(void), void(*MENU_WRITE_TEXT_t)(word, word, const char *), void(*MENU_WRITE_DEC_t)(word, word, dword));
    void MENU_ANA_INIT(Menu_One *MENU_ANA_MENU_ANA_t);
    void MENU_PROCESS();
    void MENU_BUTON_ADD(char process);
    void MENU_TEXT_ORTALA(const char* input, char* output, byte maxLen);
    Menu_One* MENU_POINTER_GET();
    void MENU_MAX_SET(byte val);
    void MENU_UST_YAZI_SET(const char *msg);
    void MENU_SELECT_LIST_SET(char **list);
    void MENU_FUNCT_CLEAR();
    void MENU_FUNCT_UPDATE();
    void(MENU_FUNCT_WRITE_DEC) (word x, word y, dword data);
    void(MENU_FUNCT_WRITE_TEXT) (word x, word y, const char *text);
    // </editor-fold>


#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

