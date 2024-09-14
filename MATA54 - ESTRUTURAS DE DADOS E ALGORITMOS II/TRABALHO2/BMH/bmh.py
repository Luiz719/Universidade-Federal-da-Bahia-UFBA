import string
from typing import Generator
from random import SystemRandom

random = SystemRandom()

def bmh_match(T: str, P: str, alph_size: int)-> Generator[tuple[int, int], None, None]:
    maxChar = 256 
    n = len(T)
    m = len(P)

    # Pré-processamento do padrão
    print(P)
    d = [m] * maxChar
    for j in range(m - 1):
        d[ord(P[j])] = m - j - 1

    i = m - 1
    iteracoes = alph_size + m - 1
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
            print(k+1, iteracoes)

        i = i + d[ord(T[i])]

# Exemplo de uso
if __name__ == "__main__":
    texto = "a a b a a b b a c b a c".replace(" ","")
    padrao = "c a c b a c".replace(" ","")
    caracteres = string.printable[:61+1]
    a = random.sample(caracteres, 32)
    T = ''.join(random.choices(a, k=1000))
    P = T[-6:]
    bmh_match(T, P, 2)
