#include "bigNumber.h"

//////////////////////////////////////////////////////////////
//  Métodos da estrutura BigNumber                          //
//  Inclui a definição dos métodos auxiliares               //
//////////////////////////////////////////////////////////////

/*Construtor de bigNumber: recebe um número inteiro*/
bigNumber listConstructor2(int num) {
	
	int count = 0;
	int size = 0;
	bigNumber bn;	
	bn.lista = malloc(sizeof(struct bList));
	bnList temp = bn.lista;

	/*Conta o numero de digitos*/
	bn.size = 1;
	count = num;
 	while (count /= 10)
 		bn.size++;
	size = bn.size;
	
	//Insere os digitos
	while (size > 0) {
 		temp->digit = num % 10;
 		num /= 10;		
		size--;
		if (size == 0) {
			temp->next = NULL;
			break;
		}
		temp->next = malloc(sizeof(struct bList));
		temp = temp->next;
	}

	return bn;
}

/*Construtor de BigNumber: Constrói um bigNumber Vazio*/
bigNumber listConstructor3() {
	bigNumber b;
	b.lista = NULL;
	b.size = 0;
	return b;
}

/*Construtor de Cópia: Gera uma lista nova com os mesmos digitos (Apontadores diferentes)*/
bigNumber listCopyConstructor(bigNumber b2) {
	bigNumber final = listConstructor3();
	int i = 0;
	for (i = 0 ; i < b2.size ; i++ )
		final = addDigit(final,getDigit(b2,i)); 
	return final;
}

//Métodos

/*Retorna o dígito na posição pos do bigNumber b (pos funciona como os índices de um array, de 0 a size-1)*/
int getDigit(bigNumber b, int pos) {
	if (pos >= b.size || pos < 0)
		return -1;
	int i = 0;
	bnList temp = b.lista;
	while (i < pos) {
		temp = temp->next;
		i++;
	}
	return temp->digit;
}

/*Retorna o número contido em b num array de int's (Não utilizado no programa final.) (É preciso dar free() manualmente ao array fora da função.)*/
int* getNumber(bigNumber b) {
	int i = 1;
	int* arr = malloc(sizeof(int) * b.size);
	bnList temp = b.lista;
	while (temp != NULL) {
		*(arr+b.size-i) = temp->digit; 
		temp = temp->next;
		i--;
	}
	return arr;	
}

/*Imprime os dígitos da lista pela ordem que estão na mesma*/
void printBNumberListOrder(bigNumber b) {
	
	if (b.size == 0) {
		printf("[ ]\n");
		return;
	}
	
	printf("[ ");
	
	bnList temp = b.lista;
	
	while (temp != NULL) {
		if (temp->next != NULL) {
			printf("%d , ",temp->digit);
			temp = temp->next;
		}
		else {
			printf("%d ]\n",temp->digit);
			break;
		}
	}
}

/*Imprime os dígitos da lista pela ordem real do número representado*/
void printBNumberRealOrder(bigNumber b) {
	
	if (b.size == 0) {
		printf("[ ]\n");
		return;
	}
	int* arr = malloc(sizeof(int)*b.size);
	int i = 0;	
	bnList temp = b.lista;
	
	while (temp != NULL) {
			*(arr+i) = temp->digit;
			temp = temp->next;
			i++;
		}
	i--;
	printf("[ ");
	for (i=b.size - 1; i > 0 ; i--) {
		printf("%d , ",*(arr+i));
	}
	printf("%d ]\n",*(arr));
	free(arr);
	return;
}

/*Adiciona um dígito n ao fim da lista do BigNumber b*/
bigNumber addDigit(bigNumber b,int n) {	
	
	if (n > 9 || n < 0)
		return b;

	bnList temp = b.lista;
	
	if (b.size == 0) {
		b.lista = malloc(sizeof(struct bList));
		b.lista->digit = n;
		b.lista->next = NULL;
		b.size++;
		return b;
	}

	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = malloc(sizeof(struct bList));
	temp->next->digit = n;
	temp->next->next = NULL;
	b.size++;
	return b;
}


/*Verifica se b1 é menor que b2*/
bool isSmaller(bigNumber b1, bigNumber b2) {
	int i = 0;
	if(b1.size < b2.size)
		return true;
	if(b2.size < b1.size)
		return false;
	for(i= (b1.size - 1); i>=0; i--) {
		if(getDigit(b1,i) < getDigit(b2,i))
			return true;
		else if(getDigit(b1,i) > getDigit(b2,i))
			return false;
	}
	return false;
}

/*Verifica se b1 é igual a b2*/
bool isEqual(bigNumber b1, bigNumber b2) {
	int i = 0;
	if(b1.size != b2.size)
		return false;
	for( i = (b1.size - 1) ; i >= 0 ; i--) {
		if(getDigit(b1,i) == getDigit(b2,i))
			continue;
		else return false;
	}
	return true;
}

/*Retorna uma nova lista que contém os digitos da lista recebida, invertidos.*/
bigNumber inverse(bigNumber b) {
	int i = b.size - 1;
	bigNumber final = listConstructor3();
	for (i=b.size-1 ; i >= 0 ; i--) 
		final = addDigit(final,getDigit(b,i));
	freeList(b);
	return final;
}

/*Testa a estrutura de um bigNumber passado como argumento e envia-a para o stdout*/
void testList(bigNumber b) {
	
	printf("Ordem real do número: ");
	printBNumberRealOrder(b);
	
	printf("Ordem dos dígitos na lista: ");
	printBNumberListOrder(b);
	
	bnList temp = b.lista;
	int i = 0;
	
	while (temp != NULL) {
		printf("Indice_No:%d\tEndereco_No:%p\tAponta_para:%p\tValor:%d\n",i,temp,temp->next,temp->digit);
		i++;
		temp = temp->next;
	}
	
	printf("Tamanho Declarado:%d\tTamanho real:%d\n",b.size,i);
	printf("\n");
	return;
}

/*Limpa a lista - Versão 2*/
void freeList(bigNumber b) {
	b.size = 0;
	bnList temp = b.lista;
	bnList prev = NULL;
	while (temp != NULL) {
		prev = temp;
		temp = temp->next;
		free(prev);
	}
	free(temp);
	return;
}

//Métodos das Operações

/*Soma dois bigNumbers e retorna o resultado*/
bigNumber add(bigNumber b1, bigNumber b2) {
	
	int i = 0;
	int carry = 0;
	int sum = 0;	
	bigNumber tmp;

	
	/*O segundo número deve ser sempre o que tem maior número de dígitos*/
	if (b1.size > b2.size) { 
		tmp = b2;
		b2 = b1;
		b1 = tmp;
	}


	int n1 = b1.size;
	int n2 = b2.size;


	bigNumber bf = listConstructor3();
  
    for (i = 0; i < n1; i++)
    {
        sum = getDigit(b1,i) + getDigit(b2,i) + carry;
        bf = addDigit(bf,sum%10);
        carry = sum/10;
    } 
    
    for (i = n1; i < n2; i++)
    {
        sum = getDigit(b2,i) + carry;
        bf = addDigit(bf,sum%10);
        carry = sum/10;
    }

    if (carry)
        bf = addDigit(bf,carry);
    return bf;
}

/*Subtrai dois bigNumbers e retorna o resultado*/
bigNumber subtract(bigNumber b1, bigNumber b2) {

	int i = 0;
    int sub = 0;
	int carry = 0;
  	bigNumber tmp;

  	 if (isEqual(b1,b2) == true)
    	return listConstructor2(0);

  	/*O segundo número deve ser sempre o que tem maior número de dígitos*/
    if (b1.size < b2.size) {
    	tmp = b2;
		b2 = b1;
		b1 = tmp;
	}
 	
    bigNumber bf = listConstructor3();

    for (i = 0; i < b2.size; i++)
    {
        sub = getDigit(b1,i) - getDigit(b2,i) - carry;

        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        bf = addDigit(bf,sub);
    }
 
    for (i = b2.size; i < b1.size; i++)
    {
        sub = getDigit(b1,i) - carry;
        if (sub < 0)
        	{sub = sub+10;
        		carry = 1;}
        else
        	carry = 0;
        
        bf = addDigit(bf,sub);
    }
    bigNumber invbf = inverse(bf);
    bnList temp = invbf.lista;
    bnList prev = NULL;
    while (temp->digit == 0) {
    	prev = temp;
    	temp = temp->next;
    	invbf.lista = temp;
    	invbf.size--;
    	free(prev);
    }
   bf = inverse(invbf);
   return bf;
}


/*Multiplica dois bigNumbers e retorna o resultado*/
bigNumber multiply(bigNumber b1, bigNumber b2) {
    
    int i = 0;
    int j = 0;
    int result[b1.size+b2.size];
    int index_n1 = 0; 
    int index_n2 = 0; 
    int carry = 0;
    int n1 = 0;
    int n2 = 0;
    int sum = 0;
    int c = 0;
    int aux = b1.size + b2.size - 1;

    /*Se algum dos operandos for 0, o resultado é 0.*/
    if ( ( b1.size == 1 && b1.lista->digit == 0 ) || ( b2.size == 1 && b2.lista->digit == 0 ) )
       return listConstructor2(0);

   	/*Inicializa o vetor com 0.*/
 	for (i = 0 ; i < b1.size + b2.size ; i++)
 		result[i] = 0;

   	for (i = 0 ; i < b1.size ; i++)
	    {
	        carry = 0;
	        n1 = getDigit(b1,i);
        	index_n2 = 0; 
         
	        for (j = 0 ; j < b2.size ; j++)
        		{
            		n2 = getDigit(b2,j);
            		sum = n1 * n2 + result[index_n1 + index_n2] + carry;
            		carry = sum/10;
 					result[index_n1 + index_n2] = sum % 10;
            		index_n2++;
        		}
        	if (carry > 0) {
            	result[index_n1 + index_n2] += carry;
        	}
        	index_n1++;
    	}
 	   
    while (aux >= 0 && result[aux] == 0)
       aux--;
 
    if (aux == -1)
       return listConstructor2(0);

    bigNumber bf = listConstructor3();

    while (c <= aux)
       bf = addDigit(bf,result[c++]);
    
    return bf;
}

bigNumber divide(bigNumber a, bigNumber b) {
	bigNumber tempA = listCopyConstructor(a);
	bigNumber last;
	
	int count = 0;
	
	bigNumber zero = listConstructor2(0);
	
	if (isEqual(a,zero) == true) {
		freeList(zero);freeList(tempA);
		return listConstructor2(0);
	}

	if (isEqual(b,zero) == true) {
		freeList(zero);freeList(tempA);
		return listConstructor3();
	}

	while (isSmaller(tempA,zero) == false) {
		if (isSmaller(b,tempA) == false)
			break;
		//Ao subtrair recursivamente, o tempA anterior é "dereferenciado" e perdido.
		//last guarda a ultima referência para permitir libertar todas as iterações.
		last = tempA;
		tempA = subtract(tempA,b);
		freeList(last);
		count++;
	}
	count++;
	freeList(zero);
	freeList(tempA);
	return listConstructor2(count);
} 

/*Versão Iterativa do Fibonacci para bigNumbers (permite libertar memória dos bigNumbers ao contrário da versão recursiva [freeHandler])*/
bigNumber bnFibonacci(bigNumber n) {
	
	bigNumber one = listConstructor2(1);

	bigNumber fib1 = listConstructor2(0);
	bigNumber fib2 = listConstructor2(1);
	bigNumber fibf = listConstructor3();
	
	bigNumber iList = listConstructor2(2);
	bigNumber nplus1 = add(n,one);
	
	bigNumber freeHandler;

	if (isEqual(n,fib1) == true) {
		freeList(fibf);freeList(fib2);freeList(iList);freeList(one);freeList(nplus1);
		return fib1;
	}
	
	if (isEqual(n,fib2) == true) {
		freeList(fib1);freeList(fibf);freeList(iList);freeList(one);freeList(nplus1);
		return fib2;
	}

	while (isSmaller(iList,nplus1) == true) {
		
		freeHandler = fibf;
		
		fibf = add(fib1,fib2);
		
		freeList(freeHandler);
		
		freeHandler = fib1;
		
		fib1 = listCopyConstructor(fib2);
		
		freeList(freeHandler);
		
		freeHandler = fib2;
		
		fib2 = listCopyConstructor(fibf);
		
		freeList(freeHandler);
		
		freeHandler = iList;
		
		iList = add(iList,one);
		
		freeList(freeHandler);
	}
	
	freeList(fib1);freeList(fib2);freeList(iList);freeList(one);freeList(nplus1);
	return fibf;
}

