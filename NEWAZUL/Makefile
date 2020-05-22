.default: all

all: azul

clean:
	rm -f azul *.o

azul: Game.o LinkedList.o main.o Node.o Player.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^