#include<xc.h>

void lcd_ini(void);
void lcd_cmd(char cmd);
void lcd_envia_byte(char nivel, char dado);
char set_bit(char cmd, char comp);
void lcd_escreve_bf(char lin, char col, char *str);

#define _XTAL_FREQ 8000000