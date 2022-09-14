#include <iostream>
#include <stdlib.h>
#include <PDR_Matrix.h>


void TestMatrix() {
    double a[4] = { 1,2,3,4 };
    double b[4] = { 2,3,4,5 };
    double r[4] = { 0,0,0,0 };

    VectorAdd(a, b, r);

    for (size_t i = 0; i < 4; i++) {
        std::cout << "a[" << i << "] = " << r[i] << std::endl;
    }
}

int main()
{
    TestMatrix();

    system("pause");
}

