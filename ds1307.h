#include "common.h"

#ifndef DS1307_H
#define	DS1307_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef USE_DS1307

    typedef struct {
        byte second;
        byte minute;
        byte hour;
        byte dayOfWeek; // 1=Mon ... 7=Sun
        byte day;
        byte month;
        word year;
    } DS1307_time_t;

    void DS1307_Init(void (*startFunc)(void), byte(*writeFunc)(byte), byte(*read_ack)(void), byte(*read_nack)(void), void(*stopFunc)(void));
    void DS1307_SetTime(byte hour, byte minute, byte second);
    void DS1307_SetDate(byte dayOfWeek, byte day, byte month, word year);
    void DS1307_GetDateTime();

#endif


#ifdef	__cplusplus
}
#endif

#endif	/* DS1307_H */

