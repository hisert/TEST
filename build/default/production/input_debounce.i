# 1 "input_debounce.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "input_debounce.c" 2
# 1 "./input_debounce.h" 1
# 14 "./input_debounce.h"
    typedef struct {
        unsigned char Temp_Counter;
        unsigned char Old_state;
    } Input_t;





    unsigned char INPUT_DEBOUNCE(Input_t *Input, unsigned char Input_Val, unsigned char Debounce);
# 2 "input_debounce.c" 2

unsigned char INPUT_DEBOUNCE(Input_t *Input, unsigned char Input_Val, unsigned char Debounce)
{
    if (Input->Old_state == Input_Val) Input->Temp_Counter = 0;
    else {
        if (Input->Temp_Counter >= Debounce) {
            Input->Temp_Counter = 0;
            Input->Old_state = Input_Val;
            if (Input_Val == 0) return 0x01;
            else return 0x02;
        } else Input->Temp_Counter = Input->Temp_Counter + 1;
    }
    return 0x00;
}
