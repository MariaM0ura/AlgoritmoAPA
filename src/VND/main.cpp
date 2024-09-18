#include "headers/vizinhos.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm> // Para usar std::min_element e std::max_element

int main() {
    int n_execucoes = 10; // Definir o número de execuções para calcular as médias
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

    // Vetores para armazenar os resultados
    std::vector<double> solucoes_construtiva(n_execucoes);
    std::vector<double> tempos_construtiva(n_execucoes);
    std::vector<double> solucoes_vnd(n_execucoes);
    std::vector<double> tempos_vnd(n_execucoes);

    // Loop para executar o algoritmo várias vezes e armazenar os resultados
    for (int i = 0; i < n_execucoes; ++i) {
        // Início do tempo de execução para heurística construtiva
        auto start_construtiva = std::chrono::high_resolution_clock::now();
        
        // Executar a heurística construtiva (adaptar para o seu código)
        Fruta fruta_construtiva(n, t, p, m, matriz);
        fruta_construtiva.producion(); // Exemplo de função que executa a heurística construtiva
        solucoes_construtiva[i] = fruta_construtiva.getSolucao(); // Função que retorna o valor da solução
        
        // Fim do tempo de execução
        auto end_construtiva = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_construtiva = end_construtiva - start_construtiva;
        tempos_construtiva[i] = diff_construtiva.count();

        // Início do tempo de execução para VND
        auto start_vnd = std::chrono::high_resolution_clock::now();
        
        // Executar o VND (adaptar para o seu código)
        Fruta fruta_vnd(n, t, p, m, matriz);
        fruta_vnd.producion(); // Exemplo de função que executa o VND
        solucoes_vnd[i] = fruta_vnd.getSolucao(); // Função que retorna o valor da solução

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
    std::cout << "---------------------------------------------\n";

    return 0;
}
