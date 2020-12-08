/*
+----------------------------------------------------+
|                                                    |
|        #######                                     |
|           #    #  ####  #    # ###### #####        |
|           #    # #    # #   #  #        #          |
|           #    # #      ####   #####    #          |
|           #    # #      #  #   #        #          |
|           #    # #    # #   #  #        #          |
|           #    #  ####  #    # ######   #          |
|                                                    |
|                      ######                        |
|      #####  ####     #     # # #####  ######       |
|        #   #    #    #     # # #    # #            |
|        #   #    #    ######  # #    # #####        |
|        #   #    #    #   #   # #    # #            |
|        #   #    #    #    #  # #    # #            |
|        #    ####     #     # # #####  ######       |
|                                                    |
|                                                    |
+----------------------------------------------------+

Authors: T. Hilaire
Licence: GPL

File: TicketToRide.h
	Client API for the TicketToRide game with CGS

Copyright 2020 T. Hilaire
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"


/* global variables used in intern, so the user do not have to pass them once again) */
int nbTr;        		/* number of tracks */
int nbC;				/* number of cities */
char** cityNames;		/* array of city names (used by printCity) */


/* -----------------------
 * Dummy function that does
 * a string copy (exactly as strcpy)
 * but replace the '_' by ' ' in the same time it does the copy
 */
void strCpyReplace(char* dest, const char* src)
{
	while(*src) {
		if (*src != '_')
			*dest++ = *src;
		else
			*dest++ = ' ';
		src++;
	}
}



/* -------------------------------------
 * Initialize connection with the server
 * Quit the program if the connection to the server
 * cannot be established
 *
 * Parameters:
 * - serverName: (string) address of the server
 * - port: (int) port number used for the connection
 * - name: (string) name of the bot : max 20 characters
 */
void connectToServer(char* serverName, unsigned int port, char* name)
{
	connectToCGS(__FUNCTION__, serverName, port, name);
}


/* ----------------------------------
 * Close the connection to the server
 * because we are polite
 *
 */
void closeConnection()
{
	/* free the data */
	char** p = cityNames;
	for(int i=0; i<nbC; i++)
		free(*p++);
	free(cityNames);
	/* close the connection */
	closeCGSConnection(__FUNCTION__);
}


/* ----------------------------------------------------------------
 * Wait for a T2R Game, and retrieve its name and first data
 * (the number of cities and the number of connections)
 *
 * Parameters:
 * - gameType: string (max 200 characters) type of the game we want to play
 *             (empty string for regular game)
 *             "TRAINING xxxx" to play with the bot xxxx
 *             "TOURNAMENT xxxx" to join the tournament xxxx
 *     gameType can also contains extra data in form "key1=value1 key2=value1 ..."
 *     to provide options (to bots)
 *     invalid keys are ignored, invalid values leads to error
 *     the options are:
 *        - 'timeout': allows an define the timeout when training (in seconds)
 *        - 'seed': allows to set the seed of the random generator
 *        - 'start': allows to set who starts ('0' to begin, '1' otherwise)
 *        - 'map': allows to choose a map ('USA' for the moment)
 *     the following bots are available:
 *        - DO_NOTHING (stupid player what withdraw cards)
 *
 * - gameName: char* to get the game Name (should be allocated, max 50 characters),
 *
 * - nbCities: to get the number of cities
 * - nbTracks: to get the number of tracks between the cities
 */
void waitForT2RGame(char* gameType, char* gameName, int* nbCities, int* nbTracks)
{
	char data[10];
	/* wait for a game */
	waitForGame(__FUNCTION__, gameType, gameName, data);

	/* parse the data */
	sscanf(data, "%d %d", nbCities, nbTracks);
	nbTr = *nbTracks;
	nbC = *nbCities;
	cityNames = (char**) malloc(nbC*sizeof(char*));
}


/* ------------------------------------------------------------
 * Get the map, the decks and initial cards and tell who starts
 * the three arrays are filled by the function
 *
 * Parameters:
 * - tracks: array of (5 x number of tracks) integers
 * 		Five integers are used to define a track:
 * 		- (1) id of the 1st city
 * 		- (2) id of the 2nd city
 * 		- (3) length of the track (between 1 and 6)
 * 		- (4) color of the track (MULTICOLOR if any color can be used)
 * 		- (5) color of the 2nd track if the track is double (NONE if the track is not a double track)
 * 	- faceUp: array of 5 t_color giving the 5 face up cards
 * 	- cards: array of 4 t_colors with the initial cards in your hand
 *
 *   (the pointers data MUST HAVE allocated with the right size !!)
 *
 * Returns 0 if you begin, or 1 if the opponent begins
 */
int getMap(int* tracks, t_color faceUp[5], t_color cards[4])
{
	char data[4096];   /* 16 char per track, 256 tracks max */
	int nbchar;
	char *p, **name;
	char city[20];

	/* check parameter */
	if (!tracks)
		dispError(__FUNCTION__, "The parameter `tracks` is NULL !");

	/* wait for a game */
	int ret = getGameData( __FUNCTION__, data, 4096);

	/* copy the city's names */
	p = data;
	name = cityNames;
	for(int i=0; i < nbC; i++){
		sscanf(p, "%s%n", city, &nbchar);
		p += nbchar;
		*name = (char*) malloc(strlen(city)+1);
		strCpyReplace(*(name++), city);
	}

	/* copy the data in the tracks array */
	for(int i=0; i < nbTr; i++){
		sscanf(p, "%d %d %d %d %d %n", tracks, tracks+1, tracks+2, tracks+3, tracks+4, &nbchar);
		tracks += 5;
		p += nbchar;
	}

	/* get the 5 face up cards */
	sscanf(p, "%d %d %d %d %d %n", (int*)faceUp, (int*)faceUp+1, (int*)faceUp+2, (int*)faceUp+3, (int*)faceUp+4, &nbchar);
	p += nbchar;
	/* get the 4 initial cards */
	sscanf(p, "%d %d %d %d", (int*)cards, (int*)cards+1, (int*)cards+2, (int*)cards+3);

    return ret;
}



/* ----------------------
 * Get the opponent move
 *
 * Parameters:
 * - move: a t_move variable, filled by the function
 * - replay: boolean, tells if the player must replay after this move or not
  *
 * Returns:
 * - NORMAL_MOVE for normal move,
 * - WINNING_MOVE for a winning move, -1
 * -  LOOSING_MOVE for a losing (or illegal) move
 * - this code is relative to the opponent (WINNING_MOVE if HE wins, ...)
 */
t_return_code getMove(t_move* move, int* replay)
{
    char moveStr[MAX_GET_MOVE];
	char msg[MAX_MESSAGE];
	int obj[3];
	char* p;
	unsigned int nbchar;

    /* get the move */
    t_return_code ret = getCGSMove(__FUNCTION__, moveStr, msg);

    /* extract result */
	if (ret == NORMAL_MOVE) {
		sscanf(moveStr, "%d%n", (int*) &move->type, &nbchar);
		p = moveStr + nbchar;
		if (move->type == CLAIM_ROUTE) {
			sscanf(p, "%d %d %d %d", &move->claimRoute.city1, &move->claimRoute.city2, (int*)&move->claimRoute.color, &move->claimRoute.nbLocomotives);
			*replay = 0;
		}
		else if (move->type == DRAW_CARD) {
			sscanf(msg, "%d %d %d %d %d %d %d", replay, (int*) &move->drawCard.card, (int*) move->drawCard.faceUp,
				   (int*)move->drawCard.faceUp + 1,
				   (int*)move->drawCard.faceUp + 2, (int*)move->drawCard.faceUp + 3, (int*)move->drawCard.faceUp + 4);
		}
		else if (move->type == DRAW_BLIND_CARD){
			sscanf(msg, "%d", replay);
			move->drawBlindCard.card = NONE;		/* we don't know which card the opponent has */
		}
		else if (move->type == DRAW_OBJECTIVES) {
			*replay = 1;
		}
		else if (move->type == CHOOSE_OBJECTIVES) {
			sscanf(p, "%d %d %d", obj, obj + 1, obj + 2);
			/* get the number of objectives kept by the opponent*/
			move->chooseObjectives.nbObjectives = (obj[0] != 0) + (obj[1] != 0) + (obj[2] != 0);
			*replay =0;
		}
	}

	return ret;
}

/* play the move "claim a route"
 * between two cities, using a color (it should correspond to a track between the two cities)
 * and a certain number of Locomotives
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 */
t_return_code claimRoute(int city1, int city2, int color, int nbLocomotives){
	char msg[256];
	char answer[MAX_GET_MOVE];
	sprintf(msg, "1 %d %d %d %d", city1, city2, color, nbLocomotives);
	return sendCGSMove(__FUNCTION__, msg, answer);
}

/* play the move "draw a blind card"
 * the drawn card is put in card
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 */
t_return_code drawBlindCard(t_color* card){
	char answer[MAX_MESSAGE];
	/* send message */
	t_return_code ret = sendCGSMove(__FUNCTION__, "2", answer);
	/* get card drawn */
	sscanf(answer, "%d", (int*)card);

	return ret;
}


/* play the move "draw a card in the deck"
 * - card: color of the card chosen in the deck (it MUST exist)
 * - deck: array representing the deck (modified by the function)
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 */
t_return_code drawCard(t_color card, t_color deck[5]){
	char answer[MAX_MESSAGE];
	char msg[MAX_GET_MOVE];
	/* send message */
	sprintf(msg, "3 %d", card);
	t_return_code ret = sendCGSMove(__FUNCTION__, msg, answer);
	/* get the new deck */
	sscanf(answer, "%d %d %d %d %d", (int*)deck, (int*)deck+1, (int*)deck+2, (int*)deck+3, (int*)deck+4);

	return ret;
}


/* play the move "draw some objective cards"
 * - obj: array representing the objective card (modified by the function)
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 * -> the move "choose objectives" MUST be play just after !!
 */
t_return_code drawObjectives(t_objective obj[3]){
	char answer[MAX_MESSAGE], *str = answer;
	int nbchar;
	/* send message */
	t_return_code ret = sendCGSMove(__FUNCTION__, "4", answer);
	/* get the new obj */
	t_objective* p = obj;
	for(int i=0;i<3;i++, p++) {
		sscanf(str, "%d %d %d%n", &p->city1, &p->city2, &p->score, &nbchar);
		str += nbchar;
	}

	return ret;
}


/* play the move "choose some objective cards"
 * - objectivesCards: array of boolean indicating which cards are taken
 * 		(0 -> the objective card is not taken)
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 * -> MUST be played after "draw objectives
 */
t_return_code chooseObjectives(int objectiveCards[3]){
	char msg[MAX_GET_MOVE];
	char answer[MAX_GET_MOVE];
	/* send message */
	sprintf(msg, "5 %d %d %d", objectiveCards[0], objectiveCards[1], objectiveCards[2]);
	t_return_code ret = sendCGSMove(__FUNCTION__, msg, answer);

	return ret;
}


/* ----------------------
 * Display the Game
 * in a pretty way (ask the server what to print)
 */
void printMap()
{
	printCGSGame(__FUNCTION__);
}



/* ----------------------------
 * Send a comment to the server
 *
 * Parameters:
 * - comment: (string) comment to send to the server (max 100 char.)
 */
void sendComment(char* comment)
{
    sendCGSComment( __FUNCTION__, comment);
}

/* --------------------
 * Display a city's name
 * Parameters:
 * - city: (int) id of the city
 */
void printCity(int city){
	printf("%s", cityNames[city]);
}

