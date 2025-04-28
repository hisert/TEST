
#ifndef SOFT_I2C_H
#include "common.h"
#define	SOFT_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        byte *lat_adress;
        byte *tris_adress;
        byte *port_adress;
        byte index;
    } port_t;

    typedef struct {
        port_t SDA;
        port_t SCK;
    } i2c_t;

    void SOFT_I2C_INIT(byte *sda_tris_adress, byte *sda_lat_adress, byte *sda_port_adress, byte sda_index, byte *sck_tris_adress, byte *sck_lat_adress, byte *sck_port_adress, byte sck_index);
    void SOFT_I2C_START();
    byte SOFT_I2C_STOP();
    void SOFT_I2C_SEND_ACK();
    void SOFT_I2C_SEND_NACK();
    byte SOFT_I2C_WRITE(byte data);
    byte SOFT_I2C_READ();

#ifdef	__cplusplus
}
#endif

#endif	/* SOFT_I2C_H */

