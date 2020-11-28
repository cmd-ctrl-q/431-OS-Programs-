#include <iostream>
using namespace std; 

int i;

int factorial(int n) {
    if (n==1) {
        return 1;
    } else {
        printf("%d * %d = %d\n",  i, n-1, i*(n-1));
        i = i*(n-1);
        return n * factorial(n-1);
    }
}

int main() {

    i = 10; // global
    int n = 10;
    int f = factorial(i);
    printf("%d! = %d", n, f);
}