from argparse import ArgumentParser
from subprocess import Popen, PIPE
from random import SystemRandom
import sys, json, os


N = 10_000
N_EXP = 10
random = SystemRandom()


args_ = ArgumentParser(description="Realiza o experimento de inclusão")
args_.add_argument("-comp", help="Compila o arquivo main.c antes de realizar o experimento", action="store_true")
args_.add_argument("-delete", help="Apaga o executável gerado após a execução do experimento", action="store_true")
args = args_.parse_args()

if args.comp:
    if os.path.exists("main.exe"):
        os.remove("main.exe")

    cmp = Popen(["gcc", "main.c", "-o", "main.exe"], stdout=PIPE, stderr=PIPE, encoding="utf-8")
    if cmp.wait():
        print(f"Erro de compilação!\n\n{cmp.stderr.read()}", file=sys.stderr)
        exit(1)

exp = dict(S_alfa_medio=[0.0]*N, S_npags_medio=[0.0]*N, S_nmax_lista=[0]*N)

for _ in range(N_EXP):
    entrada = " ".join(map(str, random.sample(range(500_000), N))).encode("utf-8")
    teste = Popen(["main.exe"], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    saida, saida_erro = teste.communicate(entrada)
    saida = saida.rstrip().replace(b'\r', b'').decode('utf-8').split("\n")

    for i in range(N):
        ln = saida[i].split()
        exp['S_alfa_medio'][i] += float(ln[0])
        exp['S_npags_medio'][i] += float(ln[1])
        exp['S_nmax_lista'][i] += int(ln[2])
    

for key in exp.keys():
    for i in range(N):
        exp[key][i] /= N_EXP

with open("resultado.json", 'w') as j:
    json.dump(json.loads(json.dumps(exp), parse_float=lambda fs: round(float(fs), 4)), j)

if args.delete:
    os.remove("main.exe")