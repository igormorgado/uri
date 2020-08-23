//Testa primalidade, fatora e mostra divisores de números entre 10^7 e 10^15
#include <iostream>
#include <math.h>
using namespace std;

int C[31700000], P[4000001], rq, nf, np, nd;
long long int n, q, F[50], D[10000];
bool teste;

void GeraCrivo (int n)
{    int i, rq, t, d;
     for (i=1; i<=n; i++)   C[i] = i;
     for (i=2; i<=n; i+=2)  C[i] = 2;
     rq = sqrt(n);
     for (i=3; i<=rq; i+=2)
     {   if (C[i] == i)
         {   t = i*i;  d = i+i;
             while(t<=n)
             {   if (C[t] == t) C[t] = i;
                 t = t+d;
             }
         }
     }
}
void GeraPrimos (int rq)
{    np=0;
     for (int i=2; i<=rq; i++)
         if (C[i]==i)  P[++np]= i;
}

bool TestaPrimo (long long int q)
{    bool primo = true;
     for (int i=1; i<=np; i++)
     {   if ((q % P[i]) == 0)
         {   if (q != P[i]) primo = false;
             break;
         }
     }
     return (primo);
}

void Fatora (long long int q)
{    int rq = sqrt(q)+1;
	 nf = 0;
     for (int i=1; i<=np; i++)
     //for (int i=1; P[i]<=rq; i++)
     {   while((q % P[i]) == 0)
         {   F[++nf] = P[i];  q = q/P[i];
         }
         if (q == 1) break;
     }
     if (q != 1) F[++nf] = q;
}

void Divisores(long long int q)
{    int nda;long long int k;
     F[0] = 1;  nd = 1;  D[1] = 1;  nda = 1;
     for (int i=1; i<=nf; i++)
     {   if (F[i] == F[i-1]) k = k*F[i];
         else
         {    nda = nd;  k = F[i];
         }
         for (int j=1; j<=nda; j++)
             D[++nd] = k*D[j];
     }
}

int main()
{   //número máximo que pode ser testado - até 1.000.000.000.000.000
    n = 1000000000000000;
    rq = sqrt(n)+1;
    GeraCrivo(rq);
    GeraPrimos(rq);
    cout << "np = " << np << endl << endl;
    while(1)
    {   cout << "q = ";  cin >> q;
        if(!q) break;
        teste = TestaPrimo(q);
        if (teste)  cout << q << " eh primo"     <<endl <<endl;
        else        cout << q << " nao eh primo" <<endl <<endl;
        Fatora(q);
        cout << "nf = " << nf <<endl << "Fatores: ";
        for (int i=1; i<=nf; i++) cout << F[i] << " ";  cout << endl << endl;
        Divisores(q);
        cout << "nd = " << nd <<endl << "Divisores: ";
        for (int i=1; i<=nd; i++) cout << D[i] << " ";  cout << endl <<endl <<endl;
    }
    return 0;
}







