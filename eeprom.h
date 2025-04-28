#include "common.h"

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

    void EEPROM_INIT(void (*eeprom_byte_write_t)(word adress, byte data), byte(*eeprom_byte_read_t)(word adress));
    void EEPROM_SET(byte index, dword value);
    dword EEPROM_GET(byte index);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

