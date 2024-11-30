// g++ -fopenmp openmp.cpp -o main 指定编译选项
#include<omp.h>
#include<iostream>
 
int main(){
    std::cout << "parallel begin:\n";
    // omp_set_num_threads(4);
    int sum = 0;
    #pragma omp parallel for //reduction(+:sum)
    for (int i = 0; i < 10; i++) {
        sum += i;
    }
    printf("%d", sum);
    std::cout << "\n parallel end.\n";
    return 0;
}