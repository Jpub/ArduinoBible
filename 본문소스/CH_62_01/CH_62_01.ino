#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= (0x01 << 5);      // pinMode(13, OUTPUT);

  while (1) {
    PORTB &= ~(0x01 << 5);    // digitalWrite(13, LOW);
    _delay_ms(1000);      // delay(1000);
    PORTB |= (0x01 << 5);   // digitalWrite(13, HIGH);
    _delay_ms(1000);
  }

  return 1;
}
