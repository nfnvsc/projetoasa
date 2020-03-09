#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct vertice{
    int val;
    vertice** connected;
} vertice;

vertice** vertice_array;

void processInput(string file_name){
    string line;
    ifstream myfile(file_name);
    vertice new_vert;

    int first, second;
    int i, aux1, aux2;

    if (myfile.is_open()){
        getline(myfile,line);
        sscanf(line.c_str(), "%d,%d", &first, &second);
        
        vertice_array = (vertice **)malloc(sizeof(vertice) * stoi(line));

        for(i = 0; i < first; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d", &aux1);

            new_vert = malloc(sizeof(vertice));
        }

        for(i = 0; i < second; i++){
            getline(myfile, line);
            sscanf(line.c_str(), "%d %d", &aux1, &aux2);
        }

        printf("%d, %d", first, second);

        myfile.close();
    }

    else cout << "Unable to open file"; 
}

int main(){
    processInput("teste.txt");
    return 0;
}