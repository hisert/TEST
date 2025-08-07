
#include "buton_debounce.h"

byte BUTON_PROCESS(Buton_t *Buton, byte Buton_Val, byte Buton_Up_Time, byte Buton_Fall_Time)
  {
  if (((Buton->Flag) & BUTON_PRESSED))
    {
    Buton->PressTime++;
    if (Buton_Val)
      {
      if (Buton->Temp_Counter) Buton->Temp_Counter = Buton->Temp_Counter - 1;
      else
        {
        Buton->Temp_Counter = Buton_Up_Time;
        Buton->Flag = Buton->Flag & ~BUTON_PRESSED;
        return BUTON_PRESSED;
        }
      }
    else Buton->Temp_Counter = Buton_Fall_Time;
    return BUTON_PRESSING;
    }
  else
    {
    if (Buton_Val == 0)
      {
      if (Buton->Temp_Counter) Buton->Temp_Counter = Buton->Temp_Counter - 1;
      else
        {
        Buton->Temp_Counter = Buton_Fall_Time;
        Buton->Flag = Buton->Flag | BUTON_PRESSED;
        return BUTON_PRESSING;
        }
      }
    else Buton->Temp_Counter = Buton_Up_Time;
    Buton->PressTime = 0;
    return BUTON_FREE;
    }
  }

word BUTON_GET_TIME(Buton_t *Buton)
  {
  return Buton->PressTime;
  }


byte BUTON_IS_PRESSED(Buton_t *Buton)
  {
  if (Buton->Flag & BUTON_PRESSED) return 1;
  return 0;
  }

