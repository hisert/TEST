#include "common.h"

#ifndef SSH1106_OLED_H
#define	SSH1106_OLED_H

#ifdef	__cplusplus
extern "C" {
#endif

    void ssh1106_command(byte command);
    void ssh1106_data(byte value);
    void SSH1106_OLED_SetFont(const byte *font);
    void SSH1106_OLED_SetDisplayNormal(void);
    void SSH1106_OLED_SetDisplayInverted(void);
    void SSH1106_OLED_SetContrast(byte contrast);
    void SSH1106_OLED_ClearDisplay(void);
    void SSH1106_OLED_FillDisplay(void);
    void SSH1106_OLED_InvertDisplay(byte value);
    void SSH1106_OLED_DrawPixel(word x, word y, byte color);
    void SSH1106_OLED_Line(word x_start, word y_start, word x_end, word y_end, byte color);
    void SSH1106_OLED_V_Line(word y_start, word y_end, word x_pos, byte color);
    void SSH1106_OLED_H_Line(word x_start, word x_end, word y_pos, byte color);
    void SSH1106_OLED_Rectangle(word x1, word y1, word x2, word y2, byte color);
    void SSH1106_OLED_FillRectangle(word x1, word y1, word x2, word y2, byte color);
    void SSH1106_OLED_Triangle(word x0, word y0, word x1, word y1, word x2, word y2, byte color);
    void SSH1106_OLED_Image(const byte *image);
    void SSH1106_OLED_Circle(word x0, word y0, word r, byte color);
    void SSH1106_OLED_Write(word x, word y, char value);
    void SSH1106_OLED_Write_Text(word x, word y, const char *text);
    void SSH1106_OLED_Write_Dec(word x, word y, dword data);
    void SSH1106_OLED_Init(void (*startFunc)(void), byte(*writeFunc)(byte), void(*stopFunc)(void));
    void SSH1106_OLED_Update(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SSH1106_OLED_H */

