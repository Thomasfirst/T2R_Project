#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "LoopOfGame.h"
#include "the_struct.h"

void filInfoPlayer(t_Player* Player,int nbWagons,int nbCards,t_color TabOfCards[10],t_objective TabOfObjetive[20]){
	Player->nbWagons=Player->nbWagons-nbWagons;
	Player->nbCards=Player->nbCards+nbCards;
	Player->TabOfCards
}