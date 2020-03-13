#include <iostream>
#include <fstream>
#include <string>
#include "tarjan.h"

using namespace std;

typedef struct vertice{
    int val;
    int num_connected;
    vertice** connected;
} vertice;

vertice** vertice_array;
int graphSize;

vertice* get_vertice(int index){
    return vertice_array[index-1];
}

void new_vertice(int value, int size, int index){
    vertice* new_vert;

    new_vert = (vertice*)malloc(sizeof(vertice));
    new_vert->val = value;
    new_vert->num_connected = 0;
    new_vert->connected = (vertice**)malloc(sizeof(vertice*) * size);

    vertice_array[index] = new_vert;

}

void add_connection(int index, vertice* new_connection){
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

            add_connection(aux1, get_vertice(aux2));
        }

        myfile.close();
    }

    else cout << "Unable to open file"; 
}

int main(){
    processInput("teste.txt");
    tarjan(vertice_array, graphSize);
    return 0;
}