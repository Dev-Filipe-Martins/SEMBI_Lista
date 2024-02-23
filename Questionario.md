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

### (e) Qual a diferença entre os registradores **CPSR** (***Current Program Status Register***) e **SPSR** (***Saved Program Status Register***)?

### (f) Qual a finalidade do **LR** (***Link Register***)?

### (g) Qual o propósito do Program Status Register (PSR) nos processadores ARM?

### (h) O que é a tabela de vetores de interrupção?

### (i) Qual a finalidade do NVIC (**Nested Vectored Interrupt Controller**) nos microcontroladores ARM e como ele pode ser utilizado em aplicações de tempo real?

### (j) Em modo de execução normal, o Cortex-M pode fazer uma chamada de função usando a instrução **BL**, que muda o **PC** para o endereço de destino e salva o ponto de execução atual no registador **LR**. Ao final da função, é possível recuperar esse contexto usando uma instrução **BX LR**, por exemplo, que atualiza o **PC** para o ponto anterior. No entanto, quando acontece uma interrupção, o **LR** é preenchido com um valor completamente  diferente,  chamado  de  **EXC_RETURN**.  Explique  o  funcionamento  desse  mecanismo  e especifique como o **Cortex-M** consegue fazer o retorno da interrupção. 

### (k) Qual  a  diferença  no  salvamento  de  contexto,  durante  a  chegada  de  uma  interrupção,  entre  os processadores Cortex-M3 e Cortex M4F (com ponto flutuante)? Descreva em termos de tempo e também de uso da pilha. Explique também o que é ***lazy stack*** e como ele é configurado. 


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
