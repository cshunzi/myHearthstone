CC = g++
CFLAGS = -Wall -std=c++11
LFLAGS =
OBJS = card.o minion.o spell.o deck.o board.o player.o main.o

all: hearthstone.exe

hearthstone.exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o hearthstone.exe

card.o: card.h card.cpp
	$(CC) $(CFLAGS) -c card.cpp

minion.o: minion.h minion.cpp card.h
	$(CC) $(CFLAGS) -c minion.cpp

spell.o: spell.h spell.cpp card.h
	$(CC) $(CFLAGS) -c spell.cpp

deck.o: deck.h deck.cpp card.h
	$(CC) $(CFLAGS) -c deck.cpp

board.o: board.h board.cpp player.h
	$(CC) $(CFLAGS) -c board.cpp

player.o: player.h player.cpp card.h
	$(CC) $(CFLAGS) -c player.cpp

main.o: main.cpp player.h deck.h board.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	del *.o hearthstone.exe
