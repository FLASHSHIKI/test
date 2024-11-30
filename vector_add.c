#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 10000000  // 向量大小

// 初始化向量
void initialize_vector(float *v, int size) {
    for (int i = 0; i < size; i++) {
        v[i] = rand() % 100;
    }
}

// 串行向量加法
void vector_add_serial(float *a, float *b, float *c, int size) {
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

// OpenMP并行化向量加法，唯一需要修改的地方
void vector_add_parallel(float *a, float *b, float *c, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

//main函数只是作为驱动测试，不需要修改
int main() {
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));
    float *c_serial = (float *)malloc(N * sizeof(float));
    float *c_parallel = (float *)malloc(N * sizeof(float));

    // 初始化向量a和b
    initialize_vector(a, N);
    initialize_vector(b, N);

    // 测量串行向量加法时间
    clock_t start_serial = clock();
    vector_add_serial(a, b, c_serial, N);
    clock_t end_serial = clock();

    double time_serial = (double)(end_serial - start_serial) / CLOCKS_PER_SEC;

    // 测量并行向量加法时间
    clock_t start_parallel = clock();
    vector_add_parallel(a, b, c_parallel, N);
    clock_t end_parallel = clock();

    double time_parallel = (double)(end_parallel - start_parallel) / CLOCKS_PER_SEC;

    // 检查串行和并行结果是否一致
    int correct = 1;
    for (int i = 0; i < N; i++) {
        if (c_serial[i] != c_parallel[i]) {
            correct = 0;
            break;
        }
    }

    if (correct) {
        printf("Results are correct.\n");
    } else {
        printf("Results are incorrect.\n");
    }

    // 输出时间对比
    printf("Serial Time: %f seconds\n", time_serial);
    printf("Parallel Time: %f seconds\n", time_parallel);

    // 释放内存
    free(a);
    free(b);
    free(c_serial);
    free(c_parallel);

    return 0;
}