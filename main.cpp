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

int max_val = -1;

class Graph{
    int v;
    list<int> *adjList; /*list of adjacent vertexs*/
    int *vertList; /*list of vertex values*/
    bool *testList; /*max number of time a vertex can be visited*/

    int nextVisit(int vertex);
    void dfsSearch(int vertex);

public:
    Graph(int v);
    void addVertex(int val, int i);
    void addConnection(int x, int y);
    void dfs();
    void printGraph();
};

Graph::Graph(int v){
    this->v = v;
    adjList = new list<int>[v];
    vertList = new int[v];
    testList = new bool[v];

    for(int i = 0; i<v; i++) testList[i] = false;
}

void Graph::addVertex(int val, int i){
    vertList[i] = val;
}

void Graph::addConnection(int x, int y){
    adjList[x].push_back(y); 
}

void Graph::printGraph(){
    for(int i = 0; i<v; i++)
        cout << vertList[i] <<"\n";
}

void Graph::dfs() {
    for (int i = 0; i < v; i++){
        max_val = -1;
        dfsSearch(i);
    }
}   

int Graph::nextVisit(int vertex){
    int vert = -1;

    list<int>::iterator i;
    
    for(i = adjList[vertex].begin(); i != adjList[vertex].end(); i++){
        if(!testList[*i]){ //first avaliable vertex
            vert = *i; 
            break;
        }
    }
    adjList[vertex].remove(vert); //no longer needs to be visited

    return vert;
}

void Graph::dfsSearch(int vertex) {
    testList[vertex] = true;
    //cout << vertex + 1 << " ";

    int vert;
    while((vert = nextVisit(vertex)) != -1){

        dfsSearch(vert);
        //cout << vertex + 1 << " ";
        vertList[vertex] = vertList[vertex] > max_val ? vertList[vertex] : max_val;
        //cout << "\1Vertex: " << vertex + 1 << " has now -> " << vertList[vertex];
        max_val = -1;
    }
    
    max_val = vertList[vertex] > max_val ? vertList[vertex] : max_val;
    vertList[vertex] = max_val;    //cout << "\n Vertex: " << vertex + 1 << " has now -> " << vertList[vertex];
    //cout << "\nMAX_VAL: " << max_val << "\n";
    testList[vertex] = false;

}

void processInput(){
    int first, second;
    int aux1, aux2;

    if (scanf("%d,%d", &first, &second) == 0) return;

    Graph graph(first);

    for(int i = 0; i < first; i++){

        if(scanf("%d", &aux1) == 0) return;

            graph.addVertex(aux1, i);
    }

    for(int i = 0; i < second; i++){
        if(scanf("%d %d", &aux1, &aux2) == 0) return;

        graph.addConnection(aux1 - 1, aux2 - 1);
    }
    graph.dfs();
    graph.printGraph();
    
}

int main(){
    processInput();
    return 0;
}