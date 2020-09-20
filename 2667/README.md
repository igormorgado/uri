# Dicas

1:47:00

Se N inicial for um multiplo de 3 ganha o segundo jogador

O problema se reduz em retornar N % 3


Ler o numero grande como string e processa com mod 3

u64 n = 3;
char N[] = "123141....131233";
u64 m = 0;
u64 N_sz = strlen(N);
for (size_t i = N; i >=0; --i)
    m = ( 10*m + atoi(N[i]) ) % n;
return m;


