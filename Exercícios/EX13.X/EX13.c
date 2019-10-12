#include <xc.h>
#include "../Bibliotecas/config.h"
#include <stdio.h>

#define _XTAL_FREQ 8000000

char TL1 = 0, TL2 = 0, TL3 = 0;
char T3SB1 = 0, T3SB2 = 0, T3SB3 = 0;

void __interrupt() int_TMR0(void)
{
    if (TMR0IF)
    {
       if (TL1)
       {
           T3SB1++;
           
           if (T3SB1 >= 120)        //Tempo de 3 segundos
           {
               TL1 = 0;
               T3SB1 = 0;
           }
       }
       
       if (TL2)
       {
           T3SB2++;
           
           if (T3SB2 >= 120)        //Tempo de 3 segundos
           {
               TL2 = 0;
               T3SB2 = 0;
           }
       }
       
       if (TL3)
       {
           T3SB3++;
           
           if (T3SB3 >= 120)        //Tempo de 3 segundos
           {
               TL3 = 0;
               T3SB3 = 0;
           }
       }
    }
    TMR0 = 61;
    TMR0IF = 0;
}

void main(void) {
    
    TRISB = 0B00000001;         //Pino 0 da porta B -> entrada e restante saída    
    TRISAbits.TRISA4 = 1;       //Pino 4 da porta A -> pino de entrada
    TRISCbits.TRISC0 = 1;       //Pino 0 da porta C -> pino de entrada
    
    PORTB = 0b00000000;         //Todos os pinos da porta B em nível 0 (leds apagados)
    
    ADCON1 = 0x0F;          //Desabilita todos os canais A/D
    
    INTCON = 0b10100000;        /* GIE/GIEH  = 1  - Habilita interrupção global
                                 * PEIE/GIEL = 0 - Não utilizado
                                 * TMR0IE = 1 - Habilita interrupção pelo TIMER0
                                 * INT0IE = 0 - Não utilizado
                                 * RBIE = 0 - Não utilizado
                                 * TMR0IF = 0 - Flag de overflow p/ o TIMER0
                                 * INT0IF = 0 - Não utilizado
                                 * RBIE = 0 - Não utilizado
                                 */
    
    T0CON = 0b11000111;         /* TMR0ON = 1 - Habilita TIMER0
                                 * T08BIT = 1 - Modo de operação em 8 bits
                                 * T0CS = 0 - Incremento pelo ciclo de máquina
                                 * T0SE = 0 - Não se aplica
                                 * PSA = 0 - Prescaler habilitado
                                 * PS2, PS1, PS0 = 1 - Prescaler de 1:256
                                 */ 
    
    TMR0 = 61;                  //Valor inicial para o reg. TMR0
    
    while(1)
    {
        if (PORTBbits.RB0)
        {
            PORTBbits.RB5 = 1;
            TL1 = 1;
        }
        
        if (PORTCbits.RC0)
        {
            PORTBbits.RB6 = 1;
            TL2 = 1;
        }
        
        if (PORTAbits.RA4)
        {
            PORTBbits.RB7 = 1;
            TL3 = 1;
        }
        
        if (!TL1) PORTBbits.RB5 = 0;
        if (!TL2) PORTBbits.RB6 = 0;
        if (!TL3) PORTBbits.RB7 = 0;
    }
}
