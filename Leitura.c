#include "Leitura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Implementação da função para ler as coordenadas do arquivo
Coordenada* lerCoordenadas(const char* arquivo) {
    FILE* file = fopen(arquivo, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    
    int capacidade; // Capacidade inicial da matriz
    int cidade;
    double x, y;
    char string[100];
    int aux = 0;
    const char c[2] = ":";
    char* token;

    char nome[256] = ""; // Inicializa o nome como uma string vazia

    while (aux < 6) {
        if (fgets(string, sizeof(string), file) != NULL) {
            if (aux == 0) { // NAME
                token = strtok(string, c);
                while (token != NULL) {
                    token = strtok(NULL, c);
                    if (token != NULL) {
                        strcpy(nome, token); // Copia o nome
                    }
                    token = strtok(NULL, c);
                }
            } else if (aux == 2) { // Tipo
                token = strtok(string, c);
                while (token != NULL) {
                    token = strtok(NULL, c);
                    if (token != NULL && strcmp(" TSP\n", token) != 0) {
                        printf("Tipo de grafo errado\n");
                        fclose(file);
                        exit(1);
                    }
                    token = strtok(NULL, c);
                }
            } else if (aux == 3) { // Dimensão
                token = strtok(string, c);
                while (token != NULL) {
                    token = strtok(NULL, c);
                    if (token != NULL) {
                        capacidade = atoi(token); // Atualiza a capacidade
                    }
                    token = strtok(NULL, c);
                }
            } else if (aux == 4) { // Tipo de peso
                token = strtok(string, c);
                while (token != NULL) {
                    token = strtok(NULL, c);
                    if (token != NULL && strcmp(" EUC_2D\n", token) != 0) {
                        printf("Tipo de peso inválido\n");
                        fclose(file);
                       
                        exit(1);
                    }
                    token = strtok(NULL, c);
                }
            }
            aux++;
        }
    }
    int count = 0;
    Coordenada* coordenadas = (Coordenada*)malloc((capacidade)* sizeof(Coordenada));
    if (coordenadas == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        exit(1);
    }
  
    // Lê as coordenadas
    while (fscanf(file, "%d %lf %lf", &cidade, &x, &y) == 3) {

        if (count >= capacidade) {
            capacidade *= 2; // Dobre a capacidade se necessário
            coordenadas = (Coordenada*)realloc(coordenadas, capacidade * sizeof(Coordenada));
            if (coordenadas == NULL) {
                perror("Erro ao realocar memória");
                fclose(file);
                exit(1);
            }
        }
        
        coordenadas[count].cap = capacidade;
        coordenadas[count].cidade = cidade;
        coordenadas[count].x = x;
        coordenadas[count].y = y;
        count++;
    }

    

    fclose(file);
    return coordenadas;
}
