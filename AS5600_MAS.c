#include "AS5600_MAS.h"

void (*mas_i2c_start)(void);
byte(*mas_i2c_write)(byte data);
byte(*mas_i2c_read_ack)(void);
byte(*mas_i2c_read_nack)(void);
void(*mas_i2c_stop)(void);

word MAS12_READ_HAL_DATA()
  {
  byte data_low;
  byte data_high;
  byte errorflag = 0;
  mas_i2c_start();
  if (mas_i2c_write(108) == 1) errorflag++;
  if (mas_i2c_write(12) == 1) errorflag++;
  mas_i2c_stop();
  mas_i2c_start();
  if (mas_i2c_write(109) == 1) errorflag++;
  data_high = mas_i2c_read_ack();
  data_low = mas_i2c_read_nack();
  mas_i2c_stop();
  if (errorflag) return 0xFFFF;
  return (data_high * 256 + data_low);
  }

word MAS12_READ_MAG_DATA()
  {
  byte data_low;
  byte data_high;
  byte errorflag = 0;
  mas_i2c_start();
  if (mas_i2c_write(108) == 1) errorflag++;
  if (mas_i2c_write(27) == 1) errorflag++;
  mas_i2c_stop();
  mas_i2c_start();
  if (mas_i2c_write(109) == 1) errorflag++;
  data_high = mas_i2c_read_ack();
  data_low = mas_i2c_read_nack();
  mas_i2c_stop();
  if (errorflag) return 0xFFFF;
  return (data_high * 256 + data_low);
  }

signed int MAS12_REMAP(word middpoint, word index)
  {
  signed int fark;
  signed int data;
  if (index >= middpoint)
    {
    fark = index - middpoint;
    if (fark >= 2047) data = (4095 - fark) * -1; //SOLDA
    else data = fark; //SAGDA
    }
  else
    {
    fark = middpoint - index;
    if (fark >= 2047) data = (4095 - fark); //SAGDA
    else data = fark * -1; //SOLDA
    }

  data += 2047; // 2047 ötele orta nokta 2047
  return data;
  }

void MAS12_INIT(void (*mas_i2c_start_t)(void), byte(*mas_i2c_write_t)(byte data), byte(*mas_i2c_read_ack_t)(void), byte(*mas_i2c_read_nack_t)(void), void(*mas_i2c_stop_t)(void))
  {
  mas_i2c_start = mas_i2c_start_t;
  mas_i2c_write = mas_i2c_write_t;
  mas_i2c_read_ack = mas_i2c_read_ack_t;
  mas_i2c_read_nack = mas_i2c_read_nack_t;
  mas_i2c_stop = mas_i2c_stop_t;
  }

