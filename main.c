#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGES 512
#define FRAMES 256
#define SIZE 8
#define DESLOC 13
#define PAGE_SIZE 9
#define FRAME_SIZE 8

typedef struct endereco {
    int numero;
    int deslocamento;
    char tipo;
} Endereco ;

char deslocamento_binario[DESLOC];
char numero_page[PAGE_SIZE];
char numero_frame[FRAME_SIZE];

void imprime_binario(int valor, int tam){
    char binario[tam];
    int i;
    itoa(valor, binario, 2);
    for(i=0; i < tam-strlen(binario); i++) {
            printf("0");
    }
    printf("%s", binario);
}

int main(){
    
    imprime_binario(1, PAGE_SIZE);
    printf(" ");
    imprime_binario(808, DESLOC);
    
    printf("\n");
    imprime_binario(0, FRAME_SIZE);
    printf(" ");
    imprime_binario(808, DESLOC);
    
    return 0;
}