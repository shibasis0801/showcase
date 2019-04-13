#include <bits/stdc++.h>

typedef unsigned int uint;
typedef unsigned long long ulong_uint;

#define repeat(i, n) for (long_uint i = 0; i < n; ++i)

using namespace std;

struct printer { 
    string separator = " ";
    
    printer() {}
    printer(string separator): separator(separator) 
    {}

    template<class... T>
    void operator()(T... args) {
        ((cout << args << separator), ...);
    }

} print;
template<class... T>
void println(const T&... args) {
    print(args...);
    cout << '\n';
}

decltype(auto)
return_tuple(int i) {
    return tuple("square", i, i * i, i / 2.0);
}

template <class... T>
int sum(const T&... numbers) { 
    return (... + numbers);
}
 
template <class K, class V>
void 
iterate_map(const map<K, V> &dict) {
    for (auto [name, relation] : dict) {
        println(name, "is my", relation);
    }
}

decltype(auto)
create_map() {
    map<string, string> family;

    family.insert(pair("Papu", "Father"));
    family.insert(pair("Mama", "Mother"));
    family.insert(pair("Rini", "Sister"));
    family.insert(pair("Charan", "BrotherIL"));
    family.insert(pair("Som", "Brother"));
    family.insert(pair("Sonu", "Brother"));
    family.insert(pair("Mitul", "Sister"));

    return family;
}

/*
template <class T>
vector<T> input_vector(int n = -1, istream &is = cin) {

    vector<T>input;
    if (n != -1) {
        input.resize(n);
        repeat(i, n) 
            is >> input[i];
    }
    else {
        while(T data; is >> data) 
            input.push_back(data);
    }

    return input;
}
*/

struct range {
    int start, finish;
    int stride;

    range(int start, int finish) : start(start), finish(finish), stride(1) {}
    range(int start, int finish, int stride) : start(start), finish(finish), stride(stride) {}

    struct iterator;

    iterator begin() {
        return iterator(start, stride);
    }

    iterator end() {
        return iterator(finish, stride);
    }

    range step(int stride) {
        int offset;
        
        if (this->stride == 1 || stride == 1)
            offset = -1;

        return range(start, finish, offset + stride + this->stride);
    }

    struct iterator {
        
        int value;
        int step = 1;
        iterator(int value, int step) : value(value), step(step) {}

        iterator &operator=(int element) {
            value = element;
            return *this;
        }
        
        // Prefix
        iterator &operator++() {
            value += step;
            return *this;
        }

        // Postfix
        iterator operator++(int) {
            auto temp = iterator(value, this->step);
            value += step;
            return temp;
        }

        bool operator!=(const iterator &iter) {
            return value < iter.value;
        }

        int operator*() {
            return value;
        }
    };
};

int main() {
    auto [square, i, i2, iby2] = return_tuple(5);
    
    println(1, 2, 3, 4);
    println(1, 2, 3, 4);
    println(sum(1, 2, 3, 4, 5));

    auto family = create_map();
    iterate_map(family);

    for (int i : range(1, 10).step(2))
        println(i);

    // Continue this tomorrow.
    // https://www.fluentcpp.com/2018/06/19/3-simple-c17-features-that-will-make-your-code-simpler/

}