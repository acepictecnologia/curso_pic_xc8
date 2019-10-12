#include <xc.h>
#include "../Bibliotecas/config.h"

#define _XTAL_FREQ 8000000

int change = 0;     //Vari�vel de mudan�a de estado
__bit run = 0;      //Vari�vel de controle para mudan�a de estado

void main(void) {
    
    int i;      //Vari�vel de controle 
    
    TRISB = 0b00000000; //Direciona os pinos da porta B como sa�da
    LATB = 0b00000000;  //Atribui n�vel l�gico 0 a todos os pinos da porta B (Leds Apagados)
    
    TRISCbits.TRISC0 = 1;   //Direciona o pino 0 da porta C como entrada
    
    while(1)
    {
        if (PORTCbits.RC0 == 1)
        {
            change++;       //Incrementa a vari�vel change
            run = 1;        //Atribui 1 � vari�vel run
        }
        
        if (change == 1 && run == 1)
        {
            for (i = 0; i < 5; i++)
            {
                LATB = 0b00000000;
                __delay_ms(100);
                LATB = 0b11111111;
                __delay_ms(100);
            }
            LATB = 0b00000000;
            run = 0;
        }
        
        if (change == 2 && run == 1)
        {
            LATB = 0b00000001;
            
            for (i = 0; i <= 7; i++)
            {
                __delay_ms(100);
                LATB = LATB << 1;
            }
            run = 0;
        }
        
        if (change == 3 && run == 1)
        {
            LATB = 0b10000000;
            
            for (i = 0; i <= 7; i++)
            {
                __delay_ms(100);
                LATB = LATB >> 1;
            }
            change = 0;
            run = 0;
        }
        
        __delay_ms(300);
    }
}
