//Testa primalidade, fatora e mostra divisores de números <= 10000
#include <iostream>
#include <math.h>
using namespace std;

int F[50], D[1000], q, nf, nd;
bool teste;

bool TestaPrimo (int q)
{    int rq;   bool primo=true;
     rq = sqrt(q);
     for (int i=2; i<=rq; i++)
         if ((q % i) == 0)
         {   primo = false;
             break;
         }    
     return (primo);
}

void Fatora (int q)
{    int rq;
     nf = 0;  rq = sqrt(q);
     if (rq*rq < q) rq++;
     for (int i=2; i<=rq; i++)
     {   while((q % i) == 0)
         {   F[++nf] = i;  q = q/i;
         }
     }
     if (q > 1) F[++nf] = q;
}

void Divisores(int q)
{    int rq;
     rq = sqrt(q);  nd = 0;
     for (int i=1; i<=rq; i++)
     {   if ((q % i) == 0)
         {   D[++nd] = i;  D[++nd] = q/i;
         }
     }
     if (rq*rq == q) nd--;
}

int main()
{   //número máximo que deve ser testado = 10.000
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



         



