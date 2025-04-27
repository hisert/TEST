
#ifndef INPUT_DEBOUNCE_H
#define	INPUT_DEBOUNCE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#define qword unsigned long long
#define open 1
#define close 0

    typedef struct {
        byte Temp_Counter;
        byte Old_state;
    } Input_t;

#define NO_CHANGEE 0x00
#define INPUT_RAISE_EDGE 0x01
#define IINPUT_FALL_EDGE 0x02

    byte INPUT_DEBOUNCE(Input_t *Input, byte Input_Val, byte Debounce);


#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_DEBOUNCE_H */

