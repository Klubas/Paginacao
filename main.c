#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "main.h"

#define PAGES 512       //4MB
#define FRAMES 256      //2MB

#define ADD_SIZE 8192       //bytes

#define DESLOC 13       //bits
#define PAGE_SIZE 9     //bits
#define FRAME_SIZE 8    //bits

Endereco pagina[PAGES];
Endereco moldura[FRAMES];

char d[DESLOC+1];
const char* imprime_binario(int valor, int tam){
    int i, j = 0;
    char temp[tam];
    itoa(valor, temp, 2);

    for(i=0; i < tam; i++) d[i] = '0';

    for(i = tam-strlen(temp); i < tam; i++) 
    {
        d[i] = temp[j]; j++;
    }

    d[i] = '\0';
    return d;
}

void inicia_vetores(Endereco vetor[], int size){
    int i;

    vetor[0].end_inicial = 0;
    vetor[0].end_final = ADD_SIZE - 1;
    vetor[0].mapeamento = -1;
    vetor[0].index = 0;

    for(i = 1; i < size; i++){
        vetor[i].end_inicial = vetor[i-1].end_final + 1;
        vetor[i].end_final = vetor[i].end_inicial + ADD_SIZE - 1;
        vetor[i].index = i;
        vetor[i].mapeamento = -1;
    }
}

void imprime_vetores(Endereco vetor[], int size, int bin_size){
    int i;
    printf("{ [Endereco], ( [ Inicio ] - [  Final ] ) }\n");
    for(i=0; i<size;i++){
        printf("{ [%8s], ( [%8d] - [%8d] ) }\n", imprime_binario(i, bin_size), vetor[i].end_inicial, vetor[i].end_final, DESLOC);
    }
}

int repete(int valor){
    int i = 0;
    for(i = 0; i < FRAMES; i++){
        if(valor == moldura[i].mapeamento) 
            return 1;
    }
    return 0;
}

void criar_tabela_paginas(){
    int i, r;
    for(i = 0; i < FRAMES; i++){
        r = rand()%PAGES;

        while(repete(r))
            r = rand()%PAGES;
        
        moldura[i].mapeamento = r;
        pagina[r].mapeamento = i;
    }
}

void exibir_tabela_paginas(){
    int i = 0;
    printf("\nPAGINAS%27s||%27sMOLDURAS\n\n", " ", " ");
    for(i = 0; i < PAGES; i++) {
        printf("[%3d] { %7d - %7d } %3d   ||  ", i, pagina[i].end_inicial, pagina[i].end_final, pagina[i].mapeamento);
        if(i<FRAMES){
            printf("%5d { %7d - %7d } [%3d]", moldura[i].mapeamento, moldura[i].end_inicial, moldura[i].end_final, i);
        }
        printf("\n");
    }
}

/*como saída, fornecerá a localização na tabela de páginas na forma nr. da página/deslocamento em decimal e binário e o respectivo endereço físico (ER) na forma nr.da moldura/deslocamento em decimal e binário, quando houver. Caso contrário, informar que houve PF.*/
void exibir_tupla(int indice, int offset){
    printf("EV : ");
    printf("%3d - %4d\t:\t", indice, offset);
    printf("%9s %13s\n", imprime_binario(indice, PAGE_SIZE), imprime_binario(offset, DESLOC));
    
    printf("ER : ");

    if(pagina[indice].mapeamento == -1){
        printf("PAGE FAULT [-1]");
    } else {     
        printf("%3d - %4d\t:\t", pagina[indice].mapeamento, offset);
        printf("%9s %13s", imprime_binario(pagina[indice].mapeamento, FRAME_SIZE), imprime_binario(offset, DESLOC));
    }
    printf("\n\n");
}

void busca_tabela(int qtd){
    int r, i, j;
    for(i = 0; i < qtd; i++){
        r = rand()%4194303;
        for(j = 0; j < PAGES; j++){
            if(pagina[j].end_inicial < r && pagina[j].end_final > r){
                exibir_tupla(j, r - pagina[j].end_inicial);
            }
        }
    }
}

int menu(){
    int op;
    printf("|\n");
	printf("|  1 - Exibir tabela de páginas \t\n");
	printf("|  2 - Gerar endereços aleatórios \t\n");
	printf("|  3 - Buscar endereço\t\n");
	printf("|  0 - Sair           \t\n");
	printf("|\n > ");
    scanf("%d", &op);
}


int main(){
    
    int i = 0;
    int qtd_enderecos = 10;

    srand(time(NULL));

    inicia_vetores(pagina, PAGES);
    inicia_vetores(moldura, FRAMES);

    criar_tabela_paginas();
    exibir_tabela_paginas();
    printf("\n");
    busca_tabela(qtd_enderecos);

    printf("%s\n", imprime_binario(1, FRAME_SIZE));
    printf("%s\n", imprime_binario(1, PAGE_SIZE));
    printf("%s", imprime_binario(808, DESLOC));
    
    return 0;
}