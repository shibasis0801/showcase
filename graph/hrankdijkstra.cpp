#include <bits/stdc++.h>

using namespace std;

#define repeat(i, n) for (int i = 0; i < n; ++i)

struct half_edge {
    int end;
    int weight;

    half_edge() {}

    half_edge(int e, int w) {
        end = e;
        weight = w;
    }

    friend bool operator>(half_edge one, half_edge two);
};

bool operator>(half_edge one, half_edge two) {
    return one.weight > two.weight;
}

template <class T>
using minHeap = priority_queue<T, vector<T>, greater<T>>;

const int inf = 9999999;

// Complete the shortestReach function below.
vector<int> shortestReach(vector<vector<half_edge>> adjList, int source) {
    vector<int> distance(adjList.size(), inf);
    minHeap<half_edge> Q;

    distance[source] = 0;
    for ( auto edge : adjList[source] ) {
        Q.push(edge);
        distance[edge.end] = edge.weight;

    }

    while ( !Q.empty() ) {

        auto minEdge = Q.top();
        Q.pop();

        for (auto edge : adjList[minEdge.end]) {
            if (distance[edge.end] > distance[minEdge.end] + edge.weight) {
                distance[edge.end] = distance[minEdge.end] + edge.weight;
                Q.push(edge);
            }
        }
    }

    return distance;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;

    int vertexCount, edgeCount, source;

    for (int t_itr = 0; t_itr < t; t_itr++) {

        cin >> vertexCount >> edgeCount; 

        vector<vector<half_edge>> adjList(vertexCount);
        
        int start, end, weight;

        repeat(i, edgeCount) {
            cin >> start >> end >> weight;

            start -= 1;
            end -= 1;

            adjList[start].emplace_back(end, weight);
            adjList[end].emplace_back(start, weight);

        }

        cin >> source;
        source -= 1;

        vector<int> result = shortestReach(adjList, source);

        repeat (i, vertexCount) {

            int distance = ( result[i] == inf )? -1 : result[i]; 

            if ( i != source ) {
                cout << distance;
                cout << " ";
            }
        }

        cout << "\n";
    }

    return 0;
}
