# 1 "task.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "task.c" 2
# 1 "./task.h" 1
# 16 "./task.h"
    typedef struct {
        unsigned char flag;
        void (*Funct)(unsigned char taskIndex);
    } TASK_t;


    void TASK_MAIN();
    void TASK_START(unsigned char taskIndex);
    void TASK_STOP(unsigned char taskIndex);
    unsigned char TASK_is_START(unsigned char taskIndex);
    void TASK_CREATE(unsigned char taskIndex, unsigned char flag, void (*Funct)(unsigned char taskIndex));
# 2 "task.c" 2
unsigned char TASK_NUM = 0;
TASK_t TASK_LIST[10];



void TASK_MAIN()
{
    for (unsigned char taskIndex = 0; taskIndex < TASK_NUM; taskIndex++) if (TASK_LIST[taskIndex].flag & 0x01) TASK_LIST[taskIndex].Funct(taskIndex);
}




void TASK_START(unsigned char taskIndex)
{
    TASK_LIST[taskIndex].flag |= 0x01;
}

void TASK_STOP(unsigned char taskIndex)
{
    TASK_LIST[taskIndex].flag &= ~0x01;
}

unsigned char TASK_is_START(unsigned char taskIndex)
{
    if (TASK_LIST[taskIndex].flag & 0x01) return 1;
    else return 0;
}

void TASK_CREATE(unsigned char taskIndex, unsigned char flag, void (*Funct)(unsigned char taskIndex))
{
    TASK_LIST[taskIndex].flag = flag;
    TASK_LIST[taskIndex].Funct = Funct;
    TASK_NUM++;
}
