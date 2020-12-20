#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "headers.h"




void LoopOfGame(t_GeneralInfo* generalInfo,t_Player* YOU,t_Player* ENNEMIE){
	// t_move move ;//
	t_move* move = malloc(sizeof(t_move));
	t_move* move2 = malloc(sizeof(t_move));

	int replay=1;
	t_return_code TestPassWinLose = 0;

	int ScanAction = 0;		// for claim a road 
	int ScanAction2 = 0;	

	while(TestPassWinLose == 0){
		printMap();
		if (generalInfo->PlayerTurn==0)
		{
			printf("Decrire action\n" );
			printf("1 pour claimRoute; 2 pour drawBlindCard; 3 pour drawCard; 4 pour drawObjectives\n" );
			scanf("%d",&ScanAction);
			
			if (ScanAction==1)		//claim road
			{
				move->type=1;
				printf("Nom ville depart:\n");		//choose your move
				scanf("%d",&move->claimRoute.city1);
				printf("Nom ville arrive:\n");
				scanf("%d",&move->claimRoute.city2);
				printf("couleur:\n");
				scanf("%d",&move->claimRoute.color);
				printf("Nonbre multicolor:\n");
				scanf("%d",&move->claimRoute.nbLocomotives);

				TestPassWinLose = playTheMove(move);
				filClaimRoad(generalInfo,move,YOU);
			}

			if (ScanAction==3)		//draw card
			{
				move->type=3;
				printf("couleur de la carte voulu:\n");		//choose your color
				scanf("%d",&move->drawCard.card);
				TestPassWinLose = playTheMove(move);
				filCard(move,YOU,generalInfo);

				if (move->drawCard.card!=9)		//cant replay if multicolor
				{
					printf("Decrire action\n" );
					printf("1 pour drawCard; 2 pour drawBlindCard\n" );
					scanf("%d",&ScanAction2);

					if(ScanAction2==1)
					{
						printf("couleur de la carte voulu:\n");		//choose your color
						scanf("%d",&move->drawCard.card);
						TestPassWinLose = playTheMove(move);
						filCard(move,YOU,generalInfo);				//fil your cards with what you draw
					}
					else
					{
						move->type=2;								//draw blind 
						TestPassWinLose = playTheMove(move);
						filBlindCard(generalInfo,move,YOU);						//fil your cards with what you drawblinb
					}
				}
			}

			if (ScanAction==2)		//draw blind card
			{
				move->type=2;
				TestPassWinLose = playTheMove(move);		//next what did u do?
				filBlindCard(generalInfo,move,YOU);						// fil your cards with what you drawblind

				printf("Decrire action\n" );
				printf("1 pour drawCard; 2 pour drawBlindCard\n" );
				scanf("%d",&ScanAction2);
				if(ScanAction2==1)
				{
					move->type=3;
					printf("couleur de la carte voulu:\n");		//choose your color
					scanf("%d",&move->drawCard.card);
					TestPassWinLose = playTheMove(move);
					filCard(move,YOU,generalInfo);				//fil your cards with what you draw
				}
				else
				{
					TestPassWinLose = playTheMove(move);		//draw blind 
					filBlindCard(generalInfo,move,YOU);						//fil your cards with what you drawblinb
				}
			}

			if (ScanAction==4)		//take ojective
			{
				move->type=4;
				TestPassWinLose = playTheMove(move);

				for (int i = 0; i < 3; ++i)
				{
					printf("objectif:%d ville:%d a ville:%d valeur:%d \n",i,move->drawObjectives.objectives[i].city1,
																			move->drawObjectives.objectives[i].city2,
																			move->drawObjectives.objectives[i].score);
				}

				move2->type=5;		//chose objective
				printf("choisir 1 valider 0 jeter pour chaque objectifs\n");
				scanf("%d",&move2->chooseObjectives.chosen[0]);
				scanf("%d",&move2->chooseObjectives.chosen[1]);
				scanf("%d",&move2->chooseObjectives.chosen[2]);

				TestPassWinLose = playTheMove(move2);
				printf("Vous avez pris %d objectifs\n",move2->chooseObjectives.nbObjectives );

				filOjective(generalInfo,move,move2,YOU);	//fil you with the objeective

			}
			if (ScanAction==5)
			{
				break;
			}

			generalInfo->PlayerTurn=1;	
		}

		else {
			if (generalInfo->PlayerTurn==1)
			{
				printf("tour ENNEMIE\n");
				// t_return_code getMove(t_move* move, int* replay);
				TestPassWinLose = getMove(move,&replay);
				lookMove(move);
				if (move->type==1)
				{
					filClaimRoad(generalInfo,move,ENNEMIE);
				}
				if (move->type==2)
				{
					filBlindCard(generalInfo,move,ENNEMIE);
				}
				if (move->type==3)
				{
					filCard(move,ENNEMIE,generalInfo);	
				}
				if (move->type==4)
				{
					replay=1;	//take objectiv
				}

		
				if(replay)
					TestPassWinLose = getMove(move2,&replay);

				generalInfo->PlayerTurn=0;
				lookMove(move2);
				if (move2->type==1)
				{
					filClaimRoad(generalInfo,move2,ENNEMIE);
				}
				if (move2->type==2)
				{
					filBlindCard(generalInfo,move2,ENNEMIE);
				}
				if (move2->type==3)
				{
					filCard(move2,ENNEMIE,generalInfo);	
				}
				if (move2->type==5)
				{
					filOjective(generalInfo,move,move2,ENNEMIE);;
				}
			}
		}
	}
	free(move);
	free(move2);
}