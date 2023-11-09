#include <stdio.h>
#include <stdlib.h>
/*
                5
          3            10
      2       4    7         12
  0                   9   11    14
*/






typedef struct tree {
  int data;
  struct tree *left, *right;
}tree;

int getData(char string[]) {
  int data;
  printf("\n%s", string);
  scanf("%d", &data);
  return data;
}

void searchData(tree *root, int data, tree **ptr) {
  if (root) {
    *ptr = root;
    if(data > root->data) {
      root = root->right;
    }
    else {
      root = root->left;
    }
    searchData(root, data, ptr);
  }
}

void insertData(tree **root, int data) {
  tree *newData = (tree*)malloc(sizeof(tree)), *ptr = NULL;
  if (newData) {
    newData->data = data;
    if (*root == NULL) {
      *root = newData;
    }
    else {
      searchData(*root, data, &ptr);
      if (ptr->data < data) {
        ptr->right = newData;
      } else if(ptr->data > data) {
        ptr->left = newData;
      }
    }
    newData->right = NULL;
    newData->left = NULL;
  }
}

int treeHeight(tree *root) {
  int leftHeight, rightHeight;
  if (root == NULL) {
    return 0;
  } else {
    leftHeight = treeHeight(root->left);
    rightHeight = treeHeight(root->right);
    if (leftHeight > rightHeight) {
      return 1 + leftHeight;
    }
    return 1 + rightHeight;
  }
}

int menu() {
  int op;
  do {
    printf("\n\t1 - inserir na arvore\n\t2 - printar simetrica");
    printf("\n\t3 - calcular altura da arvore\n\t4 - Quantidade de nos da arvore\n\t5 - Quantidade de folhas");
    printf("\n\t6 - fim\n\tEScolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > 6 || op < 1);
  return op;
}
void printSymmetric(tree *root) {
  if (root) {
    printSymmetric(root->left);
    printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
    printSymmetric(root->right);
  }
}

int countNodeFromTree(tree *root) {
  if (root) {
    int leftCount, rightCount;
    leftCount = countNodeFromTree(root->left);
    rightCount = countNodeFromTree(root->right);
    return 1 + leftCount + rightCount;
  }
  return 0;
}

int countLeafFromTree(tree *root) {
  if (root) {
    int leftCount, rightCount;
    leftCount = countLeafFromTree(root->left);
    rightCount = countLeafFromTree(root->right);
    if (!root->left && !root->right) {
      return 1;
    }
    return leftCount + rightCount;
  }
  return 0;
}

int main() {
  tree *root = NULL;
  int option, data;
  do {
    option = menu();
    system("clear||cls");
    switch (option) {
      case 1:
        data = getData("Informe o dado: ");
        insertData(&root, data);
        break;
      case 2:
        printSymmetric(root);
        break;
      case 3:
        printf("\n\tAltura da arvore ->->-> %d", treeHeight(root) - 1);
        break;
      case 4:
        printf("\nQuantidade de nos da arvore ->->-> %d", countNodeFromTree(root));
        break;
      case 5:
        printf("\nQuantidade de folhas de uma arvore ->->-> %d", countLeafFromTree(root));
        break;
      default:
        printf("\nFim\n");
    }
  } while(option != 6);
  return 0;
}
