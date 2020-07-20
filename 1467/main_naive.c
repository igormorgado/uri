#include <stdio.h>

int main(void) { 
    int A, B, C;

    while(scanf("%d %d %d\n", &A, &B, &C) != EOF)
    {
        if( (A == B) && (A != C) )
            printf("C\n");
        else if ( (A == C) && (A != B) )
            printf("B\n");
        else if ( (A != B) && (A != C) )
            printf("A\n");
        else
            printf("*\n");
    }

    return 0;
}
    
