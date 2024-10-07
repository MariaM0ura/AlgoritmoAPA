#include "headers/source.h"
#include <vector>
#include <chrono>
#include <iostream>
#include "leitor.cpp"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::string caminho_arquivo = "instancias/instancia.txt";

    double valorOtimo = 360;
    if(valorOtimo == 0){
        valorOtimo = 0.1;
    }

    int n;
    std::vector<int> t, p, m;
    std::vector<std::vector<int>> matriz;

    try {
        std::tie(n, t, p, m, matriz) = ler_instancia(caminho_arquivo);
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    Fruta fruta(n, t, p, m, matriz);
    fruta.guloso();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Tempo de execução: " << diff.count() << " s" << std::endl;

    return 0;
}
