#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//PD7 pin is connected to a push button
//6 Leds connected to PORTB(6LSB)
unsigned char bitoffset = 0x00;
int main(){
  
  DDRD = DDRD & ~(1<<2); //PD2 is input
  DDRD = DDRD & ~(1<<3);
  DDRB = 0xFF ; //Port B is set to output
  EICRA |=(1<<ISC01);
  EICRA |=(1<<ISC00);
  EICRA |=(1<<ISC11);
  EICRA |=(1<<ISC10);

  sei();
  EIMSK |= (1<<INT0);
  EIMSK |= (1<<INT1);
  PORTB =0x00;
  while(1){
      
    
  }
}

ISR (INT0_vect){
     
     PORTB |=(1<<bitoffset);
     bitoffset +=1;
     if(bitoffset > 5){
          bitoffset=0;
     }
}

ISR (INT1_vect){
    
     PORTB &= ~(1<<bitoffset);
     bitoffset +=1;
     if(bitoffset > 5){
          bitoffset=0;
     }
}