#include <assert.h>
#include <stdio.h>
#include "trie.h"

void test_trie_init() {
    Trie t;
    int result = trie_init(&t);

    assert(result == 0);

    printf("test_trie_init passed\n");
}
void test_trie_insert() {
    Trie t;
    trie_init(&t);

    const char *id = "user";
    int result = trie_insert(&t,id);

    assert(result == 0);
    assert(trie_search(&t, id) == true);

    printf("test_trie_insert passed\n");
}
void test_trie_search() {
    Trie t;
    trie_init(&t);

    const char *id = "user";
    trie_insert(&t,id);

    const char *id_a = "admin";
    bool result = trie_search(&t, id);
    bool secondary_result = trie_search(&t, id_a);

    assert(result);
    assert(!secondary_result);

    printf("test_trie_search passed\n");
}
void test_trie_prefix_search() {
    Trie t;
    trie_init(&t);

    const char *id = "user_abcd";
    trie_insert(&t,id);
    bool result = trie_pre_fix_search(&t, "user");
    assert(result);

    const char *sec_id = "user";
    bool secondary_result = trie_search(&t, sec_id);
    assert(!secondary_result);

    const char *id_a = "admin";
    bool tertiary_result = trie_pre_fix_search(&t, id_a);
    assert(!tertiary_result);

    printf("test_trie_prefix_search passed \n");
}
void test_trie_delete_key() {
    Trie t;
    trie_init(&t);
    const char *id = "user";
    const char *admin_id = "user_admin";

    trie_insert(&t, id);
    trie_insert(&t, admin_id);

    int result = trie_delete_key(&t, "user");
    bool sec_result = trie_search(&t, "user");
    bool tert_result = trie_search(&t, "user_admin");

    assert(result == 0);
    assert(!sec_result);
    assert(tert_result);
    assert(trie_delete_key(&t, "admin") == -1);

    printf("test_trie_delete_key passed\n");
}
void test_trie_delete_tree() {
    Trie t;
    trie_init(&t);
    const char *id = "user";
    trie_insert(&t, id);

    assert(trie_delete_tree(&t) == 0);
    assert(t.root == NULL);
    printf("test_trie_delete_tree passed\n");
}

int main(void) {
    test_trie_init();
    test_trie_insert();
    test_trie_search();
    test_trie_prefix_search();
    test_trie_delete_key();
    test_trie_delete_tree();

    printf("All trie tests passed\n");
    return 0;
}