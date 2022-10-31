#include <iostream>
#include <omp.h>
#include <iomanip> 

double num_steps = 1000000000;
double step = 1.0 / (double)num_steps;
int fracc = 0;
int main()
{
	
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0 / (double)num_steps;


	start_time = omp_get_wtime();

	fracc = (int)(num_steps / 10);
#pragma omp parallel  num_threads(10)
	{
		int ID = omp_get_thread_num();
#pragma omp for reduction(+:sum)
		{
			for (int i = fracc * ID; i < fracc * (ID + 1); i++)
			{
				double x = (i + 0.5) * step;
				sum += 4.0 / (1.0 + (x * x));
			}
		}
	}

	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
}