#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <string>  

struct VND {
    double melhorSolucao;
    double tempo;
    double gap;
};


struct Resultados {
    std::string instancia;  
    double solucaoOtima;
    VND vnd;
};

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
    
    double producion();
    void guloso();

    int calcularCusto(const std::vector<Pedido>& ordemPedidos, const std::vector<std::vector<int>>& matriz) const;

    bool movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimento2Opt(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimentoReinsertion(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimentoOrOPT(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimentoOrOPT3(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);

};

#endif
