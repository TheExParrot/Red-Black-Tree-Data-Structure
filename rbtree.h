/*
This module contains functions and type defintions for RB Tree Implementation
By Jack Perry
*/

#ifndef _RBTREE_H_
#define _RBTREE_H_

// Magic Numbers
#define RED 0
#define BLACK 1

#define FALSE 0
#define TRUE 1

// Struct Definitions
typedef struct node node_t;
struct node {
    void *key;
    int colour;
    node_t *left, *right, *parent;
};

typedef struct Tree {
    node_t *root;
} tree_t;

// Function Prototypes
node_t *createNode(void *key);
void insert(tree_t *tree, void *key, int (*cmp)(const void *, const void *));
void correctTree(tree_t *tree, node_t *node);
void rotateLeft(tree_t *tree, node_t *node);
void rotateRight(tree_t *tree, node_t *node);
void swapColour(node_t *n1, node_t *n2);
node_t *search(tree_t *tree, void *key, int (*cmp)(const void *, const void *));
int delete(tree_t *tree, void *key, int (*cmp)(const void *, const void *));
void print_in_order(node_t *node, void (*print)(const void *));


#endif