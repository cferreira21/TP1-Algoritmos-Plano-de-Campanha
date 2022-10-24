#include "campanha.hpp"


void campanha::addAresta(int x, int y){
    adj[x].push_back(y);
}

void campanha::addArestaInv(int x, int y){ 
    adjInv[y].push_back(x);
}

void campanha::dfs1(int v){
    if (visitado[v] == 1) return;
    
    visitado[v] = 1;
    for(int i=0; i<adj[v].size(); i++){
        dfs1(adj[v][i]);
    }
    s.push(v);
}

void campanha::dfs2(int v){
    if (visitadoInv[v] == 1) return;

    visitadoInv[v] = 1;
    for(int i=0; i<adjInv[v].size(); i++){
        dfs2(adjInv[v][i]);
    }
    componente[v] = c;
}

void campanha::kosaraju(int var){
    for(int i=1;i<=2*var;i++){ //Passo 1 
        if (visitado[i] == 0) dfs1(i);
    }

    while (!s.empty()){ //Passo 2
        int n = s.top();
        s.pop();
        if (visitadoInv[n] == 0){
            dfs2(n);
            c++;
        }
    }
    
}

void campanha::isPossivel(int numVar, int prop, int a[], int b[]){
    //Indice da variável x1 = 1
    //Indice da variável -x1 = 1 + numVar
    //Exemplo: 2 variáveis:
        //Indice da var x1 = 1
        //Indice da var -x1 = 1 + 2 = 3
        //Indice da var x2 = 2
        //Indice da var -x2 = 2 + 2 = 4

    
    for(int i=0; i<prop; i++){ // construtor do grafo de implicação normal e inverso
        if(a[i] == 0) a[i] = b[i]; // proposição de uma só variável é equivalente a proposição da variável com ela mesma
        if(b[i] == 0) b[i] = a[i];      // (0 + x1) = (x1) = (x1 + x1)

        if(a[i]>0 && b[i]>0){
            addAresta(a[i]+numVar, b[i]);
            addAresta(b[i]+numVar, a[i]);
            addArestaInv(a[i]+numVar, b[i]);
            addArestaInv(b[i]+numVar, a[i]);
        }

        else if(a[i]<0 && b[i]>0){
            addAresta(-a[i], b[i]);
            addAresta(b[i]+numVar, numVar-a[i]);
            addArestaInv(-a[i], b[i]);
            addArestaInv(b[i]+numVar, numVar-a[i]);
        }

        else if(a[i]>0 && b[i]<0){
            addAresta(a[i]+numVar, numVar-b[i]);
            addAresta(-b[i], a[i]);
            addArestaInv(a[i]+numVar, numVar-b[i]);
            addArestaInv(-b[i], a[i]);
        }
        
        else if(a[i]==0 && b[i]==0){ // se as duas variáveis são 0, desconsiderar a proposição
            continue;
        }

        else{
            addAresta(-a[i], numVar-b[i]);
            addAresta(-b[i], numVar-a[i]);
            addArestaInv(-a[i], numVar-b[i]);
            addArestaInv(-b[i], numVar-a[i]);
        }

    }

    kosaraju(numVar);

    for(int i=1;i<=numVar;i++){ 
        if (componente[i] == componente[i+numVar]){
            std::cout << "nao" << std::endl;
            return;
        }
    }

    std::cout << "sim" << std::endl;
    return;
}