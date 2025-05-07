#include "AS5600_MAS.h"
#include "input_debounce.h"

#define bit_set(register_value, bit_position) ((register_value) |= (1 << (bit_position)))

#define U_ENABLE     PORTD = PORTD | 4
#define U_DISABLE    PORTD = PORTD & ~(4)
#define V_ENABLE     PORTD = PORTD | 16
#define V_DISABLE    PORTD = PORTD & ~(16)
#define W_ENABLE     PORTD = PORTD | 128
#define W_DISABLE    PORTD = PORTD & ~(128)

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

#define MOTOR_KACIRMA_KURTARMA_TIME_MS 10

byte MOTOR_WORK = 0;
byte MOTOR_SUCCES = 0;
word MOTOR_STOP_INDEX = 0;
word MOTOR_START_INDEX = 0;
byte MOTOR_KACIRMA_KURTARMA = 0;
byte MOTOR_PWM_VAL = 0;

byte MOTOR_DIRECTION = 0;
byte MOTOR_MODE = 0;
word MAS12_NOW = 0;
word MAS12_NOW_MAPPED = 0;
word MOTOR_Z_POINT_INDEX = 0;
word MOTOR_TEKRAR_HAREKET_BASLAMA_TOLERANS = 0;
word MOTOR_TIME_OUT = 0;
word MOTOR_TIME_OUT_TEMP = 0;
word MOTOR_LAST_SUCCESS_INDEX = 2047;
word MOTOR_TORK_SINIR = 0;

byte MOTOR_HIZ = 0;
byte MOTOR_HIZ_MAX = 0;

byte PID_MIN_PWM = 0;
byte PID_MAX_PWM = 75;
float PID_INTEGRATED = 0;
float PID_Kp = 0;
float PID_Ki = 0;

void(*motor_pwm_w)(byte pwm);
void(*motor_pwm_v)(byte pwm);
void(*motor_pwm_u)(byte pwm);

void MAS12_INIT(void (*mas_i2c_start_t)(void), byte(*mas_i2c_write_t)(byte data), byte(*mas_i2c_read_ack_t)(void), byte(*mas_i2c_read_nack_t)(void), void(*mas_i2c_stop_t)(void))
  {
  mas_i2c_start = mas_i2c_start_t;
  mas_i2c_write = mas_i2c_write_t;
  mas_i2c_read_ack = mas_i2c_read_ack_t;
  mas_i2c_read_nack = mas_i2c_read_nack_t;
  mas_i2c_stop = mas_i2c_stop_t;
  }

byte MOTOR_PID_RESET()
  {
  PID_INTEGRATED = 0;
  }

byte MAS12_UPDATE()
  {
  static word MAPPED_OLD = 0;
  word TEMP = MAS12_READ_HAL_DATA();
  if (TEMP == 0xFFFF) return 1;
  MAS12_NOW = TEMP;
  MAS12_NOW_MAPPED = MAS12_REMAP(MOTOR_Z_POINT_INDEX, MAS12_NOW);
  MOTOR_HIZ = abs(MAPPED_OLD - MAS12_NOW_MAPPED);
  MAPPED_OLD = MAS12_NOW_MAPPED;
  return 0;
  }

void MOTOR_PWM_INIT(void(*motor_pwm_w_t)(byte), void(*motor_pwm_v_t)(byte), void(*motor_pwm_u_t)(byte))
  {
  motor_pwm_w = motor_pwm_w_t;
  motor_pwm_v = motor_pwm_v_t;
  motor_pwm_u = motor_pwm_u_t;
  if (motor_pwm_w != 0) motor_pwm_w(0);
  if (motor_pwm_v != 0) motor_pwm_v(0);
  if (motor_pwm_u != 0) motor_pwm_u(0);
  }

void MOTOR_PWM_LOAD(byte pwm_select, byte pwm_value)
  {
  if (pwm_select == 1) motor_pwm_w(pwm_value);
  if (pwm_select == 2) motor_pwm_v(pwm_value);
  if (pwm_select == 3) motor_pwm_u(pwm_value);
  }

void MOTOR_PWM_LOAD_ALL(byte pwm_value)
  {
  if (MOTOR_MODE == MOTOR_MODE_FIRCALI)
    {
    motor_pwm_v(pwm_value);
    motor_pwm_u(pwm_value);
    }
  if (MOTOR_MODE == MOTOR_MODE_FIRCASIZ)
    {
    if (MOTOR_WORK) MOTOR_PWM_VAL = pwm_value;
    else
      {
      motor_pwm_v(pwm_value);
      motor_pwm_u(pwm_value);
      motor_pwm_w(pwm_value);
      }
    }
  }

void MOTOR_PWM(byte MOTOR_DIRECTION, byte pwm_value)
  {
  if (MOTOR_MODE == MOTOR_MODE_FIRCALI)
    {
    if (MOTOR_DIRECTION == MOTOR_DIRECTION_RIGHT)
      {
      MOTOR_PWM_LOAD(2, pwm_value);
      MOTOR_PWM_LOAD(3, 0);
      }
    if (MOTOR_DIRECTION == MOTOR_DIRECTION_LEFT)
      {
      MOTOR_PWM_LOAD(3, pwm_value);
      MOTOR_PWM_LOAD(2, 0);
      }
    }
  if (MOTOR_MODE == MOTOR_MODE_FIRCASIZ) MOTOR_PWM_LOAD_ALL(pwm_value);
  }

byte MOTOR_LOOKING_STOP()
  {
  if (MOTOR_DIRECTION == MOTOR_DIRECTION_RIGHT) if (MAS12_NOW_MAPPED > MOTOR_STOP_INDEX) return 1;
  if (MOTOR_DIRECTION == MOTOR_DIRECTION_LEFT) if (MAS12_NOW_MAPPED < MOTOR_STOP_INDEX) return 1;
  return 0;
  }

byte MOTOR_PID_CONTROL()
  {
  word kalan = abs(MAS12_NOW_MAPPED - MOTOR_STOP_INDEX);
  word all = abs(MOTOR_START_INDEX - MOTOR_STOP_INDEX);
  static byte tekrar_kalkma_counter = 0;
  float Setpoint = kalan / 50; //Pid.wanted_speed;
  if (MOTOR_MODE == MOTOR_MODE_FIRCALI)
    {
    if (kalan > ((all * 9) / 10)) Setpoint = 6;
    else if (kalan > ((all * 8) / 10)) Setpoint = 9;
    if (kalan < 300) Setpoint = 1;
    }

  if (Setpoint > MOTOR_HIZ_MAX) Setpoint = MOTOR_HIZ_MAX;
  if (MOTOR_HIZ == 0)
    {
    if (tekrar_kalkma_counter < 30) tekrar_kalkma_counter++;
    PID_MIN_PWM = tekrar_kalkma_counter;
    }
  else
    {
    tekrar_kalkma_counter = 0;
    PID_MIN_PWM = 0;
    }
  float inputvalue = MOTOR_HIZ;
  float Theerr = Setpoint - inputvalue;
  PID_INTEGRATED = PID_INTEGRATED + (Theerr * PID_Ki);
  float Result = (Theerr * PID_Kp) + PID_INTEGRATED;
  if (Result > PID_MAX_PWM)
    {
    PID_INTEGRATED = PID_MAX_PWM;
    Result = PID_INTEGRATED;
    }
  if (Result < PID_MIN_PWM)
    {
    PID_INTEGRATED = PID_MIN_PWM;
    Result = PID_INTEGRATED;
    }
  return Result;
  }

//------------

void MOTOR_INIT(byte c)
  {
  MOTOR_MODE = c;
  }

byte MOTOR_START(word stop_index)
  {
  if (MAS12_UPDATE()) return;
  if (MOTOR_WORK == 0) if (abs(MAS12_NOW_MAPPED - stop_index) < MOTOR_TEKRAR_HAREKET_BASLAMA_TOLERANS) return 0;
  MOTOR_PID_RESET();
  MOTOR_START_INDEX = MAS12_NOW_MAPPED;
  MOTOR_STOP_INDEX = stop_index;
  if (MOTOR_MODE == MOTOR_MODE_FIRCALI)
    {
    if (MAS12_NOW_MAPPED > MOTOR_STOP_INDEX) MOTOR_DIRECTION = MOTOR_DIRECTION_LEFT;
    else MOTOR_DIRECTION = MOTOR_DIRECTION_RIGHT;
    }
  if (MOTOR_MODE == MOTOR_MODE_FIRCASIZ)
    {
    if (MAS12_NOW_MAPPED > MOTOR_STOP_INDEX) MOTOR_DIRECTION = MOTOR_DIRECTION_LEFT;
    else MOTOR_DIRECTION = MOTOR_DIRECTION_RIGHT;
    }
  MOTOR_TIME_OUT_TEMP = MOTOR_TIME_OUT;
  MOTOR_WORK = 1;
  return 1;
  }

void MOTOR_STOP()
  {
  MOTOR_WORK = 0;
  MOTOR_PWM_LOAD_ALL(0);
  }

byte MOTOR_PROCESS(word torkVal)
  {
  byte rtrnval = MOTOR_STANDBY;
  byte stopFlag = 0;
  byte Mas_err_flag = MAS12_UPDATE();
  if (Mas_err_flag) rtrnval = MOTOR_MAS12_READ_ERROR;
  if (MOTOR_WORK)
    {
    if (Mas_err_flag)
      {
      MOTOR_SUCCES = 0;
      stopFlag = 1;
      }
    else if (MOTOR_LOOKING_STOP())
      {
      MOTOR_SUCCES = 1;
      stopFlag = 1;
      rtrnval = MOTOR_BASARILI_DURDU;
      MOTOR_LAST_SUCCESS_INDEX = MOTOR_STOP_INDEX;
      }
    else if (MOTOR_TIME_OUT_TEMP > MOTOR_TIME_OUT)
      {
      MOTOR_SUCCES = 0;
      stopFlag = 1;
      rtrnval = MOTOR_TIME_OUT_DURDU;
      }
    else if (torkVal > MOTOR_TORK_SINIR)
      {
      MOTOR_SUCCES = 0;
      stopFlag = 1;
      rtrnval = MOTOR_TORK_DURDU;
      }
    if (stopFlag) MOTOR_STOP();
    else
      {
      rtrnval = MOTOR_WORKING;
      MOTOR_PWM(MOTOR_DIRECTION, MOTOR_PID_CONTROL());
      }
    }
  else
    {
    if (MOTOR_SUCCES)
      {
      if (abs(MAS12_NOW_MAPPED - MOTOR_LAST_SUCCESS_INDEX) > MOTOR_TEKRAR_HAREKET_BASLAMA_TOLERANS)
        {
        if (MOTOR_START(MOTOR_LAST_SUCCESS_INDEX)) rtrnval = MOTOR_KOL_TOPLAMA;
        }
      }
    }
  return rtrnval;
  }

void MOTOR_TORK_SET(word tork)
  {
  MOTOR_TORK_SINIR = tork;
  }

void MOTOR_PID_INIT(float Ki, float Kp)
  {
  PID_Kp = Kp;
  PID_Ki = Ki;
  }

void MOTOR_INIT_MAX_HIZ(byte max)
  {
  MOTOR_HIZ_MAX = max;
  }

void MOTOR_TIME_OUT_SET(word outTime)
  {
  MOTOR_TIME_OUT = outTime;
  }

byte MOTOR_TIME_OUT_CHECK()
  {
  if (MOTOR_WORK)
    {
    if (MOTOR_TIME_OUT_TEMP < 0xFFFF) MOTOR_TIME_OUT_TEMP++;
    if (MOTOR_MODE == MOTOR_MODE_FIRCASIZ)
      {
      if (MOTOR_KACIRMA_KURTARMA) MOTOR_KACIRMA_KURTARMA--;
      else return 1;
      }
    }
  return 0;
  }

void MOTOR_START_LAST_SUCCESS_INDEX()
  {
  MOTOR_START(MOTOR_LAST_SUCCESS_INDEX);
  }
//--------------------

void FIRCASIZ_STEP(byte Hall)
  {
  W_DISABLE;
  W_DISABLE;
  W_DISABLE;
  if (Hall == 0)
    {
    U_ENABLE;
    V_ENABLE;
    W_DISABLE;
    motor_pwm_u(MOTOR_PWM_VAL);
    motor_pwm_v(0);
    motor_pwm_w(0);
    }
  else if (Hall == 1)
    {
    U_ENABLE;
    V_DISABLE;
    W_ENABLE;
    motor_pwm_u(MOTOR_PWM_VAL);
    motor_pwm_v(0);
    motor_pwm_w(0);
    }
  else if (Hall == 2)
    {
    U_DISABLE;
    V_ENABLE;
    W_ENABLE;
    motor_pwm_u(0);
    motor_pwm_v(MOTOR_PWM_VAL);
    motor_pwm_w(0);
    }
  else if (Hall == 3)
    {
    U_ENABLE;
    V_ENABLE;
    W_DISABLE;
    motor_pwm_u(0);
    motor_pwm_v(MOTOR_PWM_VAL);
    motor_pwm_w(0);
    }
  else if (Hall == 4)
    {
    U_ENABLE;
    V_DISABLE;
    W_ENABLE;
    motor_pwm_u(0);
    motor_pwm_v(0);
    motor_pwm_w(MOTOR_PWM_VAL);
    }
  else if (Hall == 5)
    {
    U_DISABLE;
    V_ENABLE;
    W_ENABLE;
    motor_pwm_u(0);
    motor_pwm_v(0);
    motor_pwm_w(MOTOR_PWM_VAL);
    }
  }

void FIRCASIZ_DON(byte Hall)
  {
  if (MOTOR_DIRECTION == MOTOR_DIRECTION_RIGHT)
    {
    if (Hall == 5) Hall = 0;
    else if (Hall == 1) Hall = 1;
    else if (Hall == 3) Hall = 2;
    else if (Hall == 2) Hall = 3;
    else if (Hall == 6) Hall = 4;
    else if (Hall == 4) Hall = 5;
    }
  else if (MOTOR_DIRECTION == MOTOR_DIRECTION_LEFT)
    {
    if (Hall == 5) Hall = 5;
    else if (Hall == 1) Hall = 4;
    else if (Hall == 3) Hall = 3;
    else if (Hall == 2) Hall = 2;
    else if (Hall == 6) Hall = 1;
    else if (Hall == 4) Hall = 0;
    }
  FIRCASIZ_STEP(Hall);
  }

void FIRCASIZ_READ(byte HU, byte HV, byte HW)
  {
  if (MOTOR_WORK == 0) return;
  MOTOR_KACIRMA_KURTARMA = MOTOR_KACIRMA_KURTARMA_TIME_MS;
  byte Hall = 0;
  if (HU) bit_set(Hall, 0); // Hall+=1;
  if (MOTOR_DIRECTION == MOTOR_DIRECTION_RIGHT)
    {
    if (HV) bit_set(Hall, 1); //Hall+=2;
    if (HW) bit_set(Hall, 2); //Hall+=4;
    }
  else if (MOTOR_DIRECTION == MOTOR_DIRECTION_LEFT)
    {
    if (HV) bit_set(Hall, 2); //Hall+=2;
    if (HW) bit_set(Hall, 1); //Hall+=4;
    }
  FIRCASIZ_DON(Hall);
  }

//-------------------------------

void MOTOR_SET_KOL_TOPLAMA_TOLERANS(word val)
  {
  MOTOR_TEKRAR_HAREKET_BASLAMA_TOLERANS = val;
  }

word MOTOR_GET_KOL_TOPLAMA_TOLERANS()
  {
  return MOTOR_TEKRAR_HAREKET_BASLAMA_TOLERANS;
  }

void MOTOR_SET_Z_POINT(word val)
  {
  MOTOR_Z_POINT_INDEX = val;
  }

word MOTOR_GET_Z_POINT()
  {
  return MOTOR_Z_POINT_INDEX;
  }

word MOTOR_GET_LAST_SUCESS_INDEX()
  {
  return MOTOR_LAST_SUCCESS_INDEX;
  }

word MOTOR_GET_MAS12_HAM()
  {
  return MAS12_NOW;
  }

word MOTOR_GET_MAS12_MAPPED()
  {
  return MAS12_NOW_MAPPED;
  }

void MOTOR_SET_MODE(byte mode)
  {
  MOTOR_MODE = mode;
  }