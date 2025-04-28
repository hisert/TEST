#include "common.h"
#ifndef SSD1306_OLED_H
#define	SSD1306_OLED_H

#ifdef	__cplusplus
extern "C" {
#endif

    void SSH1306_OLED_SetFont(const byte *font);
    void SSH1306_OLED_InvertFont(byte invert_status);
    void SSH1306_OLED_SetContrast(byte contrast);
    void SSH1306_OLED_ClearDisplay(void);
    void SSH1306_OLED_FillDisplay(void);
    void SSH1306_OLED_InvertDisplay(byte value);
    void SSH1306_OLED_DrawPixel(word x, word y, byte color);
    void SSH1306_OLED_Line(word x_start, word y_start, word x_end, word y_end, byte color);
    void SSH1306_OLED_V_Line(word y_start, word y_end, word x_pos, byte color);
    void SSH1306_OLED_H_Line(word x_start, word x_end, word y_pos, byte color);
    void SSH1306_OLED_Rectangle(word x1, word y1, word x2, word y2, byte color);
    void SSH1306_OLED_FillRectangle(word x1, word y1, word x2, word y2, byte color);
    void SSH1306_OLED_Triangle(word x0, word y0, word x1, word y1, word x2, word y2, byte color);
    void SSH1306_OLED_Image(const byte *image);
    void SSH1306_OLED_Circle(word x0, word y0, word r, byte color);
    void SSH1306_OLED_Write(word x, word y, char value);
    void SSH1306_OLED_Write_Text(word x, word y, const char *text);
    void SSH1306_OLED_Write_Dec(word x, word y, dword data);
    void SSH1306_OLED_Init(void (*startFunc)(void), byte(*writeFunc)(byte), byte(*stopFunc)(void));
    void SSH1306_OLED_Update(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SSD1306_OLED_H */

