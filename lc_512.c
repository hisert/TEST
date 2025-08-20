#include "lc_512.h"

#ifdef USE_LC512

// <editor-fold defaultstate="collapsed" desc="CLASS FUNCTS">
byte LC512_ADDRESS = 0x50;

void (*lc512_i2c_start)(void);
byte(*lc512_i2c_write)(byte data);
byte(*lc512_i2c_read_ack)(void);
byte(*lc512_i2c_read_nack)(void);
void(*lc512_i2c_stop)(void);

void LC512_WAIT_MS(byte wait)
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

void LC512_WriteByte(word addr, byte data)
{
    lc512_i2c_start();
    lc512_i2c_write(LC512_ADDRESS << 1); // Write mode
    lc512_i2c_write((byte) (addr >> 8)); // High addr
    lc512_i2c_write((byte) (addr & 0xFF)); // Low addr
    lc512_i2c_write(data);
    lc512_i2c_stop();
    LC512_WAIT_MS(40);
}

byte LC512_ReadByte(word addr)
{
    byte data;
    lc512_i2c_start();
    lc512_i2c_write(LC512_ADDRESS << 1); // Write mode
    lc512_i2c_write((byte) (addr >> 8));
    lc512_i2c_write((byte) (addr & 0xFF));
    lc512_i2c_stop();
    lc512_i2c_start();
    lc512_i2c_write((LC512_ADDRESS << 1) | 1); // Read mode
    data = lc512_i2c_read_nack();
    lc512_i2c_stop();
    return data;
}

void LC512_WriteBuffer(word addr, byte *buf, word len)
{
    while (len > 0) {
        lc512_i2c_start();
        lc512_i2c_write(LC512_ADDRESS << 1);
        lc512_i2c_write((byte) (addr >> 8));
        lc512_i2c_write((byte) (addr & 0xFF));

        word i = 0;
        while (len > 0 && i < 128) { // 128 byte page limit
            lc512_i2c_write(*buf++);
            addr++;
            len--;
            i++;
        }
        lc512_i2c_stop();
        LC512_WAIT_MS(40);
    }
}

void LC512_ReadBuffer(word addr, byte *buf, word len)
{
    lc512_i2c_start();
    lc512_i2c_write(LC512_ADDRESS << 1);
    lc512_i2c_write((byte) (addr >> 8));
    lc512_i2c_write((byte) (addr & 0xFF));

    lc512_i2c_start();
    lc512_i2c_write((LC512_ADDRESS << 1) | 1);

    for (word i = 0; i < len; i++) {
        if (i == (len - 1)) buf[i] = lc512_i2c_read_nack();
        else buf[i] = lc512_i2c_read_ack();
    }
    lc512_i2c_stop();
}
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="USER FUNCTS">

void LC512_Init(void (*startFunc)(void), byte(*writeFunc)(byte), byte(*read_ack)(void), byte(*read_nack)(void), void(*stopFunc)(void))
{
    lc512_i2c_start = startFunc;
    lc512_i2c_write = writeFunc;
    lc512_i2c_read_ack = read_ack;
    lc512_i2c_read_nack = read_nack;
    lc512_i2c_stop = stopFunc;
}

void LC512_Adress(byte addres)
{
    LC512_ADDRESS = addres;
}
// </editor-fold>

#endif

//KULLANIM ORNEGI
//SOFT_I2C_INIT(&DDRD, &PORTD, &PIND, 1, &DDRD, &PORTD, &PIND, 0);
//LC512_Init(&SOFT_I2C_START, &SOFT_I2C_WRITE, &SOFT_I2C_READ_ACK, &SOFT_I2C_READ_NACK, &SOFT_I2C_STOP);
//LC512_Adress(0x50);


