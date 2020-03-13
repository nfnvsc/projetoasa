#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#define NIL -1
using namespace std;

typedef struct vertice {
    int val;
    int num_connected;
    int *connected;
} vertice;

vertice** vertice_array;
int graphSize;

vertice* get_vertice(int index){
    return vertice_array[index-1];
}

int min(int a, int b) {
    return a < b ? a : b;
}

void new_vertice(int value, int size, int index){
    vertice* new_vert;

    new_vert = (vertice*)malloc(sizeof(vertice));
    new_vert->val = value;
    new_vert->num_connected = 0;
    new_vert->connected = (int*)malloc(sizeof(int) * size);

    vertice_array[index] = new_vert;

}

void add_connection(int index, int new_connection){
    vertice* aux_vert = get_vertice(index);
    aux_vert->connected[aux_vert->num_connected++] = new_connection;
}

void processInput(string file_name){
    string line;
    ifstream myfile(file_name);

    int first, second;
    int i, aux1, aux2;

    if (myfile.is_open()){
        getline(myfile,line);
        sscanf(line.c_str(), "%d,%d", &first, &second);
        
        vertice_array = (vertice **)malloc(sizeof(vertice*) * first);
        graphSize = first;

        for(i = 0; i < first; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d", &aux1);

            new_vertice(aux1, first, i);
        }

        for(i = 0; i < second; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d %d", &aux1, &aux2);

            add_connection(aux1, aux2);
        }
      
        myfile.close();
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
    for (int i = 0; i < num_nodes; i++) {
        if (scc[i]->val > maxValue)
        {
            maxValue = scc[i]->val;
        }
    }
    for (int i = 0; i < num_nodes; i++) {
        scc[i]->val = maxValue;
    }
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
    vertice **scc;
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
}

int main(){
    processInput("T01_clique.in");
    tarjan(vertice_array, graphSize);
    cout << "algorithm completed" << "\n";
    return 0;
}