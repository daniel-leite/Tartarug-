# Tartarugæ

Este repositório conterá todo o código relativo à **Mademoiselle Coralinæ Turtle Jones**, ou _coralina-turtle_ para os mais íntimos.

Mais íntimos:
* Daniel Leite Ribeiro
* Josué Henrique de Freitas Andrade
* Pedro Blanc Árabe


## Software do Arduíno

O firmware da Coralinæ será dividido em um arquivo _.ino_ principal, um arquivo _.h_ de configuração e vários arquivos _.cpp_ para lidar com as subtarefas mais importantes, tais como
* Malhas de controle
* Sequenciamento de ações (estratégia)
* Processamento dos infravermelhos
* Odometria
* Comunicação serial

O código conta, ainda, com bibliotecas situadas no diretório _lib_ que devem ser copiadas para a pasta _libraries_ do computador. Sugere-se que se façam links simbólicos em vez de cópias, para que a versão utilizada das bibliotecas sempre seja a mais recente.

## Interface 

Mlle. Jones se comunicará via bluetooth com o computador utilizando um protocolo de mensagens simples, trocadas entre o Arduíno e uma interface gráfica feita no Qt (em C++ ou PyQt4). A interface será capaz de exibir:
* Perfil dos sensores atualmente ativados
* Posição do robô em relação à linha
* Obstáculos/desafios encontrados
* Ação atual (estratégia)
* Status de erro
* Velocidade de cada motor, bem como velocidades linear e angular do réptil
* Nível de bateria
* Console de texto

A interface também deverá ser capaz de 

### Protocolo de mensagens

O protocolo será composto por:
* 1 byte de início (0xE6 - `æ`)
* 1 byte de ID da mensagem 
* Bytes de dados. Tamanho variável de acordo com o ID da mensagem
* 1 byte de soma de verificação (XOR dos bytes anteriores)
Várias mensagens podem ser enviadas em sequência dentro de um mesmo pacote, sendo que todos os pacotes terminam em 0x0A - `\n`.

Os IDs de mensagem incluem:
* **Turtle → PC**
```
╔══════╦═════════════╦═════════════════╦════════════════════════════════════╗
║  ID  ║  Mensagem   ║ Tamanho (bytes) ║              Sintaxe               ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x40 ║ Heartbeat   ║        1        ║ (byte) 1: Ligado, 0: Desligado     ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x41 ║ Estado LEDs ║        2        ║ (byte 1) 0  0  0  0  0  L5 L4 L3   ║
║      ║             ║                 ║ (byte 2) L2 L1 C  R1 R2 R3 R4 R5   ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x42 ║ Velocidades ║        8        ║ (float 1) Motor esquerdo (rad/s)   ║
║      ║             ║                 ║ (float 2) Motor direito (rad/s)    ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x43 ║ Atuadores   ║        2        ║ (byte 1) Duty cycle motor esquerdo ║
║      ║             ║                 ║ (byte 2) Duty cycle motor direito  ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x44 ║ Ação atual  ║        1        ║ (byte) Vide enum da estratégia     ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x45 ║ Bateria     ║        2        ║ (uint16) Tensão × fator de escala  ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x46 ║ Texto       ║     1 a 256     ║ (byte 1) N: Qtde. de caracteres    ║
║      ║             ║                 ║ (bytes 2 a N+1) Texto p/ o console ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x47 ║ Status erro ║        1        ║ (byte) Vide enum de erros          ║
╚══════╩═════════════╩═════════════════╩════════════════════════════════════╝
```

* **PC → Turtle**
```
╔══════╦═════════════╦═════════════════╦════════════════════════════════════╗
║  ID  ║  Mensagem   ║ Tamanho (bytes) ║              Sintaxe               ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x60 ║ Parâmetro   ║        5        ║ (byte) Tipo parâmetro (vide enum)  ║
║      ║             ║                 ║ (float) Valor do parâmetro         ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x61 ║ Setpoint    ║        8        ║ (float) Velocidade linear (m/s)    ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x62 ║ Mudar ação  ║        1        ║ (byte) Vide enum da estratégia     ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x63 ║ LED         ║        3        ║ (3 bytes) R, G, B                  ║
╠══════╬═════════════╬═════════════════╬════════════════════════════════════╣
║ 0x64 ║ Buzzer      ║        1        ║ (4 MSbits) Frequência              ║
║      ║             ║                 ║ (4 LSbits) Ciclo de trabalho       ║
╚══════╩═════════════╩═════════════════╩════════════════════════════════════╝
```

## Modelagem e controle

A modelagem da querida quelídea poderá ser encontrada no arquivo _modelo/Modelagem e controle.pdf_, bem como o cálculo da lei de controle. A obtenção dos coeficientes do modelo será feita em caixa preta utilizando o método dos mínimos quadrados. Para tal, deve-se realizar o ensaio contido em _modelo/ensaio/ensaio.ino_, que gravará as informações de entrada e saída em _modelo/ensaio.csv_. Esse arquivo deverá ser posteriormente lido no MATLAB por _modelo/modelagem.m_ que, a partir dos dados do ensaio, calculará os coeficientes do modelo e os ganhos do controlador.

### Simulação

O arquivo do Simulink _modelo/Controlador.slx_ contém o diagrama da planta e do controlador. Os coeficientes podem ser inseridos manualmente ou calculados após execução do _modelagem.m_.
