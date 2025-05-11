#include "soft_i2c.h"

#ifdef USE_SOFT_I2C

i2c_t SOFT_I2C_1;
#define PORT_SDA 0
#define PORT_SCK 1
// <editor-fold defaultstate="collapsed" desc="CLASS FUNCTS">

byte SOFT_I2C_BIT_READ(byte ADRESS, byte index)
  {
  ADRESS = ADRESS & (1 << index);
  if (ADRESS) return 1;
  else return 0;
  }

void SOFT_I2C_BIT_WRITE(byte *REG_, byte index, byte onOrOff)
  {
  byte pro_adress = *REG_;
  if (onOrOff) pro_adress = pro_adress | (byte) (1 << index);
  else pro_adress = pro_adress & ~(byte) (1 << index);
  *(REG_) = pro_adress;
  }

void SOFT_I2C_TRIS_WRITE(byte SdaOrSck, byte onOroff)
  {
#if defined(__AVR_ATmega64__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__)
  if (onOroff) onOroff = 0;
  else onOroff = 1;
#endif

  if (SdaOrSck == PORT_SDA) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SDA.tris_adress), SOFT_I2C_1.SDA.index, onOroff);
  if (SdaOrSck == PORT_SCK) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SCK.tris_adress), SOFT_I2C_1.SCK.index, onOroff);
  }

void SOFT_I2C_LAT_WRITE(byte SdaOrSck, byte onOroff)
  {

  if (SdaOrSck == PORT_SDA) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SDA.lat_adress), SOFT_I2C_1.SDA.index, onOroff);
  if (SdaOrSck == PORT_SCK) SOFT_I2C_BIT_WRITE((SOFT_I2C_1.SCK.lat_adress), SOFT_I2C_1.SCK.index, onOroff);
  }

byte SOFT_I2C_PORT_READ(byte SdaOrSck)
  {
  if (SdaOrSck == PORT_SDA) return SOFT_I2C_BIT_READ(*(SOFT_I2C_1.SDA.port_adress), SOFT_I2C_1.SDA.index);
  if (SdaOrSck == PORT_SCK) return SOFT_I2C_BIT_READ(*(SOFT_I2C_1.SCK.port_adress), SOFT_I2C_1.SCK.index);
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="FOR USER">

void SOFT_I2C_INIT(byte *sda_tris_adress, byte *sda_lat_adress, byte *sda_port_adress, byte sda_index, byte *sck_tris_adress, byte *sck_lat_adress, byte *sck_port_adress, byte sck_index)
  {
  SOFT_I2C_1.SDA.tris_adress = sda_tris_adress;
  SOFT_I2C_1.SDA.lat_adress = sda_lat_adress;
  SOFT_I2C_1.SDA.port_adress = sda_port_adress;
  SOFT_I2C_1.SDA.index = sda_index;

  SOFT_I2C_1.SCK.tris_adress = sck_tris_adress;
  SOFT_I2C_1.SCK.lat_adress = sck_lat_adress;
  SOFT_I2C_1.SCK.port_adress = sck_port_adress;
  SOFT_I2C_1.SCK.index = sck_index;

  SOFT_I2C_TRIS_WRITE(PORT_SDA, 1);
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
  SOFT_I2C_LAT_WRITE(PORT_SDA, 0);
  SOFT_I2C_LAT_WRITE(PORT_SCK, 0);
  }

void SOFT_I2C_START()
  {
  SOFT_I2C_LAT_WRITE(PORT_SDA, 0);
  SOFT_I2C_LAT_WRITE(PORT_SCK, 0);
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
  SOFT_I2C_TRIS_WRITE(PORT_SDA, 1);
  // (SOFT_I2C_CLK_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SDA, 0);
  // (SOFT_I2C_CLK_DELAY);
  }

byte SOFT_I2C_STOP()
  {
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 0);
  // (SOFT_I2C_CLK_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SDA, 0);
  // (SOFT_I2C_DATA_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
  // (SOFT_I2C_CLK_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SDA, 1);
  // (SOFT_I2C_DATA_DELAY);
  return 0;
  }

void SOFT_I2C_SEND_ACK()
  {
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 0);
  // (SOFT_I2C_CLK_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SDA, 0);
  // (SOFT_I2C_DATA_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
  // (SOFT_I2C_CLK_DELAY);
  }

void SOFT_I2C_SEND_NACK()
  {
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 0);
  // (SOFT_I2C_CLK_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SDA, 1);
  // (SOFT_I2C_DATA_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
  // (SOFT_I2C_CLK_DELAY);
  }

byte SOFT_I2C_WRITE(byte data)
  {
  unsigned char i;
  for (i = 0; i < 8; i++)
    {
    SOFT_I2C_TRIS_WRITE(PORT_SCK, 0);
    // (SOFT_I2C_CLK_DELAY);
    if ((data << i)&0x80) SOFT_I2C_TRIS_WRITE(PORT_SDA, 1);
    else SOFT_I2C_TRIS_WRITE(PORT_SDA, 0);
    // (SOFT_I2C_DATA_DELAY);
    SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
    // (SOFT_I2C_CLK_DELAY);
    }
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 0);
  SOFT_I2C_TRIS_WRITE(PORT_SDA, 1);
  // (SOFT_I2C_DATA_DELAY);
  SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
  // (SOFT_I2C_DATA_DELAY);
  return SOFT_I2C_PORT_READ(PORT_SDA);
  }

byte SOFT_I2C_READ()
  {
  unsigned char i, RxData = 0;
  for (i = 0; i < 8; i++)
    {
    SOFT_I2C_TRIS_WRITE(PORT_SCK, 0);
    SOFT_I2C_TRIS_WRITE(PORT_SDA, 1);
    // (SOFT_I2C_CLK_DELAY);
    SOFT_I2C_TRIS_WRITE(PORT_SCK, 1);
    // (SOFT_I2C_DATA_DELAY);
    RxData = (byte) (RxData | (SOFT_I2C_PORT_READ(PORT_SDA) << (7 - i)));
    // (SOFT_I2C_DATA_DELAY);
    }
  return RxData;
  }

// </editor-fold>

#endif
