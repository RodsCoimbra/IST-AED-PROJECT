# Makefile do programa roap  
roap: main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h
	gcc	-Wall -std=c99 -O3	main.c Funcoes_aux.c Ficheiros_dados.c As.c As.h Funcoes_aux.h Ficheiros_dados.h	-o	roap

t:
	#@clear
	@./roap -s Enunciado_A6/enunciado601.in1
	@echo "\n"
	@diff -s Enunciado_A6/enunciado601.sol1 Enunciado_A6/enunciado601.sol2
	@echo "\n"
	@rm Enunciado_A6/*.sol2

t16:
	@clear
	@./roap -s Enunciado_A6/enunciado616.in1
	@echo "\n"
	@diff -s Enunciado_A6/enunciado616.sol1 Enunciado_A6/enunciado616.sol2
	@echo "\n"
	@rm Enunciado_A6/*.sol2
r: 
	rm Enunciado_A6/*.sol2