/*
This is the code file for the red-black tree module
By Jack Perry
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "rbtree.h"


/* function that creates a new node_t object from a integer key */
node_t *newNode(int key) {
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->key = key;
    new_node->color = RED;
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}


/* function inserts a key by inserting 
   it to the correct position and creating a node */
void insert(tree_t *tree, int key) {

}

/* function that will correct the 
   tree by ensuring the tree rule is kept true*/
void correctTree(tree_t *tree, node_t *node) {

}


/* rotation functions for specific nodes*/
void rotateLeft(tree_t *tree, node_t *node) { 

}
void rotateRight(tree_t *tree, node_t *node) {

}


/* function that find a specific node of a key in the tree*/
node_t *search(tree_t *tree, int key) {

}


/* function that deletes a specific key from the tree */
void deleteKey(tree_t *tree, int key) {

}


/* function that prints the tree in order*/
void printInorder(node_t *node) { 

    // check if null
    if (node == NULL) {
        return;
    }

    // recursive in order printing
    printInorder(node->left);
    printf("%d ", node->key);
    printInorder(node->right);

}