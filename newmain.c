#include "ATMEGA_64.h"
#include "ATMEGA_328.h"
#include "PIC_18F87K22.h"

#include "input_debounce.h"
#include "buton_debounce.h"
#include "thread.h"
#include "soft_i2c.h"
#include "task.h"
#include "eeprom.h"
#include "MENU.h"
#include "ssd1306_oled.h"
#include "ssh1106_oled.h"
#include "AS5600_MAS.h"
#include "ws2812b.h"

// <editor-fold defaultstate="collapsed" desc="MENU ">

typedef enum {
    ROLE_A_MODE,
    ROLE_B_MODE,
    ROLE_BUSY_MODE,
    ROLE_ALARM_MODE,
    ROLE_A_TIME,
    ROLE_B_TIME,
    ROLE_BUSY_TIME,
    ROLE_ALARM_TIME,
    COUNTER_A_FIX,
    COUNTER_B_FIX,
    COUNTER_A_TEMP,
    COUNTER_B_TEMP,
    RANDOM_A_MODE,
    RANDOM_B_MODE,
    RANDOM_A_AMOUNT,
    RANDOM_B_AMOUNT,
    INPUT_MODE,
    INPUT_TIME_OUT,
    INPUT_BUFFER,
    INPUT_EMG_MODE,
    ARM_DROP_MODE,
    ARM_MOTOR_MODE,
    ARM_MOTOR_SPEED,
    ARM_MOTOR_BREAK_SPEED,
    SETTINGS_DONE,
} SETTINGS;

word SETTING_VALUES[SETTINGS_DONE];

// <editor-fold defaultstate="collapsed" desc="RELAY SETTING FUNCT">
const char *SELECT_LIST_RELAY_MODE[] = {"MODE N/O", "MODE N/C"};

word MENU_FUNCT_RELAY_A_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_A_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_A_MODE];
    }
}

word MENU_FUNCT_RELAY_B_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_B_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_B_MODE];
    }
}

word MENU_FUNCT_RELAY_BUSY_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_BUSY_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_BUSY_MODE];
    }
}

word MENU_FUNCT_RELAY_ALARM_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_ALARM_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RELAY_MODE;
        return SETTING_VALUES[ROLE_ALARM_MODE];
    }
}

word MENU_FUNCT_RELAY_A_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_A_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_A_TIME];
    }
}

word MENU_FUNCT_RELAY_B_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_B_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_B_TIME];
    }
}

word MENU_FUNCT_RELAY_BUSY_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_BUSY_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_BUSY_TIME];
    }
}

word MENU_FUNCT_RELAY_ALARM_TIME(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ROLE_ALARM_TIME] = data;
        return 0;
    } else {
        return SETTING_VALUES[ROLE_ALARM_TIME];
    }
}

Menu_One RELAY_MENU[] = {
    {.text = "RELAY A MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_A_MODE, .max = 1},
    {.text = "RELAY B MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_B_MODE, .max = 1},
    {.text = "RELAY BUSY MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_BUSY_MODE, .max = 1},
    {.text = "RELAY ALARM MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RELAY_ALARM_MODE, .max = 1},
    {.text = "RELAY A TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_A_TIME, .max = 100, .min = 0},
    {.text = "RELAY B TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_B_TIME, .max = 100, .min = 0},
    {.text = "RELAY BUSY TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_BUSY_TIME, .max = 100, .min = 0},
    {.text = "RELAY ALARM TIME", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RELAY_ALARM_TIME, .max = 100, .min = 0},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="SYSTEM COUNTER FUNCT">

char *COUNTER_CANT_ERASE = "CANT ERASE";
char *COUNTER_ASK_ERASE = "ERASE DATA ?";

word MENU_FUNCT_COUNTER_A_FIX(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_A_FIX] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_CANT_ERASE;
        return SETTING_VALUES[COUNTER_A_FIX];
    }
}

word MENU_FUNCT_COUNTER_B_FIX(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_B_FIX] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_CANT_ERASE;
        return SETTING_VALUES[COUNTER_B_FIX];
    }
}

word MENU_FUNCT_COUNTER_A_TEMP(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_A_TEMP] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_ASK_ERASE;
        return SETTING_VALUES[COUNTER_A_TEMP];
    }
}

word MENU_FUNCT_COUNTER_B_TEMP(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[COUNTER_B_TEMP] = data;
        return 0;
    } else {
        SHOW_DATA_TEXT = COUNTER_ASK_ERASE;
        return SETTING_VALUES[COUNTER_B_TEMP];
    }
}

Menu_One COUNTER_MENU[] = {
    {.text = "FIX A COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_A_FIX, .max = 65536, .min = 0},
    {.text = "FIX B COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_B_FIX, .max = 65536, .min = 0},
    {.text = "TEMP A COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_A_TEMP, .max = 65536, .min = 0},
    {.text = "TEMP B COUNTER", .flag = MENU_FLAG_SHOW_DATA, .Funct = MENU_FUNCT_COUNTER_B_TEMP, .max = 65536, .min = 0},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="RANDOM SORTER FUNCT">
const char *SELECT_LIST_RANDOM_MODE[] = {"MODE DISABLE", "MODE ENABLE"};

word MENU_FUNCT_RANDOM_A_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_A_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RANDOM_MODE;
        return SETTING_VALUES[RANDOM_A_MODE];
    }
}

word MENU_FUNCT_RANDOM_B_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_B_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_RANDOM_MODE;
        return SETTING_VALUES[RANDOM_B_MODE];
    }
}

word MENU_FUNCT_RANDOM_A_AMOUNT(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_A_AMOUNT] = data;
        return 0;
    } else {
        return SETTING_VALUES[RANDOM_A_AMOUNT];
    }
}

word MENU_FUNCT_RANDOM_B_AMOUNT(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[RANDOM_B_AMOUNT] = data;
        return 0;
    } else {
        return SETTING_VALUES[RANDOM_B_AMOUNT];
    }
}

Menu_One RANDOM_MENU[] = {
    {.text = "RANDOM A MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RANDOM_A_MODE, .max = 1},
    {.text = "RANDOM B MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_RANDOM_B_MODE, .max = 1},
    {.text = "RELAY A AMOUNT", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RANDOM_A_AMOUNT, .max = 250, .min = 0},
    {.text = "RELAY B AMOUNT", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_RANDOM_B_AMOUNT, .max = 250, .min = 0},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="INPUT FUNCT">
const char *SELECT_LIST_INPUT_MODE[] = {"FREE", "CONTROL"};
const char *SELECT_LIST_EMG_MODE[] = {"N/O", "N/C"};

word MENU_FUNCT_INPUT_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_INPUT_MODE;
        return SETTING_VALUES[INPUT_MODE];
    }
}

word MENU_FUNCT_INPUT_TIME_OUT(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_TIME_OUT] = data;
        return 0;
    } else {
        return SETTING_VALUES[INPUT_TIME_OUT];
    }
}

word MENU_FUNCT_INPUT_BUFFER(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_BUFFER] = data;
        return 0;
    } else {
        return SETTING_VALUES[INPUT_BUFFER];
    }
}

word MENU_FUNCT_EMG_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[INPUT_EMG_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_EMG_MODE;
        return SETTING_VALUES[INPUT_EMG_MODE];
    }
}

Menu_One INPUT_MENU[] = {
    {.text = "INPUT MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_INPUT_MODE, .max = 1},
    {.text = "INPUT TIME OUT", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_INPUT_TIME_OUT, .max = 100, .min = 0},
    {.text = "INPUT BUFFER", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_INPUT_BUFFER, .max = 20, .min = 0},
    {.text = "EMG MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_EMG_MODE, .max = 1},
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="ARM SETTUNG FUNCT">

const char *SELECT_LIST_DROP_ARM_MODE[] = {"DISABLE", "JUST EMG", "JUST POWER FAIL", "POWER FAIL & EMG"};
const char *SELECT_LIST_ARM_MOTOR_MODE[] = {"PASSIVE", "ACTIVE"};

word MENU_FUNCT_ARM_DROP_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_DROP_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_DROP_ARM_MODE;
        return SETTING_VALUES[ARM_DROP_MODE];
    }
}

word MENU_FUNCT_ARM_MOTOR_MODE(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_MOTOR_MODE] = data;
        return 0;
    } else {
        MENU_SELECT_LIST = SELECT_LIST_ARM_MOTOR_MODE;
        return SETTING_VALUES[ARM_MOTOR_MODE];
    }
}

word MENU_FUNCT_ARM_MOTOR_SPEED(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_MOTOR_SPEED] = data;
        return 0;
    } else {
        return SETTING_VALUES[ARM_MOTOR_SPEED];
    }
}

word MENU_FUNCT_ARM_MOTOR_BREAK_SPEED(byte komut, word data)
{
    if (komut) {
        SETTING_VALUES[ARM_MOTOR_BREAK_SPEED] = data;
        return 0;
    } else {
        return SETTING_VALUES[ARM_MOTOR_BREAK_SPEED];
    }
}

Menu_One ARM_SETTING_MENU[] = {
    {.text = "DROP ARM MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_ARM_DROP_MODE, .max = 3},
    {.text = "MOTOR MODE", .flag = MENU_FLAG_SELECT, .Funct = MENU_FUNCT_ARM_MOTOR_MODE, .max = 3},
    {.text = "MOTOR SPEED", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_ARM_MOTOR_SPEED, .max = 100, .min = 0},
    {.text = "MOTOR BREAK SPEED", .flag = MENU_FLAG_VALUE, .Funct = MENU_FUNCT_ARM_MOTOR_BREAK_SPEED, .max = 100, .min = 0},
    {.text = "MAS12 STATUS", .flag = MENU_FLAG_REFRESH_DATA, .Funct = 0, .max = 0, .min = 0},
};
// </editor-fold>

Menu_One ANA_MENU[] = {
    {.text = "INPUT SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) INPUT_MENU},
    {.text = "ARM SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) ARM_SETTING_MENU},
    {.text = "RELAY SETTINGS", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) RELAY_MENU},
    {.text = "SYSTEM COUNTER", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) COUNTER_MENU},
    {.text = "RANDOM SORTER", .flag = MENU_FLAG_NEW_MENU, .Funct = (word(*)(byte, word)) RANDOM_MENU},
};
char *ANA_MENU_UST_YAZI = "   >> MAIN MENU <<";
char *RELAY_MENU_UST_YAZI = "  >> RELAY MENU <<";
char *ARM_MENU_UST_YAZI = "    >> ARM MENU <<";
char *COUNTER_MENU_UST_YAZI = " >> COUNTER MENU <<";
char *RANDOM_MENU_UST_YAZI = "  >> RANDOM MENU <<";
char *INPUT_MENU_UST_YAZI = "  >> INPUT MENU <<";

void MENU_UST_DATA_GETIR()
{
    if (MENU_POINTER == ANA_MENU) MENU_MAX = sizeof (ANA_MENU) / sizeof (ANA_MENU[0]) - 1;
    if (MENU_POINTER == RELAY_MENU) MENU_MAX = sizeof (RELAY_MENU) / sizeof (RELAY_MENU[0]) - 1;
    if (MENU_POINTER == COUNTER_MENU) MENU_MAX = sizeof (COUNTER_MENU) / sizeof (COUNTER_MENU[0]) - 1;
    if (MENU_POINTER == RANDOM_MENU) MENU_MAX = sizeof (RANDOM_MENU) / sizeof (RANDOM_MENU[0]) - 1;
    if (MENU_POINTER == INPUT_MENU) MENU_MAX = sizeof (INPUT_MENU) / sizeof (INPUT_MENU[0]) - 1;
    if (MENU_POINTER == ARM_SETTING_MENU) sizeof (ARM_SETTING_MENU) / sizeof (ARM_SETTING_MENU[0]) - 1;

    if (MENU_POINTER == ANA_MENU) MENU_UST_YAZI = ANA_MENU_UST_YAZI;
    if (MENU_POINTER == RELAY_MENU) MENU_UST_YAZI = MENU_UST_YAZI = RELAY_MENU_UST_YAZI;
    if (MENU_POINTER == ARM_SETTING_MENU) MENU_UST_YAZI = ARM_MENU_UST_YAZI;
    if (MENU_POINTER == COUNTER_MENU) MENU_UST_YAZI = COUNTER_MENU_UST_YAZI;
    if (MENU_POINTER == RANDOM_MENU) MENU_UST_YAZI = RANDOM_MENU_UST_YAZI;
    if (MENU_POINTER == INPUT_MENU) MENU_UST_YAZI = INPUT_MENU_UST_YAZI;
}

// </editor-fold>

void LED_THREAD(byte threadIndex)
{
    static THREAD_DELAY timer;
    THREAD_TIME_START(&timer);
    if (THREAD_TIME_WAIT(&timer, 950)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('D', 1);
    if (THREAD_TIME_WAIT(&timer, 50)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) PIN_SET_LAT_TOGGLE('D', 1);
    if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);
}

int main(void)
{
    SET_OSC(64);
    PIN_SET_IO('D', 'O', 'D', 1, 'H'); //LED

    THREAD_CREATE(0, THREAD_FLG_START | THREAD_FLG_LOOP, 1, LED_THREAD);
    TIMER_1_INIT(1);
    INTERRUPT_ALL(1);
    I2C_1_INIT(100000);
    UART_1_INIT(38400);
    SSH1306_OLED_Init(I2C_1_START, I2C_1_WRITE, I2C_1_STOP);
    MENU_INIT(SSH1306_OLED_ClearDisplay, SSH1306_OLED_Update, SSH1306_OLED_Write_Text, SSH1306_OLED_Write_Dec);
    MENU_ANA_INIT(ANA_MENU);
    UART_1_STRING("HELLO");
    // EEPROM_INIT(EEPROM_B_WRITE, EEPROM_B_READ);
    while (1) {
        THREAD_MAIN();
        TASK_MAIN();
        MENU_PROCESS();
    }
}

#ifdef ATMEGA_64

ISR(TIMER1_OVF_vect)
{
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
}

ISR(TIMER3_OVF_vect)
{
    TIMER_3_INTERRUPT_FUNCT();
}

ISR(USART0_TX_vect)
{
}

ISR(USART0_RX_vect)
{
    byte x = UDR0;
}

ISR(USART1_RX_vect)
{
    byte x = UDR1;
}

ISR(USART1_TX_vect)
{
}

#endif

#ifdef ATMEGA_328

ISR(TIMER1_OVF_vect)
{
    TIMER_1_INTERRUPT_FUNCT();
    THREAD_INTERRUPT();
}

ISR(USART_RX_vect)
{

}

ISR(USART_TX_vect)
{

}

ISR(PCINT0_vect)
{

}

#endif

#ifdef PIC_18F87K22

void __interrupt() _ISR(void)
{
    if (INTCONbits.RBIF) {
        byte x = PORTB;
        INTCONbits.RBIF = 0;
    } else if (PIR1bits.TMR1IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_1_INTERRUPT_FUNCT();
        THREAD_INTERRUPT();
    } else if (PIR2bits.TMR3IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_3_INTERRUPT_FUNCT();
    } else if (PIR5bits.TMR5IF) // Timer1 kesmesi olu?tu mu?
    {
        TIMER_5_INTERRUPT_FUNCT();
    } else if (PIR1bits.RC1IF) { // UART1 al?c? interrupt'?
        PIR1bits.RC1IF = 0;
        UART_1_BYTE(RCREG1);
        if (RCREG1 == '+') MENU_BUTON_ADD('U');
        if (RCREG1 == '-') MENU_BUTON_ADD('D');
        if (RCREG1 == '*') MENU_BUTON_ADD('O');
        if (RCREG1 == '/') MENU_BUTON_ADD('B');
    } else if (PIR3bits.RC2IF) { // UART1 al?c? interrupt'?
        PIR3bits.RC2IF = 0;
        UART_2_BYTE(RCREG2);
    }
}
#endif
