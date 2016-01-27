#include <stdio.h>
#include <stdlib.h>

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
        }
        else{
           bst_insert(tree->rightnode,data);
        }

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
        }
        else{
          bst_insert(tree->leftnode,data);
        }
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
    else if(data > (tree->data)){
      if(tree->rightnode == NULL){
        *found = 0;
         return -1;
      }
      return bst_find(tree->rightnode,data,found);
    }
    //if the data is less than the data of root
    //check if it's leaf, if yes, means not found
    //if not, bst_find(leftnode,data,found)
    else if(data < (tree->data)){
      if(tree->leftnode == NULL){
        *found = 0;
         return -1;
      }
      return bst_find(tree->leftnode,data,found);
    }
}


void bst_delete(bst_t* tree, int data){
  //if root is null,do nothing
  if(tree == NULL){
    return;
  }
  //if the tree's data is larger than data
  //means it must be at left branch of root
  //do bst_delete(tree->leftnode,data)
  if((tree->data) > data){
    bst_delete(tree->leftnode,data);
  }
  //if the tree's data is small than data
  //means it must be at right branch of root
  //do bst_delete(tree->rightnode,data)
  else if((tree->data) < data){
    bst_delete(tree->rightnode,data);
  }
  else{
    //if tree has two children
    if((tree->leftnode!=NULL) && (tree->rightnode != NULL)){
      bst_t *tmp = tree->leftnode;
      //go to the largest node at its left branch
      while (tmp->rightnode != NULL) {
        tmp = tmp->rightnode;
      }
      //exchange the value
      tree->data = tmp-> data;
      if(tmp->leftnode != NULL){
        (tmp->parent) -> rightnode = tmp->leftnode;
        (tmp->leftnode) -> parent = tmp->parent;
      }
      //remove the node
      else{
        tmp->leftnode = NULL;
        tmp->rightnode = NULL;
        tmp->parent = NULL;
        if(tree->leftnode == tmp){
          tree->leftnode = NULL;
        }
        else{
          tree->rightnode = NULL;
       }
      }
    }
    //if tree only has left child
    else if(tree->leftnode != NULL){
      //connect it's chind with its parent
      bst_t *tmp = tree->leftnode;
      if((tree->parent)->leftnode == tree){
        (tree->parent)->leftnode = tmp;
        tmp->parent = tree->parent;
      }
      else{
        (tree->parent)->rightnode = tmp;
        tmp->parent = tree->parent;
      }
      //remove the node
      tree->leftnode = NULL;
      tree->rightnode = NULL;
      tree->parent = NULL;
    }
    //if tree only has right child
    else if(tree->rightnode != NULL){
      //connect its child with its parent
      bst_t *tmp = tree->rightnode;
      if((tree->parent)->leftnode == tree){
        (tree->parent)->leftnode = tmp;
        tmp->parent = tree->parent;
      }
      else{
        (tree->parent)->rightnode = tmp;
        tmp->parent = tree->parent;
      }
      //remove the node
      tree->leftnode = NULL;
      tree->rightnode = NULL;
      tree->parent = NULL;
    }
    //if tree is a leaf
    else{
      //just simply remove it
      if((tree->parent)->leftnode == tree){
        (tree->parent)->leftnode = NULL;

      }
      else{
        (tree->parent)->rightnode = NULL;
     }
     tree->parent = NULL;
    }
  }
}




int main(){

   //create a root
   bst_t *root =  (bst_t*) malloc(sizeof(bst_t));
   root->data = 9;
   root->parent = NULL;
   root->leftnode = NULL;
   root->rightnode = NULL;

  // insert node
   bst_t* one = bst_insert(root,7);
   bst_t* two =bst_insert(root,10);
   bst_t* three =bst_insert(root,6);
   bst_t* four =bst_insert(root,8);
   bst_t* five=bst_insert(root,12);
   bst_t* six=bst_insert(root,11);
   bst_t* seven =bst_insert(root,13);

   int* find = (int*)malloc(sizeof(int));

   int get = bst_find(root,13,find);

   printf("Should return 13 if 13 exists: %i\n", get);

   //delete 12,11 and 10
   //right branch
   bst_delete(root,10);

   bst_t* removed = root->rightnode;
   int result  = bst_find(root,10,find);
   printf("The right child of root now should be 12 :%i\n", removed->data);
   printf("Should return -1 since 10 is removed: %i\n", result);

   bst_delete(root,12);
   removed = root->rightnode;
   result  = bst_find(root,12,find);
   printf("The right child of root now should be 11 :%i\n", removed->data);
   printf("Should return -1 since 12 is removed: %i\n", result);

   bst_delete(root,11);

   removed = root->rightnode;
   result  = bst_find(root,11,find);
   printf("The right child of root now should be 13 :%i\n", removed->data);
   printf("Should return -1 since 11 is removed: %i\n", result);




  //delete 7,6
  //left branch
   bst_delete(root,7);
   removed = root->leftnode;
   result  = bst_find(root,7,find);
   printf("The left child of root now should be 6 :%i\n", removed->data);
   printf("Should return -1 since 7 is removed: %i\n", result);

   bst_delete(root,6);
   removed = root->leftnode;
   result  = bst_find(root,6,find);
   printf("The left child of root now should be 8 :%i\n", removed->data);
   printf("Should return -1 since 6 is removed: %i\n", result);

   //delete the root, now the root should be 8
   bst_delete(root,9);
   removed = root->rightnode;
   result  = bst_find(seven,9,find);
   printf("The root should be 8: %i\n", root->data);
   printf("The right child of root now should be 12 :%i\n", removed->data);
   printf("Should return -1 since 9 is removed: %i\n", result);


   //free everything
   free(one);
   free(two);
   free(three);
   free(four);
   free(five);
   free(six);
   free(seven);
   free(root);
   free(find);

}
