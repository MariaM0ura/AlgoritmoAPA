<div>
  <h1>Problema de Otimização:</h1>
  <p>
    Seja n o número de pedidos que devem ser processados em um determinado dia na linha de
    produção da fábrica. Cada pedido i ∈ {1, . . . , n} requer um tempo ti (em minutos) para ser
    processado e deve ser concluído até o tempo pi. Entre o processamento de dois pedidos, pode
    ser necessário a limpeza e/ou adequação do tipo de embalagem. Sendo assim, consideramos
    que sij especifica o tempo (em minutos) necessário para preparar a linha de produção para
    processar o pedido j logo após o pedido i, onde i, j ∈ {1, . . . , n} e i ≠ j. Caso um pedido i
    seja finalizado após o tempo pi, a empresa paga uma multa por atraso Mi = wi ∗ (Ci − pi)
    (Multa = max(0, Valor Multa por Minuto * (Tempo de Conclusão − Prazo))), onde Ci especifica o tempo de término do processamento do pedido i e wi determina o valor
    da multa por minuto de atraso associada ao pedido i. O objetivo do problema é obter a
    sequência de processamento dos pedidos na linha de produção de forma a garantir que todos
    os pedidos sejam processados e que a soma das multas por atraso seja mínima.
  </p>

  <h5>Instância</h5>
  <p>
    numeros_de_pedidos<br>
    array_t (tempo dos pedidos)<br>
    array_p (tempo de prazo dos pedidos à medida que corre o tempo)<br>
    array_w (Multa de atraso)<br>
    matriz_s (tempo de preparação de linha (limpeza para o próximo pedido))<br><br>
    exemplo:<br>
    [5]                    número de pedidos<br>
    [15, 25, 20, 30, 20]   tempo de fabricação<br>
    [25, 45, 75, 120, 135] prazo de fabricação<br>
    [10, 12, 30, 15, 10]   multa por atraso em segundo<br><br>
    Matriz de limpeza:<br>
    [ 0  10 15 8 21<br>
      10 0 10 13 9<br>
      17 9 0 10 14 <br>
      11 13 12 0 10<br>
      5 10 15 20 0 ]
  </p>
    
  <h5>Etapas e prazos</h5>
  <p>
    Este projeto contém os seguintes entregáveis:<br>
    • Implementação de ao menos um algoritmo guloso para a geração de uma solução viável.<br>
    • Implementação de pelo menos 3 movimentos de vizinhança.<br>
    • Implementação do algoritmo de busca local chamado VND (Variable Neighborhood Descent).<br>
    • Implementação de uma meta-heurística (OPCIONAL). Sugestões: GRASP ou ILS.<br>
    • Resultados computacionais: criar uma tabela que contenha os resultados obtidos pela(s) heurística(s)
    construtiva(s) e pelo VND, e que compare tais resultados com a solução ótima de cada instância.<br>
    Essa tabela deverá conter os seguintes dados para cada heurística construtiva e para o VND:<br>
    – Média do valor da solução (em no mínimo 10 execuções para cada instância caso exista
    algum fator aleatório no algoritmo)<br>
    – Melhor solução encontrada<br>
    – Média do tempo gasto pelo respectivo algoritmo<br>
    – GAP para a solução ótima
  </p>

  <p> 
    Caso decida implementar a <h3>meta-heurística</h3>, é necessário adicionar uma coluna de resultados para ela na
    tabela.
  </p>

  <h1>Organizando pela Matriz de limpeza</h1>
  <p> 
    A ordem dos pedidos vai depender da limpeza.
  </p>
  <p> 
    Procedimento ILS:<br>
    1. so GeraSolucaoInicial(); # Aqui foi usado o Guloso<br>
    2. s← Busca Local(so);      # Aqui foi usado o VND<br>
    3. enquanto (os critérios de parada não estiverem satisfeitos) faça<br>
    4. s' Perturbacao(histórico, s);<br>
    5. s" ← Busca Local(s');<br>
    6. s← CriterioAceitacao(s, s", histórico);<br>
    7. fim-enquanto;<br>
    fim ILS;
  </p>

  <h1>Algoritmo Guloso</h1>
  <p>
    Tomam decisões baseadas em escolhas locais ótimas na esperança de que essas escolhas levem a uma solução global ótima. 
    Eles seguem o princípio da ganância (ou "greed"), fazendo a melhor escolha possível em cada etapa, sem reavaliar ou retroceder as decisões.<br>
    Ler as instâncias<br>
    Ordenar por prazo<br>
    A multa deve ser determinada sempre depois da produção.
  </p>
</div>
