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
	_player->setMapStr("stage2pixel"); // 픽셀 충돌

	_obstacleManager->init();
	_enemyManager->init();
	_itemManager->init();
	//---- 임시
	_enemyManager->setStage2();
	//---- 임시
	_obstacleManager->setObstacle(VENDING);
	_obstacleManager->setObstacle(PILLARLEFT);
	_obstacleManager->setObstacle(PILLARRIGHT);
	_stage2DoorRc = RectMakeCenter(2475, 480, 200, 30);
	_bossDoorRc = RectMakeCenter(3800, 770, 30, 200);

	_doorAlpha = 150;
	_bossDoorAlpha = 150;

	return S_OK;
}

void stage2::render()
{

	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("stage2pixel"), IMAGEMANAGER->findImage("stage2pixel")->getWidth() * 0.5f, IMAGEMANAGER->findImage("stage2pixel")->getHeight() * 0.5f);
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("stage2"), IMAGEMANAGER->findImage("stage2")->getWidth() * 0.5f, IMAGEMANAGER->findImage("stage2")->getHeight() * 0.5f);
	CAMERAMANAGER->renderRectangle(getMemDC(), _stage2DoorRc);
	CAMERAMANAGER->renderRectangle(getMemDC(), _bossDoorRc);
	CAMERAMANAGER->alphaRender(getMemDC(), IMAGEMANAGER->findImage("door_img"), (_bossDoorRc.left + _bossDoorRc.right) / 2, _bossDoorRc.top, _bossDoorAlpha);
	CAMERAMANAGER->alphaRender(getMemDC(), IMAGEMANAGER->findImage("door_img"), (_stage2DoorRc.left + _stage2DoorRc.right) / 2, _stage2DoorRc.top, _doorAlpha);
}

void stage2::update()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 4000 - WINSIZEX, 1200 - WINSIZEY);
	CAMERAMANAGER->setX(_player->getPlayerX());
	CAMERAMANAGER->setY(_player->getPlayerY());

	_enemyManager->waveStage2();

	RECT _temp;
	if (IntersectRect(&_temp, &_player->getPlayerRect(), &_stage2DoorRc))
	{
		_doorAlpha = 255;
	}
	else
	{
		_doorAlpha = 150;
	}

	if (IntersectRect(&_temp, &_player->getPlayerRect(), &_bossDoorRc))
	{
		_bossDoorAlpha = 255;
	}
	else
	{
		_bossDoorAlpha = 150;
	}
}

void stage2::release()
{
}
