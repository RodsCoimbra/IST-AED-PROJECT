# Makefile do programa roap  
rop: main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h Grafo.c Grafo.h Fila.c Fila.h
	@#rm roap
	@clear
	gcc	-Wall -std=c99 -g	main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h Grafo.c Grafo.h Fila.c Fila.h	-o	roap

FILES = $(shell ls Chess_Party/chess098.in)
Resp1 = $(FILES:.in1=.)

t:
	@clear
	@./roap -s Enunciado_A6/enunciado601.in1
	@echo "\n"
	@diff -s Enunciado_A6/enunciado601.sol1 Enunciado_A6/enunciado601.sol2
	@echo "\n"
	@rm Enunciado_A6/*.sol2

tempo:
	@for F in ${FILES}; do /usr/bin/time -v ./roap $${F}; done;
	@echo "\n"
	@#clear
	@#for F in ${Resp1}; do diff -s $${F}sol1 $${F}sol2; done;

all:
	@for F in ${FILES}; do  ./roap $${F}; done;
	@#clear
	@#for F in ${Resp1}; do diff -s $${F}sol1 $${F}sol2; done;
	
tr:
	@for F in ${FILES}; do  ./roap -s $${F}; done;
	@clear
	@for F in ${Resp1}; do diff -s $${F}sol1 $${F}sol2; done;
	rm Enunciado_A6/*.sol2

tv:
	@#for F in ${FILES}; do valgrind --leak-check=full ./roap -s $${F}; done;
	valgrind --leak-check=full ./roap Enunciado/enunciado104.in
	@echo "\n\n\n"
	@#for F in ${Resp1}; do diff -s $${F}sol1 $${F}sol2; done;


r: 
	@#rm Bilhar_Pequeno/*.sol2
	@#rm Chess_Party/*.sol2
	@rm Enunciado/*.sol2
	@#rm Enunciado_A6/*.sol2
	@#rm Small/*.sol2
	@echo "Removido com sucesso"
