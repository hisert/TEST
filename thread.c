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

// <editor-fold defaultstate="collapsed" desc="SIRALI TIME OUT        ">
#define SYSTEM_FUNCT_ALWAYS 1
#define SYSTEM_FUNCT_LAST 2
#define SYSTEM_FUNCT_FIRST 3

#define SYSTEM_FUNCT_KOMUT_WORK 1
#define SYSTEM_FUNCT_KOMUT_CLEAN 2
#define SYSTEM_FUNCT_NEXT 3
byte SYSTEM_FUNCT_RETURN = 0;

byte SYSTEM_FUNCT(SIRALI_TIME_OUT_t *SIRALI_TIME, word TIME_TUTUCU_MS, byte komut)
{
    if (komut == SYSTEM_FUNCT_NEXT) (SIRALI_TIME->flag) = (SIRALI_TIME->flag) & ~(SIRALI_TIME->temp);
    if (komut == SYSTEM_FUNCT_KOMUT_WORK) {
        if ((SIRALI_TIME->temp) == 0) if ((SIRALI_TIME->flag) == 0) TIME_OUT_RESET(&(SIRALI_TIME->time_out));
        (SIRALI_TIME->temp) = (SIRALI_TIME->temp) + 1;
        if (((SIRALI_TIME->flag)) == 0) {
            (SIRALI_TIME->flag) = (SIRALI_TIME->flag) | (SIRALI_TIME->temp);
            SYSTEM_FUNCT_RETURN = SYSTEM_FUNCT_FIRST;
            return SYSTEM_FUNCT_FIRST;
        }
        if (((SIRALI_TIME->flag)) == (SIRALI_TIME->temp)) {
            if (TIME_OUT_CHECK(&(SIRALI_TIME->time_out), TIME_TUTUCU_MS)) {
                (SIRALI_TIME->flag) = (SIRALI_TIME->flag) & ~(SIRALI_TIME->temp);
                SYSTEM_FUNCT_RETURN = SYSTEM_FUNCT_LAST;
                return SYSTEM_FUNCT_LAST;
            } else {
                SYSTEM_FUNCT_RETURN = SYSTEM_FUNCT_ALWAYS;
                return SYSTEM_FUNCT_ALWAYS;
            }
        }
    }
    if (komut == SYSTEM_FUNCT_KOMUT_CLEAN) (SIRALI_TIME->temp) = 0;
    SYSTEM_FUNCT_RETURN = 0;
    return 0;
}

byte SYSTEM_FUNCT_GET_STATE()
{
    return SYSTEM_FUNCT_RETURN;
}

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="THREAD     ">

byte THREAD_CHECK(THREAD_t *thread_t)
{
    byte temp = 0;
    if ((thread_t->flag) & THREAD_FLG_START) {
        if (TIME_OUT_CHECK(&(thread_t->temp), thread_t->duty_time)) thread_t->flag = thread_t->flag | THREAD_FLG_READY;
        if ((thread_t->flag) & THREAD_FLG_READY) {
            thread_t->flag = thread_t->flag & ~THREAD_FLG_READY;


            if (((thread_t->flag) & THREAD_FLG_IN_FUNCT) == 0) {
            }
            temp = thread_t->Funct();
            if (((thread_t->flag) & THREAD_FLG_LOOP));
            else if (temp)(thread_t->flag) = (thread_t->flag) & ~THREAD_FLG_START;
        }
    }
    return temp;
}

void THREAD_INIT(THREAD_t *thread_t, byte flag, word duty_time, byte(*Funct_t)(void))
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
