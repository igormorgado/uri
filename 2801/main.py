def E(L, N, A, B):
    return ((((L % N) * (A % N)) % N) + (B % N)) % N

def gcd(x, y):
   while(y): x, y = y, x % y
   return x

MSZ = int(input());
M = list(map(int, input().split(" ")))
N, A, B = map(int, input().split(" "))
if (gcd(N, A) == 1):
    for L in M[:-1]:
        print("{} ".format(E(L, N, A, B)), end='')
    print("{}".format(E(M[-1], N, A, B)))
else:
    print("DECIFRAGEM AMBIGUA")

