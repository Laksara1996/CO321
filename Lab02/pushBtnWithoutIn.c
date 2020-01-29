#include <avr/io.h>
#include <util/delay.h>

//PD7 pin is connected to a push button
//6 Leds connected to PORTB(6LSB)

int main(){
  
  DDRD = DDRD & ~(1<<7); //PD7 is input
  DDRB = 0xFF ; //Port B is set to output
  unsigned char count = 0x00;
  PORTB =0x00;
  while(1){
      
     if((PIND >>7 )& 1){
        count = count + 1;   
     }
     PORTB =count;
     _delay_ms(100);
    // count = count + 1;
  }
}