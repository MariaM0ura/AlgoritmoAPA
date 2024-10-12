<div>
  <h1>Problema de Otimização:<h1>
  <p>Seja n o número de pedidos que devem ser processados em um determinado dia na linha de
  produção da fábrica. Cada pedido i ∈ {1, . . . , n} requer um tempo ti (em minutos) para ser
  processado e deve ser concluı́do até o tempo pi . Entre o processamento de dois pedidos, pode
  ser necessário a limpeza e/ou adequação do tipo de embalagem. Sendo assim, consideramos
  que sij especifica o tempo (em minutos) necessário para preparar a linha de produção para
  processar o pedido j logo após o pedido i, onde i, j ∈ {1, . . . , n} e i ̸= j. Caso um pedido i
  seja finalizado após o tempo pi , a empresa paga uma multa por atraso Mi = wi ∗ (Ci − pi )(Multa = max(0, Valor Multa por Minuto *(Tempo de Conclusão − Prazo))), onde Ci especifica o tempo de término do processamento do pedido i e wi determina o valor
  da multa por minuto de atraso associada ao pedido i. O objetivo do problema é obter a
  sequência de processamento dos pedidos na linha de produção de forma a garantir que todos
  os pedidos sejam processados e que a soma das multas por atraso seja mı́nima.</p>

  <h5>Instancia</h5>
  <p>numeros_de_pedidos

  array_t (tempo dos pedidos)
  array_p (tempo de prazo dos pedidos a medida que corre o tempo)
  array_w (Multa de atraso)

  matriz_s ( tempo de preparação de linha ( limpeza para o proximo pedido ))

  exemplo:

  [5]                    numero de pedidos

  [15, 25, 20, 30, 20]   tempo de frabricação
  [25, 45, 75, 120, 135] prozo de frabricação 
  [10, 12, 30, 15, 10]   multa por atraso em segundo

  Matriz de limpeza 
  [ 0  10 15 8 21
    10 0 10 13 9
    17 9 0 10 14 
    11 13 12 0 10
    5 10 15 20 0 ]</p>
    
  <h5> Etapas e prazos <h5>
  <p>Este projeto contém os seguintes entregáveis:
  • Implementação de ao menos um algoritmo guloso para a geração de uma solução viável.
  • Implementação de pelo menos 3 movimentos de vizinhança.
  • Implementação do algoritmo de busca local chamado VND (Variable Neighborhood Descent).
  • Implementação de uma meta-heurı́stica (OPCIONAL). Sugestões: GRASP ou ILS.
  • Resultados computacionais: criar uma tabela que contenha os resultados obtidos pela(s) heurı́stica(s)
  construtiva(s) e pelo VND, e que compare tais resultados com a solução ótima de cada instância.
  Essa tabela deverá conter os seguintes dados para cada heurı́stica construtiva e para o VND:
  – Média do valor da solução (em no mı́nimo 10 execuções para cada instância caso exista
  algum fator aleatório no algoritmo)
  – Melhor solução encontrada
  – Média do tempo gasto pelo respectivo algoritmo
  – GAP para a solução ótima</p>

  <p> Caso decida implementar a <h3>meta-heurı́stica<h3>, é necessário adicionar uma coluna de resultados para ela na
  tabela.</p>

  <h1> Organizando pela Matriz de limpeza <h1>
  <p> A ordem dos pedidos vai depender da limpeza</p>
  <p>procedimento ILS 
  1 so GeraSolucaoInicial(); # Aqui foi usado o Guloso
  2 s← Busca Local(so);      # Aqui foi usado o vnd
  3 enquanto (os critérios de parada não estiverem satisfeitos) faça
  4 s' Perturbacao (histórico, s);
  5 s" ← Busca Local(s');
  6 s← CriterioAceitacao(s, s", histórico);
  8 fim-enquanto;
  fim ILS;
  </p>

  <h1>Algoritmo Guloso<h1>

Tomam decisões baseadas em escolhas locais ótimas na esperança de que essas escolhas levem a uma solução global ótima. 
Eles seguem o princípio da ganância (ou "greed"), fazendo a melhor escolha possível em cada etapa, sem reavaliar ou retroceder as decisões.

ler as instancias
ordernar por prazo 
A multa ele deve ser determinada sempre depois uma produção


</div>