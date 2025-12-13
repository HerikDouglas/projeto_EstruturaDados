#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

typedef struct Node Node;

struct Node {
    void *value;
    Node *next;
};

struct List {
    int length;
    Node *first;
    Node *last;
};

List *List_alloc() {
    List *l = malloc(sizeof(List));

    if (l) {
        l->length = 0;
        l->first = NULL;
        l->last = NULL;
    }

    return l;
}

void List_free(List *l) {
    Node *n, *aux;

    if (l) {
        n = l->first;
        free(l);

        while (n) {
            aux = n->next;
            free(n);
            n = aux;
        }
    }
}

void List_insert(List *l, void *item) {
    Node *new, *n;

    if (l) {
        new = malloc(sizeof(Node));
        new->value = item;
        new->next = NULL;

        if (l->length == 0) {
            l->first = new;
            l->last = new;
        }
        else {
            l->last->next = new;
            l->last = new;
        }

        l->length++;
    }
}

void List_insert1(List *l, void *item) {
    Node *new;

    if (l) {
        new = malloc(sizeof(Node));
        new->value = item;
        new->next = NULL;

        new->next = l->first;
        l->first = new;
        l->length++;
    }
}

void List_print(List *l, void (*print)(void*)) {
    Node *n;

    if (l) {
        n = l->first;
        while (n) {
            print(n->value);
            n = n->next;
        }
        printf("\n");
    }
}

int List_getLength(List *l) {
    if (l)
        return l->length;
    return 0;
}

typedef struct {
    int idade;
    char nome[30];
} Pessoa;

void *List_find(List *l, void *key, int (*cmp)(void*,void*)) {
    Node *n;

    if (l) {
        n = l->first;

        while (n) {
            if (cmp(key, n->value) == 0) {
                return n->value;
            }
            n = n->next;
        }
    }

    return NULL;
}