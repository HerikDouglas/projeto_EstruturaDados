#ifndef LIST_H  
#define LIST_H

typedef struct List List;

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

List *List_alloc();
void  List_free(List *l);
void  List_insert(List *l, void *item);
void *List_find(List *l, void *key, int (*cmp)(void*,void*));
void *List_remove(List *l, void *key, int (*cmp)(void*,void*));
int   List_getLength(List *l);
void  List_print(List *l, void (*print)(void*));

#endif