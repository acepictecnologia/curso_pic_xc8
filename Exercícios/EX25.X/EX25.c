#include <xc.h>
#include <stdio.h>

#include "../Bibliotecas/config.h"
#include "../Bibliotecas/usart.h"

#define _XTAL_FREQ 8000000

char i=0;       	//Vari�vel de controle para recep��o de dados
int adc = 0;        //Var�vel para armazenamento do ADC
long volt = 0;      //Vari�vel de armazenamento da convers�o para tens�o
float temp = 0;     //Vari�vel de armazenamento da convers�o para temperatura
char dado[4];       //Vari�vel para recep��o de dados pela serial
char bufferUSART[50];  //Matriz para armazenamento de dados para envio � serial

void __interrupt() trata_serial(void)
{
    if (RCIF)                 /*Verifica o flag da interrup��o da serial
                                 * quando este � 1, trata o dado recebido*/
      {
        dado[i] = USART_le();   /*Recebe um caractere e armazena em dado
                                 * na posi��o i */ 
        
        if (dado[i] == 0x0D)
        {
            //Se a string contida no vetor dado = LD1
            if (dado[0] == 'L' && dado[1] == 'D' && dado[2] == '1')
            {
                PORTBbits.RB0 = 1;      //Acende o LED                
            }
            
            //Se a string contida no vetor dado = DL1
            if (dado[0] == 'D' && dado[1] == 'L' && dado[2] == '1')
            {
                PORTBbits.RB0 = 0;      //Apaga o LED
            }
            
         i = 0;   
        }
        
        else i++;       //Se o caractere recebido for diferente de 0x0D, incrementa i
      }
    RCIF = 0;           //Limpa o flag da interrup��o pela recep��o da serial
}

void main(void) {
    
    TRISBbits.TRISB0 = 0;       //Direciona o pino 0 da porta B como sa�da
    PORTBbits.RB0 = 0;          //Atribui n�vel l�gico 0 ao pino 0 da porta B
    
    ADCON0 = 0b00000001;    /*Bits 7 e 6 = 0 - N�o utilizados
                            CHS<3:0> = 0000 - Sele��o do canal anal�gico AN0
                            GO/DONE = 0 - Convers�o A/D n�o iniciada
                            ADON = 1 - M�dulo A/D habilitado */  
    
    ADCON1 = 0b00001101;    /*Bits 7 e 6 = 0 - N�o utilizados
                            VCFG<1:0> = 00 - Define as tens�es de refer�ncia 
                                            em GND e VDD
                            PCFG<3:0> = 1101 - Habilita canais 0 e 1 para leitura*/
    
    ADCON2 = 0b10000111;    /*ADFM = 1 - Resultado da convers�o justificado � 
                                         direita.
                            Bit 6 - N�o utilizado
                            ACQT<2:0> = 0 - 0 TAD
                            ADCS<2:0> = 111 - OScilador Interno para A/D*/
    
    PIE1bits.RCIE = 1;      //Habilita a interrup��o pela recep��o na serial
    INTCONbits.GIE = 1;     //Habilita interrup��o global
    INTCONbits.PEIE = 1;    //Habilita interrup��o de perif�ricos   
    
    init_USART();
    
    string_USART("Conversao A/D: Canais ANo e AN1\r\n");
    
    while(1)
    {
        __delay_ms(1000);    	//Atraso de 1000ms

        ADCON0bits.CHS0 = 0;	//Seleciona canal AN0 para leitura
        
        __delay_us(100);        //Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a convers�o A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finaliza��o da convers�o
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits � esquerda e soma com a 
                                      parte baixa do resultado da convers�o A/D.*/
        
        temp = ((float)adc * 5000) / 1023;	//Converte a leitura adc em tens�o
        temp = temp / 10; 		//Converte a tens�o em temperatura
        
        ADCON0bits.CHS0 = 1;	//Seleciona o canal AN1 para leitura
        
        __delay_us(100);         	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a convers�o A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finaliza��o da convers�o
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits � esquerda e soma com a 
                                      parte baixa do resultado da convers�o A/D.*/
        
        volt = ((long)adc * 5000) / 1023;	//Converte a leitura adc em tens�o
        
        /*Armazena em bufferUSART a string formatada com as informa��es 
          de temperatura e tens�o*/	
        sprintf(bufferUSART, "Temp: %0.1f - Volt: %04lu mV\r\n", temp, volt);
        
         //Transmite o conte�do de bufferUSART pela Serial
        string_USART(bufferUSART);
        
    }
}
