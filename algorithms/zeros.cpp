#include <cstdlib>
#include <cmath>
#include <ctime>
#include <limits>
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

const int inf = numeric_limits<int>::max();

#define repeat(i, n) for ( int i = 0; i < n; ++i )
#define inverse_for(i, n) for ( int i = n; i >= 0; --i )

namespace mod
{
    template<class C>
    vector<vector<C>> Matrix(int rows, int cols, C default_value) {
        return vector<vector<C>>(rows, vector<C>(cols, default_value));
    }

    template<class C>
    vector<vector<C>> Matrix(int rows, int cols) {
        return vector<vector<C>>(rows, vector<C>(cols));
    }
}
namespace mod 
{
    void print() {}

    template<typename T, typename... Types>
    void print(const T& first, const Types&... rest) {
        cout << first << " ";
        print(rest...);
    }
}
namespace mod {
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
}
namespace mod 
{
    template<class T>
    string toString(T data) {
        ostringstream oss;
        oss << data;
        return oss.str();
    }

    template<class T>
    string join(const vector<T> &items, const string separator = ", ") {
        ostringstream oss;
        int n = items.size();
        repeat(i, n) {
            oss << items[i];
            if ( i != n - 1 )
                oss << separator;
        }
        return oss.str();
    }

    string concat() { return ""; }

    template<class T, class... Types>
    string concat(const T &first, const Types&... rest) {
        return toString(first) + concat(rest...);
    }
}
namespace mod
{

    template <class A, class B> class couple;
    template <class A, class B> ostream& operator<<(ostream&, const couple<A, B>&);
    template<class A, class B> 
    struct couple {
        // Improvement over std::pair in simplicity.
        // I believe that STL is not at all extendable. 
        A first;
        B second;

        couple() {}

        couple(A first, B second): first(first), second(second)
        {}

        friend ostream& operator<< <A, B> (ostream &os, const couple<A, B> &c);

    };
    template<class A, class B>
    ostream& operator<<(ostream &os, const couple<A,B> &c) {
        os << concat("( ", c.first, ", ", c.second, " )");
        return os;
    }

}

using namespace mod;

decltype(auto) random_zero_vector(int size, int probability) {
    vector<int> zeros (size, 0);
    repeat(i, size) {
        double p = rand() / (double) RAND_MAX; 
        if (10 * p > probability)
            zeros[i] = rand() % 10;
    }
    return zeros;
}


decltype(auto) reorder(vector<int> &numbers) {
    
    int zero_idx = 0, non_idx = 0;
    int size = numbers.size();

    while( numbers[zero_idx] != 0 )
        ++zero_idx;

    while( numbers[non_idx] != 0)
        ++non_idx;
    
    if ( zero_idx == size - 1 || non_idx == size - 1 )
        return numbers;

    while(non_idx != size) {
        
        if (numbers[non_idx] != 0) {
            swap(numbers[zero_idx], numbers[non_idx]);
            zero_idx++;
        }
        non_idx++;
    }
    return numbers;
}

int main(int argc, char **argv) {
    srand(time(0));
    int size, prob;

    cin >> size >> prob;
    auto zeros = random_zero_vector(size, prob);
    cout << join(z eros) << endl;
    cout << join(reorder(zeros)) << endl;


}

