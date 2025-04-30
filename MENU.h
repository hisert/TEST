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
    void MENU_TEXT_ORTALA(const char* input, char* output, byte maxLen);
    // </editor-fold>


#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

