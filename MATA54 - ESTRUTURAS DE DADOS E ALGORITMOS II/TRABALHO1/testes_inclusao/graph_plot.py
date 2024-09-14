import matplotlib.pyplot as plt
import json

N = 10_000

with open("resultado.json", 'r') as j:
    exp = json.load(j)

x = list(range(1, N+1))

plt.plot(x, exp["S_npags_medio"], color="tab:blue", label="$p*$")
plt.plot(x, exp["S_nmax_lista"], color="tab:green", label="$L^{max}$")

plt.title("$p*$ e $L^{max}$ em função do n° de itens inseridos")
plt.xlabel("Número de Itens ($i$)")
plt.legend()

plt.savefig("grafico1.jpg", dpi=300)

plt.clf()
plt.plot(x, exp["S_alfa_medio"], color="tab:orange")
plt.title(r"$\alpha^{médio}$ em função do n° de itens inseridos")
plt.xlabel("Número de itens ($i$)")
plt.ylabel(r"$\alpha^{médio}$")

plt.savefig("grafico2.jpg", dpi=300)