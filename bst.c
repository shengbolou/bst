#include "stdio.h"
#include "stdlib.h"

//create the struct for bst
typedef struct bst_t{
   int data;
   struct bst_t *parent;
   struct bst_t *leftnode;
   struct bst_t *rightnode;
} bst_t;


bst_t* insert(bst_t *tree,int data){
    //if the tree is null, then create a root node with the data
    if(tree == NULL){
      bst_t *root = (bst_t*)malloc(sizeof(bst_t*));
      root->data = data;
      root->parent = NULL;
      root->leftnode = NULL;
      root->rightnode = NULL;
      bst_t *toReturn = root;
      free(root);
      return toReturn;
    }

}


int main(){

   bst_t *result  = insert(NULL,10);

   printf("%i\n", result->data);

}
