#include <stdio.h>
#include "sav.h"

char Menu ( void )
{
    char sav;

    do{
        textcolor ( LIGHTRED );
        printf("\t\t(1) Sistema de Apuracao de Votos\n\t\t\t- S.A.V. 1.0 -\n");
        printf("\t\t(2) Sistema de Apuracao de Votos\n\t\t\t- S.A.V. 2.0 -\n");
        textcolor ( LIGHTGRAY );
        sav = getche();
        if ( sav != '1' &&  sav != '2' ) clrscr();
    } while ( sav != '1' &&  sav != '2' );

    return sav;
}

nodoCandidato* CriaListaCandidatos ( void )
{
    return NULL;
}

nodoCandidato* InsereCandidato( nodoCandidato *ptLista, infoNo dados )
{
    nodoCandidato *novo;

    novo = ( nodoCandidato* ) malloc ( sizeof( nodoCandidato ) );

    novo->info = dados;
    novo->ant = ptLista;
    ptLista = novo;

    return ptLista;
}

nodoUrna* CriaListaUrnas ( void )
{
    return NULL;
}

nodoCandidato* AbreCandidatos ( char arquivo[], nodoCandidato *ptLista )
{
    FILE    *fp1;
    infoNo  dadosBuffer;
    char    string[STR_GG], subs1[STR_P], subtrash[STRASH];

    if ( ! ( fp1 = fopen ( arquivo, "r" ) ) ){
        FRACASSO;
        return NULL;
    }
    else{
            printf("\n------------- CANDIDATOS LIDOS E ARMAZENADOS -------------\n");
            BARRA;
            dadosBuffer.votosParcial = 0;
            dadosBuffer.votosTotal = 0;
            while ( ! feof ( fp1 ) ){
                if ( fgets ( string, sizeof( string ), fp1 ) == NULL ){
                    BARRA;
                }
                else{
                        strcpy ( subs1, strtok( string, " " ) );
                        dadosBuffer.numero = atoi( subs1 );

                        strcpy ( subtrash, strtok( NULL, " ") );
                        strcpy ( dadosBuffer.nome, strtok( NULL, "\n"));
                    //Listando os Candidatos
                        printf("\n%d - %50s - %d Votos\n", dadosBuffer.numero, dadosBuffer.nome, dadosBuffer.votosTotal );

                        ptLista = InsereCandidato ( ptLista, dadosBuffer );
                }
            }
            fclose( fp1 );
    }
    return ptLista;
}

void ImprimeLista ( nodoCandidato *ptLista )
{
    nodoCandidato *ptAux;

    ptAux = ptLista;

    while ( ptAux != NULL ){
        printf("\n%d - %d Votos\n", ptAux->info.numero, ptAux->info.votosTotal );
        ptAux = ptAux->prox;
    }
}

void ImprimirEleitos( nodoCandidato *ptLista, int numEleitos )
{
    int           i;
    nodoCandidato *Aux;

    Aux = ptLista;
    BARRA;

    for ( i = 1; i <= numEleitos; i++ ){
        if ( Aux != NULL ){
            printf("\n%d - %50s - %d Votos\n", Aux->info.numero, Aux->info.nome, Aux->info.votosTotal );
            Aux = Aux->prox;
        }
    }
    BARRA;
}

nodoCandidato* CadeiaDupla ( nodoCandidato *ptLista )
{
    nodoCandidato *ptAux, *ProxAux;
    nodoCandidato *ptAux1;

    ptLista->prox = NULL;
    ptAux = ptLista;

    while ( ptAux->ant != NULL ){
        ProxAux = ptAux;
        ptAux = ptAux->ant;
        ptAux->prox = ProxAux;
    }

    ptAux1 = ptLista;
    while ( ptAux1->ant != NULL ){
        ptAux1 = ptAux1->ant;
    }
    ptLista = ptAux1;

    return ptLista;
}

void InicializaUrnas( nodoCandidato *ptLista )
{
    nodoCandidato *ptAux;

    ptAux = ptLista;

    while ( ptAux != NULL ){
        ptAux->ptUrna = NULL;
        ptAux = ptAux->prox;
    }
}

void ArmazenaVotosDaUrna( nodoCandidato *ptLista, int numeroDaUrna )
{
    nodoUrna        *nova;
    nodoCandidato   *ptAux;
    infoUrna        dadosUrna;

    dadosUrna.id = numeroDaUrna;

    ptAux = ptLista;
    while ( ptAux != NULL ){
        dadosUrna.votosDaUrna = ptAux->info.votosParcial;
        ptAux->info.votosParcial = 0;

        nova = ( nodoUrna* ) malloc ( sizeof( nodoUrna ) );

        nova->dadosDaUrna = dadosUrna;
        nova->proximaUrna = ptAux->ptUrna;
        ptAux->ptUrna = nova;

        ptAux = ptAux->prox;
    }
}

nodoCandidato* AdicionarVoto( nodoCandidato *ptLista, int votoNo )
{
    nodoCandidato *ptBusca;

    ptBusca = ptLista;

    while ( ptBusca->info.numero != votoNo && ptBusca != NULL ){
        ptBusca = ptBusca->prox;
    }
    if ( ptBusca != NULL ){
        ptBusca->info.votosParcial++;
        ptBusca->info.votosTotal++;
    //Impressão de Teste
    //printf("\n%d - %s - %d != %d\n",
    //       ptBusca->info.numero, ptBusca->info.nome, ptBusca->info.votosParcial, ptBusca->info.votosTotal );
        return ptBusca;
    }
    else return NULL;
}

nodoCandidato* ReordenarFila( nodoCandidato *ptLista, nodoCandidato *ptVotado )
{
    nodoCandidato   *ptAux;

    ptAux = ptVotado;

    while ( ptAux->ant != NULL && ptVotado->info.votosTotal > ptAux->ant->info.votosTotal ){
        ptAux = ptAux->ant;
    }

    ptVotado->ant->prox = ptVotado->prox;
    if ( ptVotado->prox != NULL ) ptVotado->prox->ant = ptVotado->ant;

    ptVotado->prox = ptAux;
    ptVotado->ant = ptAux->ant;
    if ( ptAux->ant != NULL) ptAux->ant->prox = ptVotado;
    ptAux->ant = ptVotado;

    if ( ptVotado->ant == NULL ) ptLista = ptVotado;

    return ptLista;
}

void Timer ( int *t )
{
    t[2]++;

    if ( t[2] == 60 ){
        t[1]++;
        t[2] = 0;
    }
    if ( t[1] == 60 ){
        t[0]++;
        t[1] = 0;
    }
    if ( t[0] == 24 ) *t = 0;
}

nodoCandidato* ApurarVotosUrna ( int numUrnas, nodoCandidato *ptLista, int *time )
{
    nodoCandidato *ptVotado;

    FILE        *fp;
    int         n, votoNo, numLider;
    char        urnas[STR_M];
    char        extensao[STR_PP] = ".txt";
    char        bufferNum[STR_P], stringVoto[STR_P];

    numLider = ptLista->info.numero;

    for ( n = 1; n <= numUrnas; n++ ){
        itoa ( n, bufferNum, DEZ );
        strcpy ( urnas, "urna ");
        strcat( urnas, bufferNum );
        strcat( urnas, extensao );

        printf("\nAbrindo arquivo %s\n", urnas );
        if ( ! ( fp = fopen ( urnas, "r" ) ) ){
            printf("\nNAO FOI POSSIVEL REALIZAR A APURACAO DA %s.\n", urnas );
            printf("TALVEZ O ARQUIVO %s NAO ESTEJA NA PASTA.\n", urnas );
            return NULL;
        }
        else{
            printf("Apurando Votos da %s:\n", urnas );
            BARRA;

            while ( ! feof ( fp ) ){
                if ( fgets ( stringVoto, sizeof( stringVoto ), fp ) == NULL ){
                    BARRA;
                    ArmazenaVotosDaUrna( ptLista, n );
                }
                else{
                    votoNo = atoi( stringVoto );
                    ptVotado = AdicionarVoto( ptLista, votoNo );

                    Timer ( time );
                    if ( ptVotado == NULL ) puts("Voto NULO---...");
                        if ( ptVotado->ant != NULL && ptVotado->info.votosTotal > ptVotado->ant->info.votosTotal ){
                            // puts("Tem que reordenar...");  //Impressão de Teste
                            ptLista = ReordenarFila( ptLista, ptVotado );
                            if ( numLider != ptLista->info.numero ){
                                numLider = ptLista->info.numero;
                        //Imprime Boletim de Atualização
                                printf("\n%2d:%2d:%2d - %d - %30s - %d Votos - Lidera\n",
                                       time[0], time[1], time[2], ptLista->info.numero, ptLista->info.nome, ptLista->info.votosTotal );
                            }
                        }
                }
            }
        }
        fclose( fp );
    }
    return ptLista;
}

void ImprimeVotosPorUrna ( nodoCandidato *ptLista )
{
    nodoCandidato   *auxLista;
    nodoUrna        *auxUrna;

    auxLista = ptLista;

    while ( auxLista != NULL ){
        auxUrna = auxLista->ptUrna;
        printf("\n%d - %s\n", auxLista->info.numero, auxLista->info.nome );
        if ( auxUrna == NULL ) printf ("%s - Nao recebeu votos\n", auxLista->info.nome );
        else{
            while ( auxUrna != NULL ){
                printf("Urna %3d - %5d Votos\n",
                       auxUrna->dadosDaUrna.id, auxUrna->dadosDaUrna.votosDaUrna );
                auxUrna = auxUrna->proximaUrna;
            }
        }
        auxLista = auxLista->prox;
        puts("");
        Sleep ( SLEEP );
    }
}


void ImpugnarUrna ( nodoCandidato *ptLista, int numUrna )
{
    nodoCandidato   *auxLista;
    nodoUrna        *anterior, *auxUrna;

    auxLista = ptLista;

    while ( auxLista != NULL ){
        auxUrna = auxLista->ptUrna;
        anterior = NULL;
        while (  auxUrna != NULL ){
            if ( auxUrna->dadosDaUrna.id == numUrna ){
                //decrementa os votos do total de votos
                auxLista->info.votosTotal = auxLista->info.votosTotal - auxUrna->dadosDaUrna.votosDaUrna;

                if ( anterior == NULL ) auxLista->ptUrna = auxUrna->proximaUrna; //new
                else anterior->proximaUrna = auxUrna->proximaUrna;
                free( auxUrna );
            }
            anterior = auxUrna;
            auxUrna = auxUrna->proximaUrna;
        }
        auxLista = auxLista->prox;
    }
}


nodoCandidato* Ultimo ( nodoCandidato *ptLista )
{
    nodoCandidato *ultimo;

    ultimo = ptLista;
    while ( ultimo->prox != NULL ){
        ultimo = ultimo->prox;
    }//printf("\n%d - %s - %d\n", ultimo->info.numero, ultimo->info.nome, ultimo->info.votosTotal ); //Impressão de Teste

    return ultimo;
}

int VerificaOrdem( nodoCandidato *ptLista )
{
    int             ordem;
    nodoCandidato   *ultimo;

    ultimo = Ultimo( ptLista );

    ordem = 1;
    while ( ordem == 1 && ultimo->ant != NULL ){
        if ( ultimo->info.votosTotal > ultimo->ant->info.votosTotal ) ordem = 0;
        ultimo = ultimo->ant;
    }
    //printf("\n%d - %s - %d\n", ultimo->info.numero, ultimo->info.nome, ultimo->info.votosTotal ); //Impressao de teste

    if ( ordem == 1 ) return 1;
    else return 0;

}

nodoCandidato* TrazPraFrente ( nodoCandidato *ptLista, int* avanca ) //Subfunção de ReReordena
{
    nodoCandidato   *ultimo, *walker;
    int             i, troca;

    ultimo = Ultimo( ptLista );
    //printf("\n%d - %s -%d\n", ultimo->info.numero, ultimo->info.nome, ultimo->info.votosTotal );

    for ( i = 1; i <= *avanca; i++ ){
        ultimo = ultimo->ant;
    }

    walker = ultimo;
    troca = 0;
    while ( walker->ant != NULL && ultimo->info.votosTotal > walker->ant->info.votosTotal ){
            walker = walker->ant;
            troca = 1;
    }
    if ( troca == 1 ){
    //reapontamento
        ultimo->ant->prox = ultimo->prox;

        if ( ultimo->prox != NULL ) ultimo->prox->ant = ultimo->ant;

        ultimo->prox = walker;

        if ( walker->ant != NULL) walker->ant->prox = ultimo;
        ultimo->ant = walker->ant;
        walker->ant = ultimo;
        if ( ultimo->ant == NULL ) ptLista = ultimo;
    }
    *avanca = *avanca + 1;

    return ptLista;
}

nodoCandidato* TrazPraTras ( nodoCandidato *ptLista, int *recua ) //Subfunção de ReReordena
{
    nodoCandidato   *primeiro, *walker;
    int             i, troca;

    primeiro = ptLista;

    for ( i = 1; i <= *recua; i++ ){
        primeiro = primeiro->prox;
    }

    walker = primeiro;
    troca = 0;
    while ( walker->prox != NULL && primeiro->info.votosTotal < walker->prox->info.votosTotal ){
            walker = walker->prox;
            troca = 1;
    }
    if ( troca == 1 ){
        primeiro->prox->ant = primeiro->ant;

        if ( primeiro->ant != NULL ) primeiro->ant->prox = primeiro->prox;

        primeiro->prox = walker->prox;
        primeiro->ant = walker;

        if ( walker->prox != NULL) walker->prox->ant = primeiro;

        walker->prox = primeiro;
    }
    *recua = *recua + 1;
    return ptLista;
}

nodoCandidato* ReReordena ( nodoCandidato *ptLista ) //Ordena a Lista após a Impugnação
{
    int avanca, recua;

    avanca = 0;
    recua = 0;

    while ( ! VerificaOrdem( ptLista ) ){
        ptLista = TrazPraFrente( ptLista, &avanca );
        ptLista = TrazPraTras( ptLista, &recua );

    }

    return ptLista;
}

nodoCandidato* DestruirLista ( nodoCandidato* ptLista )
{
   nodoCandidato *ptAux;

   while (ptLista != NULL){
         ptAux = ptLista;
         ptLista = ptLista->prox;
         free( ptAux );
   }
   free( ptLista );
   return NULL;
}

SAV1()
{
    nodoCandidato       *ptLista;

    int                 numUrnas, numEleitos, urnaImpug;
    char                cidade[STR_GG];
    char                arquivo[STR_GG] = "candidatos"; //++++++++++++++++++++++++
    char                extensao[STR_PP] = ".txt";
    int                 time[3] = {18,0,0};

    printf("Nome da Cidade: "); gets( cidade );

    //printf("\nNome do Arquivo com a Lista de Candidatos(sem a extensao): "); gets( arquivo );
    //tolower( arquivo );

    strcat ( arquivo, extensao );

    do{
        printf("\nNumero de Urnas: "); scanf(" %d", &numUrnas );
        if ( numUrnas <= 0 ){
            ERRONUM;
            getche();
            clrscr();
        }
    } while ( numUrnas <= 0 );

    do{
        printf("\nNumero de vereadores a serem eleitos em %s: ", cidade ); scanf(" %d", &numEleitos );
        if ( numEleitos <= 0 ){
            ERRONUM;
            getche();
            clrscr();
        }
    } while ( numEleitos  <= 0 );

    printf("\nAbrindo Arquivo %s\n", arquivo );

    ptLista = CriaListaCandidatos( );
    ptLista = AbreCandidatos( arquivo, ptLista );

    if ( ptLista == NULL ){
        printf("\nTALVEZ O ARQUIVO %s NAO ESTEJA NA PASTA\n", arquivo );
        REINICIE;
    }

    else{
        printf("\n%2d:%2d:%2d ---Inicio da Apuracao---\n",
           time[0], time[1], time[2] );

        ptLista = CadeiaDupla ( ptLista );
        InicializaUrnas( ptLista );

        ptLista = ApurarVotosUrna ( numUrnas, ptLista, time );
        if ( ptLista != NULL ){
            SUCESSO;
            textcolor ( YELLOW );
            printf("\n%2d:%2d:%2d ------------- RESULTADO DA APURACAO -------------\n", time[0], time[1], time[2] );
            textcolor ( LIGHTGRAY );
            ImprimeLista( ptLista );

            textcolor ( LIGHTRED );
            printf("\nCANDIDATOS ELEITOS:\n");
            textcolor ( LIGHTGRAY );
            ImprimirEleitos( ptLista, numEleitos );



            printf("\nImpugnar Urna: ");
            scanf(" %d", &urnaImpug );

            ImpugnarUrna ( ptLista, urnaImpug );
            printf("--- %d ---\n", VerificaOrdem( ptLista )); //Impressao de Teste

            //ptLista = ReReordena( ptLista ); //ERRO AQUI
            //ImprimeVotosPorUrna ( ptLista );
            ImprimirEleitos( ptLista, numEleitos );
        }
        else{
            REINICIE;
        }
    }
    ptLista = DestruirLista ( ptLista );
    free( ptLista );
}


//EM CONSTRUÇÃO +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
void EliminaCadeiaDupla ( nodoCandidato *ptLista )
{
    nodoCandidato *ptAux, *AntAux;

    ptAux = ptLista;
    while ( ptAux->prox != NULL ){
        ptAux = ptAux->prox;
        ptAux->ant = NULL;
    }
}

nodoCandidato* SelecionaPivo( nodoCandidato *ptLista, int n )
{
    int             i, posPivo;
    nodoCandidato   *Pivo;

    Pivo = ptLista;

    posPivo = n/2;
    for ( i = 1; i <= posPivo; i++ ){
        Pivo = Pivo->prox;
    }
    return Pivo;
}

nodoCandidato* QuickSort( nodoCandidato *ptLista, nodoCandidato *Pivo )
{
    nodoCandidato   *Aux = ptLista;
    nodoCandidato   *antAux = NULL;
    nodoCandidato   *ProximoNodo;
    int             trocou = 0;

    //PARTICAO 1 -> Menores que o Pivo
    while ( Aux != Pivo ){
        if ( Aux->info.votosTotal < Pivo->info.votosTotal ){
            trocou = 1;
            //quebra ligação e faz nova ligação
            if ( Aux == ptLista ){
                ptLista = Aux->prox;
                Aux->prox = Pivo->prox;
                Pivo->prox = Aux;
            }
            else{
                antAux->prox = Aux->prox;
                Aux->prox = Pivo->prox;
                Pivo->prox = Aux;
            }
        }
        if ( trocou == 0 ){
            antAux = Aux;
            Aux = Aux->prox;
        }
        else{
            ProximoNodo
            return QuickSort( );
        }
    }
}
*/
//EM CONSTRUÇÃO +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
