#ifndef ILS_H
#define ILS_H

#include <vector>
#include <string> 
#include "../../VND/headers/vnd.h" 


class FrutaILS : public Fruta{
public:
    // Herdando o contrutor fruta do VND
    FrutaILS(int n, const std::vector<int>& t, const std::vector<int>& p, const std::vector<int>& m, const std::vector<std::vector<int>>& matriz)
        : Fruta(n, t, p, m, matriz) {} 

    void perturbacaoPequeno();
    void perturbacaoAlta();

    double criterioAceitacao(double melhorSolucao, double solucaoAtual, double temperatura);
};

#endif
