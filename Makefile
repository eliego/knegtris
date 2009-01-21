CC = g++
CFLAGS = -g -Wall

LDFLAGS = -lncurses

all : clean Knegtris clean-build

Knegtris : Kloss.o ScreenContext.o Knegtris.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o Knegtris Kloss.o ScreenObject.o ScreenContext.o Knegtris.o

ScreenContext.o : ScreenObject.o
	$(CC) $(CFLAGS) -c ScreenContext.cc

ScreenObject.o :
	$(CC) $(CFLAGS) -c ScreenObject.cc

Kloss.o : ScreenObject.o
	$(CC) $(CFLAGS) -c Kloss.cc

Knegtris.o :
	$(CC) $(CFLAGS) -c Knegtris.cc

clean : 
	rm -rf Knegtris

clean-build :
	rm -rf *.o
