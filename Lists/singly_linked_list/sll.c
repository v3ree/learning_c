// singly linked list implementation

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sll.h"


// creates and returns a new list
sll *sll_create_list(enum SLL_TYPES value_type) 
{
    sll *new_sll = (sll *) malloc(sizeof(sll));
    new_sll->head = NULL;
    new_sll->size = 0;
    new_sll->value_type = value_type;
    return new_sll;
}


// creates and returns a new node with given value
node *sll_create_node(void *value)
{
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}


// add node to start of list
void sll_prepend(sll *list, node *new_node)
{
    node *temp = list->head;
    list->head = new_node;
    list->head->next = temp;
    list->size++;
}


// adds a new node to the end of the list
void sll_append(sll *list, node *new_node)
{
    if (!list->size) { 
        sll_prepend(list, new_node);
        return;
    }
    unsigned int last_position = list->size - 1;
    node *last_node = sll_get_node_at_position(list, last_position);
    last_node->next = new_node;
    new_node->next = NULL;
    list->size++;
}


// add node at given position
void sll_insert_at_position(sll *list, unsigned int position, node *new_node) 
{
    if (!position) { 
        sll_prepend(list, new_node);
        list->size++;
        return;
    }
    if (position == list->size - 1) { 
        sll_append(list, new_node);
        list->size++;
        return;
    }
    node *prev_node = sll_get_node_before_position(list, position);
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    list->size++;
}


// deletes the node at the given position
void sll_delete_node(sll *list, unsigned int position, bool delete_value)
{
    if (!list->size || position >= list->size) { return; }

    // delete head
    if (!position) {
        node * temp = list->head;
        list->head = temp->next;
        if (delete_value) { free(temp->value); };
        free(temp);
        list->size--;
        return;
    }

    node *prev_node = sll_get_node_before_position(list, position);
    node *current_node = prev_node->next;
    prev_node->next = current_node->next;
    if (delete_value) { free(current_node->value); };
    free(current_node);
    list->size--;
}


// returns pointer to node before position or NULL if position is invalid
node *sll_get_node_before_position(sll *list, unsigned int position)
{
    unsigned int pos = position - 1;
    if (!list->size || list->size <= pos) { return NULL; }

    node *current_node = list->head;
    unsigned int current_node_index = 0;

    while (current_node->next && current_node_index < pos) {
        current_node = current_node->next;
        current_node_index++;
    } 
    return current_node;
}


// returns pointer to node at position or NULL if position is invalid
node *sll_get_node_at_position(sll *list, unsigned int position)
{
    return sll_get_node_before_position(list, position + 1);
}


// returns pointer to first node with given value or NULL (and position -1) if none found
node *sll_find_first_node_with_value(sll *list, void *value, int *position)
{
    if (!list->size) { return NULL; }

    unsigned int current_position = 0;
    node *current_node = list->head;
    node *aux_node = sll_create_node(value);

    while (current_node) {
        if (sll_node_values_equal(list->value_type, current_node, aux_node)) { break; }
        current_node = current_node->next;
        current_position++;
    } 

    free(aux_node);

    *position = (current_position < list->size) ? (int) current_position : -1;
    return current_node;
}


// print the node value
void sll_print_node(enum SLL_TYPES value_type, node *anode) 
{
    if (!anode) { return; }

    switch (value_type) {
        case integer:
            printf("%d", *((int*) anode->value));
            break;
        case decimal:
            printf("%f", *((double*) anode->value));
            break;
        case character:
            printf("%c", *((char*) anode->value));
            break;
        case string:
            printf("%s", (char*) anode->value);
            break;
    }
}


// print all values in the list
void sll_print(sll *list) 
{
    if (!list->size || !list->head) {
        printf("List is empty!\n");
        return;
    }

    node *current_node = list->head;
    int index = 0;

    while (current_node) {
        printf("[%d] ", index);
        sll_print_node(list->value_type, current_node);
        printf("\n");

        current_node = current_node->next;
        index++;
    } 
}


// empty list by freeing all nodes 
// (and optionally all values contained in nodes - careful to not free values on the stack)
void sll_empty_list(sll *list, bool delete_node_values)
{
    node *current_node = list->head;
    while (current_node) {
        node *next_node = current_node->next;
        if (delete_node_values) { free(current_node->value); }
        free(current_node);
        current_node = next_node;
    }
    list->head = NULL;
    list->size = 0;
}


// concatenate two sll with same value type
// returns the new list but also leaves the two arg lists intact
sll *sll_concat_lists(sll *list1, sll *list2)
{
    if (list1->value_type != list2->value_type) { return NULL; }

    sll *ret_list = sll_create_list(list1->value_type);
    sll_append(ret_list, list1->head);
    sll_append(ret_list, list2->head);
    list1->size += list2->size - 2; // -2 because two list head have been already appended
    return ret_list;
}


// count items in list with given value
unsigned int sll_count_value(sll *list, void *value)
{
    node *current_node = list->head;
    unsigned int count = 0;
    node *aux_node = sll_create_node(value);

    while (current_node) {
        if (sll_node_values_equal(list->value_type, current_node, aux_node)) {
            count++;
        }
        current_node = current_node->next;
    }
    free(aux_node);
    return count;
}


// return slice of list as new list, up to end position (excluded)
sll *sll_slice(sll *list, unsigned int start, unsigned int end)
{
    int size = end - start;
    if (size < 1) return NULL;

    sll *new_list = sll_create_list(list->value_type);
    node *current_node = sll_get_node_at_position(list, start);

    while (current_node && size) {
        node * new_node;
        void *v;

        switch (list->value_type) {
            case integer: {
                v = (int *) malloc(sizeof(int));
                *((int *) v) = *((int *) current_node->value);
                }
                break;
            case decimal: {
                v = (double *) malloc(sizeof(double));
                *((double *) v) = *((double *) current_node->value);
                }
                break;
            case character: {
                v = (char *) malloc(sizeof(char));
                *((char *) v) = *((char *) current_node->value);
                }
                break;
            case string: {
                char *cv = (char *) current_node->value;
                v = (char *) malloc(sizeof(char) * strlen(cv));
                strncpy((char *) v, cv, strlen(cv));
                }
                break;
        }
        new_node = sll_create_node(v);
        sll_append(new_list, new_node);

        size--;
        current_node = current_node->next;
    }
    return new_list;
}


// compare the values of two nodes, return true if equal
bool sll_node_values_equal(enum SLL_TYPES value_type, node *first, node *second)
{
    switch (value_type) {
        case character:
        case integer:
            if (*((int*) first->value) == *((int*) second->value))
                return true;
            break;
        case decimal:
            if (*((double*) first->value) == *((double*) second->value)) {
                return true;
            }
            break;
        case string: {
            char *v1 = (char*) first->value;
            char *v2 = (char*) second->value;
            if (!strcmp(v1, v2)) return true;
            }
            break;
    }
    return false;
}


// compare two lists and return true if equal (by values)
bool sll_equal(sll *first, sll *second)
{
    if ((first->size != second->size) ||
            (first->value_type != second->value_type)) {
        return false;
    }
    node *current_first = first->head;  
    node *current_second = second->head;

    while (current_first && current_second) {
        if (!sll_node_values_equal(first->value_type, current_first, current_second))
            return false;
        current_first = current_first->next;
        current_second = current_second->next;
    }
    return true;
}
