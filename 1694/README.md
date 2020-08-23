 URI Online Judge | 1694
Loteria

Por VC++, Colégio Etapa BR Brazil
Timelimit: 4

Pinkie Pie está se sentindo com sorte. Ela está indo para a lotérica de sua cidade para fazer uma aposta e tentar a sorte.

O bilhete da aposta consiste em uma matriz de N linhas por M colunas. As casas são numeradas de 0 a N*M-1 de forma que o número da casa da r-ésima linha e c-ésima coluna (indexadas a partir do 0) é r * M + c. Uma aposta consiste em escolher K números distintos dentre os disponíveis.

Pinkie pressente que os números vencedores estarão próximos uns aos outros, então ela decide escolher números que estão ou todos na mesma linha ou todos na mesma coluna. Pinkie também acredita que números primos trazem má sorte, e não fará nenhuma aposta que contém ao menos um número primo.

Twilight passou em frente à lotéria e encontrou Pinkie incapaz de chegar a uma decisão. Querendo testar suas habilidades matemáticas, ela decidiu, enquanto Pinkie fazia sua escolha, calcular quantas apostas diferentes Pinkie Pie poderia fazer. Duas apostas são consideradas distintas se existe um elemento presente em uma aposta e ausente na outra.
Entrada

Existem diversos casos testes. Cada caso de teste consiste de uma única linha contendo três inteiros N, M e K (1 ≤ N, M ≤ 50; 1 ≤ K ≤ 10). O último caso de teste é seguido de uma linha contendo três zeros.
Saída

Para cada caso de teste, imprima uma única linha contendo o número de apostas diferentes que Pinkie Pie pode fazer, de forma que os números estejam todos ou na mesma linha ou na mesma coluna, e que nenhum número primo seja escolhido. Um número primo é um número natural maior que 1 que não possui divisores positivos além de 1 e si mesmo.

# DICAS

