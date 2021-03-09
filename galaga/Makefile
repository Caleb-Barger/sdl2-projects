OBJS=*.c
CC=gcc
LIBS=-lSDL2 
EXECDIR=bin
SRCDIR=src
FLAGS=-Wall -std=c99
EXEC=gal

all: $(SRCDIR)
	$(CC) $(FLAGS) ./$(SRCDIR)/$(OBJS)  $(LIBS) -o ./$(EXECDIR)/$(EXEC)

run: all 
	./$(EXECDIR)/$(EXEC)

clean: 
	rm ./$(EXECDIR)/$(EXEC)
