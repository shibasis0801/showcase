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
vector<vector<C>> matrix(C default_value) {
    return vector<vector<C>>(rows, vector<C>(cols, default_value));
}

template<class C>
vector<vector<C>> matrix(int rows, int cols) {
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
/**
 * Have to write an implementation for a binary tree
 * Then Graph tomorrow
 */


template <class Data>
struct Tree {
    struct Node {
        Data data;
        Node *left;
        Node *right;
        Node *parent;

        Node(Data data): data(data), left(nullptr), right(nullptr), parent(nullptr)
        {}

        friend ostream& operator<<(ostream &out, const Node &ptr) {
            out << ptr.data;
            return out;
        }

        friend bool operator<(const Node &first, const Node &second) {
            return first.data < second.data;
        }
    };

    Node *root = nullptr;
    
    Tree(): root(nullptr)
    {}

    void insert(Data data) {
        Node *start = root;
        Node *parent = nullptr;
     
        bool isLeftChild = true;
     
        Node *ptr = new Node(data);
     
        if (root == nullptr) {
            root = ptr;
            return;
        }

        while (start) {
            parent = start;

            if (  *ptr < *start ) {
                start = start->left;
                isLeftChild = true;        
            } 
            else {
                start = start->right;
                isLeftChild = false;
            }
        }

        if (isLeftChild) {
            parent->left = ptr;
            ptr->parent = parent;
        }
        else {
            parent->right = ptr;
            ptr->parent = parent;
        }
    }

    void print_inorder(const string &separator, Node *start ) {
        if (start) {
            print_inorder(separator, start->left);
            
            cout << *start;
            
            cout << separator;
            
            print_inorder(separator, start->right); 
        }
    }

    void print_inorder(const string &separator = ", ") {
        print_inorder(separator, root);
    }

    vector<string> inorder(Node *start) {
        if (start) {
            auto left = inorder(start->left);
            auto right= inorder(start->right);
            
            return join({
                left,
                vector<string>(1, toString(*start)),
                right
            });
        }
        else {
            return vector<string>();
        }
    }

    string inorder(const string separator = ", ") {
        return join(inorder(root), separator);    
    }
};


int main() {
    Tree<int> tree;
    for (int i : {12, 5, 2, 9, 18, 15, 19, 13, 17}) {
        tree.insert(i);
    }
    cout << tree.inorder();
}


















