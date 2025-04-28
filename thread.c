#include "thread.h"

byte THREAD_NUM = 0;
byte thread_return_temp = 0;
THREAD_t THREAD_LIST[10];

// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT     ">

void THREAD_INTERRUPT()
  {
  for (byte threadIndex = 0; threadIndex < THREAD_NUM; threadIndex++)
    {
    if (THREAD_LIST[threadIndex].flag & THREAD_FLG_START)
      {
      if ((THREAD_LIST[threadIndex].flag & THREAD_FLG_READY) == 0)
        {
        if ((THREAD_LIST[threadIndex].duty_temp_time) > 1) (THREAD_LIST[threadIndex].duty_temp_time)--;
        else
          {
          THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag | THREAD_FLG_READY;
          THREAD_LIST[threadIndex].duty_temp_time = THREAD_LIST[threadIndex].duty_time;
          }
        }
      }
    }
  }

void THREAD_MAIN()
  {
  for (byte threadIndex = 0; threadIndex < THREAD_NUM; threadIndex++)
    {
    if ((THREAD_LIST[threadIndex].flag & THREAD_FLG_READY))
      {
      THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag &= ~THREAD_FLG_READY;
      THREAD_LIST[threadIndex].Funct(threadIndex);
      }
    }
  }

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USER FUNCT        ">

void THREAD_START(byte threadIndex)
  {
  THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag | THREAD_FLG_START;
  }

void THREAD_STOP(byte threadIndex)
  {
  THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag & ~THREAD_FLG_START;
  }

void THREAD_DONE_CONTROL(byte threadIndex)
  {
  if ((THREAD_LIST[threadIndex].flag & THREAD_FLG_LOOP) == 0) THREAD_LIST[threadIndex].flag = THREAD_LIST[threadIndex].flag & ~THREAD_FLG_START;
  }

void THREAD_TIME(byte threadIndex, word threadTime)
  {
  THREAD_LIST[threadIndex].duty_time = threadTime;
  THREAD_LIST[threadIndex].duty_temp_time = threadTime;
  }

void THREAD_CREATE(byte threadIndex, byte flag, byte duty_time, void (*Funct_t)(byte threadIndex))
  {
  THREAD_LIST[threadIndex].Funct = Funct_t;
  THREAD_LIST[threadIndex].flag = flag;
  THREAD_LIST[threadIndex].duty_time = duty_time;
  THREAD_NUM++;
  }

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="USER FUNCT        ">

void THREAD_TIME_START(THREAD_DELAY *thread)
  {
  (thread->sleep_state_counter) = 1;
  }

byte THREAD_TIME_WAIT(THREAD_DELAY *thread, word threadTime)
  {
  byte activeSleepNum = (thread->flag);
  byte sleepNum = (thread->sleep_state_counter);
  (thread->sleep_state_counter) = (thread->sleep_state_counter) + 1;
  if (activeSleepNum == 0)
    {
    (thread->flag) = (thread->flag) + sleepNum;
    (thread->duty_time) = threadTime - 1;
    thread_return_temp = THREAD_FUNCT_FIRST;
    return THREAD_FUNCT_FIRST;
    }
  else if (activeSleepNum == sleepNum)
    {
    if ((thread->duty_time) > 1)
      {
      (thread->duty_time)--;
      thread_return_temp = THREAD_FUNCT_ALWAYS;
      return THREAD_FUNCT_ALWAYS;
      }
    else
      {
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