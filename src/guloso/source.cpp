#include "headers/source.h"
#include <iostream>
#include <vector>
#include <algorithm> 

Fruta::Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
    : n(n), t(t), p(p), m(m), matriz(matriz) {}

struct Pedido {
    int indice;
    int tempoProducao;
    int prazo;
    int multaPorMinuto;
};

bool compararPedidos(const Pedido& a, const Pedido& b) {
    if (a.prazo == b.prazo) {
        return a.multaPorMinuto > b.multaPorMinuto; 
    }
    return a.prazo < b.prazo; 
}

void Fruta::guloso() {
    int tempoAtual = 0; 
    int valorTotalSolucao = 0;
    
    std::vector<Pedido> pedidos(n);

    for (int i = 0; i < n; ++i) {
        pedidos[i] = {i, t[i], p[i], m[i]};
    }

    std::sort(pedidos.begin(), pedidos.end(), compararPedidos);


    for (int i = 0; i < n; ++i) {
        const Pedido& pedido = pedidos[i];
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Pedido " << pedido.indice + 1 << std::endl;


        if( i == 0 ){
            std::cout << "Tempo de preparacão do Primeiro perdido : " << matriz[0][pedido.indice] << std::endl;
            tempoAtual += matriz[0][pedido.indice];
        }

        std::cout << "Início da " << i + 1 << "ª produção (Pedido " << pedido.indice + 1 << "):" << std::endl;
        
        std::cout << "Tempo atual: " << tempoAtual << std::endl;

        int producao = pedido.tempoProducao;
        int tempoConclusao = tempoAtual + producao;

        std::cout << "Tempo da " << i + 1 << "ª produção: " << producao << std::endl;
        std::cout << "Tempo de conclusão: " << tempoConclusao << " Prazo de conclusão: "<< pedido.prazo << std::endl;
        

        int multa = 0;
        if (tempoConclusao > pedido.prazo) {
            multa = std::max(0, pedido.multaPorMinuto * (tempoConclusao - pedido.prazo));
            std::cout << "Multa para o pedido " << pedido.indice + 1 << ": " << multa << " Atraso de: " << tempoConclusao - pedido.prazo << std::endl;
        } else {
            std::cout << "Pedido " << pedido.indice + 1 << " entregue dentro do prazo" << std::endl;
        }

        tempoAtual += producao;
        valorTotalSolucao += multa; 

        if (pedido.indice + 1 < matriz.size()) {
            int proximoPedido = pedidos[i + 1].indice;
            std::cout << "Tempo de limpeza entre produções: " << matriz[pedido.indice + 1][proximoPedido] << std::endl;
            tempoAtual +=matriz[pedido.indice + 1][proximoPedido]; 
            std::cout << "Tempo atual : " << tempoAtual << std::endl;
        }
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Valor total da solução: " << valorTotalSolucao << std::endl;
    
    
}

