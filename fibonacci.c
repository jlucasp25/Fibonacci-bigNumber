#include "fibonacci.h"

//////////////////////////////////////////////////////////////
//  Função Fibonacci                                        //
//  Inclui a função Fibonacci.                              //
//////////////////////////////////////////////////////////////

/*Função recursiva de fibonacci que guarda as somas parciais*/
int fibonacci(int n, int* ptparcial) {	
	int i = n;
	if (n < 2)	{	
		*(ptparcial+i) = n;
		return n;
	}
	else {
		*(ptparcial+i) = fibonacci(n-1,ptparcial) + fibonacci(n-2,ptparcial);
		return fibonacci(n-1,ptparcial) + fibonacci(n-2,ptparcial);
	}
}

