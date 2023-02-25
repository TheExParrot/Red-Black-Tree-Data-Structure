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
        return;
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

    // create some pointers to use later
    node_t *parent = NULL;
    node_t *grandparent = NULL;
    node_t *uncle = NULL;

    // check condition in while loop
    while ((node != tree->root) 
            && (node->colour != BLACK) 
            && (node->parent->colour == RED)) {

        // set parents and grandparent
        parent = node->parent;
        grandparent = parent->parent;

        // LEFT SIDE: Parent is on the left of grandparent cases
        if (parent == grandparent->left) {
            // uncle is on the right as parent is left
            uncle = grandparent->right;

            // Case 1: uncle is red
            if (uncle != NULL && uncle->colour == RED) {
                grandparent->colour = RED;
                parent->colour = BLACK;
                uncle->colour = BLACK;
                node = grandparent;
            } else {
                // Case 2: additional left rotation to 
                // make node into right child if left
                if (node == parent->right) {
                    rotateLeft(tree, parent);
                    node = parent;
                    parent = node->parent;
                }

                // Case 3: node is right child
                rotateRight(tree, grandparent);
                swapColour(parent, grandparent);
                node = parent;

            }
        // RIGHT SIDE: Parent is on right side of grandparent
        } else {
            // uncle is on the left as parent is right
            uncle = grandparent->left;

            // Case 1: uncle is red
            if (uncle != NULL && uncle->colour == RED) {
                grandparent->colour = RED;
                parent->colour = BLACK;
                uncle->colour = BLACK;
                node = grandparent;
            } else {
                // Case 2: additional right rotation to 
                // make node into left child if right
                if (node == parent->left) {
                    rotateRight(tree, parent);
                    node = parent;
                    parent = node->parent;
                }

                // Case 3: node is left child
                rotateLeft(tree, grandparent);
                swapColour(parent, grandparent);
                node = parent;

            }
        }
    }
    
    // finish by setting root to black
    tree->root->colour = BLACK;

}


/* rotation functions at a source node*/
void rotateLeft(tree_t *tree, node_t *node) {
    node_t *right_child = node->right;

    // make right child the new root
    if (node == tree->root) {
        tree->root = right_child;
    }

    // update parent pointers
    right_child->parent = node->parent;
    if (node->parent != NULL) {
        if (node == node->parent->left) {
            node->parent->left = right_child;
        } else {
            node->parent->right = right_child;
        }
    }

    // update child pointers
    node->right = right_child->left;
    if (right_child->left != NULL) {
        right_child->left->parent = node;
    }
    right_child->left = node;
    node->parent = right_child;
}

void rotateRight(tree_t *tree, node_t *node) {
    node_t *left_child = node->left;

    // make left child the new root
    if (node == tree->root) {
        tree->root = left_child;
    }

    // update parent pointers
    left_child->parent = node->parent;
    if (node->parent != NULL) {
        if (node == node->parent->left) {
            node->parent->left = left_child;
        } else {
            node->parent->right = left_child;
        }
    }

    // update child pointers
    node->left = left_child->right;
    if (left_child->right != NULL) {
        left_child->right->parent = node;
    }
    left_child->right = node;
    node->parent = left_child;
}


/* colour swapper */
void swapColour(node_t *n1, node_t *n2) {
    int tmp = n1->colour;
    n1->colour = n2->colour;
    n2->colour = tmp;
}


/* function that find a specific node of a key in the tree*/
node_t *search(tree_t *tree, void *key, int (*cmp)(const void *, const void *)) {

    // use standard b-tree search algorithm
    node_t *current = tree->root;

    while (current != NULL) {
        // compare key's with cmp function pointer
        int comparison_result = cmp(key, current->key);

        // if keys match, return the current node
        if (comparison_result == 0) {
            return current;

        // if key is smaller, search left subtree
        } else if (comparison_result < 0) {
            current = current->left;

        // if key is greater, search right subtree
        } else {
            current = current->right;
        }
    }

    // if key not found, return NULL
    return NULL;
}


/* function that deletes a specific key from the tree */
int delete(tree_t *tree, void *key, int (*cmp)(const void *, const void *)) {
    
    // search for the node with the given key
    node_t *node = search(tree, key, cmp);

    // if node is not found, return FALSE
    if (node == NULL) {
        return FALSE;
    }

    // store the colour of the node to delete
    int delete_node_colour = node->colour;

    // if the node has has 0 or 1 children, delete and replace with child
    if (node->left == NULL) {
        replaceNode(tree, node, node->right);
    } else if (node->right == NULL) {
        replaceNode(tree, node, node->left);
    } else {
        // if the node has two children, find its successor and replace it
        node_t *successor = minimum(node->right);

        // get the successor's color before deleting it
        int successor_color = successor->colour;

        // if the successor is not a child of the node being deleted,
        // replace it with its right child and update its parent
        if (successor->parent != node) {
            replaceNode(tree, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }

        // replace the node being deleted with its successor and update its parent
        replaceNode(tree, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
        successor->colour = node->colour;
        node = successor;
        delete_node_colour = successor_color;
    }

    // if the node we deleted was black, we need to fix the tree
    if (delete_node_colour == BLACK) {
        correctTree(tree, node->parent);
    }

    // free the memory used by the node
    free(node);
}


/* function that replaces the target with the source nodes */
void replaceNode(tree_t *tree, node_t *trgt, node_t *src) {
    if (trgt->parent == NULL) {
        tree->root = src;
    } else if (trgt == trgt->parent->left) {
        trgt->parent->left = src;
    } else {
        trgt->parent->right = src;
    }
    if (src != NULL) {
        src->parent = trgt->parent;
    }
}

/* minimum function that moves the current node to the left (smaller) */
node_t *minimum(node_t *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}


/* function that prints the tree in order*/
void print_in_order(node_t *node, void (*print)(const void *)) { 

    // check if null
    if (node == NULL) {
        return;
    }

    // recursive in order printing
    print_in_order(node->left, print);
    print(node->key);
    print_in_order(node->right, print);

}