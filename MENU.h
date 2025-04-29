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


#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

