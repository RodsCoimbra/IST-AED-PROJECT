# Makefile do programa roap  
roap: main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h Grafo.c Grafo.h Fila.c Fila.h 
	gcc	-Wall -std=c99 -O3	main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h Grafo.c Grafo.h Fila.c Fila.h	-o	roap

A=Bilhar_Pequeno
B=Chess_Party
C=Enunciado
D=Small
FILES = $(shell ls ${A}/*.in)		
Resp1 = $(FILES:.in=.)


t:
	@#clear
	@/usr/bin/time -v ./roap Chess_Party/chess11.in
	@#./roap Enunciado/enu.in
	@echo "\n"
	@#diff -s Enunciado/ola.sol Enunciado/ola.so2
	@#rm Chess_Party/*.so2

time:
	@#for F in ${FILES}; do /usr/bin/time -v ./roap $${F}; done;
	@#echo "\n"
	@#clear
	@#for F in ${Resp1}; do diff -s $${F}sol $${F}so2; done;

all:
	@for F in ${FILES}; do  ./roap $${F} && echo "$${F}"; done;
	@#clear
	@for F in ${Resp1}; do diff -s $${F}sol $${F}so2; done;
	
tr:
	@for F in ${FILES}; do  ./roap $${F}; done;
	@clear
	@for F in ${Resp1}; do diff -s $${F}sol $${F}sol2; done;
	rm Enunciado_A6/*.sol2

tv:
	@for F in ${FILES}; do valgrind --leak-check=full ./roap $${F} && echo "\n\n\n"; done;
	@for F in ${Resp1}; do diff -s $${F}sol $${F}so2; done;

r: 
	@rm Bilhar_Pequeno/*.so2 
	@rm Chess_Party/*.so2
	@rm Enunciado/*.so2
	@rm Small/*.so2
	@echo "Removido com sucesso"