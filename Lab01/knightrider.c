#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 200

int main(void){
    DDRB = DDRB|(0b00011110);

    while(1){
    unsigned char i;
    for(i = 1;i<5;i++){

        PORTB = PORTB | (1<<i); /* set pin 5 high to turn led on */
        PORTB = PORTB & ~(1<<i-1); /* set pin 5 low to turn led off */
    _delay_ms(BLINK_DELAY_MS);
    }
   for(i = 4;i>1;i--){
        PORTB = PORTB & ~(1<<i); // set pin 5 low to turn led off 
        PORTB = PORTB | (1<<i-1); // set pin 5 high to turn led on  
    _delay_ms(BLINK_DELAY_MS);
    } 
    
    
   }
}


 
 