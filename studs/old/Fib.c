#include <stdio.h>
#include <stdlib.h>

//fibonacci = 1,1,2,3,5,8,13,...
 
int fib(int n, int * T) {
	//assume n>=1, retorna n-ésimo elemento de fibonacci
	if (T[n]==-1) {
		if (n<=2) {
			T[n] = 1;
		} else {	
			T[n] = (fib(n-1, T)+fib(n-2, T)) % 1000007;
		}
	}
	return T[n];
}
int main() {
	int n;
	int * T;
	scanf("%d", &n);
	T = (int *) malloc(sizeof(int)*(n+1));
	for (int i=0; i<=n; i++) {
		T[i] = -1;
	}
	printf("%d\n", fib(n, T));
	return 0;
}
