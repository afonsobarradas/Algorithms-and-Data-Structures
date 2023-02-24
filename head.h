#ifndef HEAD_H
#define HEAD_H

typedef struct Grafo {
    int L;   /* número de linhas do tabuleiro */
    int C;   /* número de colunas do tabuleiro */
    int **adj; /* duplo apontador para a matriz de inteiros usada para colocar informação do tabuleiro */
}grafo;

typedef struct Partida {  /* estrutura apenas usada na fase intermédia */
    int Lt;   
    int Ct;
    int Lt1;   
    int Ct1;
    char modo[3];    /*vetor de char com a indicação do modo a resolver */
}partida;

typedef struct Partida2 {   /* estrutura usada apenas na fase final */
    int Lx;                 /* coordenadas do ponto de chegada pretendido */
    int Cx;
    int count;              /* contador do número de paredes brancas partidas no caminho para a chegada */
    int paredeB;            /* número de paredes cinzentas */
}partida2;

grafo *tab;
partida *prob;
partida2 *prob2;
int greyNei(int Linha, int Coluna, FILE *fp);
int whiteNei(int Linha, int Coluna, FILE *fp, int a);
int readFile (FILE *fp, int inter);
int checkR(int Linha, int Coluna);
int checkL(int Linha, int Coluna);
int checkUp(int Linha, int Coluna);
int checkD(int Linha, int Coluna);
int modoA5(int Linha, int Coluna, FILE *fp, int inter);
void freeG();
int dijkstra(int partida , int chegada1, int chegada2, FILE *fp, int inter, int paredeB);
int modoA1(int Linha, int Coluna, char* ficheiro, FILE *fp);
char* saida0(char *ficheiro, int inter);
void caminho(int antecessor[], int chegada, int parede[], int i);
void printCaminho(int parede[], FILE *fp);

#endif