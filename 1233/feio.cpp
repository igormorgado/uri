
#include <bits/stdc++.h>
using namespace std;
long long int phi(long long int n){
    long long int result = n;
    for (long long int p=2; p*p<=n; ++p){
        if (n % p == 0){
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main(int argc, char const *argv[]) {
  long long int n;
  while (cin>>n) {
    cout<<phi(n)/2<<endl;
  }
  return 0;
}
