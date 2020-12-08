#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "LoopOfGame.h"
#include "the_struct.h"
#include "look.h"



void showMe(t_Game_Board* LePlateau, t_Player* YOU, t_GeneralInfo* generalInfo){
	printf("Le nombre de villes:%d \n",LePlateau->nbCities);
	printf("Le nombre de vois:%d \n",LePlateau->nbTracks);
	for (int i = 0; i < 5; ++i)
	{
		printf("exemple un track %d \n",LePlateau->TabOfTracks[i]);
	}
	

	printf("tu as %d wagon \n", YOU->nbWagons );
	printf("tu as %d cartes\n", YOU->nbCards);
	for (int i = 0; i < 10; ++i)
	{
		printf(" couleur:%d nombre:%d \n", i , YOU->TabOfCards[i] );
	}
	//printf("objectif\n");

	printf("au tour du joueur %d \n",generalInfo->PlayerTurn);
	for (int i = 0; i < 5; ++i)
	{
		printf("couleur sur la table :%d \n", generalInfo->faceUp[i] );
	}
}
