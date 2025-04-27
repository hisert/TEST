# 1 "soft_i2c.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "soft_i2c.c" 2
# 1 "./soft_i2c.h" 1
# 15 "./soft_i2c.h"
    volatile unsigned char *pro_adress;

    typedef struct {
        unsigned char *lat_adress;
        unsigned char *tris_adress;
        unsigned char *port_adress;
        unsigned char index;
    } port_t;

    typedef struct {
        port_t SDA;
        port_t SCK;
    } i2c_t;

    void SOFT_I2C_INIT(unsigned char *sda_tris_adress, unsigned char *sda_lat_adress, unsigned char *sda_port_adress, unsigned char sda_index, unsigned char *sck_tris_adress, unsigned char *sck_lat_adress, unsigned char *sck_port_adress, unsigned char sck_index);
    void SOFT_I2C_START();
    unsigned char SOFT_I2C_STOP();
    void SOFT_I2C_SEND_ACK();
    void SOFT_I2C_SEND_NACK();
    unsigned char SOFT_I2C_WRITE(unsigned char data);
    unsigned char SOFT_I2C_READ();
# 2 "soft_i2c.c" 2
i2c_t SOFT_I2C_1;





unsigned char SOFT_I2C_BIT_READ(unsigned char ADRESS, unsigned char index)
{
    ADRESS = ADRESS & (1 << index);
    if (ADRESS) return 1;
    else return 0;
}

void SOFT_I2C_BIT_WRITE(unsigned char *REG_, unsigned char index, unsigned char onOrOff)
{
    unsigned char pro_adress = *REG_;
    if (onOrOff) pro_adress = pro_adress | (unsigned char) (1 << index);
    else pro_adress = pro_adress & ~(unsigned char) (1 << index);
    *(REG_) = pro_adress;
}

void SOFT_I2C_TRIS_WRITE(unsigned char SdaOrSck, unsigned char onOroff)
{
    if (SdaOrSck == 0) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SDA.tris_adress), SOFT_I2C_1.SDA.index, onOroff);
    if (SdaOrSck == 1) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SCK.tris_adress), SOFT_I2C_1.SCK.index, onOroff);
}

void SOFT_I2C_LAT_WRITE(unsigned char SdaOrSck, unsigned char onOroff)
{
    if (SdaOrSck == 0) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SDA.lat_adress), SOFT_I2C_1.SDA.index, onOroff);
    if (SdaOrSck == 1) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SCK.lat_adress), SOFT_I2C_1.SCK.index, onOroff);
}

unsigned char SOFT_I2C_PORT_READ(unsigned char SdaOrSck)
{
    if (SdaOrSck == 0) return SOFT_I2C_BIT_READ(*(SOFT_I2C_1.SDA.port_adress), SOFT_I2C_1.SDA.index);
    if (SdaOrSck == 1) return SOFT_I2C_BIT_READ(*(SOFT_I2C_1.SCK.port_adress), SOFT_I2C_1.SCK.index);
}




void SOFT_I2C_INIT(unsigned char *sda_tris_adress, unsigned char *sda_lat_adress, unsigned char *sda_port_adress, unsigned char sda_index, unsigned char *sck_tris_adress, unsigned char *sck_lat_adress, unsigned char *sck_port_adress, unsigned char sck_index)
{
    SOFT_I2C_1.SDA.tris_adress = sda_tris_adress;
    SOFT_I2C_1.SDA.lat_adress = sda_lat_adress;
    SOFT_I2C_1.SDA.port_adress = sda_port_adress;
    SOFT_I2C_1.SDA.index = sda_index;

    SOFT_I2C_1.SCK.tris_adress = sck_tris_adress;
    SOFT_I2C_1.SCK.lat_adress = sck_lat_adress;
    SOFT_I2C_1.SCK.port_adress = sck_port_adress;
    SOFT_I2C_1.SCK.index = sck_index;

    SOFT_I2C_TRIS_WRITE(0, 1);
    SOFT_I2C_TRIS_WRITE(1, 1);
    SOFT_I2C_LAT_WRITE(0, 0);
    SOFT_I2C_LAT_WRITE(1, 0);
}

void SOFT_I2C_START()
{
    SOFT_I2C_LAT_WRITE(0, 0);
    SOFT_I2C_LAT_WRITE(1, 0);
    SOFT_I2C_TRIS_WRITE(1, 1);
    SOFT_I2C_TRIS_WRITE(0, 1);

    SOFT_I2C_TRIS_WRITE(0, 0);

}

unsigned char SOFT_I2C_STOP()
{
    SOFT_I2C_TRIS_WRITE(1, 0);

    SOFT_I2C_TRIS_WRITE(0, 0);

    SOFT_I2C_TRIS_WRITE(1, 1);

    SOFT_I2C_TRIS_WRITE(0, 1);

    return 0;
}

void SOFT_I2C_SEND_ACK()
{
    SOFT_I2C_TRIS_WRITE(1, 0);

    SOFT_I2C_TRIS_WRITE(0, 0);

    SOFT_I2C_TRIS_WRITE(1, 1);

}

void SOFT_I2C_SEND_NACK()
{
    SOFT_I2C_TRIS_WRITE(1, 0);

    SOFT_I2C_TRIS_WRITE(0, 1);

    SOFT_I2C_TRIS_WRITE(1, 1);

}

unsigned char SOFT_I2C_WRITE(unsigned char data)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SOFT_I2C_TRIS_WRITE(1, 0);

        if ((data << i)&0x80) SOFT_I2C_TRIS_WRITE(0, 1);
        else SOFT_I2C_TRIS_WRITE(0, 0);

        SOFT_I2C_TRIS_WRITE(1, 1);

    }
    SOFT_I2C_TRIS_WRITE(1, 0);
    SOFT_I2C_TRIS_WRITE(0, 1);

    SOFT_I2C_TRIS_WRITE(1, 1);

    return SOFT_I2C_PORT_READ(0);
}

unsigned char SOFT_I2C_READ()
{
    unsigned char i, RxData = 0;
    for (i = 0; i < 8; i++) {
        SOFT_I2C_TRIS_WRITE(1, 0);
        SOFT_I2C_TRIS_WRITE(0, 1);

        SOFT_I2C_TRIS_WRITE(1, 1);

        RxData = (unsigned char) (RxData | (SOFT_I2C_PORT_READ(0) << (7 - i)));

    }
    return RxData;
}
