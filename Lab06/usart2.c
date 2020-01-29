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

    unsigned char data[100];
    unsigned char encrypted[100];
    while(1){
        unsigned char i=0;
        data[i] = usart_receive();
        while(data[i] !='\n'){
            i++;
            data[i] = usart_receive(); 
        }

        i=0;
        while(data[i] !='\n'){
            if( (65<=data[i] && 90>=data[i]) || (97<=data[i] && 122>=data[i]) ){
                encrypted[i]=data[i]+3;
            }
            else{
                encrypted[i]=data[i];
            }
            i++;
        }
        encrypted[i]='\n';

        i=0;
        while(encrypted[i] !='\n'){
            usart_send(encrypted[i]);
            i++;
        }   
        usart_send(encrypted[i]); 
        
    }

}