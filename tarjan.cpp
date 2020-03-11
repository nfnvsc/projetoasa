#include "tarjan.h"


int min(int a, int b) {
    return a < b ? a : b;
}

void giveValues(vertice** scc, int num_nodes) {
    int maxValue = 0;
    for (int i = 0; i < num_nodes; i++) {
        if (scc[i]->val > maxValue) {
            maxValue = scc[i]->val;
        }
    }
    for (int i = 0; i < num_nodes; i++) {
        scc[i]->val = maxValue;
    }
}

void tarjanSCC(int vertex, int disc[], int low[], stack<int> *stack, bool inStack[], vertice** graph) {
    static int dtime = 0;

    disc[vertex] = low[vertex] = ++dtime;
    stack->push(vertex);
    inStack[vertex] = true;

    for (int i = 0; i < graph[vertex]->num_connected; ++i) {
        vertice* ver = graph[vertex]->connected[i];
        
        if (d[ver] == NULL) {
            tarjanSCC(ver, disc, low, stack, inStack, graph);
            low[vertex] = min(low[vertex], low[ver]);
        }
        else if (inStack[ver] == true)
            low[vertex] = min(low[vertex], disc[ver]);
    }
    //Pop the found SCC and give highest value to the components
    int w = 0;
    int index = 0;
    vertice** scc;
    if (low[vertex] == disc[vertex]) {
        while (stack->top() != ver) {
            w = (int) stack->top();
            scc[index++] = graph[w];
            inStack[w] = false;
            stack->pop();
        }
        w = (int) stack->top();
        scc[index++] = graph[w];
        inStack[w] = false;
        stack->pop();
        giveValues(scc, index);
    }
}

void tarjan(vertice** graph, int u) { // u = number of nodes
    int *d = new int[u];
    int *low = new int[u];
    bool *inStack = new bool[u];
    stack<int> s;
    
    for (int i = 0; i < u; i++) {
        d[i] = NULL;
        low[i] = NULL;
        inStack[i] = false;
    }

    for (int i = 0; i < u; i++) {
        if (d[i] == NULL)
            tarjanSCC(i, d, low, s, inStack, graph);
    }

}