#ifndef ILS_H
#define ILS_H

#include <vector>
#include <string> 
#include "../../VND/headers/vizinhos.h" 


struct ILS {
    double melhorSolucao;
    double tempo;
    double gap;
};

class FrutaILS : public Fruta{
public:
    FrutaILS(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
        : Fruta(n, t, p, m, matriz) {}  // Chama o construtor da classe base Fruta

    void perturbacaoPequeno();
    void perturbacaoAlta();

    double criterioAceitacao(double melhorSolucao, double solucaoAtual, double temperatura);
};

#endif
