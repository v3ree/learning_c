// test doubly linked list

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "test_dll.h"
#include "dll.h"


int main()
{
    test_dll_print();
    test_dll_create_node();
    test_dll_prepend_to_nonempty_list();
    test_dll_prepend_to_empty_list();
    test_dll_append_to_nonempty_list();
    test_dll_append_to_empty_list();
    test_dll_insert_at_position();
    test_dll_delete_node();
    test_dll_get_node_at_position();
    test_dll_find_first_node_with_value();
    test_dll_empty_list();
    test_dll_count_value();
    test_dll_reverse();
    test_dll_slice();
    test_dll_node_values_equal();
    test_dll_equal();
}


dll *__test_helper_make_dll_sut(enum DLL_TYPES value_type, unsigned int size)
{
    dll *sut = dll_create_list(value_type);

    switch (value_type) {
        case integer:
            for (unsigned int i = 0; i < size; i++) {
                int *v = (int *) malloc(sizeof(int));
                *v = (int) i;
                dll_append(sut, dll_create_node(v));
            }
            // printf("TEST: i-value dll created successfully!\n");
            break;
        case decimal:
            for (unsigned int i = 0; i < size; i++) {
                double *v = (double *) malloc(sizeof(double));
                *v = (double) i;
                dll_append(sut, dll_create_node(v));
            }
            // printf("TEST: d-value dll created successfully!\n");
            break;
        case character:
            for (unsigned int i = 0; i < size; i++) {
                char *v = (char *) malloc(sizeof(char));
                *v = 'v';
                dll_append(sut, dll_create_node(v));
            }
            // printf("TEST: c-value dll created successfully!\n");
            break;
        case string:
            for (unsigned int i = 0; i < size; i++) {
                char *v = (char *) malloc(sizeof(char) * 4);
                strcpy(v, "vvv");
                dll_append(sut, dll_create_node(v));
            }
            // printf("TEST: s-value dll created successfully!\n");
            break;
        default:
            return NULL;
    }
    return sut;
}


void test_dll_create_node()
{
    node *new_node;

    int ival = 100;
    new_node = dll_create_node(&ival);
    assert(*((int *) new_node->value) == ival);
    assert(!new_node->next);
    free(new_node);

    double dval = 100.0;
    new_node = dll_create_node(&dval);
    assert(*((double *) new_node->value) == dval);
    assert(!new_node->next);
    free(new_node);

    char cval = 100.0;
    new_node = dll_create_node(&cval);
    assert(*((char *) new_node->value) == cval);
    assert(!new_node->next);
    free(new_node);

    char sval[5] = "test";
    new_node = dll_create_node(&sval);
    assert(!strcmp((char *) new_node->value, sval));
    assert(!new_node->next);
    free(new_node);

    printf("Test 'create node': PASSED!\n");
}


void test_dll_create_list()
{
    dll *new_list;

    new_list = dll_create_list(integer);
    assert(new_list);
    assert(!new_list->size);
    assert(!new_list->head);
    assert(new_list->value_type == integer);
    free(new_list);

    new_list = dll_create_list(decimal);
    assert(new_list);
    assert(!new_list->size);
    assert(!new_list->head);
    assert(new_list->value_type == decimal);
    free(new_list);

    new_list = dll_create_list(character);
    assert(new_list);
    assert(!new_list->size);
    assert(!new_list->head);
    assert(new_list->value_type == character);
    free(new_list);

    new_list = dll_create_list(string);
    assert(new_list);
    assert(!new_list->size);
    assert(!new_list->head);
    assert(new_list->value_type == string);
    free(new_list);
    
    printf("Test 'create list': PASSED!\n");
}


void test_dll_prepend_to_nonempty_list()
{
    const unsigned int sut_size = 3;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);
    unsigned int initial_sut_size = sut->size;

    int *n = (int *) malloc(sizeof(int));
    *n = 33;
    *((int *) (sut->head->value)) = *n + 1;
    
    dll_prepend(sut, dll_create_node(n));
    unsigned int final_sut_size = sut->size;

    assert(initial_sut_size == sut_size);
    assert(final_sut_size == initial_sut_size + 1);
    assert(*((int *) (sut->head->value)) == *n);
    assert(*((int *) (sut->head->next->value)) == *n + 1);

    // clean-up
    initial_sut_size = 0;
    final_sut_size = 0;
    dll_empty_list(sut, true);
    free(sut);

    printf("Test 'prepend to non-empty list': PASSED!\n");
}


void test_dll_prepend_to_empty_list()
{
    const unsigned int sut_size = 0;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);
    unsigned int initial_sut_size = sut->size;

    int *n = (int *) malloc(sizeof(int));
    *n = 33;
    
    dll_prepend(sut, dll_create_node(n));
    unsigned int final_sut_size = sut->size;

    assert(initial_sut_size == sut_size);
    assert(final_sut_size == initial_sut_size + 1);
    assert(*((int *) (sut->head->value)) == *n);

    // clean-up
    initial_sut_size = 0;
    final_sut_size = 0;
    dll_empty_list(sut, true);
    free(sut);

    printf("Test 'prepend to empty list': PASSED!\n");
}


void test_dll_append_to_nonempty_list()
{
    const unsigned int sut_size = 1;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);
    unsigned int initial_sut_size = sut->size;

    int *n = (int *) malloc(sizeof(int));
    *n = 33;
    *((int *) (sut->head->value)) = *n - 1;
    
    dll_append(sut, dll_create_node(n));
    unsigned int final_sut_size = sut->size;

    assert(initial_sut_size == sut_size);
    assert(final_sut_size == initial_sut_size + 1);
    assert(*((int *) (sut->head->value)) == *n - 1);
    assert(*((int *) (sut->head->next->value)) == *n);

    // clean-up
    initial_sut_size = 0;
    final_sut_size = 0;
    dll_empty_list(sut, true);
    free(sut);

    printf("Test 'append to non-empty list': PASSED!\n");
}


void test_dll_append_to_empty_list()
{
    const unsigned int sut_size = 0;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);
    unsigned int initial_sut_size = sut->size;

    int *n = (int *) malloc(sizeof(int));
    *n = 33;
    
    dll_prepend(sut, dll_create_node(n));
    unsigned int final_sut_size = sut->size;

    assert(initial_sut_size == sut_size);
    assert(final_sut_size == initial_sut_size + 1);
    assert(*((int *) (sut->head->value)) == *n);

    // clean-up
    initial_sut_size = 0;
    final_sut_size = 0;
    dll_empty_list(sut, true);
    free(sut);

    printf("Test 'append to empty list': PASSED!\n");
}


void test_dll_insert_at_position()
{
    const unsigned int sut_size = 3;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);
    int *n = (int *) malloc(sizeof(int));
    *n = 33;

    dll_insert_at_position(sut, 1, dll_create_node(n));

    assert(sut->size == sut_size + 1);
    assert(*((int* ) dll_get_node_at_position(sut, 1)->value) == *n);

    // clean-up
    dll_empty_list(sut, true);
    free(sut);

    printf("Test 'insert at position': PASSED!\n");
}


void test_dll_delete_node()
{
    const unsigned int sut_size = 3;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);

    dll_delete_node(sut, 1, true);

    assert(sut->size == sut_size - 1);
    assert(!sut->head->next->next);

    dll_delete_node(sut, 1, true);
    assert(sut->size == sut_size - 2);
    assert(!sut->head->next);
    
    dll_delete_node(sut, 0, true);
    assert(sut->size == sut_size - 3);
    assert(!sut->head);

    // clean-up
    dll_empty_list(sut, true);
    free(sut);

    printf("Test 'delete node': PASSED!\n");
}


void test_dll_get_node_at_position()
{
    const unsigned int sut_size = 2;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);

    assert(sut->head == dll_get_node_at_position(sut, 0));
    assert(sut->head->next == dll_get_node_at_position(sut, 1));
    assert(!dll_get_node_at_position(sut, 2));

    // clean-up
    dll_empty_list(sut, true);
    free(sut);

    printf("Test 'get node at position': PASSED!\n");
}


void test_dll_find_first_node_with_value()
{
    const unsigned int sut_size = 3;
    dll *isut = __test_helper_make_dll_sut(integer, sut_size);
    dll *dsut = __test_helper_make_dll_sut(decimal, sut_size);
    dll *csut = __test_helper_make_dll_sut(character, sut_size);
    dll *ssut = __test_helper_make_dll_sut(string, sut_size);

    int position;
    int i = 1;
    double d = 2.0;
    char c = 'v';
    char str[4] = "vvv";

    assert(dll_find_first_node_with_value(isut, &i, &position));
    assert(position == 1);
    assert(dll_find_first_node_with_value(dsut, &d, &position));
    assert(position == 2);
    assert(dll_find_first_node_with_value(csut, &c, &position));
    assert(position == 0);
    assert(dll_find_first_node_with_value(ssut, str, &position));
    assert(position == 0);

    // clean-up
    position = 0; i = 0; d = 0; c = 0;
    dll_empty_list(isut, true);
    dll_empty_list(dsut, true);
    dll_empty_list(csut, true);
    dll_empty_list(ssut, true);
    free(isut);
    free(dsut);
    free(csut);
    free(ssut);

    printf("Test 'get first node with value': PASSED!\n");
}


void test_dll_print()
{
    const unsigned int sut_size = 2;
    dll *sut = __test_helper_make_dll_sut(string, sut_size);
    dll_print(sut);
    printf("[0] vvv\n[1] vvv\n");
    printf("Please check if the texts printed above are \
identical, then press ENTER.");
    getchar();

    printf("Test 'print list': PASSED!\n");
}


void test_dll_empty_list()
{
    const unsigned int sut_size = 10;
    dll *sut = __test_helper_make_dll_sut(integer, sut_size);
    assert(sut->size == sut_size);
    assert(sut->head);

    dll_empty_list(sut, true);

    assert(!sut->size);
    assert(!sut->head);

    free(sut);

    printf("Test 'empty list': PASSED!\n");
}


void test_dll_concat_lists()
{
    const unsigned int sut_size = 10;
    dll *sut1 = __test_helper_make_dll_sut(integer, sut_size);
    dll *sut2 = __test_helper_make_dll_sut(integer, sut_size);

    dll *sut_final = dll_concat_lists(sut1, sut2);

    assert(sut1->head);
    assert(sut2->head);
    assert(sut_final->head);
    assert(sut_final->size == sut1->size + sut2->size);
    assert(dll_get_node_at_position(sut_final, sut_final->size - 1));

    // clean-up
    dll_empty_list(sut_final, true);
    free(sut1);
    free(sut2);
    free(sut_final);

    printf("Test 'concatenate lists': PASSED!\n");
}


void test_dll_count_value()
{
    const unsigned int sut_size = 10;
    dll *sut1 = __test_helper_make_dll_sut(integer, sut_size);

    int *v = (int *) malloc(sizeof(int));
    *v = 3;
    node *new_node = dll_create_node(v);

    assert(dll_count_value(sut1, v) == 1);
    dll_append(sut1, new_node);
    assert(dll_count_value(sut1, v) == 2);

    // clean-up
    dll_empty_list(sut1, true);
    free(sut1);

    printf("Test 'count value': PASSED!\n");
}


void test_dll_reverse()
{
    dll *sut1 = __test_helper_make_dll_sut(integer, 10);
    dll *sut2 = dll_reverse_list(sut1);
    dll *sut3 = dll_reverse_list(sut2);
    
    assert(!dll_equal(sut1, sut2));
    assert(dll_equal(sut1, sut3));

    // clean-up
    dll_empty_list(sut1, true);
    dll_empty_list(sut2, true);
    dll_empty_list(sut3, true);
    free(sut1);
    free(sut2);
    free(sut3);

    printf("Test 'reverse': PASSED!\n");
}


void test_dll_slice()
{
    dll *sut1 = __test_helper_make_dll_sut(integer, 10);
    dll *sut2 = __test_helper_make_dll_sut(integer, 5);
    dll *sut3 = dll_slice(sut1, 0, 5);

    assert(dll_equal(sut2, sut3));

    // clean-up
    dll_empty_list(sut1, true);
    dll_empty_list(sut2, true);
    dll_empty_list(sut3, true);
    free(sut1);
    free(sut2);
    free(sut3);

    printf("Test 'slice': PASSED!\n");
}


void test_dll_node_values_equal()
{
    int *v1 = (int *) malloc(sizeof(int));
    int *v2 = (int *) malloc(sizeof(int));
    *v1 = 1;
    *v2 = 2;
    node *node_v1 = dll_create_node(v1);
    node *node_v2 = dll_create_node(v2);

    assert(!dll_node_values_equal(integer, node_v1, node_v2));

    *v2 = 1;
    assert(dll_node_values_equal(integer, node_v1, node_v2));

    free(v1);
    free(v2);
    free(node_v1);
    free(node_v2);

    printf("Test 'equal node values': PASSED!\n");
}


void test_dll_equal()
{
    dll *sut1 = __test_helper_make_dll_sut(integer, 10);
    dll *sut2 = __test_helper_make_dll_sut(integer, 10);

    assert(dll_equal(sut1, sut2));

    dll_delete_node(sut2, 3, true);
    assert(!dll_equal(sut1, sut2));

    // clean-up
    dll_empty_list(sut1, true);
    dll_empty_list(sut2, true);
    free(sut1);
    free(sut2);

    printf("Test 'equal lists': PASSED!\n");
}
