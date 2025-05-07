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

#define MOTOR_DIRECTION_RIGHT 1
#define MOTOR_DIRECTION_LEFT 0

#define MOTOR_STANDBY 0x00
#define MOTOR_MAS12_READ_ERROR 0x01
#define MOTOR_BASARILI_DURDU 0x02
#define MOTOR_WORKING 0x04
#define MOTOR_TIME_OUT_DURDU 0x08
#define MOTOR_TORK_DURDU 0x10
#define MOTOR_KOL_TOPLAMA 0x20

    void MOTOR_FIRCASIZ_INIT(void(*motor_pwm_w_kontrol_t)(byte openOrClose), void(*motor_pwm_v_kontrol_t)(byte openOrClose), void(*motor_pwm_u_kontrol_t)(byte openOrClose));
    void MOTOR_PWM_INIT(void(*motor_pwm_1_t)(byte), void(*motor_pwm_2_t)(byte), void(*motor_pwm_3_t)(byte));
    void MOTOR_PWM_LOAD(byte pwm_select, byte pwm_value);
    void MOTOR_PWM_LOAD_ALL(byte pwm_value);
    void MOTOR_PWM_LOAD(byte MOTOR_DIRECTION, byte pwm_value);

    byte MOTOR_START(word stop_index);
    void MOTOR_STOP();
    byte MOTOR_PROCESS(word torkVal);

    void MOTOR_START_LAST_SUCCESS_INDEX();
    void MOTOR_PID_INIT(float Ki, float Kp);
    void MOTOR_INIT_MAX_HIZ(byte max);
    void MOTOR_TIME_OUT_SET(word outTime);
    byte MOTOR_TIME_OUT_CHECK();
    void FIRCASIZ_READ(byte HU, byte HV, byte HW);

    void MOTOR_SET_KOL_TOPLAMA_TOLERANS(word val);
    word MOTOR_GET_KOL_TOPLAMA_TOLERANS();
    void MOTOR_SET_Z_POINT(word val);
    word MOTOR_GET_Z_POINT();
    word MOTOR_GET_LAST_SUCESS_INDEX();
    word MOTOR_GET_MAS12_HAM();
    word MOTOR_GET_MAS12_MAPPED();

#ifdef	__cplusplus
}
#endif

#endif	/* AS5600_MAS_H */

