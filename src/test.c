#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    node_t *root = NULL;
    int debug = 0;
    char c = '0';
    int k = 0;

    printf("> ");
    while (scanf("%c", &c) == 1 && c != 'q') {
        if (c == 'a') {
            scanf("%d", &k);
            root = insert(root, k, "empty");
            if (debug) {
                print_tree(root);
            }
        } else if (c == 's') {
            scanf("%d", &k);
            node_t *n = search(root, k);
            if (n)
                printf("%ld data=\"%s\"\n", n->key, n->data);
        } else if (c == 'r') {
            scanf("%d", &k);
            root = remove_item(root, k);
            if (debug) {
                print_tree(root);
            }
        } else if (c == 'd') {
            debug = 1 - debug;
        } else if (c == 'p') {
            print_tree(root);
        }

        if (c == '\n') {
            printf("> ");
        }
    }

    free_tree(root);

    return 0;
}
