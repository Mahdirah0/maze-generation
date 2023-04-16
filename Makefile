CC=g++
CFLAGS=-I.
DEPS = 
OBJ = main.cpp 

all:
	g++ -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system

