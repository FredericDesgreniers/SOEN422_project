/*
MIT License

Copyright (c) 2017 Frederic Desgreniers, Christopher McArthur

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "HX711.h"
#define BAUD 9600
#include <util/setbaud.h>
#include <avr/io.h>

void Serial_init();
void Serial_println(const char* s);

int main()
{
   HX711 scale(PD6, PD7);
   scale.set_scale(-6500);
   scale.tare();

   Serial_init();

   for (;;)
   {
      float retval = scale.get_units();
      char buffer[16];

      dtostrf(retval, -14, 4, buffer); // AVR float to char* conversion

      Serial_println(buffer);
   }
}

// UART FUNCTIONS -------------------------------

void Serial_init()
{
   UBRR0H = UBRRH_VALUE;
   UBRR0L = UBRRL_VALUE;

#if USE_2X
   UCSR0A |= _BV(U2X0);
#else
   UCSR0A &= ~(_BV(U2X0));
#endif

   UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
   UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

void Serial_write(char c)
{
   loop_until_bit_is_set(UCSR0A, UDRE0);
   UDR0 = c;
}

void Serial_println(const char* s)
{
   while (*s)
   {
      if(*s == ' ') break; // stop once a whitespace is hit
      Serial_write(*s);
      s++;
   }
   Serial_write('\n');
}
