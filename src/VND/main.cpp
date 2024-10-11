#include "headers/vizinhos.h"
#include "leitor.cpp" 
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string.h>


int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " <caminho_arquivo> <nome_instancia> <valor_otimo>\n";
        return 1;
    }

    std::string caminho_arquivo = argv[1];
    std::string nomeInstancia = argv[2]; 
    double valorOtimo = std::stod(argv[3]);  

    int n;
    std::vector<int> t, p, m;
    std::vector<std::vector<int>> matriz;

    try {
        std::tie(n, t, p, m, matriz) = ler_instancia(caminho_arquivo);
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    Fruta fruta_vnd(n, t, p, m, matriz);

    auto start_vnd = std::chrono::high_resolution_clock::now();

    std::vector<Pedido> pedidos(n);
    for (int j = 0; j < n; ++j) {
            pedidos[j] = {j, t[j], p[j], m[j]};
    }

    fruta_vnd.guloso();

    double melhorSolucaoVND, tempoVND, gapVND;
    std::tie(melhorSolucaoVND, tempoVND, gapVND) = fruta_vnd.producion(valorOtimo);


    std::cout << "VND:\n";
    std::cout << "  Melhor solução: " << melhorSolucaoVND << "\n";
    std::cout << "  Tempo: " << tempoVND << "\n";
    std::cout << "  Gap: " << gapVND << "%\n\n";

    return 0;
}
