EXEC_NAME=a.out

CC=g++

CFLAGS= -std=c++11

# Source files
SRC =                   \
	test.cpp	\
        minimax.cpp     \
	alphabeta.cpp   \   
	node.cpp	

OBJ =  ${SRC:.cpp=.o}

all: ${EXEC_NAME}

${EXEC_NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${EXEC_NAME} ${OBJ}

%.o: %.cpp
	${CC} ${CFLAGS} -c -o $@ $+ 

clean:
	rm ${EXEC_NAME} *.o *~ *# -rf

