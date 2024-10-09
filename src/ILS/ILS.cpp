#include "headers/ILS.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>


/*
    Pertubação
    Swap de forma aleaatoria
    Nivel de agrassividade: pequeno 
    Complexidade: O(n)

*/

void FrutaILS::perturbacaoPequeno() {
    std::vector<Pedido> pedidos = this->pedidos;
    int tamanho = pedidos.size();
    
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, tamanho - 1);

    // Aumenta a escala da perturbação
    int numTrocas = std::min(3, tamanho / 2); // Trocar até 3 pedidos ou metade do tamanho total
    for (int k = 0; k < numTrocas; ++k) {
        int i = dist(rng);
        int j = dist(rng);

        while (i == j) {
            j = dist(rng);
        }

        // Troca ou modifica pedidos
        std::swap(pedidos[i], pedidos[j]);
    }

    // Substitui a solução atual pela solução perturbada
    this->pedidos = pedidos;
}


double FrutaILS::iLS(int iteracao)
{
    std::vector<Pedido> melhorSolucao = this->pedidos;

    double melhorCusto = this->calcularCusto(melhorSolucao, this->matriz);
    double custoAtual = melhorCusto;

    for (int i = 0; i < iteracao; ++i) {
        std::vector<Pedido> solucaoComPerturbacao = melhorSolucao;

        this->perturbacaoPequeno();
        this->pedidos = solucaoComPerturbacao;
        custoAtual = this->calcularCusto(solucaoComPerturbacao, this->matriz);

        if (custoAtual < melhorCusto) {
            melhorCusto = custoAtual;
            melhorSolucao = this->pedidos;
        }
    }

    return melhorCusto;
}

double FrutaILS::criterioAceitacao(double melhorSolucao, double solucaoAtual, double temperatura){
    if (solucaoAtual < melhorSolucao) {
        return solucaoAtual;
    }

    double delta = solucaoAtual - melhorSolucao;
    double probabilidade = std::exp(-delta / temperatura);

    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    if (dist(rng) < probabilidade) {
        return solucaoAtual;
    }

    return melhorSolucao;
}
