#include "common.h"

#ifndef TIME_OUT_H
#define	TIME_OUT_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        word time_out_time;
    } TIME_OUT_t;



    void TIME_OUT_COUNT_INTERRUPT();
    byte TIME_OUT_CHECK(TIME_OUT_t *timeout, word outTime);
    byte TIME_OUT_FUNCT(word ana_ms, byte(*Funct_t)(void), word second_ms);

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_OUT_H */

