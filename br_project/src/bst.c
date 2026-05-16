#include <ctype.h>
#include "bst.h"
#include <stdlib.h>
#include <string.h>

//Helper function(s) 
static BSTNode *bst_create_node(void){
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
    if (data < node->data){
        node->left = bst_insert_recursive(node->left, data, payload);
        return node;
    } else if(data == node->data){
        //node is equal | Replace with current payload
        node->payload = payload;
        return node;
    }else{
        node->right = bst_insert_recursive(node->right, data, payload);
        return node;
    }
    
}
static BSTNode *bst_delete_key_recursive(BSTNode *node, int32_t data){
    
    if(node == NULL){
        return NULL;
    }
    if(data < node->data){
        node->left = bst_delete_key_recursive(node->left, data);
        return node;
    }
    if(data > node->data){
        node->right = bst_delete_key_recursive(node->right, data);
        return node;
    }
    if (data == node->data){
        //no children | Free the memory & return null
        if (node->left == NULL && node->right == NULL){
            free(node);
            return NULL;
        //one child | free memory & return the surviving child
        } else if(node->left == NULL || node ->right == NULL){
            BSTNode *surviving_child;
            if(node->left == NULL){
                surviving_child = node->right;
                free(node);
                return surviving_child;
            }else{
                surviving_child = node->left;
                free(node);
                return surviving_child;
            }
        //Two Children | Find succesor, copy the values, delete succesor
        }else{
            BSTNode *find_successor = bst_min_node(node->right);
            node->data = find_successor->data;
            node->payload = find_successor->payload;
            node->right = bst_delete_key_recursive(node->right, find_successor->data);
            return node;
        }
    }
    return node;
}

static void bst_inorder_recursive(BSTNode *node, void (*callback)(BSTNode *node)){
    //Null guard
    if(node == NULL){
        return;
    }
    //Traverse the tree in-order
    bst_inorder_recursive(node->left, callback);
    callback(node);
    bst_inorder_recursive(node->right, callback);
}

static void bst_pre_order_recursive(BSTNode *node, void (*callback)(BSTNode *node)){
    //Null guard
    if(node == NULL){
        return;
    }
    //Traverse in pre-order
    callback(node);
    bst_pre_order_recursive(node->left, callback);
    bst_pre_order_recursive(node->right, callback);
}

static void bst_post_order_recursive(BSTNode *node, void (*callback)(BSTNode *node)){
    //Null guard
    if (node == NULL){
        return;
    }
    //Traverse in post-order
    bst_post_order_recursive(node->left, callback);
    bst_post_order_recursive(node->right, callback);
    callback(node);
}

static BSTNode *bst_min_node(BSTNode *node){
    //Base case
    if (node == NULL){
        return NULL;
    }
    if (node->left == NULL){
        return node;
    }
    //Recurse left until the bottom is reached
    return bst_min_node(node->left);
}

static void bst_free_tree(BSTNode *node){
    if (node == NULL){
        return;
    }
    bst_free_tree(node->left);
    bst_free_tree(node->right);
    free(node);
}


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
    // Note: allocation failure during insertion into non-empty tree
    // is not detected. Root node failure is caught above.

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

void bst_inorder(BST *tree, void(*callback)(BSTNode *node)){
    //Null Guard
    if (tree == NULL){
        return;
    }
    //Recurse in-order
    bst_inorder_recursive(tree->root, callback);
}

void bst_preorder(BST *tree, void(*callback)(BSTNode *node)){
    //Null guard
    if(tree == NULL){
        return;
    }
    //Recurse pre-order
    bst_pre_order_recursive(tree->root, callback);
}

void bst_postorder(BST *tree, void(*callback)(BSTNode *node)){
    //Null guard
    if(tree == NULL){
        return;
    }
    //Recurse post-order
    bst_post_order_recursive(tree->root, callback);
}

int bst_delete_key(BST *tree, int32_t data){
    //Null guards
    if(tree == NULL){
        return -1;
    }
    tree->root = bst_delete_key_recursive(tree->root, data);
    //Success | Key has been found and freed
    return 0;
}

int bst_delete_tree(BST *tree){
    if (tree == NULL){
        return -1;
    }
    bst_free_tree(tree->root);
    tree->root = NULL;
    return 0;
}



