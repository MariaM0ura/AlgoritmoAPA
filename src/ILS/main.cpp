#include "../VND/leitor.cpp"
#include "../VND/headers/vnd.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <iomanip> 

const double ACEITACAO_TOLERANCIA = 0.1;
const int ITERACOES = 500;

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
    
    frutaILS.guloso();                                                 //GeraSolucaoInicial() -> Guloso
    
    /*
        A ordem gerado pelo guloso vai para o VND
        Gerando a nova solução inicial com o VND
    */
    auto [solucaoInicialVND, tempoVND, gapVND] = frutaILS.producao(valorOtimo); 
    double solucaoAtual = solucaoInicialVND;

    bool alta = false;
    std::vector<double> ultimasSolucoes;                        

    /*
        ILS em ação
        O numero de iterações vai dizer o quanto o ILS vai rodar
        A variavel alta vai dizer se é preciso uma pertubação pequena ou alta,
        O calculo para definir isso é baseado na media das ultimas soluções
        Se houver 20 solucoes e a media deles for menor que 10000, a pertubacao alta é feita
        Faz a pertubação e gera uma nova solução com o busca local do VND
        Essa nova solução só é aceita se passar pelo critério de aceitação
        As solucoes aceitas vao para um vetor de solucoes
        Onde é calculado se precisa de uma pertubação alta ou não
        Se o ILS encontrar a melhor solução, ele para indepedente do iteração
        Complexidade: O(ITERACOES * n)
    */
    auto start_total = std::chrono::high_resolution_clock::now();  

    for (int iter = 0; iter < ITERACOES; ++iter) {

        if (alta) {
            frutaILS.perturbacaoAlta();  
        } else {
            frutaILS.perturbacaoPequeno(); 
        }

        double novaSolucao = frutaILS.producao(); 

        if (novaSolucao < solucaoAtual) {
            solucaoAtual = novaSolucao;
        }

        solucaoILS[iter] = solucaoAtual;

        ultimasSolucoes.push_back(solucaoAtual);
        if (ultimasSolucoes.size() > 10) {
            ultimasSolucoes.erase(ultimasSolucoes.begin()); 
        }

        double somaUltimasSolucoes = std::accumulate(ultimasSolucoes.begin(), ultimasSolucoes.end(), 0.0);
        double mediaUltimasSolucoes = somaUltimasSolucoes / ultimasSolucoes.size();

        if (somaUltimasSolucoes > 20 && mediaUltimasSolucoes < 10000) {
            alta = true;
        }

        if (melhorSolucao == valorOtimo) {
            break;
        }
    }

auto end_total = std::chrono::high_resolution_clock::now();  
std::chrono::duration<double> tempoTotal = end_total - start_total;

double gap = 0.0;
if (valorOtimo != 0) {
    gap = (melhorSolucao - valorOtimo) / valorOtimo * 100.0;
}


/*
    Ideal para mostrar os resultados no terminal, experimente !
*/
std::cout << std::setw(11) << std::left << nomeInstancia 
          << std::setw(10) << std::right << valorOtimo 
          << std::setw(18) << std::right << melhorSolucao 
          << std::setw(18) << std::right << tempoTotal.count()
          << std::setw(15) << std::right << gap << "%" 
          << std::setw(20) << std::right << solucaoInicialVND 
          << std::setw(18) << std::right << tempoVND 
          << std::setw(15) << std::right << gapVND << "%" 
          << std::endl;

    return 0;
}
