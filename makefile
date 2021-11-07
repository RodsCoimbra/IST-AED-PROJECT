# Makefile do programa roap  
rop: main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h Grafo.c Grafo.h Fila.c Fila.h
	@#rm roap
	@clear
	gcc	-Wall -std=c99 -O3	main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h Grafo.c Grafo.h Fila.c Fila.h	-o	roap

A=Bilhar_Pequeno
B=Chess_Party
C=Enunciado
D=Enunciado_A6
E=Small
FILES = $(shell ls ${C}/*.in)
Resp1 = $(FILES:.in1=.)


t:
	@clear
	@valgrind --leak-check=full -s ./roap Enunciado/enunciado116.in
	@echo "\n"
	@#diff -s Enunciado/enunciado116.sol Enunciado/enunciado116.sol2
	@#rm Enunciado/*.sol2

time:
	@for F in ${FILES}; do /usr/bin/time -v ./roap $${F}; done;
	@echo "\n"
	@#clear
	@#for F in ${Resp1}; do diff -s $${F}sol $${F}sol2; done;

all:
	@for F in ${FILES}; do  ./roap $${F}; done;
	@clear
	@for F in ${Resp1}; do diff -s $${F}sol $${F}sol2; done;
	
tr:
	@for F in ${FILES}; do  ./roap $${F}; done;
	@clear
	@for F in ${Resp1}; do diff -s $${F}sol $${F}sol2; done;
	rm Enunciado_A6/*.sol2

tv:
	@for F in ${FILES}; do valgrind --leak-check=full ./roap $${F}; done;
	@echo "\n\n\n"
	@#for F in ${Resp1}; do diff -s $${F}sol $${F}sol2; done;

r: 
	@#rm Bilhar_Pequeno/*.sol2 
	@#rm Chess_Party/*.sol2
	@rm Enunciado/*.sol2
	@#rm Enunciado_A6/*.sol2
	@#rm Small/*.sol2
	@#echo "Removido com sucesso"
