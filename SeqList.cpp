#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

#define DEFVALUE(n, defval) ((#n[0] ? n : defval))
#define init(n) __init(DEFVALUE(n, 100))

Vector *__init(int n) {
    Vector *ret = (Vector *)malloc(sizeof(Vector) * 1);
    // to do something for init Vector
    ret->data = (int *)malloc(sizeof(int) * n);
    ret->size = n;
    ret->length = 0;
    return ret;
}

int expand(Vector *vec) {
    int *p = (int *)realloc(vec->data, vec->size * 2 * sizeof(int));
    if (p == NULL) return 0;
    vec->data = p;
    vec->size *= 2;
    return 1;
}

int insert(Vector *vec, int val, int ind) {
    if (vec == NULL) return 0;
    if (ind > vec->length || ind < 0) return 0;
    if (vec->length == vec->size && !expand(vec)) {
        return 0;
    }
    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length += 1;
    return 1;
}

int delete_node(Vector *vec, int ind) {
    if (vec == NULL) return 0;
    if (ind < 0 || ind >= vec->length) return 0;
    for (int i = ind + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void clear(Vector *vec) {
    if (vec == NULL) return ;
    if (vec->data != NULL) {
        free(vec->data);
    }
    free(vec);
    return ;
}

void output(Vector *vec) {
    printf("vector(%d, %d) : [", vec->length, vec->size);
    for (int i = 0; i < vec->length; i++) {
        printf(" %d", vec->data[i]);
    }
    printf(" ]\n");
    return ;
}

int main() {
    Vector *vec = init();
    int val, ind;
    while (~scanf("%d%d", &val, &ind)) {
        printf("insert %d, %d : %d\n", val, ind, insert(vec, val, ind));
        output(vec);
    }
    clear(vec);
    return 0;
}