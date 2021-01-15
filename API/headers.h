#ifndef __HEADERS_H__
#define __HEADERS_H__
#include "TicketToRideAPI.h"
#include "clientAPI.h"
#include "the_struct.h"

void initialisation(t_Game_Board* LePlateau,t_Player* YOU,t_Player* ENNEMIE,t_GeneralInfo* generalInfo);

void initObj(t_Player* YOU,t_GeneralInfo* generalInfo,t_Player* ENNEMIE);

void showMe(t_Game_Board* LePlateau, t_Player* YOU, t_GeneralInfo* generalInfo);

void lookMove(t_move* move);

void LoopOfGame(t_GeneralInfo* generalInfo,t_Player* YOU,t_Player* ENNEMIE);

void LoopOfGameAuto(t_GeneralInfo* generalInfo,t_Player* YOU,t_Player* ENNEMIE);


t_return_code playTheMove(t_move* move);

void filOjective(t_GeneralInfo* generalInfo,t_move* move,t_move* move2,t_Player* YOU);

void filBlindCard(t_GeneralInfo* generalInfo,t_move* move,t_Player* YOU);

void filCard(t_move* move,t_Player* YOU,t_GeneralInfo* generalInfo);

void filClaimRoad(t_GeneralInfo* generalInfo, t_move* move,t_Player* YOU);

int distanceMin(int* D, int* visite, t_GeneralInfo* generalInfo);

int* algo(t_objective objective, t_GeneralInfo* generalInfo);

t_road algo_one_road(t_objective objective, t_GeneralInfo* generalInfo);

int chooseColor(t_objective objective, t_GeneralInfo* generalInfo, t_Player* YOU);

int chooseColorIfNotTheFirst(t_objective objective, t_GeneralInfo* generalInfo);

int finishmove(t_move* move, t_GeneralInfo* generalInfo, t_Player* YOU, t_Player* ENNEMIE, int* replay);

void LoopOfGameAutoNEW(t_GeneralInfo* generalInfo,t_Player* YOU,t_Player* ENNEMIE);

int finishmove2(t_move* move, t_GeneralInfo* generalInfo, t_Player* YOU, t_Player* ENNEMIE, int* replay);

void trueAlgo(t_objective objective, t_GeneralInfo* generalInfo);



#endif