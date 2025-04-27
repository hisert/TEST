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

// <editor-fold defaultstate="collapsed" desc="MENU BUTONLARI">

#define PRESSED_OK 0x01
#define PRESSED_UP 0x02
#define PRESSED_DOWN 0x04
#define PRESSED_BACK 0x08
byte MENU_BUTON_STATUS = 0;

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
            MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_UP;
        }
    }


    temp = BUTON_PROCESS(&MENU_OK, PIN_GET_PORT('B', 1), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            //  if (BUTON_GET_TIME(&MENU_OK));
        }
        if (temp == BUTON_PRESSED) {
            if (BUTON_GET_TIME(&MENU_OK) > 1000) MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_BACK;
            else MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_OK;
        }
    }


    temp = BUTON_PROCESS(&MENU_DOWN, PIN_GET_PORT('B', 2), 10, 10);
    if (temp) {
        if (temp == BUTON_PRESSING) {
            //      if (BUTON_GET_TIME(&MENU_DOWN));
        }
        if (temp == BUTON_PRESSED) {

            MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_DOWN;
        }
    }
}

void MENU_BUTON_PROCESS()
{

}

// </editor-fold>
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
    MENU_BUTON_PROCESS();
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
    //    I2C_1_INIT(100000);
    //    // I2C_2_INIT(100000);
    //    UART_1_INIT(38400);
    TIMER_1_INIT(1);
    PIN_IOC_INTERRUPT(1, 1);

    SOFT_I2C_INIT(&TRISC, &LATC, &PORTC, 4, &TRISC, &LATC, &PORTC, 3);
    OLED_Init(SOFT_I2C_START, SOFT_I2C_WRITE, SOFT_I2C_STOP);
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
    TASK_CREATE(0, TASK_FLG_START, TASK_TEST);
    INTERRUPT_ALL(1);

    while (1) {

        THREAD_MAIN();
        TASK_MAIN();
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
        if (RCREG1 == '+') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_UP;
        if (RCREG1 == '-') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_DOWN;
        if (RCREG1 == '*') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_OK;
        if (RCREG1 == '/') MENU_BUTON_STATUS = MENU_BUTON_STATUS | PRESSED_BACK;
    } else if (PIR3bits.RC2IF) { // UART1 al?c? interrupt'?
        PIR3bits.RC2IF = 0;
        UART_2_BYTE(RCREG2);
    }
}
