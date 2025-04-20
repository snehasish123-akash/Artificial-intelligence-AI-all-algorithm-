// file: iddfs_search.cpp

#include <iostream>
#include <vector>
using namespace std;

// Simple depth-limited DFS function
bool depthLimitedDFS(int current, int target, const vector<vector<int>> &graph, int depth, vector<bool> &visited) {
    if (depth == 0 && current == target) {
        return true;
    }
    if (depth == 0) {
        return false;
    }

    visited[current] = true;

    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (depthLimitedDFS(neighbor, target, graph, depth - 1, visited)) {
                return true;
            }
        }
    }

    return false;
}

// Iterative Deepening DFS function
bool iterativeDeepeningDFS(int start, int target, const vector<vector<int>> &graph, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; depth++) {
        vector<bool> visited(graph.size(), false);
        if (depthLimitedDFS(start, target, graph, depth, visited)) {
            return true;
        }
    }
    return false;
}

int main() {
    int numVertices, numEdges;
    int startVertex, targetVertex, maxDepth;

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
        graph[to].push_back(from); // because the graph is undirected
    }

    cout << "Enter start vertex: ";
    cin >> startVertex;

    cout << "Enter target vertex: ";
    cin >> targetVertex;

    cout << "Enter maximum depth: ";
    cin >> maxDepth;

    bool found = iterativeDeepeningDFS(startVertex, targetVertex, graph, maxDepth);

    if (found) {
        cout << "Target found within the depth limit.\n";
    } else {
        cout << "Target NOT found within the depth limit.\n";
    }

    return 0;
}
