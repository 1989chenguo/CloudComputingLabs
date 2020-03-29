CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku_solve

sudoku_solve: main.cc neighbor.cc sudoku_basic.cc 
	g++  -o $@ $^ -O2 -lpthread
	
