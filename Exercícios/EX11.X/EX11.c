#include <xc.h>
#include "../Bibliotecas/config.h"
#include <stdio.h>

#include "../Bibliotecas/LCD4bits.h"

#define _XTAL_FREQ 8000000

int conta = 0;              //Variável de contagem
char contaInt = 0, controle = 0;    //Varáveis de controle

char bufferLCD[16];         //Matriz de armazenamento da stringo para o LCD

void __interrupt() int_ext(void)
{
    if (INT0IF)             //Se o flag da interrupção for 1 (INT0IF)
    {
      contaInt++;                	//Incrementa a variável conta
        if (contaInt>=10)          	//Quando conta > ou = a 10
        {
            contaInt = 0;          	//Zera a variável conta
            switch (++controle) 	/*Incrementa a variável controle antes de 
                                      ser testada*/
            {
                case 1: PORTBbits.RB4 = 1; //Caso seja 1, liga o LED do pino RB4
                break;
                case 2: PORTBbits.RB5 = 1; //Caso seja 2, liga o LED do pino RB5
                break;
                case 3: PORTBbits.RB6 = 1; //Caso seja 3, liga o LED do pino RB6
                break;
                case 4: PORTBbits.RB7 = 1; //Caso seja 4, liga o LED do pino RB7
                break;
                case 5: PORTB = 0b00000000; //Caso seja 5, apaga todos os LEDs
                        controle = 0;      //Zera a variável controle.
            }  
        }
    }  
    INT0IF = 0;
}

void main(void) {
    TRISB = 0b00000001;     /*Direciona o pino 0 da porta B como entrada
                              e o restante como saída*/
    PORTB = 0b00000000;     //Coloca em 0 todos os pinos da porta B
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    
    INTCON = 0b10010000;        /* GIE/GIEH  = 1  - Habilita interrupção global
                                 * PEIE/GIEL = 0 - Não utilizado
                                 * T0IE = 0 - Não utilizado
                                 * INT0IE = 1 - Habilita interrupção externa
                                 * RBIE = 0 - Não utilizado
                                 * T0IF = 0 - Não utilizado
                                 * INT0IF = 0 - Limpa flag para interrupção externa
                                 * RBIE = 0 - Não utilizado
                                 */
    
    INTEDG0 = 1;                //Interrupção na borda de subida do sinal
    
    lcd_ini();                  //Inicializa o LCD
    
    //Posiciona o cursor na coluna 2 da linha 1 e escreve no LCD
    lcd_escreve_bf(1, 2, "INT. EXTERNA");
    
    //Posiciona o cursor na coluna 2 da linha 2 e escreve na LCD
    lcd_escreve_bf(2, 2, "CONTAGEM: 000");
    
    while(1)
    {
        __delay_ms(1000);
        
        conta++; 
        
        if (conta>999) conta = 0;
        
        //Escreve o resultado da variável conta no LCD
        sprintf(bufferLCD, "%03d", conta);
        
        //Posiciona o cursor na coluna 12 da linha 2 e escreve no LCD
        lcd_escreve_bf(2, 12, bufferLCD);
        
    }
}
