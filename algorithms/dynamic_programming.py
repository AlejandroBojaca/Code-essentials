#memoization
def fibonacci(n, precomputed={}):
    if n == 0:
        return 0
    if n == 1:
        return 1
    if n not in precomputed:
        precomputed[n] = fibonacci(n - 1, precomputed) + fibonacci(n - 2, precomputed)
    return precomputed[n]

#tabulation
def fibonacci(n):
    f = [None] * (n + 1)
    f[0] = 0
    if n > 0:
        f[1] = 1
    for i in range(2, n + 1):
        f[i] = f[i - 2] + f[i - 1]
    return f[n]

