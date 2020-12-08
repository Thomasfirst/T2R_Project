
# options de compilation
CC = gcc
CCFLAGS = -Wall
LIBS =
LIBSDIR = 

# fichiers du projet
SRC = main.c TicketToRideAPI.c clientAPI.c LoopOfGame.c Look.c initialisation.c
OBJ = $(SRC:.c=.o)
EXEC = T2R_lExe.out


# règle initiale
all: $(EXEC)

# dépendance des .h
main.o: clientAPI.h TicketToRideAPI.h LoopOfGame.h the_struct.h look.h initialisation.h
TicketToRideAPI.o: clientAPI.h TicketToRideAPI.h
clientAPI.o: clientAPI.h
LoopOfGame.o: LoopOfGame.h clientAPI.h TicketToRideAPI.h look.h
Look.o: clientAPI.h TicketToRideAPI.h LoopOfGame.h the_struct.h look.h
initialisation.o: clientAPI.h TicketToRideAPI.h the_struct.h initialisation.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS) $(LIBSDIR)

# règles supplémentaires
clean:
	rm -f *.o
mproper:
	rm -f $(EXEC) *.o