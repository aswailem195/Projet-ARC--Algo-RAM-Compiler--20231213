SRCDIR = ../../src
INCDIR = ../../include
OBJDIR = ../../obj


# Compilateur et gcc flags
CC = gcc
CFLAGS = -Wall -g -I$(INCDIR)


# fichiers source et objets correspondant 
SRCS = $(SRCDIR)/ts.c 
OBJS = $(OBJDIR)/ts.o 

# executable
EXEC = test_ts

all: $(EXEC)

# Compilation du projet
$(EXEC): $(OBJS) test_ts.c
	$(CC) $(CFLAGS) $^ -o $@

# Regle pour compiler les fichiers objets a partir d'un .c
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean
clean:
	rm -f $(OBJS) $(EXEC) *~

.PHONY: all clean
