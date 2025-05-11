#include "ATMEGA_64.h"
#include <xc.h>

#ifdef __AVR_ATmega64__

// <editor-fold defaultstate="collapsed" desc="PIN IO">

byte PIN_GET_PORT(byte Port, byte Pin)
{
    byte hex = (byte) (1 << Pin);
    byte data = 0;
    if (Port == 'A') data = PINA;
    else if (Port == 'B') data = PINB;
    else if (Port == 'BC') data = PINC;
    else if (Port == 'D') data = PIND;
    else if (Port == 'E') data = PINE;
    else if (Port == 'F') data = PINF;
    else if (Port == 'G') data = PING;
    if (data & hex) return 1;
    else return 0;
}

void PIN_SET_LAT(byte Port, byte Pin, byte HighOrLow)
{
    byte hex = (byte) (1 << Pin);
    if (HighOrLow == 'H') {
        if (Port == 'A') PORTA = PORTA | hex;
        else if (Port == 'B') PORTB = PORTB | hex;
        else if (Port == 'C') PORTC = PORTC | hex;
        else if (Port == 'D') PORTD = PORTD | hex;
        else if (Port == 'E') PORTE = PORTE | hex;
        else if (Port == 'F') PORTF = PORTF | hex;
        else if (Port == 'G') PORTG = PORTG | hex;
    } else if (HighOrLow == 'L') {
        if (Port == 'A') PORTA = PORTA & ~hex;
        else if (Port == 'B') PORTB = PORTB & ~hex;
        else if (Port == 'C') PORTC = PORTC & ~hex;
        else if (Port == 'D') PORTD = PORTD & ~hex;
        else if (Port == 'E') PORTE = PORTE & ~hex;
        else if (Port == 'F') PORTF = PORTF & ~hex;
        else if (Port == 'G') PORTG = PORTG & ~hex;
    }
}

void PIN_SET_TRIS(byte Port, byte Pin, byte InputOrOutput)
{
    byte hex = (byte) (1 << Pin);
    if (InputOrOutput == 'O') {
        if (Port == 'A') DDRA = DDRA | hex;
        else if (Port == 'B') DDRB = DDRB | hex;
        else if (Port == 'C') DDRC = DDRC | hex;
        else if (Port == 'D') DDRD = DDRD | hex;
        else if (Port == 'E') DDRE = DDRE | hex;
        else if (Port == 'F') DDRF = DDRF | hex;
        else if (Port == 'G') DDRG = DDRG | hex;
    } else if (InputOrOutput == 'I') {
        if (Port == 'A') DDRA = DDRA & ~hex;
        else if (Port == 'B') DDRB = DDRB & ~hex;
        else if (Port == 'C') DDRC = DDRC & ~hex;
        else if (Port == 'D') DDRD = DDRD & ~hex;
        else if (Port == 'E') DDRE = DDRE & ~hex;
        else if (Port == 'F') DDRF = DDRF & ~hex;
        else if (Port == 'G') DDRG = DDRG & ~hex;
    }
}

void PIN_SET_LAT_TOGGLE(byte Port, byte Pin)
{
    byte hex = (byte) (1 << Pin);
    if (Port == 'A') PORTA = PORTA ^ hex;
    else if (Port == 'B') PORTB = PORTB ^ hex;
    else if (Port == 'C') PORTC = PORTC ^ hex;
    else if (Port == 'D') PORTD = PORTD ^ hex;
    else if (Port == 'E') PORTE = PORTE ^ hex;
    else if (Port == 'F') PORTF = PORTF ^ hex;
    else if (Port == 'G') PORTG = PORTG ^ hex;
}

void PIN_SET_IO(byte AnalogOrDijital, byte InputOrOutput, byte Port, byte Pin, byte HighOrLow)
{
    PIN_SET_LAT(Port, Pin, HighOrLow);
    PIN_SET_TRIS(Port, Pin, InputOrOutput);
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER 1">
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

void TIMER_1_SET(byte startOrStop)
{
    if (startOrStop);
    else TCCR1B = 0;
}

void TIMER_1_INIT(byte ms)
{
    float calculater;
    word prescale = 1;
    byte counter = 0;
    while (1) {
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

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="TIMER 3">

word TIMER_3_TICKS;

void TIMER_3_INTERRUPT(byte openOrClose)
{
    if (openOrClose) ETIMSK |= (1 << TOIE3);
    else ETIMSK &= ~(1 << TOIE3);
}

void TIMER_3_INTERRUPT_FUNCT()
{
    TCNT3 = TIMER_3_TICKS;
}

void TIMER_3_SET(byte startOrStop)
{
    if (startOrStop);
    else TCCR3B = 0;
}

void TIMER_3_INIT(byte ms)
{
    float calculater;
    word prescale = 1;
    byte counter = 0;
    while (1) {
        counter++;
        calculater = (CRYSTAL_FREKANS / 1000) / prescale;
        calculater = 1 / calculater;
        calculater = ms / calculater;
        if (calculater < 0xFFFF) break;
        else prescale = prescale * 8;
        if (prescale == 512) prescale = 256;
        if (prescale == 2048) prescale = 1024;

    }
    TCCR3A = 0;
    TIMER_3_TICKS = 0xFFFF - calculater;
    TIMER_3_INTERRUPT_FUNCT(TIMER_3_TICKS);
    TCCR3B = counter;
    TIMER_3_INTERRUPT(1);
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="UART 0">

void UART_1_INTERRUPT(byte openOrClose)
{
    if (openOrClose) UCSR0B = UCSR0B | (1 << RXCIE0);
    else UCSR0B = UCSR0B & ~(1 << RXCIE0);
}

void UART_1_INIT(unsigned long baudrate)
{
    baudrate = baudrate / 2;
    UCSR0A |= (1 << U2X);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (0 << TXCIE0);
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    baudrate = (((CRYSTAL_FREKANS / (baudrate * 16UL))) - 1);
    UBRR0L = baudrate;
    UBRR0H = (baudrate >> 8);
}

void UART_1_BYTE(char data)
{
    while (!(UCSR0A & (1 << UDRE0))); /* Wait for empty transmit buffer*/
    UDR0 = data;
    while (!(UCSR0A & (1 << TXC0)));
    UCSR0A |= (1 << TXC0);
}

void UART_1_STRING(const char* text)
{
    unsigned char j = 0;
    while (text[j] != 0) /* Send string till null */ {
        UART_1_BYTE(text[j]);
        j++;
    }
}

void UART_1_DECIMAL(dword val)
{

    byte basamak[10] = {};
    signed char i = 0;
    do {
        basamak[ i ] = (val % 10) + 0x30;
        val /= 10;
        i++;
    } while (val != 0);
    i--;
    while (i >= 0) {
        UART_1_BYTE(basamak[ i ]);
        i--;
    }
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="UART 1">

void UART_2_INTERRUPT(byte openOrClose)
{
    if (openOrClose) UCSR1B = UCSR1B | (1 << RXCIE1);
    else UCSR1B = UCSR1B & ~(1 << RXCIE1);
}

void UART_2_INIT(unsigned long baudrate)
{
    baudrate = baudrate / 2;
    UCSR1A |= (1 << U2X);
    UCSR1B |= (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1) | (0 << TXCIE1);
    UCSR1C |= (1 << UCSZ00) | (1 << UCSZ01);
    baudrate = (((CRYSTAL_FREKANS / (baudrate * 16UL))) - 1);
    UBRR1L = baudrate;
    UBRR1H = (baudrate >> 8);

}

void UART_2_BYTE(char data)
{
    while (!(UCSR1A & (1 << UDRE1)));
    UDR1 = data;
    while (!(UCSR1A & (1 << TXC1)));
    UCSR1A |= (1 << TXC1);
}

void UART_2_STRING(const char* text)
{
    unsigned char j = 0;
    while (text[j] != 0) /* Send string till null */ {
        UART_2_BYTE(text[j]);
        j++;
    }
}

void UART_2_DECIMAL(dword val)
{
    byte basamak[10] = {};
    signed char i = 0;
    do {
        basamak[ i ] = (val % 10) + 0x30;
        val /= 10;
        i++;
    } while (val != 0);
    i--;
    while (i >= 0) {
        UART_2_BYTE(basamak[ i ]);
        i--;
    }
}
// </editor-fold> 
//// <editor-fold defaultstate="collapsed" desc="SYSTEM">

void INTERRUPT_ALL(byte x)
{
    if (x) sei();
    if (x == 0) cli();
}

//// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="ADC">

void ADC_INIT()
{
    ADCSRA = 0x87; /* Enable ADC, fr/128  */
    ADMUX = 0x40; /* Vref: Avcc, ADC channel: 0 */
}

word ADC_READ(byte channel)
{
    word Ain, AinLow;
    ADMUX = ADMUX | (channel & 0x0f);
    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADIF)) == 0);
    _delay_us(10);
    AinLow = (word) ADCL;
    Ain = (word) ADCH * 256;
    Ain = Ain + AinLow;
    return (Ain);
}

// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="I2C">
#define I2C_DELAY 35

void I2C_1_INIT(dword freq)
{
#define BITRATE(TWSR)	((CRYSTAL_FREKANS/freq)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
    TWBR = 6;
}

byte I2C_1_READ_ACK()
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    byte delay_counter = I2C_DELAY;
    while (!(TWCR & (1 << TWINT))) {
        if (delay_counter) delay_counter--;
        else break;
        _delay_us(1);
    }
    return TWDR;
}

byte I2C_1_READ_NACK()
{
    TWCR = (1 << TWEN) | (1 << TWINT);
    byte delay_counter = I2C_DELAY;
    while (!(TWCR & (1 << TWINT))) {
        if (delay_counter) delay_counter--;
        else break;
        _delay_us(1);
    }
    return TWDR;
}

byte I2C_1_WRITE(byte data)
{
    byte status;
    TWDR = data;
    TWCR = TWCR & ~(1 << TWINT);
    TWCR = (1 << TWEN) | (1 << TWINT);
    byte delay_counter = I2C_DELAY;
    while (!(TWCR & (1 << TWINT))) {
        if (delay_counter) delay_counter--;
        else break;
        _delay_us(1);
    }
    status = TWSR & 0xF8;
    if (status == 0x28) return 0;
    if (status == 0x30) return 1;
    else return 2;
}

void I2C_1_START()
{
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    byte delay_counter = I2C_DELAY;
    while (!(TWCR & (1 << TWINT))) {
        if (delay_counter) delay_counter--;
        else break;
        _delay_us(1);
    }
}

void I2C_1_STOP()
{
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
    byte delay_counter = I2C_DELAY;
    while (!(TWCR & (1 << TWINT))) {
        if (delay_counter) delay_counter--;
        else break;
        _delay_us(1);
    }
}

// </editor-fold> 
//// <editor-fold defaultstate="collapsed" desc="PWM ALL">
//// <editor-fold defaultstate="collapsed" desc="PWM 0">
//
//void PWM_0_INIT(word presecale, byte violent)
//  {
//  if (violent == SYSTEM_PWM_SLOW) TCCR0 = (0 << WGM01) | (1 << WGM00);
//  else if (violent == SYSTEM_PWM_FAST) TCCR0 = (1 << WGM01) | (1 << WGM00);
//  TCCR0 |= presecale;
//  }
//
//void PWM_0_START()
//  {
//  TCCR0 = TCCR0 | (1 << COM01);
//  }
//
//void PWM_0_STOP()
//  {
//  TCCR0 = TCCR0 & ~(1 << COM01);
//  }
//
//void PWM_0_DUTY(byte duty)
//  {
//  float data = 2.55 * duty;
//  OCR0 = data;
//  }
//
//// </editor-fold>
//
//// <editor-fold defaultstate="collapsed" desc="PWM 1">
//
//void PWM_1_INIT(byte presecale, byte violent)
//  {
//  TCCR1A = 0;
//  TCCR1B = 0;
//  TCCR1A |= (0 << WGM11) | (1 << WGM10); //8 BIT RES.
//  if (violent == SYSTEM_PWM_FAST) TCCR1B = (0 << WGM13) | (1 << WGM12);
//  else if (violent == SYSTEM_PWM_SLOW) TCCR1B = (0 << WGM13) | (0 << WGM12);
//  TCCR1B |= presecale;
//  }
//
//// <editor-fold defaultstate="collapsed" desc="PWM 3A">
//
//void PWM_1A_INIT()
//  {
//  SYSTEM_SET_IO_TRIS('B', 5, 'O');
//  }
//
//void PWM_1A_START()
//  {
//  TCCR1A |= (1 << COM1A1) | (0 << COM1A0);
//  }
//
//void PWM_1A_STOP()
//  {
//  TCCR1A &= ~((1 << COM1A1) | (0 << COM1A0));
//  }
//
//void PWM_1A_DUTY(byte duty)
//  {
//  float data = 2.55 * duty;
//  OCR1A = data;
//  }
//
//// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="PWM 3B">
//
//void PWM_1B_INIT()
//  {
//  SYSTEM_SET_IO_TRIS('B', 6, 'O');
//  }
//
//void PWM_1B_START()
//  {
//  TCCR1A |= (1 << COM1B1) | (0 << COM1B0);
//  }
//
//void PWM_1B_STOP()
//  {
//  TCCR1A &= ~((1 << COM1B1) | (0 << COM1B0));
//  }
//
//void PWM_1B_DUTY(byte duty)
//  {
//  float data = 2.55 * duty;
//  OCR1B = data;
//  }
//// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="PWM 3C">
//
//void PWM_1C_INIT()
//  {
//  SYSTEM_SET_IO_TRIS('B', 7, 'O');
//  }
//
//void PWM_1C_START()
//  {
//  TCCR1A |= (1 << COM1C1) | (0 << COM1C0);
//  }
//
//void PWM_1C_STOP()
//  {
//  TCCR1A &= ~((1 << COM1C1) | (0 << COM1C0));
//  }
//
//void PWM_1C_DUTY(byte duty)
//  {
//  float data = 2.55 * duty;
//  OCR1C = data;
//  }
//// </editor-fold>
//
//// </editor-fold> 

//// <editor-fold defaultstate="collapsed" desc="PWM 3">
//
//void PWM_3_INIT(byte presecale, byte violent)
//  {
//  TCCR3A = 0;
//  TCCR3B = 0;
//  //TCCR3A |= (0 << WGM31) | (1 << WGM30); //8 BIT RES.
//  TCCR3A |= (1 << WGM31) | (0 << WGM30); //9 BIT RES.
//  //TCCR3A |= (1 << WGM31) | (1 << WGM30); //10 BIT RES.
//  if (violent == SYSTEM_PWM_FAST) TCCR3B = (0 << WGM33) | (1 << WGM32);
//  else if (violent == SYSTEM_PWM_SLOW) TCCR3B = (0 << WGM33) | (0 << WGM32);
//  TCCR3B |= presecale;
//  }
//
//// <editor-fold defaultstate="collapsed" desc="PWM 3A">
//
//void PWM_3A_INIT()
//  {
//  SYSTEM_SET_IO_LAT('E', 3, 'L');
//  SYSTEM_SET_IO_TRIS('E', 3, 'O');
//  }
//
//void PWM_3A_START()
//  {
//  TCCR3A |= (1 << COM3A1) | (0 << COM3A0);
//  }
//
//void PWM_3A_STOP()
//  {
//  TCCR3A &= ~((1 << COM3A1) | (0 << COM3A0));
//  }
//
//void PWM_3A_DUTY(word duty)
//  {
//  OCR3A = duty;
//  }
//
//// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="PWM 3B">
//
//void PWM_3B_INIT()
//  {
//  SYSTEM_SET_IO_LAT('E', 4, 'L');
//  SYSTEM_SET_IO_TRIS('E', 4, 'O');
//  }
//
//void PWM_3B_START()
//  {
//  TCCR3A |= (1 << COM3B1) | (0 << COM3B0);
//  }
//
//void PWM_3B_STOP()
//  {
//  TCCR3A &= ~((1 << COM3B1) | (0 << COM3B0));
//  }
//
//void PWM_3B_DUTY(word duty)
//  {
//  OCR3B = duty;
//  }
//// </editor-fold>
//// <editor-fold defaultstate="collapsed" desc="PWM 3C">
//
//void PWM_3C_INIT()
//  {
//  SYSTEM_SET_IO_LAT('E', 5, 'L');
//  SYSTEM_SET_IO_TRIS('E', 5, 'O');
//  }
//
//void PWM_3C_START()
//  {
//  TCCR3A |= (1 << COM3C1) | (0 << COM3C0);
//  }
//
//void PWM_3C_STOP()
//  {
//  TCCR3A &= ~((1 << COM3C1) | (0 << COM3C0));
//  }
//
//void PWM_3C_DUTY(word duty)
//  {
//  OCR3C = (duty);
//  }
//// </editor-fold>
//
//// </editor-fold> 

//// </editor-fold> 
// <editor-fold defaultstate="collapsed" desc="EEPROM">

void EEPROM_B_WRITE(word address, byte data)
{
    while (EECR & (1 << EEWE)); // EEWE = EEPROM Write Enable
    EEAR = address;
    EEDR = data;
    EECR |= (1 << EEMWE);
    EECR |= (1 << EEWE);
    while (EECR & (1 << EEWE)); // EEWE = EEPROM Write Enable
}

byte EEPROM_B_READ(word address)
{
    while (EECR & (1 << EEWE)); // Yazma bitmediyse bekle
    EEAR = address;
    EECR |= (1 << EERE); // EEPROM Read Enable
    return EEDR;
}
// </editor-fold> 

void(*UART_1_INTERRUPT_FUNCT_POINTER)(byte);
void(*UART_2_INTERRUPT_FUNCT_POINTER)(byte);
void(*TIMER_1_INTERRUPT_FUNCT_POINTER)(void);
void(*TIMER_3_INTERRUPT_FUNCT_POINTER)(void);

void UART_1_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_1_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_1_INIT(baudrate);
    UART_1_INTERRUPT_FUNCT_POINTER = UART_1_INTERRUPT_FUNCT_POINTER_t;
}

void UART_2_INTERRUPT_FUNCT_CONNECT(unsigned long baudrate, void(*UART_2_INTERRUPT_FUNCT_POINTER_t)(byte))
{
    UART_2_INIT(baudrate);
    UART_2_INTERRUPT_FUNCT_POINTER = UART_2_INTERRUPT_FUNCT_POINTER_t;
}

void TIMER_1_INTERRUPT_CONNECT(word ms, void(*TIMER_1_INTERRUPT_FUNCT_POINTER_t)(void))
{
    TIMER_1_INIT(ms);
    TIMER_1_INTERRUPT_FUNCT_POINTER = TIMER_1_INTERRUPT_FUNCT_POINTER_t;
}

void TIMER_3_INTERRUPT_CONNECT(word ms, void(*TIMER_3_INTERRUPT_FUNCT_POINTER_t)(void))
{
    TIMER_3_INIT(ms);
    TIMER_3_INTERRUPT_FUNCT_POINTER = TIMER_3_INTERRUPT_FUNCT_POINTER_t;
}

ISR(TIMER1_OVF_vect)
{
    TIMER_1_INTERRUPT_FUNCT();
    TIMER_1_INTERRUPT_FUNCT_POINTER();
}

ISR(TIMER3_OVF_vect)
{
    TIMER_3_INTERRUPT_FUNCT();
    TIMER_3_INTERRUPT_FUNCT_POINTER();
}

ISR(USART0_RX_vect)
{
    UART_1_INTERRUPT_FUNCT_POINTER(UDR0);
}

ISR(USART1_RX_vect)
{
    UART_2_INTERRUPT_FUNCT_POINTER(UDR1);
}
#endif