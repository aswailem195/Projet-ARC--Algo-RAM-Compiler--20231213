# Répertoire
SRCDIR = src
INCDIR = include
OBJDIR = obj
TSTDIR = test
BINDIR = bin
DOCDIR = doc

# Compilateur et gcc flags
CC = gcc
CFLAGS = -Wall -I$(INCDIR) -g

TEX = pdflatex

# fichiers source et objets correspondant 
SRCS = $(wildcard $(SRCDIR)/*.c) $(SRCDIR)/parser.c $(SRCDIR)/lexer.c
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))


# executable
EXEC = $(BINDIR)/arc

# Documentation
PDF = $(DOCDIR)/arc_doc.pdf

all: $(EXEC) $(PDF)

# Compilation de la documentation
$(PDF): $(DOCDIR)/arc_doc.tex
	$(TEX) -output-directory $(DOCDIR) $<  

# Compilation du projet
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lfl

# Regle pour compiler les fichiers objets a partir d'un .c
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regle pour le parser
$(SRCDIR)/parser.c $(INCDIR)/parser.h: $(SRCDIR)/parser.y
	bison -d -o $(SRCDIR)/parser.c $<
	mv $(SRCDIR)/parser.h $(INCDIR)

# Regle pour le lexer
$(SRCDIR)/lexer.c: $(SRCDIR)/lexer.lex $(INCDIR)/parser.h
	flex -o $@ $<

test:
	@for dir in $(sort $(dir $(wildcard $(TSTDIR)/*/) ) ); do \
		$(MAKE) -C $$dir;                \
	done

# clean
clean:
	rm -f $(OBJS) $(EXEC) $(SRCDIR)/parser.c $(SRCDIR)/lexer.c $(DOCDIR)/*.[alop]* */*~ *~

.PHONY: all test clean
