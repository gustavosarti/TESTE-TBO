#ifndef LEITURA_H
#define LEITURA_H

// Definindo a estrutura de dados para coordenadas
typedef struct {
    int cidade;
    double x; //coordenada
    double y;
    int cap; // capacidade maxima
} Coordenada;

// Declaração da função para ler as coordenadas
Coordenada* lerCoordenadas(const char* arquivo);

#endif
