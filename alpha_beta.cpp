#include <iostream>
#include <vector>
#include <climits> // for INT_MIN, INT_MAX
using namespace std;

// Function to perform Alpha-Beta Pruning
int alphaBetaPruning(int depth, int index, bool isMaxPlayer,
                     const vector<int> &leafValues, int maxDepth,
                     int alpha, int beta) {
    // Base Case: If we've reached the bottom of the tree
    if (depth == maxDepth) {
        return leafValues[index];
    }

    if (isMaxPlayer) {
        int best = INT_MIN;

        // Explore left subtree
        int leftVal = alphaBetaPruning(depth + 1, index * 2, false, leafValues, maxDepth, alpha, beta);
        best = max(best, leftVal);
        alpha = max(alpha, best);

        // Prune if possible
        if (beta <= alpha) return best;

        // Explore right subtree
        int rightVal = alphaBetaPruning(depth + 1, index * 2 + 1, false, leafValues, maxDepth, alpha, beta);
        best = max(best, rightVal);
        alpha = max(alpha, best);

        return best;
    } else {
        int best = INT_MAX;

        // Explore left subtree
        int leftVal = alphaBetaPruning(depth + 1, index * 2, true, leafValues, maxDepth, alpha, beta);
        best = min(best, leftVal);
        beta = min(beta, best);

        // Prune if possible
        if (beta <= alpha) return best;

        // Explore right subtree
        int rightVal = alphaBetaPruning(depth + 1, index * 2 + 1, true, leafValues, maxDepth, alpha, beta);
        best = min(best, rightVal);
        beta = min(beta, best);

        return best;
    }
}

int main() {
    int height;
    cout << "Enter the height of the game tree: ";
    cin >> height;

    int numLeaves = 1 << height; // 2^height
    vector<int> leafValues(numLeaves);

    cout << "Enter " << numLeaves << " leaf node values:\n";
    for (int i = 0; i < numLeaves; ++i) {
        cin >> leafValues[i];
    }

    int alpha = INT_MIN;
    int beta = INT_MAX;

    int optimalValue = alphaBetaPruning(0, 0, true, leafValues, height, alpha, beta);

    cout << "Optimal value (using Alpha-Beta Pruning): " << optimalValue << endl;

    return 0;
}
