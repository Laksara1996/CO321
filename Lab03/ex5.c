#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void delay_timer0(){
    TCNT0 = 0; /*load timer counter register*/
    TCCR0A = 0x00; /*set the Timer0 under normal mode with 1:8 prescaler*/
    TCCR0B =0x05;
    while((TIFR0 & 0x01)==0); /*wait till timer overflow bit (T0V0) is set*/
    TCCR0A =0x00;
    TCCR0B=0x00;
    TIFR0 = 0x01;
}

int main(void){
    sei();	 // enable interrupt subsystem globally 
	TIMSK1 = 0x01;// enable Timer 1 overflow interrupt 
	TCNT1 = 3036; /*load timer counter register*/
    TCCR1A = 0x00; /*set the Timer0 under normal mode with no prescaler*/
    TCCR1B =0x04;
    DDRB = DDRB|(0b00111110);

    while(1){
    unsigned char i;
    unsigned char j;
    for(i = 1;i<5;i++){

        PORTB = PORTB | (1<<i); /* set pin 5 high to turn led on */
        PORTB = PORTB & ~(1<<i-1); /* set pin 5 low to turn led off */
        for(j = 0;j<50;j++){
        delay_timer0();
        }
    }
   for(i = 4;i>1;i--){
        PORTB = PORTB & ~(1<<i); // set pin 5 low to turn led off 
        PORTB = PORTB | (1<<i-1); // set pin 5 high to turn led on  
        for(j = 0;j<50;j++){
        delay_timer0();
        }
    } 
    
    
   }
}

ISR(TIMER1_OVF_vect){ // Timer1 overflow interrupt service routine
	PORTB =PORTB ^ (1<<5);
} 



 
 