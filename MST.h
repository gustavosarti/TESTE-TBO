#ifndef MST_H
#define MST_H

#include "Leitura.h"

typedef struct {
    int origem;
    int destino;
    double peso;
} Aresta;

int compararArestas(const void* a, const void* b);
int encontrarPai(int* pais, int vertice);
void unirArvores(int* pais, int verticeA, int verticeB);
Aresta* criarMST(Coordenada* coordenadas, int numCoordenadas, int* numArestasMST);
void escreverMST(char* nomeArquivo, Aresta* mst, int numArestas);
#endif