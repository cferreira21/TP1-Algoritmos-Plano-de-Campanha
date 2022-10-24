#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "campanha.hpp"

int main(int argc, char* argv[]) {
  
  std::string filename(argv[1]);
  
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
      std::cerr << "Nao foi possivel abrir o arquivo - '"
          << filename << "'" << std::endl;
      return 1;
  }

  int s, p;
  input_file >> s >> p;
  do{
  
  int a[2*s]; // lado esquerdo das proposições // 2 proposições por linha = 2*s
  int b[2*s]; // lado direito das proposições
  for(int i=0; i<2*s; i++){
    input_file >> a[i];
    input_file >> b[i];
  }
  
  for(int i=1;i<2*s;i++){ // segunda proposição de cada linha é negada
    if(i%2 == 0) continue;
    a[i] = a[i]*(-1);
    b[i] = b[i]*(-1);
  }

  campanha *c = new campanha;
  c->isPossivel(p, 2*s, a, b);
  delete c;
  input_file >> s >> p;
  }while(s!=0 && p!=0);
  
  return(0);
}
