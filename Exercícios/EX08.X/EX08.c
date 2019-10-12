#include <xc.h>
#include "../Bibliotecas/config.h"
#include "../Bibliotecas/LCD4bits.h"

#define _XTAL_FREQ 8000000

void main(void) {
    
    ADCON1 = 0x0F;      //Desabilita todos os canais A/D
    
    lcd_ini();          //Inicializa o LCD
    
    //0x80 => 1, 2, 3, 4.... 
    
    lcd_envia_byte(0, 0x83);
   //PIC18F4520
    lcd_envia_byte(1, 'P');
    lcd_envia_byte(1, 'I');
    lcd_envia_byte(1, 'C');
    lcd_envia_byte(1, '1');
    lcd_envia_byte(1, '8');
    lcd_envia_byte(1, 'F');
    lcd_envia_byte(1, '4');
    lcd_envia_byte(1, '5');
    lcd_envia_byte(1, '2');
    lcd_envia_byte(1, '0');
    
    //0xc0 => coluna 4 = 0xc3
    lcd_envia_byte(0, 0xC3);
    
    //LCD 4 BITS
    
    lcd_envia_byte(1, 'L');
    lcd_envia_byte(1, 'C');
    lcd_envia_byte(1, 'D');
    lcd_envia_byte(1, ' ');
    lcd_envia_byte(1, '4');
    lcd_envia_byte(1, ' ');
    lcd_envia_byte(1, 'B');
    lcd_envia_byte(1, 'I');
    lcd_envia_byte(1, 'T');
    lcd_envia_byte(1, 'S');
       
    while(1);
}