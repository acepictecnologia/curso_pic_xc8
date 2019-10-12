#include <xc.h>
#include "config.h"

#define _XTAL_FREQ 8000000

void main(void) {
    
    TRISBbits.TRISB7 = 0;   //Define o pino 7 da porta B como saída
    TRISBbits.TRISB6 = 0;   //Define o pino 6 da porta B como saída
    TRISBbits.TRISB5 = 0;   //Define o pino 5 da porta B como saída
    
    LATBbits.LATB7 = 0;     //Atribui nível lógico 0 ao pino 7 da porta B
    LATBbits.LATB6 = 0;     //Atribui nível lógico 0 ao pino 6 da porta B
    LATBbits.LATB5 = 0;     //Atribui nível lógico 0 ao pino 5 da porta B
    
    TRISAbits.TRISA4 = 1;   //Define o pino 4 da porta A como entrada
    TRISBbits.TRISB0 = 1;   //Define o pino 0 da porta B como entrada
    TRISCbits.TRISC0 = 1;   //Define o pino 0 da porta C como entrada
    
    while(1)                 //Loop infinito
    {
        if (PORTAbits.RA4 == 1) //Se pino 4 da porta A = 1, botão B3 presssionado 
        {
            LATBbits.LATB7 = ~LATBbits.LATB7; //Inverte o estado do pino 7 da porta B
        }
        
        if (PORTBbits.RB0 == 1) //Se pino 0 da porta B = 1, botão B1 presssionado 
        {
            LATBbits.LATB5 = ~LATBbits.LATB5; //Inverte o estado do pino 5 da porta B
        }
        
        if (PORTCbits.RC0 == 1) //Se pino 0 da porta C = 1, botão B2 presssionado 
        {
            LATBbits.LATB6 = ~LATBbits.LATB6; //Inverte o estado do pino 6 da porta B
        }
        
        __delay_ms(300);        //Gera um delay de 300ms
    }
}


