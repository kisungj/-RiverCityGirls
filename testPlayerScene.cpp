#include "stdafx.h"
#include "testPlayerScene.h"

HRESULT testPlayerScene::init()
{

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
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("backGround"), IMAGEMANAGER->findImage("backGround")->getWidth()/2, IMAGEMANAGER->findImage("backGround")->getHeight() / 2);
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel2"), IMAGEMANAGER->findImage("pixel1")->getWidth() / 2, IMAGEMANAGER->findImage("pixel1")->getHeight() / 2);
	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel1"), IMAGEMANAGER->findImage("pixel1")->getWidth() / 2, IMAGEMANAGER->findImage("pixel1")->getHeight() / 2);
	//CAMERAMANAGER->render(getMemDC(), _player->getImgge());
	_player->render();
	_ui->render();
}

void testPlayerScene::update()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2395 - WINSIZEX, 1100 - WINSIZEY);
	

	if(!_ui->getIsPhone())
		_player->update();

	CAMERAMANAGER->setX(_player->getShadowX());
	CAMERAMANAGER->setY(_player->getShadowY());

	_ui->update();

	_ui->setHpGauge(_player->getPlayerHp(), _player->getPlayerMaxHP());
}

void testPlayerScene::release()
{
}
