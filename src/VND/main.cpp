#include "headers/vizinhos.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm> // Para usar std::min_element e std::max_element
#include <numeric>   // Para usar std::accumulate

int main() {
    int n_execucoes = 10; // Definir o número de execuções para calcular as médias

    int n = 5; // número de pedidos
    std::vector<int> t = {15, 25, 20, 30, 20}; // Produção
    std::vector<int> p = {25, 45, 75, 120, 135}; // Prazos
    std::vector<int> m = {10, 12, 30, 15, 10}; // Multas

    std::vector<std::vector<int>> matriz = { // Matriz de limpeza
        {0, 10, 15, 8, 21},
        {10, 0, 10, 13, 9},
        {17, 9, 0, 10, 14},
        {11, 13, 12, 0, 10},
        {5, 10, 15, 20, 0}
    };

    // Resultados
    std::vector<double> solucoes_construtiva(n_execucoes);
    std::vector<double> tempos_construtiva(n_execucoes);
    std::vector<double> solucoes_vnd(n_execucoes);
    std::vector<double> tempos_vnd(n_execucoes);

    Fruta fruta_construtiva(n, t, p, m, matriz);
    
    // Heurística construtiva
    for (int i = 0; i < n_execucoes; ++i) {
        auto start_construtiva = std::chrono::high_resolution_clock::now();

        // Inicializar pedidos
        std::vector<Pedido> pedidos(n);
        for (int j = 0; j < n; ++j) {
            pedidos[j] = {j, t[j], p[j], m[j]};
        }

        // Aplicar a heurística construtiva (exemplo: ordenar por prazo)
        std::sort(pedidos.begin(), pedidos.end(), [](const Pedido& a, const Pedido& b) {
            return a.prazo < b.prazo;
        });

        // Calcular o custo com a heurística construtiva
        double custo_construtiva = fruta_construtiva.calcularCusto(pedidos, matriz);
        solucoes_construtiva[i] = custo_construtiva;

        // Fim do tempo de execução
        auto end_construtiva = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_construtiva = end_construtiva - start_construtiva;
        tempos_construtiva[i] = diff_construtiva.count();
    }

    Fruta fruta_vnd(n, t, p, m, matriz);

    // Algoritmo VND
    for (int i = 0; i < n_execucoes; ++i) {
        auto start_vnd = std::chrono::high_resolution_clock::now();
        
        // Inicializar pedidos
        std::vector<Pedido> pedidos(n);
        for (int j = 0; j < n; ++j) {
            pedidos[j] = {j, t[j], p[j], m[j]};
        }

        // Aplicar o algoritmo VND
        fruta_vnd.producion(); // Você precisa garantir que a função producion() está implementada corretamente

        // Calcular o custo após VND
        double custo_vnd = fruta_vnd.calcularCusto(pedidos, matriz);
        solucoes_vnd[i] = custo_vnd;

        // Fim do tempo de execução
        auto end_vnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_vnd = end_vnd - start_vnd;
        tempos_vnd[i] = diff_vnd.count();
    }

    // Cálculo da média e melhor solução
    double media_solucao_construtiva = std::accumulate(solucoes_construtiva.begin(), solucoes_construtiva.end(), 0.0) / n_execucoes;
    double melhor_solucao_construtiva = *std::min_element(solucoes_construtiva.begin(), solucoes_construtiva.end());
    double media_tempo_construtiva = std::accumulate(tempos_construtiva.begin(), tempos_construtiva.end(), 0.0) / n_execucoes;

    double media_solucao_vnd = std::accumulate(solucoes_vnd.begin(), solucoes_vnd.end(), 0.0) / n_execucoes;
    double melhor_solucao_vnd = *std::min_element(solucoes_vnd.begin(), solucoes_vnd.end());
    double media_tempo_vnd = std::accumulate(tempos_vnd.begin(), tempos_vnd.end(), 0.0) / n_execucoes;

    // Exibir os resultados em forma de tabela
    std::cout << "Resultados computacionais:\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "                 | Heurística construtiva   | VND\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "Média Solução     | " << media_solucao_construtiva << "            | " << media_solucao_vnd << "\n";
    std::cout << "Melhor Solução    | " << melhor_solucao_construtiva << "            | " << melhor_solucao_vnd << "\n";
    std::cout << "Média Tempo (s)   | " << media_tempo_construtiva << "            | " << media_tempo_vnd << "\n";

    return 0;
}
