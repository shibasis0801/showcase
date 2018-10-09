#include <type_traits>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <limits>
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
//Start Here


template<class T>
vector<T> array_copy(
    const vector<T> &source,
    int start,
    int count 
) {
    vector<T> copied (count);
    
    repeat(i, count) 
        copied[i] = source[start + i];
    
    return copied;
}


template<class T>
void merge(vector<T> &array, int start, int mid, int end) {

    int count_left = mid - start + 1;
    int count_right= end - (mid + 1) + 1;

    auto left = array_copy(array, start, count_left);
    auto right= array_copy(array, mid + 1, count_right);

    int idx_main = start;
    int idx_left = 0;
    int idx_right= 0;
    
    while ( idx_left < count_left || idx_right < count_right) {


        if (left[idx_left] < right[idx_right]) {
            
            array[idx_main] = left[idx_left];
            ++idx_left;
            ++idx_main; 
        }
        else {

            array[idx_main] = right[idx_right];
            ++idx_right;
            ++idx_main;
        }
    }

    while (idx_left < count_left) {
        
        array[idx_main] = left[idx_left];
        ++idx_left;
        ++idx_main;
    }

    while (idx_right < count_right) {

        array[idx_main] = right[idx_right];
        ++idx_right;
        ++idx_main;
    }
}

template<class T>
void merge_sort(vector<T> &array, int start, int end) {
    if (start != end) {
        int mid = start + (end - start) / 2;
        merge_sort(array, start, mid);
        merge_sort(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}


// Must be numeric type for now.
template<class T>
void merge_sort(vector<T> &array) {
    if (!array.empty())
        merge_sort(array, 0, array.size() - 1);
}

random_device random_seed;
mt19937 random_generator(random_seed());


decltype(auto) random_int_vector(int size, int start, int end) {
    uniform_int_distribution<> distribution(start, end);

    vector<int> ranvec (size);
    
    repeat(i, size) 
        ranvec[i] = distribution(random_generator);
    
    return ranvec;
}


int main() {
    vector<int> test = random_int_vector(10, 0, 100);
    // merge_sort(test);
    cout << join(test) << "\n"; 
}










































