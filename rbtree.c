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
node_t *createNode(void *key) {
    // allocate memory
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    assert(new_node);

    // set attributes and return
    new_node->key = key;
    new_node->colour = RED;
    new_node->left = new_node->right = new_node->parent = NULL;

    return new_node;
}


/* function inserts a key by inserting 
   it to the correct position and creating a node */
void insert(tree_t *tree, void *key, int (*cmp)(const void *, const void *)) {

    // create the node to be inserted into the tree
    node_t *new_node = createNode(key);

    // if the tree is empty, create first root node and set to black
    if (tree->root == NULL) {
        new_node->colour = BLACK;
        tree->root = new_node;
    }

    // use iterative BST approach to insert, starting with root as current
    node_t *current = tree->root;
    while (TRUE) {
        // compare key with current node's key using cmp function
        int comparison_result = cmp(key, current->key);

        // if key is smaller than current node's key
        if (comparison_result < 0) {  
            // if it is empty, put the new node there and break
            if (current->left == NULL) {
                current->left = new_node;
                new_node->parent = current;
                break;
            } else {
                current = current->left;
            }
            
        // key is greater than current node's key
        } else if (comparison_result > 0) {  
            // if it is empty, put the new node there and break
            if (current->right == NULL) {
                current->right = new_node;
                new_node->parent = current;
                break;
            } else {
                current = current->right;
            }

        // key is equal to current node's key, and can be deleted
        } else {  
            free(new_node);
            return;
        }
    }

    // then call red-black tree correction function
    correctTree(tree, new_node);

}


/* function that will correct the 
   tree by ensuring the tree rule is kept true */
void correctTree(tree_t *tree, node_t *node) {

}


/* rotation functions for specific nodes*/
void rotateLeft(tree_t *tree, node_t *node) { 

}
void rotateRight(tree_t *tree, node_t *node) {

}


/* function that find a specific node of a key in the tree*/
node_t *search(tree_t *tree, void *key, int (*cmp)(const void *, const void *)) {

}


/* function that deletes a specific key from the tree */
void deleteKey(tree_t *tree, int key) {

}


/* function that prints the tree in order*/
void printInorder(node_t *node, void (*print)(const void *)) { 

    // check if null
    if (node == NULL) {
        return;
    }

    // recursive in order printing
    printInorder(node->left, print);
    print(node->key);
    printInorder(node->right, print);

}