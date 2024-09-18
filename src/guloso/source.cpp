#include "headers/source.h"
#include <iostream>
#include <vector>
#include <algorithm> // Para a função std::max e std::sort

Fruta::Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
    : n(n), t(t), p(p), m(m), matriz(matriz) {}

struct Pedido {
    int indice;
    int tempoProducao;
    int prazo;
    int multaPorMinuto;
};

/*
    ordena os pedidos pelo prazo de entrega e multa por minuto
*/
bool compararPedidos(const Pedido& a, const Pedido& b) {
    if (a.prazo == b.prazo) {
        return a.multaPorMinuto > b.multaPorMinuto; // Priorizar maior multa por minuto em caso de empate
    }
    return a.prazo < b.prazo; 
}

void Fruta::producion() {
    int tempoAtual = 0; 
    int valorTotalSolucao = 0;
    
    // Criar vetor de pedidos
    std::vector<Pedido> pedidos(n);
    for (int i = 0; i < n; ++i) {
        pedidos[i] = {i, t[i], p[i], m[i]};
    }

    std::sort(pedidos.begin(), pedidos.end(), compararPedidos);

    for (int i = 0; i < n; ++i) {
        const Pedido& pedido = pedidos[i];
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Início da " << i + 1 << "ª produção (Pedido " << pedido.indice + 1 << "):" << std::endl;
        
        std::cout << "Tempo atual: " << tempoAtual << std::endl;
        
        int producao = pedido.tempoProducao;
        int tempoConclusao = tempoAtual + producao;

        int multa = 0;
        if (tempoConclusao > pedido.prazo) {
            multa = std::max(0, pedido.multaPorMinuto * (tempoConclusao - pedido.prazo));
            std::cout << "Multa para o pedido " << pedido.indice + 1 << ": " << multa << std::endl;
        } else {
            std::cout << "Pedido " << pedido.indice + 1 << " entregue dentro do prazo" << std::endl;
        }

        std::cout << "Tempo da " << i + 1 << "ª produção: " << producao << std::endl;
        std::cout << "Tempo de conclusão: " << tempoConclusao << std::endl;

        tempoAtual += producao;
        valorTotalSolucao += multa; 

        if (i < n - 1) {
            int proximoPedido = pedidos[i + 1].indice;
            std::cout << "Tempo de limpeza entre produções: " << matriz[pedido.indice][proximoPedido] << std::endl;
            tempoAtual += matriz[pedido.indice][proximoPedido]; 
            std::cout << "Tempo atual após limpeza: " << tempoAtual << std::endl;
        }
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Valor total da solução: " << valorTotalSolucao << std::endl;
}
