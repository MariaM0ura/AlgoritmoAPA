#include "headers/ILS.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>


/*
    Pertubação
    Um numero vai ser gerado aleatoriamente entre 0 e o tamanho do pedido
    Por ser uma pertubacao pequena, o numero de trocas é no minimo 3 e no maximo metade do tamanho do pedido
    Nele vai pegar dois indicios aleatorios e vai trocar os pedidos de lugar
    Complexidade: O(n)
*/

void FrutaILS::perturbacaoPequeno() {
    std::vector<Pedido> pedidos = this->pedidos;
    int tamanho = pedidos.size();
    
    // número aleatório por gerador Mersenne Twister
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, tamanho - 1);

    int numTrocas = std::min(3, tamanho/2); 
    for (int k = 0; k < numTrocas; ++k) {
        int i = dist(rng);
        int j = dist(rng);

        while (i == j) {
            j = dist(rng);
        }

        std::swap(pedidos[i], pedidos[j]);
    }

    this->pedidos = pedidos;
}
/*
    Pertubação Alta
    Seguindo o mesmo raciocinio da pertubação pequena
    A diferenca vai ser no numero de trocas, sendo aqui no minimo 20 e no maximo o tamanho total
    Complexidade: O(n)
*/


void FrutaILS::perturbacaoAlta() {
    std::vector<Pedido> pedidos = this->pedidos;
    int tamanho = pedidos.size();
    
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, tamanho - 1);

    int numTrocas = std::min(20, tamanho); 
    for (int k = 0; k < numTrocas; ++k) {
        int i = dist(rng);
        int j = dist(rng);

        while (i == j) {
            j = dist(rng);
        }

        std::swap(pedidos[i], pedidos[j]);
    }

    this->pedidos = pedidos;
}


/*
    Desativado porque encontrei valores melhores sem ele
    Critério De Aceitação Com Função Linear Decrescente
    Se a soluçãoAtual for melhor que a melhorSolução, a solução atual é aceita
    Se a soluçãoAtual for pior que a melhorSolução, então é calculada o seu delta que é a diferença das soluções 
    Apartir dai vai ser calculado a probabilidade baseado na temperatura
    Quanto maior a temperatura maior a possibilidade dele aceitar uma solucaoAtual pior
    Depois é gerado um número aleatório entre 0 e 1 
    Se esse numero for menor que a probabilidade, a soluçãoAtual é aceita
    Complexidade: O(1)
*/
double FrutaILS::criterioAceitacao(double melhorSolucao, double solucaoAtual, double temperatura){
    if (solucaoAtual < melhorSolucao) {
        return solucaoAtual;
    }

    double delta = solucaoAtual - melhorSolucao;
    double probabilidade = std::exp(-delta / temperatura);

    // número aleatório por gerador Mersenne Twister
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    if (dist(rng) < probabilidade) {
        return solucaoAtual;
    }

    return melhorSolucao;
}
