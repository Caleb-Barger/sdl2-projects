OBJS=*.c
CC=gcc
LIBS=-lSDL2 -lm
EXECDIR=bin
SRCDIR=src
FLAGS=-Wall -std=c99
EXEC=graph

all: $(SRCDIR)
	$(CC) $(FLAGS) ./$(SRCDIR)/$(OBJS)  $(LIBS) -o ./$(EXECDIR)/$(EXEC)

run: all 
	./$(EXECDIR)/$(EXEC)

clean: 
	rm -rf ./$(EXECDIR)/$(EXEC)
