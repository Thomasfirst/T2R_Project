#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "the_struct.h"
#include "headers.h"


void initObj(t_Player* YOU,t_GeneralInfo* generalInfo,t_Player* ENNEMIE){		// now take the two objecctive with the less points
	int replay=1;
	t_move* move = malloc(sizeof(t_move));
	t_move* move2 = malloc(sizeof(t_move));

	t_return_code TestPassWinLose = 0;
	//t_objective* obj = malloc(3 * sizeof(t_objective));

	if (generalInfo->PlayerTurn == 1)
	{
		// t_return_code getMove(t_move* move, int* replay);
		TestPassWinLose = getMove(move,&replay);
		if(replay)
			TestPassWinLose = getMove(move2,&replay);
		generalInfo->PlayerTurn=0;
		filOjective(generalInfo,move,move2,ENNEMIE);
		lookMove(move);


		//t_return_code validity = drawObjectives(t_objective obj[3]);
		move->type=4;
		TestPassWinLose = playTheMove(move);

		// TestPassWinLose = drawObjectives(obj);		
		// int objectiveCards[3];
		if (move->drawObjectives.objectives[0].score < move->drawObjectives.objectives[1].score){		// Take the 2 obj whith the less points
			move2->chooseObjectives.chosen[0]=1;
			YOU->TabOfObjetive[0]=move->drawObjectives.objectives[0];
			if (move->drawObjectives.objectives[1].score < move->drawObjectives.objectives[2].score){
				move2->chooseObjectives.chosen[1]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[1];
				move2->chooseObjectives.chosen[2]=0;
			}
			else{
				move2->chooseObjectives.chosen[1]=0;
				move2->chooseObjectives.chosen[2]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[2];
			}
		}
		else{
			move2->chooseObjectives.chosen[1]=1;
			YOU->TabOfObjetive[0]=move->drawObjectives.objectives[1];
			if (move->drawObjectives.objectives[0].score < move->drawObjectives.objectives[2].score){
				move2->chooseObjectives.chosen[0]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[0];
				move2->chooseObjectives.chosen[2]=0;
			}
			else{
				move2->chooseObjectives.chosen[0]=0;
				move2->chooseObjectives.chosen[2]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[2];
			}
		}

		//t_return_code chooseObjectives(int objectiveCards[3]);
		//TestPassWinLose = chooseObjectives(objectiveCards);
		move2->type=5;
		TestPassWinLose = playTheMove(move2);

		YOU->nbObective = move2->chooseObjectives.nbObjectives;	//update nb of objectiv
		generalInfo->PlayerTurn=1;

	}

	else{
		//t_return_code validity = drawObjectives(t_objective obj[3]);
		move->type=4;
		TestPassWinLose = playTheMove(move);

		// TestPassWinLose = drawObjectives(obj);		
		// int objectiveCards[3];
		if (move->drawObjectives.objectives[0].score < move->drawObjectives.objectives[1].score){		// Take the 2 obj whith the less points
			move2->chooseObjectives.chosen[0]=1;
			YOU->TabOfObjetive[0]=move->drawObjectives.objectives[0];
			if (move->drawObjectives.objectives[1].score < move->drawObjectives.objectives[2].score){
				move2->chooseObjectives.chosen[1]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[1];
				move2->chooseObjectives.chosen[2]=0;
			}
			else{
				move2->chooseObjectives.chosen[1]=0;
				move2->chooseObjectives.chosen[2]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[2];
			}
		}
		else{
			move2->chooseObjectives.chosen[1]=1;
			YOU->TabOfObjetive[0]=move->drawObjectives.objectives[1];
			if (move->drawObjectives.objectives[0].score < move->drawObjectives.objectives[2].score){
				move2->chooseObjectives.chosen[0]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[0];
				move2->chooseObjectives.chosen[2]=0;
			}
			else{
				move2->chooseObjectives.chosen[0]=0;
				move2->chooseObjectives.chosen[2]=1;
				YOU->TabOfObjetive[1]=move->drawObjectives.objectives[2];
			}
		}

		//t_return_code chooseObjectives(int objectiveCards[3]);
		//TestPassWinLose = chooseObjectives(objectiveCards);
		move2->type=5;
		TestPassWinLose = playTheMove(move2);

		YOU->nbObective = move2->chooseObjectives.nbObjectives;	//update nb of objectiv
		generalInfo->PlayerTurn=1;

	}

	if (TestPassWinLose!=0)
	{
		printf("probleme il y a un vainceur/perdant %d \n", TestPassWinLose);
	}
	//free(obj);
	free(move);
	free(move2);
}