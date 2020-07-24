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

	_obstacleManager->init();
	_enemyManager->init();
	_itemManager->init();
	//---- 임시
	_obstacleManager->setObstacle(DESK);
	_enemyManager->setStage1();
	//---- 임시
	_doorRc = RectMakeCenter(1700, 420, 200, 30);

	_doorAlpha = 150;

	return S_OK;
}

void stage1::render()
{
	//IMAGEMANAGER->addImage("stage2", "image/map/stage2.bmp", 4000, 1200, false, RGB(0, 0, 0));
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("stage1"), IMAGEMANAGER->findImage("stage1")->getWidth() * 0.5f, IMAGEMANAGER->findImage("stage1")->getHeight() * 0.5f);
	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel2"), IMAGEMANAGER->findImage("pixel2")->getWidth() * 0.5f, IMAGEMANAGER->findImage("pixel2")->getHeight() * 0.5f);
	CAMERAMANAGER->renderRectangle(getMemDC(), _doorRc);
	CAMERAMANAGER->alphaRender(getMemDC(), IMAGEMANAGER->findImage("door_img"), (_doorRc.left + _doorRc.right) / 2, _doorRc.top, _doorAlpha);
}

void stage1::update()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2395 - WINSIZEX, 1100 - WINSIZEY);
	CAMERAMANAGER->setX(_player->getPlayerX());
	CAMERAMANAGER->setY(_player->getPlayerY());

	RECT _temp;
	if (IntersectRect(&_temp, &_player->getPlayerRect(), &_doorRc))
	{
		_doorAlpha = 255;
	}
	else
	{
		_doorAlpha = 150;
	}
}

void stage1::release()
{

}
