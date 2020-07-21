#include "stdafx.h"
#include "testPlayerScene.h"

HRESULT testPlayerScene::init()
{
	IMAGEMANAGER->addImage("backGround", "image/map/01_Detention_BG_x3_start.bmp", 2395, 900, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("pixel1", "image/map/01_Detention_BG_x3_second.bmp", 2395, 900, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("pixel2", "image/map/01_Detention_BG_x3_start_third.bmp", 2016, 672, false, RGB(0, 0, 0));

	_player = new player;
	_player->init();

	return S_OK;
}

void testPlayerScene::render()
{
	TextOut(getMemDC(), 10, 100, "Player Scene", strlen("Player Scene"));

	//CAMERAMANAGER->render(getMemDC(), )
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel1"));
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("backGround"));
	//CAMERAMANAGER->render(getMemDC(), _player->getImgge());
	_player->render();
}

void testPlayerScene::update()
{

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2395 - WINSIZEX, 900 - WINSIZEY);
	_player->update();
}

void testPlayerScene::release()
{
}
