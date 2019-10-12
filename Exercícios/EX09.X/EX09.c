#include <xc.h>
#include "../Bibliotecas/config.h"
#include <stdio.h>

#include "../Bibliotecas/LCD4bits.h"

#define _XTAL_FREQ 8000000

int conta = 0;          //Variável de contagem
char bufferLCD[16];     //Matriz para armazanamento da string para o LCD

void main(void) {
    ADCON1 = 0x0F;      //Desabilita todos os canais A/D
    
    lcd_ini();          //Inicializa o LCD
    
    lcd_envia_byte(0, 0x80);    //Posciona o cursor na coluna 1 e linha 1 do LCD
    
    sprintf(bufferLCD, "CONTAGEM: 000");
    
    lcd_escreve_bf(bufferLCD);
    
    while(1)
    {
        lcd_envia_byte(0, 0x8A);    //Posiciona o cursor na coluna 11 da linha 1
        
        sprintf(bufferLCD, "%03d", conta);
        
        lcd_escreve_bf(bufferLCD);
        
        conta++;
        
        if (conta > 999) conta = 0;
        
        __delay_ms(1000);        
    }
}
