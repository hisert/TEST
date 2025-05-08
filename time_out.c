#include "time_out.h"
#define OVER_COUNT_RESCUER 0x7000
volatile word SYSTEM_TIME_OUT_COUNTER = 0;
extern void SYSTEM_CONTROL_ALL();

void TIME_OUT_COUNT_INTERRUPT()
  {
  SYSTEM_TIME_OUT_COUNTER++;
  if (SYSTEM_TIME_OUT_COUNTER > 0xF000) SYSTEM_TIME_OUT_COUNTER = SYSTEM_TIME_OUT_COUNTER - OVER_COUNT_RESCUER;
  }

byte TIME_OUT_CHECK(TIME_OUT_t *timeout, word outTime)
  {
  if (outTime == 0)
    {
    (timeout->time_out_time) = SYSTEM_TIME_OUT_COUNTER;
    return 0;
    }
  if (SYSTEM_TIME_OUT_COUNTER >= (timeout->time_out_time));
  else (timeout->time_out_time) = (timeout->time_out_time) - OVER_COUNT_RESCUER;
  if ((SYSTEM_TIME_OUT_COUNTER - (timeout->time_out_time)) >= outTime)
    {
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
  while (1)
    {
    if (flag) return 1;
    SYSTEM_CONTROL_ALL();
    if (TIME_OUT_CHECK(&ana_time_out, ana_ms)) return 0;
    if (TIME_OUT_CHECK(&second_time_out, second_ms)) flag = Funct_t();
    }
  }
