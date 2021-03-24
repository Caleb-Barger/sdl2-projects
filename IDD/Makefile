OBJS=*.c
CC=gcc
LIBS=`sdl2-config --libs` -lSDL2_ttf
EXECDIR=bin
SRCDIR=src
FLAGS=-Wall -std=c99
EXEC=idd

all: $(SRCDIR) $(EXECDIR)
	$(CC) $(FLAGS) ./$(SRCDIR)/$(OBJS)  $(LIBS) -o ./$(EXECDIR)/$(EXEC)

run: all $(EXECDIR)
	./$(EXECDIR)/$(EXEC)

clean: 
	echo "removing bin folder and its contents..."
	rm -rf ./$(EXECDIR)/$(EXEC)

$(EXECDIR):
	mkdir ./$(EXECDIR)
