// Description:
// For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree.
// Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs).
// Given such a graph, write a function to find all the MHTs and return a list of their root labels.

// Format
// The graph contains n nodes which are labeled from 0 to n - 1.
// You will be given the number n and a list of undirected edges (each edge is a pair of labels).

// You can assume that no duplicate edges will appear in edges.
// Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

// Example 1 :
// Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]
//         0
//         |
//         1
//        / \
//       2   3 
// Output: [1]

// Example 2 :
// Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
//      0  1  2
//       \ | /
//         3
//         |
//         4
//         |
//         5 
// Output: [3, 4]

// BFS Topological Sort:
// Remove the leaves, update the degrees of inner vertexes.
// Then remove the new leaves. Doing so level by level until there are 2 or 1 nodes left.
// What's left is the answer
// The time complexity and space complexity are both O(n).

#include <vector>
#include <unordered_set>
using std::vector;
using std::unordered_set;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return vector<int>{0};
        vector<unordered_set<int>> graph(n);
        for (vector<int> edge: edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        
        vector<int> leaves;
        // add leaves into the queue
        for (int i = 0; i < n; ++i) {
            if (graph[i].size() == 1) {
                leaves.push_back(i);
            }
        }
        
        while (n > 2) {
            // remove the leaves
            n -= leaves.size();
            vector<int> newLeaves;
            for (int node: leaves) {
                // update the degrees of inner vertexes.
                for (int adj: graph[node]) {
                    graph[adj].erase(node);
                    if (graph[adj].size() == 1) {
                        newLeaves.push_back(adj);
                    }
                }
            }
            leaves = newLeaves;
        }
        return leaves;
    }
};