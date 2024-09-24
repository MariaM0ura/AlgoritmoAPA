#include "headers/vizinhos.h"
#include "leitor.cpp" // Incluir o leitor
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>


int main() {
    // Leitura da vez
    /*
        Instancias do A ao P 
    */
    std::string caminho_arquivo = "instancias/n60A.txt";
    std::vector<std::string> nomeInstancia;


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

    int n_execucoes = 10;

    std::vector<double> solucoes_construtiva(n_execucoes);
    std::vector<double> tempos_construtiva(n_execucoes);
    std::vector<double> solucoes_vnd(n_execucoes);
    std::vector<double> tempos_vnd(n_execucoes);

    Fruta fruta_construtiva(n, t, p, m, matriz);


    std::vector<Heuristica> resultadoHeuristica;
    // Heurística construtiva
    for (int i = 0; i < n_execucoes; ++i) {
        auto start_construtiva = std::chrono::high_resolution_clock::now();

        // Inicializar pedidos
        std::vector<Pedido> pedidos(n);
        for (int j = 0; j < n; ++j) {
            pedidos[j] = {j, t[j], p[j], m[j]};
        }

        // Aplicar a heurística construtiva
        std::sort(pedidos.begin(), pedidos.end(), [](const Pedido& a, const Pedido& b) {
            return a.prazo < b.prazo;
        });

        // Calcular o custo com a heurística construtiva
        double custo_construtiva = fruta_construtiva.calcularCusto(pedidos, matriz);
        solucoes_construtiva[i] = custo_construtiva;

        auto end_construtiva = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_construtiva = end_construtiva - start_construtiva;
        tempos_construtiva[i] = diff_construtiva.count(); 

        double media_solucao_construtiva = std::accumulate(solucoes_construtiva.begin(), solucoes_construtiva.end(), 0.0) / n_execucoes;
        double melhor_solucao_construtiva = *std::min_element(solucoes_construtiva.begin(), solucoes_construtiva.end());
        double media_tempo_construtiva = std::accumulate(tempos_construtiva.begin(), tempos_construtiva.end(), 0.0) / n_execucoes;
        double gap = (media_solucao_construtiva - melhor_solucao_construtiva) / melhor_solucao_construtiva * 100;

        resultadoHeuristica[i] = { melhor_solucao_construtiva, media_solucao_construtiva, gap}
    }

    // Algoritmo VND

    std::vector<VND> resultadosVND;

    Fruta fruta_vnd(n, t, p, m, matriz);
    /*
        Inicio do VDN não precisa de 10 execuções somente se o houver algoritmo de aleatoriedade
    */
    for (int i = 0; i < n_execucoes; ++i) {
        auto start_vnd = std::chrono::high_resolution_clock::now();

        // Inicializar pedidos
        std::vector<Pedido> pedidos(n);
        for (int j = 0; j < n; ++j) {
            pedidos[j] = {j, t[j], p[j], m[j]};
        }

        // Aplicar o algoritmo VND
        fruta_vnd.producion(); 

        // Calcular o custo após VND
        double custo_vnd = fruta_vnd.calcularCusto(pedidos, matriz);
        solucoes_vnd[i] = custo_vnd;

        auto end_vnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_vnd = end_vnd - start_vnd;
        tempos_vnd[i] = diff_vnd.count();


        double media_solucao_vnd = std::accumulate(solucoes_vnd.begin(), solucoes_vnd.end(), 0.0) / n_execucoes;
        double melhor_solucao_vnd = *std::min_element(solucoes_vnd.begin(), solucoes_vnd.end());
        double media_tempo_vnd = std::accumulate(tempos_vnd.begin(), tempos_vnd.end(), 0.0) / n_execucoes;

        resultadosVND[i] = { melhor_solucao_vnd, media_tempo_vnd, gap};

    }

    std::vector<Resultados> resultados[n];

    for(int i = 0; i < n; i++){
        resultados[i] = { nomeInstancia, resultadoHeuristica, resultadosVND}
    }

    /*
    
    O VECTOR RESULTADO VAI SER ENVIADO PARA UM ARQUIVO CHAMADO result.txt
    para mostra a a tabela de resultados
    baseado na instancia 
    */

    // Exibir resultados



    return 0;
}
