#ifndef TEST_SLL_H
#define TEST_SLL_H

#include "dll.h"

dll *__test_helper_make_dll_sut(enum DLL_TYPES, unsigned int);
void test_dll_create_node();
void test_dll_create_list();
void test_dll_prepend_to_nonempty_list();
void test_dll_prepend_to_empty_list();
void test_dll_append_to_nonempty_list();
void test_dll_append_to_empty_list();
void test_dll_insert_at_position();
void test_dll_delete_node();
void test_dll_get_node_at_position();
void test_dll_find_first_node_with_value();
void test_dll_print();
void test_dll_empty_list();
void test_dll_concat_lists();
void test_dll_count_value();
void test_dll_reverse();
void test_dll_slice();
void test_dll_node_values_equal();
void test_dll_equal();

#endif
