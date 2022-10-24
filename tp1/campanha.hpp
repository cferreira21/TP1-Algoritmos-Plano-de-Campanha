#ifndef CAMPANHA
#define CAMPANHA
#include <iostream>
#include <vector>
#include <stack>

int const pMax = 20000; // Quantidade máxima de variáveis incluindo suas negações

struct campanha{

    std::vector<int> adj[pMax]; //Grafo em lista de adjacencia
    std::vector<int> adjInv[pMax];
    bool visitado[pMax];
    bool visitadoInv[pMax];
    std::stack<int> s; //pilha de vértices terminados do kosaraju passo 1 
    int c = 1; //contador
    int componente[pMax]; //componente fortemente conectado de cada vértice


    void addAresta(int x, int y);
    void addArestaInv(int x, int y);

    void dfs1(int v); //dfs do passo 1 de kosaraju
    void dfs2(int v); //dfs do passo 2 de kosaraju

    void kosaraju(int var);

    void isPossivel(int s, int p, int a[], int b[]);

};

#endif