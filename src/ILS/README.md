procedimento ILS 
1 so GeraSolucaoInicial(); # Aqui foi usado o Guloso
2 s← Busca Local(so);      # Aqui foi usado o vnd
3 enquanto (os critérios de parada não estiverem satisfeitos) faça
4 s' Perturbacao (histórico, s);
5 s" ← Busca Local(s');
6 s← CriterioAceitacao(s, s", histórico);
8 fim-enquanto;
fim ILS;