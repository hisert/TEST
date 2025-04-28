#include "common.h"

#ifndef AS5600_MAS_H
#define	AS5600_MAS_H

#ifdef	__cplusplus
extern "C" {
#endif

    word MAS12_READ_HAL_DATA();
    word MAS12_READ_MAG_DATA();
    signed int MAS12_REMAP(word middpoint, word index);
    void MAS12_INIT(void (*mas_i2c_start_t)(void), byte(*mas_i2c_write_t)(byte data), byte(*mas_i2c_read_ack_t)(void), byte(*mas_i2c_read_nack_t)(void), void(*mas_i2c_stop_t)(void));

#ifdef	__cplusplus
}
#endif

#endif	/* AS5600_MAS_H */

