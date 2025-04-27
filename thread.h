
#ifndef THREAD_H
#define	THREAD_H

#ifdef	__cplusplus
extern "C" {
#endif

#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#define qword unsigned long long

#define THREAD_FLG_START 0x01
#define THREAD_FLG_READY 0x04
#define THREAD_FLG_LOOP 0x08

    typedef struct {
        byte flag;
        word duty_time;
        word duty_temp_time;
        void (*Funct)(byte threadIndex);
    } THREAD_t;

    void THREAD_INTERRUPT();
    void THREAD_MAIN();
    void THREAD_START(byte threadIndex);
    void THREAD_STOP(byte threadIndex);
    void THREAD_DONE_CONTROL(byte threadIndex);
    void THREAD_TIME(byte threadIndex, word threadTime);
    void THREAD_CREATE(byte threadIndex, byte flag, byte duty_time, void (*Funct_t)(byte threadIndex));


#define THREAD_FUNCT_FIRST 0x01
#define THREAD_FUNCT_ALWAYS 0x02
#define THREAD_FUNCT_LAST 0x03

    byte thread_return_temp = 0;

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

#ifdef	__cplusplus
}
#endif

#endif	/* THREAD_H */

