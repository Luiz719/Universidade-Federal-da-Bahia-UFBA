from typing import Generator


def comparar_strings(str1:str, str2:str) -> tuple[bool, int]:
    if len(str1) != len(str2):
        return (False, 0)
    
    c = 0
    for c1, c2 in zip(str1, str2):
        c += 1
        if c1 != c2:
            return (False, c)
    
    return (True, c)


def rk_match(texto:str, padrao:str) -> Generator[tuple[int, int], None, None]:
    Q = 7919            #Módulo para o hash (preferencialmente primo)
    B = 10              #Base numérica

    m = len(padrao)     #Tamanho do texto
    n = len(texto)      #Tamanho do padrão
    w = pow(B, m-1, Q)  #B^{m-1} mod Q
    vt = 0              #Hash do texto (atualizável)
    vp = 0              #Hash do padrão
    s = 0               #Posição da busca

    for pi, ti in zip(padrao, texto):
        vp = (vp*B+ord(pi))%Q
        vt = (vt*B+ord(ti))%Q
    
    iteracoes = m
    while s <= n-m:
        iteracoes += 1

        if (vp == vt):
            comp, it = comparar_strings(padrao, texto[s:s+m])
            iteracoes += it
            if comp:
                yield (s, iteracoes)
        
        s += 1
        
        if s <= n-m:
            vt = (B*(vt-ord(texto[s-1])*w)+ord(texto[s+m-1]))%Q