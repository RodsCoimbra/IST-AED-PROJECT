# Makefile do projeto RoaP

# escolha do compilador
CC= gcc
# flags para a compilação
CFLAGS= -Wall -std=c99
# gerar variáveis com listas de ficheiros, essenciais para a utilização do "makefile"
SRCS=$(wildcard *.c)	# contém todos os .c
OBJS = $(SRCS:.c=.o) # A variável objs é igual à variável srcs, mas substitui todos os .c por .o 
HEADERS=$(wildcard *.h)	# contém todos os .h

# nome do executável após fazer "makefile"
all: roap

# compilar executável com optimização, dar o comando "make release"
release: CFLAGS+= -O3
release: clean
release: roap


roap: $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $@

# listar dependências. para simplificar, cada ficheiro .o depende do correspondente .c, de todos os ficheiros .h e da Makefile
%.o: %.c $(HEADERS) Makefile
	$(CC) -c $(CFLAGS) -o $@ $<

# para forçar recompilação, dar o comando "make clean" e depois "make" ou o comando "make clean ; make"
clean:
	rm -f *.o covid19