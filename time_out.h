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
    byte TIME_OUT_FUNCT(word ms, byte(Funct) (byte flag));

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_OUT_H */

