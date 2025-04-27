# 1 "thread.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "thread.c" 2
# 1 "./thread.h" 1
# 18 "./thread.h"
    typedef struct {
        unsigned char flag;
        unsigned int duty_time;
        unsigned int duty_temp_time;
        void (*Funct)(unsigned char threadIndex);
    } THREAD_t;

    void THREAD_INTERRUPT();
    void THREAD_MAIN();
    void THREAD_START(unsigned char threadIndex);
    void THREAD_STOP(unsigned char threadIndex);
    void THREAD_DONE_CONTROL(unsigned char threadIndex);
    void THREAD_TIME(unsigned char threadIndex, unsigned int threadTime);
    void THREAD_CREATE(unsigned char threadIndex, unsigned char flag, unsigned char duty_time, void (*Funct_t)(unsigned char threadIndex));






    unsigned char thread_return_temp = 0;

    typedef struct {
        unsigned char flag;
        unsigned int duty_time;
        unsigned char sleep_state_counter;
    } THREAD_DELAY;

    void THREAD_TIME_START(THREAD_DELAY *thread);
    unsigned char THREAD_TIME_WAIT(THREAD_DELAY *thread, unsigned int threadTime);
    unsigned char THREAD_TIME_DONE(THREAD_DELAY *thread);
    void THREAD_CLEAR(THREAD_DELAY *thread);
    unsigned char THREAD_GET_STATE();
# 2 "thread.c" 2

unsigned char THREAD_NUM = 0;
THREAD_t THREAD_LIST[10];



void THREAD_INTERRUPT()
{
    for (unsigned char threadIndex = 0; threadIndex < THREAD_NUM; threadIndex++) {
        if (THREAD_LIST[threadIndex].flag & 0x01) {
            if ((THREAD_LIST[threadIndex].flag & 0x04) == 0) {
                if ((THREAD_LIST[threadIndex].duty_temp_time) > 1) (THREAD_LIST[threadIndex].duty_temp_time)--;
                else {
                    THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag | 0x04;
                    THREAD_LIST[threadIndex].duty_temp_time = THREAD_LIST[threadIndex].duty_time;
                }
            }
        }
    }
}

void THREAD_MAIN()
{
    for (unsigned char threadIndex = 0; threadIndex < THREAD_NUM; threadIndex++) {
        if ((THREAD_LIST[threadIndex].flag & 0x04)) {
            THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag &= ~0x04;
            THREAD_LIST[threadIndex].Funct(threadIndex);
        }
    }
}




void THREAD_START(unsigned char threadIndex)
{
    THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag | 0x01;
}

void THREAD_STOP(unsigned char threadIndex)
{
    THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag & ~0x01;
}

void THREAD_DONE_CONTROL(unsigned char threadIndex)
{
    if ((THREAD_LIST[threadIndex].flag & 0x08) == 0) THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag & ~0x01;
}

void THREAD_TIME(unsigned char threadIndex, unsigned int threadTime)
{
    THREAD_LIST[threadIndex].duty_time = threadTime;
    THREAD_LIST[threadIndex].duty_temp_time = threadTime;
}

void THREAD_CREATE(unsigned char threadIndex, unsigned char flag, unsigned char duty_time, void (*Funct_t)(unsigned char threadIndex))
{
    THREAD_LIST[threadIndex].Funct = Funct_t;
    THREAD_LIST[threadIndex].flag = flag;
    THREAD_LIST[threadIndex].duty_time = duty_time;
    THREAD_NUM++;
}





void THREAD_TIME_START(THREAD_DELAY *thread)
{
    (thread->sleep_state_counter) = 1;
}

unsigned char THREAD_TIME_WAIT(THREAD_DELAY *thread, unsigned int threadTime)
{
    unsigned char activeSleepNum = (thread->flag);
    unsigned char sleepNum = (thread->sleep_state_counter);
    (thread->sleep_state_counter) = (thread->sleep_state_counter) + 1;
    if (activeSleepNum == 0) {
        (thread->flag) = (thread->flag) + sleepNum;
        (thread->duty_time) = threadTime - 1;
        thread_return_temp = 0x01;
        return 0x01;
    } else if (activeSleepNum == sleepNum) {
        if ((thread->duty_time) > 1) {
            (thread->duty_time)--;
            thread_return_temp = 0x02;
            return 0x02;
        } else {
            (thread->flag) = (thread->flag) & ~sleepNum;
            thread_return_temp = 0x03;
            return 0x03;
        }
    }
    thread_return_temp = 0;
    return 0;
}

unsigned char THREAD_TIME_DONE(THREAD_DELAY *thread)
{
    if (thread->flag == 0) return 1;
    else return 0;
}

void THREAD_CLEAR(THREAD_DELAY *thread)
{
    thread->flag = 0;
}

unsigned char THREAD_GET_STATE()
{
    return thread_return_temp;
}
