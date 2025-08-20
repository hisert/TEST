#include "common.h"


#ifndef HC595_H
#define	HC595_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef USE_HC595

    typedef struct {
        volatile unsigned char *lat_adress;
        byte index;
    } pin2_t;

    void HC595_Init(volatile unsigned char *sh_lat, byte sh_index, volatile unsigned char *ds_lat, byte ds_index, volatile unsigned char *st_lat, byte st_index);
    void HC595_WriteData(dword data, byte len);
    void HC595_WriteBytes(byte *data, byte len);

#endif


#ifdef	__cplusplus
}
#endif

#endif	/* HC595_H */

