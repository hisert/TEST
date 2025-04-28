#include "common.h"

#ifndef TASK_H
#define	TASK_H

#ifdef	__cplusplus
extern "C" {
#endif


#define TASK_FLG_START 0x01

    typedef struct {
        byte flag;
        void (*Funct)(byte taskIndex);
    } TASK_t;


    void TASK_MAIN();
    void TASK_START(byte taskIndex);
    void TASK_STOP(byte taskIndex);
    byte TASK_is_START(byte taskIndex);
    void TASK_CREATE(byte taskIndex, byte flag, void (*Funct)(byte taskIndex));


#ifdef	__cplusplus
}
#endif

#endif	/* TASK_H */

