#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Simple tree node structure
struct Node {
    int value;
    vector<Node*> children;

    Node(int val) {
        value = val;
    }
};

// Heuristic function (just returns the value)
int heuristic(Node* node) {
    return node->value;
}

// Beam Search algorithm
void beamSearch(Node* root, int beamWidth, int goal) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        vector<Node*> currentLevel;

        // Visit all nodes in the current level
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            Node* current = q.front();
            q.pop();

            cout << "Visiting node: " << current->value << endl;

            if (current->value == goal) {
                cout << "Goal found: " << current->value << endl;
                return;
            }

            for (int j = 0; j < current->children.size(); j++) {
                currentLevel.push_back(current->children[j]);
            }
        }

        // Sort nodes by heuristic value (descending)
        sort(currentLevel.begin(), currentLevel.end(), [](Node* a, Node* b) {
            return heuristic(a) > heuristic(b);
        });

        // Push top-k (beam width) nodes to the queue
        for (int i = 0; i < beamWidth && i < currentLevel.size(); i++) {
            q.push(currentLevel[i]);
        }
    }

    cout << "Goal not found in the tree." << endl;
}

int main() {
    int beamWidth, goal;
    cout << "Enter beam width: ";
    cin >> beamWidth;
    cout << "Enter goal value: ";
    cin >> goal;

    // Build tree manually
    Node* root = new Node(1);
    Node* child1 = new Node(4);
    Node* child2 = new Node(3);
    Node* child3 = new Node(2);

    root->children = {child1, child2, child3};

    child1->children = {new Node(10), new Node(5)};
    child2->children = {new Node(8), new Node(6)};
    child3->children = {new Node(7), new Node(9)};

    beamSearch(root, beamWidth, goal);

    return 0;
}
