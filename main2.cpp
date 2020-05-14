#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#define CAPACITY 1
#define in(a) (a*2-1)
#define out(a) (a*2)

using namespace std;

struct Edge
{
    int u;      // Origin
    int v;      // Destination
    int cap;
    int flux;   // Current flux
    Edge* inverse;
};

class Graph {
public:
    Graph(int V)
    {
        numberOfVertices = V;
        intraEdges = (Edge*)malloc(sizeof(Edge)*numberOfVertices*2);
        adjacencyList.resize(numberOfVertices*2);
        parent = (Edge**)malloc(sizeof(Edge*)*numberOfVertices*2); // This array is filled by BFS and to store path
        for(int i=0; i< numberOfVertices*2; i++) {
            parent[i] = NULL;
            adjacencyList[i].clear();
        }
    }
    void addIntraEdge(int u)
    {   
        Edge *edge1 = (Edge*)malloc(sizeof(Edge));
        Edge *edge2 = (Edge*)malloc(sizeof(Edge));
        
        *edge1 = {in(u),out(u), CAPACITY, 0, NULL};
        *edge2 = {out(u),in(u), CAPACITY, 1, edge1};
        edge1->inverse = edge2;

        adjacencyList[in(u)].push_back(*edge1);
        adjacencyList[out(u)].push_back(*edge2);
    }
    void addEdge(int u, int v)
    {                
        adjacencyList[out(u)].push_back({out(u),in(v), CAPACITY, 0, NULL});
    }
    void addEdgeInv(int u, int v)
    {            

        Edge *edge1 = (Edge*)malloc(sizeof(Edge));    
        Edge *edge2 = (Edge*)malloc(sizeof(Edge));

        *edge1 = {out(u),in(v), CAPACITY, 0, NULL};
        *edge2 = {out(v),in(u), CAPACITY, 1, edge1};
        edge1->inverse = edge2;

        adjacencyList[out(u)].push_back(*edge1);
        adjacencyList[out(v)].push_back(*edge2);        
    }
    bool isMarket(int u){
        for(auto &edge : adjacencyList[out(u)])
            if(edge.v == sink)
                return true;

        return false;
    }

    void clearEdges(int u)
    {        
        adjacencyList[out(u)].clear();
    }
    void setSource(int s)
    {
        source = s;
    }
    void setSink(int s)
    {
        sink = in(s);
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
        cout << "new: " << endl;
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            for (auto &edge : adjacencyList[current]) {
                cout << edge.u << " -> " << edge.v << " Cap: " << rCap(&edge) << endl;
                if ((visited[edge.v] == false) && (rCap(&edge) > 0)) {
                    cout << edge.u << " -> " << edge.v << endl;
                    q.push(edge.v);
                    parent[edge.v] = &edge;
                    visited[edge.v] = true;
                }
            }
        }

        //cout << parent[234234];


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

                //if(v != sink && parentEdge->u != source) //?
                    //min(path_flow, rCap(parentEdge->inverse)); //?

                //cout <<"Path Flow: " << path_flow << " Parent: " << rCap(parentEdge) << " V: " << v << endl;
            }

            // update residual capacities of the edges and reverse edges
            // along the path
            for (v = sink; v != source; v = parent[v]->u)
            {
                parentEdge = parent[v];
                parentEdge->flux += path_flow;

                if(parentEdge->inverse != NULL)
                    parentEdge->inverse->flux -= path_flow;
                
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
    
    graph.setSource(0);
    graph.setSink((M * N) + 1);    

    for (int i = 0; i < S; i++)
    {
        if (scanf("%d %d", &x, &y) == 0) return; 
        graph.addEdge(M * (y - 1) + x, (M * N) + 1); //supermercados apontam para a sink
    }
    for (int i = 0; i < C; i++)
    {
        if (scanf("%d %d", &x, &y) == 0) return;
        graph.addEdge(0, M * (y - 1) + x); //source aponta para as casas 

    }

    for (int i = 1; i < M * N + 1; i++)
    {
        //right
        if (graph.isMarket(i)){
            cout << i << " is a market!" << endl;
            continue;
        } 

        if (i % M != 0){
            graph.addEdgeInv(i, i + 1);
        }

        //under
        if (i < M * (N - 1)){
            graph.addEdgeInv(i, i + M);
        }
    }

    for(int i = 1; i < M * N + 1; i++) graph.addIntraEdge(i);

    
    cout << graph.fordFulkerson() << endl;
}

int main() {
    
    processInput();
    return 0;
}