// singly linked list header

#ifndef SLL_H
#define SLL_H

#include "stdbool.h"


enum SLL_TYPES { 
	integer, 
	decimal, 
	character, 
	string 
};

typedef struct node {
    void *value;        // IMPORTANT: value can be pointer to int, char, double or string
    struct node *next;
} node;

typedef struct sll {
    node *head;
    unsigned int size;
    enum SLL_TYPES value_type;
} sll;


node *sll_create_node(void *);
sll *sll_create_list(enum SLL_TYPES);
void sll_prepend(sll *, node *);
void sll_append(sll *, node *);
void sll_insert_at_position(sll *, unsigned int,  node *);
void sll_delete_node(sll *, unsigned int, bool);
node *sll_get_node_before_position(sll *, unsigned int);
node *sll_get_node_at_position(sll *, unsigned int);
node *sll_find_first_node_with_value(sll *, void *, int *);
void sll_print_node(enum SLL_TYPES value_type, node *anode);
void sll_print(sll *);
void sll_empty_list(sll *, bool);
sll *sll_concat_lists(sll *, sll *);
unsigned int sll_count_value(sll *list, void *value);
sll *sll_slice(sll *list, unsigned int start, unsigned int end);
bool sll_node_values_equal(enum SLL_TYPES value_type, node *first, node *second);
bool sll_equal(sll *first, sll *second);

#endif
