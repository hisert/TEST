#include "hc595.h"

#ifdef USE_HC595

// <editor-fold defaultstate="collapsed" desc="CLASS FUNCTS">
pin2_t SH_CP;
pin2_t DS;
pin2_t ST_CP;

void HC595_WAIT_US(byte wait)
{
    for (byte x = 0; x < wait; x++) {
#ifdef USE_ATMEL
        _delay_us(1);
#endif
#ifdef USE_PIC
        _delay_us(1);
#endif
    }
}

void HC595_BIT_WRITE(byte *REG_, byte index, byte onOrOff)
{
    byte pro_adress = *REG_;
    if (onOrOff) pro_adress = pro_adress | (byte) (1 << index);
    else pro_adress = pro_adress & ~(byte) (1 << index);
    *(REG_) = pro_adress;
}

void HC595_Pulse_SRCLK(void)
{
    HC595_BIT_WRITE(SH_CP.lat_adress, SH_CP.index, 1);
    HC595_WAIT_US(1);
    HC595_BIT_WRITE(SH_CP.lat_adress, SH_CP.index, 0);
}

void HC595_Pulse_RCLK(void)
{
    HC595_BIT_WRITE(ST_CP.lat_adress, ST_CP.index, 1); // ? do?ru
    HC595_WAIT_US(1);
    HC595_BIT_WRITE(ST_CP.lat_adress, ST_CP.index, 0); // ? do?ru
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="USER FUNCTS">

void HC595_Init(volatile byte *sh_lat, byte sh_index, volatile byte *ds_lat, byte ds_index, volatile byte *st_lat, byte st_index)
{
    SH_CP.lat_adress = sh_lat;
    ST_CP.lat_adress = st_lat;
    DS.lat_adress = ds_lat;

    SH_CP.index = sh_index;
    ST_CP.index = st_index;
    DS.index = ds_index;

    HC595_BIT_WRITE(SH_CP.lat_adress, SH_CP.index, 0);
    HC595_BIT_WRITE(DS.lat_adress, DS.index, 0);
    HC595_BIT_WRITE(ST_CP.lat_adress, ST_CP.index, 0);
}

void HC595_WriteData(uint32_t data, uint8_t len)
{
    for (int b = 0; b < len; b++) {
        uint8_t current = (data >> (8 * b)) & 0xFF; // önce en dü?ük byte

        for (uint8_t i = 0; i < 8; i++) {
            HC595_BIT_WRITE(DS.lat_adress, DS.index, (current >> (7 - i)) & 0x01);
            HC595_Pulse_SRCLK();
        }
    }
    HC595_Pulse_RCLK(); // latch et
}

void HC595_WriteBytes(byte *data, byte len)
{
    for (uint8_t j = 0; j < len; j++) { // buffer s?ras? 0..len-1
        byte current = data[j]; // ilgili byte

        for (uint8_t i = 0; i < 8; i++) { // bitleri MSB -> LSB
            HC595_BIT_WRITE(DS.lat_adress, DS.index, (current >> (7 - i)) & 0x01);
            HC595_Pulse_SRCLK();
        }
    }
    HC595_Pulse_RCLK(); // latch clock darbesi -> ç?k??lara aktar
}
// </editor-fold>

#endif

//KULLANIM ORNEGI
//HC595_Init(&PORTE, 2, &PORTE, 3, &PORTE, 4);
//HC595_WriteData(0x00FE,1);