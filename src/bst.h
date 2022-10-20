/* bst.h */

#define DATA_SIZE 20

typedef struct node {
    long key;
    char data[DATA_SIZE];

    struct node *left;
    struct node *right;
} node_t;

node_t *search(node_t *p, long key);
node_t *insert(node_t *p, long key, char *data);
node_t *find_min(node_t *p);
node_t *remove_min(node_t *p);
node_t *remove_item(node_t *p, long key);
void free_tree(node_t *p);
void print_tree(node_t *p);
