#include "stdafx.h"
#include "stage2.h"
#include "obstacleManager.h"
#include "itemManager.h"
#include "enemyManager.h"
HRESULT stage2::init(obstacleManager* obstacleManager, itemManager* itemManager, enemyManager* enemyManager)
{
	_obstacleManager = obstacleManager;
	_itemManager = itemManager;
	_enemyManager = enemyManager;

	return S_OK;
}

void stage2::render()
{
}

void stage2::update()
{
}

void stage2::release()
{
}
