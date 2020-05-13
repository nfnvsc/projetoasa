#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#define CAPACITY 1

using namespace std;

struct Edge
{
    int u;      // Origin
    int v;      // Destination
    int cap;
    int flux;   // Current flux
};

class Graph {
public:
    Graph(int V) : source(-1), sink(-1)
    {
        intraEdges = (Edge*)malloc(sizeof(Edge)*V);
        adjacencyList.resize(V);
        numberOfVertices = V;
    }
    void addIntraEdge(int u)
    {   

        //Edge edge = {u, u, CAPACITY, 0};
        intraEdges[u] = {u, u, CAPACITY, 0}; 
    }
    void addEdge(int u, int v)
    {        
        adjacencyList[u].push_back({u, v, CAPACITY, 0});
    }
    void clearEdges(int u)
    {        
        adjacencyList[u].clear();
    }
    void setMarkets(int m) {
        markets = m;
    }
    void setHouses(int h) {
        houses = h;
    }
    void setSource(int s)
    {
        source = s;
    }
    void setSink(int s)
    {
        sink = s;
    }
    bool bfs(int rGraph[V][V], int parent[])
    {
        // Create a visited array and mark all vertices as not visited
        bool visited[numberOfVertices];
        memset(visited, 0, sizeof(visited));

        // Create a queue, enqueue source vertex and mark source vertex
        // as visited
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        // Standard BFS Loop
        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (auto &edge : adjacencyList[current]) {

                if (visited[edge.v] == false) {
                    q.push(edge.v);
                    parent[edge.v] = current;
                    visited[edge.v] = true;
                }
            }
        }

        // If we reached sink in BFS starting from source, then return
        // true, else false
        return (visited[sink] == true);
    }
    int fordFulkerson() {
        int u, v;

        // Create a residual graph and fill the residual graph with
        // given capacities in the original graph as residual capacities
        // in residual graph
        int rGraph[][V]; // Residual graph where rGraph[i][j] indicates
                          // residual capacity of edge from i to j (if there
                          // is an edge. If rGraph[i][j] is 0, then there is not)
        for (u = 0; u < V; u++)
            for (v = 0; v < V; v++)
                rGraph[u][v] = graph[u][v];

        int parent[numberOfVertices]; // This array is filled by BFS and to store path

        int max_flow = 0; // There is no flow initially

        // Augment the flow while tere is path from source to sink
        while (bfs(rGraph, parent))
        {
            // Find minimum residual capacity of the edges along the
            // path filled by BFS. Or we can say find the maximum flow
            // through the path found.
            int path_flow = INT_MAX;
            for (v = sink; v != source; v = parent[v])
            {
                u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }

            // update residual capacities of the edges and reverse edges
            // along the path
            for (v = sink; v != source; v = parent[v])
            {
                u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }

            // Add path flow to overall flow
            max_flow += path_flow;
        }

        // Return the overall flow
        return max_flow;
    }

private:
    vector<list<Edge>> adjacencyList;
    Edge* intraEdges;
    int numberOfVertices;
    int source, sink, markets, houses;
};

void processInput()
{
    int M, N, S, C;
    int x, y;
    if (scanf("%d %d", &M, &N) == 0)
        return;
    if (scanf("%d %d", &S, &C) == 0)
        return;

    Graph graph((M * N)*2 + 2);

    for (int i = 1; i < M * N + 1; i++)
    {
        graph.addIntraEdge(i);
        //right
        if (i % M != 0){
            graph.addEdge(i, i + 1);
            graph.addEdge(i + 1, i);
        }

        //under
        if (i < M * (N - 1)){
            graph.addEdge(i, i + M);
            graph.addEdge(i + M, i);
        }
    }
    for (int i = 0; i < S; i++)
    {
        if (scanf("%d %d", &x, &y) == 0) return;
        graph.clearEdges(M * (y - 1) + x);
       
        graph.addEdge(M * (y - 1) + x, M * N + 1); //supermercados apontam para o target
    }
    for (int i = 0; i < C; i++)
    {
        if (scanf("%d %d", &x, &y) == 0) return;
        graph.addEdge(0, M * (y - 1) + x); //source aponta para as casas 
    }

    graph.setHouses(C);
    graph.setMarkets(S);
    graph.setSource(0);
    graph.setSink(M * N + 1);
    cout << graph.maxMatches() << endl;
}

int main() {
    processInput();
    return 0;
}