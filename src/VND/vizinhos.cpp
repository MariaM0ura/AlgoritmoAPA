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

bool Fruta::movimentoMulta(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    int tamanho = pedidos.size();
    bool encontrouMelhoria = false;

    for (int i = 0; i < tamanho; ++i) {
        for (int j = i + 1; j < tamanho - 1; ++j) {
            std::swap(pedidos[i], pedidos[j]);

            int custoVizinho = calcularCusto(pedidos, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                encontrouMelhoria = true;
            } else {
                std::swap(pedidos[i], pedidos[j]); // desfaz o swap
            }
        }
    }

    return encontrouMelhoria;
}

bool Fruta::movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();
    std::cout << "Tamanho: " << tamanho << std::endl;

    std::vector<bool> fixado(tamanho, false);

    for (int i = 0; i < tamanho; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            std::swap(pedidos[i], pedidos[j]);

            int custoVizinho = calcularCusto(pedidos, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                std::cout << "Melhorou o custo: " << melhorCusto << std::endl;
                melhoria = true;

                for(i = i + 1; i < tamanho; ++i){
                    if(fixado[i]) continue;

                    for(j = j + 1; j < tamanho; ++j){
                        if(fixado[j]) continue;

                        std::swap(pedidos[i], pedidos[j]);
                        int custoVizinho = calcularCusto(pedidos, matriz);

                        if(custoVizinho < melhorCusto){
                            melhorCusto = custoVizinho;
                            std::cout << "Melhorou o custo: " << melhorCusto << std::endl;
                            melhoria = true;

                            fixado[i] = true;
                            fixado[j] = true;
                            
                        } else {
                            std::swap(pedidos[i], pedidos[j]);
                        }
                    }
                }
            } else {
                std::swap(pedidos[i], pedidos[j]); // desfaz o swap
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
                pedidos.insert(pedidos.begin() + i, pedidoRemovido); // desfaz a reinserção
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
    std::cout << "Custo inicial: " << melhorCusto << std::endl;
    bool melhoria = true;

    while (melhoria) {
        melhoria = false;

        
        if (movimento2Opt(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria no 2Opt: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }

        if (movimentoReinsertion(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria no Reinsertion: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }

        if (movimentoMulta(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria no Multa: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }

        

        if (movimentoSwap(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria no Swap: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }
    }

    std::cout << "Custo final após VND: " << melhorCusto << std::endl;

    std::cout << "Sequência final de produção: ";
    for (const Pedido& pedido : pedidos) {
        std::cout << pedido.indice + 1 << " ";
    }

    return melhorCusto;
}
