#include <ctype.h>
#include "bst.h"
#include <stdlib.h>
#include <string.h>

//Main functions
int bst_init(BST *tree){
    //Null guard
    if (tree == NULL){
        return -1;
    }
    //Successful initialization
    tree->root = NULL;
    return 0;
}

int bst_insert(BST *tree, const int32_t data, void *payload){
    //Null guard
    if(tree == NULL || payload == NULL){
        return -1;
    }
    BSTNode *result = bst_insert_recursive(tree->root, data, payload);
    //Node creation failed
    if (result == NULL){
        return -1;
    }
    tree->root = result;
    return 0;

}

BSTNode *bst_search(BST *tree, int32_t data){
    //Null guard
    if(tree == NULL){
        return NULL;
    }
    //Start comparision search at root
    return bst_search_recursive(tree->root, data);

}
//Helper function 
BSTNode *bst_create_node(void){
    //Allocate memory for a new BST node
    BSTNode *new_node = malloc(sizeof(BSTNode));
    if (new_node == NULL){
        return NULL;
    }
    //Temporary assignment placeholders
    new_node->data = 0;
    new_node->payload = NULL;
    new_node->right = NULL;
    new_node->left = NULL;
    
    return new_node;
}

static BSTNode *bst_search_recursive(BSTNode *node, int32_t data){
    //Base case
    if(node == NULL){
        return NULL;
    }
    //Recursively search for the data
    if (data < node->data){
        return bst_search_recursive(node->left, data);
    }else if (data >node->data){
        return bst_search_recursive(node->right, data);
    }else{
        return node;
    }
}

static BSTNode *bst_insert_recursive(BSTNode *node, int32_t data, void *payload){
    //Base case | No nodes created
    if (node == NULL){
        BSTNode *new_tree_node = bst_create_node();
        new_tree_node->data = data;
        new_tree_node->payload = payload;
        return new_tree_node;
    }
    if (data < new_tree_node->data){
        new_tree_node->left = bst_insert_recursive(new_tree_node->left, data, payload);
        return new_tree_node;
    } else if(data == new_tree_node->data){
        //node is equal | Replace with current payload
        new_tree_node->payload = payload;
        return new_tree_node;
    }else{
        new_tree_node->right = bst_insert_recursive(new_tree_node->right, data, payload);
        return new_tree_node;
    }
    
}
