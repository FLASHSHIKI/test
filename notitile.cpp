#include <iostream>

int main(){
    int a = 10;
    int* pra = &a;
    int** prapra = &pra;
    std::cout << a << " " << pra << " " << prapra;
    return 0;
}