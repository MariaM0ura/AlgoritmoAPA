#include <iostream>
#include <fstream>
#include <vector>

int main() {
    /****
      Leitor de intancia 
      vai ler o arquivo .txt e armazenar os dados em vetores    
    ***/
    std::ifstream file("src/VND/instancia/instancia.txt");

    if(!file){
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        return 1;
    }

    int num_de_pedidos;
    file >> num_de_pedidos;

    std::vector<int> t(num_de_pedidos), p(num_de_pedidos), w(num_de_pedidos);


    // Lendo os arrays t, p, w
    for (int i = 0; i < num_de_pedidos; i++) file >> t[i];
    for (int i = 0; i < num_de_pedidos; i++) file >> p[i];
    for (int i = 0; i < num_de_pedidos; i++) file >> w[i];

    // Matriz de preparação de linha
    std::vector<std::vector<int>> s(num_de_pedidos, std::vector<int>(num_de_pedidos));
    for (int i = 0; i < num_de_pedidos; i++) {
        for (int j = 0; j < num_de_pedidos; j++) {
            file >> s[i][j];
        }
    }

    // Exemplo de como exibir os dados lidos
    std::cout << "numero de pedidos: " << num_de_pedidos << std::endl;

    std::cout << "Tempos de fabricação: ";
    for (int i = 0; i < num_de_pedidos; i++) std::cout << t[i] << " ";
    std::cout << std::endl;

    std::cout << "Prazos de fabricação: ";
    for (int i = 0; i < num_de_pedidos; i++) std::cout << p[i] << " ";
    std::cout << std::endl;

    std::cout << "Multas por atraso: ";
    for (int i = 0; i < num_de_pedidos; i++) std::cout << w[i] << " ";
    std::cout << std::endl;

    std::cout << "Matriz de limpeza: " << std::endl;
    for (int i = 0; i < num_de_pedidos; i++) {
        for (int j = 0; j < num_de_pedidos; j++) {
            std::cout << s[i][j] << " ";
        }
        std::cout << std::endl;
    }

    file.close();
    return 0;
}