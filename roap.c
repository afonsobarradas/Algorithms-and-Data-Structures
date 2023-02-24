/****************************************
 Projeto AED 2021-2022
 Realizado por:
 Afonso Barradas 96141
 Gonçalo Simão 96215
 Grupo 047
 ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
int main (int argc, char *argv[])
{
    int aux=0, inter=-1, check=0;
    char *ficheiro= NULL, *write;
    if (argc != 2) {inter=0;}else{inter=1;}    /*inter= 0- intermedio
                                                inter = 1- final */
    if (inter==1)
    {
        ficheiro=argv[1]; /* fase final- ficheiro no segundo argumento do comando do terminal (sem a flag -s) */
    } 
    else 
    { 
        ficheiro=argv[2];
    }
    FILE *fpin,*fpout;
    write= saida0(ficheiro, inter);
    
    fpin= fopen(ficheiro, "r");
    fpout= fopen(write, "w");

    while(1)
    {
    if(check==-1) check=0;
    aux= readFile(fpin, inter);
    if (aux==-1){
		break;
	}
    if (inter==1)  /* final */
    {
        if(prob2->Lx<=0 || prob2->Lx>tab->L || prob2->Cx<=0 || prob2->Cx>tab->C){ /* ponto de chegada não pertencente ao tabuleiro */
            fprintf(fpout, "-1\n\n"); freeG(); free(prob2); check=-1;
        } 
        if (check!=-1)
        { 
            if (tab->adj[prob2->Lx-1][prob2->Cx-1]!= 0){    /* ponto de chegada não é casa branca */
                fprintf(fpout, "-1\n\n");
                freeG(); free(prob2);
            }
            else {
                dijkstra(1, prob2->Lx, prob2->Cx, fpout, 1, prob2->paredeB);
                freeG();
                free(prob2);
            }
        }
    }
    else  /* intermedio */
    {
    if (strcmp(prob->modo, "A1") ==0)
    {
        modoA1(prob->Lt, prob->Ct, write, fpout);
        freeG();
        free(prob);
    }
    else if (strcmp(prob->modo, "A2") ==0)
    {
        whiteNei(prob->Lt, prob->Ct, fpout, 0);
        freeG();
        free(prob);
    }
    else if (strcmp(prob->modo, "A3") ==0) 
    {
        greyNei(prob->Lt, prob->Ct, fpout);
        freeG();
        free(prob); 
    }
    else if (strcmp(prob->modo, "A4") ==0)
    {
        whiteNei(prob->Lt, prob->Ct, fpout, -1);
        freeG();
        free(prob);
    }
    else if (strcmp(prob->modo, "A5") ==0)
    {
        modoA5(prob->Lt, prob->Ct, fpout, 0);
        freeG();
        free(prob);
    }
    else if(strcmp(prob->modo,"A6")==0)
    {
       /* if (prob->Lt<=0 || prob->Ct>tab->L || prob->Lt1<=0 || prob->Ct1>tab->L || prob->Ct<=0 || prob->Lt1>tab->L || prob->Lt> tab->L || prob->Ct1<=0)
        {fprintf(fpout, "-2\n\n");
        freeG();
        free(prob);
        break;
        if (dijkstra(prob, prob2->Lx, prob2->Cx) ==0 )
        fprintf(fpout, "1\n\n");
        if (dijkstra(1, prob2->Lx, prob2->Cx)==-1)
        fprintf(fpout, "-1\n\n");
        freeG();
        free(prob);
        
    }*/
    }
    }
    }
fclose(fpin);
fclose(fpout);
free(write);
if (aux==-1){free(tab);}
return 0;
}
