#include "thread.h"


// <editor-fold defaultstate="collapsed" desc="TIME OUT         ">
word SYSTEM_TIME_OUT_COUNTER = 0;
extern void SYSTEM_CONTROL_ALL();

void TIME_OUT_COUNT_INTERRUPT()
{
    if (SYSTEM_TIME_OUT_COUNTER == 0xFFFF) SYSTEM_TIME_OUT_COUNTER = 0;
    SYSTEM_TIME_OUT_COUNTER++;
}

byte TIME_OUT_RESET(TIME_OUT_t *timeout)
{
    (timeout->time_out_time) = SYSTEM_TIME_OUT_COUNTER;
}

byte TIME_OUT_CHECK(TIME_OUT_t *timeout, word outTime)
{
    if ((word) (SYSTEM_TIME_OUT_COUNTER - (timeout->time_out_time)) >= outTime) {
        (timeout->time_out_time) = SYSTEM_TIME_OUT_COUNTER;
        return 1;
    }
    return 0;
}

byte TIME_OUT_FUNCT(word ana_ms, byte(*Funct_t)(void), word second_ms)
{
    byte flag = 0;
    static TIME_OUT_t ana_time_out;
    static TIME_OUT_t second_time_out;
    TIME_OUT_CHECK(&ana_time_out, 0);
    TIME_OUT_CHECK(&second_time_out, 0);
    flag = Funct_t();
    while (1) {
        if (flag) return 1;
        SYSTEM_CONTROL_ALL();
        if (TIME_OUT_CHECK(&ana_time_out, ana_ms)) return 0;
        if (TIME_OUT_CHECK(&second_time_out, second_ms)) flag = Funct_t();
    }
}

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="THREAD     ">

void THREAD_CHECK(THREAD_t *thread_t)
{
    if ((thread_t->flag) & THREAD_FLG_START) {
        if (TIME_OUT_CHECK(&(thread_t->temp), thread_t->duty_time)) thread_t->flag = thread_t->flag | THREAD_FLG_READY;
        if ((thread_t->flag) & THREAD_FLG_READY) {
            thread_t->flag = thread_t->flag & ~THREAD_FLG_READY;
            thread_t->Funct();
            if (((thread_t->flag) & THREAD_FLG_LOOP) == 0) (thread_t->flag) = (thread_t->flag) & ~THREAD_FLG_START;
        }
    }
}

void THREAD_INIT(THREAD_t *thread_t, byte flag, word duty_time, void (*Funct_t)(void))
{
    thread_t->Funct = Funct_t;
    thread_t->flag = flag;
    thread_t->duty_time = duty_time;
}

void THREAD_START(THREAD_t *thread_t)
{
    thread_t->flag = thread_t->flag | THREAD_FLG_START;
}

void THREAD_STOP(THREAD_t *thread_t)
{
    thread_t->flag = thread_t->flag & ~THREAD_FLG_START;
}

byte THREAD_is_START(THREAD_t *thread_t)
{
    if ((thread_t->flag) & THREAD_FLG_START) return 1;
    else return 0;
}

void THREAD_TIME_RESET(THREAD_t *thread_t)
{
    TIME_OUT_RESET(&thread_t);
}

void THREAD_ARRAY_CHECK(THREAD_t *array, size_t length)
{
    for (size_t i = 0; i < length; i++) THREAD_CHECK(&array[i]);
}
// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="THREAD TIME         ">
// <editor-fold defaultstate="collapsed" desc="USER FUNCT        ">
byte thread_return_temp = 0;

void THREAD_TIME_START(THREAD_DELAY *thread)
{
    (
            thread->sleep_state_counter) = 1;
}

byte THREAD_TIME_WAIT(THREAD_DELAY *thread, word threadTime)
{
    byte activeSleepNum = (thread->flag);
    byte sleepNum = (thread->sleep_state_counter);
    (thread->sleep_state_counter) = (thread->sleep_state_counter) + 1;
    if (activeSleepNum == 0) {
        (thread->flag) = (thread->flag) + sleepNum;
        (thread->duty_time) = threadTime - 1;
        thread_return_temp = THREAD_FUNCT_FIRST;
        return THREAD_FUNCT_FIRST;
    } else if (activeSleepNum == sleepNum) {
        if ((thread->duty_time) > 1) {
            (thread->duty_time)--;
            thread_return_temp = THREAD_FUNCT_ALWAYS;
            return THREAD_FUNCT_ALWAYS;
        } else {
            (thread->flag) = (thread->flag) & ~sleepNum;
            thread_return_temp = THREAD_FUNCT_LAST;
            return THREAD_FUNCT_LAST;
        }
    }
    thread_return_temp = 0;

    return 0;
}

byte THREAD_TIME_DONE(THREAD_DELAY *thread)
{
    if (thread->flag == 0) return 1;

    else return 0;
}

void THREAD_CLEAR(THREAD_DELAY *thread)
{

    thread->flag = 0;
}

byte THREAD_GET_STATE()
{
    return thread_return_temp;
}
// </editor-fold> 
// </editor-fold> 

