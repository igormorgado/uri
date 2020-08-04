#include <stdio.h>
#include <stdlib.h>

void SubConj(int n, int pref[], int d) {
	//gerar todos os subconjuntos de 1 a n
	//sendo que os elementos 1 a d estão (ou não estão) no subconjunto
	//de acordo com pref[i] = V <==> i-ésimo está no subconjunto
	
	//nó do backtracking = elemento # 1 2 3 4 ... d ... n
	//						    pref[ S N N S ... N  ?  ? ] 

	if (d==n) {
		printf("{ ");
		for (int i=1;i<=n;i++) {
			if (pref[i] == 1) {
				printf("%d ", i);
			}
		}
		printf(" }\n");
	} else {
		pref[d+1] = 1;
		SubConj(n, pref, d+1);
		pref[d+1] = 0;
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
