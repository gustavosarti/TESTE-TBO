# Nome do seu programa de saída
PROG = programa

# Lista de arquivos fonte
SRCS = Leitura.c MST.c TSP.c main.c

# Opções do compilador
CFLAGS = -lm

# Comando para compilar o programa
CC = gcc

all: $(PROG)

$(PROG): $(SRCS)
	$(CC) -o $(PROG) $(SRCS) $(CFLAGS)

clean:
	rm -f $(PROG)
