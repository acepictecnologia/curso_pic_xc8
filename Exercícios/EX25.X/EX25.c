#include <xc.h>
#include <stdio.h>

#include "../Bibliotecas/config.h"
#include "../Bibliotecas/usart.h"

#define _XTAL_FREQ 8000000

char i=0;       	//Variável de controle para recepção de dados
int adc = 0;        //Varável para armazenamento do ADC
long volt = 0;      //Variável de armazenamento da conversão para tensão
float temp = 0;     //Variável de armazenamento da conversão para temperatura
char dado[4];       //Variável para recepção de dados pela serial
char bufferUSART[50];  //Matriz para armazenamento de dados para envio à serial

void __interrupt() trata_serial(void)
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
    RCIF = 0;           //Limpa o flag da interrupção pela recepção da serial
}

void main(void) {
    
    TRISBbits.TRISB0 = 0;       //Direciona o pino 0 da porta B como saída
    PORTBbits.RB0 = 0;          //Atribui nível lógico 0 ao pino 0 da porta B
    
    ADCON0 = 0b00000001;    /*Bits 7 e 6 = 0 - Não utilizados
                            CHS<3:0> = 0000 - Seleção do canal analógico AN0
                            GO/DONE = 0 - Conversão A/D não iniciada
                            ADON = 1 - Módulo A/D habilitado */  
    
    ADCON1 = 0b00001101;    /*Bits 7 e 6 = 0 - Não utilizados
                            VCFG<1:0> = 00 - Define as tensões de referência 
                                            em GND e VDD
                            PCFG<3:0> = 1101 - Habilita canais 0 e 1 para leitura*/
    
    ADCON2 = 0b10000111;    /*ADFM = 1 - Resultado da conversão justificado à 
                                         direita.
                            Bit 6 - Não utilizado
                            ACQT<2:0> = 0 - 0 TAD
                            ADCS<2:0> = 111 - OScilador Interno para A/D*/
    
    PIE1bits.RCIE = 1;      //Habilita a interrupção pela recepção na serial
    INTCONbits.GIE = 1;     //Habilita interrupção global
    INTCONbits.PEIE = 1;    //Habilita interrupção de periféricos   
    
    init_USART();
    
    string_USART("Conversao A/D: Canais ANo e AN1\r\n");
    
    while(1)
    {
        __delay_ms(1000);    	//Atraso de 1000ms

        ADCON0bits.CHS0 = 0;	//Seleciona canal AN0 para leitura
        
        __delay_us(100);        //Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a conversão A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finalização da conversão
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits à esquerda e soma com a 
                                      parte baixa do resultado da conversão A/D.*/
        
        temp = ((float)adc * 5000) / 1023;	//Converte a leitura adc em tensão
        temp = temp / 10; 		//Converte a tensão em temperatura
        
        ADCON0bits.CHS0 = 1;	//Seleciona o canal AN1 para leitura
        
        __delay_us(100);         	//Atraso de 100us
        
        ADCON0bits.GO = 1;		//Inicia a conversão A/D		
        
        while (ADCON0bits.GO);	//Aguarda a finalização da conversão
        
        adc = ADRESH;		//Armazena a parte alta do resultado em adc
        
        adc = (adc << 8) + ADRESL;	/*Desloca 8 bits à esquerda e soma com a 
                                      parte baixa do resultado da conversão A/D.*/
        
        volt = ((long)adc * 5000) / 1023;	//Converte a leitura adc em tensão
        
        /*Armazena em bufferUSART a string formatada com as informações 
          de temperatura e tensão*/	
        sprintf(bufferUSART, "Temp: %0.1f - Volt: %04lu mV\r\n", temp, volt);
        
         //Transmite o conteúdo de bufferUSART pela Serial
        string_USART(bufferUSART);
        
    }
}
