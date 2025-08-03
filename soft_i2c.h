
#ifndef SOFT_I2C_H
#include "common.h"
#define	SOFT_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        volatile unsigned char *lat_adress;
        volatile unsigned char *tris_adress;
        volatile unsigned char *port_adress;
        byte index;
    } port_t;

    typedef struct {
        port_t SDA;
        port_t SCK;
    } i2c_t;

    void SOFT_I2C_INIT(volatile unsigned char *sda_tris_adress, volatile unsigned char *sda_lat_adress, volatile unsigned char *sda_port_adress, byte sda_index, volatile unsigned char *sck_tris_adress, volatile unsigned char *sck_lat_adress, volatile unsigned char *sck_port_adress, byte sck_index);
    void SOFT_I2C_START();
    void SOFT_I2C_STOP();
    void SOFT_I2C_SEND_ACK();
    void SOFT_I2C_SEND_NACK();
    byte SOFT_I2C_WRITE(byte data);
    byte SOFT_I2C_READ();
    byte SOFT_I2C_READ_ACK();
    byte SOFT_I2C_READ_NACK();
    byte SOFT_I2C_TEST();

#ifdef	__cplusplus
}
#endif

#endif	/* SOFT_I2C_H */

