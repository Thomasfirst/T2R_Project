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


#ifndef __API_CLIENT_T2R__
#define __API_CLIENT_T2R__
#include "clientAPI.h"


/* colors' definitions */
typedef enum {
	NONE = 0,       		/* used to indicate a track is not double */
	PURPLE,
	WHITE,
	BLUE,
	YELLOW,
	ORANGE,
	BLACK,
	RED,
	GREEN,
	MULTICOLOR 				/* used for the locomotive card (joker) or for a track that can accept any color */
} t_color;

/* different possible moves */
typedef enum
{
	CLAIM_ROUTE = 1,
	DRAW_BLIND_CARD = 2,
	DRAW_CARD = 3,
	DRAW_OBJECTIVES = 4,
	CHOOSE_OBJECTIVES = 5
} t_typeMove;

/* an objective card */
typedef struct{
	int city1, city2;
	int score;
} t_objective;

/* a 'claim a route' move */
typedef struct{
	int city1, city2;		/* id of the two cities */
	t_color color;			/* main color of the track */
	int nbLocomotives;		/* number of Locomotives used */
} t_claimRouteMove;

/* a 'draw a card' move */
typedef struct{
	t_color card;			/* color of the card taken */
	t_color faceUp[5];		/* returned face up cards */
} t_drawCard;

/* a 'draw blind card' move */
typedef struct{
	t_color card;			/* returned card */
} t_drawBlindCard;

/* a 'draw objectives' move */
typedef struct{
	t_objective objectives[3];	/* returned objectives */
} t_drawObjectives;

/* a 'choose an objective' move */
typedef struct{
	int nbObjectives;			/* returned number of objectives */
	int chosen[3];				/* array of boolean, to tell which objective we choose */
} t_chooseObjectives;

/* a move */
typedef struct{
	t_typeMove type;
	union{
		t_claimRouteMove claimRoute;
		t_drawCard drawCard;
		t_drawBlindCard drawBlindCard;
		t_drawObjectives drawObjectives;
		t_chooseObjectives chooseObjectives;
	};
} t_move;


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
void connectToServer(char* serverName, unsigned int port, char* name);



/* ----------------------------------
 * Close the connection to the server
 * because we are polite
 *
 */
void closeConnection();


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
void waitForT2RGame(char* gameType, char* gameName, int* nbCities, int* nbTracks);


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
int getMap(int* tracks, t_color faceUp[5], t_color cards[4]);



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
t_return_code getMove(t_move* move, int* replay);


/* play the move "claim a route"
 * between two cities, using a color (it should correspond to a track between the two cities)
 * and a certain number of Locomotives
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 */
t_return_code claimRoute(int city1, int city2, int color, int nbLocomotives);


/* play the move "draw a blind card"
 * the drawn card is put in card
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 */
t_return_code drawBlindCard(t_color* card);


/* play the move "draw a card in the deck"
 * - card: color of the card chosen in the deck (it MUST exist)
 * - deck: array representing the deck (modified by the function)
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 */
t_return_code drawCard(t_color card, t_color deck[5]);


/* play the move "draw some objective cards"
 * - obj: array representing the objective card (modified by the function)
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 * -> the move "choose objectives" MUST be play just after !!
 */
t_return_code drawObjectives(t_objective obj[3]);

/* play the move "choose some objective cards"
 * - objectivesCards: array of boolean indicating which cards are taken
 * 		(0 -> the objective card is not taken)
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 * -> MUST be played after "draw objectives
 */
t_return_code chooseObjectives(int objectiveCards[3]);

/* ----------------------
 * Display the Game
 * in a pretty way (ask the server what to print)
 */
void printMap();



/* ----------------------------
 * Send a comment to the server
 *
 * Parameters:
 * - comment: (string) comment to send to the server (max 100 char.)
 */
void sendComment(char* comment);


/* --------------------
 * Display a city's name
 * Parameters:
 * - city: (int) id of the city
 */
void printCity(int city);

#endif
