# Questionário Sistemas Embarcados I

## 1. Explique brevemente o que é compilação cruzada (***cross-compiling***) e para que ela serve.

   A compilação cruzada (***cross-compiling***) consiste no processo de compilar um código executável em uma arquitetura (sistema operacional) diferente daquela em que o compilador está sendo executado. Basicamente, podemos escrever um código em um computador e compilá-lo para ser executado em outra plataforma com arquitetura ou sistema operacional diferente. 
   Esse processo é utilizado para criação de softwares multiplataforma e para desenvolvimento de softwares embarcados.

   No caso de softwares embarcados, temos o sistema embarcado (target): microcontrolador STM32 Arquitetura ARM Cortex M4. E temos a máquina de desenvolimento (host): arquitetura Linux. O código é escrito no (host) compilado utilizando o St link para ser executado no (target).
    
## 2. O que é um código de inicialização ou ***startup*** e qual sua finalidade?

   O código de inicialização (startup) tem o papel de iniciar uma rotina intermediária de instruções que executa algumas tarefas antes da chamada da função main(). Um arquivo do tipo (startup.c) possui o código de inicialização responsavel por executar as tarefas de inicialização quando um programa é iniciado.

   Sua finalidade é preparar o ambiente para que o programa possa funcionar corretamente. Basicamente o código de inicialização carrega as bibliotecas necessárias, configura as variáveis de ambiente, inicializa os objetos do programa, executa outras tarefas de inicialização e no caso da arquitetura ARM cortex-M também deve realizar a alocação da tabela de vetores de interrupção na memória.

   O código de inicialização garante que o programa seja configurado corretamente e que tenha os recursos necessarios para funcionar.
   
## 3. Sobre o utilitário **make** e o arquivo **Makefile responda**:

#### (a) Explique com suas palavras o que é e para que serve o **Makefile**.

   O Makefile é o arquivo que contém as instruções necessárias para que o utilitário Make seja capaz de compilar os arquivos, programas e bibliotecas de forma automática. Contendo os comandos de compilação que devem ser utilizados e como lidar com os erros.
   As instruçoes no Makefile possui 5 tipos de elementos, sendo eles: regras explícitas, regras implícitas, definições de variávveis, diretivas e comentários.

#### (b) Descreva brevemente o processo realizado pelo utilitário **make** para compilar um programa.

   O utilitário make usa o arquivo texto (Makefile) para determinar quais arquivos precisam ser compilados e como compila-los. O make utiliza a base de dados do (Makefile) e a data de modificação dos arquivos para decidir de forma automática quais arquivos precisam ser atualizados, e quais os arquivos que precisam ser compilados novamente, executando os comandos de registro na base de dados para cada um desses arquivos e exibe mensagens de erro caso ocorrer algum problema de compilação.

#### (c) Qual é a sintaxe utilizada para criar um novo **target**?

   O "target" é escrito no início da linha, seguido por uma sinal de dois pontos ":".

   Os "prerequisites" são listados após o "target", separadas por espaços.

   Os "targets" e "prerequisites" são nomes de arquivos separados por espaços. Um "prerequisite" é um arquivo utilizado como entrada para criar um "target" que geralmente depende de vários arquivos.

   O "recipe" é escrito em linhas separadas, começando com uma tabulação.
   
   Na seguinte sintaxe:

      target … : prerequisites …
         recipe
         …
         …

   O "target" é o arquivo objeto que desejamos gerar, "prerequisistes" é a dependencia mínima para gerar o arquivo e "recipe" é a linha de comando que deve ser utilizada para gerar o arquivo alvo.

   Exemplo:

      main.o: main.c
	      arm-none-eabi-gcc -c -g -mcpu=cortex-m4 -mthumb -O0 -Wall main.c -o main.o
   
   O "main.o" é o arquivo objeto que desejamos gerar. Para isso, dependemos do arquivo "main.c" como "prerequisite". O "recipe" é a linha de comando para gerar o alvo.

#### (d) Como são definidas as dependências de um **target**, para que elas são utilizadas?

   As dependências de um "target" são definidas na mesma linha do alvo, logo após o sinal de dois pontos ":", e são listadas cada arquivo de dependência na mesma linha separando-as por espaços.

   São utilizadas para gerar o arquivo objeto antes de criar o "target", funciona como um pré-requisito para que o "target seja criado".

#### (e) O que são as regras do **Makefile**, qual a diferença entre regras implícitas e explícitas?

   Uma regra do "Makefile" diz quando e como fazer determinados arquivos, chamados de alvos "target". Ele lista os arquivos de pré-requisitos do destino e as instruções para criar ou atualizar o destino. Uma regra também pode explicar como e quando realizar uma ação.

   As regras implícitas dizem quando e como refazer arquivos. Ela descrevev como um alvo pode depender de um arquivo com um nome semelhante ao alvo e fornece uma receita para criar ou atualizar este alvo. 
   
   Algumas caracteristicas de regras implícitas:
   - São predefinidas pelo utilitário make
   - Não precisam ser escritas no Makefile
   - São usadas para construir arquivos de objeto a partir de arquivos de origem

   As regras explícitas lista os arquivos dos quais os alvos dependem, chamados de pré-requisitos do alvo. Tamvém fornece instruçoes ou uma receita para criar ou atualizar os alvos.

   As regras explícitas:
   - São definidas pelo usuários no Makefile
   - São necessarias para construir targets que não podem ser construidos com regras implicitas

## 4. Sobre a arquitetura **ARM Cortex-M** responda:

### (a) Explique o conjunto de instruções ***Thumb*** e suas principais vantagens na arquitetura ARM. Como o conjunto de instruções ***Thumb*** opera em conjunto com o conjunto de instruções ARM?

   As instruçoes "Thumb" são um conjunto de instruçoes de 16-bits que foram desenvolvidas para a arquitetura ARM. O conjunto de intruçoes ARM de 32-bits é o tradicional e por padrao o compilador gera o código utilizando o conjunto de instruçoes ARM. No caso de processadores ARM Cortex-M, apenas o conjunto de instruçoes "Thumb" é suportado. Logo é preciso alterar este comportamento utilizando a seguinte opçao:
         -mthumb
   
   As instruçoes "Thumb" foram projetadas para reduzir o tamanho do código e melhorar a eficiência energética em comparação com as instruções ARM de 32 bits.Isso ocorre porque elas usam menos ciclos de clock e menos energia para serem executadas. Além disso o código Thumb pode ser até 50% menor que o código ARM equivalente

   Alguns processadores ARM podem executar dois conjuntos de instruçoes distintos, isso significa que você pode usar instruções Thumb e ARM no mesmo programa.

   Uma das maneiras de operar as instruçoes Thumb e ARM de forma conjunta é utilizando o modo de operação. No modo ARM o processador executa instruçoes de 32-bits e no modo Thumb executa instruçoes de 16-bits. A mudança entre os modos é realizada através do registrador de status do programa (CSR).

   Compiladores modernos podem gerar código em ambos os conjuntos, além disso, o processador pode alternar entre os modes dinamicamente, de acordo com a instrução em execuçao.

### (b) Explique as diferenças entre as arquiteturas ***ARM Load/Store*** e ***Register/Register***.

   A arquitetura Load/Store tem um modelo de memória dividida em duas áreas: registradores e memória principal. As instruçoes de carga e armazenamento movem dados entre os registradores e a memória principal. As operaçoes aritméticas e lógicas são realizadas apenas em registradores.

   Essa arquitetura tem um menor consumo de energia e possui um código mais compacto e eficiente.

   Já na arquitetura Register/Register, todos os dados residem em registradores. As operaçoes aritméticas e lógicas são realizadas em registradores ou na memória principal.\

   É um modelo mais complexo, mas com maior flexibilidade e desempenho para operaçoes complexas. Além disso, permite acesso direto a memória principal para operaçoes específicas.

### (c) Os processadores **ARM Cortex-M** oferecem diversos recursos que podem ser explorados por sistemas baseados em **RTOS** (***Real Time Operating Systems***). Por exemplo, a separação da execução do código em níveis de acesso e diferentes modos de operação. Explique detalhadamente como funciona os níveis de acesso de execução de código e os modos de operação nos processadores **ARM Cortex-M**.

   Um sistema RTOS (Real Time Operating System) é um sistema operacional projetado para gerenciar o tempo real em processadores ARM Cortex-M. O RTOS fornece uma estrutura para executar tarefas e gerenciar recursos em tempo real, garantindo que as tarefas críticas sejam executadas dentro de prazos específicos.

   Um RTOS é capaz de:
   - Gerenciar tarefas: cria, agenda e executa tarefas com diferentes prioridades.
   - Gerenciar interrupçoes: manipula interrupçoes externas e internas de forma organizada e eficiente.
   - Gerenciar sicronizaçao: Controla o acesso a recursos compartilhados pro diferentes tarefas, evitando conflitos e garantindo a integridade dos dados.
   - Gerenciar memória: faz a alocaçao e desalocaçao de memória dinamicamente, otimizando o uso da memória disponível.
   - Comunicar entre tarefas: fornece mecanismos para comunicação eficiente e segura entre diferentes tarefas.
   - Fazer serviços em tempo real: possui suporte para temporizadores, alarmes e outras funcionalidades relacionadas ao tempo real.

   Os processadores ARM Cortex-M possuem 2 níveis de acesso para execuçao de código:

   - Nível de acesso privilegiado (PAL): Permite acesso total aos recursos do processador, incluindo registradores restritos e instruçoes especiais. É utilizado para executar código do sistema operacional, drivers e outras funçoes críticas.
   - Nível de acesso sem privilégio (NPAL): Permite acesso limitado aos recursos do processador, impedindo o acesso a registradores restritos e instruçoes especiais. É utilizado para executar o código da aplicaçao, garantindo a aestabilidade do sistema.

   Também possuem 2 modosd de operação:

   - Modo Thread: Modo padrão de execuçao do processador, onde as instruçoes sao executadas sequencialmente. É utilizado para executar a maioria das tarefas do sistema.
   - Modo Handler: Modo especial ativado quando ocorre uma exceçao ou interrupçao. Permite que o processador lide com eventos específicos, como falhas de memória ou solicitaçoes de entrada e saída.

### (d) Explique como os processadores ARM tratam as exceções e as interrupções. Quais são os diferentes tipos de exceção e como elas são priorizadas? Descreva a estratégia de **group priority** e **sub-priority** presente nesse processo.

   As Exceções são eventos anormais que ocorrem durante a execução do programa, como divisão por zero, overflow e acesso a memória inválida. O processador ARM gera um vetor de exceção que identifica a causa da exceçao e direciona o fluxo de execuçao para o manipulador de exceção específico. O manipulador de exceção é responsavel por tomar as medidas cabíveis para lidar com a exceção, como registrar o erro, encerrar a tarefa ou reiniciar o sistema.

   As interrupções são eventos externos que solicitam a atenção do processador, como um sinal de um dispositivo de entrada/saída ou um evento de temporização. O processador ARM gera um vetor de interrupcão que identifica a origem da interrupção e direciona o fluxo de execução para o manipulador de interrupção específico. O manipulador de interrupção é responsavel por atender a solicitação da interrupçao e retornar ao ponto de interrupçao após a conclusão da tarefa.
   
   A arquitetura ARM reserva 15 vetores de interrupçoes destinadas a exceçoes geradas pelo processador, chamadas de (Built-in-exceptions). Estes vetores são indexados de 1-15. O índice 0 não é um vetor de interrupçao mas sim o valor inicial do SP (Stack pointer). Essa foi a saída criada pela ARM para ter um stack pointer inicializado desde o começo do código, permitindo que toda a partida possa ser feita em linguagem C.
   
   Além dos vetores de interrupçao da CPU a arquitetura também suporta linhas de interrupçao externas ao núcleo da CPU, (External Exceptions). Estas linhas de interrupçao geralmente são roteadas para perifericos específicos do fabricvante do chip tais como DMA (Direct memory access), GPIO (General Purpose Input/Output), etc. Todas estas interrupçoes são configuradas por meio de um periférico conhecido como NVIC (Nested Vectored Interrupt Controller). Um detalhe adicional é que o endereço base desses vetores de interrupçao pode ser alterado em núcleo ARM Cortex-M3 ou superior através do registro VTOR (Verctor table offset register)

   A estratégia de prioridade de grupo e subprioridade é o método para organizar e gerenciar interrupções em sistemas embarcados. Essa estratégia divide as interrupções em grupos e subgrupos, permitindo um controle mais granular sobre a ordem de atendimento das interrupções.

   Em (Group Priority) cada grupo de interrupções é atribuido a um nível de prioridade. o nivel de prioridade mais alto são atendidas antes de prioridades mais baixas. Isso garente que as interrupções mais críticas sejam sempre atendidas primeiro, mesmo que existam muitas interrupções de menor importancia pendentes.

   Em (Sub-priority) dentro de cada grupo de interrupções, as interrupçoes podem ser further prioritized usando subprioridades. As subprioridades mais altas dentro do mesmo grupo são atendidas antes de interrupções com subprioridade mais baixa.

### (e) Qual a diferença entre os registradores **CPSR** (***Current Program Status Register***) e **SPSR** (***Saved Program Status Register***)?

   Os registradores CPSR e SPSR são registradores de status do programa presentes nos processadores ARM. Ambos armazenam informações sobre o modo de operação atual, nível de interrupção e outras flags de status, mas possuem diferentes funções e comportamentos.

   O CPSR (Current Program Status Register) tem a função de armazenar o estado atual do processador, é atualizado constantemente durante a execução do programa e é acessível em todos os modos de operação. Nele possui o modo de operação, o nível de interrupção e as flags de status.

   O SPSR (Saved Program Status Register) tem a função de armazenar o estado do processador antes de entrar em um modo de exceção, é atualizado apenas quando o processador entra em um modo de exceção e é acessível apenas nos modos de exceção. Nele possui o modo de operação anterior, o nível de interrupção anterior e as flags de status anteriores.

### (f) Qual a finalidade do **LR** (***Link Register***)?

   O (LR) Link Register é um registrador especial que tem como finalidade de armazenar o endereço de retorno para uma sub-rotina. Ele é usado para implementar o mecanismo de pilha de chamadas, permitindo que o processador retorne a instruçao que chamou a sub-rotina após a sua execução. Quando uma sub-rotina é chamada, o endereço da próxima instruçao a ser executada (o endereço de retorno) é salvo no LR. A sub-rotina então é executada normalmente e ao final, o valor armazenado no LR é usado para retornar a instrução que chamou a sub-rotina.

   O LR é usado em conjunto com a pilha de memória para implementar a pilha de chamadas. A pilha de chamadas é uma estrututra de dados LIFO (Last-in-First-out) que armazena os endereçoes de retorno de sub-rotinas.

### (g) Qual o propósito do Program Status Register (PSR) nos processadores ARM?

   O PSR (Program Status Refister) é um registrador que armazena informações sobre o estado atual do processador.

   Ele define o modo de operação do processador, onde cada modo possui diferentes permissões e funcionalidades. Indica o nível de prioridade da interrupção que está sendo atendidad ou que está pendente. Armazena flags de status que indicam condições específicas do processador, como carry, overflow, zero, negative, etc. Também permite habilitar ou desabilitar interrupções específicas, definindo a máscara de interrupção.

### (h) O que é a tabela de vetores de interrupção?

   A tabela de vetores de interrupção é uma estrutura de dados que mapeia os endereços de memória das rotinas de tratamento de interrupção. Ela é essencial para garantir que as interrupções sejam tratadas de forma rápida e eficiente, minimizando o impacto no desempenho do sistema.
   
   Nela, cada interrupção tem um número de identificação unico. A tabela é um array indexado por esses números de identificação. Cada entrada na tabela contém o endereço de memória da rotina de tratamento de interrupção específica para a interrupçao associada. Quando ocorre uma interrupção, o precessador consulta a tabela usando o número de identificação da interrupção coo índice. O processador então, carrega e executa a rotina de tratamento de interrupção localizada no endereço de memória obtido da tabela.

### (i) Qual a finalidade do NVIC (**Nested Vectored Interrupt Controller**) nos microcontroladores ARM e como ele pode ser utilizado em aplicações de tempo real?

   O NVIC tem a finalidade de gerenciar o tratamento de interrupçoes de forma eficiente e confiável. Ele é fundamental para o desenvolvimento de aplicações embarcadas em tempo real, onde a resposta rápida e precisa as interrupçoes é critica para o bom funcionamento do sistema.

   O NVIC recebe solicitações de interrupção de diferentes fontes, como periféricos, timers e eventos de software. Ele então prioriza e direciona as interrupções para as rotinas de tratamento de interrupção adequada.

   Ele permite definir prioridades para cada fonte de interrupção, garantindo que as interrupções mais críticas sejam sempre atendidas em primeiro lugar. Também permite que as interrupções de alta prioridade interrompam o tratamento de interrupções de menor prioridade, garantindo a resposta imediata as interrupções mais urgentes.

   O NVIC permite habilitar ou desabilitar interrupções específicas, permitindo que o software controle o fluxo de interrupçoes do sistema.

   Em aplicaçoes de tempo real, o NVIC pode ser utilizado para garantir que os processos críticos sejam executados em tempo hábil, priorizando suas interrupções e garantindo a resposta rápida a eventos externos. Ele pode ser utilizado para sincronizar a aquisição de dados de sensores com outros eventos dno sistema, garantindo a precisão e confiabilidade dos dados coletados

### (j) Em modo de execução normal, o Cortex-M pode fazer uma chamada de função usando a instrução **BL**, que muda o **PC** para o endereço de destino e salva o ponto de execução atual no registador **LR**. Ao final da função, é possível recuperar esse contexto usando uma instrução **BX LR**, por exemplo, que atualiza o **PC** para o ponto anterior. No entanto, quando acontece uma interrupção, o **LR** é preenchido com um valor completamente  diferente,  chamado  de  **EXC_RETURN**.  Explique  o  funcionamento  desse  mecanismo  e especifique como o **Cortex-M** consegue fazer o retorno da interrupção. 

   Instrução BL (Branch and Link) é uma instrução condicional de ramificação utilizada para desviar o fluxo de execução do programa para um endereço de memória específico. É frequentemente utilizada para chamar sub-rotinas e implementar estruturas de controle como loops e instruçoes condicionais.

   PC (Program Counter) é um registrador especial que armazena o endereço da próxima instrução a ser executada.

   Esse mecanismo é um método para lidar com exceções de software. Quando uma exceção de software é gerada, o processador precisa determinar o endereço da próxima instrução a ser executada. O mecanismo de preenchimento facilita esse processo, fornecendo um endereço de retorno padrão para as exceçoes de software.

   O processador ARM possui um registrador especial chamado EXC_RETURN. Esse registrador armazena o endereço da próxima instrução a ser executada após a exceção de software ser tratada. Quando a exeção é gerada, o processador verifica o valor do registrador EXC_RETURN. Se o valor do registrador EXC_RETURN for diferente de zero, o processador carrega esse valor no registrador (PC). Isso faz com que o programa continue a execução a partir da instrução indicada pelo EXC_RETURN. Se o valor for zero, o processador assume que o software precisa lidar com a exceção. Nesse caso, o processador chama a rotina de tratamento de exceção do sistema operacional.

### (k) Qual  a  diferença  no  salvamento  de  contexto,  durante  a  chegada  de  uma  interrupção,  entre  os processadores Cortex-M3 e Cortex M4F (com ponto flutuante)? Descreva em termos de tempo e também de uso da pilha. Explique também o que é ***lazy stack*** e como ele é configurado. 

   No Cortex-M3 apenas os registradores do núcleo são salvos, com isso, o contexto salvo é menor. Em questões de desempenho, o salvamento de contexto é mais rápido, pois há menos registradores para salvar. Além disso, não utiliza mecanismo de salvamento em pilha, e não possui modo de ponto flutuante.

   O Cortex-M4F salva os registradores do núcleo e os registradores de ponto flutuante, assim, o contexto salvo é maior. O desempenho para salvamento de contexto é mais lento, pois há mais registradores para salvar. Pode utilizar um mecanismo de salvamento em pilha ou em registradores específicos. Possui modo de ponto flutuante, que precisa ser ativado antes de usar os registradores de ponto flutuante. 

   O Lazy Stack é uma técnica de otimização de memória utilizada em processadores ARM para reduzir o uso de memória RAM. Em vez de alocar uma pilha fixa para cada thread, a pilha lazy é alocada dinamicamente apensa quando necessário. Isso pode ser útil para aplicaçoes embarcadas com recursos de memória limitados.

   Quando uma thread é criada, apenas uma pequena parte da pilha é alocada. Se a thread precisar de mais espaço na pilha, ela é expandida dinamicamente em páginas de memória. O uso da pilha lazy pode melhorar o desempenho geral do sistema, pois reduz o uso de memória RAM e a fragmentação da memória.

   Em sua configuração, o linker script é utilizado para definir o tamanho da pilha inicial e o tamanho máximo da pilha. A biblioteca de tempo de execução fornece funçoes para alocar e liberar memória de pilha automaticamente.

## Referências

### Básicas

[1] [STM32F411xC Datasheet](https://www.st.com/resource/en/datasheet/stm32f411ce.pdf)

[2] [RM0383 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

[3] [Using the GNU Compiler Collection (GCC)](https://gcc.gnu.org/onlinedocs/gcc/index.html)

[4] [GNU Make](https://www.gnu.org/software/make/manual/html_node/index.html)

### Vídeos Microsoft Teams

[5] [05 - Introdução à arquitetura de computadores](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[6] [06 - Arquitetura Cortex-M Parte 1/2](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[7] [07 - Arquitetura Cortex-M Parte 2/2](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[8] [08 - Microcontroladores STM32](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

[9] [10 - Introdução à arquitetura de computadores](https://web.microsoftstream.com/embed/channel/f6b3a0de-e6f3-4652-b2d5-f1164032498a?app=microsoftteams&sort=undefined&l=pt-br#)

### Material Suplementar

[5] [A General Overview of What Happens Before main()](https://embeddedartistry.com/blog/2019/04/08/a-general-overview-of-what-happens-before-main/)
 
[6] [Bare metal embedded lecture-1: Build process](https://youtu.be/qWqlkCLmZoE?si=mn5yDnJYudQ1PpZH)
 
[7] [Bare metal embedded lecture-2: Makefile and analyzing relocatable obj file](https://youtu.be/Bsq6P1B8JqI?si=yuNLPj3JQ-2IT1yo)
 
[8] [Bare metal embedded lecture-3: Writing MCU startup file from scratch](https://youtu.be/2Hm8eEHsgls?si=c27MpZ47ApiMSwHR)
 
[9] [Lecture 15: Booting Process](https://youtu.be/3brOzLJmeek?si=MsHRUEJP8zofjwJQ)
