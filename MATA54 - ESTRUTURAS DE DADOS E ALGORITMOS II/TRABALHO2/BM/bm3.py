def unify(P, a, b, m, out_p):
    for i in range(m+1):
        if P[a + i] != P[b + i] and out_p <= 0:
            return False
        out_p -= 1
    return True

def rpr(P, j):
    m = int(len(P)/2)
    k = m + j - 1
    while k > 1:
        a = m - (j + 1)
        if(P[j+m-1] != P[k-1] or k <= m):
            out_p = m - k
            if unify(P, j + m, k, m - (j + 1), out_p):
                break
        k -= 1
    return k-m+1

def make_delta2(P):
    m = len(P)
    P2 = P * 2
    delta2 = [1] * (m+1)
    for i in range(1, m):
        delta2[i] = m + 1 - rpr(P2, i)
    return delta2

# Exemplo de uso
if __name__ == "__main__":
    P = "a a b a b b a a".replace(" ", "")
    m = len(P)
    delta2 = make_delta2(P)

    print("Delta2 table:", delta2)

