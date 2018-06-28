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

char binario[DESLOC];
const char* imprime_binario(int valor, int tam){
    int i, j = 0;
    char temp[DESLOC];
    itoa(valor, temp, 2);

    for(i=0; i < tam; i++) {
            binario[i] = '0';
    }
    for(i = tam-strlen(temp); i < tam; i++) {
        binario[i] = temp[j];
        j++;
    }
    return binario;
}

void inicia_vetores(Endereco vetor[], int size){
    int i;

    vetor[0].end_inicial = 0;
    vetor[0].end_final = ADD_SIZE - 1;
    vetor[0].mapeamento = -1;

    for(i = 1; i < size; i++){
        vetor[i].end_inicial = vetor[i-1].end_final + 1;
        vetor[i].end_final = vetor[i].end_inicial + ADD_SIZE - 1;
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
    printf("PAGINAS      ||     MOLDURAS\n");
    printf("----------------------------\n");
    for(i = 0; i < PAGES; i++) {
        //printf("%9s  -   %8s", imprime_binario(pagina[i].mapeamento, PAGE_SIZE), imprime_binario(moldura[i].mapeamento, FRAME_SIZE));
        if(i<FRAMES)
            printf("[%3d] %5d  ||  %5d [%3d]\n", i, pagina[i].mapeamento, moldura[i].mapeamento, i);
        else
            printf("[%3d] %5d  ||  \n", i, pagina[i].mapeamento);
    }
}



int main(){
    
    int i = 0;

    srand(time(NULL));

    /*inicia_vetores(paginas, PAGES);
    imprime_vetores(paginas, PAGES, PAGE_SIZE);*/
    inicia_vetores(pagina, PAGES);
    inicia_vetores(moldura, FRAMES);
    //imprime_vetores(molduras, FRAMES, FRAME_SIZE);
    criar_tabela_paginas();
    exibir_tabela_paginas();

  //  printf("%s", imprime_binario(10, FRAME_SIZE));

  // imprime_binario(3, PAGE_SIZE);
    /*printf(" ");
    imprime_binario(808, DESLOC);
    
    printf("\n");
    imprime_binario(0, FRAME_SIZE);
    printf(" ");
    imprime_binario(808, DESLOC);*/
    
    return 0;
}