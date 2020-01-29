#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char counter=0;


int main(void){
    sei();	 // enable interrupt subsystem globally 
	TIMSK1 = 0x01;// enable Timer 1 overflow interrupt 
	TCNT1 = 34286; /*load timer counter register*/
    TCCR1A = 0x00; /*set the Timer0 under normal mode with no prescaler*/
    TCCR1B =0x04;

    TIMSK0 = 0x01;
    TCNT0 = 5; /*load timer counter register*/
    TCCR0A = 0x00; /*set the Timer0 under normal mode with 1:8 prescaler*/
    TCCR0B =0x03;
    DDRB = DDRB|(0b00111110);

    while(1){
        PORTB = PORTB ^ (1<<4);
          counter=0;
          while(counter < 50){}
    } 
    
    
   
}

ISR(TIMER1_OVF_vect){ // Timer1 overflow interrupt service routine
	PORTB =PORTB ^ (1<<5);
} 

ISR(TIMER0_OVF_vect){ // Timer1 overflow interrupt service routine
	counter++;
} 



 
 