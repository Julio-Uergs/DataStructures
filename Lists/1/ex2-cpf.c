// 2.	Faça um código em C que permite ao usuário criar uma lista com os seguintes dados: CPF usuário, Nome do curso, ano de início. Realize as seguintes operações utilizando funções:
// a.	Inserir nó na lista – final 
// b.	Imprimir a lista 

// OBS: Apresente os dados com a seguinte construção (endereço do nó, valores do nó, valor do próximo). 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tie {
	char courseName[30], CPF[12], ingressYear[5];
	struct tie *nxt;
} knot;

void clearStdin() {
    int c = getchar();
    while (c != '\n') { //do while c == n || c == EOF?
        c = getchar();
    }
}

//NEM sempre é bom limpar o buffer
void clearVerifier (long unsigned int size, char *string) {
    if (strlen(string) + 1 == size) {
        int c = getchar();
		while (c != '\n') { //do while c == n || c == EOF?
        c = getchar();
		}
    }
}

void clear() {
#ifdef _WIN32
  system("cls");
#endif
#ifdef linux
  system("clear");
#endif
}

void cMenu(knot *new) {
		clearStdin();
		printf("Please insert your CPF: ");
		fgets(new->CPF, sizeof(new->CPF), stdin);
		new->CPF[strcspn(new->CPF, "\n")] = '\0';
		clearVerifier(sizeof(new->CPF), new->CPF);
		clear();
		printf("Please insert your course name: ");
		fgets(new->courseName, sizeof(new->courseName), stdin);
		new->courseName[strcspn(new->courseName, "\n")] = '\0';
		clearVerifier(sizeof(new->courseName), new->courseName);
		clear();
		printf("Please insert the year you joined your university: ");
		fgets(new->ingressYear, sizeof(new->ingressYear), stdin);
		new->ingressYear[strcspn(new->ingressYear, "\n")] = '\0';
		clearVerifier(sizeof(new->ingressYear), new->ingressYear);
}

void pileDown (knot **beg) { 	//i know it's not that way, but you get what I mean...
    knot *new, *read = *beg;
	clear();
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("Memory Full!\n");
    } else {
		cMenu(new);
		if(*beg == NULL) {
			new->nxt = NULL;
			*beg = new;
		} else {
			while (read->nxt != NULL) {		//até o fim da lista
				read = read->nxt;			//lê o próximo valor
			}
			new->nxt = NULL;
			read->nxt = new;
		}
    }
}

void prntStack (knot *beg) {
	knot *read = beg;
	int unimed = 0, blood = 0;
	clear();
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
			printf("Address\tCourse Name\tCPF\tIngress Year\tNext\n");
		do {
		    printf("%p\t%s\t%s\t%s\t%p\n", read, read->courseName, read->CPF, read->ingressYear, read->nxt);
			read = read->nxt;
	    } while (read != NULL);
	}
	printf("\n\nPress Return to Main Menu");
	getchar(), getchar();
}

void mMenu(int *men) {
	clear();
	printf("1-New entry\n2-Show entries\n3-Exit\n\nInsert your option: ");
	scanf("%d", men);
	while (*men < 1 || *men > 3) {
		printf("Invalid option, try again: ");
		scanf("%d", men);
	}
}

int main () {
	knot *beg = NULL;
	int men;
	do {
		mMenu(&men);
		switch (men) {
			case 1: pileDown(&beg);
			break;
			case 2: prntStack(beg);
			break;
		}
	} while (men != 3);
	clear();
}
