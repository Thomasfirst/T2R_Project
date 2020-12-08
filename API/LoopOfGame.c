#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "LoopOfGame.h"
#include "look.h"


void LoopOfGame(int* PlayerBegin){
	t_move move ;//= (t_move*) malloc(sizeof(t_move));
	int replay=1;
	t_return_code TestPassWinLose = 0;
	
	//char ScanAction[100];
	t_color card = 0;

	while(TestPassWinLose == 0){
		printMap();
		if (*PlayerBegin==0)
		{
			printf("on entre you\n");
			// printf("Decrire action\n" );
			// scanf("%s",ScanAction);
			// char* LAction = malloc(strlen(ScanAction)+1);
			// strcpy(LAction,ScanAction);

			// t_return_code drawBlindCard(t_color* card);
			TestPassWinLose = drawBlindCard(&card);
			printf("un drawn a moi\n");

			if(TestPassWinLose!=0)
				break;

			//if(card!=MULTICOLOR)
			TestPassWinLose = drawBlindCard(&card);
			*PlayerBegin=1;	

			printf("deux drawn you\n");
		}

		else {
			if (*PlayerBegin==1)
			{
				printf("on retre lui\n");
				if(TestPassWinLose!=0)
					break;

				// t_return_code getMove(t_move* move, int* replay);
				TestPassWinLose = getMove(&move,&replay);
				printf("un drawn enemie\n");

				if(TestPassWinLose!=0)
					break;
		
				if(replay)
					TestPassWinLose = getMove(&move,&replay);
				*PlayerBegin=0;
				printf("deux drawn enemie\n");	
			}
		}
		//printf("test: %d \n",TestPassWinLose);
		break;
	}
}