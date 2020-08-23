 URI Online Judge | 1568
{soma+=i++} até N

Por Shahriar Manzoor, SEU BD Bangladesh
Timelimit: 3
Todos os números positivos podem ser expressos como a soma de um, dois ou mais números inteiros positivos consecutivos. Por exemplo, 9 pode ser expresso em três diferentes formas, 2+3+4, 4+5 ou 9. Dado um número inteiro menor que (9*10^14+1) ou (9E14 + 1) ou (9*10¹⁴ +1), você terá que determinar de quantas maneiras este número pode ser expresso como a soma de números consecutivos.
Entrada

O arquivo de entrada contém menos de 1100 linhas de entrada (casos de teste). Cada caso de teste contém um inteiro N (0 ≤ N ≤ 9E14) . O final de entrada é determinado por EOF.
Saída

Para cada caso de teste produza uma linha de saída. Esta linha deverá conter um inteiro que informa de quantas maneiras N pode ser expresso como a soma de inteiros consecutivos.



# Dicas

1 desenvolvero problema algebricamente

N = (a+1)+...+(a+k) = (a+k)(a+k+1)/2 - a(a+1)/2 = k (2a+k+1)/2

N impar -> k (impar) divisor de N é solucao

N par -> k par nao faz sentido
         k tem que ser impar. Divisor de N?

         Problema sao os divisores / devem ser fatorados


