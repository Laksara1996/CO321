
#include <avr/io.h>


int main(void) {
unsigned char Lvalue = 0;
unsigned int Hvalue=0;
DDRC &=~(0b00000001);
DDRB |=0b00111111;
DDRD |=0b00111100;

PRR &=~(1<<PRADC);
ADMUX &=~(1<<REFS1); //Ref AVCC mode
ADMUX |=(1<<REFS0);  
ADMUX |=(1<<ADLAR);
ADMUX |=0b0001;   //select analog input A1 = PC1
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
     PORTB =Hvalue;       //bit9--------------------------------bit0
     PORTD = Hvalue>>4;   //PD5,PD4,PD3,PD2,PB5,PB4,PB3,PB2,PB1,PB0
     ADCSRA |=(1<<ADIF);
}

}

