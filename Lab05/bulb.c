
#include <avr/io.h>

int main(void) {
unsigned char Lvalue = 0;
unsigned int Hvalue=0;
#define threshold 225

DDRC &=~(0b00000001);
DDRB |=0b00000001;


PRR &=~(1<<PRADC);
ADMUX &=~(1<<REFS1);  //for externel AREF SET both REFS1 and REFS0 to 0;
ADMUX &=~(1<<REFS0);
ADMUX |=(1<<ADLAR);
ADMUX |=0b0001;   //select analog input pc1
ADCSRA |=(1<<ADEN);
//
ADCSRA &=~(1<<ADATE);
ADCSRA |=(1<<ADIF); //clear interupt flag bit
//prescaler
ADCSRA |=(1<<ADPS2);
ADCSRA |=(1<<ADPS1);
ADCSRA |=(1<<ADPS0);
ADCSRB &=~(1<<ACME);
DIDR0 |=(1<< ADC1D);

while(1){
     ADCSRA |=(1<<ADSC);
     while((~ADCSRA) & (1<<ADIF));
     Lvalue = (ADCL >> 6);
     Hvalue =ADCH;
     Hvalue = ((Hvalue<<2)|Lvalue);
     if(Hvalue>threshold){
         PORTB=1;
     }else{
         PORTB=0;
     }
     ADCSRA |=(1<<ADIF);
}

}

