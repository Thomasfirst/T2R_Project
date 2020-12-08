#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "LoopOfGame.h"
#include "the_struct.h"
#include "look.h"
#include "initialisation.h"

int main()
{
	
	t_Game_Board LePlateau;		/* describe struct t_Game_Board*/

	t_Player YOU;

	t_Player ENNEMIE;

	t_GeneralInfo generalInfo;

	initialisation(&LePlateau,&YOU,&ENNEMIE,&generalInfo);
	
	LoopOfGame(&generalInfo.PlayerTurn);

	showMe(&LePlateau,&YOU,&generalInfo);
	



	closeConnection();

	return 0;
}