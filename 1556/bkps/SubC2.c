#include <stdio.h>
#include <stdlib.h>

void SubConj(int n, int pref[], int d) {
    //gerar todos os subconjuntos de 1 a n
    //que contenham os elementos pref[1..d]

    printf("{ ");
    for (int i=1;i<=d;i++) {
        printf("%d ", pref[i]);
    }
    printf(" }\n");

    for (int e = (d==0 ? 1 : pref[d]+1); e<=n; e++) {
        pref[d+1] = e;
        SubConj(n, pref, d+1);
    }

}

int main() {
    int n;
    scanf("%d", &n);
    int pref[n+1];
    SubConj(n, pref, 0);
    return 0;
}
