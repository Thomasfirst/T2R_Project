#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "the_struct.h"
#include "headers.h"

int distanceMin(int* D, int* visite, t_GeneralInfo* generalInfo){
	int min = 999;
	int indice_min=0;

	for (int ire = 0; ire < generalInfo->theGameBoard->nbCities; ++ire)
	{
		if ((visite[ire] == 0) && (D[ire] < min))
		{
			min = D[ire];
			indice_min = ire;
		}
	}
	return indice_min;
}

int* algo(t_objective objective, t_GeneralInfo* generalInfo){
	int src = objective.city1;
	int i = objective.city2;
	int G[generalInfo->theGameBoard->nbCities][generalInfo->theGameBoard->nbCities];	/*tab of 2D for all the city*/

	for (int k = 0; k < generalInfo->theGameBoard->nbCities; ++k)		/* initialisation at 999*/
	{
		for (int j = 0; j < generalInfo->theGameBoard->nbCities; ++j)
		{
			G[k][j] = 999;
		}
	}

	for (int tour = 0; tour < generalInfo->theGameBoard->nbTracks; ++tour)		/* 999 replace by the length for city*/
		{
			if (generalInfo->theGameBoard->TabOfTracks[tour].ocupation != -1)
			{
				G[generalInfo->theGameBoard->TabOfTracks[tour].city1][generalInfo->theGameBoard->TabOfTracks[tour].city2] = 
				generalInfo->theGameBoard->TabOfTracks[tour].length;
				
				G[generalInfo->theGameBoard->TabOfTracks[tour].city2][generalInfo->theGameBoard->TabOfTracks[tour].city1] = 
				generalInfo->theGameBoard->TabOfTracks[tour].length;
			}
		}

	int visite[generalInfo->theGameBoard->nbCities];
	int u = 0;

	int D[generalInfo->theGameBoard->nbCities];
	int* prec = malloc(generalInfo->theGameBoard->nbCities * sizeof(int));

	for (int h = 0; h < generalInfo->theGameBoard->nbCities; ++h)
	{
		D[h] = 999;
		visite[h] = 0;
	}

	D[src] = 0;

	while( u != i)
	{
		u = distanceMin(D, visite, generalInfo);
		visite[u] = 1;
		for (int v = 0; v < generalInfo->theGameBoard->nbCities; ++v)
		{
			if ( (visite[v]==0) && (G[u][v] < 999) && (D[u] + G[u][v] < D[v]) )
			{
				D[v] = D[u] + G[u][v];
				prec[v] = u;
			}
		}
		
	}

	/* look the traject*/
	int vtest = i;
	while( vtest != src)
	{
		printf("%d à %d \n", prec[vtest], vtest);
		vtest = prec[vtest];
	}

	
	return prec;
}

t_road algo_one_road(t_objective objective, t_GeneralInfo* generalInfo){	/* give the road to claim*/

	int v = objective.city2;
	t_road roadToPlace;
	roadToPlace.city1 = -1;
	int* prec = algo(objective, generalInfo);


	while(roadToPlace.city1 == -1)	/*while we have the road*/
	{
		for (int tour = 0; tour < generalInfo->theGameBoard->nbTracks; ++tour)
		{
			if (( (generalInfo->theGameBoard->TabOfTracks[tour].city1 == v ) 
				&& (generalInfo->theGameBoard->TabOfTracks[tour].city2 == prec[v] ))
				|| ((generalInfo->theGameBoard->TabOfTracks[tour].city1 == prec[v] ) 
				&& (generalInfo->theGameBoard->TabOfTracks[tour].city2 == v ) ))
			{
				if (generalInfo->theGameBoard->TabOfTracks[tour].ocupation == 1)
				{
					if (prec[v] == objective.city1)
					{
						roadToPlace.city1 = -2;
						roadToPlace.city2 = -2;
						printf("fin objective !!!\n");
						break;
					}
					v = prec[v];	/* pass to the next road*/
					break;
				}
				else
				{	/* the road we need to take next*/
					roadToPlace.city1 = v;
					roadToPlace.city2 = prec[v];
					roadToPlace.length = generalInfo->theGameBoard->TabOfTracks[tour].length;
					roadToPlace.ocupation = generalInfo->theGameBoard->TabOfTracks[tour].ocupation;
					roadToPlace.color1 = generalInfo->theGameBoard->TabOfTracks[tour].color1;
					roadToPlace.color2 = generalInfo->theGameBoard->TabOfTracks[tour].color2;
				}
			}
		}
	}

	printf("%d à %d long%d ocup%d color%d color%d\n", roadToPlace.city1 ,
														roadToPlace.city2,
														roadToPlace.length,
														roadToPlace.ocupation,
														roadToPlace.color1,
														roadToPlace.color2);
	

	return roadToPlace;
}

int chooseColor(t_objective objective, t_GeneralInfo* generalInfo, t_Player* YOU){	/* if no color for road choose the best one to use */
	int v = objective.city2;
	t_road roadToPlace;
	int* prec = algo(objective, generalInfo);

	int maxColorCards[10];
	for (int i = 0; i < 10; ++i)
	{
		maxColorCards[i]=0;
	}

	int max=0;
	int indiceMax=0;


	while(roadToPlace.city2 != objective.city1)		/* look the road for objective*/
	{
		for (int tour = 0; tour < generalInfo->theGameBoard->nbTracks; ++tour)
		{
			if (( (generalInfo->theGameBoard->TabOfTracks[tour].city1 == v ) 
				&& (generalInfo->theGameBoard->TabOfTracks[tour].city2 == prec[v] ))
				|| ((generalInfo->theGameBoard->TabOfTracks[tour].city1 == prec[v] ) 
				&& (generalInfo->theGameBoard->TabOfTracks[tour].city2 == v ) ))
			{
				if (generalInfo->theGameBoard->TabOfTracks[tour].ocupation == 0)	/*don't need if we have the road*/
				{
					roadToPlace.city1 = v;
					roadToPlace.city2 = prec[v];
					roadToPlace.length = generalInfo->theGameBoard->TabOfTracks[tour].length;
					roadToPlace.ocupation = generalInfo->theGameBoard->TabOfTracks[tour].ocupation;
					roadToPlace.color1 = generalInfo->theGameBoard->TabOfTracks[tour].color1;
					roadToPlace.color2 = generalInfo->theGameBoard->TabOfTracks[tour].color2;

						/* mark the color we going to use */ 
					maxColorCards[generalInfo->theGameBoard->TabOfTracks[tour].color1] += 1;
					maxColorCards[generalInfo->theGameBoard->TabOfTracks[tour].color2] += 1;
				}

				if ((prec[v] == objective.city1) && (generalInfo->theGameBoard->TabOfTracks[tour].ocupation == 1))
				{
					printf("nouveau objective pas de couleur\n\n");
					return 0;
				}

				v = prec[v];	//next
			}
		}
	}

	for (int i = 1; i < 9; ++i)
	{
		if( (YOU->TabOfCards[i] > max) && (maxColorCards[i] == 0) )		/* look for the card we have the most and dont need*/
		{
			max = YOU->TabOfCards[i];
			indiceMax = i;
		} 
	}

	max = 0;

	if (indiceMax == 0)
	{
		for (int i = 1; i < 9; ++i)
		{
			if (YOU->TabOfCards[i] > max)
			{
				indiceMax = i;
				max = YOU->TabOfCards[i];
			}
		}
	}

	free(prec);

	printf("%d couleur a utiliser\n\n", indiceMax);
	return indiceMax;

}

int chooseColorIfNotTheFirst(t_objective objective, t_GeneralInfo* generalInfo){
	int v = objective.city2;
	t_road roadToPlace;
	int* prec = algo(objective, generalInfo);

	int maxColorCards[10];
	for (int i = 0; i < 10; ++i)
	{
		maxColorCards[i]=0;
	}

	int indice=0;


	while(roadToPlace.city2 != objective.city1)		/* look the road for objective*/
	{
		for (int tour = 0; tour < generalInfo->theGameBoard->nbTracks; ++tour)
		{
			if (( (generalInfo->theGameBoard->TabOfTracks[tour].city1 == v ) 
				&& (generalInfo->theGameBoard->TabOfTracks[tour].city2 == prec[v] ))
				|| ((generalInfo->theGameBoard->TabOfTracks[tour].city1 == prec[v] ) 
				&& (generalInfo->theGameBoard->TabOfTracks[tour].city2 == v ) ))
			{
				if (generalInfo->theGameBoard->TabOfTracks[tour].ocupation == 0)	/*don't need if we have the road*/
				{
					roadToPlace.city1 = v;
					roadToPlace.city2 = prec[v];
					roadToPlace.length = generalInfo->theGameBoard->TabOfTracks[tour].length;
					roadToPlace.ocupation = generalInfo->theGameBoard->TabOfTracks[tour].ocupation;
					roadToPlace.color1 = generalInfo->theGameBoard->TabOfTracks[tour].color1;
					roadToPlace.color2 = generalInfo->theGameBoard->TabOfTracks[tour].color2;

						/* mark the color we going to use */ 
					maxColorCards[generalInfo->theGameBoard->TabOfTracks[tour].color1] += 1;
					maxColorCards[generalInfo->theGameBoard->TabOfTracks[tour].color2] += 1;
				}

				if ((prec[v] == objective.city1) && (generalInfo->theGameBoard->TabOfTracks[tour].ocupation == 1))
				{
					printf("nouveau objective pas de couleur\n\n");
					return 0;
				}

				v = prec[v];	//next
			}
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 1; j < 9; ++j)
		{
			if ( (generalInfo->faceUp[i] == j ) && (maxColorCards[j] != 0)  )
			{
				indice = j;
			}
		}
	}


	printf("%d couleur a prendre si ya pas la premiere\n\n", indice);
	return indice;
}




void trueAlgo(t_objective objective, t_GeneralInfo* generalInfo){	/* fail*/
	int start = objective.city1;
	int end = objective.city2;

	int followRoad[generalInfo->theGameBoard->nbCities];
	for (int i = 0; i < generalInfo->theGameBoard->nbCities; ++i)
	{
		followRoad[i] = 0;
	}
	int followRoadEnd[generalInfo->theGameBoard->nbCities];
	for (int i = 0; i < generalInfo->theGameBoard->nbCities; ++i)
	{
		followRoadEnd[i] = 0;
	}

	int G[generalInfo->theGameBoard->nbCities][generalInfo->theGameBoard->nbCities];	/*tab of 2D for all the city*/
	for (int k = 0; k < generalInfo->theGameBoard->nbCities; ++k)		/* initialisation at 999*/
	{
		for (int j = 0; j < generalInfo->theGameBoard->nbCities; ++j)
		{
			G[k][j] = 999;
		}
	}
	for (int tour = 0; tour < generalInfo->theGameBoard->nbTracks; ++tour)		/* 999 replace by the length for city*/
		{
			G[generalInfo->theGameBoard->TabOfTracks[tour].city1][generalInfo->theGameBoard->TabOfTracks[tour].city2] = 
			generalInfo->theGameBoard->TabOfTracks[tour].length;
		}

		/* fonction*/

	followRoad[start] = 1;
	followRoadEnd[start] = 1;
	int compt = 0;

	while(followRoadEnd[end] == 0)
	{
		compt ++;
		for (int v = 0; v < generalInfo->theGameBoard->nbCities; ++v)
		{
			if (followRoad[v] == compt)
			{
				for (int i = 0; i < generalInfo->theGameBoard->nbCities; ++i)
				{
					if ( (G[v][i] < 999) || (G[i][v] < 999) )
					{
						followRoadEnd[i] = compt + 1;
					}
				}
			}
		}
		for (int i = 0; i < generalInfo->theGameBoard->nbCities; ++i)
		{
			followRoad[i] = followRoadEnd[i];
		}
	}printf("suite\n");

	/* suite fonction */

	t_road thePath[10];

	while(compt != 1)
	{
		for (int v = 0; v < generalInfo->theGameBoard->nbCities; ++v)
		{
			if (followRoad[v] == compt)
			{
				for (int i = 0; i < generalInfo->theGameBoard->nbCities; ++i)
				{
					if (( (G[v][i] < 999) || (G[i][v] < 999) ) && ( followRoadEnd[i] == compt - 1))
					{
						followRoadEnd[v] = -1;
						thePath[compt-1].city1 = v;
						thePath[compt-1].city2 = i;
					}
				}
			}
		}
		compt -= 1;
		for (int i = 0; i < generalInfo->theGameBoard->nbCities; ++i)
		{
			followRoad[i] = followRoadEnd[i];
		}
	}


	for (int i = 0; i < 10; ++i)
	{
		printf("%d à %d \n", thePath[i].city1, thePath[i].city2 );
	}
}