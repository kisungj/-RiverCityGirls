#include "stdafx.h"
#include "testBossScene.h"

HRESULT testBossScene::init()
{
	_boss = new boss;
	_boss->init();
	return S_OK;
}

void testBossScene::render()
{
	_boss->render();

}

void testBossScene::update()
{
	_boss->update();
}

void testBossScene::release()
{
	_boss->release();
}
