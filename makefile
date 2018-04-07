############################# Makefile ##########################
# Programa 1 - Laboratórios de Programação
# BigNumber + Fibonacci
# João Lucas Pires - 201606617
# Solange Sampaio - 201603610

CFLAG = -Wall -std=c11 -O3
CC = gcc
HEADERS = fibonacci.h bigNumber.h

all: main
main: fibonacci.o bigNumber.o main.o
	$(CC) bigNumber.o fibonacci.o main.o -o main $(CFLAG)
bigNumber.o: bigNumber.c
	$(CC) -o bigNumber.o -c bigNumber.c $(CFLAG)
fibonacci.o: fibonacci.c
	$(CC) -o fibonacci.o -c fibonacci.c $(CFLAG)
main.o: main.c $(HEADERS)
	$(CC) -o main.o -c main.c $(CFLAG)
clean:
	rm -rf *.o
