#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Função objetiva (fictícia, deve ser alterada para seu problema real)
double funcao_objetiva(vector<int>& solucao) {
    // Exemplo de soma dos valores
    double soma = 0.0;
    for (int val : solucao) {
        soma += val;
    }
    return soma;
}

// Movimento de Vizinhança 1: Troca dois elementos de posição
void movimento_vizinhanca1(vector<int>& solucao) {
    int i = rand() % solucao.size();
    int j = rand() % solucao.size();
    swap(solucao[i], solucao[j]);
}

// Movimento de Vizinhança 2: Inverte uma subsequência
void movimento_vizinhanca2(vector<int>& solucao) {
    int i = rand() % solucao.size();
    int j = rand() % solucao.size();
    if (i > j) swap(i, j);
    reverse(solucao.begin() + i, solucao.begin() + j);
}

// Movimento de Vizinhança 3: Incrementa ou decrementa um valor aleatório
void movimento_vizinhanca3(vector<int>& solucao) {
    int i = rand() % solucao.size();
    solucao[i] += (rand() % 3) - 1; // -1, 0, ou 1
}

// Busca Local (VND)
void VND(vector<int>& solucao_inicial, int max_iteracoes) {
    vector<int> melhor_solucao = solucao_inicial;
    double melhor_valor = funcao_objetiva(melhor_solucao);
    
    int iter = 0;
    while (iter < max_iteracoes) {
        vector<int> solucao_atual = melhor_solucao;
        double valor_atual = melhor_valor;
        bool melhora = false;

        // Vizinhança 1
        movimento_vizinhanca1(solucao_atual);
        double novo_valor = funcao_objetiva(solucao_atual);
        if (novo_valor < valor_atual) {
            melhor_solucao = solucao_atual;
            melhor_valor = novo_valor;
            melhora = true;
        }

        // Vizinhança 2
        solucao_atual = melhor_solucao;
        movimento_vizinhanca2(solucao_atual);
        novo_valor = funcao_objetiva(solucao_atual);
        if (novo_valor < valor_atual) {
            melhor_solucao = solucao_atual;
            melhor_valor = novo_valor;
            melhora = true;
        }

        // Vizinhança 3
        solucao_atual = melhor_solucao;
        movimento_vizinhanca3(solucao_atual);
        novo_valor = funcao_objetiva(solucao_atual);
        if (novo_valor < valor_atual) {
            melhor_solucao = solucao_atual;
            melhor_valor = novo_valor;
            melhora = true;
        }

        if (!melhora) {
            // Se nenhuma melhoria, encerra
            break;
        }

        iter++;
    }

    // Melhor solução encontrada
    solucao_inicial = melhor_solucao;
}

// Função para gerar uma solução inicial aleatória
vector<int> gerar_solucao_inicial(int tamanho) {
    vector<int> solucao(tamanho);
    for (int i = 0; i < tamanho; ++i) {
        solucao[i] = rand() % 100; // Valores aleatórios entre 0 e 99
    }
    return solucao;
}

int main() {
    srand(time(0));  // Inicializa o gerador de números aleatórios

    const int num_execucoes = 10;
    const int tamanho_instancia = 100;  // Tamanho da solução
    const int max_iteracoes = 1000;

    double soma_valor_solucao = 0.0;
    double melhor_solucao_global = 1e9;
    double soma_tempo_execucao = 0.0;

    for (int exec = 0; exec < num_execucoes; ++exec) {
        vector<int> solucao_inicial = gerar_solucao_inicial(tamanho_instancia);

        // Marca o tempo inicial
        auto inicio = high_resolution_clock::now();

        // Executa o VND
        VND(solucao_inicial, max_iteracoes);

        // Marca o tempo final
        auto fim = high_resolution_clock::now();
        double tempo_gasto = duration_cast<microseconds>(fim - inicio).count() / 1000.0; // ms

        double valor_solucao = funcao_objetiva(solucao_inicial);

        // Atualiza métricas
        soma_valor_solucao += valor_solucao;
        melhor_solucao_global = min(melhor_solucao_global, valor_solucao);
        soma_tempo_execucao += tempo_gasto;

        cout << "Execução " << exec + 1 << ": Valor da solução = " << valor_solucao << ", Tempo gasto = " << tempo_gasto << " ms" << endl;
    }

    // Média dos resultados
    double media_valor_solucao = soma_valor_solucao / num_execucoes;
    double media_tempo_execucao = soma_tempo_execucao / num_execucoes;

    cout << "\nResultados finais após " << num_execucoes << " execuções:" << endl;
    cout << "Melhor solução encontrada: " << melhor_solucao_global << endl;
    cout << "Média do valor da solução: " << media_valor_solucao << endl;
    cout << "Média do tempo gasto: " << media_tempo_execucao << " ms" << endl;

    return 0;
}
