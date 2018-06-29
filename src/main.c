#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "../includes/main.h"
#include "../includes/safeitoa.h"

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
    //itoa(valor, temp, 2);
    safeitoa(valor, temp, tam, 2);

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
        printf("{ [%8s], ( [%8d] - [%8d] ) }\n", imprime_binario(i, bin_size), vetor[i].end_inicial, vetor[i].end_final);
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
        r = rand()%PAGES - 1;

        while(repete(r))
            r = rand()%PAGES - 1;
        
        moldura[i].mapeamento = r;
        pagina[r].mapeamento = i;
    }
}

void exibir_tabela_paginas(){
    int i = 0;
    printf("|\n|-------------------------------------|--|------------------------------------|\n");
    printf("|  PAGINAS%28s|/\\|%26sMOLDURAS  |\n", " ", " ");
    printf("|  [Indice(P)] {Intervalo} Indice(M)  |\\/| Indice(P) {Intervalo} [Indice(M)]  |\n");
    printf("|-------------------------------------|--|------------------------------------|\n");
    for(i = 0; i < PAGES; i++) {
        printf("|  [%3d] { %7d - %7d } %4d   ", i, pagina[i].end_inicial, pagina[i].end_final, pagina[i].mapeamento);
        if(i<FRAMES){
            printf("|/\\|  %4d { %7d - %7d } [%3d]  |\n", moldura[i].mapeamento, moldura[i].end_inicial, moldura[i].end_final, i);
        } else {
            printf("|\\/|  %34s|\n", " ");
        }
    }
    printf("|-------------------------------------|--|------------------------------------|\n");
    printf("|  [Indice(P)] {Intervalo} Indice(M)  |/\\| Indice(P) {Intervalo} [Indice(M)]  |\n");
    printf("|  PAGINAS%28s|\\/|%26sMOLDURAS  |\n", " ", " ");
    printf("|-------------------------------------|--|------------------------------------|\n");
}

/*como saída, fornecerá a localização na tabela de páginas na forma nr. da página/deslocamento em decimal e binário e o respectivo endereço físico (ER) na forma nr.da moldura/deslocamento em decimal e binário, quando houver. Caso contrário, informar que houve PF.*/
void exibir_tupla(int indice, int offset, int end){
    printf("|\n|\n|  Endereço:  %13d  ", end);
    printf("\n|-------------------------------------|--|------------------------------------|\n");
    printf("|         Indice    Deslocamento      |  |    Indice     Deslocamento         |\n");
    printf("|  EV : ");
    printf("%6d   %10d           |/\\|", indice, offset);
    printf("   %9s   ", imprime_binario(indice, PAGE_SIZE)); 
    printf("%13s%8s|\n", imprime_binario(offset, DESLOC), "");
    
    printf("|  ER : ");

    if(pagina[indice].mapeamento > FRAMES || pagina[indice].mapeamento < 0){
        printf("   PAGE FAULT [%2d]%12s|\\/|%36s|", pagina[indice].mapeamento, "", "");
    } else {     
        printf("%6d   %10d           |\\/|", pagina[indice].mapeamento, offset);
        printf("   %9s   ", imprime_binario(pagina[indice].mapeamento, FRAME_SIZE)); 
        printf("%13s%8s|", imprime_binario(offset, DESLOC), "");
    }
   printf("\n|-------------------------------------|--|------------------------------------|\n");
}

void gera_enderecos(int qtd){
    int r, i, j;
    for(i = 0; i < qtd; i++){

        r = rand()%ADD_SIZE*PAGES;
        
        busca_endereco(r);
    }
}

void busca_endereco(int end){
    int j;
    
    //printf("\n|  Tipo Indice Deslocamento  |  | %8sIndice    Deslocamento", " " );
    for(j = 0; j < PAGES; j++){
            if(pagina[j].end_inicial <= end && pagina[j].end_final >= end){
                exibir_tupla(j, end - pagina[j].end_inicial, end);
            }
        }
}

int menu(){
    int var1, var2;
    printf("|-----------------------------------------------------------------------------|\n");
	printf("|  1 - Exibir tabela de páginas %46s|\n", "");
	printf("|  2 - Gerar endereços aleatórios e  buscar na tabela %24s|\n", "");
	printf("|  3 - Buscar endereço  %54s|\n", "");
    printf("|  4 - Nova Tabela de páginas %48s|\n", "");
	printf("|  0 - Sair %66s|\n", "");
    printf("|-----------------------------------------------------------------------------|\n");
	printf("|\n > ");
    scanf("%d", &var1);

    
    switch (var1){
        case 1: 
            exibir_tabela_paginas(); 
            break;
        case 2: 
            printf("|\n|  Quantidade de endereços:\n|\n > ");
            scanf("%d", &var2);
            printf("|\n");
            gera_enderecos(var2);
            break;
        case 3: 
            printf("|\n|  Endereço a ser buscado: \n|\n > ");
            scanf("%d", &var2);
            printf("|\n");
            if(var2 >= ADD_SIZE*PAGES){
                printf("|  Endereço indisponível\n|\n"); break;
            } else if(var2 < 0){
                printf("|  Endereço inválido\n|\n"); break;
            }
            busca_endereco(var2);
            break;
        case 4:
            printf("|\n|  Criando nova tabela de páginas...\n|\n");
            inicia_vetores(pagina, PAGES);
            inicia_vetores(moldura, FRAMES);
            criar_tabela_paginas();
            break;
        case 0: return 0;
        default: printf("|\n|  Inválido\n|\n"); break;
    }
    return var1;
}


int main(){
    setlocale(LC_ALL, "Portuguese");

    srand(time(NULL));

    inicia_vetores(pagina, PAGES);
    inicia_vetores(moldura, FRAMES);
    criar_tabela_paginas();
    /*
    exibir_tabela_paginas();
    printf("\n");
    busca_tabela(qtd_enderecos);

    printf("%s\n", imprime_binario(1, FRAME_SIZE));
    printf("%s\n", imprime_binario(1, PAGE_SIZE));*/
    while(menu());
    
    return 0;
}