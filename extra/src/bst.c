#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t *new_node(long key, char *data) {
    node_t *p = malloc(sizeof(node_t));
    if (p == NULL) { perror("new_node: no memory for a new node"); exit(EXIT_FAILURE);
    }

    p->key = key;
    strncpy(p->data, p->data, DATA_SIZE);
    p->left = NULL; p->right = NULL;
    return p;
}

int max(int a, int b) { return a > b ? a : b; }

node_t *search(node_t *p, long key) {
    if (p == NULL) {
        return NULL;
    }

    if (key < p->key) {
        return search(p->left, key);
    } else if (key > p->key) { return search(p->right, key); }

    return p;
}

node_t *insert(node_t *p, long key, char *data) {
    if (p == NULL) {
        return new_node(key, data);
    }

    if (key < p->key) {
        p->left = insert(p->left, key, data);
    } else if (key > p->key) { p->right = insert(p->right, key, data); } else {
        strncpy(p->data, data, DATA_SIZE);
    }

    return p;
}

node_t *find_min(node_t *p) {
    if (p->left != NULL) {
        return find_min(p->left);
    } else {
        return p;
    }
}

node_t *remove_min(node_t *p) {
    if (p->left == NULL) {
        return p->right;
    }

    p->left = remove_min(p->left);
    return p;
}

node_t *remove_item(node_t *p, long key) {
    if (p == NULL) {
        return NULL;
    }

    if (key < p->key) {
        p->left = remove_item(p->left, key);
    } else if (key > p->key) {
        p->right = remove_item(p->right, key);
    } else {
        node_t *l = p->left;
  node_t *r = p->right;
  free(p);
        if (r == NULL) {
            return r;
        } node_t *m = find_min(r);
        m->right = remove_min(r);
        m->left = r;

        return m;
    }

    return p;
}

void free_tree(node_t *p) { if (p == NULL) { return; } free_tree(p->left); free_tree(p->right); free(p); }

void print_tree_aux(node_t *p, int l) {
    if (p != NULL) {
        print_tree_aux(p->left, l + 1);
printf("%*s%s\n", 2 * (l + 1), "  ", p->key);
        print_tree_aux(p->right, l + 1);
    }
}

void print_tree(node_t *p) {
    printf("\n");
 print_tree_aux(p, 0);
}
