
#include <ctype.h>
#include "trie.h"

#include <stdlib.h>
#include <string.h>

//Static helpers

/*
 * Determine what index position the item needs depending on its type: alphabetical, numeric, or _.
 */
static int char_to_index(char item) {
    if (islower(item)) {
        return item - 'a';
    } else if (isdigit(item)) {
        return item - '0';
    } else if (item == '_') {
        return 36;
    }
    return -1;
}

static TrieNode *trie_create_node(){
    //Allocate memory for a new TrieNode | cast since malloc returns a void
    TrieNode *new_node = malloc(sizeof(TrieNode));
    if (new_node == NULL) {
        return NULL;
    }
    memset(new_node->children, 0, sizeof(new_node->children));
    new_node->is_leaf = false;
    return new_node;
}

static bool trie_has_children(TrieNode *node) {
    for (int i=0; i < TRIE_ALPHABET_SIZE; i++) {
        //Any non-null slot is found
        if (node->children[i] != NULL){
            return true;
        }
    }
    //Any null slot is found
    return false;
}

static void trie_free_nodes(TrieNode *node) {
    //Null guard
    if (node == NULL) {
        return;
    }
    //Recurse into each child node
    for (int i=0; i< TRIE_ALPHABET_SIZE; i++) {
        trie_free_nodes(node->children[i]);
    }
    free(node);
}

static bool trie_delete_recursive (TrieNode *node, const char *c, int depth) {
    //Base case | reached end of key
    if (c[depth] == '\0') {
        node->is_leaf = false;
        return !trie_has_children(node);
    }
    int char_index = char_to_index(c[depth]);
    bool can_free = trie_delete_recursive(node->children[char_index], c, depth+1);
    if (can_free) {
        free(node->children[char_index]);
        node->children[char_index] = NULL;
    }
    if (!(trie_has_children(node)) && !(node->is_leaf)) {
        return true;
    }
    return false;
}

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
int trie_insert(Trie *t, const char *data) {
    //Null guard | return -1 instead of null due to function return
    if (t == NULL || data == NULL) {
        return -1;
    }
    TrieNode *current_index = t->root;
    //Iterate through trie
    for (int i = 0; data[i] != '\0'; i++) {
        //Find index position
        int char_index = char_to_index(data[i]);
        if (char_index == -1) {
            return -1;
        }
        //Check if specified index is NOT filled
        if (current_index->children[char_index] == NULL) {
            TrieNode *next_leaf = trie_create_node();
            //Malloc failed
            if (next_leaf == NULL) {
                return -1;
            }
            //Assign leaf to the index
            current_index->children[char_index] = next_leaf;
            //Move current index to the next leaf
            current_index = current_index->children[char_index];
        //Index is filled
        }else {
            //Char (node) is already created | Move to the next position
            current_index = current_index->children[char_index];
        }
    }
    //Last char is the last leaf
    current_index->is_leaf = true;
    return 0;
}
//Check if the exact key exists in the trie.
bool trie_search(Trie *tree, const char *c) {
    //Null guards
    if (tree == NULL || c == NULL) {
        return false;
    }
    TrieNode *search_node = tree->root;

    for (int i=0; c[i] != '\0'; i++) {
        int char_index = char_to_index(c[i]);
        if (char_index == -1) {
            return false;
        }
        //Specified index is not filled
        if (search_node->children[char_index] == NULL) {
            return false;
        }
        //Keep searching
        search_node = search_node->children[char_index];
    }
    //Check the leaf for the item
    return search_node->is_leaf;
}
//Check if anything "does" start with the specific "string"
bool trie_pre_fix_search(Trie *t, const char *c) {
    //Null guards
    if (t == NULL || c == NULL) {
        return false;
    }
    TrieNode *prefix_search_node = t->root;
    for (int i=0; c[i] != '\0'; i++) {
        int char_index = char_to_index(c[i]);
        if (char_index == -1) {
            return false;
        }
        //Encountered a null node | Prefix is not found
        if (prefix_search_node->children[char_index] == NULL) {
            return false;
        }
        //Continue searching
        prefix_search_node = prefix_search_node->children[char_index];
    }
    //No null nodes encountered | prefix exists
    return true;
}
int trie_delete_key(Trie *t, const char *c) {
    //Null guards
    if (t == NULL || c == NULL) {
        return -1;
    }
    TrieNode *find_key_node = t->root;
    for (int i=0; c[i] != '\0'; i++) {
        int char_index = char_to_index(c[i]);
        if (char_index == -1) {
            return -1;
        }
        //Haven't found the leaf, Continue searching
        if (find_key_node->children[char_index] != NULL) {
            find_key_node = find_key_node->children[char_index];
        //Node is null and we can't free it
        } else {
            return -1;
        }
    }
    if (find_key_node->is_leaf != true) {
        return -1;
    }
    //recursive call
    trie_delete_recursive(t->root, c, 0);
    return 0;
}
int trie_delete_tree(Trie *tree){
    //Null guard 
    if (tree == NULL){
    	return -1;
    }
    trie_free_nodes(tree->root);
    tree->root= NULL;
    return 0;
}





