#include "ssd1306_oled.h"
#include <string.h>
#include <stdio.h>
#include <xc.h>
// <editor-fold defaultstate="collapsed" desc="LIBRARY DEFINE    ">
#define LEFT                  0
#define RIGHT                 254
#define CENTER                255

#define BLACK                 0
#define WHITE                 1
#define INVERSE               2

//#define SSD1306_ADDR        0x3D
#define SSD1306_ADDR          0x3C


#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 32

#define SSD1306_COMMAND                     0x00
#define SSD1306_DATA                        0xC0
#define SSD1306_DATA_CONTINUE               0x40

/* SSD1306 Command Set*/
// Fundamental Commands
#define SSD1306_SET_CONTRAST_CONTROL                    0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME                   0xA4
#define SSD1306_DISPLAY_ALL_ON                          0xA5
#define SSD1306_NORMAL_DISPLAY                          0xA6
#define SSD1306_INVERT_DISPLAY                          0xA7
#define SSD1306_DISPLAY_OFF                             0xAE
#define SSD1306_DISPLAY_ON                              0xAF
#define SSD1306_NOP                                     0xE3
// Scrolling Commands
#define SSD1306_HORIZONTAL_SCROLL_RIGHT                 0x26
#define SSD1306_HORIZONTAL_SCROLL_LEFT                  0x27
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT    0x29
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT     0x2A
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
// Addressing Setting Commands
#define SSD1306_SET_LOWER_COLUMN                        0x00
#define SSD1306_SET_HIGHER_COLUMN                       0x10
#define SSD1306_MEMORY_ADDR_MODE                        0x20
#define SSD1306_SET_COLUMN_ADDR                         0x21
#define SSD1306_SET_PAGE_ADDR                           0x22
// Hardware Configuration Commands
#define SSD1306_SET_START_LINE                          0x40
#define SSD1306_SET_SEGMENT_REMAP                       0xA0
#define SSD1306_SET_MULTIPLEX_RATIO                     0xA8
#define SSD1306_COM_SCAN_DIR_INC                        0xC0
#define SSD1306_COM_SCAN_DIR_DEC                        0xC8
#define SSD1306_SET_DISPLAY_OFFSET                      0xD3
#define SSD1306_SET_COM_PINS                            0xDA
#define SSD1306_CHARGE_PUMP                             0x8D
// Timing & Driving Scheme Setting Commands
#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO             0xD5
#define SSD1306_SET_PRECHARGE_PERIOD                    0xD9
#define SSD1306_SET_VCOM_DESELECT                       0xDB

typedef struct _Current_Font_s {
    const byte *font; // Fonts Stored are Const
    byte x_size;
    byte y_size;
    byte offset;
    byte numchars;
    byte inverted;
} Current_Font_s;

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="LIBRARY CONFIG    ">
const byte SMALL_FONTS[] = {
    0x06, 0x08, 0x20, 0x5f, // x_size, y_size, offset, number of char
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp
    0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, // !
    0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, // #
    0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
    0x00, 0x23, 0x13, 0x08, 0x64, 0x62, // %
    0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, // (
    0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, // )
    0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // *
    0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // ,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /

    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // <
    0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // ?

    0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // @
    0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // D
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // G
    0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
    0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // O

    0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
    0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // W
    0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
    0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // [
    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, // Backslash (Checker pattern)
    0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // ]
    0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // _

    0x00, 0x00, 0x03, 0x05, 0x00, 0x00, // `
    0x00, 0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, // b
    0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // c
    0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // d
    0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // f
    0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
    0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // j
    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // m
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // o

    0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // p
    0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // q
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // t
    0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x00, 0x10, 0x7C, 0x82, 0x00, // {
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, // |
    0x00, 0x00, 0x82, 0x7C, 0x10, 0x00, // }
    0x00, 0x00, 0x06, 0x09, 0x09, 0x06 // ~ (Degrees)
};
static Current_Font_s cfont;
byte buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8];
void (*oled_i2c_start)(void);
byte(*oled_i2c_write)(byte data);
byte(*oled_i2c_stop)(void);
#define DEF_I2C_OLED_START  oled_i2c_start()
#define DEF_I2C_OLED_WRITE(data) oled_i2c_write(data);
#define DEF_I2C_OLED_STOP oled_i2c_stop()
// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="LIBRARY FUNCT     ">

void ssd1306_command(byte command)
{
    byte controlx = 0x00; // Co=0, D/C=0
    DEF_I2C_OLED_START;
    DEF_I2C_OLED_WRITE(SSD1306_ADDR << 1);
    DEF_I2C_OLED_WRITE(controlx);
    DEF_I2C_OLED_WRITE(command);
    DEF_I2C_OLED_STOP;
}

void ssd1306_data(byte value)
{
    byte controlx = 0x40; // Co = 0, D/C = 1
    DEF_I2C_OLED_START;
    DEF_I2C_OLED_WRITE(SSD1306_ADDR << 1);
    DEF_I2C_OLED_WRITE(controlx);
    DEF_I2C_OLED_WRITE(value);
    DEF_I2C_OLED_STOP;
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="USER FUNCT        ">

void OLED_SetFont(const byte *font)
{
    cfont.font = font;
    cfont.x_size = *(font + 0);
    cfont.y_size = *(font + 1);
    cfont.offset = *(font + 2);
    cfont.numchars = *(font + 3);
    cfont.inverted = 0;
}

void OLED_InvertFont(byte invert_status)
{
    if (invert_status) cfont.inverted = 1;
    else cfont.inverted = 0;
}

void OLED_SetContrast(byte contrast)
{
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(contrast);
}

void OLED_ClearDisplay(void)
{
    memset(buffer, 0, (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8));
}

void OLED_FillDisplay(void)
{
    memset(buffer, 0xFF, (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8));
}

void OLED_InvertDisplay(byte value)
{
    if (value) ssd1306_command(SSD1306_INVERT_DISPLAY);
    else ssd1306_command(SSD1306_NORMAL_DISPLAY);
}

void OLED_DrawPixel(word x, word y, byte color)
{
    if ((x < 0) || (x >= SSD1306_LCDWIDTH) || (y < 0) || (y >= SSD1306_LCDHEIGHT)) return;
    switch (color) {
    case WHITE: buffer[x + (y / 8) * SSD1306_LCDWIDTH] |= (1 << (y & 7));
        break;
    case BLACK: buffer[x + (y / 8) * SSD1306_LCDWIDTH] &= ~(1 << (y & 7));
        break;
    case INVERSE: buffer[x + (y / 8) * SSD1306_LCDWIDTH] ^= (1 << (y & 7));
        break;
    }
}

void OLED_Line(word x_start, word y_start, word x_end, word y_end, byte color)
{
    word x, y, addx, addy, dx, dy;
    signed long P;
    word i;
    dx = abs((word) (x_end - x_start));
    dy = abs((word) (y_end - y_start));
    x = x_start;
    y = y_start;

    if (x_start > x_end) addx = -1;
    else addx = 1;
    if (y_start > y_end) addy = -1;
    else addy = 1;
    if (dx >= dy) {
        P = 2 * dy - dx;

        for (i = 0; i <= dx; ++i) {
            OLED_DrawPixel(x, y, color);
            if (P < 0) {
                P += 2 * dy;
                x += addx;
            } else {
                P += 2 * dy - 2 * dx;
                x += addx;
                y += addy;
            }
        }
    } else {
        P = 2 * dx - dy;
        for (i = 0; i <= dy; ++i) {
            OLED_DrawPixel(x, y, color);

            if (P < 0) {
                P += 2 * dx;
                y += addy;
            } else {
                P += 2 * dx - 2 * dy;
                x += addx;
                y += addy;
            }
        }
    }
}

void OLED_V_Line(word y_start, word y_end, word x_pos, byte color)
{
    word temp;
    if (y_start > y_end) {
        temp = y_start;
        y_start = y_end;
        y_end = temp;
    }

    while (y_start <= y_end) {
        OLED_DrawPixel(x_pos, y_start, color);
        y_start++;
    }
}

void OLED_H_Line(word x_start, word x_end, word y_pos, byte color)
{
    word temp;
    if (x_start > x_end) {
        temp = x_start;
        x_start = x_end;
        x_end = temp;
    }

    while (x_start <= x_end) {
        OLED_DrawPixel(x_start, y_pos, color);
        x_start++;
    }
}

void OLED_Rectangle(word x1, word y1, word x2, word y2, byte color)
{
    OLED_H_Line(x1, x2, y1, color);
    OLED_H_Line(x1, x2, y2, color);
    OLED_V_Line(y1, y2, x1, color);
    OLED_V_Line(y1, y2, x2, color);
}

void OLED_FillRectangle(word x1, word y1, word x2, word y2, byte color)
{
    word i;
    for (i = x1; i <= x2; i++) OLED_V_Line(y1, y2, i, color);
}

void OLED_Triangle(word x0, word y0, word x1, word y1, word x2, word y2, byte color)
{
    OLED_Line(x0, y0, x1, y1, color);
    OLED_Line(x1, y1, x2, y2, color);
    OLED_Line(x2, y2, x0, y0, color);
}

void OLED_Image(const byte *image)
{
    word i;
    for (i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++) buffer[i] = *(image + i);
}

void OLED_Circle(word x0, word y0, word r, byte color)
{
    word f = 1 - r;
    word ddF_x = 1;
    word ddF_y = -2 * r;
    word x = 0;
    word y = r;

    OLED_DrawPixel(x0, y0 + r, color);
    OLED_DrawPixel(x0, y0 - r, color);
    OLED_DrawPixel(x0 + r, y0, color);
    OLED_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawPixel(x0 + x, y0 + y, color);
        OLED_DrawPixel(x0 - x, y0 + y, color);
        OLED_DrawPixel(x0 + x, y0 - y, color);
        OLED_DrawPixel(x0 - x, y0 - y, color);
        OLED_DrawPixel(x0 + y, y0 + x, color);
        OLED_DrawPixel(x0 - y, y0 + x, color);
        OLED_DrawPixel(x0 + y, y0 - x, color);
        OLED_DrawPixel(x0 - y, y0 - x, color);
    }
}

void OLED_Write(word x, word y, char value)
{
    word font_idx = 0;
    word rowcnt = 0;
    word cnt = 0;
    byte b;
    word temp = 0;

    word cbyte, cx, cy;
    word cbit;

    if (cfont.y_size % 8 == 0) {
        font_idx = ((value - cfont.offset)*(cfont.x_size * (cfont.y_size / 8))) + 4;
        for (rowcnt = 0; rowcnt < (cfont.y_size / 8); rowcnt++) {
            for (cnt = 0; cnt < cfont.x_size; cnt++) {
                temp = *(cfont.font + font_idx + cnt + (rowcnt * cfont.x_size));
                for (b = 0; b < 8; b++) {
                    if (temp & (1 << b)) {
                        if (cfont.inverted == 0) OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 1);
                        else OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 0);
                    } else {
                        if (cfont.inverted == 0) OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 0);
                        else OLED_DrawPixel(x + cnt, y + (rowcnt * 8) + b, 1);
                    }
                }
            }
        }
    } else {
        font_idx = ((value - cfont.offset)*((cfont.x_size * cfont.y_size) / 8)) + 4;
        cbyte = *(cfont.font + font_idx);
        cbit = 7;
        for (cx = 0; cx < cfont.x_size; cx++) {
            for (cy = 0; cy < cfont.y_size; cy++) {
                if ((cbyte & (1 << cbit)) != 0) {
                    if (cfont.inverted == 0) OLED_DrawPixel(x + cx, y + cy, 1);
                    else OLED_DrawPixel(x + cx, y + cy, 0);
                } else {
                    if (cfont.inverted == 0) OLED_DrawPixel(x + cx, y + cy, 0);
                    else OLED_DrawPixel(x + cx, y + cy, 1);
                }
                cbit--;
                if (cbit < 0) {
                    cbit = 7;
                    font_idx++;
                    cbyte = *(cfont.font + font_idx);
                }
            }
        }
    }
}

void OLED_Write_Text(word x, word y, const char *text)
{
    byte cnt;
    byte length;

    length = strlen((const char*) text);
    // if (x == RIGHT) x = 128 - (length * cfont.x_size);
    // if (x == CENTER) x = (128 - (length * cfont.x_size)) / 2;
    for (cnt = 0; cnt < length; cnt++) OLED_Write(x + (cnt * (cfont.x_size)), y, *text++);
}

void OLED_Write_Dec(word x, word y, dword data)
{
    char text[30];
    byte cnt;
    byte length;
    sprintf(text, "%d", data);
    length = strlen(text);
    // if (x == RIGHT) x = 128 - (length * cfont.x_size);
    // if (x == CENTER) x = (128 - (length * cfont.x_size)) / 2;
    for (cnt = 0; cnt < length; cnt++) OLED_Write(x + (cnt * (cfont.x_size)), y, text[cnt]);
}

void OLED_Init(void (*startFunc)(void), byte(*writeFunc)(byte), byte(*stopFunc)(void))
{
    oled_i2c_start = startFunc;
    oled_i2c_write = writeFunc;
    oled_i2c_stop = stopFunc;
    ssd1306_command(SSD1306_DISPLAY_OFF);
    ssd1306_command(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    ssd1306_command(0x80);
    ssd1306_command(SSD1306_SET_MULTIPLEX_RATIO);
    ssd1306_command(SSD1306_LCDHEIGHT - 1);
    ssd1306_command(SSD1306_SET_DISPLAY_OFFSET);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_SET_START_LINE | 0x00); // Line: 0
    ssd1306_command(SSD1306_CHARGE_PUMP);
    ssd1306_command(0x14);
    ssd1306_command(SSD1306_MEMORY_ADDR_MODE);
    ssd1306_command(0x00); //Horizontal Addressing Mode is Used
    ssd1306_command(SSD1306_SET_SEGMENT_REMAP | 0x01);
    ssd1306_command(SSD1306_COM_SCAN_DIR_DEC);
    ssd1306_command(SSD1306_SET_COM_PINS);
    ssd1306_command(0x02);
    ssd1306_command(SSD1306_SET_CONTRAST_CONTROL);
    ssd1306_command(0x8F);
    ssd1306_command(SSD1306_SET_PRECHARGE_PERIOD);
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_SET_VCOM_DESELECT);
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAY_ALL_ON_RESUME);
    ssd1306_command(SSD1306_NORMAL_DISPLAY);
    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
    ssd1306_command(SSD1306_DISPLAY_ON);

    OLED_SetFont(SMALL_FONTS);
    OLED_ClearDisplay();
}

void OLED_Update(void)
{
    word i = 0;
    byte x = 0;
    ssd1306_command(SSD1306_SET_COLUMN_ADDR);
    ssd1306_command(0); // Column start address (0 = reset)
    ssd1306_command(SSD1306_LCDWIDTH - 1); // Column end address (127 = reset)
    ssd1306_command(SSD1306_SET_PAGE_ADDR);
    ssd1306_command(0); // Page start address (0 = reset)
    ssd1306_command(3); // Page end address
    for (i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++) {
        DEF_I2C_OLED_START;
        DEF_I2C_OLED_WRITE(SSD1306_ADDR << 1);
        DEF_I2C_OLED_WRITE(0x40);
        for (x = 0; x < 16; x++) {
            DEF_I2C_OLED_WRITE(buffer[i]);
            i++;
        }
        i--;
        DEF_I2C_OLED_STOP;
    }
}

// </editor-fold> 
