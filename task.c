#include "task.h"
byte TASK_NUM = 0;
TASK_t TASK_LIST[10];

// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT ">

void TASK_MAIN()
{
    for (byte taskIndex = 0; taskIndex < TASK_NUM; taskIndex++) if (TASK_LIST[taskIndex].flag & TASK_FLG_START) TASK_LIST[taskIndex].Funct(taskIndex);
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USER FUNCT    ">

void TASK_START(byte taskIndex)
{
    TASK_LIST[taskIndex].flag |= TASK_FLG_START;
}

void TASK_STOP(byte taskIndex)
{
    TASK_LIST[taskIndex].flag &= ~TASK_FLG_START;
}

byte TASK_is_START(byte taskIndex)
{
    if (TASK_LIST[taskIndex].flag & TASK_FLG_START) return 1;
    else return 0;
}

void TASK_CREATE(byte taskIndex, byte flag, void (*Funct)(byte taskIndex))
{
    TASK_LIST[taskIndex].flag = flag;
    TASK_LIST[taskIndex].Funct = Funct;
    TASK_NUM++;
}
// </editor-fold> 