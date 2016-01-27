#include "stdio.h"
#include "stdlib.h"

//create the struct for bst
typedef struct bst_t{
   int data;
   struct bst_t *parent;
   struct bst_t *leftnode;
   struct bst_t *rightnode;
} bst_t;


bst_t* bst_insert(bst_t *tree,int data){
    //if the tree is null, then create a root node with the data
    if(tree == NULL){
      bst_t *root = (bst_t*)malloc(sizeof(bst_t));
      root->data = data;
      root->parent = NULL;
      root->leftnode = NULL;
      root->rightnode = NULL;
      return root;
    }
    else{
      //if the data is greater than the data of root
      //check if it's leaf, if yes, insert it
      //if not, bst_insert(rightnode,data)
      if(data > (tree->data)){
        if(tree->rightnode == NULL){
          bst_t *node = (bst_t*)malloc(sizeof(bst_t));
          tree->rightnode = node;
          node->data = data;
          node->parent = tree;
          node->leftnode = NULL;
          node->rightnode = NULL;
          return node;
        }
        bst_insert(tree->rightnode,data);

      }
      else{
        //if the data is less than the data of root
        //check if it's leaf, if yes, insert it
        //if not, bst_insert(leftnode,data)
        if(tree->leftnode == NULL){
          bst_t *node = (bst_t*)malloc(sizeof(bst_t));
          tree->leftnode = node;
          node->data = data;
          node->parent = tree;
          node->leftnode = NULL;
          node->rightnode = NULL;
          return node;
        }
        bst_insert(tree->leftnode,data);
      }
    }
}

int bst_find(bst_t *tree, int data, int* found){
    //if root is null, set found to 0 and return -1(undefined)
    if(tree == NULL){
      *found = 0;
       return -1;
    }
    //if found, set found to 1 and return the data
    if((tree->data) == data){
      *found = 1;
      return data;
    }
    //if the data is greater than the data of root
    //check if it's leaf, if yes, means not found
    //if not, bst_find(rightnode,data,found)
    if(data > (tree->data)){
      if(tree->rightnode == NULL){
        *found = 0;
         return -1;
      }
      bst_find(tree->rightnode,data,found);
    }
    //if the data is less than the data of root
    //check if it's leaf, if yes, means not found
    //if not, bst_find(leftnode,data,found)
    if(data < (tree->data)){
      if(tree->leftnode == NULL){
        *found = 0;
         return -1;
      }
      bst_find(tree->leftnode,data,found);
    }
}


int bst_delete(bst_t* tree, int data){
  //if root is null,do nothing
  if(tree == NULL){
    return -1;
  }
  //if found, go to the smallest node in the right branch
  //so set the leftnode of its rightnode to its leftnode
  //and set both its leftnode and rightnode to NULL
  if((tree->data) == data){
    (tree->rightnode)->leftnode = tree->leftnode;
    tree->leftnode = NULL;
    tree->rightnode = NULL;
    return 1;
  }
  //if the data is greater than the data of root
  //check if it's leaf, if yes, means not found
  //if not, bst_delete(rightnode,data)
  if(data > (tree->data)){
    if(tree->rightnode == NULL){
      return -1;
    }
    bst_delete(tree->rightnode,data);
  }
  //if the data is less than the data of root
  //check if it's leaf, if yes, means not found
  //if not, bst_delete(leftnode,data,found)
  if(data < (tree->data)){
    if(tree->leftnode == NULL){
      return -1;
    }
    bst_delete(tree->leftnode,data);
  }

}




int main(){

  bst_t *root =  (bst_t*) malloc(sizeof(bst_t));
  root->data = 9;
  root->parent = NULL;
  root->leftnode = NULL;
  root->rightnode = NULL;

   bst_t *result  = bst_insert(root,10);

   int* find = (int*)malloc(sizeof(int));

   int get = bst_find(root,10,find);

   int remove = bst_delete(root,10);

   printf("%i\n", remove);

   free(result);
   free(root);

}
