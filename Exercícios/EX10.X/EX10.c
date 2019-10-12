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
    
    //Posiciona o cursor na coluna 1 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 1, "CONTAGEM: 000");
    
    while(1)
    {
        sprintf(bufferLCD, "%03d", conta);
        
        //Posiciona o cursor na coluna 11 da linha 1 e escreve no LCD
        lcd_escreve_bf(1, 11, bufferLCD);
        
        conta++;
        
        if (conta > 999) conta = 0;
        
        __delay_ms(1000);        
    }
}
