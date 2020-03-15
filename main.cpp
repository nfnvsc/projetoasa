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

    void dfs();
    void dfsSearch(int vertex, vector<bool> &visited);

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
    dfs();
    cout << "Number vertices: " << v << "\n";
    for(int i = 0; i<v; i++)
        cout << vertList[i] <<"\n";
}

void Graph::dfs() {
    vector<bool> visited(v, false);
    for (int i = 0; i < v; i++)
        if (!visited[i])
            dfsSearch(i, visited);
}

void Graph::dfsSearch(int vertex, vector<bool> &visited) {
    stack<int> stack;
    stack.push(vertex);
    // while(!stack.empty()) { ->  segfault com isto
        vertex = stack.top();
        stack.pop();
        if (!visited[vertex]) {
            visited[vertex] = true;
        }
        for (auto i = adjList[vertex].begin(); i != adjList[vertex].end(); i++) {
            if(!visited[*i])
            stack.push(*i);
        }
    //}
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
    processInput("T01_clique.in");

    return 0;
}