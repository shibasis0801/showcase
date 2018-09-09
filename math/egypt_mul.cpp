#include <iostream>
using namespace std;

int half(int x) {
    return x >> 1;
}

bool odd(int x) {
    return x & 0x1;
}

int multiply1(int n, int a) {
    if (n == 1) return a;
    int result = multiply1(half(n), a + a);
    if (odd(n)) result = result + a;
    return result;
} 

int mult_acc0(int r, int n, int a) {
    if (n == 1)
        return r + a;
    if(odd(n)){
        return mult_acc0(r + a, half(n), a + a);
    } 
    else
        return mult_acc0(r, half(n), a + a);
}

int mult_acc1(int r, int n, int a) {
    if (n == 1)
        return r + a;
    if (odd(n))
        r += a;
    return mult_acc0(r, half(n), a + a);
}

int mult_acc2(int r, int n, int a) {
    if (odd(n)) {
        r += a;
        if (n == 1)
            return r; 
    }
    return mult_acc2(r, half(n), a + a);
}

int mult_acc3(int r, int n, int a) {
    if (odd(n)) {
        r += a;
        if (n == 1)
            return r;
    }
    n = half(n);
    a += a;
    return mult_acc3(r, n, a);
}

int mult_acc4(int r, int n, int a) {
    while (true) {
        if (odd(n)) {
            r += a;
            if (n == 1)
                return n;
        }
        n = half(n);
        a += a;
    }
}

int multiply2(int n, int a) {
    return mult_acc4(0, n, a);
}


int multiply(int n, int a) {
    int sum = 0;
    while(n != 1) {
        if (n % 2 == 0) {
            n /= 2;
            a += a;
        } else {
            n -= 1;
            sum += a;
        }
    }
    return sum + a;
}

int main() {
    cout << multiply1(41, 59) << endl << multiply(16, 20) << endl;
}
