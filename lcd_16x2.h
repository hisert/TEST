#include "common.h"


#ifndef LCD_16X2_H
#define	LCD_16X2_H

#ifdef	__cplusplus
extern "C" {
#endif



#ifdef USE_LCD_16x2

    typedef struct {
        volatile unsigned char *lat_adress;
        byte index;
    } pin_t;


    void LCD_16x2_Char(char data);
    void LCD_16x2_String(byte row, byte col, const char *str);
    void LCD_16x2_Clear(void);
    void LCD_16x2_SetCursor(byte row, byte col);
    void LCD_16x2_Init(volatile unsigned char *d7_lat, byte d7_index, volatile unsigned char *d6_lat, byte d6_index, volatile unsigned char *d5_lat, byte d5_index, volatile unsigned char *d4_lat, byte d4_index, volatile unsigned char *rs_lat, byte rs_index, volatile unsigned char *en_lat, byte en_index);
    void LCD_16x2_Home(void);
    void LCD_16x2_Display(byte onOff);
    void LCD_16x2_Cursor(byte onOff);
    void LCD_16x2_Blink(byte onOff);
    void LCD_16x2_ShiftDisplayLeft(void);
    void LCD_16x2_ShiftDisplayRight(void);
    void LCD_16x2_ShiftEnable(byte Mode);
    void LCD_16x2_ShiftWork();
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_16X2_H */

