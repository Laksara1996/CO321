#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void){
   DDRB = DDRB|(0b00011110);

    while(1){
    PORTB = PORTB | (0b00011110); /* set pin 5 high to turn led on */
    _delay_ms(BLINK_DELAY_MS);

    PORTB = PORTB & ~(0b00011110); /* set pin 5 low to turn led off */
    _delay_ms(BLINK_DELAY_MS);
   }
}


 
 