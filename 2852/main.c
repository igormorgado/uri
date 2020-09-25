#include <string.h>
#include <stdio.h>

int main(void) {
    char K[47];
    scanf("%s\n", K);
    size_t Ksz = strlen(K);

    int N;
    scanf("%d\n", &N);

    const int Asz = 26;             /* Alphabet size */
    char P[100000];
    for(size_t i = 0; i < N; ++i)
    {
        //scanf("%100000[^\n]", line);
        fgets(P, sizeof P, stdin);
        size_t Psz = strlen(P);
        P[Psz-1]='\0';     // Remove newline.
        Psz -= 1;          // Do not count the removed new line

        // printf("%zu %s %s\n", i, K, P);

        int vowel_word = 0;
        int new_word = 1;
        int new_line = 1;
        int c = 0;
        int k = 0;
        char C;
        char L;
        size_t j = 0;               // Crypt counter
        for(size_t i =0; i < Psz; ++i)
        {
            if (P[i] == ' ')
            {
                // putchar('\n');
                if (L != ' ' && new_line == 0 && P[i+1] != '\0') putchar(' ');
                new_word = 1;
                L = P[i];
                continue;
            }
            new_line = 0;

            if (new_word == 1)
            {
                new_word = 0;
                if (P[i] == 'a' || P[i] == 'e' || P[i] == 'i' || P[i] == 'o' || P[i] == 'u')
                {
                    vowel_word = 1;
                }
                else
                {
                    vowel_word = 0;
                }
            }

            if (vowel_word == 1)
            {
                C = P[i];
            }
            else
            {
                c = P[i] - 'a';
                k = K[j % Ksz] - 'a';
                C = (c + k) % Asz;
                C += 'a';
                j++;
            }
            L = P[i];
            putchar(C);
        }
        putchar('\n');
    }
    return 0;
}
