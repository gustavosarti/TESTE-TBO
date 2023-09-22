#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Leitura.h"
#include <math.h>
#include "MST.h"

// Função para comparar duas arestas pelo peso
int compararArestas(const void* a, const void* b) {
    Aresta* arestaA = (Aresta*)a;
    Aresta* arestaB = (Aresta*)b;
    if (arestaA->peso < arestaB->peso) {
        return -1;
    } else if (arestaA->peso > arestaB->peso) {
        return 1;
    } else {
        return 0;
    }
}

// Função para encontrar o pai de um vértice na floresta
int encontrarPai(int* pais, int vertice) {
    if (pais[vertice] == vertice) {
        return vertice;
    } else {
        return encontrarPai(pais, pais[vertice]);
    }
}

// Função para unir duas árvores em uma única árvore
void unirArvores(int* pais, int verticeA, int verticeB) {
    int paiA = encontrarPai(pais, verticeA);
    int paiB = encontrarPai(pais, verticeB);
    pais[paiA] = paiB;
}

// Função para criar a MST utilizando o algoritmo de Kruskal
Aresta* criarMST(Coordenada* coordenadas, int numCoordenadas, int* numArestasMST) {
    // Criando a lista de arestas
    int numArestas = numCoordenadas * (numCoordenadas - 1) / 2;
    Aresta* arestas = (Aresta*)malloc(numArestas * sizeof(Aresta));
    if (arestas == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    int count = 0;
    for (int i = 0; i < numCoordenadas; i++) {
        for (int j = i + 1; j < numCoordenadas; j++) {
            double distancia = sqrt(pow(coordenadas[i].x - coordenadas[j].x, 2) + pow(coordenadas[i].y - coordenadas[j].y, 2));
            Aresta aresta = {i, j, distancia};
            arestas[count] = aresta;
            count++;
        }
    }

    // Ordenando a lista de arestas por peso
    qsort(arestas, numArestas, sizeof(Aresta), compararArestas);

    // Inicializando a floresta
    int* pais = (int*)malloc(numCoordenadas * sizeof(int));
    if (pais == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    for (int i = 0; i < numCoordenadas; i++) {
        pais[i] = i;
    }


    // Criando a MST
    Aresta* mst = (Aresta*)malloc((numCoordenadas - 1) * sizeof(Aresta));
    if (mst == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    count = 0;
    for (int i = 0; i < numArestas; i++) {
        int origem = arestas[i].origem;
        int destino = arestas[i].destino;
        if (encontrarPai(pais, origem) != encontrarPai(pais, destino)) {
            mst[count] = arestas[i];
            count++;
            unirArvores(pais, origem, destino);
        }
        if (count == numCoordenadas - 1) {
            break;
        }
    }

    // Liberando a memória alocada
    free(arestas);
    free(pais);

    // Atualizando o número de arestas na MST
    *numArestasMST = count;

    return mst;
}

void escreverMST(char* nomeArquivo, Aresta* mst, int numArestas) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    fprintf(arquivo, "NAME: %s\n", nomeArquivo);
    fprintf(arquivo, "TYPE: MST\n");
    fprintf(arquivo, "DIMENSION: %d\n", numArestas + 1);
    fprintf(arquivo, "MST_SECTION\n");
    for (int i = 0; i < numArestas; i++) {
        fprintf(arquivo, "%d %d\n", mst[i].origem + 1, mst[i].destino + 1);
    }
    fprintf(arquivo, "EOF\n");
    fclose(arquivo);
}
