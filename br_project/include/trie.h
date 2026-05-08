
#ifndef BEDROCK_TRIE_H
#define BEDROCK_TRIE_H
#include <stdbool.h>
#define TRIE_ALPHABET_SIZE 38

typedef struct TrieNode{
    struct TrieNode *children[TRIE_ALPHABET_SIZE];
    bool is_leaf;
}TrieNode;

typedef struct Trie {
    TrieNode *root;
}Trie;


int trie_init(Trie *tree);
int trie_insert(Trie *t, const char *data);
bool trie_search(Trie *tree, const char *c);
bool trie_pre_fix_search(Trie *t, const char *c);
int trie_delete_key(Trie *t, const char *c);
int trie_delete_tree(Trie *tree);
int char_to_index(char item);
TrieNode *trie_create_node();
#endif //BEDROCK_TRIE_H
