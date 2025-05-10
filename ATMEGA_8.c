#include "ATMEGA_8.h"
#ifdef __AVR_ATmega8__

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
    if (Port == 'B') PORTB |= hex;
    else if (Port == 'C') PORTC |= hex;
    else if (Port == 'D') PORTD |= hex;
    }
  else if (HighOrLow == 'L')
    {
    if (Port == 'B') PORTB &= ~hex;
    else if (Port == 'C') PORTC &= ~hex;
    else if (Port == 'D') PORTD &= ~hex;
    }
  }

void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput)
  {
  byte hex = (byte) (1 << Pin);
  if (InputOrOutput == 'O')
    {
    if (Port == 'B') DDRB |= hex;
    else if (Port == 'C') DDRC |= hex;
    else if (Port == 'D') DDRD |= hex;
    }
  else if (InputOrOutput == 'I')
    {
    if (Port == 'B') DDRB &= ~hex;
    else if (Port == 'C') DDRC &= ~hex;
    else if (Port == 'D') DDRD &= ~hex;
    }
  }

void PIN_SET_LAT_TOGGLE(byte Port, byte Pin)
  {
  byte hex = (byte) (1 << Pin);
  if (Port == 'B') PORTB ^= hex;
  else if (Port == 'C') PORTC ^= hex;
  else if (Port == 'D') PORTD ^= hex;
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
  if (openOrClose) TIMSK |= (1 << TOIE0);
  else TIMSK &= ~(1 << TOIE0);
  }

void TIMER_0_INIT(byte ms)
  {
  float calculater;
  word prescale = 1;
  byte cs_bits = 0;
  while (1)
    {
    cs_bits++;
    calculater = (CRYSTAL_FREKANS / 1000.0) / prescale;
    calculater = 1.0 / calculater;
    calculater = ms / calculater;
    if (calculater < 256) break;
    else prescale *= 8;
    if (prescale == 512) prescale = 256;
    if (prescale == 2048) prescale = 1024;
    if (cs_bits > 5) break; // Tüm prescaler seçeneklerini denedik
    }
  TCCR0 = cs_bits; // Prescaler ayarland?
  TIMER_0_TICKS = 255 - (byte) calculater;
  TIMER_0_INTERRUPT_FUNCT();
  TIMER_0_INTERRUPT(1);
  }

void TIMER_0_SET(byte startOrStop)
  {
  if (startOrStop) TCCR0 |= (TCCR0 & 0x07); // Önceki prescaler ayar?n? koru
  else TCCR0 = 0;
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
  if (openOrClose) TIMSK |= (1 << TOIE1);
  else TIMSK &= ~(1 << TOIE1);
  }

void TIMER_1_INIT(byte ms)
  {
  float calculater;
  word prescale = 1;
  byte cs_bits = 0;
  while (1)
    {
    cs_bits++;
    calculater = (CRYSTAL_FREKANS / 1000.0) / prescale;
    calculater = 1.0 / calculater;
    calculater = ms / calculater;
    if (calculater < 65536) break;
    else prescale *= 8;
    if (prescale == 512) prescale = 256;
    if (prescale == 2048) prescale = 1024;
    if (cs_bits > 5) break; // Tüm prescaler seçeneklerini denedik
    }
  TCCR1B = (TCCR1B & 0xF8) | cs_bits; // Prescaler ayarland?, di?er bitler korunuyor
  TIMER_1_TICKS = 65535 - (word) calculater;
  TIMER_1_INTERRUPT_FUNCT();
  TIMER_1_INTERRUPT(1);
  }

void TIMER_1_SET(byte startOrStop)
  {
  if (startOrStop) TCCR1B |= (TCCR1B & 0x07); // Önceki prescaler ayar?n? koru
  else TCCR1B &= 0xF8;
  }
// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="UART 0     ">

void UART_1_INIT(unsigned long baudrate)
  {
  float calculater;
  word ubrr_val;
  UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (0 << TXCIE);
  UCSRC |= ((1 << UCSZ1) | (1 << UCSZ0)); // 8-bit data
  ubrr_val = (word) (CRYSTAL_FREKANS / (16.0 * baudrate) - 0.5);
  UBRRH = (ubrr_val >> 8) & 0xFF;
  UBRRL = ubrr_val & 0xFF;
  }

void UART_1_BYTE(char data)
  {
  while (!(UCSRA & (1 << UDRE))); /* Wait for empty transmit buffer*/
  UDR = data;
  while (!(UCSRA & (1 << TXC))); // Tüm veri gönderildi mi?
  UCSRA |= (1 << TXC); // TXC bayra??n? temizle
  }

void UART_1_STRING(const char* text)
  {
  byte j = 0;
  while (text[j] != 0) /* Send string till null */
    {
    UART_1_BYTE(text[j]);
    j++;
    }
  }

void UART_1_DECIMAL(dword val)
  {
  byte basamak[10] = {};
  signed char i = 0;
  do
    {
    basamak[ i ] = (val % 10) + '0';
    val /= 10;
    i++;
    }
  while (val != 0);
  i--;
  while (i >= 0)
    {
    UART_1_BYTE(basamak[ i ]);
    i--;
    }
  }

// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="ADC        ">

void ADC_INIT()
  {
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler /128
  }

word ADC_READ(byte channel)
  {
  ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // Select ADC channel, keep reference
  ADCSRA |= (1 << ADSC); // Start conversion
  while (!(ADCSRA & (1 << ADIF))); // Wait for conversion to complete
  ADCSRA |= (1 << ADIF); // Clear ADIF flag
  return ADCW; // Return 10-bit ADC value
  }

// </editor-fold> -OK
// <editor-fold defaultstate="collapsed" desc="I2C        ">

#define I2C_1_DELAY 35

void I2C_1_INIT()
  {
  // Enable pull-ups on SDA (PC4) and SCL (PC5)
  PORTC |= (1 << PC4) | (1 << PC5);
  // Set SDA and SCL as input
  DDRC &= ~((1 << PC4) | (1 << PC5));
  // Set SCL frequency to 400kHz (example, adjust based on your clock)
  TWBR = (byte) ((CRYSTAL_FREKANS / 400000UL) - 16) / 2;
  }

void I2C_1_START()
  {
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  while (!(TWCR & (1 << TWINT)));
  if ((TWSR & 0xF8) != 0x08 && (TWSR & 0xF8) != 0x10)
    {
    // START or Repeated START failed
    return;
    }
  }

byte I2C_1_WRITE(byte data)
  {
  TWDR = data;
  TWCR = (1 << TWEN) | (1 << TWINT);
  while (!(TWCR & (1 << TWINT)));
  return (TWSR & 0xF8);
  }

byte I2C_1_READ_ACK()
  {
  TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
  while (!(TWCR & (1 << TWINT)));
  return TWDR;
  }

byte I2C_1_READ_NACK()
  {
  TWCR = (1 << TWEN) | (1 << TWINT);
  while (!(TWCR & (1 << TWINT)));
  return TWDR;
  }

void I2C_1_STOP()
  {
  TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
  while (!(TWCR & (1 << TWINT)));
  }

// </editor-fold> -OK
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
  while (EECR & (1 << EEWE)); // Önceki yazma i?lemi bitene kadar bekle

  EEARH = (byte) ((address >> 8) & 0x01);
  EEARL = (byte) (address & 0xFF);
  EEDR = data; // Yaz?lacak veriyi yükle

  EECR |= (1 << EEMWE); // Yazma etkinle?tirme sinyali
  EECR |= (1 << EEWE); // Yazma i?lemini ba?lat
  while (EECR & (1 << EEWE)); // Yazma i?leminin tamamlanmas?n? bekle
  _delay_ms(5);
  }

// EEPROM'dan 1 byte oku

byte EEPROM_B_READ(word address)
  {
  while (EECR & (1 << EEWE)); // Yazma i?lemi varsa bekle

  EEARH = (byte) ((address >> 8) & 0x01);
  EEARL = (byte) (address & 0xFF);
  EECR |= (1 << EERE); // Okuma i?lemini ba?lat

  return EEDR; // Okunan veriyi döndür
  }

void(*UART_1_INTERRUPT_FUNCT_POINTER)(byte);
void(*TIMER_0_INTERRUPT_FUNCT_POINTER)(void);
void(*TIMER_1_INTERRUPT_FUNCT_POINTER)(void);

void UART_1_INTERRUPT_FUNCT_CONNECT(void(*UART_1_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_1_INTERRUPT_FUNCT_POINTER = UART_1_INTERRUPT_FUNCT_POINTER_t;
}

void TIMER_0_INTERRUPT_CONNECT(void(*TIMER_0_INTERRUPT_FUNCT_POINTER_t)(void))
{
    TIMER_0_INTERRUPT_FUNCT_POINTER = TIMER_0_INTERRUPT_FUNCT_POINTER_t;
}

void TIMER_1_INTERRUPT_CONNECT(void(*TIMER_1_INTERRUPT_FUNCT_POINTER_t)(void))
{
    TIMER_1_INTERRUPT_FUNCT_POINTER = TIMER_1_INTERRUPT_FUNCT_POINTER_t;
}

ISR(TIMER0_OVF_vect)
{
    TIMER_0_INTERRUPT_FUNCT();
    TIMER_0_INTERRUPT_FUNCT_POINTER();
}

ISR(TIMER1_OVF_vect)
{
    TIMER_1_INTERRUPT_FUNCT();
    TIMER_1_INTERRUPT_FUNCT_POINTER();
}

ISR(USART_RXC_vect)
{
    UART_1_INTERRUPT_FUNCT_POINTER(UDR);
}

#endif