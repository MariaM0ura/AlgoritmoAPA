#include "headers/source.h"
#include <vector>
#include <chrono>
#include <iostream>

int main() {
    // Início da contagem do tempo de execução
    auto start = std::chrono::high_resolution_clock::now();

    int n = 5; 
    std::vector<int> t = {15, 25, 20, 30, 20};   // Tempos de produção
    std::vector<int> p = {25, 45, 75, 120, 135}; // Prazos
    std::vector<int> m = {10, 12, 30, 15, 10};   // Multas por minuto

    std::vector<std::vector<int>> matriz = {
        {0, 10, 15, 8, 21},
        {10, 0, 10, 13, 9},
        {17, 9, 0, 10, 14},
        {11, 13, 12, 0, 10},
        {5, 10, 15, 20, 0}
    };

    // Criação da instância da classe Fruta
    Fruta fruta(n, t, p, m, matriz);
    fruta.producion();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Tempo de execução: " << diff.count() << " s" << std::endl;

    return 0;
}
