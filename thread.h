#include "common.h"
#ifndef THREAD_H
#define	THREAD_H

#ifdef	__cplusplus
extern "C" {
#endif


    // <editor-fold defaultstate="collapsed" desc="TIME OUT         ">

    typedef struct {
        word time_out_time;
    } TIME_OUT_t;

    void TIME_OUT_COUNT_INTERRUPT();
    byte TIME_OUT_RESET(TIME_OUT_t *timeout);
    byte TIME_OUT_CHECK(TIME_OUT_t *timeout, word outTime);
    byte TIME_OUT_FUNCT(word ana_ms, byte(*Funct_t)(void), word second_ms);
    // </editor-fold> 
    // <editor-fold defaultstate="collapsed" desc="THREAD         ">
#define THREAD_FLG_START 0x01
#define THREAD_FLG_READY 0x04
#define THREAD_FLG_LOOP 0x08

    typedef struct {
        byte flag;
        word duty_time;
        TIME_OUT_t temp;
        byte (*Funct)();
    } THREAD_t;


    void THREAD_INIT(THREAD_t *thread_t, byte flag, word duty_time, byte (*Funct_t)(void));
    void THREAD_START(THREAD_t *thread_t);
    void THREAD_STOP(THREAD_t *thread_t);
    byte THREAD_is_START(THREAD_t *thread_t);
    byte THREAD_CHECK(THREAD_t *thread_t);
    void THREAD_TIME_RESET(THREAD_t *thread_t);
    void THREAD_ARRAY_CHECK(THREAD_t *array, size_t length);
    // </editor-fold> 
    // <editor-fold defaultstate="collapsed" desc="THREAD TIME         ">
#define THREAD_FUNCT_FIRST 0x01
#define THREAD_FUNCT_ALWAYS 0x02
#define THREAD_FUNCT_LAST 0x03

    typedef struct {
        byte flag;
        word duty_time;
        byte sleep_state_counter;
    } THREAD_DELAY;

    void THREAD_TIME_START(THREAD_DELAY *thread);
    byte THREAD_TIME_WAIT(THREAD_DELAY *thread, word threadTime);
    byte THREAD_TIME_DONE(THREAD_DELAY *thread);
    void THREAD_CLEAR(THREAD_DELAY *thread);
    byte THREAD_GET_STATE();
    // </editor-fold> 

#ifdef	__cplusplus
}
#endif

#endif	/* THREAD_H */

