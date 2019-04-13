#include <algorithm>
#include <functional> 
#include <iterator>
#include <iostream>
#include <utility>
#include <string> 
#include <vector>
#include <queue>
#include <stack>

#define repeat(i, n) for (int i = 0; i < n; ++i)
#define all(v) v.begin(), v.end()

const int INF = 999999999;

template <class datatype>
using max_priority_queue = priority_queue<datatype, vector<datatype>, greater<datatype>>;

template <class datatype>
using min_priority_queue = priority_queue<datatype>;

template <class T>
struct maxHeap {
    max_priority_queue<T> Q;

    T dequeue() {
        T data = Q.top();
        Q.pop();
        return data;
    }

    void enqueue(T data) {
        Q.push(data);
    }
}