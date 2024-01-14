CC=gcc
PREFIX=/usr

all:
	${CC} ucfetch.c -O2 -o ucfetch
	
clean:
	-rm *.o ucfetch

install:
	install -s ucfetch ${PREFIX}/bin

uninstall:
	-rm ${PREFIX}/bin/ucfetch
