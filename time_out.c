#include "time_out.h"
#define OVER_COUNT_RESCUER 0xF0000000
volatile dword SYSTEM_TIME_OUT_COUNTER = 0xF0000000;

void TIME_OUT_COUNT_INTERRUPT()
  {
  SYSTEM_TIME_OUT_COUNTER++;
  if (SYSTEM_TIME_OUT_COUNTER > 0xF0000000) SYSTEM_TIME_OUT_COUNTER = SYSTEM_TIME_OUT_COUNTER - 0xF0000000;
  }

byte TIME_OUT_CHECK(TIME_OUT_t *timeout, word outTime)
  {
  dword fark = 0;
  if (SYSTEM_TIME_OUT_COUNTER >= (timeout->time_out_time)) fark = SYSTEM_TIME_OUT_COUNTER - (timeout->time_out_time);
  else
    {
    (timeout->time_out_time) = (timeout->time_out_time) - OVER_COUNT_RESCUER;
    fark = SYSTEM_TIME_OUT_COUNTER - (timeout->time_out_time);
    }
  if (fark > outTime) return 1;
  else return 0;
  }

byte TIME_OUT_CLEAR(TIME_OUT_t *timeout)
  {
  (timeout->time_out_time) = SYSTEM_TIME_OUT_COUNTER;
  }

