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
    Graph(int V)
    {
        numberOfVertices = V;
        intraEdges = (Edge*)malloc(sizeof(Edge)*numberOfVertices);
        adjacencyList.resize(V);
        parent = (Edge**)malloc(sizeof(Edge*)*numberOfVertices); // This array is filled by BFS and to store path
        for(int i=0; i< numberOfVertices; i++) parent[i] = NULL;
    }
    void addIntraEdge(int u)
    {   
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
    void setSource(int s)
    {
        source = s;
    }
    void setSink(int s)
    {
        sink = s;
    }

    int rCap(Edge *edge){
        return edge->cap - edge->flux;
    }

    bool bfs()
    {
        // Create a visited array and mark all vertices as not visited
        bool visited[numberOfVertices];
        memset(visited, 0, sizeof(visited));

        // Create a queue, enqueue source vertex and mark source vertex
        // as visited
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = NULL;

        // Standard BFS Loop
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            for (auto &edge : adjacencyList[current]) {          
                if ((visited[edge.v] == false) && (rCap(&edge) > 0)) {
                    q.push(edge.v);
                    parent[edge.v] = &edge;                    
                    visited[edge.v] = true;
                }
            }
        }


        // If we reached sink in BFS starting from source, then return
        // true, else false
        return (visited[sink] == true);
    }
    int fordFulkerson() {
        int v;
        Edge* parentEdge;

        // Create a residual graph and fill the residual graph with
        // given capacities in the original graph as residual capacities
        // in residual graph

        int max_flow = 0; // There is no flow initially

        // Augment the flow while tere is path from source to sink
        while (bfs())
        {
            // Find minimum residual capacity of the edges along the
            // path filled by BFS. Or we can say find the maximum flow
            // through the path found.

            int path_flow = 1;
            for (v = sink; v != source; v = parent[v]->u)
            {
                parentEdge = parent[v];
                path_flow = min(path_flow, rCap(parentEdge));
                if(v != sink)
                    path_flow = min(path_flow, rCap(&intraEdges[v]));
                cout <<"Path Flow: " << path_flow << " Parent: " << rCap(parentEdge) << " Intra: " << rCap(&intraEdges[v]) << " V: " << v << endl;
            }

            // update residual capacities of the edges and reverse edges
            // along the path
            for (v = sink; v != source; v = parent[v]->u)
            {
                parentEdge = parent[v];
                parentEdge->flux += path_flow;
                if (v!= sink)
                    intraEdges[v].flux += path_flow;

                for (auto invEdge : adjacencyList[v]) 
                    if (invEdge.v == parentEdge->u){
                        invEdge.flux -= path_flow;
                        break;
                    }
            }

            // Add path flow to overall flow
            max_flow += path_flow;
            //break;
        }

        // Return the overall flow
        return max_flow;
    }

private:
    vector<list<Edge>> adjacencyList;
    Edge* intraEdges;
    Edge** parent;
    int numberOfVertices;
    int source, sink;
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
    graph.setSource(0);
    graph.setSink(M * N + 1);
    //graph.addIntraEdge(M*N+1, )
    cout << graph.fordFulkerson() << endl;
}

int main() {
    
    processInput();
    return 0;
}