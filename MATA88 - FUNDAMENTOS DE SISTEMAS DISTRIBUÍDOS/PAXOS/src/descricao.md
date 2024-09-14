# Implementação Automatizada do Algoritmo Paxos com Comunicação por Sockets
## Arquitetura do Sistema
A arquitetura do sistema é composta pelos seguintes componentes principais:
1. **SocketMessenger**: Responsável pela comunicação entre os nós usando sockets UDP. Essa classe implementa a interface `Messenger` e fornece métodos para enviar e receber mensagens.
2. **SocketHeartbeatMessenger**: Estende o `SocketMessenger` e implementa a interface `HeartbeatMessenger`. Adiciona funcionalidades de envio de heartbeats e agendamento de tarefas.
3. **AutomatedPaxosNode**: Estende o `HeartbeatNode` e adiciona comportamento automatizado. Essa classe é responsável por ler os valores do arquivo compartilhado, propor valores e lidar com as mensagens recebidas.
4. **run_node**: Função que configura e executa um nó Paxos, incluindo a criação do `SocketHeartbeatMessenger` e do `AutomatedPaxosNode`.
5. **generate_shared_values**: Script separado que gera valores aleatórios e os grava em um arquivo compartilhado (`shared_values.txt`).
Os nós Paxos interagem entre si por meio do envio de mensagens usando o `SocketMessenger`. O nó líder (Node A) envia heartbeats regularmente e lida com as propostas recebidas dos outros nós. Os nós seguidores (Node B e Node C) leem os valores do arquivo compartilhado e os enviam como propostas.
## Explicação do Algoritmo
1. **Inicialização**: Quando um nó é executado, verifica se é o líder (Node A) ou um seguidor (Node B ou Node C). O líder começa imediatamente o processo de liderança, enquanto os seguidores aguardam a criação do arquivo compartilhado.
2. **Leitura de Valores Compartilhados**: Os nós seguidores monitoram a existência do arquivo `shared_values.txt` e, quando o arquivo é criado, leem os valores nele contidos.
3. **Proposição de Valores**: Após ler os valores do arquivo compartilhado, os nós seguidores começam a propor esses valores um por um, com um pequeno atraso entre cada proposta.
4. **Preparação e Aceite**: Quando um nó (líder ou seguidor) envia uma proposta, o processo Paxos é iniciado. O nó líder envia mensagens de "prepare" para todos os nós, enquanto os nós seguidores recebem essas mensagens e respondem com "promise" se a proposta tiver um número maior que a última proposta aceita.
5. **Alcance de Consenso**: Quando o nó líder recebe promessas de um quórum de nós, ele envia uma mensagem de "accept" para todos os nós. Os nós aceitam a proposta e enviam uma mensagem de "accepted" para informar o resultado.
6. **Liderança e Heartbeats**: O nó líder (Node A) envia heartbeats regularmente para indicar que ainda está ativo. Se os outros nós não receberem heartbeats por um determinado período, eles iniciarão o processo de aquisição de liderança.
## Justificativa das Escolhas de Projeto
1. **SocketMessenger e SocketHeartbeatMessenger**: Essas classes foram criadas para fornecer uma camada de comunicação por sockets, permitindo que os nós Paxos se comuniquem entre si. Isso facilita a execução dos nós em máquinas separadas e a replicação do sistema.
2. **AutomatedPaxosNode**: Essa classe estende o `HeartbeatNode` e adiciona comportamento automatizado, como a leitura dos valores compartilhados e a proposta desses valores. Isso simplifica a interação do usuário com o sistema, tornando-o mais autônomo.
3. **Arquivo Compartilhado**: O uso de um arquivo compartilhado (`shared_values.txt`) para armazenar os valores a serem propostos permite que os nós seguidores acessem as mesmas informações, sem a necessidade de uma etapa adicional de comunicação para distribuir esses valores.
4. **Estruturas de Dados**: O uso de dicionários e conjuntos (dictionaries e sets) para armazenar informações sobre propostas, promessas e aceitações é eficiente e permite uma fácil manipulação desses dados.
5. **Separação de Responsabilidades**: A divisão do sistema em diferentes componentes (SocketMessenger, SocketHeartbeatMessenger, AutomatedPaxosNode) segue o princípio da separação de responsabilidades, tornando o código mais modular, testável e fácil de manter.
## Instruções de Compilação e Execução
1. Certifique-se de ter o Python 3 instalado em sua máquina.
2. Salve o arquivo `paxos_implementation.py` em um diretório de sua escolha.
3. Salve o arquivo `generate_shared_values.py` no mesmo diretório.
4. Abra três terminais (ou janelas de prompt de comando) e navegue até o diretório onde os arquivos foram salvos.
5. No primeiro terminal, execute o script `generate_shared_values.py` para criar o arquivo `shared_values.txt`