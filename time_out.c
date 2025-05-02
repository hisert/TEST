#include "time_out.h"
#define OVER_COUNT_RESCUER 0x7000
volatile word SYSTEM_TIME_OUT_COUNTER = 0;

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

byte TIME_OUT_FUNCT(word ms, byte(Funct) (byte flag))
  {
  static TIME_OUT_t time_out;
  TIME_OUT_CHECK(&time_out, 0);
  Funct(1);
  while (TIME_OUT_CHECK(&time_out, ms) == 0)
    {
    SYSTEM_CONTROL_ALL();
    if (Funct(0)) return 1;
    }
  return 0;
  }
