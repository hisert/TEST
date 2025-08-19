#include "lcd_16x2.h"

#ifdef USE_LCD_16x2

// <editor-fold defaultstate="collapsed" desc="CLASS FUNCTS">
pin_t Pin_D7;
pin_t Pin_D6;
pin_t Pin_D5;
pin_t Pin_D4;
pin_t Pin_RS;
pin_t Pin_EN;
byte ShiftMode = 0;
const char *Index_0_Msg;
const char *Index_1_Msg;
word Index_0_Offset = 0; // 1. sat?r offset
word Index_1_Offset = 0; // 2. sat?r offset

void LCD_16x2_WAIT_MS(byte wait)
{
    for (byte x = 0; x < wait; x++) {
#ifdef USE_ATMEL
        _delay_ms(1);
#endif
#ifdef USE_PIC
        __delay_ms(1);
#endif
    }
}

void LCD_16x2_WAIT_US(byte wait)
{
    for (byte x = 0; x < wait; x++) _delay_us(1);
}

void LCD_16x2_BIT_WRITE(byte *REG_, byte index, byte onOrOff)
{
    byte pro_adress = *REG_;
    if (onOrOff) pro_adress = pro_adress | (byte) (1 << index);
    else pro_adress = pro_adress & ~(byte) (1 << index);
    *(REG_) = pro_adress;
}

void LCD_16x2_Nibble(byte value)
{
    LCD_16x2_BIT_WRITE(Pin_D4.lat_adress, Pin_D4.index, ((value >> 4) & 1));
    LCD_16x2_BIT_WRITE(Pin_D5.lat_adress, Pin_D5.index, ((value >> 5) & 1));
    LCD_16x2_BIT_WRITE(Pin_D6.lat_adress, Pin_D6.index, ((value >> 6) & 1));
    LCD_16x2_BIT_WRITE(Pin_D7.lat_adress, Pin_D7.index, ((value >> 7) & 1));

    LCD_16x2_BIT_WRITE(Pin_EN.lat_adress, Pin_EN.index, 1);
    LCD_16x2_WAIT_US(50);
    LCD_16x2_BIT_WRITE(Pin_EN.lat_adress, Pin_EN.index, 0);
    LCD_16x2_WAIT_US(50);

    LCD_16x2_BIT_WRITE(Pin_D4.lat_adress, Pin_D4.index, ((value >> 0) & 1));
    LCD_16x2_BIT_WRITE(Pin_D5.lat_adress, Pin_D5.index, ((value >> 1) & 1));
    LCD_16x2_BIT_WRITE(Pin_D6.lat_adress, Pin_D6.index, ((value >> 2) & 1));
    LCD_16x2_BIT_WRITE(Pin_D7.lat_adress, Pin_D7.index, ((value >> 3) & 1));

    LCD_16x2_BIT_WRITE(Pin_EN.lat_adress, Pin_EN.index, 1);
    LCD_16x2_WAIT_US(50);
    LCD_16x2_BIT_WRITE(Pin_EN.lat_adress, Pin_EN.index, 0);
    LCD_16x2_WAIT_US(50);
}

void LCD_16x2_Command(byte cmd)
{
    LCD_16x2_BIT_WRITE(Pin_RS.lat_adress, Pin_RS.index, 0);
    LCD_16x2_Nibble(cmd);
    LCD_16x2_WAIT_MS(2);
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="FOR USER">

void LCD_16x2_Char(char data)
{
    LCD_16x2_BIT_WRITE(Pin_RS.lat_adress, Pin_RS.index, 1);
    LCD_16x2_Nibble(data);
    LCD_16x2_WAIT_MS(2);
}

void LCD_16x2_String(byte row, byte col, const char *str)
{
    if (row == 0) Index_0_Msg = str;
    if (row == 1) Index_1_Msg = str;
    LCD_16x2_SetCursor(row, col);
    while (*str) LCD_16x2_Char(*str++);
}

void LCD_16x2_JustString(byte row, byte col, const char *str)
{
    LCD_16x2_SetCursor(row, col);
    while (*str) LCD_16x2_Char(*str++);
}

void LCD_16x2_Clear(void)
{
    LCD_16x2_Command(0x01);
    LCD_16x2_WAIT_MS(10);
}

void LCD_16x2_SetCursor(byte row, byte col)
{
    byte pos;
    if (row == 0) pos = 0x80 + col;
    else pos = 0xC0 + col;
    LCD_16x2_Command(pos);
}

void LCD_16x2_Init(volatile unsigned char *d7_lat, byte d7_index, volatile unsigned char *d6_lat, byte d6_index, volatile unsigned char *d5_lat, byte d5_index, volatile unsigned char *d4_lat, byte d4_index, volatile unsigned char *rs_lat, byte rs_index, volatile unsigned char *en_lat, byte en_index)
{
    Pin_D7.lat_adress = d7_lat;
    Pin_D6.lat_adress = d6_lat;
    Pin_D5.lat_adress = d5_lat;
    Pin_D4.lat_adress = d4_lat;
    Pin_RS.lat_adress = rs_lat;
    Pin_EN.lat_adress = en_lat;
    Pin_D7.index = d7_index;
    Pin_D6.index = d6_index;
    Pin_D5.index = d5_index;
    Pin_D4.index = d4_index;
    Pin_RS.index = rs_index;
    Pin_EN.index = en_index;
    LCD_16x2_WAIT_MS(20);
    LCD_16x2_Command(0x02); // 4-bit ba?lat
    LCD_16x2_Command(0x28); // 2 sat?r, 5x8 font
    LCD_16x2_Command(0x0C); // Ekran aç?k, imleç kapal?
    LCD_16x2_Command(0x06); // ?mleç sa?a kay
    LCD_16x2_Clear();
    LCD_16x2_WAIT_MS(20);
}

void LCD_16x2_Home(void)
{
    LCD_16x2_Command(0x02);
    LCD_16x2_WAIT_MS(2);
}

void LCD_16x2_Display(byte onOff)
{
    if (onOff) LCD_16x2_Command(0x0C); // Display ON, cursor/blink off
    else LCD_16x2_Command(0x08); // Display OFF
}

void LCD_16x2_Cursor(byte onOff)
{
    if (onOff) LCD_16x2_Command(0x0E); // Display ON, cursor ON
    else LCD_16x2_Command(0x0C); // Display ON, cursor OFF
}

void LCD_16x2_Blink(byte onOff)
{
    if (onOff) LCD_16x2_Command(0x0D); // Display ON, cursor OFF, blink ON
    else LCD_16x2_Command(0x0C); // Display ON, cursor OFF, blink OFF
}

void LCD_16x2_ShiftCursorLeft(void)
{
    LCD_16x2_Command(0x10);
}

void LCD_16x2_ShiftCursorRight(void)
{
    LCD_16x2_Command(0x14);
}

void LCD_16x2_ShiftDisplayLeft(void)
{
    LCD_16x2_Command(0x18);
}

void LCD_16x2_ShiftDisplayRight(void)
{
    LCD_16x2_Command(0x1C);
}

void LCD_16x2_ShiftEnable(byte Mode)
{
    if (Mode != ShiftMode) {
        Index_0_Offset = 0;
        Index_1_Offset = 0;
    }
    ShiftMode = Mode;
}

void LCD_16x2_ShiftWork()
{
    if (ShiftMode == 0) return;
    byte displayWidth = 16; // LCD geni?li?i
    word len0 = strlen(Index_0_Msg);
    word len1 = strlen(Index_1_Msg);
    if (ShiftMode == 1) {
        LCD_16x2_SetCursor(0, 0);
        for (byte i = 0; i < displayWidth; i++) {
            char c = ' ';
            if (len0 > 0) c = Index_0_Msg[(i + Index_0_Offset) % len0]; // wrap-around
            LCD_16x2_Char(c);
        }
        LCD_16x2_JustString(1, 0, Index_1_Msg); // 2. sat?r sabit
        Index_0_Offset++;
    } else if (ShiftMode == 2) {
        LCD_16x2_SetCursor(1, 0);
        for (byte i = 0; i < displayWidth; i++) {
            char c = ' ';
            if (len1 > 0) c = Index_1_Msg[(i + Index_1_Offset) % len1]; // wrap-around
            LCD_16x2_Char(c);
        }
        LCD_16x2_JustString(0, 0, Index_0_Msg); // 1. sat?r sabit
        Index_1_Offset++;
    } else if (ShiftMode == 3) {
        LCD_16x2_SetCursor(0, 0);
        for (byte i = 0; i < displayWidth; i++) {
            char c = ' ';
            if (len0 > 0) c = Index_0_Msg[(i + Index_0_Offset) % len0]; // wrap-around
            LCD_16x2_Char(c);
        }
        LCD_16x2_SetCursor(1, 0);
        for (byte i = 0; i < displayWidth; i++) {
            char c = ' ';
            if (len1 > 0) c = Index_1_Msg[(i + Index_1_Offset) % len1]; // wrap-around
            LCD_16x2_Char(c);
        }
        Index_0_Offset++;
        Index_1_Offset++;
    }
}

#endif

//KULLANIM ORNEGI
//LCD_16x2_Init(&PORTB, 0, &PORTB, 1, &PORTB, 2, &PORTB, 3, &PORTB, 6, &PORTB, 7);
//LCD_16x2_ShiftEnable(3);
