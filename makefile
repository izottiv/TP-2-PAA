build:	main.c menorCaminho.c mapa.c gerarMapa.c
	gcc main.c menorCaminho.c mapa.c gerarMapa.c -o Teste

run:
	./Teste