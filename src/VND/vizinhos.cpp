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

        // Adicionar tempo de transição para o próximo pedido
        if (i < n - 1) {
            int tempoTransicao = matriz[pedido.indice][pedidos[i + 1].indice];
            tempoAtual += tempoTransicao;
        }
    }


    /*
    std::cout << "---------------------------------------------\n";
    std::cout << "Calculando custo para a sequência: ";
    for (const Pedido& pedido : pedidos) {
        std::cout << pedido.indice + 1 << " ";
    }
    std::cout << std::endl;
    std::cout << "Custo total da solução: " << valorTotalSolucao << std::endl;
    
    */

   return valorTotalSolucao;
    
}


// Função swap com troca por menor multa
bool Fruta::movimentoMulta(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    int tamanho = pedidos.size();
    bool encontrouMelhoria = false;
    int melhor_custo = melhorCusto;
    std::vector<Pedido> melhor_solucao = pedidos;

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            // Troca de pedidos
            std::vector<Pedido> solucao_vizinha = pedidos;
            std::swap(solucao_vizinha[i], solucao_vizinha[j]);

            // Converter a solução vizinha para um vetor de índices
            std::vector<int> ordem_vizinha(tamanho);
            for (int k = 0; k < tamanho; ++k) {
                ordem_vizinha[k] = solucao_vizinha[k].indice;
            }

            // Calcular o custo da nova solução
            int custo_vizinho = calcularCusto(solucao_vizinha, matriz);

            // Exibir informações sobre a troca e o custo
            //std::cout << "Trocando pedidos " << i + 1 << " e " << j + 1 << "\n";
            //std::cout << "Custo anterior: " << melhor_custo << " | Custo vizinho: " << custo_vizinho << "\n";

            // Se o custo da solução vizinha for menor, atualizar a melhor solução
            if (custo_vizinho < melhor_custo) {
                //std::cout << "Melhoria encontrada! Novo melhor custo: " << custo_vizinho << "\n";
                melhor_custo = custo_vizinho;
                melhor_solucao = solucao_vizinha;
                encontrouMelhoria = true;
            }
        }
    }

    // Atualizar a solução atual com a melhor solução encontrada
    pedidos = melhor_solucao;
    melhorCusto = melhor_custo;

    /*
    
    // Exibir a nova solução e o melhor custo, se houve melhoria
    if (encontrouMelhoria) {
        std::cout << "Melhor custo após movimento: " << melhor_custo << "\n";
        std::cout << "Solução após movimento: ";
        for (const auto& pedido : melhor_solucao) {
            std::cout << pedido.indice + 1 << " "; // Exibindo o índice +1 para representar a posição original do pedido
        }
        std::cout << std::endl;
    }

    */

    std::cout << "Melhor custo com Multa: " << melhor_custo << "\n";
    //std::cout << "Solução após movimento: ";
    
    return encontrouMelhoria;
}


bool Fruta::movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();
    std::vector<Pedido> melhorSolucao = pedidos;

    // Variáveis para armazenar a solução vizinha e o custo vizinho
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            // Troca de pedidos
            std::vector<Pedido> solucaoVizinha = pedidos;
            std::swap(solucaoVizinha[i], solucaoVizinha[j]);

            // Calcular o custo da nova solução
            int custoVizinho = calcularCusto(solucaoVizinha, matriz);

            // Exibir informações sobre a troca e o custo
            //std::cout << "Trocando pedidos " << pedidos[i].indice + 1 << " e " << pedidos[j].indice + 1 << "\n";
            //std::cout << "Custo anterior: " << melhorCusto << " | Custo vizinho: " << custoVizinho << "\n";

            // Se o custo da solução vizinha for menor, atualizar a melhor solução
            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhorSolucao = solucaoVizinha;
                melhoria = true;
            }
        }
    }

    // Se houve melhoria, atualizar a solução atual
    if (melhoria) {
        pedidos = melhorSolucao;
        std::cout << "Solução após movimento com Swap: ";
        /*
        for (const auto& pedido : melhorSolucao) {
            std::cout << pedido.indice + 1 << " "; // Exibindo o índice +1 para representar a posição original do pedido
        }
        std::cout << std::endl;
        */
        
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

           // Calcular o custo da nova solução
            int custoVizinho = calcularCusto(solucaoVizinha, matriz);

           // Se o custo da solução vizinha for menor, atualizar a melhor solução
           if (custoVizinho < melhorCusto) {
               melhorCusto = custoVizinho;
               melhorSolucao = solucaoVizinha;
               melhora = true;
           }
       }
   }

    // Atualizar a solução atual com a melhor solução encontrada
    pedidos = melhorSolucao;

    // Exibir a nova solução e o melhor custo, se houve melhoria


    
    if (melhora) {
        std::cout << "Melhor custo após movimento com 20pt: " << melhorCusto << "\n";
        /*
        std::cout << "Solução após movimento: ";
        for (const auto& pedido : melhorSolucao) {
            std::cout << pedido.indice + 1 << " "; // Exibindo o índice +1 para representar a posição original do pedido
        }
        std::cout << std::endl;
        */
    }    
    
    


    return melhora;
}

bool Fruta::movimentoReinsertion(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto) {
    bool melhoria = false;
    int tamanho = pedidos.size();
    std::vector<Pedido> melhorSolucao = pedidos;

    // Reinsertion: Remover um pedido e inseri-lo em outra posição
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            if (i == j) continue;  // Ignorar se a posição de reinserção for a mesma

            // Criar uma nova solução removendo o pedido i e inserindo na posição j
            std::vector<Pedido> solucaoVizinha = pedidos;
            
            // Remover o pedido da posição i
            Pedido pedidoRemovido = solucaoVizinha[i];
            solucaoVizinha.erase(solucaoVizinha.begin() + i);

            // Inserir o pedido na nova posição j
            solucaoVizinha.insert(solucaoVizinha.begin() + j, pedidoRemovido);

            // Calcular o custo da nova solução
            int custoVizinho = calcularCusto(solucaoVizinha, matriz);

            // Se o custo da solução vizinha for menor, atualizar a melhor solução
            if (custoVizinho < melhorCusto) {
                melhorCusto = custoVizinho;
                melhorSolucao = solucaoVizinha;
                melhoria = true;
            }
        }
    }

    // Atualizar a solução atual com a melhor solução encontrada
    pedidos = melhorSolucao;

    // Exibir a nova solução e o melhor custo, se houve melhoria

    
    if (melhoria) {
        std::cout << "Melhor custo após reinsertion: " << melhorCusto << "\n";
    /*
        std::cout << "Solução após reinsertion: ";
        for (const auto& pedido : melhorSolucao) {
            std::cout << pedido.indice + 1 << " ";  // Exibindo o índice +1 para representar a posição original do pedido
        }
        std::cout << std::endl;
     */
    }
    



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

    // Calcular o custo inicial com base na solução gulosa
    int melhorCusto = calcularCusto(pedidos, matriz);
    std::cout << "Custo inicial: " << melhorCusto << std::endl;

    // VND: explorar diferentes vizinhanças para melhorar a solução
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
