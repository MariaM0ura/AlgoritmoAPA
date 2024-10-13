<div>
  <h1>Problema de Otimização</h1>
  <p>
      Considere que <strong>n</strong> é o número de pedidos que devem ser processados em um determinado dia na linha de produção da fábrica. Cada pedido <strong>i</strong> (onde <strong>i</strong> pertence a {1, . . . , <strong>n</strong>}) requer um tempo <strong>t<sub>i</sub></strong> (em minutos) para ser processado e deve ser concluído até o tempo <strong>p<sub>i</sub></strong>. Entre o processamento de dois pedidos, pode ser necessário realizar a limpeza e/ou a adequação do tipo de embalagem. Assim, consideramos que <strong>s<sub>ij</sub></strong> especifica o tempo (em minutos) necessário para preparar a linha de produção para processar o pedido <strong>j</strong> logo após o pedido <strong>i</strong>, onde <strong>i</strong> e <strong>j</strong> pertencem a {1, . . . , <strong>n</strong>} e <strong>i ≠ j</strong>. 
  </p>
  <p>
      Se um pedido <strong>i</strong> for finalizado após o tempo <strong>p<sub>i</sub></strong>, a empresa deverá pagar uma multa por atraso dada por <strong>M<sub>i</sub> = w<sub>i</sub> × (C<sub>i</sub> − p<sub>i</sub>)</strong>. Essa multa é calculada como <strong>max(0, Valor Multa por Minuto × (Tempo de Conclusão − Prazo))</strong>, onde <strong>C<sub>i</sub></strong> representa o tempo de término do processamento do pedido <strong>i</strong> e <strong>w<sub>i</sub></strong> determina o valor da multa por minuto de atraso associado ao pedido <strong>i</strong>. O objetivo é determinar a sequência de processamento dos pedidos na linha de produção de maneira a garantir que todos sejam atendidos e que a soma das multas por atraso seja minimizada.
  </p>
  
  <h5>Instância</h5>
  <p>
      Para representar a instância do problema, consideramos os seguintes elementos:<br>
      - <strong>números_de_pedidos</strong>: quantidade total de pedidos a serem processados<br>
      - <strong>array_t</strong>: vetor que contém os tempos de processamento dos pedidos<br>
      - <strong>array_p</strong>: vetor que contém os prazos de conclusão dos pedidos<br>
      - <strong>array_w</strong>: vetor que indica a multa por atraso para cada pedido<br>
      - <strong>matriz_s</strong>: matriz que indica os tempos de preparação da linha (limpeza) entre os pedidos<br><br>
      Exemplo de instância:<br>
      - [5]                      número de pedidos<br>
      - [15, 25, 20, 30, 20]     tempos de fabricação<br>
      - [25, 45, 75, 120, 135]   prazos de fabricação<br>
      - [10, 12, 30, 15, 10]     multas por atraso em segundos<br><br>
      Matriz de limpeza:<br>
      <pre>
      [ 0  10 15  8 21
        10  0 10 13  9
        17  9  0 10 14 
        11 13 12  0 10
        5  10 15 20  0 ]
      </pre>
  </p>


  <h1> Etapas e Resoluções</h1>

  <h3> Algoritmo Guloso </h3>
  <p>
    Tomapm decisões baseadas em escolhas locais ótimas na esperança de que essas escolhas levem a uma solução global ótima. 
    Eles seguem o princípio da ganância (ou "greed"), fazendo a melhor escolha possível em cada etapa, sem reavaliar ou retroceder as decisões.  
  </p>

  <h4>Procedimento</h4>
  <p>
    1. s ← GeraSolucaoInicial(); # Aqui geramos uma solução inicial<br>
    2. Ordena os pedidos através da prioridade aplicada (ex: prazo ou tempo de processamento);<br>
    3. s' ← GeraNovaSolução(s); # Gera uma nova solução com base na prioridade dos pedidos<br>
    4. Retorna solução s';<br>
  </p>

  <h3>Variable Neighbourhood Descent (VND)</h3>
  <p>
    Método de busca local que explora o espaço de soluções por meio de trocas sistemáticas de vizinhança. O VND se baseia na ideia de que, ao alternar entre diferentes estruturas de vizinhança, é possível encontrar soluções melhores e evitar ficar preso em ótimos locais. Os movimentos de vizinhança implementados foram:
  </p>
  <ul>
    <li>
      <strong>Movimento Or-Opt:</strong> Este movimento envolve a remoção de um pedido de sua posição atual e a reinserção em uma nova posição, melhorando potencialmente a solução ao considerar diferentes sequências de pedidos.
    </li>
    <li>
      <strong>Movimento Swap:</strong> Neste movimento, dois pedidos são trocados de lugar na sequência. Esse tipo de movimentação pode ajudar a encontrar uma solução com menor custo, ajustando a ordem de processamento dos pedidos.
    </li>
    <li>
      <strong>Movimento 2-Opt:</strong> O movimento 2-Opt é uma técnica que remove dois segmentos da rota atual e os reconecta de uma maneira diferente, resultando em uma nova sequência que pode reduzir o custo total.
    </li>
    <li>
      <strong>Movimento Reinsertion:</strong> Esse movimento consiste em remover um pedido de sua posição e reinseri-lo em outra posição, permitindo ajustes na ordem de processamento que podem levar a melhorias significativas na solução.
    </li>
  </ul>

  <h4>Procedimento VND(f(.), N(.), r, s):</h4>
  <p><br>
  1. Seja k o número de estruturas diferentes de vizinhança;<br>
  2. k ← 1; {Tipo de estrutura de vizinhança corrente}<br>
  3. enquanto (k ≤ r) faça:<br> # Também pode ser while
  4. &nbsp;&nbsp; Encontre o melhor vizinho s' ∈ N(k)(s);<br>
  5. &nbsp;&nbsp; se (f(s') < f(s)) então<br>
  6. &nbsp;&nbsp;&nbsp;&nbsp; s ← s';<br>
  7. &nbsp;&nbsp;&nbsp;&nbsp; k ← 1;<br>
  8. &nbsp;&nbsp; senão<br>
  9. &nbsp;&nbsp;&nbsp;&nbsp; k ← k + 1;<br>
  10. &nbsp;&nbsp; fim-se;<br>
  11. fim-enquanto;<br>
  12. Retorne s;<br>
</p>



<h3>ILS (Iterated Local Search)</h3>
<p>
  A ILS (Iterated Local Search) é uma meta-heurística que se baseia na ideia de que um procedimento de busca local pode ser melhorado gerando novas soluções de partida. Essas novas soluções são obtidas por meio de perturbações na solução atual, permitindo uma exploração mais ampla do espaço de busca.
</p>
<p>
  O objetivo principal da ILS é evitar que o algoritmo fique preso em ótimos locais locais, os quais são comuns em métodos de busca local. Ao introduzir perturbações, a ILS facilita a busca por soluções melhores, permitindo que a busca local seja reiniciada a partir de uma nova solução, que pode ser significativamente diferente da anterior.
</p>
<h4>Procedimento ILS:</h4>

  <p> 
    <br>
    1. so GeraSolucaoInicial(); # Aqui foi usado o Guloso<br>
    2. s← Busca Local(so);      # Aqui foi usado o VND<br>
    3. enquanto (os critérios de parada não estiverem satisfeitos) faça<br>
    4. s' Perturbacao(histórico, s);<br>
    5. s" ← Busca Local(s');<br>
    6. s← CriterioAceitacao(s, s", histórico);<br>
    7. fim-enquanto;<br>
    fim ILS;
  </p>

  <h1>Instruções para Executar o Código</h1>
  
  <h2>Descrição</h2>
  <p>Este projeto contém implementações de algoritmos de otimização, incluindo o ILS (Iterated Local Search) e o VND (Variable Neighborhood Descent). As instâncias estão localizadas no diretório <strong>instancias</strong>, e o código pode ser compilado e executado para analisar diferentes instâncias.</p>
  
  <h2>Requisitos</h2>
  <ul>
      <li>gcc ou g++ (compilador C++)</li>
      <li>Make (ferramenta para automatizar o processo de compilação)</li>
  </ul>
  <h2>Compilação</h2>
  <p>Para compilar o projeto, acesse o diretório onde o <strong>Makefile</strong> está localizado e execute o seguinte comando:</p>
  <pre>make</pre>
  <p>Esse comando compilará todos os componentes necessários para o funcionamento do projeto.</p>

  <h2>Execução</h2>
  <p>Para iniciar a execução do algoritmo ILS com todas as instâncias disponíveis, utilize o seguinte comando:</p>
  <pre>make ils_all</pre>

  <p>Se você deseja executar o algoritmo ILS com uma instância específica, substitua <strong>n60A</strong> pelo nome da instância desejada e utilize o seguinte comando:</p>
  <pre>make ils_inst instancia=n60A</pre>

  <p>Adicionalmente, é possível executar apenas o VND. Para isso, você pode utilizar os seguintes comandos:</p>
  <ul>
      <li><strong>Executar todas as instâncias do VND:</strong></li>
      <pre>make vnd_all</pre>
      <li><strong>Executar uma instância específica do VND:</strong></li>
      <pre>make vnd_inst instancia=n60A</pre>
  </ul>
  <p>Certifique-se de substituir <strong>n60A</strong> pelo nome da instância desejada em ambos os comandos para garantir a execução correta.</p>



</div>
