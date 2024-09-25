#include "headers/vizinhos.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

// Definição da classe Fruta e construtor
Fruta::Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
    : n(n), t(t), p(p), m(m), matriz(matriz) {}

/*
    calcula o custo total da solução
*/

int Fruta::calcularCusto(const std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz) const {
    int n = pedidos.size();
    int tempoAtual = 0;
    int valorTotalSolucao = 0;

    for (int i = 0; i < n; ++i) {
        const Pedido& pedido = pedidos[i];
        int producao = pedido.tempoProducao;
        int tempoConclusao = tempoAtual + producao;

        int multa = 0;
        if (tempoConclusao > pedido.prazo) {
            multa = std::max(0, pedido.multaPorMinuto * (tempoConclusao - pedido.prazo));
        }
        tempoAtual += producao;
        valorTotalSolucao += multa;

        if (i < n - 1) {
            int tempoTransicao = matriz[pedido.indice][pedidos[i + 1].indice];
            tempoAtual += tempoTransicao;
        }
    }

   return valorTotalSolucao;
    
}


bool Fruta::movimentoMulta(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    int tamanho = pedidos.size();
    bool encontrouMelhoria = false;
    int melhor_custo = melhorCusto;
    std::vector<Pedido> melhor_solucao = pedidos;

    /*
        Swwap com funcionalidade
    
    */

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            std::vector<Pedido> solucao_vizinha = pedidos;
            std::swap(solucao_vizinha[i], solucao_vizinha[j]);

            std::vector<int> ordem_vizinha(tamanho);
            for (int k = 0; k < tamanho; ++k) {
                ordem_vizinha[k] = solucao_vizinha[k].indice;
            }

            int custo_vizinho = calcularCusto(solucao_vizinha, matriz);

            if (custo_vizinho < melhor_custo) {
                melhor_custo = custo_vizinho;
                melhor_solucao = solucao_vizinha;
                encontrouMelhoria = true;
            }
        }
    }

    pedidos = melhor_solucao;
    melhorCusto = melhor_custo;

    return encontrouMelhoria;
}


bool Fruta::movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();
    std::vector<Pedido> melhorSolucao = pedidos;

    /*
        tá uma merdA isso aqui 
    
    */

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            std::vector<Pedido> solucaoVizinha = pedidos;
            std::swap(solucaoVizinha[i], solucaoVizinha[j]);

            int custoVizinho = calcularCusto(solucaoVizinha, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhorSolucao = solucaoVizinha;
                melhoria = true;
            }
        }
    }

    return melhoria;
}

bool Fruta::movimento2Opt(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhora = false;
    int tamanho = pedidos.size();
    std::vector<Pedido> melhorSolucao = pedidos;

    /*
        Comecar o 2Opt: testar toas as combinações de troca de arestas
    */
   for(int i = 0; i < tamanho -1; i++){
       for(int j = i + 1; j < tamanho; j++){
           std::vector<Pedido> solucaoVizinha = pedidos;
           std::reverse(solucaoVizinha.begin() + i, solucaoVizinha.begin() + j + 1);

            int custoVizinho = calcularCusto(solucaoVizinha, matriz);

           if (custoVizinho < melhorCusto) {
               melhorCusto = custoVizinho;
               melhorSolucao = solucaoVizinha;
               melhora = true;
           }
       }
   }

    pedidos = melhorSolucao;

    return melhora;
}

bool Fruta::movimentoReinsertion(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();
    std::vector<Pedido> melhorSolucao = pedidos;

    /*
    Reinsertion: Remover um pedido e inseri-lo em outra posição
    
    */ 
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            if (i == j) continue; 

            std::vector<Pedido> solucaoVizinha = pedidos;
            
            Pedido pedidoRemovido = solucaoVizinha[i];
            solucaoVizinha.erase(solucaoVizinha.begin() + i);

            solucaoVizinha.insert(solucaoVizinha.begin() + j, pedidoRemovido);

            int custoVizinho = calcularCusto(solucaoVizinha, matriz);

            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhorSolucao = solucaoVizinha;
                melhoria = true;
            }
        }
    }

    pedidos = melhorSolucao;

    return melhoria;
}


/*
    Função producion

    Custo Inicial: ordem natural dos pedidos
*/
double Fruta::producion() {
    std::vector<Pedido> pedidos(n);
    for (int i = 0; i < n; ++i) {
        pedidos[i] = {i, t[i], p[i], m[i]};
    }

    int melhorCusto = calcularCusto(pedidos, matriz);
    std::cout << "Custo inicial: " << melhorCusto << std::endl;


    /*
    VND: explorar diferentes vizinhanças para melhorar a solução
    
    */

    bool melhoria = true;
    while (melhoria) {
        melhoria = false;
        if (movimento2Opt(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria encontrada no 2Opt: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }
        
        if (movimentoReinsertion(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria encontrada no Reinsertion: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }

        if (movimentoMulta(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria encontrada no Multa: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }

        if (movimentoSwap(pedidos, matriz, melhorCusto)) {
            std::cout << "Melhoria encontrada no Swap: " << melhorCusto << std::endl;
            melhoria = true;
            continue;
        }
        
    }

    std::cout << "Custo final após VND: " << melhorCusto << std::endl;

    /*
    std::cout << "Sequência final de produção: ";
    for (const Pedido& pedido : pedidos) {
        std::cout << pedido.indice + 1 << " "; // Exibindo o índice +1 para representar a posição original do pedido
    }
    */

    return melhorCusto;
}
