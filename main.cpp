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

int max_val = 0;


class Graph{
    int v;
    list<int> *adjList; /*list of adjacent vertexs*/
    int *vertList; /*list of vertex values*/
    int *maxVisit; /*max number of time a vertex can be visited*/

    void dfs();
    int nextVisit(int vertex, int *visited);
    void dfsSearch(int vertex, int *visited);

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
    maxVisit = new int[v];

    for(int i = 0; i<v; i++) maxVisit[i] = 1;
}

void Graph::addVertex(int val, int i){
    vertList[i] = val;
}

void Graph::addConnection(int x, int y){
    adjList[x].push_back(y); 
    maxVisit[y] += 1;
}

void Graph::printGraph(){
    dfs();
    for(int i = 0; i<v; i++)
        cout << vertList[i] <<"\n";
}

void Graph::dfs() {
    int *visited = new int[v]; 
    for (int i = 0; i < v; i++){
        visited[i] = 0; 
        if(adjList[i].empty())
            maxVisit[i] -= 1;
    } 

    for (int i = 0; i < v; i++){
        max_val = 0;
        if ((visited[i] < maxVisit[i]) && (!adjList[i].empty()))
            dfsSearch(i, visited);
    }

}   

int Graph::nextVisit(int vertex, int *visited){
    int vert = -1;
    list<int>::iterator i;
    
    for(i = adjList[vertex].begin(); i != adjList[vertex].end(); i++){
        if(visited[*i] < maxVisit[*i]){ //first avaliable vertex
            vert = *i; 
            break;
        }
    }
    
    for(;i != adjList[vertex].end();i++)
        if((visited[*i] < visited[vert]) && (visited[*i] < maxVisit[*i])) //get the vertex with least visits
            vert = *i;

    adjList[vertex].remove(vert); //no longer needs to be visited

    return vert;
}

void Graph::dfsSearch(int vertex, int *visited) {
    if (visited[vertex] != maxVisit[vertex])
        visited[vertex] += 1;

    //cout << vertex + 1 << " ";

    int vert;

    while((vert = nextVisit(vertex, visited)) != -1){

        dfsSearch(vert, visited);
        //cout << vertex + 1 << " ";
        vertList[vertex] = vertList[vertex] > max_val ? vertList[vertex] : max_val;
        max_val = 0;
    }
    
    //cout << "\n";
    max_val = vertList[vertex] > max_val ? vertList[vertex] : max_val;
    vertList[vertex] = max_val;
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
    graph.printGraph();
    
}

int main(){
    processInput();
    return 0;
}