//g++ hello.cpp -mavx512f -o main  对于avx512需要指定编译选项mavx512f
#include <immintrin.h>
#include <iostream>

void avx512_add(float* a, float* b, float* result, int n) {
    // 处理数组的前n个元素
    for (int i = 0; i < n; i += 16) {
        // 加载数据到ZMM寄存器
        __m512 va = _mm512_loadu_ps(a + i);
        __m512 vb = _mm512_loadu_ps(b + i);
        // 执行AVX-512加法
        __m512 vresult = _mm512_add_ps(va, vb);
        // 将结果存回内存
        _mm512_storeu_ps(result + i, vresult);
    }
}

int main() {
    const int n = 1024; 
    float a[n], b[n], result[n];

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    avx512_add(a, b, result, n);

    for (int i = 0; i < n; i++) {
        std::cout << "Result[" << i << "] = " << result[i] << std::endl;
    }

    return 0;
}