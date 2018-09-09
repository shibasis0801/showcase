#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
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
template<class C>
vector<vector<C>> Matrix(int rows, int cols, C default_value) {
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


vector<vector<Node *>> level_order_traversal() {
        
    DFSQueue<Node *> Q;
    int level = 0;
    Q.enqueue(root, level);

    while ( ! Q.empty() ) {
        Node *ptr = Q.dequeue();

        auto nodes = children(ptr);

        for (Node *child : nodes) 
            Q.enqueue(child, level);
    }

    return Q.levels;
}

template <class Data>
struct DFSQueue{
    /**
     * Stores Nodes found in DFS in a 2D vector.
     * Each 1D vector contains all nodes in that layer.
     */

    queue<Data> Q;
    Map<Node *, int> distance;
    vector<vector<Data>> levels;

    void enqueue(Data data, int level) {
        
        if ( level < levels.size() )
            levels.push_back(vector<Data>());

        Q.push(data);
        levels[level].push_back(data);    
    }

    Data dequeue() {

        Data data = Q.front();
        Q.pop();
        return data;
    }

    bool empty() {
        return Q.empty();
    }
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
        
        Node *ptr = new Node(data);
     
        if (root == nullptr) {
            root = ptr;
            return;
        }

        Node *start = root;
        Node *parent = nullptr;
     
        bool isLeftChild = true;

        while (start) {

            parent = start;

            isLeftChild = *ptr < *start;

            start = isLeftChild ? start->left : start->right;
        }

        ptr->parent = parent;

        if (isLeftChild) 
            parent->left = ptr;
        else 
            parent->right = ptr;

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



    vector<Node *> children(Node *ptr) {

        vector<Node *> ptrs;
        
        if (ptr->left)
            ptrs.push_back(ptr->left);
        if (ptr->right)
            ptrs.push_back(ptr->right);

        return ptrs;

    }


    void level_order_traversal() {
        
        queue<Node *> Q;
        Q.push(root);

        int level = 0;
        vector<vector<Node *>> levels;

        levels.push_back(vector<Node *>());
        levels[level].push_back(root);

        while( ! Q.empty() ) {

            Node *ptr = Q.front();
            Q.pop();
            level++;

            auto nodes = children(ptr);
            
            if ( ! nodes.empty() )
                levels.push_back(vector<Node *>());
            
            for (Node *child : nodes) {
        
                Q.push(child);
                levels[level].push_back(child);

            }
        }
    }

};


int main() {
    Tree<int> tree;
    for (int i : {12, 5, 2, 9, 18, 15, 19, 13, 17}) {
        tree.insert(i);
    }
    cout << tree.inorder() << endl;
    
    
}


















