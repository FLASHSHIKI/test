#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

template <int n>
void it(double r, double *x, int64_t itn)  //优化后的并行化计算
{
    for (int64_t i = 0; i < itn; i++)
    {
        for (int64_t j = 0; j < n; j++)
        {
            x[j] = r * x[j] * (1.0 - x[j]);
        }
    }
}

template <int gn>
void itvg(double r, double *x, int64_t n, int64_t itn)  //分块
{
    for (int64_t i = 0; i < n; i += gn)
    {
        it<gn>(r, x + i, itn);
    }
}

int main()
{
    int64_t itn;
    double r;
    int64_t n;
    double *x;

    std::ifstream fi("conf.data");
    fi >> itn >> r >> n;
    fi.close();

    x = (double *)malloc(n * 8);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 4.0);
    for(int i=0; i<n ;i++){
        x[i] = dis(gen);
    }

    auto t1 = std::chrono::steady_clock::now();
    itvg<128>(r, x, n, itn);
    auto t2 = std::chrono::steady_clock::now();
    int d1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    printf("%d\n", d1);


    return 0;
}