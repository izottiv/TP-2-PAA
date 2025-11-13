build:	main.c manipulacaoMapa/mapa.c identificacaoMenorCaminho/menorCaminho.c geracaoMapa/gerarMapa.c
	gcc main.c manipulacaoMapa/mapa.c identificacaoMenorCaminho/menorCaminho.c geracaoMapa/gerarMapa.c -o Teste

run:
	./Teste