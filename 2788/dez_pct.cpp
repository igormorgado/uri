#include<bits/stdc++.h>

using namespace std;

int counter(unsigned long long x){
    int ans = 0;
    while(x > 0){
        ans++;
        x/=10;
    }
    return ans;
}

int main(){
    priority_queue<unsigned long long, vector<unsigned long long>, greater<unsigned long long> > fila;
    unsigned long long n, m;
    scanf("%llu%llu",&n,&m);
    fila.push(n);
    while(!fila.empty()){
        unsigned long long u = fila.top();
        fila.pop();

        int dig = counter(u);

        //cout << u << " = " << dig << '\n';

        if(u % m == 0){
            printf("%llu\n",u);
            return 0;
        }

        if(dig == 18) continue;

        unsigned long long v = u * 10;

        fila.push(v);

        for(unsigned long long i=1;i<=9;i++) fila.push((v+i));

        for(unsigned long long i=1;i<=9;i++) fila.push(((i*pow(10,dig))+u));
    }
    return 0;
}
