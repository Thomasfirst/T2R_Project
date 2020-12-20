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

t_return_code playTheMove(t_move* move);

void filOjective(t_GeneralInfo* generalInfo,t_move* move,t_move* move2,t_Player* YOU);

void filBlindCard(t_GeneralInfo* generalInfo,t_move* move,t_Player* YOU);

void filCard(t_move* move,t_Player* YOU,t_GeneralInfo* generalInfo);

void filClaimRoad(t_GeneralInfo* generalInfo, t_move* move,t_Player* YOU);




#endif