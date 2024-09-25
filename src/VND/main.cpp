#include "headers/vizinhos.h"
#include "leitor.cpp" // Incluir o leitor
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string.h>


int main() {
    // Leitura da instância
    std::string caminho_arquivo = "instancias/n60A.txt";
    /*
        Mudar manualmente
    */
    std::string nomeInstancia = "n60A"; 
    double valorOtimo = 453;

    // Chamar a função para ler a instância do arquivo
    int n;
    std::vector<int> t, p, m;
    std::vector<std::vector<int>> matriz;

    try {
        std::tie(n, t, p, m, matriz) = ler_instancia(caminho_arquivo);
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    int n_execucoes = 1;

    std::vector<double> solucoes_construtiva(n_execucoes);
    std::vector<double> tempos_construtiva(n_execucoes);
    std::vector<double> solucoes_vnd(n_execucoes);
    std::vector<double> tempos_vnd(n_execucoes);

    Fruta fruta_construtiva(n, t, p, m, matriz);

    // Algoritmo VND
    std::vector<VND> resultadosVND(n_execucoes);
    std::vector<VND> resultadoFinalVND(n_execucoes);


    Fruta fruta_vnd(n, t, p, m, matriz);
    
    for (int i = 0; i < n_execucoes; ++i) {
        auto start_vnd = std::chrono::high_resolution_clock::now();

        // Inicializar pedidos
        std::vector<Pedido> pedidos(n);
        for (int j = 0; j < n; ++j) {
            pedidos[j] = {j, t[j], p[j], m[j]};
        }

        // Aplicar o algoritmo VND e capturar o custo final
        double custo_vnd = fruta_vnd.producion();
        solucoes_vnd[i] = custo_vnd;

        auto end_vnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_vnd = end_vnd - start_vnd;
        tempos_vnd[i] = diff_vnd.count();

        double media_solucao_vnd = std::accumulate(solucoes_vnd.begin(), solucoes_vnd.end(), 0.0) / n_execucoes;

        double melhor_solucao_vnd = *std::min_element(solucoes_vnd.begin(), solucoes_vnd.end());
        double media_tempo_vnd = std::accumulate(tempos_vnd.begin(), tempos_vnd.end(), 0.0) / n_execucoes;
        double gap = (melhor_solucao_vnd - valorOtimo) / valorOtimo * 100;

        resultadosVND[i] = {melhor_solucao_vnd, media_tempo_vnd, gap};
    }

    for(int i = 0; i < n_execucoes; i++){
        std::cout << "VND: " << resultadosVND[i].melhorSolucao << " " << resultadosVND[i].tempo << " " << resultadosVND[i].gap << std::endl;
    }


    // Armazenar resultados
    Resultados resultados;
    resultados.instancia = nomeInstancia;
    resultados.vnd = resultadosVND[0];  // Exemplo de como você pode armazenar o primeiro resultado
    //resultados.heuristica = resultadoHeuristica[0];  // Exemplo de como você pode armazenar o primeiro resultado

    // Exibir resultados
    std::cout << "Resultados computacionais:\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "Instância: " << resultados.instancia << "\n";
    std::cout << "Valor Otimo: "<<  valorOtimo << "\n";
     std::cout << "---------------------------------------------\n";

/*
    std::cout << "ILS ou GAp:\n";
    std::cout << "  Melhor solução: " << resultados.heuristica.melhorSolucao << "\n";
    std::cout << "  Tempo: " << resultados.heuristica.tempo << "\n";
    std::cout << "  Gap: " << resultados.heuristica.gap << "%\n";
*/

    std::cout << "\nVND:\n";
    std::cout << "  Melhor solução: " << resultados.vnd.melhorSolucao << "\n";
    std::cout << "  Tempo: " << resultados.vnd.tempo << "\n";
    std::cout << "  Gap: " << resultados.vnd.gap << "%\n";

    return 0;
}
