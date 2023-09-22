#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Leitura.h"
#include "MST.h"

// Função para encontrar o índice da cidade mais próxima
int encontrarCidadeMaisProxima(int cidadeAtual, int* visitadas, double** matrizAdjacencia, int numCoordenadas) {
    int cidadeMaisProxima = -1;
    double distanciaMinima = INFINITY;
    for (int i = 0; i < numCoordenadas; i++) {
        if (!visitadas[i] && matrizAdjacencia[cidadeAtual][i] < distanciaMinima) {
            cidadeMaisProxima = i;
            distanciaMinima = matrizAdjacencia[cidadeAtual][i];
        }
    }
    return cidadeMaisProxima;
}

// Função para encontrar o caminho mais curto utilizando a MST e o algoritmo de vizinhança mais próxima
int* encontrarCaminhoMaisCurto(Coordenada* coordenadas, int numCoordenadas) {
    // Criando a MST
    int numArestasMST;
    Aresta* mst = criarMST(coordenadas, numCoordenadas, &numArestasMST);

    // Criando a matriz de adjacência
    double** matrizAdjacencia = (double**)malloc(numCoordenadas * sizeof(double*));
    if (matrizAdjacencia == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    for (int i = 0; i < numCoordenadas; i++) {
        matrizAdjacencia[i] = (double*)malloc(numCoordenadas * sizeof(double));
        if (matrizAdjacencia[i] == NULL) {
            perror("Erro ao alocar memória");
            exit(1);
        }
        for (int j = 0; j < numCoordenadas; j++) {
            matrizAdjacencia[i][j] = INFINITY;
        }
    }
    for (int i = 0; i < numArestasMST; i++) {
        int origem = mst[i].origem;
        int destino = mst[i].destino;
        double peso = mst[i].peso;
        matrizAdjacencia[origem][destino] = peso;
        matrizAdjacencia[destino][origem] = peso;
    }

    // Encontrando o caminho mais curto
    int* caminho = (int*)malloc(numCoordenadas * sizeof(int));
    if (caminho == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    int cidadeAtual = 0;
    int* visitadas = (int*)calloc(numCoordenadas, sizeof(int));
    if (visitadas == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    caminho[0] = cidadeAtual;
    visitadas[cidadeAtual] = 1;
    for (int i = 1; i < numCoordenadas; i++) {
        int cidadeMaisProxima = encontrarCidadeMaisProxima(cidadeAtual, visitadas, matrizAdjacencia, numCoordenadas);
        caminho[i] = cidadeMaisProxima;
        visitadas[cidadeMaisProxima] = 1;
        cidadeAtual = cidadeMaisProxima;
    }

    // Liberando a memória alocada
    free(mst);
    for (int i = 0; i < numCoordenadas; i++) {
        free(matrizAdjacencia[i]);
    }
    free(matrizAdjacencia);
    free(visitadas);

    return caminho;
}

void escreverCaminho(char* nomeArquivo, int* caminho, int numCoordenadas) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    fprintf(arquivo, "NAME: %s\n", nomeArquivo);
    fprintf(arquivo, "TYPE: TOUR\n");
    fprintf(arquivo, "DIMENSION: %d\n", numCoordenadas);
    fprintf(arquivo, "TOUR_SECTION\n");
    for (int i = 0; i < numCoordenadas; i++) {
        fprintf(arquivo, "%d\n", caminho[i] + 1);
    }
    fprintf(arquivo, "EOF\n");
    fclose(arquivo);
}

/*
int main() {
    Coordenada* coordenadas = lerCoordenadas("arquivo.tsp");
    int numCoordenadas = coordenadas[0].cap;
    int* caminho = encontrarCaminhoMaisCurto(coordenadas, numCoordenadas);
    printf("Caminho mais curto:\n");
    for (int i = 0; i < numCoordenadas + 1; i++) {
        printf("%d ", caminho[i]);
    }
    printf("\n");
    free(coordenadas);
    free(caminho);
    return 0;
}
*/