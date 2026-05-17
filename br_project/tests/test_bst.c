#include <assert.h>
#include <stdio.h>
#include "bst.h"

//Test helpers
void print_node(BSTNode *node) {
    printf("%d\n", node->data);
    printf("%s\n", node->payload);
}

//Main tests
void test_bst_init() {
    BST tree;
    int result = bst_init(&tree);

    assert(result == 0);
    printf("test_bst_init passed\n");
}

void test_bst_insert() {
    BST tree;
    bst_init(&tree);

    int32_t data = 9;
    char *payload = "test--payload";
    int result = bst_insert(&tree, data, payload);

    assert(result == 0);
    assert(bst_search(&tree, data));

    char *original = "original";
    char *updated = "updated";
    bst_insert(&tree, 9, original);
    bst_insert(&tree, 9, updated);
    BSTNode *found = bst_search(&tree, 9);
    assert(found->payload == updated);

    printf("test_bst_insert passed\n");
}

void test_bst_inorder() {
    BST inorder_tree;
    bst_init(&inorder_tree);

    int32_t nodeA = 15;
    int32_t nodeD = 13;
    int32_t nodeL = 35;

    char *payloadA = "root node";
    char *payloadD = "left node";
    char *payloadL = "right node";

    bst_insert(&inorder_tree, nodeA, payloadA);
    bst_insert(&inorder_tree, nodeD, payloadD);
    bst_insert(&inorder_tree, nodeL, payloadL);

    bst_inorder(&inorder_tree, print_node);

    printf("test_bst_inorder passed\n");
}

void test_bst_preorder() {
    BST preorder_tree;
    bst_init(&preorder_tree);

    int32_t nodeA = 15;
    int32_t nodeD = 13;
    int32_t nodeL = 35;

    char *payloadA = "root node";
    char *payloadD = "left node";
    char *payloadL = "right node";

    bst_insert(&preorder_tree, nodeA, payloadA);
    bst_insert(&preorder_tree, nodeD, payloadD);
    bst_insert(&preorder_tree, nodeL, payloadL);

    bst_preorder(&preorder_tree, print_node);

    printf("test_bst_preorder passed\n");
}

void test_bst_postorder() {
    BST postorder_tree;
    bst_init(&postorder_tree);

    int32_t nodeA = 15;
    int32_t nodeD = 13;
    int32_t nodeL = 35;

    char *payloadA = "root node";
    char *payloadD = "left node";
    char *payloadL = "right node";

    bst_insert(&postorder_tree, nodeA, payloadA);
    bst_insert(&postorder_tree, nodeD, payloadD);
    bst_insert(&postorder_tree, nodeL, payloadL);

    bst_postorder(&postorder_tree, print_node);

    printf("test_bst_postorder passed\n");
}

void test_bst_delete_key() {
    BST delete_key_tree;
    bst_init(&delete_key_tree);

    int32_t nodeA = 15;
    int32_t nodeD = 13;
    int32_t nodeL = 35;

    int32_t nodeJ = 600;

    char *payloadA = "root node";
    char *payloadD = "left node";
    char *payloadL = "right node";

    bst_insert(&delete_key_tree, nodeA, payloadA);
    bst_insert(&delete_key_tree, nodeD, payloadD);
    bst_insert(&delete_key_tree, nodeL, payloadL);

    int result = bst_delete_key(&delete_key_tree,nodeA);
    int secondary_result = bst_delete_key(&delete_key_tree, nodeJ);
    assert(result == 0);
    assert(secondary_result == -1);

    bst_postorder(&delete_key_tree, print_node);
    printf("test_bst_delete_key passed \n");
}

void test_bst_delete_tree() {
    BST delete_tree;
    bst_init(&delete_tree);

    int32_t nodeA = 15;
    int32_t nodeD = 13;
    int32_t nodeL = 35;

    char *payloadA = "root node";
    char *payloadD = "left node";
    char *payloadL = "right node";

    bst_insert(&delete_tree, nodeA, payloadA);
    bst_insert(&delete_tree, nodeD, payloadD);
    bst_insert(&delete_tree, nodeL, payloadL);

    int result = bst_delete_tree(&delete_tree);
    assert(result == 0);
    assert(delete_tree.root == NULL);
    printf("tree deleted successfully\n");
    printf("test_bst_delete_tree passed\n");
}

int main (void) {
    test_bst_init();
    test_bst_insert();
    test_bst_inorder();
    test_bst_preorder();
    test_bst_postorder();
    test_bst_delete_key();
    test_bst_delete_tree();

    printf("All bst tests passed\n");
}