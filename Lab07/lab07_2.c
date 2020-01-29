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

void EEPROMwrite(unsigned int address,char data){
    //wait for completion of previous write
    while(EECR & (1<<EEPE));

    //set up address and data regs
    EEAR = address;
    EEDR = data;
    //write logical 1 to EEMPE
    EECR |= (1<<EEMPE);
    //start eeprom write
    EECR |=(1<<EEPE);
}

char EEPROMread(unsigned int address){
    //wait for completion of writes
    while(EECR & (1<<EEPE));
    //set up adress;
    EEAR = address;
    //start eeprom read
    EECR |=(1<<EERE);
    //return data;
    return EEDR;
}


int main(){
    usart_init(MYUBRR);

    unsigned char data[100];
    unsigned int addr=0;

        while(addr<1023){
            unsigned char i=0;
            while(1){
                data[i] = EEPROMread(addr); 
                if(data[i]=='\n' || data[i]==255){
                   break; 
                }
                i++;
                addr++;
            }
            i=0;
            while(1){
                usart_send(data[i]);
                if(data[i]=='\n' || data[i]==255){
                   break; 
                }
                i++;
            } 

            addr++;
        }
   
}

