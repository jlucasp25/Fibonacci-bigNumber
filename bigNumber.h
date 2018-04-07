#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////
//  Classe/Estrutura BigNumber                              //
//  Inclui a definição da estrutura e os métodos auxiliares //
//////////////////////////////////////////////////////////////

/*A explicação de cada função encontra-se no ficheiro bigNumber.c*/

//Tipo booleano auxiliar
typedef enum { false, true } bool;

//Struct da Lista (de bigNumbers)

typedef struct bList {
	int digit; //Digito
	struct bList *next; //Apontador para o próximo dígito/nó
} *bnList;

//Struct bigNumber 
typedef struct {
	bnList lista; //Lista de digitos
	int size; //Tamanho da lista (quantidade de digitos)
} bigNumber;

//Protótipos

bigNumber listConstructor2(int num); 
bigNumber listConstructor3();
bigNumber listCopyConstructor(bigNumber b2);

void printBNumberListOrder(bigNumber b);
void printBNumberRealOrder(bigNumber b);

int* getNumber(bigNumber b);
int getDigit(bigNumber b, int pos);

bigNumber addDigit(bigNumber b,int n);

bigNumber add(bigNumber b1, bigNumber b2);
bigNumber subtract(bigNumber b1, bigNumber b2);
bigNumber multiply(bigNumber b1, bigNumber b2);
bigNumber divide(bigNumber a, bigNumber b);
bigNumber bnFibonacci(bigNumber n);

bool isSmaller(bigNumber b1, bigNumber b2);
bool isEqual(bigNumber b1, bigNumber b2);

bigNumber inverse(bigNumber b);

void testList(bigNumber b);
void freeList(bigNumber b);
