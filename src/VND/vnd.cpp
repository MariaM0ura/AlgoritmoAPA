#include "headers/vnd.h"
#include <algorithm>
#include <limits>
#include <vector>
#include <chrono>
#include <iostream>
#include <tuple>


/*
    Construtor da Fruta
    Vai receber o numero de pedidos, tempo, prazo, multa e a matriz de limpeza
*/
Fruta::Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
    : n(n), t(t), p(p), m(m), matriz(matriz) {}


/*
    Gulosos:
    Vai ordenar os pedidos de acordo com o menor prazo 
    Caso o prazo seja igual, vai ordenar pela maior multa, e quem faz isso é a função compararPedidos
    Não retornar nada pois os ele atualiza o vetor de pedidos (This->)

*/
bool compararPedidos(const Pedido& a, const Pedido& b) {
    if (a.prazo == b.prazo) {
        return a.multaPorMinuto > b.multaPorMinuto; 
    }
    return a.prazo < b.prazo; 
}

void Fruta::guloso() {
    //int valorTotalSolucao = 0;
    
    std::vector<Pedido> pedidos(n);

    for (int i = 0; i < n; ++i) {
        pedidos[i] = {i, t[i], p[i], m[i]};
    }

    std::sort(pedidos.begin(), pedidos.end(), compararPedidos);

    //valorTotalSolucao = calcularCusto(pedidos, matriz);

    /*
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Valor total (Guloso): " << valorTotalSolucao << std::endl;    
    */


    this->pedidos = pedidos;    
}


/*
    Calcula o custo:
    Vai receber o struct de pedidos(tempo, prazo, multa) e a matriz de limpeza
    Caso seja o primeiro pedido ele faz acrescenta no tempoAtual a preparação da maquina
    Se o tempo de conclusão for maior que o prazo, ele calcula a multa
    retornando o valor total da solucao, que é a soma das multas
    Complexidade O(n)
*/

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

/*
    -------- Movimento de vizinhança Swap --------
    Vai trocar a posição de dois pedidos e calcular o custo
    Caso o custo seja menor que o melhor custo, ele atualiza o melhor custo
    Se não desfaz a troca
    e retorna verdadeiro para melhora se houve pelo menos uma melhoria

    Complexidade O(n^3)
*/
bool Fruta::movimentoSwap(std::vector<Pedido> &pedidos, const std::vector<std::vector<int>> &matriz, int &melhorCusto){
    bool melhoria = false;
    int tamanho = pedidos.size();

    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {

            std::swap(pedidos[i], pedidos[j]);  

            int custoVizinho = calcularCusto(pedidos, matriz);           // O(n)

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

/*
    -------- Movimento de vizinhança 2Opt --------
    Vai inverter a ordem de dois pedidos e calcular o custo
    Caso o custo seja menor que o melhor custo, ele atualiza o melhor custo
    Se não desfaz a inversão
    e retorna verdadeiro para melhora se houve pelo menos uma melhoria, caso contrário ele retorna falso

    Complexidade O(n^3)

*/
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

/*
    -------- Movimento de vizinhança Reinsertion --------
    Vai remover um pedido e inserir em outra posição e calcular o custo
    Caso o custo seja menor que o melhor custo, ele atualiza o melhor custo
    Se não desfaz a remoção e inserção
    e retorna verdadeiro para melhora se houve pelo menos uma melhoria, caso contrário ele retorna falso

    Complexidade O(n^3)

*/
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

/*
    -------- Movimento de vizinhança OrOPT --------
    Vai remover um pedido e inserir em outra posição e calcular o custo
    Caso o custo seja menor que o melhor custo, ele atualiza o melhor custo
    Se não desfaz a remoção e inserção
    e retorna verdadeiro para melhora se houve pelo menos uma melhoria, caso contrário ele retorna falso

    Complexidade O(n^3)

*/
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



/*
    função de VND (producao(double valorOtimo)) com retorno dos seus resultados para o montagem da tabela de resultados com o ILS
    Tem a mesma função do producao() com retorno somente do valor da produção
    Aqui ele retonar o custo, tempo e gap
    ------------ Repetido ------------
    ------ Funcionamento do VND ------
    recebe os pedidos na ordem do guloso 
    melhorCusto inicia com o custo do guloso
    existe uma variavel melhoria que é um booleano que inicia como true
    enquanto houver melhoria ele vai continuar rodando o VND
    dentro o while, melhoria recebe o valor false, e a cada movimento ele verifica se houve melhoria
    Se ele encontrar uma melhoria, volta para o inicio do while e continua rodando
    Saira do while, se e somente se não houver melhoria em nenhum dos movimentos de vizinhaça
    retorna o melhorCusto encontrado por busca local
*/
std::tuple<double, double, double> Fruta::producao(double valorOtimo){
  std::vector<Pedido> pedidos = this->pedidos;
    int melhorCusto = calcularCusto(pedidos, matriz);
    bool melhoria = true;

    auto start = std::chrono::high_resolution_clock::now();

    while (melhoria) {
        melhoria = false;

        if (movimentoOrOPT(pedidos, matriz, melhorCusto)) {
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
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    double tempo = diff.count();

    double gap;
    if (valorOtimo == 0) {
        gap = (melhorCusto == 0) ? 0 : 100;  
    } else {
        gap = (melhorCusto - valorOtimo) / valorOtimo * 100;
    }

    return std::make_tuple(melhorCusto, tempo, gap);
}


/*
    ------ Funcionamento do VND ------
    recebe os pedidos na ordem do guloso 
    melhorCusto inicia com o custo do guloso
    existe uma variavel melhoria que é um booleano que inicia como true
    enquanto houver melhoria ele vai continuar rodando o VND
    dentro o while, melhoria recebe o valor false, e a cada movimento ele verifica se houve melhoria
    Se ele encontrar uma melhoria, volta para o inicio do while e continua rodando
    Saira do while, se e somente se não houver melhoria em nenhum dos movimentos de vizinhaça
    retorna o melhorCusto encontrado por busca local
    --------- Objetivo de existencia ---------
    Esse função existe para ser chamada no ILS, uma vez que só precisamos dos resultados iniciais do VND 
    Aqui apenas faz o retorno da melhoria do custo
    -----------------------------------------
    Complexidade: 

*/
double Fruta::producao(){
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
    }

    //std::cout << "Custo final após VND: " << melhorCusto << std::endl;

    return melhorCusto;
}
