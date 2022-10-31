#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NPOINTS 1000
# define MAXITER 1000

struct d_complex {
    double r;
    double i;
};

void testpoint(struct d_complex);

struct d_complex c;
int numoutside = 0;

int main() {
    int i, j, e=4;
    double area, error, eps = 1.0e-5;
    omp_set_num_threads(4);

    for (int threads = 1; threads < 5; threads++)
    {
        double start_time = omp_get_wtime(), run_time;
#pragma omp parallel num_threads(threads) default(shared) firstprivate(eps) private(c,i,j)
    {
#pragma omp for
    for (i = 0; i < NPOINTS; i++) {
        for (j = 0; j < NPOINTS; j++) {
            c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS)+eps;
            c.i = 1.125 * (double)(j) / (double)(NPOINTS)+eps;
            testpoint(c);
        }
    }

    area = 2.0 * 2.5 * 1.125 * (double)((NPOINTS * NPOINTS) - (numoutside/ threads)) / (double)((NPOINTS * NPOINTS));
    error = area / (double)NPOINTS;
    }
    run_time = omp_get_wtime() - start_time;
    printf("THREADS: %d RUNTIME: %5.4f\n", threads ,run_time);
    printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
    printf("Correct answer should be around 1.510659\n");
}

    }
void testpoint(struct d_complex c) {

    struct d_complex z;
    int iter;
    double temp;

    z = c;
    for (iter = 0; iter < MAXITER; iter++) {
        temp = (z.r * z.r) - (z.i * z.i) + c.r;
        z.i = z.r * z.i * 2 + c.i;
        z.r = temp;
        if ((z.r * z.r + z.i * z.i) > 4.0) {
#pragma omp atomic
            numoutside++;
            break;
        }
    }
}