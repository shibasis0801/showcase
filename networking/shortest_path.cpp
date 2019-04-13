/*

1. Implement the shortest path algorithm for a topology of 50 nodes with following features:
a. Let the topology be formed by giving the node ID and its transmission range as input.
b. Let the link be established by checking the range of the nodes and assign random weights to the links established.
c. Consider 5 pairs of (source, destination)
d. For every such pair find the shortest path while storing the sequence of working nodes in a table.


n = 50, create K50

then assign different x, y coordinates randomly.

Use adjacency list

Take 5 random nodes and find shortest distance

find a random node and find the minimum cost if one travels to all vertices atleast once


*/


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

using namespace std;

template <class T>
vector<vector<T>> matrix(int rows, int cols) {
	return vector<vector<T>> (rows, vector<T>(cols));
}

struct point {
	int x;
	int y;

	point(){}

	point(pair<int, int> p) {
		x = p.first;
		y = p.second;
	}

	friend bool operator< (const point &one, const point &two);
	friend ostream& operator<<(ostream &os, const point &ti);
};


bool operator< (const point &one, const point &two) {
	bool x = one.x < two.x;
	
	bool x_equal = one.x == two.y;

	bool y = one.y < two.y;

	return x || (x_equal && y);
}

ostream& operator<<(ostream &os, const point &ti) {
	os << ti.x << ", " << ti.y;
	return os;
}


int distance(const point &one, const point &two) {

	return sqrt(
		pow(one.x - two.x, 2) +
		pow(one.y - two.y, 2)
	);
}

int random(int max) {
	return rand() % max;
}

vector<point> 
generate_random_points(int n) {
    set<point> points;

    while (points.size() != n) {
    	auto p = point(minmax(random(2 * n), random(2 * n)));
    	points.insert(p);
    }

    vector<point> point_vector;

    for (auto p : points)
    	point_vector.push_back(p);

    random_shuffle(all(point_vector));

    return point_vector;
}


decltype(auto) 
random_adjacency_matrix(int n) {
	auto adjacency_matrix = matrix<int>(n,n);
	auto points = generate_random_points(n);

	random_device random_device;
    mt19937 generator(random_device());

    uniform_int_distribution<> distribution(1, n * 5);

	repeat(i, n)
		repeat(j, i){
			int d = random(10) * distance(points[i], points[j]) + 5;
			adjacency_matrix[j][i] = adjacency_matrix[i][j] = d;
		}

	return adjacency_matrix;
}

void print_matrix(auto matrix) {
	repeat(i, matrix.size()){
		repeat(j, matrix.size()) {
			cout << matrix[i][j] << '\t';
		}
		cout << endl;	
	}
}

decltype(auto)
floyd_warshall(const auto& graph) {
	auto result = graph;
	int V = graph.size();

	repeat(k, V) {
		repeat(i, V) {
			repeat(j, V) {
				
				int sum = result[i][k] + result[k][j];

				if (result[i][j] > sum)
					result[i][j] = sum;
			}
		}
	}
	return result;
}

struct node {
	int index;
	int distance;

	node(int i, int d): index(i), distance(d) 
	{}
	
	friend bool operator> (const node &one, const node &two);
};

bool operator> (const node &one, const node &two) {
	return one.distance > two.distance;
}

int prim_cost(const auto &graph) {

	int inf = 999999;

	priority_queue<node, vector<node>, greater<node>> Q;


	int size = graph.size();

	vector<int> key (size, inf);
	vector<int> parent(size, -1);
	vector<bool> inMST(size, false);

	int source = random(size);

	Q.push(node(source, 0));
	key[source] = 0;

	int cost = 0;

	while( !Q.empty()) {
		auto top = Q.top();
		Q.pop();

		int src = top.index;


		inMST[src] = true;

		repeat(i, size) {
			if (i != src) {
				int d = graph[src][i];

				if(inMST[i] == false && key[i] > d) {
					key[i] = d;
					Q.push(node(i, d));
					cost += d;
					parent[i] = src;
				}
			}
		}

	}

	return cost;
}


int main() {

	srand(time(0));

	int n;
	cout << "Enter N\n";
	cin >> n;
	
	auto adjmat = random_adjacency_matrix(n);

	print_matrix(adjmat);

	auto shortest_path_pairs = floyd_warshall(adjmat);

	cout << '\n';

	print_matrix(shortest_path_pairs);

	cout << '\n';

	cout << "Query for distances by typing a b to find distance(a,b) , type -1 -1 to end\n";

	int a,b;
	while(true) {
		cin >> a >> b;
		if (a != -1 && b != -1)
			cout << shortest_path_pairs[a][b] << '\n';
		else 
			break;
	}


	cout << "Prim Cost = " << prim_cost(adjmat) << endl;
}