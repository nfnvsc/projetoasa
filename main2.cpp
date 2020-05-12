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
    void setSource(int s)
    {
        source = s;
    }
    void setSink(int s)
    {
        sink = s;
    }

    int maximumFlow()
    { // Edmonds–Karp

        int maximumFlow = 0;   

        vector<Edge *> parentEdges(numberOfVertices, nullptr);        
        deque<int> bfsQueue;

        // Do a BFS to find every path from source to sink
        bfsQueue.push_back(source);
        while (bfsQueue.empty() == false)
        {

            int current = bfsQueue.front();
            bfsQueue.pop_front();
            //parentEdges[current] = 0;
            cout << "current: " << current << endl;
            for (auto &edge : adjacencyList[current])
            {
                if ((edge.v != sink) && (parentEdges[edge.v] != NULL)) continue; //prevent it from going backwards

                printf("Parent of %d is %d\n", edge.v, edge.u);
                parentEdges[edge.v] = &edge;
                bfsQueue.push_back(edge.v);

                if (edge.v == sink)
                {   
                    
                    printf("encontrou saida : %d\n", edge.v);

                    // A path was found from source to sink
                    // Find the maximum flow on this path
                    int maxFlow = numeric_limits<int>::max();
                    auto parentEdge = parentEdges[edge.v];
                    while (parentEdge != nullptr)
                    {
                        maxFlow = min(maxFlow, parentEdge->cap - parentEdge->flux);
                        //maxFlow = min(maxFlow, intraEdges[edge.u].cap - intraEdges[edge.u].flux);
                        parentEdge = parentEdges[parentEdge->u];
                        //printf("\n%d", parentEdge->u);
                    }

                    maximumFlow += maxFlow;

                    // Augment the entire path
                    parentEdge = parentEdges[edge.v];
                    while (parentEdge != nullptr)
                    {
                        //intraEdges[edge.u].flux += maxFlow;
                        parentEdge->flux += maxFlow;
                        parentEdge = parentEdges[parentEdge->u];
                    }
                }
            }
        }
        return maximumFlow;
    }

private:
    vector<list<Edge>> adjacencyList;
    Edge* intraEdges;
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
    cout << graph.maximumFlow() << endl;
}

int main() {
    processInput();
    return 0;
}