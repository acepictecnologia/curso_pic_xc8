#include <xc.h>

#include "../Bibliotecas/config.h"
#include "usart.h"

#define _XTAL_FREQ 8000000

char dado[4];                   //vetor p/ armazenamento de dados recebidos pela serial

char i = 0;                     //Variável de controle para recepção de dados     

void main(void) {
    
    ADCON1 = 0x0F;              //Desabilita os canais A/D
    TRISBbits.TRISB0 = 0;       //Pino 0 da porta B como saída
    PORTBbits.RB0 = 0;          //Atribui 0 ao pino 0 da porta B
    
    init_USART();               //Configura a USART
        
    string_USART("Microcontrolador PIC18F4520\r\n");
    string_USART("LD1 - ACENDE O LED\r\n");
    string_USART("DL1 - APAGA O LED\r\n");
    
    while(1)
    {
      if (RCIF)                 /*Verifica o flag da interrupção da serial
                                 * quando este é 1, trata o dado recebido*/
      {
        dado[i] = USART_le();   /*Recebe um caractere e armazena em dado
                                 * na posição i */ 
        
        if (dado[i] == 0x0D)
        {
            //Se a string contida no vetor dado = LD1
            if (dado[0] == 'L' && dado[1] == 'D' && dado[2] == '1')
            {
                PORTBbits.RB0 = 1;      //Acende o LED
                string_USART("L1");     //Envia L1 pela serial
            }
            
            //Se a string contida no vetor dado = DL1
            if (dado[0] == 'D' && dado[1] == 'L' && dado[2] == '1')
            {
                PORTBbits.RB0 = 0;      //Apaga o LED
                string_USART("L0");     //Envia L0 pela serial
            }
            
         i = 0;   
        }
        
        else i++;       //Se o caractere recebido for diferente de 0x0D, incrementa i
      }
    }   
}