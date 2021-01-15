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

	int Chose;
	printf("Choisissez le bot que vous souhaiter : \n");
	printf("Tappez 1 pour le bot classique (plus de 70%% winrate)\n");
	printf("Tappez 2 pour le bot expert (plus de 90%% winrate)\n");
	printf("Tappez 3 pour jouer manuellement\n");
	scanf("%d",&Chose);

	initialisation(&LePlateau,&YOU,&ENNEMIE,&generalInfo);

	initObj(&YOU,&generalInfo,&ENNEMIE);


	if (Chose==1)
	{
		LoopOfGameAuto(&generalInfo,&YOU,&ENNEMIE); 
	}
	if (Chose==2)
	{
		LoopOfGameAutoNEW(&generalInfo,&YOU,&ENNEMIE);
	}
	if (Chose==3)
	{
		LoopOfGame(&generalInfo,&YOU,&ENNEMIE);
	}


	//showMe(&LePlateau,&YOU,&generalInfo);
	//printf("ENNEMIE\n");
	//showMe(&LePlateau,&ENNEMIE,&generalInfo);

	


	closeConnection();
	
	free(generalInfo.theGameBoard->TabOfTracks);
	
	return 0;
}