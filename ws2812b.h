#include "common.h"

#ifndef WS2812B_H
#define	WS2812B_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MY_RGB_RED   0x00FF00
#define MY_RGB_GREEN 0xFF0000
#define MY_RGB_BLUE  0x0000FF
#define MY_RGB_WHITE  0xFFFFFF
#define MY_RGB_SARI  MY_RGB_RED + MY_RGB_GREEN
#define MY_RGB_MOR  MY_RGB_RED + MY_RGB_BLUE 
#define MY_RGB_SIYAN  MY_RGB_GREEN + MY_RGB_BLUE 
#define MY_RGB_BEYAZ MY_RGB_RED + MY_RGB_GREEN + MY_RGB_BLUE


    void LED_INIT_PORT(byte *lat_adress_t, byte index_t);
    void LED_CLEAN();
    void LED_UPDATE();
    void LED_DATA_COPY_SINGLE(word dataLen, dword data);
    void LED_DATA_MASK(word dataStart, word dataLen, dword data);
    void LED_DATA_REVERSE(word dataLen);
    void LED_TOGGLE_DATA(byte index, word dataLen, dword data, byte fast);
    void LED_SLEEPING(byte index, word dataLen, dword data);
    void LED_SONSUZ_TUR(byte index, word dataLen, byte fast);
    void LED_DATA_METEOR_EKLE(word ledsayisi, dword data);
    void LED_DATA_CLEAN(void);

#ifdef	__cplusplus
}
#endif

#endif	/* WS2812B_H */

