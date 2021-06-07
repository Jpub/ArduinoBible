#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= 0x03F;      // pinMode (6개 핀)

  while (1) {
    PORTB &= ~0x3F;       // digitalWrite (6개 핀)
    _delay_ms(1000);      // delay
    PORTB |= 0x3F;      // digitalWrite (6개 핀)
    _delay_ms(1000);
  }

  return 1;
}
