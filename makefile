CC = g++
CFLAGS = -Wall -m64 -g
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: julia.o controls.o
	$(CC) julia.o controls.o $(CFLAGS) $(SFMLFLAGS) -o julia

julia.o: julia.asm
	nasm -f elf64 -g -o julia.o julia.asm

controls.o: main.cpp
	$(CC) $(CFLAGS) $(SFMLFLAGS) -c main.cpp -o controls.o 

clean:
	rm -f *.o
	rm -f julia
