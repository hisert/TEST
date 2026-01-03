#include "common.h"

#ifndef LC_512_H
#define	LC_512_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef USE_LC512

    void LC512_WriteByte(word addr, byte data);
    byte LC512_ReadByte(word addr);
    void LC512_WriteBuffer(word addr, byte *buf, word len);
    void LC512_ReadBuffer(word addr, byte *buf, word len);
    void LC512_WriteString(word startAddr, const char *str, byte length);
    void LC512_WriteDec(word startAddr, qword data, byte length);
    qword LC512_ReadDec(word startAddr, byte length);
    void LC512_Init(void (*startFunc)(void), byte(*writeFunc)(byte), byte(*read_ack)(void), byte(*read_nack)(void), void(*stopFunc)(void));
    void LC512_Adress(byte addres);

#endif


#ifdef	__cplusplus
}
#endif

#endif	/* LC_512_H */

