#ifndef MAIN_H
#define MAIN_H

#include "safeitoa.h"

typedef struct endereco{
	int end_inicial;
	int end_final;
	int mapeamento;
    int index;
} Endereco ;

const char* imprime_binario(int valor, int tam);

void inicia_vetores(Endereco vetor[], int size);

void imprime_vetores(Endereco vetor[], int size, int bin_size);

void criar_tabela_paginas();

void exibir_tabela_paginas();

void gera_enderecos(int qtd);

void busca_endereco(int end);

void exibir_tupla(int, int, int);

#endif