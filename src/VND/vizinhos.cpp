#include "headers/vizinhos.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

Fruta::Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
    : n(n), t(t), p(p), m(m), matriz(matriz) {}


bool compararPedidos(const Pedido& a, const Pedido& b) {
    if (a.prazo == b.prazo) {
        return a.multaPorMinuto > b.multaPorMinuto; 
    }
    return a.prazo < b.prazo; 
}

void Fruta::guloso() {
    int valorTotalSolucao = 0;
    
    std::vector<Pedido> pedidos(n);

    for (int i = 0; i < n; ++i) {
        pedidos[i] = {i, t[i], p[i], m[i]};
    }

    std::sort(pedidos.begin(), pedidos.end(), compararPedidos);

    valorTotalSolucao = calcularCusto(pedidos, matriz);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Valor total (Guloso): " << valorTotalSolucao << std::endl;

    this->pedidos = pedidos;    
}

int Fruta::calcularCusto(const std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz) const {
    int n = pedidos.size();
    int tempoAtual = 0;
    int valorTotalSolucao = 0;

    for (int i = 0; i < n; ++i) {
        const Pedido& pedido = pedidos[i];

        if (i == 0) {
            tempoAtual += matriz[0][pedido.indice];
        }

        int producao = pedido.tempoProducao;
        int tempoConclusao = tempoAtual + producao;

        int multa = (tempoConclusao > pedido.prazo) ? pedido.multaPorMinuto * (tempoConclusao - pedido.prazo) : 0;

        tempoAtual += producao;
        valorTotalSolucao += multa;

        if (i + 1 < n) {
            int proximoPedido = pedidos[i + 1].indice;
            tempoAtual += matriz[pedido.indice][proximoPedido];
        }
    }

    return valorTotalSolucao;
}

bool Fruta::movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {

            std::swap(pedidos[i], pedidos[j]);  

            int custoVizinho = calcularCusto(pedidos, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhoria = true;

            } else {
                std::swap(pedidos[i], pedidos[j]);  
            }            
        }
    }

    return melhoria;
}


bool Fruta::movimento2Opt(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhora = false;
    int tamanho = pedidos.size();

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            
            int custoVizinho = calcularCusto(pedidos, matriz);

            if (custoVizinho < melhorCusto) {
                    melhorCusto = custoVizinho;
                    melhora = true; 
            } else {
                std::reverse(pedidos.begin() + i, pedidos.begin() + j + 1);
            }
        }
    }
    return melhora;
}

bool Fruta::movimentoReinsertion(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();

    for (int i = 0; i < tamanho; ++i) {
        Pedido pedidoRemovido = pedidos[i]; 
        pedidos.erase(pedidos.begin() + i);

        for (int j = 0; j < tamanho - 1; ++j) { 
            if (j >= i) j++; 

            pedidos.insert(pedidos.begin() + j, pedidoRemovido);

            int custoAtual = calcularCusto(pedidos, matriz);

            if (custoAtual < melhorCusto) {
                melhorCusto = custoAtual;
                melhoria = true;
                break; 
            } else {
                pedidos.erase(pedidos.begin() + j);
            }
        }

        pedidos.insert(pedidos.begin() + i, pedidoRemovido);
    }

    return melhoria;
}

bool Fruta::movimentoOrOPT(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - 1; ++j) {
            if (i == j) continue;

            Pedido pedidoRemovido = pedidos[i];
            pedidos.erase(pedidos.begin() + i);
            pedidos.insert(pedidos.begin() + j, pedidoRemovido);

            int custoVizinho = calcularCusto(pedidos, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhoria = true;
            } else {
                pedidos.erase(pedidos.begin() + j);
                pedidos.insert(pedidos.begin() + i, pedidoRemovido); 
            }
        }
    }

    return melhoria;
}

bool Fruta::movimentoOrOPT3(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();

    // Iterar sobre todas as combinações de três elementos
    for (int i = 0; i < tamanho - 2; ++i) {
        // Salvar os pedidos a serem removidos
        Pedido pedidoRemovido1 = pedidos[i];
        Pedido pedidoRemovido2 = pedidos[i + 1];
        Pedido pedidoRemovido3 = pedidos[i + 2];

        // Remover os três pedidos
        pedidos.erase(pedidos.begin() + i, pedidos.begin() + i + 3); 

        // Testar inserções nas várias posições
        for (int j = 0; j < pedidos.size() + 1; ++j) {
            pedidos.insert(pedidos.begin() + j, pedidoRemovido1);
            pedidos.insert(pedidos.begin() + j + 1, pedidoRemovido2);
            pedidos.insert(pedidos.begin() + j + 2, pedidoRemovido3);

            // Calcular o custo após a inserção
            int custoVizinho = calcularCusto(pedidos, matriz);

            // Verificar se encontramos uma solução melhor
            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhoria = true;
            } 

            // Reverter as inserções
            pedidos.erase(pedidos.begin() + j, pedidos.begin() + j + 3);
        }

        pedidos.insert(pedidos.begin() + i, pedidoRemovido1);
        pedidos.insert(pedidos.begin() + i + 1, pedidoRemovido2);
        pedidos.insert(pedidos.begin() + i + 2, pedidoRemovido3);
    }

    return melhoria;
}



double Fruta::producion(){
    std::vector<Pedido> pedidos = this->pedidos;

    int melhorCusto = calcularCusto(pedidos, matriz);
    bool melhoria = true;

    while (melhoria) {
        melhoria = false;


        if(movimentoOrOPT(pedidos, matriz, melhorCusto)){
            melhoria = true;
            continue;
        }

        if (movimentoSwap(pedidos, matriz, melhorCusto)) {
            melhoria = true;
            continue;
        }

        if (movimento2Opt(pedidos, matriz, melhorCusto)) {
            melhoria = true;
            continue;
        }

        if (movimentoReinsertion(pedidos, matriz, melhorCusto)) {
            melhoria = true;
            continue;
        }

        if (movimentoOrOPT3(pedidos, matriz, melhorCusto)) {
            melhoria = true;
            continue;
        }


    }

    //std::cout << "Custo final após VND: " << melhorCusto << std::endl;

    return melhorCusto;
}
