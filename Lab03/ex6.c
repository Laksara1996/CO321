#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char counter=0;


int main(void){
    sei();	 // enable interrupt subsystem globally 
	TIMSK0 = 0x01;// enable Timer 1 overflow interrupt 
	TCNT0 = 5; /*load timer counter register*/
    TCCR0A = 0x00; /*set the Timer0 under normal mode with no prescaler*/
    TCCR0B =0x04;
    DDRB = DDRB|(0b00100000);

    while(1){
          PORTB = PORTB ^ (1<<5);
          counter=0;
          while(counter < 25){}
   }
}

ISR(TIMER0_OVF_vect){ // Timer1 overflow interrupt service routine
    counter++;
} 



 
 