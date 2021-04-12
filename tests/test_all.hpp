//
// Created by duncan on 3/9/21.
//

#ifndef MINI_LISP_TEST_ALL_HPP
#define MINI_LISP_TEST_ALL_HPP

#include "gtest/gtest.h"

// Creates an integer on the heap using the appropriate type casting for C++
// malloc
#define HEAP_INT (int*)malloc(sizeof(int))

// Populates the linked list ll using the vector of integers num_vec and the
// function add_func. Example usage: POPULATE_ALL(dll, num_vec, &DLL_insert);
#define POPULATE_LL(ll, num_vec, add_func) ({                                  \
    int counter{0};                                                            \
    for (auto &i : (num_vec)) {                                                \
        int *i_heap = HEAP_INT;                                                \
        *i_heap = i;                                                           \
        (*(add_func))(ll, i_heap);                                             \
        counter++;                                                             \
        ASSERT_EQ(counter, (ll)->len) << "Length was not "                     \
        "updated correctly";                                                   \
    }                                                                          \
})

// Some vectors of integers to use when creating DLLs
#define NUM_VECS const std::vector<std::vector<int>> num_vecs = { \
        {1, 2, 3, 4}, \
        {1, 2, 3, 4, 5, 6}, \
        {1}, \
        {1, 2}};

#endif //MINI_LISP_TEST_ALL_HPP
