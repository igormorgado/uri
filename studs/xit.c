#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {double x, y;}Vec2;

int SentidoPercurso(Vec2 p1, Vec2 p2, Vec2 p3)
{  long long a, b, c, d;
    a= p2.x - p1.x;  b= p3.y - p1.y;  c=p3.x - p1.x;  d=p2.y - p1.y;
    a = a*b-c*d;
    if (a > 0) return 1;
    else if (a < 0) return -1;
    else return 0;
}


void Quicksort(Vec2 *pol, int e, int d)
    // O ponto 0 fica fixo na ordenação, pois tem o menor x
{  int i,j,k;  Vec2 t,r;  long long d0, d1, d2;
    if (d > e)
    {  i=e;  j=d;  t=pol[(e+d)/2];
        d1= pol[0].x-t.x;  d2= pol[0].y-t.y;  d0=d1*d1+d2*d2;
        while(i<=j)
        {  while(1)
            {  k=SentidoPercurso(pol[0],pol[i],t);
                if (k==1) i++;
                else if (k==0)
                {  d1= pol[0].x-pol[i].x;  d2= pol[0].y-pol[i].y;  d1= d1*d1+d2*d2;
                    if (d1 < d0) i++;
                    else break;
                }
                else break;
            }
            while(1)
            {  k=SentidoPercurso(pol[0],t,pol[j]);
                if (k==1) j--;
                else if (k==0)
                {  d1= pol[0].x-pol[j].x;  d2= pol[0].y-pol[j].y;  d1= d1*d1+d2*d2;
                    if (d0 < d1) j--;
                    else break;
                }
                else break;
            }
            if (i<=j) {r=pol[i];  pol[i]=pol[j];  pol[j]=r;  i++; j--;}
        }
        Quicksort(pol, e,j);  Quicksort(pol, i,d);
    }
}

void OrdenaPontosy(Vec2 *pol, int tp)
    /*   Ordena pontos por ângulo, escolhendo como referência o ponto mais embaixo e mais
         à esquerda. */
{
    int i, m;
    Vec2 p;

    m=0;
    for ( i=1;i<tp;i++)
        if ((pol[i].y < pol[m].y)||(pol[i].y==pol[m].y)&&(pol[i].x<pol[m].x)) m=i;
    p=pol[0];  pol[0]=pol[m];  pol[m]=p;
    Quicksort(pol, 1,tp-1);
}

size_t ConvexHull(Vec2 * pol, size_t tp, Vec2 *ch, size_t *tc)
{
    OrdenaPontosy(pol, tp);
    /*Repete o ponto inicial no final*/
    ch[0]= pol[0];
    pol[tp]= pol[0];


    size_t j = 1;
    /* Elimina pontos iniciais colineares */
    while (SentidoPercurso(ch[0],pol[j],pol[j+1])==0) j++;
    ch[1]= pol[j];
    ch[2]= pol[j+1];
    size_t topo  = 2;
    for (size_t i = j+2; i<= tp; i++)
    {   while (SentidoPercurso(ch[topo-1], ch[topo], pol[i]) <= 0) topo--;
        topo++;  ch[topo]= pol[i];
    }
    *tc = topo;
    return (topo);
}


int main()
{
    Vec2 s[7] = {
        {3,6},
        {8,4},
        {5,4},
        {4,3},
        {5,2},
        {1,2},
        {6,1}
    };

    Vec2 cvxhl[7] = {0};
    size_t n = 0;
    ConvexHull(s, 7, cvxhl, &n);

    printf("Expecting: {6,1}, {8,4}, {3,6}, {1,2}\n");
     for(size_t i = 0; i < n; ++i)
        printf("%zu: (%.1f, %.1f)\n", i, cvxhl[i].x, cvxhl[i].y);
    return 0;
    return 0;
}

