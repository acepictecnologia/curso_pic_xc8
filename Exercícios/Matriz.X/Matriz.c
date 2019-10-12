#include <xc.h>
#include <stdio.h>

char buffer[25];

int teste = 3458;

void main(void) {
    
    sprintf(buffer, "Valor de teste = %d", teste);
    
    while(1);
}
