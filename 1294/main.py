import numpy as np
import matplotlib.pyplot as plt

sizes = np.array([[ 1.0, 1.0 ],
                  [ 2.0, 2.0 ],
                  [ 3.0, 3.0 ]])

def f(x, w, h):
    return (4.0 * x * x * x) - (2.0 * w * x * x) - (2.0 * h * x * x) + (w * h * x)

def df(x, w, h):
    return (12.0 * x * x) - (4.0 * w * x)     - (4.0 * h * x)     + (w * h);

def ddf(x, w, h):
    return (24.0 * x) - (4.0 * w) - (4.0 * h);

def newton(x0, w, h, n):
    x = x0;
    for i in range(n):
        x -= df(x, w, h) / ddf(x, w, h)
    return x

def solve_poly_two(a, b, c):
    delta = b*b - 4.0 * a * c;
    if delta < 0: 
        print("COMPLEXO")
    x0 = (-b + np.sqrt(delta))/(2.0*a);
    x1 = (-b - np.sqrt(delta))/(2.0*a);
    return x0, x1;


for W, H in sizes:
    a = 12.0;
    b = -4.0 * (W + H)
    c = W * H
    vertex = -b / (2*a)
    x = np.linspace(0, min(W, H)/2, 101)

    fig, ax = plt.subplots(1,1)
    ax.plot(x, f(x, W, H), label=f"f(x, {W}, {H})")
    ax.plot(x, df(x, W, H), label=f"df(x, {W}, {H})")
    ax.vlines(vertex, min(min(f(x,W,H)), min(df(x,W,H))), max( max(f(x,W,H)), max(df(x,W,H))), colors='red')
    ax.legend()
    ax.set_xlabel("x")
    ax.set_ylabel("V(x, W, H)")
    ax.set_xlim([0, min(W,H)/2])
    ax.grid(True)
    fig.suptitle(f"W: {W}, H: {H}")
    
    
    
    # x0, x1 = solve_poly_two(a, b, c);
    # fmt = "W: {:7.3f} H: {:7.3f} x0: {:7.3f} x1: {:7.3f}  df(x0): {:7.3f} df(x1): {:7.3f} f(x0): {:7.3f} f(x1): {:7.3f}"
    # print (fmt.format(W, H, x0, x1, df(x0, W, H), df(x1, W, H), f(x0, W, H), f(x1, W, H)));
    # // double x = newton((W+H)/8.0, W, H, 10);
    # // printf("%.3f 0.000 %.3f\n", f(x, W, H), (W+H)/4.0);
