ASIZE = 256

def make_delta1(P):
    m = len(P)
    delta1 = [m for _ in range(ASIZE)]
    for i in range(m - 1):
        delta1[ord(P[i])] = m - i - 1
    return delta1

def unify(P, a, b, m, out_p):
    it = 0
    for i in range(m+1):
        it += 1
        if P[a + i] != P[b + i] and out_p <= 0:
            return (False, it)
        out_p -= 1
    return (True, it)

def rpr(P, j):
    m = int(len(P)/2)
    k = m + j - 1
    it = 0
    while k > 1:
        it += 1
        if(P[j+m-1] != P[k-1] or k <= m):
            out_p = m - k
            unified, iterations = unify(P, j + m, k, m - (j + 1), out_p)
            if unified:
                break
        k -= 1
    return (k-m+1, it)

def make_delta2(P):
    m = len(P)
    P2 = P * 2
    delta2 = [1] * (m+1)
    it = 0
    for i in range(1, m):
        it += 1
        nrpr, c = rpr(P2, i)
        it += c
        delta2[i] = m + 1 - nrpr

    return (delta2, it)


def bm_match(T, P, alph_size):

    m, n = len(P), len(T)

    # Preprocessamento
    delta1 = make_delta1(P)
    iteracoes = alph_size + m - 1 #delta 1
    delta2, it = make_delta2(P)
    iteracoes += it

    # Busca
    i = m - 1
    
    while i < n:
        # Pesquisa
        k = i
        j = m - 1
        if T[k] != P[j]:
            iteracoes+=1
        else:
            while j >= 0 and T[k] == P[j]:
                iteracoes+=1
                j -= 1
                k -= 1

        if j < 0:
            yield (k+1, iteracoes)
            i += max(delta2[j+1], delta1[ord(T[k])])           
        else:   
            k += max(delta2[j+1], delta1[ord(T[k])])
            i = k

# Exemplo de uso
if __name__ == "__main__":
    P = "abcabc"
    T = "ababcababcabcabc"
    bm_match(T, P, 10)
