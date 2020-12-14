#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio2.h>


#define STR_GG      61      //String_Extra Grande
#define STR_G       41      //String_Grande
#define STR_M       21      //String_Média
#define STR_P       11      //String_Pequena
#define DEZ         10      //Base Decimal
#define STR_PP      6       //String_Extra Pequena
#define STRASH      2       //String_Trash
#define SLEEP       3000    //Tempo de Espera entre as impressões de ImprimeVotosPorUrna

#define SUCESSO     printf("\nOPERACAO REALIZADA COM SUCESSO.\n")
#define FRACASSO    printf("\nNAO FOI POSSIVEL REALIZAR A OPERACAO.\n")
#define ERRONUM     printf("\nERRO: DIGITE UM NUMERO MAIOR QUE ZERO.\n")
#define BARRA       textcolor(YELLOW); printf("_____________________________________________________________________\n"); textcolor(LIGHTGRAY)
#define REINICIE    printf("\nINSIRA O(S) ARQUIVO(S) AUSENTES NA PASTA E REINICIE.\n\n")
#define YBUG        textcolor(YELLOW); printf("\BUG..."); textcolor(LIGHTGRAY)
#define RBUG        textcolor(RED); printf("\BUG..."); textcolor(LIGHTGRAY)

//Estruturas_______________________________________________________________________________________________________________
struct TinfoUrna{
	int 		id;
	int			votosDaUrna;
};
typedef struct TinfoUrna infoUrna;

struct TUrna{
    infoUrna        dadosDaUrna;
    struct TUrna    *proximaUrna;
};
typedef struct TUrna nodoUrna;

struct TinfoNo{
    char    nome[STR_GG];
    int     numero;
    int     votosParcial;
    int     votosTotal;
};
typedef struct TinfoNo infoNo;

struct TCandidatoNo{
    infoNo                  info;
    struct TCandidatoNo     *ant;
    struct TCandidatoNo     *prox;
    nodoUrna                *ptUrna;
};
typedef struct TCandidatoNo nodoCandidato;

//Cabeçalho das Funções____________________________________________________________________________________________________

char Menu ( void );

nodoCandidato* CriaListaCandidatos ( void );

nodoCandidato* InsereCandidato( nodoCandidato *ptLista, infoNo dados );

nodoUrna* CriaListaUrnas ( void );

nodoCandidato* AbreCandidatos ( char arquivo[], nodoCandidato *ptLista );

void ImprimeLista ( nodoCandidato *ptLista );

void ImprimirEleitos( nodoCandidato *ptLista, int numEleitos );

nodoCandidato* CadeiaDupla ( nodoCandidato *ptLista );

void InicializaUrnas( nodoCandidato *ptLista );

void ArmazenaVotosDaUrna( nodoCandidato *ptLista, int numeroDaUrna );

nodoCandidato* AdicionarVoto( nodoCandidato *ptLista, int votoNo );

nodoCandidato* ReordenarFila( nodoCandidato *ptLista, nodoCandidato *ptVotado );
//Função que mantem a ordem de prioridade entre os candidatos durante a apuração

void Timer ( int *t ); //Relógio

nodoCandidato* ApurarVotosUrna( int numUrnas, nodoCandidato *ptLista, int *time );

void ImprimeVotosPorUrna( nodoCandidato *ptLista );

void ImpugnarUrna( nodoCandidato *ptLista, int numUrna );

nodoCandidato* Ultimo( nodoCandidato *ptLista );

int VerificaOrdem( nodoCandidato *ptLista );

nodoCandidato* TrazPraFrente( nodoCandidato *ptLista, int* avanca ); // Transporta os Elementos com maior prioridade para Frente da Lista

nodoCandidato* TrazPraTras( nodoCandidato *ptLista, int *recua ); // Transporta os Elementos com menor prioridade para o Fim da Lista

nodoCandidato* ReReordena ( nodoCandidato *ptLista ); //Ordena a Fila após a Impugnação

nodoCandidato* DestruirLista ( nodoCandidato* ptLista );

void SAV1( void ); //Função Principal do S.A.V. Utilizando Listas Lineares


//Funções em Construção
/*

void EliminaCadeiaDupla ( nodoCandidato *ptLista );

nodoCandidato* SelecionaPivo( nodoCandidato *ptLista, int n );

nodoCandidato* QuickSort( nodoCandidato *ptLista, nodoCandidato *Pivo );
*/
