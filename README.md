# connect_four_game

### Descrição do programa:

Este programa é composto pelos seguintes ficheiros: “alphabeta.cpp”, “alphabeta.h”, “common.h”, “minimax.cpp”, “minimax.h”, “myboost.cpp”, “myboost.h”, “node.cpp”, “node.h”, “connect4.cpp”,"Makefile". <br/> <br/> 
O ficheiro “connect4.cpp” contém a função main,  o “alphabeta.cpp” contém a implementação do alphabeta, “minimax.cpp” contém a implementação do minimax, “myboost.cpp” contém a função que pré-calcula todas as combinações possíveis de segmentos de 4, 5, 6 e 7 e o “node.cpp” é o ficheiro que contém a implementação de nó. <br/> 

-------------------------------------------

### Requerimentos:

Compilador g++ com c++ versão 11. <br/>
OS linux. (necessário devido a utilização da biblioteca readline)

-------------------------------------------

### Instruções para compilar e executar:

Compilar: make <br/> 
executar: ./connect4 <br/> 

-------------------------------------------

### Execução:

No inicio do programa vai ser questionado as seguintes perguntas: <br/> 
* Se quer bot contra bot; <br/> 
* Qual metodo pretendido (MiniMax ou AlphaBeta); <br/> 

Caso escolha bot contra bot: <br/> 
* Qual a dificuldade do primeiro bot (X), que vai ser o primeiro a jogar; <br/> 
* Qual a dificuldade do segundo bot (O); <br/> 

Caso escolha jogador contra bot: <br/> 
* Qual a dificuldade do bot; <br/> 
* Que simbolo pretende usar; <br/> 
* Se quer ser o primeiro a jogar; <br/> 

Em cada jogada do jogador humano é pedido o número da coluna em que pretende jogar (0 a 6) <br/> 

Em cada jogada do bot é mostrado o tempo em milissegundos que demorou a fazer a jogada, numero de nós expandindos (em caso de ser AlphaBeta é mostrado também o número de podas). <br/> 

Quando algum jogador ganhar é impresso o símbolo do jogador que ganhou e o tempo total de jogo do bot. <br/> 

É depois questionado se pretende jogar outra vez e terá de fazer todos os passos acima descritos. <br/> 

-------------------------------------------

### Autores:

| Nome              | Numero UP     |
| ----------------- | ------------- |
| Diogo Pereira     | 201605323     |
| Afonso Fernandes  | 201606852     |
