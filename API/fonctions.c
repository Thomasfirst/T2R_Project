#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "the_struct.h"
#include "headers.h"


t_return_code playTheMove(t_move* move){	/* play a move given*/
	t_return_code TestPassWinLose = 0;

	if (move->type==1)
	{
		TestPassWinLose = claimRoute(move->claimRoute.city1,move->claimRoute.city2,move->claimRoute.color,move->claimRoute.nbLocomotives);
	}

	if (move->type==3)
	{
		TestPassWinLose=drawCard(move->drawCard.card, move->drawCard.faceUp );
	}

	if (move->type==2)
	{
		TestPassWinLose=drawBlindCard(&move->drawBlindCard.card);
	}

	if (move->type==4)
	{
		TestPassWinLose = drawObjectives(move->drawObjectives.objectives);	
	}	

	if (move->type==5)
	{
		TestPassWinLose = chooseObjectives(move->chooseObjectives.chosen);
		move->chooseObjectives.nbObjectives = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (move->chooseObjectives.chosen[i] != 0)
			{
				move->chooseObjectives.nbObjectives = move->chooseObjectives.nbObjectives + 1;
			}
		}
	}
	
	return TestPassWinLose;
}