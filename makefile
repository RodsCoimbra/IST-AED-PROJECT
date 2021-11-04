# Makefile do programa roap  
roap: main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h
	gcc	-Wall -std=c99 -O3	main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h	-o	roap


FILES = $(shell ls Enunciado_A6/*.in1)
Resp1 = $(FILES:.in1=.)

t:
	@clear
	@./roap -s Enunciado_A6/enunciado601.in1
	@echo "\n"
	@diff -s Enunciado_A6/enunciado601.sol1 Enunciado_A6/enunciado601.sol2
	@echo "\n"
	@rm Enunciado_A6/*.sol2

all:
	@for F in ${FILES}; do  ./roap -s $${F}; done;
	@clear
	@for F in ${Resp1}; do diff -s $${F}sol1 $${F}sol2; done;
	
tr:
	@for F in ${FILES}; do  ./roap -s $${F}; done;
	@clear
	@for F in ${Resp1}; do diff -s $${F}sol1 $${F}sol2; done;
	rm Enunciado_A6/*.sol2

tv:
	@for F in ${FILES}; do valgrind --leak-check=full ./roap -s $${F}; done;
	@echo "\n\n\n"
	@for F in ${Resp1}; do diff -s $${F}sol1 $${F}sol2; done;
r: 
	rm Enunciado_A6/*.sol2