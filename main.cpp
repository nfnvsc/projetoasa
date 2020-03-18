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

    int nextVisit(int vertex, int *visited, bool cond);
    void dfsSearch(int vertex, int *visited, bool cond);

public:
    Graph(int v);
    void dfs();
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
            dfsSearch(i, visited, true);
    }

    for(int i = 0; i < v; i++){
        //cout << "Expected: " << maxVisit[i] << " Got: " << visited[i] << "\n";
        max_val = 0;
        while(maxVisit[i] > visited[i])
            dfsSearch(i, visited, true);
    }
    /*
    for(int i = 0; i < v; i++){
        cout << "Expected: " << maxVisit[i] << " Got: " << visited[i] << "\n";
    }
    */
}   

int Graph::nextVisit(int vertex, int *visited, bool cond){
    int vert = -1;
    //static int auxVert = -1;

    list<int>::iterator i;
    
    if(!cond){
        for(i = adjList[vertex].begin(); i != adjList[vertex].end(); i++)
            if(visited[*i] == 0){ //only select undiscovered vertexs
                vert = *i; 
                break;
            }
    }

    else{
        for(i = adjList[vertex].begin(); i != adjList[vertex].end(); i++){
            if(visited[*i] < maxVisit[*i]){ //first avaliable vertex
                vert = *i; 
                break;
                }
            }
    }

    adjList[vertex].remove(vert); //no longer needs to be visited

    return vert;
}

void Graph::dfsSearch(int vertex, int *visited, bool cond) {
    if (visited[vertex] != maxVisit[vertex])
        visited[vertex] += 1;

    //cout << vertex + 1 << " ";

    int vert;

    while((vert = nextVisit(vertex, visited, cond)) != -1){

        dfsSearch(vert, visited, false);
        //cout << vertex + 1 << " ";
        vertList[vertex] = vertList[vertex] > max_val ? vertList[vertex] : max_val;
        //cout << "\1Vertex: " << vertex + 1 << " has now -> " << vertList[vertex];
        max_val = 0;
    }
    
    max_val = vertList[vertex] > max_val ? vertList[vertex] : max_val;
    vertList[vertex] = max_val;
    //cout << "\n Vertex: " << vertex + 1 << " has now -> " << vertList[vertex];
    //cout << "\nMAX_VAL: " << max_val << "\n";

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