#include "stdafx.h"
#include "stage1.h"
#include "obstacleManager.h"
#include "itemManager.h"
#include "enemyManager.h"
#include "player.h"
HRESULT stage1::init(obstacleManager * obstacleManager, itemManager* itemManager, enemyManager* enemyManager, player* player)
{
	_obstacleManager = obstacleManager;
	_itemManager = itemManager;
	_enemyManager = enemyManager;
	_player = player;


	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2395 - WINSIZEX, 1100 - WINSIZEY);
	return S_OK;
}

void stage1::render()
{
	//IMAGEMANAGER->addImage("stage2", "image/map/stage2.bmp", 4000, 1200, false, RGB(0, 0, 0));
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("stage1"), IMAGEMANAGER->findImage("stage1")->getWidth() * 0.5f, IMAGEMANAGER->findImage("stage1")->getHeight() * 0.5f);

}

void stage1::update()
{
	CAMERAMANAGER->setX(_player->getPlayerX());
	CAMERAMANAGER->setY(_player->getPlayerY());
}

void stage1::release()
{

}
