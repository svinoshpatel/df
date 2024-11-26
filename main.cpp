#include <vector>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
	int to, length;
};

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<int>& distance, vector<int>& prev)
{
	int n = graph.size();
	distance.assign(n, INF);
	prev.assign(n, -1);
	distance[start] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
	queue.push({0, start});

	while (!queue.empty()) {
		int u = queue.top().second;		
		queue.pop();

		for (const Edge& edge : graph[u]) {
			int v = edge.to;
			int length = edge.length;

			if (distance[v] > distance[u] + length) {
				distance[v] = distance[u] + length;
				prev[v] = u;
				queue.push({distance[v], v});
			}
		}
	}
}

void floydWarshall(vector<vector<int>>& distance) {
	int v = distance.size();
	for (int k = 0; k < v; ++k)
		for (int i = 0; i < v; ++i)
			for (int j = 0; j < v; ++j)
				if (distance[i][k] != INF && distance[k][j] != INF && distance[i][k] + distance[k][j] < distance[i][j])
					distance[i][j] = distance[i][k] + distance[k][j];
}

int main() {
	const int v = 5;
	vector<int> distance;
	vector<int> prev;
	vector<vector<Edge>> graph = {
		{{1, 4}, {2, 2}},
		{{2, 3}, {3, 2}, {4, 3}},
		{{1, 1}, {3, 4}, {4, 5}},
		{},
		{{3, 1}},
	};

	vector<vector<int>> distance2 = {
		{0, 4, 2, INF, INF},
		{INF, 0, 3, 2, 3},
		{INF, 1, 0, 4, 5},
		{INF, INF, INF, 0, INF},
		{INF, INF, INF, 1, 0},
	};

	cout << "Dijkstra: ";
	dijkstra(0, graph, distance, prev);
	for (int i = 0; i < distance.size(); ++i) {
		cout << "Vertex " << i << ": "  << distance[i] << endl;
	}

	cout << "\nFloyd-Warshall: " << endl;
    	floydWarshall(distance2);
    	for (int i = 0; i < distance2.size(); ++i) {
        	for (int j = 0; j < distance2[i].size(); ++j) {
            		if (distance2[i][j] == INF) {
                		cout << "INF ";
			} else {
                		cout << distance2[i][j] << " ";
            		}
        	}
        	cout << endl;
    	}
}
