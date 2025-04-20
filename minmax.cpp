#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Minimax function
int minimax(int depth, int nodeIndex, bool isMax, vector<int> &leaves, int height)
{
    // Base case: leaf node
    if (depth == height)
        return leaves[nodeIndex];

    if (isMax)
    {
        // Maximizer's move
        return max(
            minimax(depth + 1, nodeIndex * 2, false, leaves, height),
            minimax(depth + 1, nodeIndex * 2 + 1, false, leaves, height));
    }
    else
    {
        // Minimizer's move
        return min(
            minimax(depth + 1, nodeIndex * 2, true, leaves, height),
            minimax(depth + 1, nodeIndex * 2 + 1, true, leaves, height));
    }
}

int main()
{
    int height;
    cout << "Enter height of the game tree (e.g., 3): ";
    cin >> height;

    int leafCount = 1 << height; // 2^height
    vector<int> leaves(leafCount);

    cout << "Enter " << leafCount << " leaf node values (game scores):\n";
    for (int i = 0; i < leafCount; ++i)
    {
        cin >> leaves[i];
    }

    int optimalValue = minimax(0, 0, true, leaves, height);
    cout << "Optimal value using Minimax: " << optimalValue << endl;

    return 0;
}
