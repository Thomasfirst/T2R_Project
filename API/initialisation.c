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
	char name[] = "testingBot";

	char gameName[] = "TestDePartieThomas";
	char gameType[] = "TRAINING DO_NOTHING map=USA";
	
	/*t_Game_Board LePlateau;		 describe struct t_Game_Board*/
	LePlateau->nbCities=0;
	LePlateau->nbTracks=0;

	// connectToServer(char* serverName, unsigned int port, char* name);
	connectToServer(serverName,port,name);

	// waitForT2RGame(char* gameType, char* gameName, int* nbCities, int* nbTracks);
	waitForT2RGame(gameType,gameName,&LePlateau->nbCities,&LePlateau->nbTracks);


		/*t_Player YOU;		your info*/
	YOU->nbWagons=45;
	YOU->nbCards=4;
	for (t_color i = 0; i < 10; ++i)
		YOU->TabOfCards[i]=0;
	// t_objective TabOfObjetive[20];

		/*t_Player ENNEMIE;		ennemie info*/
	ENNEMIE->nbWagons=45;
	ENNEMIE->nbCards=4;
	for (t_color i = 0; i < 10; ++i)
		ENNEMIE->TabOfCards[i]=0;
	// t_objective TabOfObjetive[20];

		/*t_GeneralInfo generalInfo;		info of the game*/
	generalInfo->PlayerTurn=1;		
	generalInfo->YourNumber=0;
	//t_color faceUp[5];
	generalInfo->theGameBoard=LePlateau;
	//int TwoPlayer[2];

	t_color cards[4];
	//int tracks[LePlateau->nbTracks*5];
	int* tracks = malloc((LePlateau->nbTracks*5) * sizeof(int));
	for (int i = 0; i < LePlateau->nbTracks*5; ++i)
		tracks[i]=0;

	LePlateau->TabOfTracks=tracks;		/*arrray of the tracks*/
	// getMap(int* tracks, t_color faceUp[5], t_color cards[4]);
	generalInfo->PlayerTurn = getMap(generalInfo->theGameBoard->TabOfTracks, generalInfo->faceUp, cards);
	YOU->TabOfCards[cards[0]]+=1;		/*import the 4 first draw*/
	YOU->TabOfCards[cards[1]]+=1;
	YOU->TabOfCards[cards[2]]+=1;
	YOU->TabOfCards[cards[3]]+=1;


	initObj(YOU,generalInfo);

}