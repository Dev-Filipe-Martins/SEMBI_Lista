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

   Um Makefile consiste de "Regras" na seguinte sintaxe:

      target … : prerequisites …
        recipe
        …
        …
   
   A prerequisite is a file that is used as input to create the target. A target often depends on several files.

   Os targets e prerequisites são nomes de arquivos separados por espaços.

   O target é o arquivo objeto que desejamos gerar. prerequisistes é a dependencia mínima para gerar o arquivo. Recipe é a linha de comando que deve ser utilizada para gerar o arquivo alvo.

#### (d) Como são definidas as dependências de um **target**, para que elas são utilizadas?

   




#### (e) O que são as regras do **Makefile**, qual a diferença entre regras implícitas e explícitas?


   As regras do Makefile são instruçoes que definem como o utilitário make deve construir um determinado alvo

   As regras implícitas dizem quando e como refazer arquivos. Ela descrevev como um alvo pode depender de um arquivo com um nome semelhante ao alvo e fornece uma receita para criar ou atualizar este alvo.
   - São predefinidas pelo utilitário make
   - Não precisam ser escritas no Makefile
   - São usadas para construir arquivos de objeto a partir de arquivos de origem

   As regras explicitas lista os arquivos dos quais os alvos dependem, chamados de pré-requisitos do alvo. Tamvém fornece instruçoes ou uma receita para criar ou atualizar os alvos.
   - Sáo definidas pelo usuários no Makefile
   - São necessarias para construir targets que não podem ser construidos com regras implicitas
   


## 4. Sobre a arquitetura **ARM Cortex-M** responda:

### (a) Explique o conjunto de instruções ***Thumb*** e suas principais vantagens na arquitetura ARM. Como o conjunto de instruções ***Thumb*** opera em conjunto com o conjunto de instruções ARM?

### (b) Explique as diferenças entre as arquiteturas ***ARM Load/Store*** e ***Register/Register***.

### (c) Os processadores **ARM Cortex-M** oferecem diversos recursos que podem ser explorados por sistemas baseados em **RTOS** (***Real Time Operating Systems***). Por exemplo, a separação da execução do código em níveis de acesso e diferentes modos de operação. Explique detalhadamente como funciona os níveis de acesso de execução de código e os modos de operação nos processadores **ARM Cortex-M**.

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
