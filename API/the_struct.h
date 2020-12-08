#ifndef __THE_STRUCT_H__
#define __THE_STRUCT_H__
#include "TicketToRideAPI.h"
#include "clientAPI.h"


typedef struct{		/* Nb ville Nb route tab des route*/
	int nbCities;
	int nbTracks;
	int* TabOfTracks;
} t_Game_Board;

typedef struct{		/* player info*/
	int nbWagons;
	int nbCards;
	t_color TabOfCards[10];		/*{NONE,PURPLE,WHITE,BLUE,YELLOW,ORANGE,BLACK,RED,GREEN,MULTICOLOR};*/
	t_objective TabOfObjetive[20];
} t_Player;

typedef struct{		/* player info*/
	int PlayerTurn;		/* player who is the turn*/
	int YourNumber;		/* your number normally you are 0*/
	t_color faceUp[5];
	t_Game_Board theGameBoard;
	int TwoPlayer[2];
} t_GeneralInfo;



#endif