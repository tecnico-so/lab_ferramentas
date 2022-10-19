/* bst.h */

#define DATA_SIZE  20

typedef struct node {
    long key;
    char data[DATA_SIZE];

    struct node* left;
    struct node* right;
} node;

node *search(node *p, long key);
node *insert(node *p, long key, char *data);
node *find_min(node *p);
node *remove_min(node *p);
node *remove_item(node *p, long key);
void free_tree(node *p);
void print_tree(node *p);
