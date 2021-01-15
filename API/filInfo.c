#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "the_struct.h"
#include "headers.h"



void filOjective(t_GeneralInfo* generalInfo,t_move* move,t_move* move2,t_Player* YOU){
	for (int i = 0; i < 3; ++i)
	{
		if (move2->chooseObjectives.chosen[i] != 0)
		{
			YOU->nbObective = YOU->nbObective + 1;
			if (generalInfo->PlayerTurn==0)
			{
				YOU->TabOfObjetive[YOU->nbObective - 1] = move->drawObjectives.objectives[i];
			}
		}
	}
}

void filBlindCard(t_GeneralInfo* generalInfo,t_move* move,t_Player* YOU){
	if (generalInfo->PlayerTurn==0)
	{
		YOU->TabOfCards[move->drawBlindCard.card] += 1;
	}
		YOU->nbCards += 1;
	
	
}

void filCard(t_move* move,t_Player* YOU,t_GeneralInfo* generalInfo){
	YOU->TabOfCards[move->drawCard.card] += 1;
	YOU->nbCards += 1;

	for (int i = 0; i < 5; ++i)		// refresh the 5 cards visible
	{
		generalInfo->faceUp[i] = move->drawCard.faceUp[i];
	}
}

void filClaimRoad(t_GeneralInfo* generalInfo, t_move* move,t_Player* YOU){
	int j;
	for ( j = 0; j < generalInfo->theGameBoard->nbTracks; ++j)
	{
		if( ((move->claimRoute.city1 == generalInfo->theGameBoard->TabOfTracks[j].city1) && 	/* found the right road in arrayoftracks*/
			(move->claimRoute.city2 == generalInfo->theGameBoard->TabOfTracks[j].city2))
			||	/* or */
			((move->claimRoute.city1 == generalInfo->theGameBoard->TabOfTracks[j].city2) && 
			(move->claimRoute.city2 == generalInfo->theGameBoard->TabOfTracks[j].city1)) )
		{
			if (generalInfo->PlayerTurn==0)	// your turn 
			{
				YOU->nbWagons = YOU->nbWagons - generalInfo->theGameBoard->TabOfTracks[j].length;	/*sub the lenght */

				YOU->TabOfCards[move->claimRoute.color] = YOU->TabOfCards[move->claimRoute.color]			/* sub the nb or card trow, add multicolor if use*/
												 - generalInfo->theGameBoard->TabOfTracks[j].length
												 + move->claimRoute.nbLocomotives;

				YOU->TabOfCards[9] = YOU->TabOfCards[9] - move->claimRoute.nbLocomotives;						/* sub nb of multicolor use*/

				YOU->nbCards = YOU->nbCards	- generalInfo->theGameBoard->TabOfTracks[j].length;		/*nb of cards - the lenght */

				/* we say now if it's your road it's 1
				*	and if it's ennemie's road it's -1 for occupation*/

				generalInfo->theGameBoard->TabOfTracks[j].ocupation = 1;
			
			}
			else if (generalInfo->PlayerTurn==1)
			{
				YOU->nbCards = YOU->nbCards	- generalInfo->theGameBoard->TabOfTracks[j].length;		/*nb of cards - the lenght */

				generalInfo->theGameBoard->TabOfTracks[j].ocupation = -1;

				YOU->nbWagons = YOU->nbWagons - generalInfo->theGameBoard->TabOfTracks[j].length;	/*sub the lenght */
			}
		}
	}

}