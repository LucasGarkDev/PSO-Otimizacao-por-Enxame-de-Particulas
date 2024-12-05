# PSO-Otimizacao-por-Enxame-de-Particulas
Utilize um algoritmo de otimização por enxame de partículas para minimizar a função descrita pela equação abaixo, função Eggholder function, que é uma função clássica na condução de testes para otimização de funções. Bidimensional e apresentando vários mínimos locais, essa função alcança o mínimo global em: Minimize a função (Eggholder function)

Algoritmo: Pseudocódigo do PSO.

1. Determine o número de partículas P da população.
   
2. Inicialize aleatoriamente a posição inicial (x) de cada partícula p de P.
   
3. Atribua uma velocidade inicial (v) igual para todas as partículas.
   
4. Para cada partícula p em P faça:
 (a) Calcule sua aptidão fp = f (p).
(b) Calcule a melhor posição da partícula p até o momento (pΒ).

6. Descubra a partícula com a melhor aptidão de toda a população (gΒ).
   
7. Para cada partícula p em P faça:
(a) Atualize a velocidade da partícula pela fórmula:

vi
(t +1)=W∗vi
(t)+ϕ1∗rand1
(.)∗( pB−xi
(t))+ϕ2∗rand2
( gB−xi
(t))

(b) Atualize a posição da particular pela fórmula:

x (t 1)  x (t) v (t 1)

7. Se condição de término não for alcançada, retorne ao passo 4.

Observações:

• Para limitar a velocidade de uma partícula para que o sistema não extrapole o
espaço de busca, são impostos limites (vmax) para seus valores em cada dimensão
(d) do espaço de busca:

• No algoritmo, as velocidades iniciais devem ser geradas aleatoriamente, com valores
limitados a 15% do espaço de busca de cada parâmetro (~[-77, +77]).

• Assumir como intervalo x∈[−512,+512] e y∈[−512,+512]

• Em relação aos valores máximos da partícula, caso este saia do intervalo das variáveis, eles
deverão ser corrigidos para o máximo ou mínimo do intervalo [-512, +512], e a velocidade
setada em 0.

• O critério de parada será o número de iterações (20, 50 e 100 iterações).

• Considere o tamanho da população como 50 e 100 indivíduos.

• A escolha dos parâmetros do algoritmo evolutivo (setup) faz parte do trabalho. Por favor,
use valores conforme recomendado na literatura (estado da arte).

• Faça uma análise estatística dos resultados obtidos para 10 execuções, descrevendo numa
tabela o melhor, a média dos resultados e o desvio padrão.

• Plote os gráficos da curva com os dados obtidos (melhor resultado e média) para cada
número de iterações (20, 50 e 100).

• Escreva um relatório sobre os resultados obtidos (análise) e a eficácia do algoritmo. A
entrega do código fonte é obrigatória.
