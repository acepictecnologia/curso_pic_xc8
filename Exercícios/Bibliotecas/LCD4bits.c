#include "LCD4bits.h"

void lcd_ini(void)
{
    char i;                 //Variável de controle para envio dos comandos
    
   TRISD = 0b00000000;      //Todos os pinos da porta D como saída 
   TRISEbits.TRISE0 = 0;    //Pino 0 da porta E como saída
   TRISEbits.TRISE1 = 0;    //Pino 1 da porta E como saída
   
   LATD = 0b00000000;       //Toda a porta D em nível lógico 0
   LATEbits.LATE0 = 0;      //Pino 0 da porta E em nível 0
   LATEbits.LATE1 = 0;      //Pino 1 da porta E em nível 0
   
   __delay_ms(15);          //Atraso de 15ms
   
   for(i = 0; i < 3; i++)
   {
       lcd_cmd(0x30);
       __delay_ms(5);
   }
   lcd_cmd(0x02);       //LCD deve trabalhar com 4 bits de dados
   __delay_us(40);      //Atraso de 40us
   lcd_cmd(0x28);       //Comunicação em 4 bits com 2 linhas e matriz 7X5
   __delay_us(40);      //Atraso de 40us
   lcd_cmd(0x01);       //Limpa a memória do LCD
   __delay_ms(2);       //Atraso de 2 ms
   lcd_cmd(0x0C);       //Liga o display sem cursor
   __delay_us(40);      //Atraso de 40us
   lcd_cmd(0x06);       //Desloca o curso à direita após um novo caractere
   __delay_us(40);      //Atraso de 40us
}

char set_bit(char cmd, char comp)
{
    if ((cmd & comp) >= 1)
        return 1;
    else
        return 0;
}

//0x30 => 0b00110000 & 0b00010000 => > 0
//0x0c => 0b00001100 & 0b00010000 => = 0

void lcd_cmd(char cmd)
{
    LATDbits.LATD4 = set_bit(cmd, 0b00010000);
    LATDbits.LATD5 = set_bit(cmd, 0b00100000);
    LATDbits.LATD6 = set_bit(cmd, 0b01000000);
    LATDbits.LATD7 = set_bit(cmd, 0b10000000);
    
    LATEbits.LATE1 = 1; //Atribui 1 ao pino 1 da porta E (EN = 1)
    LATEbits.LATE1 = 0; //Atribui 0 ao pino 1 da porta E (EN = 0)
    
    __delay_us(100);    //Gera um atraso de 100us
    
    LATDbits.LATD4 = set_bit(cmd, 0b00000001);
    LATDbits.LATD5 = set_bit(cmd, 0b00000010);
    LATDbits.LATD6 = set_bit(cmd, 0b00000100);
    LATDbits.LATD7 = set_bit(cmd, 0b00001000);
    
    LATEbits.LATE1 = 1; //Atribui 1 ao pino 1 da porta E (EN = 1)
    LATEbits.LATE1 = 0; //Atribui 0 ao pino 1 da porta E (EN = 0)
}

void lcd_envia_byte(char nivel, char dado)
{
    LATEbits.LATE0 = nivel; //habilita comando ou leitura para o LCD
    __delay_us(100);        //Atraso de 100us
    LATEbits.LATE1 = 0;     //Atribui 0 ao pino 1 da porta E (EN = 0)
    lcd_cmd(dado);
}

void lcd_escreve_bf(char lin, char col, char *str)
{
    char end;               //Variável de controle para o posicionamento
                            //do cursor
    
    if (lin == 1)               //Caso a variável lin seja 1
        end = col + 0x80 - 1;   //Posciona o cursor na coluna informada
    else if (lin == 2)          //Caso a variável lin seja 2
        end = col + 0xC0 - 1;   //Posiciona o cursor na coluna informada
    
    lcd_envia_byte(0, end);
    
    while(*str)
    {
       lcd_envia_byte(1,*str);
       str++;
    }
}
