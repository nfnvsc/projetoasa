#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iostream>
#include <bits/stdc++.h>
#define NIL -1

using namespace std;

class Graph{
    int v;
    list<int> *adjList;
    list<int> vertList;

    public:
        Graph(int v);
        void addVertex(int val);
        void addConnection(int x, int y);
        void printGraph();
};

Graph::Graph(int v){
    this->v = v;
    adjList = new list<int>[v];
}

void Graph::addVertex(int val){
    vertList.push_back(val);
}

void Graph::addConnection(int x, int y){
    adjList[x].push_back(y); 
}

void Graph::printGraph(){
    cout << v << "\n";
    for(int i = 0; i<v; i++)
        for (list<int>::iterator it = adjList[i].begin(); it != adjList[i].end(); it++)
            cout << i + 1 << " + " << *it << "\n";
}

typedef struct vertice {
    int val;
    int num_connected;
    int *connected;
} vertice;

int graphSize;

int min(int a, int b) {
    return a < b ? a : b;
}

void processInput(string file_name){
    string line;
    ifstream myfile(file_name);
    int *vertexValues;
    int second;
    int i, aux1, aux2;

    if (myfile.is_open()){
        getline(myfile,line);
        sscanf(line.c_str(), "%d,%d", &graphSize, &second);
        
        vertexValues = new int[graphSize];
        Graph graph(graphSize);

        for(i = 0; i < graphSize; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d", &aux1);

            graph.addVertex(aux1);
        }

        for(i = 0; i < second; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d %d", &aux1, &aux2);

            graph.addConnection(aux1-1, aux2);
        }
      
        myfile.close();
        cout << "Printing\n";
        graph.printGraph();

    }

    else cout << "Unable to open file"; 
}

void printGraph(vertice **graph, int graphSize) {
    for (int i = 0; i < graphSize; i++)
    {
        cout << graph[i]->val << "\n";
    }
}

void giveValues(vertice **scc, int num_nodes)
{
    int maxValue = 0;
    for (int i = 0; i < num_nodes; i++) 
        if (scc[i]->val > maxValue)
            maxValue = scc[i]->val;

    for (int i = 0; i < num_nodes; i++)
        scc[i]->val = maxValue;
}

void tarjanSCC(int vertex, int disc[], int low[], stack<int> &stack, bool inStack[], vertice **graph) {
    static int dtime = 0;

    disc[vertex] = low[vertex] = ++dtime;
    stack.push(vertex);
    inStack[vertex] = true;

    for (int i = 0; i < graph[vertex]->num_connected; i++) {
        int ver = graph[vertex]->connected[i];
        if (disc[ver] == NIL) {
            tarjanSCC(ver, disc, low, stack, inStack, graph);
            low[vertex] = min(low[vertex], low[ver]);
        }
        else if (inStack[ver] == true)
            low[vertex] = min(low[vertex], disc[ver]);
    }

    //Pop the found SCC and give highest value to the components
    int w = 0;
    int index = 0;
    vertice **scc = (vertice**)malloc(sizeof(vertice*) * graphSize);

    if (low[vertex] == disc[vertex]) {
        while (stack.top() != vertex) {
            w = (int)stack.top();
            scc[index++] = get_vertice(w);
            inStack[w] = false;
            stack.pop();
        }
        w = (int)stack.top();
        scc[index++] = get_vertice(w);
        inStack[w] = false;
        stack.pop();
    }
    giveValues(scc, index);
    free(scc);
}

void tarjan(vertice **graph, int u) { // u = number of nodes
    int *d = new int[u];
    int *low = new int[u];
    bool *inStack = new bool[u];
    stack<int> s;

    for (int i = 0; i < u; i++) {
        d[i] = low[i] = NIL;
        inStack[i] = false;
    }
    for (int i = 0; i < u; i++) {
        if (d[i] == NIL)
            tarjanSCC(i, d, low, s, inStack, graph);
    }

    printGraph(graph, graphSize);
}

int main(){
    processInput("T01_clique.in");
    //tarjan(vertice_array, graphSize);
    cout << "algorithm completed" << "\n";
    return 0;
}