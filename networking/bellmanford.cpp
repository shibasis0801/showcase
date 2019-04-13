#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

#define repeat(i, n) for (int i = 0; i < n; ++i)
#define all(v) v.begin(), v.end()

const int INF = 999999999;

using namespace std;

int random(int max) {
	return rand() % max;
}

void print() {}

template<typename T, typename... Types>
void print(const T& first, const Types&... rest) {
    cout << first << " ";
    print(rest...);
}


struct edge {
	int start;
	int end;
	double weight;

	edge(int start, int end, double weight): start(start), end(end), weight(weight)
	{}

	friend ostream& operator<<(ostream& os, const edge &e);
	friend istream& operator<<(istream& is, edge &e);
};

ostream& operator<<(ostream& os, const edge &e) {
	os << '(' << e.start << ", " << e.end << ')' << " -> " << e.weight;
	return os;
}


istream& operator<<(istream& is, edge &e) {
	is >> e.start >> e.end >> e.weight;
	return is;
}

struct Graph {
	vector<int> V;
	vector<edge> E;

	Graph(int n_vertices): V(vector<int>(n_vertices))
	{}

	bool vertexExists(int v) {
		return 0 <= v && v < V.size();
	}

	void addEdge(int start, int end, double weight) {
		
		if (vertexExists(start) && vertexExists(end)) 
			E.emplace_back(start, end, weight);
		else 
			cerr << "start or end not correct\n";
	}
};

vector<double> 
bellman_ford(Graph &graph, int source) {
	
	int V = graph.V.size();
	vector<double> distances(V, INF);

	distances[source] = 0;

	repeat(i, V - 1) {
		for(const edge &e : graph.E) {
			if (distances[e.start] != INF) {
				if (distances[e.end] > distances[e.start] + e.weight)
					distances[e.end] = distances[e.start] + e.weight;
			}
		}
	}

	for(const edge &e : graph.E) {
		if (distances[e.end] > distances[e.start] + e.weight)
			cerr << "Negative weight cycle";
	}

	return distances;
}


int main() {
	int n;
	cin >> n;

	Graph graph(n);
	int e;
	cin >> e;

	int start, end;
	double weight;
	while(e--) {
		cin >> start >> end >> weight;
		graph.addEdge(start, end, weight);
	}

	for(auto e : graph.E) {
		cout << e << endl;
	}

	auto distances = bellman_ford(graph, 0);

	repeat(i, distances.size()) {
		cout << i << "->" << distances[i] << endl;
	}
}





