#REGRA
#target: prerequisites
#	receipt

# Variável C compiler
CC = arm-none-eabi-gcc
RM = rm -rf
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0

#SRCS = startup.c main.c
#OBJS = $(addsufix .o, $(basename $(SRCS)))
# Outra forma:
OBJS = $(patsubst %, %.o, startup main)
#OBJS = $(patsubst %, %.o, $(basename $(SRCS)))

#all: startup.o main.o
all: $(OBJS)

%.o: %.c
	$(CC) -c -g $(CFLAGS) $< -o $@

# Como a função é a mesma da acima, all é capaz de separar
#main.o: main.c
#	$(CC) -c -g $(CFLAGS) $< -o %@

clean:
	$(RM) *.o