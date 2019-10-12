#include "usart.h"

void init_USART(void)
{
    TXSTAbits.TXEN = 1; //Habilita a transmissão pela USART
    RCSTAbits.CREN = 1; //Habilita a recepção pela USART
    TXSTAbits.SYNC = 0; //Habilita o modo assíncrono
    RCSTAbits.SPEN = 1; //Habilita USART e configura os pinos RC6 e RC7 como TX e RX
    
    TXSTAbits.BRGH = 0;         //Configura os controle de baud rate
    BAUDCTLbits.BRG16 = 0;
    
    SPBRG = 12;                 //Baud Rate = 9600 bps  
}

void escreve_USART(char c)
{
   while(!TRMT);        //Aguarda a finalização da transmissão do caractere
   TXREG = c;           //Carrega em TXREG e transmite o caractere via USART
}

void string_USART(char *str)
{
  while(*str != '\0')
  {
      escreve_USART(*str);
      str++;
  }
}

char USART_le(void)
{
    while(!RCIF);       //Enquanto RCIF = 0, aguarda a chegada de um caractere
    return RCREG;       //Retorna o caractere recebido
}
