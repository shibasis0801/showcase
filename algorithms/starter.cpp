#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
/**
 * Utils
 */
#define repeat(i, n) for ( int i = 0; i < n; ++i )
#define inverse_for(i, n) for ( int i = n; i >= 0; --i )

void print() {}

template<typename T, typename... Types>
void print(const T& first, const Types&... rest) {
    cout << first << " ";
    print(rest...);
}

/**
 * Matrix
 */

template<class C, int rows, int cols>
vector<vector<C>> Matrix(C default_value) {
    return vector<vector<C>>(rows, vector<C>(cols, default_value));
}

template<class C>
vector<vector<C>> Matrix(int rows, int cols) {
    return vector<vector<C>>(rows, vector<C>(cols));
}


/**
 * Vector
 */

//Not much efficient. But simple to understand and use.
template<class T>
vector<T> join(const vector<vector<T>> &items) {
    vector<T> flatten;
    for (const auto &vec : items) {
        for (auto item : vec) {
            flatten.push_back(item);
        }
    }
    return std::move(flatten);
}

template<class T>
vector<T> join(const initializer_list<vector<T>> &items) {
    vector<T> flatten;
    for (const auto &vec : items) {
        for (auto item : vec) {
            flatten.push_back(item);
        }
    }
    return std::move(flatten);
}

/**
 * String
 */
template<class T>
string toString(T data) {
    ostringstream oss;
    oss << data;
    return oss.str();
}

string join(const vector<string> &items, const string separator = ", ") {
    ostringstream oss;
    int n = items.size();
    repeat(i, n) {
        oss << items[i];
        if ( i != n - 1 )
            oss << separator;
    }
    return oss.str();
}
