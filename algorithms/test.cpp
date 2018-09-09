#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define repeat(i, n) for ( int i = 0; i < n; ++i )
#define inverse_for(i, n) for ( int i = n; i >= 0; --i )

void print() {}

template<typename T, typename... Types>
void print(const T& first, const Types&... rest) {
    cout << first << " ";
    print(rest...);
}

template<class C, int rows, int cols>
vector<vector<C>> matrix(C default_value) {
    return vector<vector<C>>(rows, vector<C>(cols, default_value));
}

template<class C>
vector<vector<C>> matrix(int rows, int cols) {
    return vector<vector<C>>(rows, vector<C>(cols));
}


template<class... T>
vector join(const vector<T> &first, const vector<T>... &items) {

}

int main()
{ }
