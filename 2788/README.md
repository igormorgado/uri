# Dicas

Soma de modulares...

Sempre tem uma solucao com 17 digitos (long long int serve)

Sempre tem solucao


2:22:00
Seja  xxxyyyyyyyxxx uma solucao (menor multiplode M)

xxxyyyyyyxxxx % M == 0
xxx000000xxxx % M != 0 (provavelmente)

Onde  yyyyyy contem N (o numero a ser extendido).

yyyyyy % M e' o complemento de xxxx000000xxx % M para xxxxyyyyyxxx % M = 0

ou seja, invm - 1.

Entao yyyyy e' o menor numero que contem N cujo resto da divisao por N seja
yyyyy mod N.


# Algo (por alto)

comeca com N 

adiciona digitos a direita e a esquerda guardando os minimos.

Tem duas estruturas:

R vetor que guarda o resto da divisao tem tamanho  M
F uma fila


N = 6, M = 4


Pego o N, e coloco na fila, 


// Coloca elemento na fila
pushfila(N);

// Processa fila:
n = popfila()

idx = n % M 
R[idx]  = n

// Terminou processamento de tamanho 1. Como nao tem solucao vamos procurar
tamanho 2. Adicionando elementos ao final e ao inicio de N.

Adiciona todos os digitos possiveis a direita e a esquerda de N e enfilera cada
um deles na fila...

Ou seja fila nunca eh maior que 9+ 10 + 1 (para redundancia) 20...

Procesa fila..

Vai armazenando os elementos nos indices de  idx =  popfila % M;

ao armazenar verifica se o elemento (n) 'e menor do que o que esta la, se nao
for, nem coloca.. pq eh maior e la ja tem uma solucao menor.

2:37:00

Fila.. tamanho de 20*R

Fila de tamanho 4.000.000

