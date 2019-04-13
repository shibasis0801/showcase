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
	int end;
	int weight;
	edge(){}
	edge(int e, int w) {
		end = e;
		weight = w;
	}

	friend bool operator<(const edge &self, const edge &other);
};

bool operator>(const edge &self, const edge &other) {
	return self.weight > other.weight;
}

vector<vector<edge>> graph(9);

void initgraph() {
	vector<vector<int>> v = {
		{0, 4, 0, 0, 0, 0, 0, 8, 0}, 
		{4, 0, 8, 0, 0, 0, 0, 11, 0}, 
        {0, 8, 0, 7, 0, 4, 0, 0, 2}, 
        {0, 0, 7, 0, 9, 14, 0, 0, 0}, 
        {0, 0, 0, 9, 0, 10, 0, 0, 0}, 
        {0, 0, 4, 14, 10, 0, 2, 0, 0}, 
        {0, 0, 0, 0, 0, 2, 0, 1, 6}, 
        {8, 11, 0, 0, 0, 0, 1, 0, 7}, 
        {0, 0, 2, 0, 0, 0, 6, 7, 0} 
	}; 

	repeat(i, 9) {
		repeat(j, 9) {
			if(v[i][j])
				graph[i].emplace_back(j, v[i][j]);
		}
	}
}

vector<int> 
dijsktra(int source) {
	vector<int> distances(graph.size(), INF);

	priority_queue<edge, vector<edge>, greater<edge>> Q;

	Q.push(edge(source, 0));
	distances[source] = 0;	

	edge src;
	while(!Q.empty()) {
		src = Q.top();
		Q.pop();

		for (edge e : graph[src.end]) {
			if(distances[e.end] > distances[src.end] + e.weight ) {
				distances[e.end] = distances[src.end] + e.weight;
				Q.push(edge(e.end, distances[e.end]));
			}
		}
	}

	return distances;
}

int main() {
	initgraph();
	auto distances = dijsktra(0);
	for (int d : distances)
		cout << d << endl;
}	