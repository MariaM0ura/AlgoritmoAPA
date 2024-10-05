#include "headers/vizinhos.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

Fruta::Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
    : n(n), t(t), p(p), m(m), matriz(matriz) {}

// Cálculo do custo total da solução
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

        if (pedido.indice + 1 < matriz.size()) {
            int proximoPedido = pedidos[i + 1].indice;
            tempoAtual += matriz[pedido.indice + 1][proximoPedido];
        }
    }

    return valorTotalSolucao;
}


bool Fruta::movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();
    std::vector<bool> fixado(tamanho, false);

    for (int i = 0; i < tamanho - 1; ++i) {
        if (fixado[i]) continue;  

        for (int j = i + 1; j < tamanho; ++j) {
            if (fixado[j]) continue;  

            std::swap(pedidos[i], pedidos[j]);  

            /*
                Fazer calculo somente onde foi modificado o valor do vetor
            */
            int custoVizinho = calcularCusto(pedidos, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhoria = true;

                fixado[i] = true;  
                fixado[j] = true;
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

    for (int i = 0; i < tamanho; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            std::reverse(pedidos.begin() + i, pedidos.begin() + j + 1);

            int custoVizinho = calcularCusto(pedidos, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhora = true;
            } else {
                std::reverse(pedidos.begin() + i, pedidos.begin() + j + 1); // desfaz o reverse
            }
        }
    }

    return melhora;
}

bool Fruta::movimentoReinsertion(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
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

double Fruta::producion() {
    std::vector<Pedido> pedidos(n);
    for (int i = 0; i < n; ++i) {
        pedidos[i] = {i, t[i], p[i], m[i]};
    }

    int melhorCusto = calcularCusto(pedidos, matriz);
    bool melhoria = true;

    while (melhoria) {
        melhoria = false;

        if (movimentoSwap(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria no Swap: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }

        std::cout << "Não melhorou mais no swap, custo ficou: "<< melhorCusto  << std::endl;

        if (movimento2Opt(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria no 2Opt: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }

        std::cout << "Não melhorou mais no 2Opt, custo ficou: "<< melhorCusto << std::endl;

        if (movimentoReinsertion(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria no Reinsertion: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }
        std::cout << "Não melhorou mais no Reinsertion, custo ficou: "<< melhorCusto << std::endl;

    }

    std::cout << "Não melhorou nem no swap nem no 2OPT nem no Reinsertion"  << std::endl;

    std::cout << "Custo final após VND: " << melhorCusto << std::endl;


    /*
    std::cout << "Sequência final de produção: ";
    for (const Pedido& pedido : pedidos) {
        std::cout << pedido.indice + 1 << " ";
    }

    
    */
    

    return melhorCusto;
}
