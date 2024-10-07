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


    std::vector<double> solucoes_vnd(1);
    std::vector<double> tempos_vnd(1);

    Fruta fruta_vnd(n, t, p, m, matriz);

    std::vector<VND> resultadosVND(1);
    std::vector<VND> resultadoFinalVND(1);

    auto start_vnd = std::chrono::high_resolution_clock::now();

    std::vector<Pedido> pedidos(n);
    for (int j = 0; j < n; ++j) {
            pedidos[j] = {j, t[j], p[j], m[j]};
    }

    fruta_vnd.guloso();

    double custo_vnd = fruta_vnd.producion();
    solucoes_vnd[0] = custo_vnd;

    auto end_vnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff_vnd = end_vnd - start_vnd;
    tempos_vnd[0] = diff_vnd.count();

    double melhor_solucao_vnd = solucoes_vnd[0];
    double tempo_vnd = tempos_vnd[0];
    double gap;

    if (valorOtimo == 0) {
        gap = (melhor_solucao_vnd == 0) ? 0 : 100;  
    } else {
        gap = (melhor_solucao_vnd - valorOtimo) / valorOtimo * 100;
    }

    std::cout << "VND:\n";
    std::cout << "  Melhor solução: " << melhor_solucao_vnd << "\n";
    std::cout << "  Tempo: " << tempo_vnd << "\n";
    std::cout << "  Gap: " << gap << "%\n\n";

    return 0;
}
