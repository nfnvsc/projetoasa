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
    int *vertList;
    int *maxVisit;

    void dfs();
    int aux(int vertex, int *visited);
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

    //if (!adjList[y].empty())
    maxVisit[y] += 1;

    

}

void Graph::printGraph(){
    dfs();
    for(int i = 0; i<v; i++)
        cout << vertList[i] <<"\n";
}

void Graph::dfs() {
    max_val = 0; //nao devia ser global
    int *visited = new int[v]; 
    for (int i = 0; i < v; i++){
        visited[i] = 0; 

        if(adjList[i].empty())
            maxVisit[i] = 1;
    } 
    
    //cout << "vert 4: " << maxVisit[3] << "\n";

    for (int i = 0; i < v; i++)
        if (visited[i] != maxVisit[i])
            dfsSearch(i, visited);
}

int Graph::aux(int vertex, int *visited){

    auto i = adjList[vertex].begin();
    int vert = *i;

    while(i != adjList[vertex].end()){
        if((visited[*i] < visited[vert]) && (visited[*i] < maxVisit[*i]))
            vert = *i;
        i++;
    }


    if (visited[vert] == maxVisit[vert]) return -1;

    return vert;
}

void Graph::dfsSearch(int vertex, int *visited) {
    if (visited[vertex] != maxVisit[vertex])
        visited[vertex] += 1;

    //cout << vertex + 1 << " ";

    int vert;

    while((vert = aux(vertex, visited)) != -1){

        dfsSearch(vert, visited);
        //cout << vertex + 1 << " ";
        vertList[vertex] = vertList[vertex] > max_val ? vertList[vertex] : max_val;
        max_val = 0;
    }
    
    //cout << "\n";
    max_val = vertList[vertex] > max_val ? vertList[vertex] : max_val;
    vertList[vertex] = max_val;
}

void processInputFile(string file_name){
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

            graph.addConnection(aux1 - 1, aux2 - 1);
        }
        graph.printGraph();
        myfile.close();
    }

    else cout << "Unable to open file"; 
}


void processInput(){
    int first, second;
    int aux1, aux2;
    while(1){

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
    
}


int main(){

    //processInput();

    processInputFile("T01_clique.in");
    cout << "XXXXXXXX\n";
    processInputFile("T02_tree_with_prop.in");
    cout << "XXXXXXXX\n";
    processInputFile("T03_tree_no_prop.in");
    cout << "XXXXXXXX\n";
    processInputFile("T04_small_no_prop.in");
    cout << "XXXXXXXX\n";
    processInputFile("T05_disconnected.in");


    return 0;
}