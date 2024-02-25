################################################################################
 # Makefile
 #
 #   Aluno: Filipe Ferreira Martins (11911EAU021) <filipe.ferreira.feelt@ufu.br>
 # 
################################################################################

# Sintaxe da Regra:

# target: prerequisites
# 	receipt

# Ferramentas do toolchain:

# Variável C compiler:
CC = arm-none-eabi-gcc
# Variável para remover arquivos e diretórios
RM = rm -rf

# Diretórios onde os arquivos objeto (.o) serão salvos:
#OBJDIR = src/build
OBJDIR = build
# Diretórios onde os arquivos das listas de dependências (.d) serão salvos:
DEPDIR = .deps

# Arquivos a serem compilados
SRCS = startup.c  main.c

# Flags do compilador e linker
# Flag do compilador
CFLAGS = -g -mcpu=cortex-m4 -mthumb -Wall -O0
# Flag da lista de dependencias
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d

# Gera uma lista de arquivos objeto utilizando os arquivos fonte
OBJS = $(patsubst %, $(OBJDIR)/%.o, $(basename $(SRCS)))
DEPS = $(patsubst %, $(DEPDIR)/%.d, $(basename $(SRCS)))

# Cria diretorios onde serao armazenados arquivos objeto
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)
$(shell mkdir -p $(dir $(DEPS)) > /dev/null)

all: $(OBJS)
# Muda o a pasta para acessar os arquivos objeto
#all: $(OBJS) -C src

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(DEPS):

# build/main.o: main.c config.h
# build/startup.o: startup.c
# build/main.o: main.c config.h

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(DEPDIR)