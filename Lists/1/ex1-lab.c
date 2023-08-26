// 1.	Suponha que em um laboratório, cada paciente quando chega escolhe uma senha para atendimento. Essa senha pode ser para realizar exames de sangue ou exames de imagem. Quando um paciente é chamado pelo atendente ele deve informar o número da senha, seu nome, o plano de saúde(Unimed/Ipê) e o tipo de exame a fazer(sangue/imagem). Ao término do dia, cada atendente gera a listagem dos pacientes que ele atendeu. Apresente:

// a)	A listagem dos pacientes atendidos
// b)	A quantidade de pacientes atendidos que possuem Unimed.
// c)	A quantidade de pacientes atendidos para realizar exames de Sangue.

// OBS: Apresente os dados com a seguinte construção (endereço do nó, valores do nó, valor do próximo). 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tie {
	char name[50], lifeInsurance, exam; // (0 - Unimed. 1 - Ipê) and (0 - Blood. 1 - Imaging)
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
		printf("Client name: ");
		clearStdin();
		fgets(new->name, sizeof(new->name), stdin);
		new->name[strcspn(new->name, "\n")] = '\0'; // more hacky workarounds (finds \n, replaces it with \0
		clearVerifier(sizeof(new->name), new->name);
		clear();
		printf("Client password: [0 - Blood. 1 - Imaging]: ");
		scanf("%c", &(new->exam));
		while (new->exam < '0' || new->exam > '1') {
			printf("Err. Invalid option. Try again: [0 - Blood. 1 - Imaging]: ");
			scanf("%c", &(new->exam));
		}
		clearStdin();
		clear();
		printf("Client life insurance provider: [0 - Unimed | 1 - Ipê]: ");
		scanf("%c", &(new->lifeInsurance));
		while (new->lifeInsurance < '0' || new->lifeInsurance> '1') {
			printf("Err. Invalid option. Try again: [0 - Blood. 1 - Imaging]: ");
			scanf("%c", &(new->lifeInsurance));
		}
		clearStdin();
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
			printf("Address\tName\tExam Type\tLife Insurance\tNext\n");
		do {
		    printf("%p\t%s\t", read, read->name);
			if (read->exam == '1')
				printf("Imaging\t");
			else {
				printf("Blood\t");
				blood++;
			}
			if (read->lifeInsurance == '1')
				printf("Ipê");
			else {
				printf("Unimed");
				unimed++;
			}
			printf("\t%p\n", read->nxt);
			read = read->nxt;
	    } while (read != NULL);
	}
	printf("\nThere are %d people that have Unimed.\nAnd %d people that had blood examinations.\n\nPress Return to Main Menu", unimed, blood);
	getchar(), getchar();
}

void mMenu(int *men) {
	clear();
	printf(/*  .---.         ____      _______      | ,_|       .'  __ `.  \  ____  \  ,-./  )      /   '  \  \ | |    \ |  \  '_ '`)    |___|  /  | | |____/ /   > (_)  )       _.-`   | |     .  (  .  .-'    .'   _    | |  ( ' )  \  `-'`-'|___  |  _( )_  | | (_{;}_) |   |        \ \ (_ o _) / |  (_,_)  /   `--------`  '.(_,_).'  /_______.'  */"1-Serve a new customer\n2-List past customers\n3-Exit\n\nInsert your option: ");
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
