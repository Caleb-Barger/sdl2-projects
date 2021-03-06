OBJS=*.c
CC=gcc
LIBS=-lSDL2 -lm
FLAGS=-Wall -std=c99
OUT=renderer
EXEC=bin
SRC=src

all: $(SRC)
	$(CC) $(FLAGS) ./$(SRC)/$(OBJS) $(LIBS) -o ./$(EXEC)/$(OUT)
run: all 
	./$(EXEC)/$(OUT)
clean:
	rm ./$(EXEC)/$(OUT)
