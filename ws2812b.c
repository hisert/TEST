#include "ws2812b.h"

#ifdef USE_WS2812B


// <editor-fold defaultstate="collapsed" desc="RGB DEFINE ">
#define HELPER_FUNCTS_ARRAY_LEN 10
#define LED_PORT PORTD
#define LED_PORT_INDEX 5
#define LED_MAX 50
dword ws2812_data[100];
word ws812_data_counter = 0;

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="RGB HELPER ">

void ws2812_print(dword color) //Set the color of the LED
{
    dword data;
    //  cli();
    for (byte i = 0; i < 24; i++) //The loop to set 24 bits (one full LED)
    {
        data = color & 0x800000;
        color <<= 1; //Shift the color value
        SET_BIT(LED_PORT, LED_PORT_INDEX);
        if (data) {
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            CLR_BIT(LED_PORT, LED_PORT_INDEX);
        }
        CLR_BIT(LED_PORT, LED_PORT_INDEX);
    }
    //  sei();
    asm("nop");
    asm("nop");
}

void LED_CLEAN()
{
    for (word x = 0; x < LED_MAX; x++) ws2812_data[x] = 0;
    ws812_data_counter = 0;
}

void LED_UPDATE()
{
    for (word x = 0; x < 50; x++) ws2812_print(ws2812_data[x]);
    ws812_data_counter = 0;
}

void LED_DATA_COPY_SINGLE(word dataLen, dword data)
{
    for (word x = 0; x < dataLen; x++) {
        ws2812_data[ws812_data_counter] = data;
        ws812_data_counter++;
    }
}

void LED_DATA_MASK(word dataStart, word dataLen, dword data)
{
    for (word x = 0; x < dataLen; x++) ws2812_data[dataStart + x ] = data;
}

void LED_DATA_REVERSE(word dataLen)
{
    dword temp;
    dataLen = dataLen - 1;
    ws812_data_counter--;
    for (byte x = 0; x <= dataLen / 2; x++) {
        temp = ws2812_data[ws812_data_counter - x];
        ws2812_data[ws812_data_counter - x] = ws2812_data[ws812_data_counter - dataLen + x];
        ws2812_data[ws812_data_counter - dataLen + x] = temp;
    }
    ws812_data_counter++;
}

void rotate(dword arr[], int n, int amount)
{
    dword temp[50];
    for (int i = 0; i < amount; i++) temp[i] = arr[n - amount + i];
    for (int i = n - 1; i >= amount; i--) arr[i] = arr[i - amount];

    for (int i = 0; i < amount; i++) arr[i] = temp[i];
}

void LED_TOGGLE_DATA(byte index, word dataLen, dword data, byte fast)
{
    static byte fast_counter[HELPER_FUNCTS_ARRAY_LEN];
    static byte toggle_flag[HELPER_FUNCTS_ARRAY_LEN];
    if (index == 0xFF) {
        for (byte x = 0; x < HELPER_FUNCTS_ARRAY_LEN; x++) {
            fast_counter[x] = 0;
            toggle_flag[x] = 0;
        }
        return;
    }
    if (toggle_flag[index]) LED_DATA_COPY_SINGLE(dataLen, 0);
    else LED_DATA_COPY_SINGLE(dataLen, data);
    if (toggle_flag[index] == 0) fast = fast / 4;
    if (((fast_counter[index] < fast)) && (fast < 20 && fast > 0)) fast_counter[index] = fast_counter[index] + 1;
    else {
        fast_counter[index] = 0;
        if (toggle_flag[index]) toggle_flag[index] = 0;
        else toggle_flag[index] = 1;
    }
}

void LED_SLEEPING(byte index, word dataLen, dword data)
{
    static byte fast_counter[HELPER_FUNCTS_ARRAY_LEN];
    byte fast = 0;
    static byte pwm_holder[HELPER_FUNCTS_ARRAY_LEN];
    static byte pwm_direction[HELPER_FUNCTS_ARRAY_LEN];
    if (index == 0xFF) {
        for (byte x = 0; x < HELPER_FUNCTS_ARRAY_LEN; x++) {
            fast_counter[x] = 0;
            pwm_holder[x] = 0;
            pwm_direction[x] = 0;
        }
        return;
    }
    dword printdata = 0;
    byte pwm_max = 255;
    byte pwm_min = 20;
    byte pwm_artis = 3;
    byte pwm_azalis = 3;

    if (fast_counter[index] != fast) fast_counter[index]++;
    else {
        fast_counter[index] = 0;
        if (pwm_direction[index]) {
            if ((pwm_holder[index] + pwm_artis) < pwm_max) pwm_holder[index] = pwm_holder[index] + pwm_artis;
            else pwm_direction[index] = 0;
        } else {
            if ((pwm_holder[index] - pwm_azalis) > pwm_min) pwm_holder[index] = pwm_holder[index] - pwm_artis;
            else pwm_direction[index] = 1;
        }
    }

    printdata = pwm_holder[index];
    if (data == MY_RGB_BLUE) printdata = printdata;
    else if (data == MY_RGB_RED) printdata = printdata << 8;
    else if (data == MY_RGB_GREEN) printdata = printdata << 16;
    else if (data == MY_RGB_MOR) printdata = (printdata) + (printdata << 8);
    else if (data == MY_RGB_SARI) printdata = (printdata << 8) + (printdata << 16);
    else if (data == MY_RGB_SIYAN) printdata = (printdata) + (printdata << 16);
    else if (data == MY_RGB_WHITE) printdata = printdata + (printdata << 8) + (printdata << 16);
    LED_DATA_COPY_SINGLE(dataLen, printdata);
}

void LED_SONSUZ_TUR(byte index, word dataLen, byte fast)
{
    static byte fast_counter[HELPER_FUNCTS_ARRAY_LEN];
    static word kayma_place[HELPER_FUNCTS_ARRAY_LEN];
    if (index == 0xFF) {
        for (byte x = 0; x < HELPER_FUNCTS_ARRAY_LEN; x++) {
            fast_counter[x] = 0;
            kayma_place[x] = 0;
        }
        return;
    }
    if (fast_counter[index] != fast) fast_counter[index]++;
    else {
        fast_counter[index] = 0;
        if (kayma_place[index] != (dataLen - 1)) kayma_place[index] = kayma_place[index] + 1;

        else kayma_place[index] = 0;
    }
    rotate(&(ws2812_data[ws812_data_counter - dataLen]), dataLen, kayma_place[index]);
}

void LED_DATA_METEOR_EKLE(word ledsayisi, dword data)
{
    dword printdata;
    for (signed int z = 0; z < ledsayisi; z++) {
        printdata = 255;
        if (z > ((ledsayisi * 8) / 8)) printdata = 255;
        else if (z > ((ledsayisi * 7) / 8)) printdata = 200;
        else if (z > ((ledsayisi * 6) / 8)) printdata = 170;
        else if (z > ((ledsayisi * 5) / 8)) printdata = 90;
        else if (z > ((ledsayisi * 4) / 8)) printdata = 80;
        else if (z > ((ledsayisi * 3) / 8)) printdata = 40;
        else if (z > ((ledsayisi * 2) / 8)) printdata = 20;
        else if (z > ((ledsayisi * 1) / 8)) printdata = 10;
        else printdata = 10;
        if (data == MY_RGB_BLUE) printdata = printdata;
        else if (data == MY_RGB_RED) printdata = printdata << 8;
        else if (data == MY_RGB_GREEN) printdata = printdata << 16;
        else if (data == MY_RGB_MOR) printdata = (printdata) + (printdata << 8);
        else if (data == MY_RGB_SARI) printdata = (printdata << 8) + (printdata << 16);
        else if (data == MY_RGB_SIYAN) printdata = (printdata) + (printdata << 16);
        else

            if (data == MY_RGB_WHITE) printdata = printdata + (printdata << 8) + (printdata << 16);
        LED_DATA_COPY_SINGLE(1, printdata);
    }
}

void LED_DATA_CLEAN(void)
{
    LED_TOGGLE_DATA(0xFF, 0, 0, 0);
    LED_SLEEPING(0xFF, 0, 0);
    LED_SONSUZ_TUR(0xFF, 0, 0);
}

// </editor-fold> 


#endif