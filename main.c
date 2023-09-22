#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Leitura.h"
#include <math.h>
#include "MST.h"
#include "TSP.h"
#include <time.h>

char* extrairNomeArquivo(char* nomeArquivo) {
    char* nome = (char*)malloc(strlen(nomeArquivo) + 1);
    if (nome == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    strcpy(nome, nomeArquivo);
    char* extensao = strrchr(nome, '.');
    if (extensao != NULL) {
        *extensao = '\0';
    }
    return nome;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }
    char* nomeArquivo = extrairNomeArquivo(argv[1]);
    Coordenada* coordenadas = lerCoordenadas(argv[1]);
    int numCoordenadas = coordenadas[0].cap;
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

    // Criando o array de coordenadas a partir da matriz de adjacência
    Coordenada* coordenadasAdj = (Coordenada*)malloc(numCoordenadas * sizeof(Coordenada));
    if (coordenadasAdj == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    for (int i = 0; i < numCoordenadas; i++) {
        coordenadasAdj[i].x = i;
        coordenadasAdj[i].y = i;
    }

    clock_t inicio = clock();
    int* caminho = encontrarCaminhoMaisCurto(coordenadasAdj, numCoordenadas);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    char nomeArquivoMST[strlen(nomeArquivo) + 5];
    sprintf(nomeArquivoMST, "%s.mst", nomeArquivo);
    char nomeArquivoTour[strlen(nomeArquivo) + 6];
    sprintf(nomeArquivoTour, "%s.tour", nomeArquivo);

    escreverMST(nomeArquivoMST, mst, numArestasMST, numCoordenadas);
    escreverCaminho(nomeArquivoTour, caminho, numCoordenadas);
    free(coordenadas);
    free(mst);
    free(caminho);
    free(nomeArquivo);
    free(coordenadasAdj);

    printf("Tempo para gerar o tour: %f segundos\n", tempo);

    return 0;
}