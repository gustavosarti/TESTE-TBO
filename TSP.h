#ifndef TSP_H
#define TSP_H

#include "Leitura.h"
#include "MST.h"

int encontrarCidadeMaisProxima(int cidadeAtual, int* visitadas, double** matrizAdjacencia, int numCoordenadas);
int* encontrarCaminhoMaisCurto(Coordenada* coordenadas, int numCoordenadas);
void escreverCaminho(char* nomeArquivo, int* caminho, int numCoordenadas);

#endif