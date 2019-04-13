#include <bits/stdc++.h>

#include "../library/printer.hpp"
#include "../library/range.hpp"

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