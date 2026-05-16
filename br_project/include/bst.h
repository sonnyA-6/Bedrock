
#ifndef BEDROCK_BST_H
#define BEDROCK_BST_H
#include <stdbool.h>
#include <stdint.h>

typedef struct BSTNode{
    int32_t data;
    void* payload;
    struct BSTNode *right;
    struct BSTNode *left;
}BSTNode;

typedef struct BST {
    struct BSTNode *root;
}BST;


int bst_init(BST *tree);
int bst_insert(BST *tree, const int32_t data, void *payload);
BSTNode* bst_search(BST *tree, int32_t data);
void bst_inorder(BST *tree, void (*callback)(BSTNode *node));
void bst_preorder(BST *tree, void (*callback)(BSTNode *node));
void bst_postorder(BST *tree, void (*callback)(BSTNode *node));
int bst_delete_key(BST *tree, int32_t data);
int bst_delete_tree(BST *tree);

#endif //BEDROCK_BST_H
