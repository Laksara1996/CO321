#include<avr/io.h>
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void usart_init(unsigned int ubrr){
    UBRR0H = (unsigned char) (ubrr>>8);
    UBRR0L = (unsigned char) (ubrr);

    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    UCSR0C &= ~(1<<USBS0);
    UCSR0C |=(3<<UCSZ00);  
}

void usart_send(unsigned char data){
    while( !(UCSR0A & ( 1<<UDRE0 )) );

    UDR0 = data;
}

unsigned char usart_receive(void){
    while( !(UCSR0A & (1<<RXC0)) );

    return UDR0;
}

int main(){
    usart_init(MYUBRR);

    unsigned char data[73]= "E15043 Bhagya T P Y E15048 Chandrasiri S A G L E15363 Thilakrathne S D B\n";
    while(1){
        //data = usart_receive();
        unsigned char i;
        for(i=0;i<73;i++)
            usart_send(data[i]);
        
    }

}