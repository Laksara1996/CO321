#include <avr/io.h>

void delay_timer0(){
    TCNT0 = 131; /*load timer counter register*/
    TCCR0A = 0x00; /*set the Timer0 under normal mode with 1:8 prescaler*/
    TCCR0B =0x04;
    while((TIFR0 & 0x01)==0); /*wait till timer overflow bit (T0V0) is set*/
    TCCR0A =0x00;
    TCCR0B=0x00;
    TIFR0 = 0x01;
}

int main(void){
    DDRB =DDRB|(1<<5);
    while(1){
        PORTB = PORTB ^ (1<<5);
    }
}