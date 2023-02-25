#include <stdio.h>

#include "rbtree.h"
#include "integer.h"

int
main(int argc, char *argv[]) {
    tree_t tree = {NULL};
    insert(&tree, &(int){3}, int_cmp);
    insert(&tree, &(int){1}, int_cmp);
    insert(&tree, &(int){4}, int_cmp);
    insert(&tree, &(int){5}, int_cmp);
    insert(&tree, &(int){2}, int_cmp);
    print_in_order(tree.root, int_print);
    printf("\n");
    return 0;
}