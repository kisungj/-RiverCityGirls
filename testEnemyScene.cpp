#include "stdafx.h"
#include "testEnemyScene.h"

HRESULT testEnemyScene::init()
{
	_enemy = new enemy;
	_enemy->init();

	return S_OK;
}

void testEnemyScene::render()
{
	TextOut(getMemDC(), 10, 100, "Enemy Scene", strlen("Enemy Scene"));

	_enemy->render();
}

void testEnemyScene::update()
{
	_enemy->update();
}

void testEnemyScene::release()
{
	_enemy->release();
}
