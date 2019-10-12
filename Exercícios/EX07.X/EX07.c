#include <xc.h>
#include "../Bibliotecas/config.h"

#define _XTAL_FREQ 8000000

void lcd_ini(void);
void lcd_cmd(char cmd);
void lcd_envia_byte(char nivel, char dado);

void main(void) {
    
    ADCON1 = 0x0F;      //Desabilita todos os canais A/D
    
    lcd_ini();          //Inicializa o LCD
    
    //0x80 => 1, 2, 3, 4.... 
    
    lcd_envia_byte(0, 0x83);
   //PIC18F4520
    lcd_envia_byte(1, 'P');
    lcd_envia_byte(1, 'I');
    lcd_envia_byte(1, 'C');
    lcd_envia_byte(1, '1');
    lcd_envia_byte(1, '8');
    lcd_envia_byte(1, 'F');
    lcd_envia_byte(1, '4');
    lcd_envia_byte(1, '5');
    lcd_envia_byte(1, '2');
    lcd_envia_byte(1, '0');
    
    //0xc0 => coluna 4 = 0xc3
    lcd_envia_byte(0, 0xC3);
    
    //LCD 8 BITS
    
    lcd_envia_byte(1, 'L');
    lcd_envia_byte(1, 'C');
    lcd_envia_byte(1, 'D');
    lcd_envia_byte(1, ' ');
    lcd_envia_byte(1, '8');
    lcd_envia_byte(1, ' ');
    lcd_envia_byte(1, 'B');
    lcd_envia_byte(1, 'I');
    lcd_envia_byte(1, 'T');
    lcd_envia_byte(1, 'S');
       
    while(1);
}

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
   lcd_cmd(0x38);       //Comunicação em 8 bits com 2 linhas e matriz 7X5
   __delay_us(40);      //Atraso de 40us
   lcd_cmd(0x01);       //Limpa a memória do LCD
   __delay_ms(2);       //Atraso de 2 ms
   lcd_cmd(0x0C);       //Liga o display sem cursor
   __delay_us(40);      //Atraso de 40us
   lcd_cmd(0x06);       //Desloca o curso à direita após um novo caractere
   __delay_us(40);      //Atraso de 40us
}

void lcd_cmd(char cmd)
{
    LATD = cmd;         //Atribui à porta D o valor correspondente à variável cmd
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
