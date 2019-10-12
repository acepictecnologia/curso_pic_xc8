#include <xc.h>

#include "../Bibliotecas/config.h"

#define _XTAL_FREQ 8000000

void escreve_USART(char c);     //Protótipo da função escreve_USART())

void main(void) {
    
    TXSTAbits.TXEN = 1; //Habilita a transmissão pela USART
    TXSTAbits.SYNC = 0; //Habilita o modo assíncrono
    RCSTAbits.SPEN = 1; //Habilita USART e configura os pinos RC6 e RC7 como TX e RX
    
    TXSTAbits.BRGH = 0;         //Configura os controle de baud rate
    BAUDCTLbits.BRG16 = 0;
    
    SPBRG = 12;                 //Baud Rate = 9600 bps
        
    //Chama a função escreve_USART com o caractere a ser transmitido
    escreve_USART('P');
    escreve_USART('I');
    escreve_USART('C');
    escreve_USART('1');
    escreve_USART('8');
    escreve_USART('F');
    escreve_USART('4');
    escreve_USART('5');
    escreve_USART('2');
    escreve_USART('0');    
    
    while(1)
    {
    }
   
}

void escreve_USART(char c)
{
   while(!TRMT);        //Aguarda a finalização da transmissão do caractere
   TXREG = c;           //Carrega em TXREG e transmite o caractere via USART
}
