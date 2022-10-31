#include <iostream>
#include <omp.h>
#include <iomanip> 

/*
int omp_get_num_threads();
int omp_get_thread_num();
double omp_get_wtime();

*/
double num_steps = 1000000000;
double step = 1.0 / (double)num_steps;
int fracc = 0;

int main()
{
    for (int num_threads_ = 1; num_threads_ <= 11; num_threads_++)
    {
        std::cout << "num threads:" << num_threads_ << std::endl;
        double x, pi, sum = 0.0;
        double PI[50][8];
        double start_time, run_time;
        fracc = (int)(num_steps / num_threads_);
        std::cout << "fracc:" << fracc << std::endl;
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num_threads_)
        {
            double partial_sum = 0.0;
            int ID = omp_get_thread_num();
            for (int i = fracc * ID; i < fracc * (ID + 1); i++)
            {
                double x = (i + 0.5) * step;
                partial_sum += 4.0 / (1.0 + (x * x));
            }
#pragma omp atomic
            sum += partial_sum;
        }

        pi = sum * step;
        run_time = omp_get_wtime() - start_time;
        std::cout << std::setprecision(15) << pi << std::endl;
        std::cout << "Tiempo: " << std::setprecision(15) << run_time << std::endl << std::endl;
    }
}

