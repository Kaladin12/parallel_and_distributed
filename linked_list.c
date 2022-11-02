#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif


struct node {
    int data;
    int fibdata;
    struct node* next;
};

int fibonacci[FS + 1];

void fib(int n) {
    int x, y;
    if (n < 2) {
        fibonacci[n] = n;
    }
    else {
        x = fibonacci[n - 1];
        y = fibonacci[n - 2];
        fibonacci[n] = x + y;
    }
}

void processwork(struct node* p)
{
    int n, i;
    n = p->data;
    for (i = 0; i < n+1; i++)
    {
        fib(i);
    }
    p->fibdata = fibonacci[n];
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;

    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i = 0; i < N; i++) {
        temp = malloc(sizeof(struct node));
        p->next = temp;
        p = temp;
        p->data = FS + i + 1;
        p->fibdata = i + 1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char* argv[]) {
    double start, end;
    struct node* p = NULL;
    struct node* temp = NULL;
    struct node* head = NULL;

    printf("Process linked list\n");
    printf("  Each linked list node will be processed by function 'processwork()'\n");
    printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n", N, FS);
    printf("  SECUENCIAL");
    int iter;
    p = init_list(p);
    head = p;
    start = omp_get_wtime();
    {
        // solo es necesario iterar sobre la cantidad de nodos que tiene la lista
        for (iter = 0; iter < N+1; iter++)
        {
            processwork(p);
            p = p->next;
        }
    }
    end = omp_get_wtime();
    p = head;
    while (p != NULL) {
        printf("%d : %d\n", p->data, p->fibdata);
        temp = p->next;
        free(p);
        p = temp;
    }
    free(p);

    printf("Compute Time: %f seconds\n", end - start);

    return 0;
}
