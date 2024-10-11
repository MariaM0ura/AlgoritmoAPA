#include "../VND/leitor.cpp"
#include "headers/ILS.h"
#include "../VND/headers/vizinhos.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <iomanip> 

const double ACEITACAO_TOLERANCIA = 0.1;
const int ITERACOES = 1000;

int main(int argc, char* argv[]) {
    /*
        Leitura do arquivo da instacia ( pelo arquivo headers/leitor.cpp) -> isso é um padrão
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

    FrutaILS frutaILS(n, t, p, m, matriz);

    std::vector<double> solucaoILS(ITERACOES);
    std::vector<double> tempoILS(ITERACOES);
    
    double melhorSolucao = std::numeric_limits<double>::max(); 
    double gap = 0.0;
    
    frutaILS.guloso();                                                 //GeraSolucaoInicial() -> Guloso
    
    // Solução inicial usando VND
    auto [solucaoInicialVND, tempoVND, gapVND] = frutaILS.producao(valorOtimo); 
    double solucaoAtual = solucaoInicialVND;

    bool alta = false;
    std::vector<double> ultimasSolucoes;                        // Armazena as últimas 10 soluções para calcular a média

    for (int iter = 0; iter < ITERACOES; ++iter) {
    auto start_vnd = std::chrono::high_resolution_clock::now();
    double solucaoAnterior = solucaoAtual;  

    if (alta) {
        frutaILS.perturbacaoAlta();  
    } else {
        frutaILS.perturbacaoPequeno(); 
    }

    // Busca local após a perturbação
    double novaSolucao = frutaILS.producao(); 

    solucaoAtual = frutaILS.criterioAceitacao(solucaoAtual, novaSolucao, ACEITACAO_TOLERANCIA); 

    solucaoILS[iter] = solucaoAtual;

    ultimasSolucoes.push_back(solucaoAtual);
    if (ultimasSolucoes.size() > 10) {
        ultimasSolucoes.erase(ultimasSolucoes.begin()); 
    }

    double somaUltimasSolucoes = std::accumulate(ultimasSolucoes.begin(), ultimasSolucoes.end(), 0.0);
    double mediaUltimasSolucoes = somaUltimasSolucoes / ultimasSolucoes.size();

    // Se a soma for maior que 20 e a média das últimas 10 for menor que 100000, ativa perturbação alta
    if (somaUltimasSolucoes > 20 && mediaUltimasSolucoes < 10000) {
        alta = true;
    }

    auto end_vnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff_vnd = end_vnd - start_vnd;
    tempoILS[iter] = diff_vnd.count();

    // Verifica se a solução atual é a melhor
    if (solucaoAtual < melhorSolucao) {
        melhorSolucao = solucaoAtual;
    }

    // Calcula o gap em relação ao valor ótimo
    if (valorOtimo != 0) {
        gap = (melhorSolucao - valorOtimo) / valorOtimo * 100.0;
        if(gap == 0) break;
    }
}



std::cout << std::setw(11) << std::left << nomeInstancia 
          << std::setw(10) << std::right << valorOtimo 
          << std::setw(18) << std::right << melhorSolucao 
          << std::setw(18) << std::right << std::accumulate(tempoILS.begin(), tempoILS.end(), 0.0) 
          << std::setw(15) << std::right << gap << "%" 
          << std::setw(20) << std::right << solucaoInicialVND 
          << std::setw(18) << std::right << tempoVND 
          << std::setw(15) << std::right << gapVND << "%" 
          << std::endl;

    return 0;
}
