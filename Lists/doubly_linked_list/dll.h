// doubly linked list header

#ifndef DLL_H
#define DLL_H

#include "stdbool.h"


enum DLL_TYPES { 
    integer, 
    decimal, 
    character, 
    string 
};

typedef struct node {
    void *value;        // IMPORTANT: value can be pointer to int, char, double or string
    struct node *next;
    struct node *prev;
} node;

typedef struct dll {
    node *head;
    node *tail;
    unsigned int size;
    enum DLL_TYPES value_type;
} dll;

node *dll_create_node(void *);
dll *dll_create_list(enum DLL_TYPES);
void dll_prepend(dll *, node *);
void dll_append(dll *, node *);
void dll_insert_at_position(dll *, unsigned int,  node *);
void dll_delete_node(dll *, unsigned int, bool);
node *dll_get_node_at_position(dll *, unsigned int);
node *dll_find_first_node_with_value(dll *, void *, int *);
void dll_print_node(enum DLL_TYPES value_type, node *anode);
void dll_print(dll *);
void dll_empty_list(dll *, bool);
dll *dll_concat_lists(dll *, dll *);
unsigned int dll_count_value(dll *list, void *value);
dll *dll_reverse_list(dll *list);
dll *dll_slice(dll *list, unsigned int start, unsigned int end);
bool dll_node_values_equal(enum DLL_TYPES value_type, node *first, node *second);
bool dll_equal(dll *first, dll *second);

#endif
