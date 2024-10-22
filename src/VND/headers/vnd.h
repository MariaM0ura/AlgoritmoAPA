#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <string>  


/*
    Struct para Pedido 
    cada pedido vai ter um indice, tempo, prazo e a multa
*/
struct Pedido {
    int indice;
    int tempoProducao;
    int prazo;
    int multaPorMinuto; 
};

class Fruta {
public:
    int n;
    std::vector<int> t;
    std::vector<int> p;
    std::vector<int> m;
    std::vector<std::vector<int>> matriz;

    Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz);
    std::vector<Pedido> pedidos;

    void guloso();
    int calcularCusto(const std::vector<Pedido>& ordemPedidos, const std::vector<std::vector<int>>& matriz) const;

    /* VND na pratica*/
    double producao();
    std::tuple<double, double, double> producao(double valorOtimo);

    /* Movimentos de vizinhança */
    bool movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimento2Opt(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimentoReinsertion(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimentoOrOPT(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    
};

#endif
