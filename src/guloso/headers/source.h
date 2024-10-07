#ifndef SOURCE_H
#define SOURCE_H

#include <vector>

class Fruta {
private:
    int n;                                 // número de pedidos
    std::vector<int> t;                    // tempo de fabricação de cada pedido
    std::vector<int> p;                    // prazo de entrega de cada pedido
    std::vector<int> m;                    // multa por atraso de cada pedido
    std::vector<std::vector<int>> matriz;  // matriz de limpeza entre pedidos

public:
    Fruta(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz);

    void guloso();
};

#endif
