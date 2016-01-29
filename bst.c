#include <stdio.h>
#include <stdlib.h>

//create the struct for bst node
typedef struct t_node{
   int data;
   struct t_node *parent;
   struct t_node *leftnode;
   struct t_node *rightnode;
} t_node;


// create the struct for bst
typedef struct bst_t{
   struct t_node *root;
}bst_t;



//help method node_insert
void node_insert(t_node *tree,int data){
    //if the tree is null, then create a root node with the data
    if(tree == NULL){
      t_node *root = (t_node*)malloc(sizeof(t_node));
      root->data = data;
      root->parent = NULL;
      root->leftnode = NULL;
      root->rightnode = NULL;
    }
    else{
      //if the data is greater than the data of root
      //check if it's leaf, if yes, insert it
      //if not, node_insert(rightnode,data)
      if(data > (tree->data)){
        if(tree->rightnode == NULL){
          t_node *node = (t_node*)malloc(sizeof(t_node));
          tree->rightnode = node;
          node->data = data;
          node->parent = tree;
          node->leftnode = NULL;
          node->rightnode = NULL;
        }
        else{
           node_insert(tree->rightnode,data);
        }

      }
      else{
        //if the data is less than the data of root
        //check if it's leaf, if yes, insert it
        //if not, node_insert(leftnode,data)
        if(tree->leftnode == NULL){
          t_node *node = (t_node*)malloc(sizeof(t_node));
          tree->leftnode = node;
          node->data = data;
          node->parent = tree;
          node->leftnode = NULL;
          node->rightnode = NULL;
        }
        else{
          node_insert(tree->leftnode,data);
        }
      }
    }
}


//help method node_find
int node_find(t_node *tree, int data, int* found){
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
    //if not, node_find(rightnode,data,found)
    else if(data > (tree->data)){
      if(tree->rightnode == NULL){
        *found = 0;
         return -1;
      }
      return node_find(tree->rightnode,data,found);
    }
    //if the data is less than the data of root
    //check if it's leaf, if yes, means not found
    //if not, node_find(leftnode,data,found)
    else if(data < (tree->data)){
      if(tree->leftnode == NULL){
        *found = 0;
         return -1;
      }
      return node_find(tree->leftnode,data,found);
    }
}


//help method node_delete
void node_delete(t_node* tree, int data){
  //if root is null,do nothing
  if(tree == NULL){
    return;
  }
  //if the tree's data is larger than data
  //means it must be at left branch of root
  //do node_delete(tree->leftnode,data)
  if((tree->data) > data){
    node_delete(tree->leftnode,data);
  }
  //if the tree's data is small than data
  //means it must be at right branch of root
  //do node_delete(tree->rightnode,data)
  else if((tree->data) < data){
    node_delete(tree->rightnode,data);
  }
  else{
    //if tree has two children
    if((tree->leftnode!=NULL) && (tree->rightnode != NULL)){
      t_node *tmp = tree->leftnode;
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
      free(tmp);
    }
    //if tree only has left child
    else if(tree->leftnode != NULL){
      //connect it's chind with its parent
      t_node *tmp = tree->leftnode;
      if(tree->parent == NULL){
        tmp->parent = NULL;
      }
      else if((tree->parent)->leftnode == tree){
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
      free(tree);
    }
    //if tree only has right child
    else if(tree->rightnode != NULL){
      //connect its child with its parent
      t_node *tmp = tree->rightnode;
      if(tree->parent == NULL){
        tmp->parent = NULL;
      }
      else if((tree->parent)->leftnode == tree){
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
      free(tree);
    }
    //if tree is a leaf
    else{
      //just simply remove it
      if(tree->parent == NULL){
        free(tree);
        tree = NULL;
      }
      else if((tree->parent)->leftnode == tree){
        (tree->parent)->leftnode = NULL;
        tree->parent = NULL;
        free(tree);
      }
      else{
        (tree->parent)->rightnode = NULL;
        tree->parent = NULL;
        free(tree);
      }
    }
  }
}


void bst_insert(bst_t* bst, int data){
    node_insert(bst->root, data);
}


int bst_find(bst_t* bst, int data, int* found){
    node_find(bst->root,data, found);
}

void bst_delete(bst_t* bst, int data){
    node_delete(bst->root,data);
}



int main(){

   //create a root
   t_node *root =  (t_node*) malloc(sizeof(t_node));
   root->data = 9;
   root->parent = NULL;
   root->leftnode = NULL;
   root->rightnode = NULL;

   //create a tree
   bst_t *bst = (bst_t*)malloc(sizeof(bst_t));
   bst->root = root;

  // insert node
   bst_insert(bst,7);
   bst_insert(bst,10);
   bst_insert(bst,6);
   bst_insert(bst,8);
   bst_insert(bst,12);
   bst_insert(bst,11);
   bst_insert(bst,13);

   int* find = (int*)malloc(sizeof(int));

   int get = bst_find(bst,13,find);

   printf("Should return 13 if 13 exists: %i\n", get);

   //delete 12,11 and 10
   //right branch
   bst_delete(bst,10);

   t_node* removed = bst->root->rightnode;
   int result  = bst_find(bst,10,find);
   printf("The right child of root now should be 12 :%i\n", removed->data);
   printf("Should return -1 since 10 is removed: %i\n", result);

   bst_delete(bst,12);
   removed = bst->root->rightnode;
   result  = bst_find(bst,12,find);
   printf("The right child of root now should be 11 :%i\n", removed->data);
   printf("Should return -1 since 12 is removed: %i\n", result);

   bst_delete(bst,11);

   removed = bst->root->rightnode;
   result  = bst_find(bst,11,find);
   printf("The right child of root now should be 13 :%i\n", removed->data);
   printf("Should return -1 since 11 is removed: %i\n", result);




  //delete 7,6
  //left branch
   bst_delete(bst,7);
   removed = bst->root->leftnode;
   result  = bst_find(bst,7,find);
   printf("The left child of root now should be 6 :%i\n", removed->data);
   printf("Should return -1 since 7 is removed: %i\n", result);

   bst_delete(bst,6);
   removed = bst->root->leftnode;
   result  = bst_find(bst,6,find);
   printf("The left child of root now should be 8 :%i\n", removed->data);
   printf("Should return -1 since 6 is removed: %i\n", result);

   //delete the root, now the root should be 8
   bst_delete(bst,9);
   removed = bst->root->rightnode;
   printf("The root should be 8: %i\n", bst->root->data);
   printf("The right child of root now should be 13 :%i\n", removed->data);


   //delete the rest of the nodes
   bst_delete(bst,13);
   bst_delete(bst,8);

   // free *find and *bst
   free(find);
   free(bst);

}
