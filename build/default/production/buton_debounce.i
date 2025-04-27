# 1 "buton_debounce.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "buton_debounce.c" 2

# 1 "./buton_debounce.h" 1
# 14 "./buton_debounce.h"
    typedef struct {
        unsigned int PressTime;
        unsigned char Temp_Counter;
        unsigned char Flag;
    } Buton_t;





    unsigned char BUTON_PROCESS(Buton_t *Buton, unsigned char Buton_Val, unsigned char Buton_Up_Time, unsigned char Buton_Fall_Time);
    unsigned int BUTON_GET_TIME(Buton_t *Buton);
# 3 "buton_debounce.c" 2

unsigned char BUTON_PROCESS(Buton_t *Buton, unsigned char Buton_Val, unsigned char Buton_Up_Time, unsigned char Buton_Fall_Time)
{
    if (((Buton->Flag) & 0x02)) {
        Buton->PressTime++;
        if (Buton_Val) {
            if (Buton->Temp_Counter) Buton->Temp_Counter = Buton->Temp_Counter - 1;
            else {
                Buton->Temp_Counter = Buton_Up_Time;
                Buton->Flag = Buton->Flag & ~0x02;
                return 0x02;
            }
        } else Buton->Temp_Counter = Buton_Fall_Time;
        return 0x01;
    } else {
        if (Buton_Val == 0) {
            if (Buton->Temp_Counter) Buton->Temp_Counter = Buton->Temp_Counter - 1;
            else {
                Buton->Temp_Counter = Buton_Fall_Time;
                Buton->Flag = Buton->Flag | 0x02;
                return 0x01;
            }
        } else Buton->Temp_Counter = Buton_Up_Time;
        return 0x00;
    }
}

unsigned int BUTON_GET_TIME(Buton_t *Buton)
{
    return Buton->PressTime;
}
