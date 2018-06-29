#ifndef MAIN_H
#define MAIN_H

#include "safeitoa.h"

typedef struct endereco{
	int end_inicial;
	int end_final;
	int mapeamento;
    int index;
} Endereco ;

typedef struct ratio {
    double hit;
    double miss;
} Ratio;

const char* imprime_binario(int valor, int tam);

void inicia_vetores(Endereco vetor[], int size);

void imprime_vetores(Endereco vetor[], int size, int bin_size);

void criar_tabela_paginas();

void exibir_tabela_paginas();

void gera_enderecos(int qtd);

void busca_endereco(int end);

int exibir_tupla(int, int, int);

Ratio calcula_ratio(int qtd, int hits);

void init();

#endif