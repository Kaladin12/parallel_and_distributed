#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif
/*

struct node {
    int data;
    int fibdata;
    struct node* next;
};
// arreglo para guardar la referencia de cada nodo de la linked list
struct node* pointers[N + 1];

int fibonacci[FS + 1];

int fib(int n) {
    int x, y;
    if (n < 2) {
        fibonacci[n] = n;
        return (n);
    }
    else {
        x = fibonacci[n - 1];
        y = fibonacci[n - 2];
        printf("%d %d", x, y);
        fibonacci[n] = x+y;
        return (x + y);
    }
}

void processwork(struct node* p)
{
    int n, i;
    n = p->data;
    for (i = 0; i < n; i++)
    {
        p->fibdata = fib(n);
    }
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
        // guardamos la referencia
        pointers[i] = p;
        p = temp;
        p->data = FS + i + 1;
        p->fibdata = i + 1;
    }
    p->next = NULL;
    // referencia del ultimo nodo
    pointers[i] = p;
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

    p = init_list(p);
    head = p;
    start = omp_get_wtime();
    int iter = 0;
    omp_set_num_threads(4);
    printf("PARALLEL NOT TASKS\n");
    {
#pragma omp parallel num_threads(1) default(shared)
        {
            printf("Number of threads: %d\n", omp_get_num_threads());
#pragma omp for firstprivate(iter, p, fibonacci)
            for (iter = 0; iter < N + 1; iter++)
            {
                // como se tiene la referencia guardada, ahora los valores pueden ser calculados por cada thread y mantener la referencia del siguiente nodo
                processwork(pointers[iter]);
            }
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
*/