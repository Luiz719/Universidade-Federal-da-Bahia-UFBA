def compute_prefix_function(Q):
    P = Q[::-1]
    m = len(P)
    π = [0] * (m + 1)
    q = 0

    for i in range(2, m + 1):
        while q > 0 and P[q] != P[i - 1]:
            q = π[q]

        if P[q] == P[i - 1]:
            q += 1

        π[i] = q

    return π

# Exemplo de uso
if __name__ == "__main__":
    pattern = "a b c a b c a c a b".replace(" ", "")
    prefix_array = compute_prefix_function(pattern)
    print("Prefix Array:", prefix_array)
