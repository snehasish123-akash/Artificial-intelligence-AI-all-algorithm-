#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

// Simple hash function for pair<int, int>
struct PairHash {
    size_t operator()(const pair<int, int> &p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

// Manhattan distance function
int manhattanDistance(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

// A* pathfinding function
pair<bool, vector<pair<int, int>>> aStar(
    pair<int, int> start,
    pair<int, int> goal,
    vector<vector<vector<pair<int, int>>>> &graph)
{
    unordered_map<pair<int, int>, int, PairHash> cost;
    unordered_map<pair<int, int>, pair<int, int>, PairHash> cameFrom;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> frontier;

    cost[start] = 0;
    frontier.push({manhattanDistance(start, goal), start});

    while (!frontier.empty()) {
        pair<int, int> current = frontier.top().second;
        frontier.pop();

        if (current == goal) {
            vector<pair<int, int>> path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return {true, path};
        }

        for (auto neighbor : graph[current.first][current.second]) {
            int newCost = cost[current] + 1;
            if (!cost.count(neighbor) || newCost < cost[neighbor]) {
                cost[neighbor] = newCost;
                cameFrom[neighbor] = current;
                int priority = newCost + manhattanDistance(neighbor, goal);
                frontier.push({priority, neighbor});
            }
        }
    }

    return {false, {}};
}

int main() {
    int rows, cols;
    cout << "Enter grid size (rows and columns): ";
    cin >> rows >> cols;

    vector<vector<vector<pair<int, int>>>> graph(rows, vector<vector<pair<int, int>>>(cols));

    cout << "Enter connections (1 if connected, else 0):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < cols; y++) {
                    int connected;
                    cin >> connected;
                    if (connected == 1) {
                        graph[i][j].push_back({x, y});
                    }
                }
            }
        }
    }

    int sx, sy, gx, gy;
    cout << "Enter start cell (row col): ";
    cin >> sx >> sy;
    cout << "Enter goal cell (row col): ";
    cin >> gx >> gy;

    auto result = aStar({sx, sy}, {gx, gy}, graph);

    if (result.first) {
        cout << "Path found:\n";
        for (auto p : result.second) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
