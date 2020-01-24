// doubly linked list implementation

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dll.h"


// creates and returns a new list
dll *dll_create_list(enum DLL_TYPES value_type) 
{
    dll *new_dll = (dll *) malloc(sizeof(dll));
    new_dll->head = NULL;
    new_dll->tail = NULL;
    new_dll->size = 0;
    new_dll->value_type = value_type;
    return new_dll;
}


// creates and returns a new node with given value
node *dll_create_node(void *value)
{
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}


// add node to start of list
void dll_prepend(dll *list, node *new_node)
{
    if (!list->size) { 
        list->head = new_node;
        list->tail = new_node;
        list->size++;
        return;
    }
    list->head->prev = new_node;
    new_node->next = list->head;
    new_node->prev = NULL;
    list->head = new_node;
    list->size++;
}


// adds a new node to the tail of the list
void dll_append(dll *list, node *new_node)
{
    if (!list->size) { 
        dll_prepend(list, new_node);
        return;
    }
    list->tail->next = new_node;
    new_node->prev = list->tail;
    new_node->next = NULL;
    list->tail = new_node;
    list->size++;
}


// add node at given position counting from the head
// moves node at position to next of new
void dll_insert_at_position(dll *list, unsigned int position, node *new_node) 
{
    if (!position) { 
        dll_prepend(list, new_node);
        list->size++;
        return;    
    }
    if (position == list->size - 1) { 
        dll_append(list, new_node);
        list->size++;
        return;
    }
    node *current_node = dll_get_node_at_position(list, position);
    new_node->next = current_node;
    new_node->prev = current_node->prev;
    current_node->prev->next = new_node;
    current_node->prev = new_node;
    list->size++;
}


// deletes the node at the given position counting from the head
void dll_delete_node(dll *list, unsigned int position, bool delete_value)
{
    if (!list->size || position >= list->size) { return; }

    node *current_node = dll_get_node_at_position(list, position);

    // delete both head and tail
    if (list->size == 1){
        list->head = NULL;
        list->tail = NULL;
    }
    // delete head
    else if (!position) {
        list->head = current_node->next;
        list->head->prev = NULL;
    }
    // delete tail
    else if (position == list->size - 1) {
        list->tail = current_node->prev;
        list->tail->next = NULL;
    }
    // delete middle node
    else {
        current_node->prev->next = current_node->next;
        current_node->next->prev = current_node->prev;
    }

    if (delete_value) { free(current_node->value); };
    free(current_node);
    list->size--;
}


// returns pointer to node at position or NULL if position is invalid
node *dll_get_node_at_position(dll *list, unsigned int position)
{
    if (position >= list->size) { return NULL; }
    unsigned int distance_from_tail = list->size - 1 - position;

    node *current_node;

    // search from closest list ending
    if (position <= distance_from_tail) {
        current_node = list->head;
        unsigned int current_node_index = 0;

        while (current_node && current_node_index < position) {
            current_node = current_node->next;
            current_node_index++;
        } 
    } else {
        current_node = list->tail;
        unsigned int current_node_index = list->size - 1;

        while (current_node && current_node_index > position) {
            current_node = current_node->prev;
            current_node_index--;
        } 
    }
    return current_node;
}


// returns pointer to first node with given value or NULL (and position -1) if none found
node *dll_find_first_node_with_value(dll *list, void *value, int *position)
{
    if (!list->size) { return NULL; }

    unsigned int current_position = 0;
    node *current_node = list->head;
    node *aux_node = dll_create_node(value);

    while (current_node) {
        if (dll_node_values_equal(list->value_type, current_node, aux_node)) { break; }
        current_node = current_node->next;
        current_position++;
    } 

    free(aux_node);

    *position = (current_position < list->size) ? (int) current_position : -1;
    return current_node;
}


// print all values in the list
void dll_print_node(enum DLL_TYPES value_type, node *anode) 
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
void dll_print(dll *list) 
{
    if (!list->size || !list->head) {
        printf("List is empty!\n");
        return;
    }

    node *current_node = list->head;
    int index = 0;

    while (current_node) {
        printf("[%d] ", index);
        dll_print_node(list->value_type, current_node);
        printf("\n");

        current_node = current_node->next;
        index++;
    } 
}


// empty list by freeing all nodes 
// (and optionally all values contained in nodes - careful to not free values on the stack)
void dll_empty_list(dll *list, bool delete_node_values)
{
    node *current_node = list->head;
    while (current_node) {
        node *next_node = current_node->next;
        if (delete_node_values) { free(current_node->value); }
        free(current_node);
        current_node = next_node;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}


// concatenate two dll with same value type
// returns the new list but also leaves the two arg lists intact
dll *dll_concat_lists(dll *list1, dll *list2)
{
    if (list1->value_type != list2->value_type) { return NULL; }

    dll *ret_list = dll_create_list(list1->value_type);
    dll_append(ret_list, list1->head);
    dll_append(ret_list, list2->head);
    list1->size += list2->size - 2; // -2 because two list head have been already appended
    return ret_list;
}


// count items in list with given value
unsigned int dll_count_value(dll *list, void *value) 
{
    node *current_node = list->head;
    unsigned int count = 0;
    node *aux_node = dll_create_node(value);

    while (current_node) {
        if (dll_node_values_equal(list->value_type, current_node, aux_node)) {
            count++;
        }
        current_node = current_node->next;
    }
    free(aux_node);
    return count;
}


// reverse the list and return pointer to new list
dll *dll_reverse_list(dll *list) 
{
    node *current_node = list->tail;

    dll *reversed_list = dll_create_list(list->value_type);
    dll *reversed_new_list = dll_create_list(list->value_type);

    while (current_node) {
        node *new_node = dll_create_node(current_node->value);
        dll_append(reversed_list, new_node);

        current_node = current_node->prev;
    }
    reversed_new_list = dll_slice(reversed_list, 0, reversed_list->size);

    dll_empty_list(reversed_list, false);
    free(reversed_list);

    return reversed_new_list;
}


// return slice of list as new list, up to end position (excluded)
dll *dll_slice(dll *list, unsigned int start, unsigned int end)
{
    int size = end - start;
    if (size < 1) return NULL;

    dll *new_list = dll_create_list(list->value_type);
    node *current_node = dll_get_node_at_position(list, start);

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
        new_node = dll_create_node(v);
        dll_append(new_list, new_node);
        size--;
        current_node = current_node->next;
    }
    return new_list;
}


// compare the values of two nodes, return true if equal
bool dll_node_values_equal(enum DLL_TYPES value_type, node *first, node *second)
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
bool dll_equal(dll *first, dll *second)
{
    if ((first->size != second->size) ||
            (first->value_type != second->value_type)) {
        return false;
    }
    node *current_first = first->head;  
    node *current_second = second->head;    

    while (current_first && current_second) {
        if (!dll_node_values_equal(first->value_type, current_first, current_second))
            return false;
        current_first = current_first->next;
        current_second = current_second->next;
    }
    return true;
}
