#include <vector>
#include <iostream>
#include <initializer_list>
using namespace std;

template<class T>
struct list {
    struct node {
        T info;
        node *next;
        node *prev;
        node(int info) : info(info), next(nullptr), prev(nullptr) {}
    };
    node *head = nullptr, *tail = nullptr;
    
    list(){}
    
    list(const initializer_list<T> &items) {
        for(T item : items)
            push_back(item);
    }
    
    list(const vector<T> &items) {
        for(T item : items)
            push_back(item);
    }

    void push_back(T info) {
        node *ptr = new node(info);
        
        if(head == nullptr) 
            head = tail = ptr;
        else {
            ptr->prev = tail;
            tail->next = ptr;
            tail = ptr;
        }
    }

    void push_front(T info) {
        node *ptr = new node(info);

        if(head == nullptr) 
            head = tail = ptr;
        else {
            head->prev = ptr;
            ptr->next  = head;
            head = ptr;
        }
    }

    void pop_front() {
        if(head == nullptr)
            cerr << "HEAD NULL";
        else {
            node *temp = head;
            head->next->prev = nullptr;
            head = head->next;
            delete temp;
        }
    }

    void pop_back() {
        if(tail == nullptr)
            cerr << "TAIL NULL";
        else {
            node *temp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete temp;
        }
    }

    inline
    T front() { 
        if(head == nullptr)
            cerr << "HEAD NULL"; 
        return head->info; 
    }

    inline
    T back() { 
        if(tail == nullptr)
            cerr << "TAIL NULL";
        return tail->info; 
    }

    template<class consumer>
    void for_each(consumer action, node *start, node *end, bool reverse = false) {
        for(node *temp = start; 
            temp != end; 
            temp = (reverse) ? temp->prev : temp->next)  
                action(temp->info);
    }

    template<class consumer>
    void for_each(consumer action) {
        for_each(action, head, tail->next);
    }

    template<class consumer>
    void reverse_for(consumer action) {
        for_each(action, tail, head->prev, true);
    }

    template<class unary_function>
    list map(unary_function functor) {
        list result;
        for_each([&](T info) -> void { result.push_back(functor(info)); });
        return result;
    }

    template<class unary_predicate>
    list filter(unary_predicate test) {
        list result;
        for_each([&](T info) -> void { if(test(info)) result.push_back(info); });
        return result;
    }
    
    node* search(T target) {
        for(node *temp = head; temp != nullptr; temp = temp->next)
            if(temp->info == target)
                return temp;

        return nullptr;
    }

    void remove(T target) {
        node *temp = search(target);
        if(temp == nullptr)
            cerr << "Target Not Found";
        
        if(head == tail)
            head = tail = nullptr;
        else if (head == temp) {
            head->next->prev = nullptr;
            head = head->next;
        } 
        else if (tail == temp) {
            tail->prev->next = nullptr;
            tail = tail->prev;
        }
        else {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }

        delete temp;
    }
    
    inline bool empty() { return head == tail && head == nullptr; }
};

template<class T>
vector<T>
range(T start, T end, T step = 1) {
    vector<T> v;
    for(T i = start; i < end; i += step)
        v.push_back(i);
    return std::move(v);
}

int main() {
    list<int> t = range(1, 100);
    
    auto is_even = [=](int i) -> bool { return i % 2 == 0; };
    auto square  = [=](int i) { return i * i; };
    auto print   = [=](int i) -> void { cout << i << '\n'; };
    
    auto remove_from_t  = [&](int i) -> void { t.remove(i); };

    
    t.filter(is_even).map(square).for_each(print);
    
    t.filter(is_even).for_each(remove_from_t);
    
    t.for_each(print);

    list<int> x = {1, 2, 3, 4, 5};
    x.for_each(print);
}