/*
This module contains functions and type defintions for RB Tree Implementation
By Jack Perry
*/

#ifndef _RBTREE_H_
#define _RBTREE_H_

// Magic Numbers
#define RED 0
#define BLACK 1

// Struct Definitions
typedef struct node node_t;
struct node {
    int key;
    int color;
    node_t *left, *right, *parent;
};

typedef struct Tree {
    node_t *root;
} tree_t;

// Function Prototypes
node_t *newNode(int key);
void insert(tree_t *tree, int key);
void correctTree(tree_t *tree, node_t *node);
void rotateLeft(tree_t *tree, node_t *node);
void rotateRight(tree_t *tree, node_t *node);
node_t *search(tree_t *tree, int key);
void delete(tree_t *tree, int key);
void printInorder(node_t *node);


#endif