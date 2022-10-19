#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

node* new_node(long key, char *data)
{
    node* p = malloc(sizeof(node));
    if(p == NULL)
    {
        perror("new_node: no memory for a new node");
        exit(EXIT_FAILURE);
    }

    p->key = key;
    strncpy(p->data, data, DATA_SIZE);
    p->left  = NULL;
    p->right = NULL;

    return p;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

node* search(node* p, long key)
{
    if ( !p )
        return NULL;

    if ( key < p->key )
        return search(p->left, key);
    else if ( key > p->key )
        return search(p->right, key);
    else
        return p;
}

node* insert(node* p, long key, char *data)
{
    if ( !p )
        return new_node(key, data);

    if ( key < p->key )
        p->left = insert(p->left, key, data);
    else if ( key > p->key )
        p->right = insert(p->right, key, data);
    else 
        strncpy(p->data, data, DATA_SIZE);

    return p;
}

node* find_min(node* p)
{
    if ( p->left != NULL )
        return find_min(p->left);
    else
        return p;
}

node* remove_min(node* p)
{
    if ( p->left == NULL )
        return p->right;

    p->left = remove_min(p->left);
    return p;
}

node* remove_item(node* p, long key)
{
    if ( !p )
        return NULL;

    if ( key < p->key )
        p->left = remove_item(p->left, key);
    else if ( key > p->key )
        p->right = remove_item(p->right, key);
    else
    {
        node* l = p->left;
        node* r = p->right;
        node* m;
        free(p);

        if ( r == NULL )
            return l;

        m = find_min(r);
        m->right = remove_min(r);        
        m->left = l;

        return m;
    }

    return p;
}

void free_tree(node* p)
{
    if ( !p )
        return;

    free_tree(p->left);
    free_tree(p->right);
    free(p);
}

void print_tree_2(node* p, int l)
{
  if (p) {
    print_tree_2(p->left, l+1);
    printf("%*s%ld\n", 2*(l+1), "  " , p->key);
    print_tree_2(p->right, l+1);
  }
}

void print_tree(node* p)
{
  printf("\n");
  print_tree_2(p, 0);
}

