#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct Node_* Node;
struct Node_ {
    Node next;
    void* element;
};

struct List_ {
    Node head;
    Node tail;
    size_t size;
    Node iterator;
};

Node _create_node(void* element) {
    Node node = malloc(sizeof(struct Node_));
    node->next = NULL;
    node->element = element;
    return node;
}

void _destroy_node(Node node, void (*free_element)(void*)) {
    if (free_element != NULL) {
        free_element(node->element);
    }
    free(node);
}

List list_create() {
    List list = malloc(sizeof(struct List_));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->iterator = NULL;
    return list;
}

void list_destroy(List list, void (*free_element)(void*)) {
    Node node = list->head;
    while (node != NULL) {
        Node next = node->next;
        _destroy_node(node, free_element);
        node = next;
    }
    free(list);
}

bool list_is_empty(List list) {
    return list->size == 0;
}

size_t list_size(List list) {
    return list->size;
}

void* list_get_first(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    return list->head->element;
}

void* list_get_last(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    return list->tail->element;
}

void* list_get(List list, int position) {
    if (position >= list->size) {
        return NULL;
    }
    Node node = list->head;
    for (size_t i = 0; i < position; i++) {
        node = node->next;
    }
    return node->element;
}

int list_find(List list, bool (*equal)(void*, void*), void* element) {
    Node node = list->head;
    for (size_t i = 0; i < list->size; i++) {
        if (equal(node->element, element)) {
            return i;
        }
        node = node->next;
    }
    return -1;
}

void list_insert_first(List list, void* element) {
    Node node = _create_node(element);
    node->next = list->head;
    list->head = node;
    if (list_is_empty(list)) {
        list->tail = node;
    }
    list->size++;
}

void list_insert_last(List list, void* element) {
    Node node = _create_node(element);
    if (list_is_empty(list)) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    list->size++;
}

void list_insert(List list, void* element, int position) {
    if (position > list->size) {
        return;
    }
    if (position == 0) {
        list_insert_first(list, element);
    } else if (position == list->size) {
        list_insert_last(list, element);
    } else {
        Node node = _create_node(element);
        Node prev = list->head;
        for (size_t i = 0; i < position - 1; i++) {
            prev = prev->next;
        }
        node->next = prev->next;
        prev->next = node;
        list->size++;
    }
}

void* list_remove_first(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    Node node = list->head;
    list->head = node->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    void* element = node->element;
    _destroy_node(node, NULL);
    list->size--;
    return element;
}

void* list_remove_last(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    void* element = list->tail->element;
    if (list_size(list) == 1) {
        list_make_empty(list, NULL);
    } else {
        Node node = list->head;
        while (node->next != list->tail) {
            node = node->next;
        }
        list->tail = node;
        list->size--;
    }
    return element;
}

void* list_remove(List list, int position) {
    if (position >= list_size(list)) {
        return NULL;
    } else if (position == 0) {
        return list_remove_first(list);
    } else if (position == list_size(list) - 1) {
        return list_remove_last(list);
    }

    Node prev = list->head;
    for (size_t i = 0; i < position - 1; i++) {
        prev = prev->next;
    }
    Node node = prev->next;
    void* element = node->element;
    prev->next = node->next;
    _destroy_node(node, NULL);
    list->size--;
    return element;
}

void list_make_empty(List list, void (*free_element)(void*)) {
    Node node = list->head;
    while (node != NULL) {
        Node next = node->next;
        _destroy_node(node, free_element);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void list_to_array(List list, void** out_array) {
    Node node = list->head;
    for (size_t i = 0; i < list->size; i++) {
        out_array[i] = node->element;
        node = node->next;
    }
}

int list_count_all(List list, bool (*equal)(void*, void*), void* element) {
    Node node = list->head;
    int count = 0;
    while (node != NULL) {
        if (equal(node->element, element)) {
            count++;
        }
        node = node->next;
    }
    return count;
}

int list_remove_all(List list, bool (*equal_element)(void*, void*), void (*free_element)(void*), void* element) {
    Node previous = NULL, node = list->head, next = NULL;
    int count = 0;
    while (node != NULL) {
        next = node->next;
        if (equal_element(node->element, element)) {
            if (previous == NULL) {
                list->head = node->next;
            } else {
                previous->next = node->next;
            }
            if (free_element != NULL) {
                free_element(node->element);
            }
            next = node->next;
            free(node);
            node = next;
            if (node == NULL) {
                list->tail = previous;
            }
            count++;
            list->size--;
        } else {
            previous = node;
            node = node->next;
        }
    }
    return count;
}

int list_remove_duplicates(List list, bool (*equal_element)(void*, void*), void (*free_element)(void*), void* element) {
    Node previous = NULL, node = list->head, next = NULL;
    int count = 0;
    while (node != NULL) {
        next = node->next;
        if (equal_element(node->element, element)) {
            count++;
            if (count > 1) {
                if (previous == NULL) {
                    list->head = node->next;
                } else {
                    previous->next = node->next;
                }
                if (free_element != NULL) {
                    free_element(node->element);
                }
                free(node);
                node = next;
                if (node == NULL) {
                    list->tail = previous;
                }
                list->size--;
            } else {
                previous = node;
                node = node->next;
            }
        } else {
            previous = node;
            node = node->next;
        }
    }
    return count;
}

List list_join(List list1, List list2) {
    List list = list_create();
    Node node = list1->head;
    while (node != NULL) {
        list_insert_last(list, node->element);
        node = node->next;
    }
    node = list2->head;
    while (node != NULL) {
        list_insert_last(list, node->element);
        node = node->next;
    }
    return list;
}

void list_print(List list, void (*print_element)(void* element)) {
    Node node = list->head;
    for (size_t i = 0; i < list->size; i++) {
        print_element(node->element);
        node = node->next;
    }
    printf("\n");
}

List list_get_sublist_between(List list, int start_idx, int end_idx) {
    if (end_idx < start_idx) {
        return NULL;
    }
    List result = list_create();
    int idx = 0;
    Node node = list->head;
    while (idx < start_idx) {
        node = node->next;
        idx++;
    }
    while (idx <= end_idx) {
        list_insert_last(result, node->element);
        node = node->next;
        idx++;
    }
    return result;
}

List list_get_sublist(List list, int indexes[], int count) {
    if (count <= 0) {
        return NULL;
    }
    List result = list_create();
    for (int i = 0; i < count; i++) {
        int target_idx = indexes[i];
        int current_idx = 0;
        Node node = list->head;
        while (current_idx != target_idx) {
            node = node->next;
            current_idx++;
        }
        list_insert_last(result, node->element);
    }
    return result;
}

List list_map(List list, void* (*func)(void*)) {
    if (func == NULL) {
        return NULL;
    }
    List l = list_create();
    Node node = list->head;
    while (node != NULL) {
        void* ret = func(node->element);
        list_insert_last(l, ret);
        node = node->next;
    }
    return l;
}

List list_filter(List list, bool (*func)(void*)) {
    if (func == NULL) {
        return NULL;
    }
    List l = list_create();
    Node node = list->head;
    while (node != NULL) {
        if (func(node->element)) {
            list_insert_last(l, node->element);
        }
        node = node->next;
    }
    return l;
}

void list_iterator_start(List list) {
    list->iterator = list->head;
}

bool list_iterator_has_next(List list){
    return list->iterator != NULL;
}

void* list_iterator_get_next(List list) {
    if (list->iterator == NULL) {
        return NULL;
    }
    void* element = list->iterator->element;
    list->iterator = list->iterator->next;
    return element;
}
