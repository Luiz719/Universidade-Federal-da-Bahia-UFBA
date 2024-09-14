from random import SystemRandom
from kmp import KMPSearch

import matplotlib.pyplot as plt
import string

random = SystemRandom()


def gerar_alfabeto(k:int) -> list[str]:
    kmp_search = KMPSearch('Z')
    z = next(kmp_search.search(string.printable))
    
    caracteres = string.printable[:z[0]+1]
    return random.sample(caracteres, k)


def realizar_experimento() -> dict[int, dict[int, float]] :
    ks_valores:dict[int, dict[int, float]] = {}

    for k in (2, 4, 16, 32):
        texto = ''.join(random.choices(gerar_alfabeto(k), k=1000))
        pms_valores:dict[int, float] = {}

        for m in (2, 4, 6, 8, 10, 12, 14):
            pm = texto[-m:]
            
            kmp_search = KMPSearch(pm)
            pms_valores.setdefault(m, tuple(kmp_search.search(texto))[-1][1]/1000)
        
        ks_valores.setdefault(k, pms_valores)
    
    return ks_valores


experimento = realizar_experimento()
for _ in range(9):
    exp = realizar_experimento()
    for k in exp.keys():
        for m in exp[k].keys():
            experimento[k][m] += exp[k][m]

for k in experimento.keys():
    for m in experimento[k].keys():
        experimento[k][m] /= 10

cores = iter(("blue", "orange", "green", "red", "purple", "olive", "cyan", "brown", "pink", "gray"))

for k in experimento.keys():
    plt.plot(list(experimento[k].keys()), list(experimento[k].values()), color="tab:"+next(cores), label=str(k))

plt.title("Desempenho do algoritmo de busca em texto KMP")
plt.xlabel("Tamanho do padrão")
plt.ylabel("Nº de iterações por símbolo")
plt.legend(title="Tamanho do\nalfabeto", alignment="left")

from PIL import Image
from io import BytesIO

img_ = BytesIO()
plt.savefig(img_, dpi=300)
img = Image.open(img_)
img = img.crop((60, 70, 1770, img.height-10))
img.save("kmp_grafico.png")
