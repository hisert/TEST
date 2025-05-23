#include "input_debounce.h"

byte INPUT_DEBOUNCE(Input_t *Input, byte Input_Val, byte Debounce)
  {
  if (Input->Old_state == Input_Val) Input->Temp_Counter = 0;
  else
    {
    if (Input->Temp_Counter >= Debounce)
      {
      Input->Temp_Counter = 0;
      Input->Old_state = Input_Val;
      if (Input_Val == 0) return INPUT_FALL_EDGE;
      else return INPUT_RAISE_EDGE;
      }
    else Input->Temp_Counter = Input->Temp_Counter + 1;
    }
  return NO_CHANGEE;
  }

