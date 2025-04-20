#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Simple heuristic function (returns constant value)
double simpleHeuristic(int a, int b) {
    return 1.0;
}

// Best First Search Algorithm
pair<bool, vector<int>> bestFirstSearch(int start, int goal, vector<vector<int>> &graph) {
    unordered_map<int, double> cost;
    unordered_map<int, int> parent;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    cost[start] = 0;
    pq.push({simpleHeuristic(start, goal), start});

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        if (current == goal) {
            vector<int> path;
            while (current != start) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return {true, path};
        }

        for (int neighbor : graph[current]) {
            double newCost = cost[current] + 1;
            if (cost.find(neighbor) == cost.end() || newCost < cost[neighbor]) {
                cost[neighbor] = newCost;
                parent[neighbor] = current;
                pq.push({simpleHeuristic(neighbor, goal) + newCost, neighbor});
            }
        }
    }

    return {false, {}};
}

int main() {
    int numVertices, numEdges;
    int start, goal;

    cout << "Enter number of vertices: ";
    cin >> numVertices;

    vector<vector<int>> graph(numVertices);

    cout << "Enter number of edges: ";
    cin >> numEdges;

    cout << "Enter each edge (from to):\n";
    for (int i = 0; i < numEdges; i++) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
        graph[to].push_back(from);  // assuming undirected graph
    }

    cout << "Enter start vertex: ";
    cin >> start;

    cout << "Enter goal vertex: ";
    cin >> goal;

    pair<bool, vector<int>> result = bestFirstSearch(start, goal, graph);

    if (result.first) {
        cout << "Path found: ";
        for (int node : result.second) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
