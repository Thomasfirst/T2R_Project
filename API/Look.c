#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "the_struct.h"
#include "headers.h"




void showMe(t_Game_Board* LePlateau, t_Player* YOU, t_GeneralInfo* generalInfo){
	printf("Le nombre de villes:%d \n",generalInfo->theGameBoard->nbCities); 	//LePlateau->nbCities);
	printf("Le nombre de vois:%d \n",generalInfo->theGameBoard->nbTracks);
	
	for (int i = 0; i < 5; ++i)
	{
		printf("exemple un track %d \n",generalInfo->theGameBoard->TabOfTracks[i]);
	}
	

	printf("tu as %d wagon \n", YOU->nbWagons );
	printf("tu as %d cartes\n", YOU->nbCards);
	for (int i = 0; i < 10; ++i)
	{
		printf(" couleur:%d nombre:%d \n", i , YOU->TabOfCards[i] );
	}
	printf("%d objectif\n", YOU->nbObective);

	for (int i = 0; i < YOU->nbObective; ++i)
	{
		printf("objectif num:%d ville:%d a ville:%d valeur:%d \n",i,YOU->TabOfObjetive[i].city1,YOU->TabOfObjetive[i].city2,YOU->TabOfObjetive[i].score);
	}


	printf("au tour du joueur %d \n",generalInfo->PlayerTurn);
	for (int i = 0; i < 5; ++i)
	{
		printf("couleur sur la table :%d \n", generalInfo->faceUp[i] );
	}
}
