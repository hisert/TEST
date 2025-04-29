#include "ATMEGA_328.h"
#ifdef ATMEGA_328

// <editor-fold defaultstate="collapsed" desc="PIN IO">

byte PIN_GET_PORT(byte Port, byte Pin)
  {
  byte hex = (byte) (1 << Pin);
  byte data = 0;
  if (Port == 'B') data = PINB;
  else if (Port == 'C') data = PINC;
  else if (Port == 'D') data = PIND;
  if (data & hex) return 1;
  else return 0;
  }

void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow)
  {
  byte hex = (byte) (1 << Pin);
  if (HighOrLow == 'H')
    {
    if (Port == 'B') PORTB = PORTB | hex;
    else if (Port == 'C') PORTC = PORTC | hex;
    else if (Port == 'D') PORTD = PORTD | hex;
    }
  else if (HighOrLow == 'L')
    {
    if (Port == 'B') PORTB = PORTB & ~hex;
    else if (Port == 'C') PORTC = PORTC & ~hex;
    else if (Port == 'D') PORTD = PORTD & ~hex;
    }
  }

void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput)
  {
  byte hex;
  hex = 1;
  for (byte i = 0; i < Pin; i++) hex *= 2;
  if (InputOrOutput == 'O')
    {
    if (Port == 'B') DDRB = DDRB | hex;
    else if (Port == 'C') DDRC = DDRC | hex;
    else if (Port == 'D') DDRD = DDRD | hex;
    }
  else if (InputOrOutput == 'I')
    {
    if (Port == 'B') DDRB = DDRB & ~hex;
    else if (Port == 'C') DDRC = DDRC & ~hex;
    else if (Port == 'D') DDRD = DDRD & ~hex;
    }
  }

void PIN_SET_LAT_TOGGLE(byte Port, byte Pin)
  {
  byte hex = (byte) (1 << Pin);
  if (Port == 'B') PORTB = PORTB ^ hex;
  else if (Port == 'C') PORTC = PORTC ^ hex;
  else if (Port == 'D') PORTD = PORTD ^ hex;
  }

void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow)
  {
  PIN_SET_LAT(Port, Pin, HighOrLow);
  PIN_SET_TRIS(Port, Pin, InputOrOutput);
  }

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER 0    ">
word TIMER_0_TICKS;

void TIMER_0_INTERRUPT_FUNCT()
  {
  TCNT0 = TIMER_0_TICKS;
  }

void TIMER_0_INTERRUPT(byte openOrClose)
  {
  if (openOrClose) TIMSK0 |= (1 << TOIE0);
  else TIMSK0 &= ~(1 << TOIE0);
  }

void TIMER_0_INIT(byte ms)
  {
  float calculater;
  word prescale = 1;
  byte counter = 0;
  while (1)
    {
    counter++;
    calculater = (CRYSTAL_FREKANS / 1000) / prescale;
    calculater = 1 / calculater;
    calculater = ms / calculater;
    if (calculater < 0xFF) break;
    else prescale = prescale * 8;
    if (prescale == 512) prescale = 256;
    if (prescale == 2048) prescale = 1024;

    }
  TCCR0A = 0;
  TIMER_0_TICKS = 0xFF - calculater;
  TIMER_0_INTERRUPT_FUNCT();
  TCCR0B = counter;
  TIMER_0_INTERRUPT(1);
  }

void TIMER_0_SET(byte startOrStop)
  {
  if (startOrStop);
  else TCCR0B = 0;
  }
// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="TIMER 1    ">
word TIMER_1_TICKS;

void TIMER_1_INTERRUPT_FUNCT()
  {
  TCNT1 = TIMER_1_TICKS;
  }

void TIMER_1_INTERRUPT(byte openOrClose)
  {
  if (openOrClose) TIMSK1 |= (1 << TOIE1);
  else TIMSK1 &= ~(1 << TOIE1);
  }

void TIMER_1_INIT(byte ms)
  {
  float calculater;
  word prescale = 1;
  byte counter = 0;
  while (1)
    {
    counter++;
    calculater = (CRYSTAL_FREKANS / 1000) / prescale;
    calculater = 1 / calculater;
    calculater = ms / calculater;
    if (calculater < 0xFFFF) break;
    else prescale = prescale * 8;
    if (prescale == 512) prescale = 256;
    if (prescale == 2048) prescale = 1024;

    }
  TCCR1A = 0;
  TIMER_1_TICKS = 0xFFFF - calculater;
  TIMER_1_INTERRUPT_FUNCT();
  TCCR1B = counter;
  TIMER_1_INTERRUPT(1);
  }

void TIMER_1_SET(byte startOrStop)
  {
  if (startOrStop);
  else TCCR1B = 0;
  }
// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="TIMER 2    ">
word TIMER_2_TICKS;

void TIMER_2_INTERRUPT(byte openOrClose)
  {
  if (openOrClose) TIMSK2 |= (1 << TOIE2);
  else TIMSK2 &= ~(1 << TOIE2);
  }

void TIMER_2_INTERRUPT_FUNCT()
  {
  TCNT2 = TIMER_2_TICKS;
  }

void TIMER_2_INIT(byte ms)
  {
  float calculater;
  word prescale = 1;
  byte counter = 0;
  while (1)
    {
    counter++;
    calculater = (CRYSTAL_FREKANS / 1000) / prescale;
    calculater = 1 / calculater;
    calculater = ms / calculater;
    if (calculater < 0xFF) break;
    else prescale = prescale * 8;
    if (prescale == 512) prescale = 256;
    if (prescale == 2048) prescale = 1024;

    }
  TCCR2A = 0;
  TIMER_2_TICKS = 0xFF - calculater;
  TIMER_2_INTERRUPT_FUNCT();
  TCCR2B = counter;
  TIMER_2_INTERRUPT(1);
  }

void TIMER_2_SET(byte startOrStop)
  {
  if (startOrStop);
  else TCCR2B = 0;
  }
// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="UART 0     ">

void UART_0_INIT(unsigned long baudrate)
  {
  float calculater;
  byte temp;
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
  UCSR0C |= ((1 << UCSZ00) | 1 << UCSZ01);
  calculater = (((CRYSTAL_FREKANS / (baudrate * (16)))) - 1);
  temp = (word) (calculater) & 0xFF;
  UBRR0L = temp;
  temp = calculater;
  temp = (word) (temp >> 8) & 0xFF;
  UBRR0H = temp;
  }

void UART_0_BYTE(char data)
  {
  while (!(UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer*/
  UDR0 = data;
  }

void UART_0_STRING(const char* text)
  {
  unsigned char j = 0;
  while (text[j] != 0) /* Send string till null */
    {
    UART_0_BYTE(text[j]);
    j++;
    }
  }

void UART_0_DECIMAL(dword val)
  {

  byte basamak[10] = {};
  signed char i = 0;
  do
    {
    basamak[ i ] = (val % 10) + 0x30;
    val /= 10;
    i++;
    }
  while (val != 0);
  i--;
  while (i >= 0)
    {
    UART_0_BYTE(basamak[ i ]);
    i--;
    }
  }

// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="ADC        ">

void ADC_INIT()
  {
  ADCSRA = 0x87; /* Enable ADC, fr/128  */
  }

word ADC_READ(byte channel)
  {
  word Ain, AinLow;
  ADMUX = 0x80;
  ADMUX = ADMUX + channel;
  ADCSRA |= (1 << ADSC);
  while ((ADCSRA & (1 << ADIF)) == 0);
  AinLow = (word) ADCL;
  Ain = (word) ADCH * 256;
  Ain = Ain + AinLow;
  return (Ain);
  }

// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="I2C        ">

#define I2C_1_DELAY 35

void I2C_1_INIT()
  {
  PORTC = PORTC | 16;
  PORTC = PORTC | 32;
  DDRC = DDRC & ~16;
  DDRC = DDRC & ~32;
#define BITRATE(TWSR)	((CRYSTAL_FREKANS/400000)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
  TWBR = BITRATE(TWSR = 0x00);
  }

void I2C_1_START()
  {
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  byte delay_counter = I2C_1_DELAY;
  while (!(TWCR & (1 << TWINT)))
    {
    if (delay_counter) delay_counter--;
    else break;
    _delay_us(1);
    }
  }

byte I2C_1_WRITE(byte data)
  {
  byte status;
  TWDR = data;
  TWCR = TWCR & ~(1 << TWINT);
  TWCR = (1 << TWEN) | (1 << TWINT);
  byte delay_counter = I2C_1_DELAY;
  while (!(TWCR & (1 << TWINT)))
    {
    if (delay_counter) delay_counter--;
    else break;
    _delay_us(1);
    }
  status = TWSR & 0xF8;
  if (status == 0x28) return 0;
  if (status == 0x30) return 1;
  else return 2;
  }

byte I2C_1_READ_ACK()
  {
  TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
  byte delay_counter = I2C_1_DELAY;
  while (!(TWCR & (1 << TWINT)))
    {
    if (delay_counter) delay_counter--;
    else break;
    _delay_us(1);
    }
  return TWDR;
  }

byte I2C_1_READ_NACK()
  {
  TWCR = (1 << TWEN) | (1 << TWINT);
  byte delay_counter = I2C_1_DELAY;
  while (!(TWCR & (1 << TWINT)))
    {
    if (delay_counter) delay_counter--;
    else break;
    _delay_us(1);
    }
  return TWDR;
  }

void I2C_1_STOP()
  {
  TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
  byte delay_counter = I2C_1_DELAY;
  while (!(TWCR & (1 << TWINT)))
    {
    if (delay_counter) delay_counter--;
    else break;
    _delay_us(1);
    }
  }

// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="PWM ALL">
//// <editor-fold defaultstate="collapsed" desc="PWM 0      ">
byte PWM_0_MODE = 0;
byte PWM_0_RESULATION = 0;

void PWM_0_INIT(byte presecale, byte mode, byte resulation)
  {
  TCCR0A = 0;
  TCCR0B = 0;
  if (resulation == 8) TCCR0A |= (0 << WGM01) | (1 << WGM00); //8 BIT RES.
  if (resulation == 9) TCCR0A |= (1 << WGM01) | (0 << WGM00); //9 BIT RES.
  if (resulation == 10) TCCR0A |= (1 << WGM01) | (1 << WGM00); //10 BIT RES.
  if (mode == SYSTEM_PWM_DUTY_SLOW) TCCR0B = (0 << WGM01) | (1 << WGM00);
  else if (mode == SYSTEM_PWM_DUTY_FAST) TCCR0B = (1 << WGM01) | (1 << WGM00); //FAST
  else if (mode == SYSTEM_PWM_FREQ) TCCR0B = (1 << WGM01) | (0 << WGM00);
  TCCR0B |= presecale;
  PWM_0_MODE = mode;
  PWM_0_RESULATION = resulation;
  }

// <editor-fold defaultstate="collapsed" desc="PWM 0A">

void PWM_0A_INIT()
  {
  SYSTEM_INIT_IO('D', 6, 'O', 'L');
  }

void PWM_0A_START()
  {
  if ((PWM_0_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_0_MODE == SYSTEM_PWM_DUTY_SLOW)) TCCR0A = TCCR0A | (1 << COM0A1) | (0 << COM0A0); //CLEAR COMPARE
  //if ((PWM_0_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_0_MODE == SYSTEM_PWM_DUTY_SLOW))   TCCR0A = TCCR0A | (1 << COM0A1) | (1 << COM0A0); //SET COMPARE

  }

void PWM_0A_STOP()
  {
  TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
  }

void PWM_0A_DUTY(word duty)
  {
  word carp = 0;
  if (PWM_0_RESULATION == 8) carp = 1;
  else if (PWM_0_RESULATION == 9) carp = 2;
  else if (PWM_0_RESULATION == 10) carp = 4;
  float data = 2.55 * duty * carp;
  OCR0A = data;
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 0B">

void PWM_0B_INIT()
  {
  SYSTEM_INIT_IO('D', 5, 'O', 'L');
  }

void PWM_0B_START()
  {
  if ((PWM_0_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_0_MODE == SYSTEM_PWM_DUTY_SLOW)) TCCR0A = TCCR0A | (1 << COM0B1) | (0 << COM0B0); //CLEAR COMPARE
  //if ((PWM_0_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_0_MODE == SYSTEM_PWM_DUTY_SLOW))   TCCR0A = TCCR0A | (1 << COM0B1) | (1 << COM0B0); //SET COMPARE

  }

void PWM_0B_STOP()
  {
  TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
  }

void PWM_0B_DUTY(word duty)
  {
  word carp = 0;
  if (PWM_0_RESULATION == 8) carp = 1;
  else if (PWM_0_RESULATION == 9) carp = 2;
  else if (PWM_0_RESULATION == 10) carp = 4;
  float data = 2.55 * duty * carp;
  OCR0B = data;
  }

// </editor-fold>
//// </editor-fold> -OK
//// <editor-fold defaultstate="collapsed" desc="PWM 1      ">
byte PWM_1_MODE = 0;
byte PWM_1_RESULATION = 0;

void PWM_1_INIT(byte presecale, byte mode, byte resulation)
  {
  TCCR1A = 0;
  TCCR1B = 0;
  if (resulation == 8) TCCR1A |= (0 << WGM11) | (1 << WGM10); //8 BIT RES.
  if (resulation == 9) TCCR1A |= (1 << WGM11) | (0 << WGM10); //9 BIT RES.
  if (resulation == 10) TCCR1A |= (1 << WGM11) | (1 << WGM10); //10 BIT RES.
  if (mode == SYSTEM_PWM_DUTY_SLOW) TCCR1B = (0 << WGM11) | (1 << WGM10);
  else if (mode == SYSTEM_PWM_DUTY_FAST) TCCR1B = (1 << WGM11) | (1 << WGM10); //FAST
  else if (mode == SYSTEM_PWM_FREQ) TCCR1B = (1 << WGM11) | (0 << WGM10);
  TCCR1B |= presecale;
  PWM_1_MODE = mode;
  PWM_1_RESULATION = resulation;
  }

// <editor-fold defaultstate="collapsed" desc="PWM 1A">

void PWM_1A_INIT()
  {
  SYSTEM_INIT_IO('B', 1, 'O', 'L');
  }

void PWM_1A_START()
  {
  if ((PWM_1_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_1_MODE == SYSTEM_PWM_DUTY_SLOW)) TCCR1A = TCCR1A | (1 << COM1A1) | (0 << COM1A0); //CLEAR COMPARE
  //if ((PWM_1_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_1_MODE == SYSTEM_PWM_DUTY_SLOW))   TCCR1A = TCCR1A | (1 << COM1A1) | (1 << COM1A0); //SET COMPARE

  }

void PWM_1A_STOP()
  {
  TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
  }

void PWM_1A_DUTY(word duty)
  {
  word carp = 0;
  if (PWM_1_RESULATION == 8) carp = 1;
  else if (PWM_1_RESULATION == 9) carp = 2;
  else if (PWM_1_RESULATION == 10) carp = 4;
  float data = 2.55 * duty * carp;
  OCR1A = data;
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 1B">

void PWM_1B_INIT()
  {
  SYSTEM_INIT_IO('B', 2, 'O', 'L');
  }

void PWM_1B_START()
  {
  if ((PWM_1_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_1_MODE == SYSTEM_PWM_DUTY_SLOW)) TCCR1A = TCCR1A | (1 << COM1B1) | (0 << COM1B0); //CLEAR COMPARE
  //if ((PWM_1_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_1_MODE == SYSTEM_PWM_DUTY_SLOW))   TCCR1A = TCCR1A | (1 << COM1B1) | (1 << COM1B0); //SET COMPARE

  }

void PWM_1B_STOP()
  {
  TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
  }

void PWM_1B_DUTY(word duty)
  {
  word carp = 0;
  if (PWM_1_RESULATION == 8) carp = 1;
  else if (PWM_1_RESULATION == 9) carp = 2;
  else if (PWM_1_RESULATION == 10) carp = 4;
  float data = 2.55 * duty * carp;
  OCR1B = data;
  }

// </editor-fold>
//// </editor-fold> -OK
//// <editor-fold defaultstate="collapsed" desc="PWM 2      ">
byte PWM_2_MODE = 0;
byte PWM_2_RESULATION = 0;

void PWM_2_INIT(byte presecale, byte mode, byte resulation)
  {
  TCCR2A = 0;
  TCCR2B = 0;
  if (resulation == 8) TCCR2A |= (0 << WGM21) | (1 << WGM20); //8 BIT RES.
  else if (resulation == 9) TCCR2A |= (1 << WGM21) | (0 << WGM20); //9 BIT RES.
  else if (resulation == 10) TCCR2A |= (1 << WGM21) | (1 << WGM20); //10 BIT RES.
  if (mode == SYSTEM_PWM_DUTY_SLOW) TCCR2B = (0 << WGM21) | (1 << WGM20);
  else if (mode == SYSTEM_PWM_DUTY_FAST) TCCR2B = (1 << WGM21) | (1 << WGM20); //FAST
  else if (mode == SYSTEM_PWM_FREQ) TCCR2B = (1 << WGM21) | (0 << WGM20);
  TCCR2B |= presecale;
  PWM_2_MODE = mode;
  PWM_2_RESULATION = resulation;
  }

// <editor-fold defaultstate="collapsed" desc="PWM 2A">

void PWM_2A_INIT()
  {
  PORTB = PORTB & ~8;
  DDRB = DDRB | 8;
  OCR2A = 0;
  }

void PWM_2A_START()
  {
  if ((PWM_2_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_2_MODE == SYSTEM_PWM_DUTY_SLOW)) TCCR2A = TCCR2A | (1 << COM2A1) | (0 << COM2A0); //CLEAR COMPARE
  //if ((PWM_2_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_2_MODE == SYSTEM_PWM_DUTY_SLOW))   TCCR2A = TCCR2A | (1 << COM2A1) | (1 << COM2A0); //SET COMPARE

  }

void PWM_2A_STOP()
  {
  TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0));
  PORTB = PORTB & ~8;
  }

void PWM_2A_DUTY(word duty)
  {
  word carp = 0;
  if (PWM_2_RESULATION == 8) carp = 1;
  else if (PWM_2_RESULATION == 9) carp = 2;
  else if (PWM_2_RESULATION == 10) carp = 3;
  float data = 2.55 * duty * carp;
  OCR2A = data;
  }

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="PWM 2B">

void PWM_2B_INIT()
  {
  PORTD = PORTD & ~8;
  DDRD = DDRD | 8;
  OCR2B = 0;
  }

void PWM_2B_START()
  {
  if ((PWM_2_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_2_MODE == SYSTEM_PWM_DUTY_SLOW)) TCCR2A = TCCR2A | (1 << COM2B1) | (0 << COM2B0); //CLEAR COMPARE
  //if ((PWM_2_MODE == SYSTEM_PWM_DUTY_FAST) || (PWM_2_MODE == SYSTEM_PWM_DUTY_SLOW))   TCCR2A = TCCR2A | (1 << COM2B1) | (1 << COM2B0); //SET COMPARE

  }

void PWM_2B_STOP()
  {
  TCCR2A &= ~((1 << COM2B1) | (1 << COM2B0));
  PORTD = PORTD & ~8;
  }

void PWM_2B_DUTY(word duty)
  {
  word carp = 0;
  if (PWM_2_RESULATION == 8) carp = 1;
  else if (PWM_2_RESULATION == 9) carp = 2;
  else if (PWM_2_RESULATION == 10) carp = 3;
  float data = 2.55 * duty * carp;
  OCR2B = data;
  }

// </editor-fold>
//// </editor-fold> -OK
// </editor-fold> 
//// <editor-fold defaultstate="collapsed" desc="SYSTEM">

void INTERRUPT_ALL(byte x)
  {
  if (x) sei();
  if (x == 0) cli();
  }

//// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="EEPROM">

void EEPROM_B_WRITE(word address, byte data)
  {
  while (EECR & (1 << EEPE)); // Önceki yazma i?lemi bitene kadar bekle

  EEAR = address; // Adresi ayarla
  EEDR = data; // Yaz?lacak veriyi yükle

  EECR |= (1 << EEMPE); // Yazma etkinle?tirme sinyali
  EECR |= (1 << EEPE); // Yazma i?lemini ba?lat
  while (EECR & (1 << EEPE)); // Önceki yazma i?lemi bitene kadar bekle

  }

// EEPROM'dan 1 byte oku

byte EEPROM_B_READ(word address)
  {
  while (EECR & (1 << EEPE)); // Yazma i?lemi varsa bekle

  EEAR = address; // Adresi ayarla
  EECR |= (1 << EERE); // Okuma i?lemini ba?lat

  return EEDR; // Okunan veriyi döndür
  }
// </editor-fold> 
#endif