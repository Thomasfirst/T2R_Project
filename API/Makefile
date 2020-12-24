
# options de compilation
CC = gcc
CCFLAGS = -Wall
LIBS =
LIBSDIR = 

# fichiers du projet
SRC = main.c TicketToRideAPI.c clientAPI.c LoopOfGame.c Look.c initialisation.c initObj.c fonctions.c filInfo.c chooseMove.c
OBJ = $(SRC:.c=.o)
EXEC = T2R_lExe.out


# règle initiale
all: $(EXEC)

# dépendance des .h
main.o: clientAPI.h TicketToRideAPI.h the_struct.h headers.h


LoopOfGame.o: clientAPI.h TicketToRideAPI.h headers.h
Look.o: clientAPI.h TicketToRideAPI.h the_struct.h headers.h
initObj: clientAPI.h TicketToRideAPI.h the_struct.h headers.h
initialisation.o: clientAPI.h TicketToRideAPI.h the_struct.h headers.h
fonctions: clientAPI.h TicketToRideAPI.h the_struct.h headers.h
filInfo.c: clientAPI.h TicketToRideAPI.h the_struct.h headers.h
chooseMove.c: clientAPI.h TicketToRideAPI.h the_struct.h headers.h

TicketToRideAPI.o: clientAPI.h TicketToRideAPI.h
clientAPI.o: clientAPI.h

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