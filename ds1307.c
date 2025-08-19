#include "ds1307.h"

#ifdef USE_DS1307
// <editor-fold defaultstate="collapsed" desc="CLASS FUNCTS">
DS1307_time_t DS107_Time;
#define DS1307_ADDRESS 0x68

void (*ds1307_i2c_start)(void);
byte(*ds1307_i2c_write)(byte data);
byte(*ds1307_i2c_read_ack)(void);
byte(*ds1307_i2c_read_nack)(void);
void(*ds1307_i2c_stop)(void);

byte bcd2dec(byte val)
{
    return (val >> 4) * 10 + (val & 0x0F);
}

byte dec2bcd(byte val)
{
    return ((val / 10) << 4) | (val % 10);
}

void DS1307_WriteReg(byte reg, byte *data, byte len)
{
    ds1307_i2c_start();
    ds1307_i2c_write(DS1307_ADDRESS << 1); // write
    ds1307_i2c_write(reg);
    for (byte i = 0; i < len; i++) ds1307_i2c_write(data[i]);
    ds1307_i2c_stop();
}

void DS1307_ReadReg(byte reg, byte *data, byte len)
{
    ds1307_i2c_start();
    ds1307_i2c_write(DS1307_ADDRESS << 1); // Write mode
    ds1307_i2c_write(reg);
    ds1307_i2c_stop(); // baz? kütüphanelerde stop-start gerekebilir

    ds1307_i2c_start();
    ds1307_i2c_write((DS1307_ADDRESS << 1) | 1); // Read mode

    for (byte i = 0; i < len; i++) {
        if (i == (len - 1)) data[i] = ds1307_i2c_read_nack();
        else data[i] = ds1307_i2c_read_ack();
    }
    ds1307_i2c_stop();
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="USER FUNCTS">

void DS1307_Init(void (*startFunc)(void), byte(*writeFunc)(byte), byte(*read_ack)(void), byte(*read_nack)(void), void(*stopFunc)(void))
{
    ds1307_i2c_start = startFunc;
    ds1307_i2c_write = writeFunc;
    ds1307_i2c_read_ack = read_ack;
    ds1307_i2c_read_nack = read_nack;
    ds1307_i2c_stop = stopFunc;

    byte sec;
    DS1307_ReadReg(0x00, &sec, 1);
    sec &= 0x7F; // CH=0 -> osilatörü aç
    DS1307_WriteReg(0x00, &sec, 1);
}

void DS1307_SetTime(byte hour, byte minute, byte second)
{
    byte buf[3];
    buf[0] = dec2bcd(second & 0x7F);
    buf[1] = dec2bcd(minute);
    buf[2] = dec2bcd(hour);
    DS1307_WriteReg(0x00, buf, 3);
}

void DS1307_SetDate(byte dayOfWeek, byte day, byte month, word year)
{
    byte buf[4];
    buf[0] = dec2bcd(dayOfWeek);
    buf[1] = dec2bcd(day);
    buf[2] = dec2bcd(month);
    buf[3] = dec2bcd(year % 100);
    DS1307_WriteReg(0x03, buf, 4);
}

void DS1307_GetDateTime()
{
    byte buf[7];
    DS1307_ReadReg(0x00, buf, 7);
    DS107_Time.second = bcd2dec(buf[0] & 0x7F);
    DS107_Time.minute = bcd2dec(buf[1]);
    DS107_Time.hour = bcd2dec(buf[2] & 0x3F);
    DS107_Time.dayOfWeek = bcd2dec(buf[3]);
    DS107_Time.day = bcd2dec(buf[4]);
    DS107_Time.month = bcd2dec(buf[5]);
    DS107_Time.year = 2000 + bcd2dec(buf[6]);
}

// </editor-fold>
#endif

//KULLANIM ORNEGI
//extern DS1307_time_t DS107_Time;
//SOFT_I2C_INIT(&DDRD, &PORTD, &PIND, 1, &DDRD, &PORTD, &PIND, 0);
//DS1307_Init(&SOFT_I2C_START, &SOFT_I2C_WRITE, &SOFT_I2C_READ_ACK, &SOFT_I2C_READ_NACK, &SOFT_I2C_STOP);
//DS1307_SetTime(1, 2, 3);
//DS1307_SetDate(4, 5, 6, 7);
//DS1307_GetDateTime();


