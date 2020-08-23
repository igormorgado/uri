 URI Online Judge | 2892
Treino No Velódromo

Por Paulo E. D. Pinto, UERJ-Universidade do Estado do Rio de Janeiro BR Brazil
Timelimit: 1

Três ciclistas estão treinando no velódromo para a próxima Olimpíada.  Eles dão a partida juntos e fazem milhares de voltas a cada dia, de forma regular. Cada um leva dado tempo para completar a volta e corre sempre com a mesma velocidade.
O técnico anotou o tempo de uma volta para os dois primeiros ciclistas e só sabe, em relação ao terceiro o tempo que leva para os três se alinharem novamente na linha de partida.

Você vai ajudar o técnico calculando todos os possíveis tempos que o terceiro ciclista leva para uma volta.
Entrada

Cada entrada contém três inteiros: T,  1 ≤  T ≤  106, o tempo que os ciclistas levam para se encontrar novamente na linha de partida,   A, B,  1 ≤  A, B ≤  102, os tempos respectivos que os ciclistas 1 e 2 levam para dar uma volta. A entrada termina com 0 0 0, que não devem ser processados.
Saída

Para cada entrada, imprimir, de forma ordenada, os possíveis tempos que o terceiro ciclista leva para completar uma volta, de forma a ocorrer a coincidência mencionada.

MMC inverse



# DICAS

T = MMC(A,B, C) = MMC(MMC(A,B), C)

T = ( A * B / D ) * C / E --> C é divisor de T.

C é o que se quer encontrar.


