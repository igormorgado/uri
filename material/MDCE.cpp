//Obtem o MDC estendido de 2 números. Dados a e b, encontra, d (mdc de a e b) e
// também x e y, satisfazendo a.x + b.y = d
#include <iostream>
#include <math.h>
using namespace std;

typedef struct ret { int d; int x; int y;};
int a, b; ret r;

int MDC(int a, int b)
{   if (b == 0) return a;
    else return MDC(b, a % b);
}
ret MDCE(int a, int b, ret ra)
{   int xx;
    if (b == 0)
    {   ra.d = a;  ra.x = 1;  ra.y = 0;
    }
    else
    {   ra = MDCE(b, a % b, ra);
        xx = ra.x;  ra.x = ra.y;  ra.y = xx - (a / b)*ra.y;
    }    
    cout << "a = " << a <<" b = "<< b << " d = " << ra.d << " x = " << ra.x <<" y = " <<ra.y
          << "  " << a << "." << ra.x << " + " << b << "." << ra.y << " = " << ra.d << endl;
    return ra;          
}

int main()
{    while (1)
    {   cout << "informe a e b: ";
        cin >> a >> b;
        if ((!a) || (!b)) break;
        r.d = MDC(a, b);
        cout << "MDC = " <<r.d << endl;
        r = MDCE(a, b, r);
        cout << "MDC = " << r.d << " x = " << r.x << " y = " << r.y << endl << endl;
    }
}
