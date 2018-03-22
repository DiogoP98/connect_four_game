# connect_four_game
Connect four game in c++ for assigment  of the class of IA

Descrição do programa:
	No zip que enviámos estão os seguintes ficheiros: “alphabeta.cpp”, “alphabeta.h”, “common.h”, “minimax.cpp”, “minimax.h”, “myboost.cpp”, “myboost.h”, “node.cpp”, “node.h”, “connect4.cpp”,"Makefile". 
	O ficheiro “connect4.cpp” contém a função main,  o “alphabeta.cpp” contém a implementação do alphabeta, “minimax.cpp” contém a implementação do minimax, “myboost.cpp” contém a função que pré-calcula todas as combinações possíveis de segmentos de 4, 5, 6 e 7 e o “node.cpp” é o ficheiro que contém a implementação de nó.

-------------------------------------------

Requerimentos:
	Compilador g++ com c++ versão 11.

-------------------------------------------

Instruções para compilar e executar:
	Compilar: make
	executar: ./connect4

-------------------------------------------

Execução:
	No inicio do programa vai ser questionado as seguintes perguntas:
		Se quer bot contra bot;
		Qual metodo pretendido (MiniMax ou AlphaBeta);
	Caso escolha bot contra bot:
		Qual a dificuldade do primeiro bot (X), que vai ser o primeiro a jogar;
		Qual a dificuldade do segundo bot (O);
	Caso escolha jogador contra bot:
		Qual a dificuldade do bot;
		Que simbolo pretende usar;
		Se quer ser o primeiro a jogar;
	Em cada jogada do jogador humano é pedido o número da coluna pretendida (0 a 6)
	Em cada jogada do bot é mostrado o tempo em milissegundo que demorou a fazer a jogada, numero de nós expandindos (em caso de ser AlphaBeta também o número de podas).
	Quando algum jogador ganhar é impresso o símbolo do jogador que ganhou e o tempo total de jogo do bot.
	É depois questionado se pretende jogar outra vez e terá de fazer todos os passos acima descritos.

-------------------------------------------

Nota:
	Caso encontre algum erro a compilar tente uma compilacao limpa: make clean & make.

Diogo Pereira           201605323
Afonso Fernandes        291696852
Lucas Paula             201608440

