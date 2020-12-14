#include <stdio.h>
#include "sav.h"

int main()
{
    char    sav;
    int     control;

    textcolor ( LIGHTRED );
    printf("\t\tTribunal Regional Eleitoral - T.R.E.\n");

    control = 1;

    do{
        sav = Menu();

        switch( sav ){
            case '1': //Sistema de Apuração de Votos 1 - LLDE
            clrscr();
            textcolor ( LIGHTRED );
            printf("- S.A.V. 1.0 - LLDE\n");
            textcolor ( LIGHTGRAY );
            SAV1();
            break;
            case '2':
            clrscr();
            textcolor ( RED );
            printf("- S.A.V. 2.0 - HEAP\n"); //Em Projeto
            textcolor ( LIGHTGRAY );
            // SAV2();
            break;
            default: printf("ERRO-01-Menu");
        }
        printf("\n(1)Continuar\n(0)Sair\n\n");
        scanf(" %d", &control);
        fflush(stdin);
        clrscr();
    } while ( control == 1 );
    return 0;
}


