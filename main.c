#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigNumber.h"
#include "fibonacci.h"

//////////////////////////////////////////////////////////////
//  Função main()                                           //
//  Inclui a interface e dá inicio ao programa.             //
//////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
	
	char choice = '0';
	int n;
	int i = 0;
	bigNumber b1 = listConstructor3();
	bigNumber b2 = listConstructor3();
	bigNumber bf = listConstructor3();
	
	if (argc == 1 || argc == 2) {
		printf("Utilização do Programa\n\n");
		printf("Fibonacci:\n\tNOME_DO_PROGRAMA FIB N\t (onde N representa o número de fibonacci a calcular\n");
		printf("BigNumbers:\n\tSoma:\n\tNOME_DO_PROGRAMA BN + VAL1 VAL2\n\n"); 
		printf("\tSubtração:\n\tNOME_DO_PROGRAMA BN - VAL1 VAL2\n\n"); 
		printf("\tMultiplicação:\n\tNOME_DO_PROGRAMA BN x VAL1 VAL2\n\n"); 
		printf("\tDivisão Inteira:\n\tNOME_DO_PROGRAMA BN / VAL1 VAL2\n");
		printf("\t\t\t\t\t  (onde VAL1 e VAL2 são os operandos)\n"); 
		printf("\tFibonacci:\n\tNOME_DO_PROGRAMA BN FIB N\t  (onde N é o número de fibonacci a calcular)\n\n"); 
		return 0;
	}
	
	/*Casos dos Fibonacci*/
	if ( !strcmp(argv[1],"FIB") && ( (n = atoi(argv[2])) < 0) )  {
		printf("O nº de fibonacci tem de ser maior que 0!\n");
		freeList(b1);freeList(b2);freeList(bf);
		exit(1);
	}
	else if (!strcmp(argv[1],"FIB")) {
		int ptparcial[n];
		int final = fibonacci(n,ptparcial);
		printf("O número de fibonacci para n=%d é: %d\n", n, final);
		printf("Os valores parciais obtidos foram:\n ");
		for (i = 1 ; i < n ; i++) {
			if (i % 10 == 0)
				printf("\n");
			printf("%d\t",ptparcial[i]);	
		}
		printf("\n");
		freeList(b1);freeList(b2);freeList(bf);
		return 0;
	}
	
 /*Casos dos Big Numbers*/	
	if ( !strcmp(argv[1],"BN") ) {
		/*Casos do Fibonacci de BigNumbers*/
		if (!strcmp(argv[2],"FIB")) {
			
			for (i = strlen(argv[3]) - 1; i >= 0 ; i--)
				b1 = addDigit(b1, ( *(argv[3]+i) - '0') );			

			bf = bnFibonacci(b1);
			
			printf("O número de fibonacci para n=");
			printBNumberRealOrder(b1);
			printf("é: ");
			printBNumberRealOrder(bf);
			
			while (1) {
			printf("\nDeseja ver mais informações sobre as listas? (S/N)\n");
			choice = getchar();
			if (choice == 'S' || choice == 's' ) {
				printf("\n");
				testList(b1);
				testList(bf);
				break;
			}
			else if (choice == 'N' || choice == 'n') {
				break;
			}
			else 
				continue;
		}		
			freeList(b1);freeList(b2);freeList(bf);
			return 0;
	}
		if (argc < 5) {
			printf("Argumentos não compatíveis! Execute o programa sem argumentos para ver as opções disponíveis.\n");
			freeList(b1);freeList(b2);freeList(bf);
			exit(1);
		}

		for (i = strlen(argv[3]) - 1; i >= 0 ; i--)
			b1 = addDigit(b1, ( *(argv[3]+i) - '0') );

		for (i = strlen(argv[4]) - 1 ; i >= 0 ; i--)
			b2 = addDigit(b2, ( *(argv[4]+i) - '0') );
		/*Operações de Big Numbers*/
		if (!strcmp(argv[2],"+"))
			bf = add(b1,b2);
		
		else if (!strcmp(argv[2],"-")) { 
			if (isSmaller(b1,b2) == true) {
				printf("O primeiro operando tem de ser maior que o segundo!\n");
				freeList(b1);freeList(b2);freeList(bf);
				exit(1);
			}
				bf = subtract(b1,b2);
		}
		else if (!strcmp(argv[2],"x"))
			bf = multiply(b1,b2);
		
		else if (!strcmp(argv[2],"/")) {
			bf = divide(b1,b2);
			if (bf.lista == NULL) {
				printf("É impossivel dividr por 0!\n");
				freeList(b1);freeList(b2);freeList(bf);
				exit(1);
			}
		}
		else {
			printf("Argumentos não compatíveis! Execute o programa sem argumentos para ver as opções disponíveis.\n");
			freeList(b1);freeList(b2);freeList(bf);
			exit(1);
		}
		printf("O Resultado é: ");
		printBNumberRealOrder(bf);
		while (1) {
			printf("\nDeseja ver mais informações sobre as listas? (S/N)\n");
			choice = getchar();
			if (choice == 'S' || choice == 's' ) {
				printf("\n");
				testList(b1);
				testList(b2);
				testList(bf);
				break;
			}
			else if (choice == 'N' || choice == 'n') {
				break;
			}
			else 
				continue;
		}		
	}
	freeList(b1);freeList(b2);freeList(bf);
	return 0;
}