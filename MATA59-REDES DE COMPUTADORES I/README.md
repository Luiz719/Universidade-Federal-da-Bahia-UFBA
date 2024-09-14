# Zeus Server
O Zeus Server utiliza conexão do tipo close, isto é: a cada requisição, uma nova conexão deve ser aberta.

Lista de Comandos:
```
SD:<password>:::             << Para desligar o servidor

GET:<username>:<filename>::  << Para obter o arquivo

PUT:<username>:<filename>:<file_length>:  << Para salvar um arquivo
<bytes>
...
<bytes>

LS:<username>:::             << Para listar os arquivos do cliente

DEL:<username>:<filename>::  << Para apagar um arquivo do cliente
```

O Zeus Server pode ser executado diretamente no script. Para tal, informe o seu endereço (IP, Port)
e o endereço do servidor listener (esta configuração é opcional), ao qual o Zeus Server irá dizer
informar a sua entrada e saída à rede. Atualmente o Zeus Server está configurado para receber 1024
bytes por vez, mas você pode alterar isso como preferir.

### Enviando e recebendo os dados de arquivo do Zeus Server:
Abaixo está um exemplo de transação para os comandos **PUT** e **GET** no Zeus Server:

```
Request:
PUT:Carlos Alberto:Sobremesa.png:20321193:
010101111011110101010101...
101101001111011101111011...
...
011111011110100001110110...

Response: NULL
```

```
Request:
GET:Carlos Alberto:Sobremesa.png:

Response:
20321193:
010101111011110101010101...
101101001111011101111011...
...
011111011110100001110110...
```
