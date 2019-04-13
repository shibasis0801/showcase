#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>

using namespace std;

#define repeat(i, n) for (int i = 0; i < n; ++i)
#define all(v) v.begin(), v.end()

const int INF = 999999999;

struct partial_edge {
    int end;
    int weight;


    partial_edge(int end = -1, int weight = INF) : end(end), weight(weight) {}

    friend istream& operator>>(istream &is, partial_edge &edge);
    friend ostream& operator<<(ostream &is, partial_edge &edge);
    friend bool operator<(const partial_edge &one, const partial_edge &two);
};

istream& operator>>(istream &is, partial_edge &edge) {
    is >> edge.end >> edge.weight;
    return is;
}

ostream& operator<<(ostream &os, partial_edge &edge) {
    os << edge.end << " => " << edge.weight;
    return os;
}

bool operator>(const partial_edge &one, const partial_edge &two) {
    return one.weight > two.weight;
}

vector<vector<partial_edge>> parseInput() {
    vector<vector<partial_edge>> edges;
    
    partial_edge edge;
    int start;
    while (cin >> start && cin >> edge) {
        
        auto [end, weight] = edge;
        
        if (start >= edges.size())
            edges.resize(start + 1);

        edges[start].push_back(edge);
    }

    return edges;
}

decltype(auto) dijkstra(int source, const vector<vector<partial_edge>> &adj_list) {

    vector<int> distance(adj_list.size(), INF);
    vector<int> parent(adj_list.size(), -1);
    priority_queue<partial_edge, vector<partial_edge>, greater<partial_edge>> Q;

    distance[source] = 0;
    Q.emplace(source, 0);

    while ( ! Q.empty() ) {
        auto [ node_end, node_distance ] = Q.top();
        Q.pop();

        for (auto edge : adj_list[node_end]) {
            
            if (distance[edge.end] > distance[node_end] + edge.weight) {
                distance[edge.end] = distance[node_end] + edge.weight;
                Q.push(edge);
                parent[edge.end] = node_end;
            }
        }
    }

    return make_pair(distance, parent);
}

string path(const vector<int> &parent, int source, int destination) {
    
    
    if (source == destination)
        return to_string(source);
    else if (parent[destination] == -1)
        return "No Path Found";

    return path(parent, source, parent[destination]) + " -> " + to_string(destination);

}

int main() {
    auto adjList = parseInput();
    
    auto [ distance, parent ] = dijkstra(0, adjList);

    cout << path(parent, 0, 5) << endl;
}