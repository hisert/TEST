#include "ATMEGA_64.h"
#include "ATMEGA_328.h"
#include "ATMEGA_88.h"
#include "ATMEGA_8.h"
#include "PIC_18F87K22.h"
#include "PIC_18F67K40.h"
#include "PIC_18F46K22.h"
#include "input_debounce.h"
#include "buton_debounce.h"
#include "thread.h"
#include "soft_i2c.h"
#include "eeprom.h"
#include "MENU.h"
#include "ssd1306_oled.h"
#include "ssh1106_oled.h"
#include "AS5600_MAS.h"
#include "ws2812b.h"
#include "register.h"
#include "lcd_16x2.h"
void REG_PROCESS(char *msg);
void INIT_REG();

//// <editor-fold defaultstate="collapsed" desc="PIN DEFINE ISLEMLERI                                                           ">
//// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="VARIABLES      ">

typedef enum {
    THREAD_LED,
    THREAD_UART_1_RX,
    THREAD_UART_2_RX,
    THREAD_BUZZER,
    THREAD_DONE,
} THREAD_LIST;

THREAD_t THREADS[THREAD_DONE];
char UART_2_MSG[20];
char UART_1_MSG[20];
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM FUNCT   ">

void SYSTEM_CONTROL_ALL()
{
    THREAD_ARRAY_CHECK(THREADS, ARRAY_SIZE(THREADS));
}

byte WAIT_WHILE()
{
    SYSTEM_CONTROL_ALL();
    return 1;
}

void WAIT_INTERRUPT(word ms)
{
    static TIME_OUT_t time_out;
    TIME_OUT_RESET(&time_out);
    while (WAIT_WHILE()) if (TIME_OUT_CHECK(&time_out, ms)) break;
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="EEPROM FUNCT   ">

typedef enum {
    MAGIC_BYTES,
    SETTINGS_DONE,
} SETTINGS;

word SETTING_VALUES[SETTINGS_DONE];

void CONFIG_SET(byte index, word data)
{

    SETTING_VALUES[index] = data;
}

word CONFIG_GET(byte index)
{

    return SETTING_VALUES[index];
}

void EEPROM_START()
{
    EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
    if (EEPROM_GET(MAGIC_BYTES != 0xAABB)) {
        for (byte x = 0; x < SETTINGS_DONE; x++) EEPROM_SET(x, 0);
        EEPROM_SET(MAGIC_BYTES, 0xAABB);
    }

    for (byte x = 0; x < SETTINGS_DONE; x++) SETTING_VALUES[x] = EEPROM_GET(x);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="MAIN FUNCT     ">

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PROJE FUNCT    ">

void RS485_SEND(char *msg)
{

    PIN_SET_LAT('E', 5, 'H');
    //    UART_3_STRING(msg);
    PIN_SET_LAT('E', 5, 'L');
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DIGITAL BUZZER ">

typedef struct {
    byte State;
    word Time;
} Tone_t;
Tone_t ASKI_UPDATE[] = {
    {.State = 1, .Time = 10},
    {.State = 0, .Time = 10},
    {.State = 1, .Time = 10},
    {.State = 0, .Time = 0},
};
Tone_t TONE_START[] = {
    {.State = 1, .Time = 80},
    {.State = 0, .Time = 50},
    {.State = 1, .Time = 80},
    {.State = 0, .Time = 50},
    {.State = 1, .Time = 80},
    {.State = 0, .Time = 50},
    {.State = 1, .Time = 80},
    {.State = 0, .Time = 50},
    {.State = 0, .Time = 0},
};
Tone_t TONE_MOTOR_SUCCESS[] = {
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 1, .Time = 20},
    {.State = 0, .Time = 20},
    {.State = 0, .Time = 0},
};
Tone_t TONE_MOTOR_TORK[] = {
    {.State = 1, .Time = 1000},
    {.State = 0, .Time = 100},
    {.State = 1, .Time = 100},
    {.State = 0, .Time = 100},
    {.State = 0, .Time = 0},
};
Tone_t TONE_MOTOR_TIME_OUT[] = {
    {.State = 1, .Time = 1000},
    {.State = 0, .Time = 100},
    {.State = 1, .Time = 100},
    {.State = 0, .Time = 100},
    {.State = 1, .Time = 100},
    {.State = 0, .Time = 100},
    {.State = 0, .Time = 0},
};
Tone_t *PLAY_TONE = 0;
byte BUZZER_PLAYING = 0;

void DIGITAL_BUZZER_PLAY(Tone_t *tone)
{

    PLAY_TONE = tone;
    BUZZER_PLAYING = 1;
}

void DIGITAL_BUZZER_PROCESS()
{
    static TIME_OUT_t time_out;
    static byte temp_flag = 0;
    if (BUZZER_PLAYING) {
        if (temp_flag == 0) {
            temp_flag = 1;
            TIME_OUT_RESET(&time_out);
            if ((PLAY_TONE->State) == 1)PIN_SET_LAT('F', 1, 'H');
            else PIN_SET_LAT('F', 1, 'L');
        }
        if (TIME_OUT_CHECK(&time_out, PLAY_TONE->Time)) {
            temp_flag = 0;
            PLAY_TONE++;
            if (((PLAY_TONE->State) == 0) && ((PLAY_TONE->Time) == 0)) {

                PIN_SET_LAT('F', 1, 'L');
                BUZZER_PLAYING = 0;
            }
        }
    }
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT   ">

byte THREAD_UART_1_RX_FUNCT()
{
    REG_PROCESS(UART_1_MSG);
    //RS485_SEND(UART_1_MSG);
    return THREAD_RETURN_STOP;
}

byte THREAD_UART_2_RX_FUNCT()
{
    return THREAD_RETURN_STOP;
}

byte THREAD_LED_FUNCT()
{
    static SIRALI_TIME_OUT_t timer;
    SYSTEM_FUNCT(&timer, 0, SYSTEM_FUNCT_KOMUT_CLEAN);
    if (SYSTEM_FUNCT(&timer, 900, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('B', 4, 'H');
    if (SYSTEM_FUNCT(&timer, 100, SYSTEM_FUNCT_KOMUT_WORK)) if (SYSTEM_FUNCT_GET_STATE() == SYSTEM_FUNCT_FIRST) PIN_SET_LAT('B', 4, 'L');
    LCD_16x2_ShiftWork();
    return THREAD_RETURN_CONTINUE;
}

byte THREAD_BUZZER_FUNCT()
{
    DIGITAL_BUZZER_PROCESS();
    return THREAD_RETURN_CONTINUE;
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="INTERRUPT FUNCT">

void UART_2_INTERRUPT_FUNCT(byte data)
{
    static byte counter = 0;
    byte x = data;
    if (x == '<') counter = 0;
    else if (x == '>') {
        UART_2_MSG[counter] = 0;
        THREAD_START(&THREADS[THREAD_UART_2_RX]);
    } else

        if (counter < 20) UART_2_MSG[counter++] = x;
}

void UART_1_INTERRUPT_FUNCT(byte data)
{
    static byte counter = 0;
    byte x = data;
    if (x == '<') counter = 0;
    else if (x == '>') {
        UART_1_MSG[counter++] = x;
        UART_1_MSG[counter] = 0;
        THREAD_START(&THREADS[THREAD_UART_1_RX]);
    }

    if (counter < 20) UART_1_MSG[counter++] = x;
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="REG FUNCT      ">

enum REG_NAMES_t {
    REGx_ADDR = 0, //0 0x00
    REGx_RAND_CODE, //1 0x01
    REGx_SERI_NO, //2 0x02
    REGx_VERSION, //3 0x03
    REGx_SLAVE_ADRESS, //4 0x04
    REGx_RAND_CODE_2, //5 0x05
    REGx_MAS_HAM, //6 0x06
    REGx_NAMES_NUM,
};

void REG_PROCESS(char *msg)
{
#define TX_LEN 20
    static byte UNLOCK = 0;
    static word SECURE_CODE = 1111;
    dword DATA = 0;
    word ADRESS = 0;
    byte SECOND_ADRESS = 0;
    byte KOMUT = 0;

    word MY_ADRESS = REG_GET(REGx_ADDR);
    byte MY_SECOND_ADRESS = REG_GET(REGx_SLAVE_ADRESS);
    char TX[TX_LEN];
    char DATA_S[10];
    char SYMBOL_S[3];
    char ADRESS_S[6];
    char SECOND_ADRESS_S[3];
    char KOMUT_S[3];
    char READ_WRITE[2];
    char temp[10];

    REG_PARSE_INDEX(msg, SYMBOL_S, 1, 1);
    REG_PARSE_INDEX(msg, ADRESS_S, 2, 5);
    REG_PARSE_INDEX(msg, SECOND_ADRESS_S, 6, 7);
    REG_PARSE_INDEX(msg, KOMUT_S, 8, 9);
    REG_PARSE_INDEX(msg, READ_WRITE, 10, 10);
    REG_PARSE_DATA(msg, DATA_S);

    ADRESS = (word) REG_CONVERT_STR_HEX_TO_DWORD(ADRESS_S);
    SECOND_ADRESS = (byte) REG_CONVERT_STR_HEX_TO_DWORD(SECOND_ADRESS_S);
    KOMUT = (byte) REG_CONVERT_STR_HEX_TO_DWORD(KOMUT_S);

    DATA = REG_PROCESS_GET_DATA_DEC(KOMUT, DATA_S);
    if (REG_PARSE_COMPARE(SYMBOL_S, "Q")) return;
    if (ADRESS == 0) {
        if (KOMUT == REGx_RAND_CODE) goto passed;
        if (UNLOCK) goto passed;
        return;
    }
    if ((KOMUT == REGx_ADDR) || (KOMUT == REGx_SLAVE_ADRESS)) if (UNLOCK) goto passed;
    if ((ADRESS == MY_ADRESS) && (SECOND_ADRESS == MY_SECOND_ADRESS)) goto passed;
    return;

passed:

    for (byte x = 0; x < TX_LEN; x++) TX[x] = 0x00;
    if (REG_PARSE_COMPARE(READ_WRITE, ":") == 0) {
        if ((REG_GET_FLAG(KOMUT) & RG_NV) & (UNLOCK == 0)) return;
        if (REG_GET_FLAG(KOMUT) & RG_WR) {
            if (KOMUT == REGx_RAND_CODE) {
                if (DATA == 0x0000) {
                    UNLOCK = 0;
                    REG_SET_UNLOCK_START();
                    REG_SET(KOMUT, 0);
                    //task start
                } else if ((DATA ^SECURE_CODE) == REG_GET(KOMUT)) {
                    UNLOCK = 0xFF;
                    REG_SET(KOMUT, DATA);
                    REG_SET_UNLOCK_STOP();
                } else {
                    UNLOCK = 0;
                    REG_SET(KOMUT, 0);
                    REG_SET_UNLOCK_STOP();
                }
            } else REG_SET(KOMUT, DATA);
            if (REG_GET_FLAG(KOMUT) & RG_FNC) REG_FUNC(KOMUT, ':');
        } else return;
    }
    if (REG_PARSE_COMPARE(READ_WRITE, "?") == 0) {
        if (REG_GET_FLAG(KOMUT) & RG_RD) {
            if (KOMUT == REGx_RAND_CODE) {
                if (REG_GET_UNLOCK()) {
                    REG_CHANGE_RANDCODE();
                    REG_SET(KOMUT, REG_GET_RANDCODE());
                    REG_SET_UNLOCK_STOP();
                } else return;
            }
            if (REG_GET_FLAG(KOMUT) & RG_FNC) REG_FUNC(KOMUT, '?');
        } else return;
    }
    if (REG_GET_FLAG(KOMUT) & RG_NV) REG_EEPROM_SET(KOMUT);

    REG_PROCESS_GET_DATA_STR(KOMUT, temp);
    REG_CONVERT_DWORD_TO_STR_HEX(REG_GET(REGx_ADDR), ADRESS_S, 4);
    REG_CONVERT_DWORD_TO_STR_HEX(REG_GET(REGx_SLAVE_ADRESS), SECOND_ADRESS_S, 2);
    if (REG_GET_FLAG(KOMUT) & RG_MAIN) REG_TX_ADD(TX, "MAIN1");
    REG_TX_ADD(TX, "<");

    REG_TX_ADD(TX, SYMBOL_S);
    REG_TX_ADD(TX, "R");
    REG_TX_ADD(TX, ADRESS_S);
    REG_TX_ADD(TX, SECOND_ADRESS_S);
    REG_TX_ADD(TX, KOMUT_S);
    REG_TX_ADD(TX, ":");
    REG_TX_ADD(TX, temp);
    REG_TX_ADD(TX, ">");

    if (REG_GET_FLAG(KOMUT) & RG_EN) RS485_SEND(TX);
}

void REG_FUNCT_MAS_HAM(byte regId, byte komut)
{
    if (komut == '?');
}

void INIT_REG()
{
    REG_CREATE(REGx_ADDR, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
    REG_CREATE(REGx_RAND_CODE, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD, 0, 0xFFFF, 0);
    REG_CREATE(REGx_SERI_NO, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_WR | RG_RD | RG_NV, 0, 0xFFFF, 0);
    REG_CREATE(REGx_VERSION, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_4 | RG_RD, 0x01, 0xFFFF, 0);
    REG_CREATE(REGx_SLAVE_ADRESS, 0, RG_EN | RG_IN_HEX | RG_OUT_HEX_2 | RG_WR | RG_RD | RG_NV, 0, 0xFF, 0);

    REG_CREATE(REGx_MAS_HAM, REG_FUNCT_MAS_HAM, RG_EN | RG_IN_DEC | RG_OUT_DEC_4 | RG_RD | RG_FNC, 0, 0xFFFF, 0);
    REGISTER_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
}

// </editor-fold>

int main(void)
{
    // MCU_INIT(1, 16);
    //  INIT_REG();
    TIMER_1_INTERRUPT_CONNECT(1, TIME_OUT_COUNT_INTERRUPT);
    //   UART_3_INTERRUPT_FUNCT_CONNECT(9600, UART_1_INTERRUPT_FUNCT);
    PIN_SET_IO('D', 'O', 'B', 4, 'L'); //RUN2 LED 
    PIN_SET_IO('D', 'O', 'B', 0, 'L'); //B0
    PIN_SET_IO('D', 'O', 'B', 1, 'L'); //B1
    PIN_SET_IO('D', 'O', 'B', 2, 'L'); //B2
    PIN_SET_IO('D', 'O', 'B', 3, 'L'); //B3
    PIN_SET_IO('D', 'O', 'B', 6, 'L'); //B2
    PIN_SET_IO('D', 'O', 'B', 7, 'L'); //B3

    THREAD_INIT(&THREADS[THREAD_LED], THREAD_FLG_START | THREAD_FLG_LOOP, 100, THREAD_LED_FUNCT);
    THREAD_INIT(&THREADS[THREAD_UART_1_RX], 0, 0, THREAD_UART_1_RX_FUNCT);
    THREAD_INIT(&THREADS[THREAD_UART_2_RX], 0, 0, THREAD_UART_2_RX_FUNCT);
    //THREAD_INIT(&THREADS[THREAD_BUZZER], THREAD_FLG_START | THREAD_FLG_LOOP, 0, THREAD_BUZZER_FUNCT);
    //DIGITAL_BUZZER_PLAY(TONE_START);

    INTERRUPT_ALL(1);
    LCD_16x2_Init(&PORTB, 0, &PORTB, 1, &PORTB, 2, &PORTB, 3, &PORTB, 6, &PORTB, 7);
    LCD_16x2_ShiftEnable(3);
    while (1) {
        SYSTEM_CONTROL_ALL();
    }
}
