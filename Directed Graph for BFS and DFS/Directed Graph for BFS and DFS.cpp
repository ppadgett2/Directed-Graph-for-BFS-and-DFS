// Directed Graph for BFS and DFS
// Parker Padgett
// 11-2-23

/*
Given a directed graph and two vertices (say source and destination vertex), determine if the destination
vertex is reachable from the source vertex or not.
If a path exists from the source vertex to the destination vertex, print it.

For example, there exist two paths [0𦠬𧛳] and [0𦠭𧛳] from vertex 0 to vertex 7 in the following graph.

In contrast, there is no path from vertex 7 to any other vertex.

Directed Graph
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int src, dest;
};


class Graph
{
public:
    vector<vector<int>> adjList;

    // Building my contructor...

    Graph(vector<Edge> const& edges, int n)
    {
        adjList.resize(n); // Resized adjacency list to the number of edges...

        //Adding edges to the graph...

        for (auto& edge : edges) // Range based loop...
        {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};

// Perform BFS traversal from given source verte...

bool isReachable(Graph const& graph, int src, int dest)
{
    // Size of the graph...
    int n = graph.adjList.size();

    vector<bool> visited(n); // to keep track of whether you've been to this vertex before

    queue<int> q; // Create a queue for BFS...

    // Mark the source as discovered...
    visited[src] = true;

    // enqueue the source vertex...
    q.push(src);

    while (!q.empty())
    {
        // dequeue from the front and print it...
        int v = q.front(); // Access to the value...
        q.pop(); // Deletes from the queue...

        // If the destination is found...
        if (v == dest)
        {
            return true;
        }

        // Check each edge...
        for (int u : graph.adjList[v])
        {
            if (!visited[u])
            {
                visited[u] = true; // mark the node as visited...
                q.push(u);
            }
        }
    }
    return false;
}


// Perform DFS traversal in directed graph...

bool isReachableDFS(Graph const& graph, int src, int dest, vector<bool>& visited, vector<int>& path)
{
    // mark the current node as visited...
    visited[src] = true;

    // include the current node to the path...
    path.push_back(src);

    // if vertex is found...
    if (src == dest)
    {
        return true;
    }

    // do for every edge
    for (int i : graph.adjList[src])
    {
        // if 'u' has been visited...
        if (!visited[i])
        {
            if (isReachableDFS(graph, i, dest, visited, path))
            {
                return true;
            }
        }
    }

    // backtrack: remove the current node from the path...
    path.pop_back();

    // if destination is not found...
    return false;
}

// Helper function to print out the path...
void printPath(vector<int> const& path)
{
    for (int i : path)
    {
        cout << i << ' ';
    }
    cout << endl;
}

int main()
{
    // Vector of graph edges based on the example...
    vector<Edge> edges = {
        {0,3}, {1,0}, {1,2}, {1,4}, {2,7}, {3,4}, {3,5}, {4,3}, {4,6}, {5,6}, {6,7}
    };

    // Total number of edges...
    int n = 8;

    // Build a graph...
    Graph graph(edges, n);

    // to keep track of visited verticecs...
    vector<bool> visited(n);

    // Source and destination edges...
    int src = 0, dest = 7;

    // vector to store the path...
    vector<int> path;


    // perform the DFS...
    if (isReachableDFS(graph, src, dest, visited, path))
    {
        cout << "Path exists from vertex " << src << " to vertex " << dest;
        cout << " The complete path is ";
        printPath(path);
    }
    else
    {
        cout << "No path exists! ";
    }

    // perform the BFS...
    /*if(isReachable(graph, src, dest))
    {
        cout << "Path exists from vertex " << src << " to vertex " << dest;
    }
    else
    {
        cout << "No path exists!";
    }
    */

    return 0;
}