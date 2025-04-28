#include <pic18.h>
#include <xc.h>
#include "config.h"
#include <string.h>
#include <stdio.h>

#include "PIC_18F87K22.h"
#include "ssd1306_oled.h"
#include "input_debounce.h"
#include "buton_debounce.h"
#include "thread.h"
#include "soft_i2c.h"
#include "task.h"
#include "MENU.h"
// <editor-fold defaultstate="collapsed" desc="X">
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="TYPEDEF DEFINE">
#define FLAG_JOIN(TASK_REG,TASK)      TASK_REG = TASK_REG | TASK
#define FLAG_ERASE(TASK_REG,TASK)     TASK_REG =TASK_REG & ~TASK
#define FLAG_CONTROL(TASK_REG,TASK)     TASK_REG & TASK
#define TERSLE(DAT) DAT= ~DAT
#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#define qword unsigned long long
#define open 1
#define close 0
#define SET_BIT(reg,bit) (reg = reg | (1 << bit))
#define CLR_BIT(reg,bit) (reg = reg & ~(1 << bit))
#define TOGGLE_BIT(reg,bit) (reg = reg ^ (1 << bit))
#define CHECK_BIT(reg,bit) ((reg & (1 << bit)) / (1 << bit))
void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow);

// </editor-fold>

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

void LOG_PRINT(char *msg)
{
    UART_1_STRING(msg);
    UART_1_STRING("\r\n");
}
// <editor-fold defaultstate="collapsed" desc="MENU ">


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

void MENU_BUTON_READ()
{
    static Buton_t MENU_OK;
    static Buton_t MENU_DOWN;
    static Buton_t MENU_UP;
    byte temp = 0;

    temp = BUTON_PROCESS(&MENU_UP, PIN_GET_PORT('B', 0), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            // if (BUTON_GET_TIME(&MENU_UP));
        }
        if (temp == BUTON_PRESSED) {
            MENU_BUTON_ADD('U');
        }
    }


    temp = BUTON_PROCESS(&MENU_OK, PIN_GET_PORT('B', 1), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            //  if (BUTON_GET_TIME(&MENU_OK));
        }
        if (temp == BUTON_PRESSED) {
            if (BUTON_GET_TIME(&MENU_OK) > 1000) MENU_BUTON_ADD('B');
            else MENU_BUTON_ADD('O');
        }
    }


    temp = BUTON_PROCESS(&MENU_DOWN, PIN_GET_PORT('B', 2), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            //      if (BUTON_GET_TIME(&MENU_DOWN));
        }
        if (temp == BUTON_PRESSED) {

            MENU_BUTON_ADD('D');
        }
    }
}

// <editor-fold defaultstate="collapsed" desc="INPUT ENTER">
#define IN_INPUT_A_PRESSED 0x0001
#define IN_INPUT_A_RELEASED 0x0002
#define IN_INPUT_B_PRESSED 0x0004
#define IN_INPUT_B_RELEASED 0x0008
#define IN_INHIBIT_A_PRESSED 0x0010
#define IN_INHIBIT_A_RELEASED 0x0020
#define IN_INHIBIT_B_PRESSED 0x0040
#define IN_INHIBIT_B_RELEASED 0x0080
#define IN_INPUT_EMG_PRESSED 0x0100
#define IN_INPUT_EMG_RELEASED 0x0200
#define IN_INPUT_EMG_MUTE_PRESSED 0x0400
#define IN_INPUT_EMG_MUTE_RELEASED 0x0800
#define IN_INPUT_RES_PRESSED 0x1000
#define IN_INPUT_RES_RELEASED 0x2000

#define IN_A_READ CHECK_BIT(PORTF,1) 
#define IN_B_READ CHECK_BIT(PORTF,2) 
#define IN_INHIBIT_A_READ CHECK_BIT(PORTF,3) 
#define IN_INHIBIT_B_READ CHECK_BIT(PORTF,4) 
#define IN_EMG_READ CHECK_BIT(PORTF,5) 
#define IN_EMG_MUTE_READ CHECK_BIT(PORTF,6) 
#define IN_RES_READ CHECK_BIT(PORTF,7) 

word IN_STATUS = 0;

void INPUT_READ()
{
#define DEBOUNCE_TIME 4
    byte temp = 0;
    static Input_t INPUT_A;
    temp = INPUT_DEBOUNCE(&INPUT_A, IN_A_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_A_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_A_RELEASED;
    }
    static Input_t INPUT_B;
    temp = INPUT_DEBOUNCE(&INPUT_B, IN_B_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_B_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_B_RELEASED;
    }
    static Input_t INHIBIT_A;
    temp = INPUT_DEBOUNCE(&INHIBIT_A, IN_INHIBIT_A_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_A_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_A_RELEASED;
    }
    static Input_t INHIBIT_B;
    temp = INPUT_DEBOUNCE(&INHIBIT_B, IN_INHIBIT_B_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_B_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INHIBIT_B_RELEASED;
    }
    static Input_t INPUT_EMG;
    temp = INPUT_DEBOUNCE(&INPUT_EMG, IN_EMG_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_RELEASED;
    }

    static Input_t INPUT_EMG_MUTE;
    temp = INPUT_DEBOUNCE(&INPUT_EMG_MUTE, IN_EMG_MUTE_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_MUTE_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_EMG_MUTE_RELEASED;
    }
    static Input_t RES;
    temp = INPUT_DEBOUNCE(&RES, IN_RES_READ, DEBOUNCE_TIME);
    if (temp) {
        if (temp == INPUT_RAISE_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_RES_PRESSED;
        if (temp == IINPUT_FALL_EDGE) IN_STATUS = IN_STATUS | IN_INPUT_RES_RELEASED;
    }
}

void INPUT_PROCESS()
{
    if (IN_STATUS) {
        if (IN_STATUS & IN_INPUT_A_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_A_PRESSED;
            LOG_PRINT("INPUT A PRESSED");
        }
        if (IN_STATUS & IN_INPUT_A_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_A_RELEASED;
            LOG_PRINT("INPUT A RELEASED");
        }
        if (IN_STATUS & IN_INPUT_B_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_B_PRESSED;
            LOG_PRINT("INPUT B PRESSED");
        }
        if (IN_STATUS & IN_INPUT_B_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_B_RELEASED;
            LOG_PRINT("INPUT B RELEASED");
        }
        if (IN_STATUS & IN_INHIBIT_A_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_A_PRESSED;
            LOG_PRINT("INHIBIT A PRESSED");
        }
        if (IN_STATUS & IN_INHIBIT_A_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_A_RELEASED;
            LOG_PRINT("INHIBIT A RELEASED");
        }
        if (IN_STATUS & IN_INHIBIT_B_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_B_PRESSED;
            LOG_PRINT("INHIBIT B PRESSED");
        }
        if (IN_STATUS & IN_INHIBIT_B_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INHIBIT_B_RELEASED;
            LOG_PRINT("INHIBIT B RELEASED");
        }
        if (IN_STATUS & IN_INPUT_EMG_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_PRESSED;
            LOG_PRINT("INPUT EMG PRESSED");
        }
        if (IN_STATUS & IN_INPUT_EMG_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_RELEASED;
            LOG_PRINT("INPUT EMG RELEASED");
        }
        if (IN_STATUS & IN_INPUT_EMG_MUTE_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_MUTE_PRESSED;
            LOG_PRINT("INPUT EMG MUTE PRESSED");
        }
        if (IN_STATUS & IN_INPUT_EMG_MUTE_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_EMG_MUTE_RELEASED;
            LOG_PRINT("INPUT EMG MUTE RELEASED");
        }
        if (IN_STATUS & IN_INPUT_RES_PRESSED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_RES_PRESSED;
            LOG_PRINT("INPUT RES PRESSED");
        }
        if (IN_STATUS & IN_INPUT_RES_RELEASED) {
            IN_STATUS = IN_STATUS &~IN_INPUT_RES_RELEASED;
            LOG_PRINT("INPUT RES RELEASED");
        }
    }
}

// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="ROLE FONKSIYONLARI">
#define ROLE_CIKIS_AB_ENABLE SET_BIT(LATD,1)
#define ROLE_CIKIS_AB_DISABLE CLR_BIT(LATD,1)
#define ROLE_CIKIS_AB_CHECK CHECK_BIT(LATD,1)
#define ROLE_CIKIS_BA_ENABLE SET_BIT(LATD,2)
#define ROLE_CIKIS_BA_DISABLE CLR_BIT(LATD,2)
#define ROLE_CIKIS_BA_CHECK CHECK_BIT(LATD,2)
#define ROLE_CIKIS_ALARM_ENABLE SET_BIT(LATD,3)
#define ROLE_CIKIS_ALARM_DISABLE CLR_BIT(LATD,3)
#define ROLE_CIKIS_ALARM_CHECK CHECK_BIT(LATD,3)
#define ROLE_CIKIS_BUSY_ENABLE SET_BIT(LATD,4)
#define ROLE_CIKIS_BUSY_DISABLE CLR_BIT(LATD,4)
#define ROLE_CIKIS_BUSY_CHECK CHECK_BIT(LATD,4)
#define ROLE_CIKIS_MODE_NORMALLY_OPEN 0
#define ROLE_CIKIS_MODE_NORMALLY_CLOSE 1

typedef enum {
    ROLE_CIKIS_AB = 0,
    ROLE_CIKIS_BA,
    ROLE_CIKIS_ALARM,
    ROLE_CIKIS_BUSY,
    ROLE_CIKIS_DONE,
} ROLE_TYPES;
byte ROLE_CIKIS_MODE[ROLE_CIKIS_DONE];
word ROLE_CIKIS_TIME[ROLE_CIKIS_DONE];
byte ROLE_CIKIS_STATE[ROLE_CIKIS_DONE];

void ROLE_MODE_SELECT(byte index, byte mode)
{
    ROLE_CIKIS_MODE[index] = mode;
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
        else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
    }
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
        else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
    }
} //ROLENIN NORMALLY OPEN NORMALLY CLOSE OLACAGINI BELIRLEYEN FONKSIYON.

void ROLE_GO_OUTPUT(byte index, byte time)
{
    ROLE_CIKIS_STATE[index] = 1;
    ROLE_CIKIS_TIME[index] = ((time));
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_OPEN) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
        else if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
    }
    if (ROLE_CIKIS_MODE[index] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) {
        if (index == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
        else if (index == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
        else if (index == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
        else

            if (index == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
    }
} //ROLEYI CEKME ISLEMINI BASLATAN FONKSIYON.ARKA PLANDA KENDI KENDINE ISLEM TAMAMLANIR.

void ROLE_OUTPUT(byte index)
{
    if (index == ROLE_CIKIS_AB)ROLE_GO_OUTPUT(ROLE_CIKIS_AB, SETTING_VALUES[ROLE_A_TIME]);
    if (index == ROLE_CIKIS_BA)ROLE_GO_OUTPUT(ROLE_CIKIS_BA, SETTING_VALUES[ROLE_B_TIME]);
    if (index == ROLE_CIKIS_BUSY)ROLE_GO_OUTPUT(ROLE_CIKIS_BUSY, SETTING_VALUES[ROLE_BUSY_TIME]);
    if (index == ROLE_CIKIS_ALARM)ROLE_GO_OUTPUT(ROLE_CIKIS_ALARM, SETTING_VALUES[ROLE_ALARM_TIME]);
}

void INTERRUPT_KONTROL_ROLE_TIME()
{
    for (byte x = 0; x < 4; x++) {
        if (ROLE_CIKIS_STATE[x] == 0) continue;
        else {
            if (ROLE_CIKIS_TIME[x]) ROLE_CIKIS_TIME[x] = ROLE_CIKIS_TIME[x] - 1;
            else {
                if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_OPEN) {
                    if (x == ROLE_CIKIS_AB) ROLE_CIKIS_AB_DISABLE;
                    else if (x == ROLE_CIKIS_BA) ROLE_CIKIS_BA_DISABLE;
                    else if (x == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_DISABLE;
                    else if (x == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_DISABLE;
                }
                if (ROLE_CIKIS_MODE[x] == ROLE_CIKIS_MODE_NORMALLY_CLOSE) {
                    if (x == ROLE_CIKIS_AB) ROLE_CIKIS_AB_ENABLE;
                    else if (x == ROLE_CIKIS_BA) ROLE_CIKIS_BA_ENABLE;
                    else if (x == ROLE_CIKIS_ALARM) ROLE_CIKIS_ALARM_ENABLE;
                    else if (x == ROLE_CIKIS_BUSY) ROLE_CIKIS_BUSY_ENABLE;
                }
                ROLE_CIKIS_STATE[x] = 0;
            }
        }
    }
} //ON FONDA BASLANGICI YAPILMIS OLAN ROLE CIKISLARINI NC,NO VE ZAMANINA GORE SAYIP BITIS ISLEMLERINI YAPAN FONKSIYON.

void INIT_ROLE()
{
    SETTING_VALUES[ROLE_A_TIME] = 5;
    SETTING_VALUES[ROLE_B_TIME] = 10;
    SETTING_VALUES[ROLE_BUSY_TIME] = 15;
    SETTING_VALUES[ROLE_ALARM_TIME] = 20;

    SETTING_VALUES[ROLE_A_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;
    SETTING_VALUES[ROLE_B_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;
    SETTING_VALUES[ROLE_ALARM_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;
    SETTING_VALUES[ROLE_BUSY_MODE] = ROLE_CIKIS_MODE_NORMALLY_OPEN;

    ROLE_MODE_SELECT(ROLE_CIKIS_AB, SETTING_VALUES[ROLE_A_MODE]);
    ROLE_MODE_SELECT(ROLE_CIKIS_BA, SETTING_VALUES[ROLE_B_MODE]);
    ROLE_MODE_SELECT(ROLE_CIKIS_ALARM, SETTING_VALUES[ROLE_ALARM_MODE]);
    ROLE_MODE_SELECT(ROLE_CIKIS_BUSY, SETTING_VALUES[ROLE_BUSY_MODE]);
} //ROLE NO NC EPROOMDAKI KAYITLI DURUMA GORE SETLENIYOR.

//// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="THREAD FUNCT">

void LED_THREAD(byte threadIndex)
{
    static THREAD_DELAY timer;
    THREAD_TIME_START(&timer);
    if (THREAD_TIME_WAIT(&timer, 950)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) TERSLE(LATD4);
    if (THREAD_TIME_WAIT(&timer, 50)) if (THREAD_GET_STATE() == THREAD_FUNCT_FIRST) TERSLE(LATD4);
    if (THREAD_TIME_DONE(&timer)) THREAD_DONE_CONTROL(threadIndex);
}

void INPUT_THREAD(byte threadIndex)
{
    MENU_BUTON_READ();
    MENU_PROCESS();
    INPUT_READ();
    INPUT_PROCESS();
}

void ROLE_THREAD(byte threadIndex)
{
    INTERRUPT_KONTROL_ROLE_TIME();
}

// </editor-fold>

void TASK_TEST(byte taskIndex)
{
    TERSLE(LATD1);
}

void main(void)
{
    SET_OSC(64);
    //    PIN_SET_IO('D', 'I', 'B', 0, 'L');
    //    PIN_SET_IO('D', 'I', 'B', 1, 'L');
    //    PIN_SET_IO('D', 'I', 'B', 2, 'L');
    PIN_SET_ANSEL(0xFF, 0xFF);
    PIN_SET_IO('D', 'O', 'A', 3, 'L');

    PIN_SET_IO('D', 'I', 'B', 4, 'L'); //SENSOR 1
    PIN_SET_IO('D', 'I', 'B', 5, 'L'); //SENSOR 2
    PIN_SET_IO('D', 'I', 'B', 6, 'L'); //SENSOR 3

    PIN_SET_IO('D', 'O', 'D', 1, 'L'); //ROLE 1
    PIN_SET_IO('D', 'O', 'D', 2, 'L'); //ROLE 2
    PIN_SET_IO('D', 'O', 'D', 3, 'L'); //ROLE 3
    PIN_SET_IO('D', 'O', 'D', 4, 'L'); //ROLE 4

    PIN_SET_IO('D', 'I', 'F', 1, 'L'); //INPUT A
    PIN_SET_IO('D', 'I', 'F', 2, 'L'); //INPUT B
    PIN_SET_IO('D', 'I', 'F', 3, 'L'); //INHIBIT A
    PIN_SET_IO('D', 'I', 'F', 4, 'L'); //INHIBIT B
    PIN_SET_IO('D', 'I', 'F', 5, 'L'); //INPUT EMG
    PIN_SET_IO('D', 'I', 'F', 6, 'L'); //INPUT EMG MUTE
    PIN_SET_IO('D', 'I', 'F', 7, 'L'); //INPUT RES

    //    PWM_6_INIT(10000, 2); //MOTOR FAZ1
    //    PWM_7_INIT(10000, 2); //MOTOR FAZ2
    //    PWM_8_INIT(10000, 2); //MOTOR FAZ3
    //    PWM_6_SET(1);
    //    PWM_7_SET(1);
    //    PWM_8_SET(1);
    //    PWM_6_DUTY(10);
    //    PWM_7_DUTY(20);
    //    PWM_8_DUTY(30);
    //
    //    PWM_4_INIT(10000, 4); //MOSFET 1 
    //    PWM_5_INIT(10000, 4); //MOSFET 2
    //    PWM_4_SET(1);
    //    PWM_5_SET(1);
    //    PWM_4_DUTY(80);
    //    PWM_5_DUTY(90);
    //
    //
    I2C_1_INIT(100000);
    //    // I2C_2_INIT(100000);
    UART_1_INIT(38400);
    TIMER_1_INIT(1);
    PIN_IOC_INTERRUPT(1, 1);

    // SOFT_I2C_INIT(&TRISC, &LATC, &PORTC, 4, &TRISC, &LATC, &PORTC, 3);
    OLED_Init(I2C_1_START, I2C_1_WRITE, I2C_1_STOP);
    OLED_Write_Dec(0, 0, 1253);
    OLED_Update();
    INIT_ROLE();
    ROLE_OUTPUT(ROLE_CIKIS_AB);
    ROLE_OUTPUT(ROLE_CIKIS_BA);
    ROLE_OUTPUT(ROLE_CIKIS_BUSY);
    ROLE_OUTPUT(ROLE_CIKIS_ALARM);

    THREAD_CREATE(0, THREAD_FLG_START | THREAD_FLG_LOOP, 1, LED_THREAD);
    THREAD_CREATE(1, THREAD_FLG_START | THREAD_FLG_LOOP, 10, INPUT_THREAD);
    THREAD_CREATE(2, THREAD_FLG_START | THREAD_FLG_LOOP, 100, ROLE_THREAD);
    INTERRUPT_ALL(1);
    MENU_INIT(OLED_ClearDisplay, OLED_Update, OLED_Write_Text, OLED_Write_Dec);
    MENU_ANA_INIT(ANA_MENU);

    while (1) {

        THREAD_MAIN();
    }
}

void __interrupt() _ISR(void)
{
    if (INTCONbits.RBIF) {
        byte x = PORTB;
        INTCONbits.RBIF = 0;
        PIN_SET_LAT_TOGGLE('A', 3);
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
