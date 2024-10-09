#include "../VND/leitor.cpp"
#include "headers/ILS.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <numeric>
#include "../VND/headers/vizinhos.h" 

const double ACEITACAO_TOLERANCIA = 0.1;
const int ITERACOES = 1000;

int main(int argc, char* argv[]) {
    /*
        Leitura do arquivo da instacia ( pelo arquivo headers/leitor.cpp) -> isso é um padrão
        Ele foi modificado para que pudesse ler todos os arquivos 
    */

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

    std::srand(static_cast<unsigned>(std::time(0))); 

    /*
        Inicia a contrução do ILS
        Construtor da classe Fruta (ILS.h)
    */

    //std::cout << "Iniciando ILS\n";
    FrutaILS frutaILS(n, t, p, m, matriz);

    // Vetores para armazenar soluções e tempos
    std::vector<double> solucaoILS(ITERACOES);
    std::vector<double> tempoILS(ITERACOES);
    
    double melhorSolucao = std::numeric_limits<double>::max(); 
    double gap = 0.0;
    
    frutaILS.guloso();                                                 //GeraSolucaoInicial() -> Guloso
    
    // Solução inicial usando VND
    double solucaoInicialVND = frutaILS.producion(); 
    double solucaoAtual = solucaoInicialVND;

    for (int iter = 0; iter < ITERACOES; ++iter) {
        auto start_vnd = std::chrono::high_resolution_clock::now();

        frutaILS.perturbacaoPequeno(); // Inicia a perturbação na solução encontrada
        
        // Busca local após a perturbação
        double novaSolucao = frutaILS.producion(); 

        // Aceitação da nova solução
        solucaoAtual = frutaILS.criterioAceitacao(solucaoAtual, novaSolucao, ACEITACAO_TOLERANCIA); 

        solucaoILS[iter] = solucaoAtual; // Armazena a solução desta iteração

        auto end_vnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_vnd = end_vnd - start_vnd;
        tempoILS[iter] = diff_vnd.count();

        // Verifica se a solução atual é a melhor
        if (solucaoAtual < melhorSolucao) {
            melhorSolucao = solucaoAtual;
            //std::cout << "Melhorou a solução com ILS: " << melhorSolucao << " (Solução do VND: " << solucaoInicialVND << ")\n";
        }

        // Calcula o gap em relação ao valor ótimo
        if (valorOtimo != 0) {
            gap = (melhorSolucao - valorOtimo) / valorOtimo * 100.0;
        }
    }

    // Mostra o melhor resultado ao final das iterações
    std::cout << "ILS:\n";
    std::cout << "  Melhor solução: " << melhorSolucao << "\n";
    std::cout << "  Tempo médio por iteração: " << std::accumulate(tempoILS.begin(), tempoILS.end(), 0.0) / ITERACOES << " segundos\n";
    std::cout << "  Gap: " << gap << "%\n";

    return 0;
}
