FLAGS= -Wextra -Wall -DDEBUG -g -std=c++14

all: predictors.o
	g++ $(FLAGS) *.o -o predictors
predictors.o: predictors.cpp predictors.h
	g++ $(FLAGS) -c predictors.cpp -o predictors.o
clean:
	rm -rf *.o predictors