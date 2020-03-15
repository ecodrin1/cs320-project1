#FLAGS= -Wextra -Wall -DDEBUG -std=c++14

all: predictors.o
	g++ *.o -o predictors
predictors.o: predictors.cpp predictors.h
	g++ -c predictors.cpp -o predictors.o
clean:
	rm -rf *.o predictors