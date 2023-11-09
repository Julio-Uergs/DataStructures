#include <stdio.h>
#include <stdlib.h>

#define menuEntries 6

typedef struct tree {int data; struct tree *left, *right;} tree;

void clear() {
	#ifdef _WIN32
		system("cls");
    #endif
    #ifdef linux
		system("clear");
    #endif
}

void printTree(tree *root, int level) {
    if (root) {
      printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
      printTree(root->left, level + 1);
      printTree(root->right, level + 1);
    }
}

//recebe valor int
void getVal (int *val) {
	clear();
	scanf("%d", val);
}

//imprime o menu e recebe os valores, por algum motivo a função de receber os valores estava bugando aqui e eu resolvi não perder tempo tentando descobrir o que tinha de errado.
void mainMenu (int *menu) {
    // clear();
	printf ("Main Menu\n\n1-InsertIntoTree  2-PrintTree  3-PreOrder  4-InOrder  5-PostOrder  %d-Exit\n\nInsert your option: ", menuEntries);
	scanf ("%d", menu);
	while (*menu < 1 || *menu > menuEntries) {
		printf ("Invalid option, try again: ");
		scanf ("%d", menu);
	}
    // clear(); //não limpei a tela, caso tu queira ver todos os resultados ao mesmo tempo :)
}
