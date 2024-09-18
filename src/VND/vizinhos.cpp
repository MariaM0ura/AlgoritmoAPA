#include "headers/vizinhos.h"
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

// Função que calcula o valor total da solução (custo/multa) para uma sequência de pedidos
int calcularCusto(const std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz) {
    int tempoAtual = 0;
    int valorTotalSolucao = 0;
    
    for (int i = 0; i < pedidos.size(); ++i) {
        int producao = pedidos[i].tempoProducao;
        int prazo = pedidos[i].prazo;
        int multaPorMinuto = pedidos[i].multaPorMinuto;

        int tempoConclusao = tempoAtual + producao;
        int multa = std::max(0, multaPorMinuto * (tempoConclusao - prazo));
        valorTotalSolucao += multa;
        
        tempoAtual = tempoConclusao;
        if (i < pedidos.size() - 1) {
            tempoAtual += matriz[pedidos[i].indice][pedidos[i + 1].indice];
        }
    }
    
    return valorTotalSolucao;
}

// Função para aplicar a primeira vizinhança: troca dois pedidos
bool vizinhancaTroca(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    for (int i = 0; i < pedidos.size(); ++i) {
        for (int j = i + 1; j < pedidos.size(); ++j) {
            std::swap(pedidos[i], pedidos[j]);
            int novoCusto = calcularCusto(pedidos, matriz);
            
            if (novoCusto < melhorCusto) {
                melhorCusto = novoCusto;
                return true; // Encontrou melhoria
            }
            std::swap(pedidos[i], pedidos[j]); // Reverter a troca
        }
    }
    return false;
}

// Função para aplicar a segunda vizinhança: mover um pedido para outra posição
bool vizinhancaMover(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    for (int i = 0; i < pedidos.size(); ++i) {
        Pedido pedidoMovido = pedidos[i];
        
        for (int j = 0; j < pedidos.size(); ++j) {
            if (i == j) continue;
            
            pedidos.erase(pedidos.begin() + i);
            pedidos.insert(pedidos.begin() + j, pedidoMovido);
            int novoCusto = calcularCusto(pedidos, matriz);
            
            if (novoCusto < melhorCusto) {
                melhorCusto = novoCusto;
                return true; // Encontrou melhoria
            }
            pedidos.erase(pedidos.begin() + j);
            pedidos.insert(pedidos.begin() + i, pedidoMovido); // Reverter movimento
        }
    }
    return false;
}

// Função para aplicar a terceira vizinhança: reverter uma subsequência
bool vizinhancaReverter(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    for (int i = 0; i < pedidos.size(); ++i) {
        for (int j = i + 2; j < pedidos.size(); ++j) {
            std::reverse(pedidos.begin() + i, pedidos.begin() + j);
            int novoCusto = calcularCusto(pedidos, matriz);
            
            if (novoCusto < melhorCusto) {
                melhorCusto = novoCusto;
                return true; // Encontrou melhoria
            }
            std::reverse(pedidos.begin() + i, pedidos.begin() + j); // Reverter a subsequência
        }
    }
    return false;
}

// Implementação da função de produção com VND
void Fruta::producion() {
    // Criar vetor de pedidos
    std::vector<Pedido> pedidos(n);
    for (int i = 0; i < n; ++i) {
        pedidos[i] = {i, t[i], p[i], m[i]};
    }

    // Começar com uma solução inicial (gulosa): ordenar por prazo e multa por minuto
    std::sort(pedidos.begin(), pedidos.end(), [](const Pedido& a, const Pedido& b) {
        return (a.prazo < b.prazo) || (a.prazo == b.prazo && a.multaPorMinuto > b.multaPorMinuto);
    });

    // Calcular o custo inicial
    int melhorCusto = calcularCusto(pedidos, matriz);
    std::cout << "Custo inicial: " << melhorCusto << std::endl;

    // VND: explorar diferentes vizinhanças
    bool melhoria = true;
    while (melhoria) {
        melhoria = false;
        
        // Vizinhança 1: troca
        if (vizinhancaTroca(pedidos, matriz, melhorCusto)) {
            melhoria = true;
            continue;
        }

        // Vizinhança 2: mover
        if (vizinhancaMover(pedidos, matriz, melhorCusto)) {
            melhoria = true;
            continue;
        }

        // Vizinhança 3: reverter subsequência
        if (vizinhancaReverter(pedidos, matriz, melhorCusto)) {
            melhoria = true;
            continue;
        }
    }

    // Exibir a solução final e seu custo
    std::cout << "Custo final após VND: " << melhorCusto << std::endl;
    std::cout << "Sequência final de produção: ";
    for (const Pedido& pedido : pedidos) {
        std::cout << pedido.indice + 1 << " ";
    }
    std::cout << std::endl;
}
