#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//PD7 pin is connected to a push button
//6 Leds connected to PORTB(6LSB)

int main(){
  
  DDRD = DDRD & ~(1<<2); //PD7 is input
  DDRB = 0xFF ; //Port B is set to output
  EICRA |=(0<<ISC00);
  EICRA |=(1<<ISC01);
  sei();
  EIMSK |= (1<<INT0);
  PORTB =1;
  while(1){
      
    
  }
}

ISR (INT0_vect){
     PORTB = PORTB ^ 1;
     _delay_ms(300);
}