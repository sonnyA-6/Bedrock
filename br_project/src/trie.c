
#include <ctype.h>
#include "trie.h"

#include <stdlib.h>
#include <string.h>


int trie_init(Trie *tree) {
    if (tree == NULL) {
        return -1;
    }
    //Create root
    TrieNode *root = trie_create_node();
    if (root == NULL)  {
        return -1;
    }
    tree->root = root;
    return 0;
}
int trie_insert(Trie *t, const char *data);
bool trie_search(Trie *tree, const char *c);
bool trie_pre_fix_search(Trie *t, const char *c);
int trie_delete_key(Trie *t, const char *c);
int trie_delete_tree(Trie *tree);
TrieNode *trie_create_node(){
    //Allocate memory for a new TrieNode | cast since malloc returns a void
    TrieNode *new_node = malloc(sizeof(TrieNode));
    if (new_node == NULL) {
        return NULL;
    }
    memset(new_node->children, 0, sizeof(new_node->children));
    new_node->is_leaf = false;
    return new_node;
}

/*
 * Determine what index position the item needs depending on its type: alphabetical, numeric, or _.
 */
int char_to_index(char item) {
    if (islower(item)) {
        return item - 'a';
    } else if (isdigit(item)) {
        return item - '0';
    } else if (item == '_') {
        return 36;
    }
    return -1;
}