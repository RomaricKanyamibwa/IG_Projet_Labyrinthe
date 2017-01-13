# Modèle de fichier Makefile  pour le fichier template.c
LIBDIR = /home/sasl/encad/brajard/projet/CGS_lib

# options de compilation
CC = gcc -g
CCFLAGS = -Wall -I $(LIBDIR)/include
LIBS = -L $(LIBDIR)/lib
LDFLAGS = -lm -lcgs

# fichiers du projet
SRC = template.c Aetoile.c array_mod.c
OBJ = $(SRC:.c=.o)
EXEC = template


# règle initiale
all: $(EXEC)

# dépendance des .h
template.o:template.h Aetoile.h  array_mod.h

Aetoile.o: Aetoile.h array_mod.h

array_mod.o: array_mod.h


# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

# règles supplémentaires
clean:
	rm -f *.o
rmproper:
	rm -f $(EXEC) *.o
