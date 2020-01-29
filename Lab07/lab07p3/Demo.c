//Headers
#include <stdlib.h>
#include <avr/io.h>
#include "Keypad.h"
#include "lcd.h"

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


int main(void)
{   
	KP_Setup();
	lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    
	char key = Key_None;
	uint8_t shmain = 1;
	while(1){
		if(shmain == 1){
			lcd_clrscr();
			lcd_puts("Change key : A\n");
			lcd_gotoxy(0,1); 
			lcd_puts("Encrypt msg : B\n");
			shmain=0;
		}
		key = KP_GetKey();
		if(key == 'A'){
			lcd_clrscr();
			lcd_puts("Enter new Key\n");
    	    lcd_gotoxy(0,1); 
			_delay_ms(500);
			while(1){
				key = KP_GetKey();
				if(key != Key_None){
					lcd_putc(key);
					EEPROMwrite(0,key-48);
					_delay_ms(2000);
					break;
				}
			}
			lcd_clrscr();
    	    lcd_puts("Key Changed\n");
			shmain = 1;
			_delay_ms(1500);
		
		}else if(key=='B'){
           lcd_clrscr();
		   lcd_puts("Enter your text\n");
		   lcd_gotoxy(0,1);
		   _delay_ms(1000);
		   char buf[10] = "";
		   uint8_t count =0;
		   while(1){
			  if(count>9){
				  break;
			  }
              key = KP_GetKey();
				if(key != Key_None){
					lcd_putc(key);
					buf[count]=key;
					count++;
					_delay_ms(500);
				}
		   } 
		   _delay_ms(500);
		   lcd_clrscr();
		   lcd_puts("Your Cipher Text\n");
		   lcd_gotoxy(0,1);
		   _delay_ms(1000);
		   char ckey =EEPROMread(0);
		   for(int i=0;i<10;i++){
			   lcd_putc(buf[i]+ckey);
		   }
		    shmain=1;
			_delay_ms(5000);
		}
	}
	return 0;
}



