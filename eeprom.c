#include "eeprom.h"

void (*eeprom_byte_write)(word adress, byte data);
byte(*eeprom_byte_read)(word adress);

void EEPROM_INIT(void (*eeprom_byte_write_t)(word adress, byte data), byte(*eeprom_byte_read_t)(word adress))
{
    eeprom_byte_write = eeprom_byte_write_t;
    eeprom_byte_read = eeprom_byte_read_t;
};

void EEPROM_WRITE_DWORD(word address, dword value)
{
    for (int i = 0; i < 4; i++) {
        byte byte_value = (value >> (8 * i)) & 0xFF; // dü?ük byte önce
        eeprom_byte_write(address + i, byte_value);
    }
}

dword EEPROM_READ_DWORD(word address)
{
    dword value = 0;
    for (int i = 0; i < 4; i++) {
        byte byte_value = eeprom_byte_read(address + i);
        value |= ((dword) byte_value) << (8 * i);
    }
    return value;
}

void EEPROM_SET(byte index, dword value)
{
    EEPROM_WRITE_DWORD((index * 4), value);
}

dword EEPROM_GET(byte index)
{
    return EEPROM_READ_DWORD((index * 4));
}

