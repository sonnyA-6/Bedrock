cmake_minimum_required(VERSION 4.2)
project(bedrock C)
set(CMAKE_C_STANDARD 11)
add_library(bedrock STATIC
        src/stack.c
        src/bst.c
        src/trie.c
        src/db.c
)
target_include_directories(bedrock PUBLIC include/)
add_executable(test_stack tests/test_stack.c)
target_link_libraries(test_stack bedrock)
