#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "the_struct.h"
#include "headers.h"


int main()
{
	
	t_Game_Board LePlateau;		/* describe struct t_Game_Board*/

	t_Player YOU;

	t_Player ENNEMIE;

	t_GeneralInfo generalInfo;

	initialisation(&LePlateau,&YOU,&ENNEMIE,&generalInfo);
	
	LoopOfGame(&generalInfo,&YOU,&ENNEMIE);

	showMe(&LePlateau,&YOU,&generalInfo);
	printf("ENNEMIE\n");
	showMe(&LePlateau,&ENNEMIE,&generalInfo);

	



	closeConnection();
	
	free(LePlateau.TabOfTracks);
	return 0;
}