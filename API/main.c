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

	initObj(&YOU,&generalInfo,&ENNEMIE);



	
	LoopOfGameAuto(&generalInfo,&YOU,&ENNEMIE);

	showMe(&LePlateau,&YOU,&generalInfo);

	//printf("ENNEMIE\n");
	//showMe(&LePlateau,&ENNEMIE,&generalInfo);

	



	closeConnection();
	
	free(generalInfo.theGameBoard->TabOfTracks);
	
	return 0;
}