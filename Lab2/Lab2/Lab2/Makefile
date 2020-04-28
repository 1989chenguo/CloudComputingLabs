CC = g++
 
STD = -std=c++11
 
CFLAGS = -g  -Wall -pthread
 
SRC = $(wildcard *.cpp)
 
OBJ = $(patsubst %cpp, %o, $(SRC))
 
BIN = HttpServer

 
all:$(OBJ)
	$(CC) $(OBJ) $(CFLAGS)  -o $(BIN)
 
%.o:%.cpp
	$(CC) $(STD) $(CFLAGS) -c $< -o $@
 
 
.PHONY : clean
clean:
	rm *.o $(BIN)  -rf 