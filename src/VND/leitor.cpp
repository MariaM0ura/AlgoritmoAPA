#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

/*
    Leitor.cpp vai lê o arquivo separando em cada variável e enviar para o main
    A tupla vai receber todos os dados dos pedidos, separando eles
    E vai retornar todos os valores  (numero de pedidos, tempo, prazo, multa, matriz de limpeza)
    Complexidade O(n^2) por causa da matriz de limpeza
*/


std::tuple<int, std::vector<int>, std::vector<int>, std::vector<int>, std::vector<std::vector<int>>> ler_instancia(const std::string& caminho_arquivo) {
    std::ifstream file(caminho_arquivo);

    if (!file) {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        throw std::runtime_error("Arquivo não encontrado");
    }

    int num_de_pedidos;
    file >> num_de_pedidos;

    std::vector<int> t(num_de_pedidos), p(num_de_pedidos), w(num_de_pedidos);
    for (int i = 0; i < num_de_pedidos; i++) file >> t[i];
    for (int i = 0; i < num_de_pedidos; i++) file >> p[i];
    for (int i = 0; i < num_de_pedidos; i++) file >> w[i];

    std::vector<std::vector<int>> matriz(num_de_pedidos, std::vector<int>(num_de_pedidos));
    for (int i = 0; i < num_de_pedidos; i++) {
        for (int j = 0; j < num_de_pedidos; j++) {
            file >> matriz[i][j];
        }
    }

    file.close();
    return std::make_tuple(num_de_pedidos, t, p, w, matriz);
}
