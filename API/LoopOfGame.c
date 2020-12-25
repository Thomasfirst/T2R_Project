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

	t_road roadToPlace;

	int ScanAction = 0;		// for claim a road 
	int ScanAction2 = 0;	

	while(TestPassWinLose == 0){
		printMap();
		roadToPlace = algo_one_road( YOU->TabOfObjetive[0], generalInfo);

		int test = chooseColor(YOU->TabOfObjetive[0], generalInfo, YOU);

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




void LoopOfGameAuto(t_GeneralInfo* generalInfo,t_Player* YOU,t_Player* ENNEMIE){
	// t_move move ;//
	t_move* move = malloc(sizeof(t_move));
	t_move* move2 = malloc(sizeof(t_move));

	int replayEnnemie=1;

	int replayYou=1;

	t_return_code TestPassWinLose = 0;

	t_road roadToPlace;

	int colorIfNoColor;

	int finishObjective = 0;

	int colorToDraw = 0; 

	while(TestPassWinLose == 0){
		printMap();

		replayYou=2;

		for (int iObj = 0; iObj < YOU->nbObective; ++iObj)		/* complete objective */
		{
			if(finishObjective==1)
				break;
			roadToPlace = algo_one_road( YOU->TabOfObjetive[iObj], generalInfo);
			colorToDraw = chooseColorIfNotTheFirst( YOU->TabOfObjetive[iObj], generalInfo);
			colorIfNoColor = chooseColor( YOU->TabOfObjetive[iObj], generalInfo, YOU);
			

			if ( (roadToPlace.city2 == -2) && (roadToPlace.city1 == -2))	/* the last objective complete*/
			{
				if (iObj -1 < 0)
				{
					finishObjective = 1;		/* all objective finish*/
					break;
				}
				roadToPlace = algo_one_road( YOU->TabOfObjetive[iObj -1], generalInfo);	/*next objective*/
				colorToDraw = chooseColorIfNotTheFirst( YOU->TabOfObjetive[iObj - 1], generalInfo);
				colorIfNoColor = chooseColor( YOU->TabOfObjetive[iObj -1], generalInfo, YOU);
				break;
			}
		}
		

		if (generalInfo->PlayerTurn==0)
		{
			if (finishObjective == 0)
			{
			
				/* claim road */
				if ((roadToPlace.color1 == 9)&&(colorIfNoColor != 0))	/* if no color*/
				{
					
					if ((YOU->TabOfCards[colorIfNoColor] >= roadToPlace.length) &&(YOU->nbWagons >= roadToPlace.length))
					{
						move->type=1;

						move->claimRoute.city1 = roadToPlace.city1;
						move->claimRoute.city2 = roadToPlace.city2;
						move->claimRoute.color = colorIfNoColor;
						move->claimRoute.nbLocomotives = 0;	

						TestPassWinLose = playTheMove(move);
						filClaimRoad(generalInfo,move,YOU);
						replayYou = 0;
					}
				}

				else if ((YOU->TabOfCards[roadToPlace.color1] >= roadToPlace.length)&&(YOU->nbWagons >= roadToPlace.length))	/*if color1 for the road*/
				{
					move->type=1;

					move->claimRoute.city1 = roadToPlace.city1;
					move->claimRoute.city2 = roadToPlace.city2;
					move->claimRoute.color = roadToPlace.color1;
					move->claimRoute.nbLocomotives = 0;	

					TestPassWinLose = playTheMove(move);
					filClaimRoad(generalInfo,move,YOU);
					replayYou = 0;
				}
				else if ((YOU->TabOfCards[roadToPlace.color1] + YOU->TabOfCards[9] >= roadToPlace.length)&&(YOU->nbWagons >= roadToPlace.length))	/*if color1 + multicilorCards for the road*/
				{
					move->type=1;

					move->claimRoute.city1 = roadToPlace.city1;
					move->claimRoute.city2 = roadToPlace.city2;
					move->claimRoute.color = roadToPlace.color1;
					move->claimRoute.nbLocomotives = YOU->TabOfCards[9];	

					TestPassWinLose = playTheMove(move);
					filClaimRoad(generalInfo,move,YOU);
					replayYou = 0;
				}

				else if ((((YOU->TabOfCards[roadToPlace.color2] >= roadToPlace.length) 
						&&(YOU->nbWagons >= roadToPlace.length))	
						&& (roadToPlace.color2 != 0))/*if color2 + multicilorCards for the road*/
						&& (roadToPlace.color2 != 9))
				{
					move->type=1;

					move->claimRoute.city1 = roadToPlace.city1;
					move->claimRoute.city2 = roadToPlace.city2;
					move->claimRoute.color = roadToPlace.color2;
					move->claimRoute.nbLocomotives = 0;	

					TestPassWinLose = playTheMove(move);
					filClaimRoad(generalInfo,move,YOU);
					replayYou = 0;
				}
				else if ((((YOU->TabOfCards[roadToPlace.color2] + YOU->TabOfCards[9] >= roadToPlace.length)
						&&(YOU->nbWagons >= roadToPlace.length))
						&& (roadToPlace.color2 != 0))	/*if color2 for the road*/
						&& (roadToPlace.color2 != 9))
				{
					move->type=1;

					move->claimRoute.city1 = roadToPlace.city1;
					move->claimRoute.city2 = roadToPlace.city2;
					move->claimRoute.color = roadToPlace.color2;
					move->claimRoute.nbLocomotives = YOU->TabOfCards[9];	

					TestPassWinLose = playTheMove(move);
					filClaimRoad(generalInfo,move,YOU);
					replayYou = 0;
				}

				/*-----*/
				/* draw the cards */
				
				if (replayYou == 2)		/* draw the color we need now for the road*/
				{
					for (int i = 0; i < 5; ++i)
					{
						if( ((generalInfo->faceUp[i] == roadToPlace.color1) || (generalInfo->faceUp[i] == roadToPlace.color2))
							 && (generalInfo->faceUp[i] != 9) )
						{
							move->type=3;
							move->drawCard.card = generalInfo->faceUp[i];
							lookMove(move);
							TestPassWinLose = playTheMove(move);
							filCard(move,YOU,generalInfo);
							replayYou -= 1;	/* 2 main you can play again*/
							lookMove(move);
							break;
						}
					}
					if (replayYou==1)	/* 2nd draw */
					{
						for (int i = 0; i < 5; ++i)
						{
							if( ((generalInfo->faceUp[i] == roadToPlace.color1) || (generalInfo->faceUp[i] == roadToPlace.color2))
								&& (generalInfo->faceUp[i] != 9) )
							{
								move->type=3;
								move->drawCard.card = generalInfo->faceUp[i];
								lookMove(move);
								TestPassWinLose = playTheMove(move);
								filCard(move,YOU,generalInfo);
								replayYou -= 1;	/* 2 main you can play again*/
								lookMove(move);printf("le nb2\n");
								break;
							}
						}
					}	
				}


				/*-----*/

				if ((replayYou == 2)&& (colorToDraw != 0))	/* drawn an other road we need for objective*/
				{
					printf("%d colorToDraw\n", colorToDraw);
					for (int i = 0; i < 5; ++i) /*found a card we need*/
					{
						if ((generalInfo->faceUp[i] == colorToDraw))
						{
							move->type=3;
							move->drawCard.card = generalInfo->faceUp[i];
							lookMove(move);
							TestPassWinLose = playTheMove(move);
							filCard(move,YOU,generalInfo);
							replayYou -= 1;	/* 2 main you can play again*/
							break;
						}
					}
					// if ((replayYou==1)&& (colorToDraw != 0))	/* 2nd draw  add 50% effectivness*/
					// {
					// 	for (int i = 0; i < 5; ++i)
					// 	{
					// 		if ((generalInfo->faceUp[i] == colorToDraw) || (generalInfo->faceUp[i] == colorToDraw))
					// 		{
					// 			move->type=3;
					// 			move->drawCard.card = generalInfo->faceUp[i];
					// 			lookMove(move);
					// 			TestPassWinLose = playTheMove(move);
					// 			filCard(move,YOU,generalInfo);
					// 			replayYou -= 1;	/* end move*/
					// 			break;
					// 		}
					// 	}
					// }	
				}
				else if ((replayYou == 1)&& (colorToDraw != 0))	/* if we have only 1 move found a card we need*/
				{
					printf("%d colorToDraw\n", colorToDraw);
					for (int i = 0; i < 5; ++i)
					{
						if ((generalInfo->faceUp[i] == colorToDraw) )
						{
							move->type=3;
							move->drawCard.card = generalInfo->faceUp[i];
							lookMove(move);
							TestPassWinLose = playTheMove(move);
							filCard(move,YOU,generalInfo);
							replayYou -= 1;	/* end move*/
							break;
						}
					}
				}


				/*-----*/

				if (replayYou == 2)	/* draw blind if ne other chose x2 */
				{
					move->type=2;
					TestPassWinLose = playTheMove(move);
					filBlindCard(generalInfo,move,YOU);	
					lookMove(move);

					replayYou -= 1;

					move->type=2;
					TestPassWinLose = playTheMove(move);
					filBlindCard(generalInfo,move,YOU);	
					lookMove(move);

					replayYou -= 1;
				}
				if (replayYou == 1) /* draw blind if ne other chose x1 */
				{
					move->type=2;
					TestPassWinLose = playTheMove(move);
					filBlindCard(generalInfo,move,YOU);	
					lookMove(move);

					replayYou -= 1;
				}
			
			}

			int replayToEnd = 2;// 2 its for 2 move
			int the_end;
			if (finishObjective == 1)
			{
				printf("OMG CA FONCTIONNE \nOMG CA FONCTIONNE \nOMG CA FONCTIONNE \n");


				the_end = finishmove(move, generalInfo,  YOU,  ENNEMIE,  &replayToEnd);
				printf("the_end = %d and replayToEnd= %d \n", the_end, replayToEnd);
				lookMove(move);

				TestPassWinLose = playTheMove(move);

				if (move->type == 1)
				{
					filClaimRoad(generalInfo,move,YOU);
				}
				if (move->type == 2)
				{
					filBlindCard(generalInfo,move,YOU);
				}
				if (move->type == 3)
				{
					filCard(move,YOU,generalInfo);
				}
					

				if (replayToEnd == 1)
				{
					the_end = finishmove(move, generalInfo,  YOU,  ENNEMIE,  &replayToEnd);
					printf("the_end = %d and replayToEnd= %d \n", the_end, replayToEnd);
					lookMove(move);

					TestPassWinLose = playTheMove(move);
					if (move->type == 1)
					{
						filClaimRoad(generalInfo,move,YOU);
					}
					if (move->type == 2)
					{
						filBlindCard(generalInfo,move,YOU);
					}
					if (move->type == 3)
					{
						filCard(move,YOU,generalInfo);
					}	
				}
			}


				//-------------------

			generalInfo->PlayerTurn=1;	
		}

		else {
			if (generalInfo->PlayerTurn==1)
			{
				printf("ENNEMIE\n");
				// t_return_code getMove(t_move* move, int* replay);
				TestPassWinLose = getMove(move,&replayEnnemie);
				lookMove(move);
				if (move->type==1)
				{
					filClaimRoad(generalInfo,move,ENNEMIE);
					if (replayEnnemie !=0)
					{
						printf("L'ENNEMIE TRICHE !!!!!\n");
						TestPassWinLose =1;
					}
				}
				else if (move->type==2)
				{
					filBlindCard(generalInfo,move,ENNEMIE);
				}
				else if (move->type==3)
				{
					filCard(move,ENNEMIE,generalInfo);	
				}
				else if (move->type==4)
				{
					replayEnnemie=1;	//take objectiv
				}

		
				if(replayEnnemie){
					TestPassWinLose = getMove(move2,&replayEnnemie);
					lookMove(move2);

					if (move2->type==1)
					{
						filClaimRoad(generalInfo,move2,ENNEMIE);
						printf("L'ENNEMIE TRICHE 22!!!!!\n" );
						TestPassWinLose =1;

					}
					else if (move2->type==2)
					{
						filBlindCard(generalInfo,move2,ENNEMIE);
					}
					else if (move2->type==3)
					{
						filCard(move2,ENNEMIE,generalInfo);	
					}
					else if (move2->type==5)
					{
						filOjective(generalInfo,move,move2,ENNEMIE);;
					}
				}

				generalInfo->PlayerTurn=0;

			}
		}
	}
	free(move);
	free(move2);
}