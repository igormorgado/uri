#include <stdio.h>

#define MOD 1e9+7;

#define pb push_back
#define gcd(x,y) __gcd((x),(y))

typedef long long ll;
typedef long double ld;

// Multiply caring overflow
ll mulmod(ll a, ll b, ll m=MOD) {
  ll r=0;
  for (a %= m; b; b>>=1, a=(a*2)%m) if (b&1) r=(r+a)%m;
  return r;
}

// Fast exponential
ll fexp(ll a, ll b, ll m=MOD) {
  ll r=1;
  for (a %= m; b; b>>=1, a=(a*a)%m) if (b&1) r=(r*a)%m;
  return r;
}

// Miller-Rabin - Primarily Test
bool miller(ll n, ll a) {
  if (a >= n) return 1;
  ll s = 0, d = n-1;
  while (d%2 == 0 and d) d >>= 1, s++;
  ll x = fexp(a, d, n);
  if (x == 1 or x == n-1) return 1;
  for (int r = 0; r < s; r++, x = mulmod(x,x,n)) {
    if (x == 1) return 0;
    if (x == n-1) return 1;
  }
  return 0;
}

bool isprime(ll n) {
  int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  for (int i = 0; i < 12; ++i) if (!miller(n, base[i])) return 0;
  return 1;
}

// Pollard Rho - Integer factoring
ll pollard(ll n) {
  ll x, y, d, c=-1;
  if (n%2==0) return 2;
  while (1) {
    y = x = 2;
    while (1) {
      x = mulmod(x,x,n); x = (x-c)%n;
      y = mulmod(y,y,n); y = (y-c)%n;
      y = mulmod(y,y,n); y = (y-c)%n;
      d = gcd(abs(n+y-x), n);
      if (d == n) break;
      else if (d > 1) return d;
    }
    c--;
  }
}

void fator(ll n, vector<ll>& v) {
  if (isprime(n)) { v.pb(n); return; }
  ll f = pollard(n);
  fator(f, v); fator(n/f, v);
}

ll n;

int main() {
  while (scanf("%lld", &n) && n) {
    vector<ll> f;
    fator(n, f);
    assert(f.size() == 3);
    sort(f.begin(), f.end());
    printf("%lld = %lld x %lld x %lld\n", n, f[0], f[1], f[2]);
  }
  return 0;
}
