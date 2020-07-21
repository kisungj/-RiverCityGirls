#include "stdafx.h"
#include "testPlayerScene.h"

HRESULT testPlayerScene::init()
{
	IMAGEMANAGER->addImage("backGround", "image/map/01_Detention_BG_x3_start.bmp", 2395, 900, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("pixel1", "image/map/01_Detention_BG_x3_second.bmp", 2395, 900, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("pixel2", "image/map/01_Detention_BG_x3_start_third.bmp", 2016, 672, false, RGB(0, 0, 0));
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2395 - WINSIZEX, 900 - WINSIZEY);
	_player = new player;
	_player->init();

	_ui = new ui;
	_ui->init();

	return S_OK;
}

void testPlayerScene::render()
{
	TextOut(getMemDC(), 10, 100, "Player Scene", strlen("Player Scene"));

	//CAMERAMANAGER->render(getMemDC(), )
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel1"), IMAGEMANAGER->findImage("pixel1")->getWidth() / 2, IMAGEMANAGER->findImage("pixel1")->getHeight() / 2);
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("backGround"), IMAGEMANAGER->findImage("backGround")->getWidth()/2, IMAGEMANAGER->findImage("backGround")->getHeight() / 2);
	//CAMERAMANAGER->render(getMemDC(), _player->getImgge());
	_player->render();
	_ui->render();
}

void testPlayerScene::update()
{

	

	if(!_ui->getIsPhone())
		_player->update();

	_ui->update();

	_ui->setHpGauge(_player->getPlayerHp(), _player->getPlayerMaxHP());
}

void testPlayerScene::release()
{
}
