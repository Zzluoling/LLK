#include "pch.h"
#include "CBasicGame.h"
#include"CGameLogic.h"

void CBasicGame::StartGame() 
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);

}