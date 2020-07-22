#include "stdafx.h"
#include "stage2.h"
#include "obstacleManager.h"
#include "itemManager.h"
#include "enemyManager.h"
#include "player.h"
HRESULT stage2::init(obstacleManager* obstacleManager, itemManager* itemManager, enemyManager* enemyManager, player* player)
{
	_obstacleManager = obstacleManager;
	_itemManager = itemManager;
	_enemyManager = enemyManager;
	_player = player;

	return S_OK;
}

void stage2::render()
{
}

void stage2::update()
{
	CAMERAMANAGER->setX(_player->getPlayerX());
	CAMERAMANAGER->setY(_player->getPlayerY());
}

void stage2::release()
{
}
