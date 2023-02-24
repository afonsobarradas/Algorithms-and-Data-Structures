#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "float.h"
#include "head.h"
#include <stdbool.h>

/***********************************************************************************
Função readFile:
Descrição: Percorrer o ficheiro de entrada, colocando a informação correspondente
em variáveis úteis. Aloca informação do tabuleiro numa matriz LxC

Argumento de entrada: Apontador para ficheiro (de entrada), inteiro com indicação 
do modo em que estamos a realizar atualmente

Retorno: -1 caso não haja informação suficiente a um tabuleiro completo
          0 caso contrário  
*************************************************************************************/
int readFile(FILE *fp, int inter)
{
    int a1, a2= 0, i, j, peso =0;
    tab = (grafo*)malloc(sizeof(grafo));
    if(tab==NULL) exit(0);
    int nao_brancas=0;
    if (fscanf(fp, "%d %d", &tab->L, &tab->C) != 2 ) return -1;
    if (inter==0)
    {
    prob = (partida*)malloc(sizeof(partida));
    if (fscanf(fp, "%d %d %s", &prob->Lt, &prob->Ct, prob->modo ) != 3 ) return -1;
    if (prob->modo[1]== '6')
        if (fscanf(fp, "%d %d", &prob->Lt1, &prob->Ct1) != 2) return -1;
    }
    else 
    {
        prob2 = (partida2*)malloc(sizeof(partida2));
        if (prob2== NULL) exit(0);
        prob2->paredeB=0;
        if (fscanf(fp, "%d %d", &prob2->Lx, &prob2->Cx) != 2) return -1;
    }
    if (fscanf(fp, "%d", &nao_brancas)!= 1) return -1;

    /* matriz L*C */
    tab->adj = (int**) malloc((tab->L)*sizeof(int*));

    if(tab->adj == NULL){
        exit(0);
    }

    for(i=0; i <tab->L ; i++){
        tab->adj[i]= (int*) malloc (tab->C * sizeof(int));

        if(tab->adj[i] == NULL){
            exit(0);
        }
    }

    for(i=0; i <tab->L ; i++){
            for(j=0; j <tab->C ; j++){
                tab->adj[i][j]=0;

            }
    }

    for (i=0; i< nao_brancas  ; i++)
    {
       if(fscanf(fp, "%d", &a1)!=1) { exit(0);
       }
       if(fscanf(fp, "%d", &a2)!=1) { exit(0);
       }
       if(fscanf(fp, "%d", &peso)!=1) { exit(0);
       }
          tab->adj[a1-1][a2-1]= peso;
         /* if (peso>0){if (modoA5(a1, a2, fp, 1)) prob2->paredeB++;}*/
    }

return 0;
}

int modoA1(int Linha, int Coluna, char* ficheiro, FILE *fp)
{
    if (Linha> tab->L || Coluna> tab->C || Linha <=0 || Coluna <=0)
    {
        fprintf(fp, "-2\n\n");
        return -1;
    }
    else if (tab->adj[Linha-1][Coluna-1] == 0)   /* 0- branca, 1- cinzenta, 2- preta*/
    {
        fprintf(fp, "0\n\n");
        return 0;
    }
    else 
    {
        fprintf(fp, "%d\n\n", tab->adj[Linha-1][Coluna-1]);
        return 1;
    }
}
int whiteNei(int Linha, int Coluna, FILE *fp, int a)
{
    if (Linha> tab->L || Coluna> tab->C || Linha <=0 || Coluna <=0)
    {
        fprintf(fp, "-2\n\n" );
        return -2;
    }
    if (Linha>1 && Coluna>1 && Linha< tab->L && Coluna< tab->C)  /* meio tabuleiro, check 4 */
    {
        
        if (checkUp(Linha, Coluna) == a /*up*/ || checkD(Linha, Coluna) == a /*left*/|| checkL(Linha, Coluna)== a /*down*/|| checkR(Linha, Coluna) /*right*/==a)
        {
            fprintf(fp, "1\n\n");
            return 1;
        }
    }
    else if (Linha==1 && Coluna ==1 ) /* canto sup esquerdo */
    {
        if (checkR(Linha, Coluna)== a || checkD(Linha, Coluna)==a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == 1 && Coluna == tab->C) /* sup direito*/
    {
        if (checkL(Linha, Coluna)==a || checkD(Linha, Coluna)==a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha ==1 && Coluna != 1 && Coluna != tab->C) /* cima meio */
    {
        if (checkR(Linha, Coluna)==a || checkD(Linha, Coluna)==a || checkL(Linha, Coluna) == a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == tab->L && Coluna == tab->C) /* inf direito */
    {
        if (checkL(Linha, Coluna)==a || checkUp(Linha, Coluna)==a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == tab->L && Coluna == 1) /* inf esq */
    {
        if (checkR(Linha, Coluna)==a || checkUp(Linha, Coluna)==a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Coluna ==1) /* esq meio */
    {
        if (checkR(Linha, Coluna)==a || checkUp(Linha, Coluna)==a || checkD(Linha, Coluna)==a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == tab->L) /* baixo meio */
    {
        if (checkL(Linha, Coluna)==a || checkUp(Linha, Coluna)==a || checkR(Linha, Coluna)==a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }

    else if (Coluna == tab->C) /* direita meio*/
    {
        if (checkL(Linha, Coluna)==a || checkUp(Linha, Coluna)==a || checkD(Linha, Coluna)==a)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    fprintf(fp, "0\n\n");
return 0;
}
int greyNei(int Linha, int Coluna, FILE *fp)
{
    if (Linha> tab->L || Coluna> tab->C || Linha <=0 || Coluna <=0)
    {
        fprintf(fp, "-2\n\n" );
        return -2;
    }
    if (Linha>1 && Coluna>1 && Linha< tab->L && Coluna< tab->C)  /* meio tabuleiro, check 4 */
    {
        
        if (checkUp(Linha, Coluna) > 0  /*up*/ || checkD(Linha, Coluna) > 0 /*left*/|| checkL(Linha, Coluna) >0 /*down*/|| checkR(Linha, Coluna) /*right*/>0)
        {
            fprintf(fp, "1\n\n");
            return 1;
        }
    }
    else if (Linha==1 && Coluna ==1 ) /* canto sup esquerdo */
    {
        if (checkR(Linha, Coluna) > 0 || checkD(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == 1 && Coluna == tab->C) /* sup direito*/
    {
        if (checkL(Linha, Coluna) > 0 || checkD(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha ==1 && Coluna != 1 && Coluna != tab->C) /* cima meio */
    {
        if (checkR(Linha, Coluna) > 0 || checkD(Linha, Coluna) > 0 || checkL(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == tab->L && Coluna == tab->C) /* inf direito */
    {
        if (checkL(Linha, Coluna) > 0 || checkUp(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == tab->L && Coluna == 1) /* inf esq */
    {
        if (checkR(Linha, Coluna) > 0 || checkUp(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Coluna ==1) /* esq meio */
    {
        if (checkR(Linha, Coluna) > 0 || checkUp(Linha, Coluna) > 0 || checkD(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    else if (Linha == tab->L) /* baixo meio */
    {
        if (checkL(Linha, Coluna) > 0 || checkUp(Linha, Coluna) > 0 || checkR(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }

    else if (Coluna == tab->C) /* direita meio*/
    {
        if (checkL(Linha, Coluna) > 0 || checkUp(Linha, Coluna) > 0 || checkD(Linha, Coluna) > 0)
        {fprintf(fp, "1\n\n");
        return 1;}
    }
    fprintf (fp, "0\n\n");
return 0;
}

int modoA5(int Linha, int Coluna, FILE *fp, int inter)
{
    
    if (Linha<1 || Coluna <1 || Linha > tab->L || Coluna > tab->C) /* fora tab */
    {
        if (inter==0)fprintf(fp, "-2\n\n");
        return -2;
    }
    else if (tab->adj[Linha-1][Coluna-1]<=0) /* ñ é cinzenta */
    {
        if (inter==0)fprintf(fp, "-1\n\n");
        return -1;
    }
    /* está nos cantos */
    else if ((Linha ==1 && Coluna ==1) || (Linha== tab->L && Coluna == tab->C) || (Linha == 1 && Coluna == tab->C) || (Coluna ==1 && Linha == tab->L)) 
    {
        if (inter==0) fprintf(fp, "0\n\n");
        return 0;
    }
    /* de acordo com os seus vizinhos, torna impossível passar sem mudar de direção */
    else if ((checkR(Linha, Coluna) != 0 && checkD(Linha, Coluna) != 0) || (checkR(Linha, Coluna)!=0 && checkUp(Linha, Coluna) != 0) || (checkL(Linha, Coluna) != 0 && checkUp(Linha, Coluna) != 0) || (checkL(Linha, Coluna) != 0 && checkD(Linha, Coluna) != 0))
    {
        if (inter==0)fprintf(fp, "0\n\n");
        return 0;
    }
    else 
    {
        if (inter==0)fprintf(fp, "1\n\n");
        return 1;
    }
}
/*************************************************************************
Funções checkR, checkL, checkD e checkUp

Descrição: verificar se tem vizinho à direita de uma determinada casa
Argumentos de entrada: coordenadas da casa cujo vizinho se quer inspecionar
Retorno: -2: caso não tenha o vizinho correspondente à função em vigor
caso tenha, retorna o valor do tabuleiro desse vizinho 
**************************************************************************/

int checkR(int Linha, int Coluna) /* direita */ 
{
    if (Linha>0 && Linha<=tab->L && 0<Coluna && Coluna<tab->C) return tab->adj[Linha-1][Coluna];
    return -2;
}
int checkL(int Linha, int Coluna) /* esquerda */
{
    if (Linha>0 && Linha<=tab->L && 1<Coluna && Coluna<=tab->C) return tab->adj[Linha-1][Coluna-2];
    return -2;
}
int checkD(int Linha, int Coluna) /* baixo */
{  
    if (Linha>0 && Linha<tab->L && 0<Coluna && Coluna<=tab->C) return tab->adj[Linha][Coluna-1];
    return -2;
}
int checkUp(int Linha, int Coluna) /* cima. */
{
    if (Linha>1 && Linha<=tab->L && 0<Coluna && Coluna<=tab->C) return tab->adj[Linha-2][Coluna-1];
    return -2;
}
/***********************************************************
Função freeG:

Sem argumentos de entrada e sem retorno, tem como objetivo libertar 
a memória alocada anteriormente para a matriz, bem como a estrutura
Grafo 
*************************************************************/
void freeG()
{
    int i;
    for (i=0; i<tab->L; i++)
    {
        free(tab->adj[i]);
    }
    free(tab->adj);
    free(tab);
}

/******************************
Função saida0:
Descrição: Recebe o nome do ficheiro de entrada e altera para a extensão requerida no ficheiro de escrita
Argumentos de entrada: apontador para ficheiro de entrada
Retorno: apontador para ficheiro alterado
********************************/
char* saida0(char *ficheiro, int inter) {

    char *write;    
    write = (char *) malloc((strlen(ficheiro) + 1) * sizeof(char));
    strcpy(write, ficheiro);
    if (inter==0)   /* fase intermédia- sol1 */
    { 
        write[strlen(write) - 3] = '\0'; 
        strcat(write, "sol1"); 
        return write; 
    }
    write[strlen(write) - 2] = '\0'; /* fase final- sol */
    strcat(write, "sol");
    return write;
}
/**************************************************************************
Função caminho
Descrição: Percorrer o caminho percorrido até à chegada, inversamente,
através do vetor antecessor, recursivamente, contando as paredes cinzentas e guardando
as mesmas no vetor de inteiros parede, para mais tarde imprimir 

Argumentos de entrada: vetor antecessor, inteiro que indica ponto chegada, 
vetor parede e inteiro i para com a recursividade ir indicando os indexs do vetor parede 
nos quais devemos escrever na próxima iteração

Sem retorno
***************************************************************************/
void caminho (int antecessor[], int chegada, int parede[], int i)
{
    if(chegada!=1)
    {
    int novop=0, ltant, ctant;
    novop= antecessor[chegada-1];
    ltant=((novop)/tab->C)+1; 
    ctant= ((novop)%tab->C);
    if (ctant==0){ ctant= tab->C; ltant= ltant-1;}
    
    if (tab->adj[ltant-1][ctant-1]>0)
    { 
        prob2->count++;
        parede[i]= ltant;
        parede[i+1]= ctant;
        i=i+2;
    }
    caminho(antecessor, novop, parede, i); 
    }  
     else {return;}
}
/********************************************************************************
Função printCaminho

Descrição: Imprimir o inteiro com o número da totalidade paredes cinzentas quebradas
e imprimir o vetor parede obtido anteriormente, bem como o peso de cada parede cinzenta,
presente na respetiva entrada na matriz

Argumentos de entrada: vetor de inteiros parede e apontador para ficheiro de saída

Sem retorno
*********************************************************************************/


void printCaminho(int parede[], FILE *fp)
{
    int i;
    fprintf(fp, "%d\n", prob2->count);
    i=2*prob2->count-1;
    while(i>=0)
    {
        fprintf(fp, "%d %d %d\n", parede[i-1], parede[i], tab->adj[parede[i-1]-1][parede[i]-1]);
        i=i-2;
    }
    fprintf(fp, "\n");
    free(parede);
    return;
}

/********************************************************************
Função minDistance
Descrição: loop ao longo dos vetores de dois vetores da função anterior
para descobrir a próxima casa a visitar no Dijkstra

Argumentos de entrada: vetor inteiros dist e booleano sptSet 

Retorno: indicação da casa que atualmente custa menos visitar
**********************************************************************/

int minDistance(int dist[], bool sptSet[])
{
    int min =__INT_MAX__, min_index=0, MAX, v;
    MAX= tab->L*tab->C;
    for ( v = 0; v < MAX; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}
/**************************************************************
Função dijkstra

Descrição: Implementação do algoritmo Dijkstra para cada casa do tabuleiro

Argumentos de entrada: ponto de partida (sempre 1 neste caso), coordenadas
do ponto de chegada, apontador para ficheiro de saída, inteiro com info da
fase do projeto e número de casas cinzentas do tabuleiro

Retorno: custo mínimo de chegar da casa inicial à chegada
**************************************************************/

int dijkstra(int partida , int chegada1, int chegada2, FILE *fp, int inter, int paredeB)
{
    int i, u , v, MAX, ltant=1, ctant=1, chegada=0, pesotot=-1, w=0, count;
    prob2->paredeB=0;
    /* vértices do Dijkstra= casas do tabuleiro */
    MAX= (tab->L)*(tab->C);     
    /* vetor com custo mínimo atual para chegar ao ponto no seu index */
    int *dist=(int*)malloc(MAX*sizeof(int));
    /* variável booleana para indicar se já foi visitado ou não */
    bool sptSet[MAX];             
    /* vetor no qual se indica o antecessor da casa index */         
    int *antecessor=(int*)malloc(MAX*sizeof(int));   

    /* inicialização */
    for (i = 0; i < MAX; i++)
       { dist[i] =__INT_MAX__, sptSet[i] = false, antecessor[i]=-1;}    
    
    /* ponto 1 sempre visitado por si próprio e com custo 0 */
    dist[0] = 0;
    antecessor[0]=partida;
    /* converter coordenadas da chegada num número indicativo da sua posição no tabuleiro */
    chegada= ((chegada1-1)*tab->C + chegada2); 

    for (count=0; count<MAX; count++) 
    { 
      
        u= minDistance(dist, sptSet);
        u=u+1;

        /* condição de paragem: verificar se próximo vértice desbloqueado corresponde à chegada */

        if (u == chegada) {   
            if (dist[u-1]== __INT_MAX__) {break; }
            pesotot=dist[chegada-1];
            fprintf(fp, "%d\n", pesotot);
            if (pesotot==0){fprintf(fp, "\n"); free(dist);
            free(antecessor); return pesotot;}
            prob2->count=0;
            int *parede=(int*)malloc(prob2->paredeB*sizeof(int));
            caminho(antecessor, chegada, parede, 0);
            printCaminho(parede, fp);
            free(dist);
            free(antecessor);
            return pesotot;
        }
        sptSet[u-1] = true;
        /* converter de número indicativo da posição da matriz para as respetivas coordenadas: ltant e ctant */

        ltant=((u)/tab->C)+1; 
        ctant= ((u)%tab->C);
        if (ctant==0){ ctant= tab->C; ltant= ltant-1;} 
        
        /* Vizinho direita */

        v=u+1; 
        w= v+1; 
        if (checkR(ltant, ctant)!= -2) 
        {   /*gratis*/
            if (!sptSet[v-1] && tab->adj[ltant-1][ctant]==0 && dist[u-1] != __INT_MAX__
                && dist[u-1] + tab->adj[ltant-1][ctant] < dist[v-1]){
                dist[v-1] = dist[u-1] + tab->adj[ltant-1][ctant];
                antecessor[v-1]=u; 
            }
            /* caso tenha parede à direita*/

            if (checkR(ltant, ctant+1)!= -2){ 
                if (tab->adj[ltant-1][ctant]>0){  /*possivel ir alem da parede*/
                    if (!sptSet[w-1] && tab->adj[ltant-1][ctant+1]==0 && dist[u-1] != __INT_MAX__
                        && dist[u-1] + tab->adj[ltant-1][ctant] < dist[w-1])
                    {
                        dist[w-1] = dist[u-1] + tab->adj[ltant-1][ctant];
                        antecessor[w-1]=v; 
                        antecessor[v-1]= u;
                        prob2->paredeB++;
                    }
                }
            }
        }
        v= u+tab->C; /*baixo*/
        w= v+ tab->C;
        if (checkD(ltant, ctant)!= -2)
        {
            if (tab->adj[ltant][ctant-1]== 0)
            {
            if (!sptSet[v-1] &&/* tab->adj[ltant][ctant-1]== 0 &&*/ dist[u-1] != __INT_MAX__
                && dist[u-1] + tab->adj[ltant][ctant-1] < dist[v-1]){
                dist[v-1] = dist[u-1] + tab->adj[ltant][ctant-1];
                antecessor[v-1]=u;
                
            }
            }
            else {
            if (checkD(ltant+1, ctant)!= -2) 
            {
                if (tab->adj[ltant][ctant-1]>0)
                {
                    if (!sptSet[w-1] && tab->adj[ltant+1][ctant-1]==0 && dist[u-1] != __INT_MAX__
                        && dist[u-1] + tab->adj[ltant][ctant-1] < dist[w-1])
                    {    
                        dist[w-1] = dist[u-1] + tab->adj[ltant][ctant-1];
                        antecessor[w-1]=v;
                        antecessor[v-1]=u;
                        prob2->paredeB++;
                    }
                }
            }
            }
        }
        v= u- 1; /*esquerda*/
        w= v-1;
        if (checkL(ltant, ctant)!= -2)
        {
            if (tab->adj[ltant-1][ctant-2]== 0)
            {
                if (!sptSet[v-1] && tab->adj[ltant-1][ctant-2]== 0 && dist[u-1] != __INT_MAX__
                    && dist[u-1] + tab->adj[ltant-1][ctant-2] < dist[v-1]){
                    dist[v-1] = dist[u-1] + tab->adj[ltant-1][ctant-2];
                    antecessor[v-1]=u;
                    }
            }
            else{
            if (checkL(ltant, ctant-1)!= -2){ 
                if (tab->adj[ltant-1][ctant-2]>0){ 
                    if (!sptSet[w-1] && tab->adj[ltant-1][ctant-3]==0 && dist[u-1] != __INT_MAX__
                        && dist[u-1] + tab->adj[ltant-1][ctant-2] < dist[w-1])
                    {
                        dist[w-1] = dist[u-1] + tab->adj[ltant-1][ctant-2];
                        antecessor[w-1]=v;
                        antecessor[v-1]=u; 
                        prob2->paredeB++;
                    }
                }
            }
            }
        }
        
        v= u-tab->C; /*cima*/
        w= v-tab->C;
        if (checkUp(ltant, ctant)!= -2) 
        {
            if (tab->adj[ltant-2][ctant-1]== 0)
            {
                if (!sptSet[v-1] && tab->adj[ltant-2][ctant-1]== 0 && dist[u-1] != __INT_MAX__
                    && dist[u-1] + tab->adj[ltant-2][ctant-1] < dist[v-1]){
                    dist[v-1] = dist[u-1] + tab->adj[ltant-2][ctant-1];
                    antecessor[v-1]=u;
                }
            }
            else{
                if (checkUp(ltant-1, ctant)!= -2){ if (tab->adj[ltant-2][ctant-1]>0){
                    if (!sptSet[w-1] && tab->adj[ltant-3][ctant-1]==0 && dist[u-1] != __INT_MAX__
                        && dist[u-1] + tab->adj[ltant-2][ctant-1] < dist[w-1])
                    {
                        dist[w-1] = dist[u-1] + tab->adj[ltant-2][ctant-1];
                        antecessor[w-1]=v; 
                        antecessor[v-1]=u;
                        prob2->paredeB++;
                    }
                }
                }
            }
    }
    }
    
if(dist[chegada-1]== __INT_MAX__) dist[chegada-1]=-1;
pesotot=dist[chegada-1];
fprintf(fp, "%d\n\n", pesotot);
free(dist);
free(antecessor);
return pesotot;
}
