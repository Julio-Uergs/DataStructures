//O tempo de compilação vai ser o mesmo independente do tamanho da lista, a variável seria o tempo de execução, já que a lista é dinâmica e não existe em tempo de compilação.
//No entanto, o tempo de execução para uma lista grande varia com a ordem dos elementos, o algoritmo de ordenação escolhido e a quantidade de elementos da lista.
//Para medir o tempo de ordenação eu usaria um plugin do zsh que mede o tempo de execução do programa e o apresenta assim que o programa é finalizado. Caso este método não tenha precisão o suficiente, outra alternativa seria usar a função time() da time.h
//Para 10000 itens, o pior caso foi 1 segundo. No entanto, para 100000 itens, demora 42 segundos para ordenar a lista.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tie {
	int val; 			//32 bits
	struct tie *nxt;	//64 bits
} knot;					//96 bits

void swap(knot *a, knot *b) {
  int temp = a->val;
  a->val = b->val;
  b->val = temp;
}

void bblSort(knot **beg) {
	knot *current = *beg;
  	knot *read = NULL;
	int swapped = 1;
	while (swapped) {
		swapped = 0;
		current = *beg;
		read = current->nxt;
		while (read != NULL) {
			if (current->val > read->val) {
				swap(current, read);
				swapped = 1;
			}
			current = read;
			read = read->nxt;
		}
	}
}

void pileUp (knot **beg, int val) {
    knot *new;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
    else {
        new->val = val; 				//atribuí o valor para a variável final.
		// printf("End Val: %p\tEnd Ptr: %p\n", &new->val, new);
        if (*beg == NULL)				//verifica se é o último  (ou, no caso, o único?) item da pilha
            new->nxt = NULL;			//se sim, salva o ponteiro como NULL, indicando que ele é o último item.
        else
            new->nxt = *beg;			//se não, aponta para o "de baixo"
        }
		*beg = new;						//atribuí o novo início, já que ele sempre vai mudar.
}

void prntStack (knot *beg) {
	knot *read = beg;
	int pos = 0;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
			printf("Val\tPos\tAddress\n");
		do {
		    printf("%d\t%d\t%p\n", read->val, pos++, read->nxt);
			read = read->nxt;
	    } while (read != NULL);
	}
}

int main() {
	knot *beg = NULL;
	time_t fStart, oStart, oEnd, fEnd;
	int val = 0;
	long *start, *end;
	time(start);
	while (val < 1000000) {
		pileUp(&beg, val++);
	}
	time(end);
	prntStack(beg);
	//printf("\n\nEOF\n\n");
	 oStart = time(NULL);
	// bblSort(&beg);
	 oEnd = time(NULL);
	// prntStack(beg);
	printf("It took %f s to order the list using bubble sort\nAdditionally, it took %.2f to fill the entire list with numbers and %.2f for the entire program to run.\n", (double)(end - start), difftime(fEnd, fStart), (double) oEnd - (double) fStart);
}
