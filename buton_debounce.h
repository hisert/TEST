#include "common.h"
#ifndef BUTON_DEBOUNCE_H
#define	BUTON_DEBOUNCE_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        word PressTime;
        byte Temp_Counter;
        byte Flag;
    } Buton_t;

#define BUTON_FREE 0x00
#define BUTON_PRESSING 0x01
#define BUTON_PRESSED 0x02

    byte BUTON_PROCESS(Buton_t *Buton, byte Buton_Val, byte Buton_Up_Time, byte Buton_Fall_Time);
    word BUTON_GET_TIME(Buton_t *Buton);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTON_DEBOUNCE_H */

