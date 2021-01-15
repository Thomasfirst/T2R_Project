#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "the_struct.h"
#include "headers.h"



void initialisation(t_Game_Board* LePlateau,t_Player* YOU,t_Player* ENNEMIE,t_GeneralInfo* generalInfo){

	char serverName[] = "li1417-56.members.linode.com";
	unsigned int port = 5678;	//or 5678 or 1234
	char name[] = "Lord";

	char gameName[] = "TestDePartieThomas";
	char gameType[] = "TRAINING NICE_BOT map=USA start=0 timeout=80";	/*PLAY_RANDOM	NICE_BOT*/
	
	/*		 describe struct t_Game_Board*/
	LePlateau->nbCities=0;
	LePlateau->nbTracks=0;

	connectToServer(serverName,port,name);

	waitForT2RGame(gameType,gameName,&LePlateau->nbCities,&LePlateau->nbTracks);


		/*		your info*/
	YOU->nbWagons=45;
	YOU->nbCards=4;
	YOU->nbObective=0;
	for (t_color i = 0; i < 10; ++i)
		YOU->TabOfCards[i]=0;

		/*	ennemie info*/
	ENNEMIE->nbWagons=45;
	ENNEMIE->nbCards=4;
	ENNEMIE->nbObective=0;
	for (t_color i = 0; i < 10; ++i)
		ENNEMIE->TabOfCards[i]=0;

		/*		info of the game*/
	generalInfo->PlayerTurn=1;		
	generalInfo->YourNumber=0;
	generalInfo->theGameBoard=LePlateau;

	t_color cards[4];
	int* tracks = malloc((LePlateau->nbTracks*5) * sizeof(int));
	for (int i = 0; i < LePlateau->nbTracks*5; ++i)
		tracks[i]=0;

	generalInfo->PlayerTurn = getMap(tracks, generalInfo->faceUp, cards);
	YOU->TabOfCards[cards[0]]+=1;		/*import the 4 first draw*/
	YOU->TabOfCards[cards[1]]+=1;
	YOU->TabOfCards[cards[2]]+=1;
	YOU->TabOfCards[cards[3]]+=1;

		/*initilisation of tab of t_road*/
	t_road* tracksRoad = malloc((LePlateau->nbTracks) * sizeof(t_road));		/*arrray of the t_road*/
	for (int i = 0; i < LePlateau->nbTracks; ++i)
	{
		tracksRoad[i].city1 = tracks[i*5];
		tracksRoad[i].city2 = tracks[i*5+1];
		tracksRoad[i].length = tracks[i*5+2];
		tracksRoad[i].ocupation = 0;
		tracksRoad[i].color1 = tracks[i*5+3];
		tracksRoad[i].color2 = tracks[i*5+4];
	}
	LePlateau->TabOfTracks=tracksRoad;	

	free(tracks);
		

}