#include <iostream>
#include <omp.h>
#include <iomanip> 

double num_steps = 1000000000;
double step = 1.0 / (double)num_steps;
int fracc = 0;
int main()
{
	for (int num_threads_ = 1; num_threads_ <= 11; num_threads_++)
	{
		int i;
		double x, pi, sum = 0.0;
		double start_time, run_time;

		step = 1.0 / (double)num_steps;


		start_time = omp_get_wtime();

		fracc = (int)(num_steps / num_threads_);
		std::cout << fracc << std::endl;
#pragma omp parallel num_threads(num_threads_)
		{
			int i = 0;
			int ID = omp_get_thread_num();
//#pragma omp for reduction(+:sum)
// #pragma omp for reduction(+:sum) schedule(static, 50)
// #pragma omp for reduction(+:sum) schedule(guided, 50)
// #pragma omp for reduction(+:sum) schedule(auto)
#pragma omp for reduction(+:sum) schedule(dynamic, 50)
			for (i = 0; i < 1000000000; i++)
			{
				double x = (i + 0.5) * step;
				sum += 4.0 / (1.0 + (x * x));
			}
		}

		pi = step * sum;
		run_time = omp_get_wtime() - start_time;
		std::cout << pi << "\nTime: " << run_time << std::endl;
	}
}	