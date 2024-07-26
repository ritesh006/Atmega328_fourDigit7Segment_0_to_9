#include <avr/io.h>
#include <util/delay.h>

// Define digit selection pins (using PORTD)
#define D1 PD2  // IO2
#define D2 PD3  // IO3
#define D3 PD4  // IO4
#define D4 PD5  // IO5

// Define segment control pins (using PORTB and PORTC)
#define a PB0  // IO8
#define b PB1  // IO9
#define c PB2  // IO10
#define d PC0  // AD0
#define e PC1  // AD1
#define f PC2  // AD2
#define g PC3  // AD3

void offAllDigits();
void displayDigit(uint8_t digit);
void displayNumber(uint8_t number);
void displayNumberOnDigit(uint8_t number, uint8_t digit);

void setup() {
  // Set digit selection pins as output (PORTD)
  DDRD |= (1 << D1) | (1 << D2) | (1 << D3) | (1 << D4);

  // Set segment control pins as output (PORTB and PORTC)
  DDRB |= (1 << a) | (1 << b) | (1 << c);
  DDRC |= (1 << d) | (1 << e) | (1 << f) | (1 << g);

  offAllDigits();  // Ensure all digits are off initially
}

void loop() {
  // Cycle through numbers 0 to 9 on all four digits
  for (uint8_t number = 0; number < 10; number++) {
    for (uint16_t i = 0; i < 100; i++) { // Adjust the value to keep the digit stable
      displayNumberOnDigit(number, D1);
      displayNumberOnDigit(number, D2);
      displayNumberOnDigit(number, D3);
      displayNumberOnDigit(number, D4);
    }
    _delay_ms(1000);  // Wait for 1 second before moving to the next number
  }
}

void offAllDigits() {
  PORTD |= (1 << D1) | (1 << D2) | (1 << D3) | (1 << D4);
}

void displayDigit(uint8_t digit) {
  // Turn off all digits first
  offAllDigits();
  
  // Select the digit to display the number
  PORTD &= ~(1 << digit);
}

void displayNumber(uint8_t number) {
  // Set the segments for the number
  switch (number) {
    case 0:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << b) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << e) | (1 << f);
      break;
    case 1:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b)) | (1 << a) | (1 << b);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << e) | (1 << f);
      break;
    case 2:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << b);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << e) | (1 << g);
      break;
    case 3:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << b) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << g);
      break;
    case 4:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << b) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << f) | (1 << g);
      break;
    case 5:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << f) | (1 << g);
      break;
    case 6:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << e) | (1 << f) | (1 << g);
      break;
    case 7:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << b) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << g);
      break;
    case 8:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << b) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << e) | (1 << f) | (1 << g);
      break;
    case 9:
      PORTB = (PORTB & ~(1 << a) & ~(1 << b) & ~(1 << c)) | (1 << a) | (1 << b) | (1 << c);
      PORTC = (PORTC & ~(1 << d) & ~(1 << e) & ~(1 << f) & ~(1 << g)) | (1 << d) | (1 << f) | (1 << g);
      break;
  }
}

void displayNumberOnDigit(uint8_t number, uint8_t digit) {
  displayDigit(digit);
  displayNumber(number);
  _delay_ms(5);  // Short delay for multiplexing
  offAllDigits();  // Turn off all digits before next update to avoid ghosting
}

int main(void) {
  setup();
  while (1) {
    loop();
  }
  return 0;
}
