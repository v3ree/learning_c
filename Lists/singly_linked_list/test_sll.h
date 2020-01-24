#ifndef TEST_SLL_H
#define TEST_SLL_H

#include "sll.h"

sll *__test_helper_make_sll_sut(enum SLL_TYPES, unsigned int);
void test_sll_create_node();
void test_sll_create_list();
void test_sll_prepend_to_nonempty_list();
void test_sll_prepend_to_empty_list();
void test_sll_append_to_nonempty_list();
void test_sll_append_to_empty_list();
void test_sll_insert_at_position();
void test_sll_delete_node();
void test_sll_get_node_before_position();
void test_sll_get_node_at_position();
void test_sll_find_first_node_with_value();
void test_sll_print();
void test_sll_empty_list();
void test_sll_concat_lists();
void test_sll_count_value();
void test_sll_slice();
void test_sll_node_values_equal();
void test_sll_equal();

#endif
