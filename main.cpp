#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iostream>
#include <bits/stdc++.h>
#define min(a,b) (a < b ? a : b);
#define max(a,b) (a > b ? a : b);
#define NIL -1

using namespace std;

class Graph{
    int v;
    list<int> *adjList; /*list of adjacent vertexs*/
    int *vertList;

    void tarjan();
    void tarjanSCC(int vertex, int disc[], int low[], stack<int> &stack, bool inStack[], bool reset);

    public:
        Graph(int v);
        void addVertex(int val, int i);
        void addConnection(int x, int y);
        void printGraph();
};

Graph::Graph(int v){
    this->v = v;
    adjList = new list<int>[v];
    vertList = new int[v];
}

void Graph::addVertex(int val, int i){
    vertList[i] = val;
}

void Graph::addConnection(int x, int y){
    adjList[x].push_back(y); 
}

void Graph::printGraph(){
    tarjan();
    cout << "Number vertices: " << v << "\n";
    for(int i = 0; i<v; i++)
        cout << vertList[i] <<"\n";
}

void Graph::tarjan() { // u = number of nodes
    int *d = new int[v];
    int *low = new int[v];
    bool *inStack = new bool[v];
    stack<int> s;

    for (int i = 0; i < v; i++) {
        d[i] = low[i] = NIL;
        inStack[i] = false;
    }

    for (int i = 0; i < v; i++) {
        if (d[i] == NIL)
            tarjanSCC(i, d, low, s, inStack, true);
    }

}

void Graph::tarjanSCC(int vertex, int disc[], int low[], stack<int> &stack, bool inStack[], bool reset) {
    static int dtime = 0;
    static int max_val;

    disc[vertex] = low[vertex] = ++dtime;

    max_val = reset ? 0 : max(max_val, vertList[vertex]);

    stack.push(vertex);
    inStack[vertex] = true;

    for (list<int>::iterator it = adjList[vertex].begin(); it != adjList[vertex].end(); it++) {
        int ver = *it;
        if (disc[ver] == NIL) {
            tarjanSCC(ver, disc, low, stack, inStack, false);
            low[vertex] = min(low[vertex], low[ver]);
        }
        else if (inStack[ver] == true)
            low[vertex] = min(low[vertex], disc[ver]);
    }

    //Pop the found SCC and give highest value to the components
    int w = 0;
    if (low[vertex] == disc[vertex]) {
        while (stack.top() != vertex) {
            w = (int)stack.top();
            vertList[w] = max_val; //ta certo?
            inStack[w] = false;
            stack.pop();
        }
        w = (int)stack.top();
        vertList[w] = max_val; //ta certo?
        inStack[w] = false;
        stack.pop();
    }

}

/*
void giveValues(vertice **scc, int num_nodes)
{
    int maxValue = 0;
    for (int i = 0; i < num_nodes; i++) 
        if (scc[i]->val > maxValue)
            maxValue = scc[i]->val;

    for (int i = 0; i < num_nodes; i++)
        scc[i]->val = maxValue;
}
*/

void processInput(string file_name){
    string line;
    ifstream myfile(file_name);
    int first, second;
    int aux1, aux2;

    if (myfile.is_open()){
        getline(myfile,line);
        sscanf(line.c_str(), "%d,%d", &first, &second);

        Graph graph(first);

        for(int i = 0; i < first; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d", &aux1);

            graph.addVertex(aux1, i);
        }

        for(int i = 0; i < second; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d %d", &aux1, &aux2);

            graph.addConnection(aux1-1, aux2);
        }
        graph.printGraph();
      
        myfile.close();
    }

    else cout << "Unable to open file"; 
}


int main(){
    processInput("T02_tree_with_prop.in");
    
    return 0;
}