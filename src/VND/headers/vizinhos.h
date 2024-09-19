#ifndef SOURCE_H
#define SOURCE_H

#include <vector>

struct Pedido {
    int indice;
    int tempoProducao;
    int prazo;
    int multaPorMinuto; 
};

class Fruta {
private:
    int n;
    std::vector<int> t;
    std::vector<int> p;
    std::vector<int> m;
    std::vector<std::vector<int>> matriz;



public:
    Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz);

    void producion();
    int calcularCusto(const std::vector<Pedido>& ordemPedidos, const std::vector<std::vector<int>>& matriz) const;
    bool movimentoMulta(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
    bool movimentoSwap(std::vector<Pedido>& pedidos, const std::vector<std::vector<int>>& matriz, int& melhorCusto);
};

#endif
