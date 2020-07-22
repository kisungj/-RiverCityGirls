#include "stdafx.h"
#include "testEnemyScene.h"

HRESULT testEnemyScene::init()
{

	_em = new enemyManager;
	_em->init();
	_em->setBoy();

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_testPlayer = RectMakeCenter(_x, _y, 130, 200);

	return S_OK;
}

void testEnemyScene::render()
{
	TextOut(getMemDC(), 10, 100, "Enemy Scene", strlen("Enemy Scene"));

	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("background"), IMAGEMANAGER->findImage("background")->getWidth() / 2, IMAGEMANAGER->findImage("background")->getHeight()/2);
	CAMERAMANAGER->renderRectangle(getMemDC(), _punch);
	CAMERAMANAGER->renderRectangle(getMemDC(), _testPlayer);

	for (int i = 0; i < _em->getVBoy().size(); ++i)
	{
		_em->getVBoy()[i]->render();
	}
}

void testEnemyScene::update()
{
	//테스트용
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_right = false;
			_x -= 5;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_right = true;
			_x += 5;
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_y -= 3;
		}

		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_y += 3;
		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (_right)
				_punch = RectMakeCenter(_x + 65, _y, 95, 200);

			if (!_right)
				_punch = RectMakeCenter(_x - 65, _y, 95, 200);
		}

		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			_punch = RectMakeCenter(0, 0, 0, 0);
		}
	}

	RECT temp;

	for (int i = 0; i < _em->getVBoy().size(); i++)
	{
		_em->getVBoy()[i]->update();
		_em->getVBoy()[i]->directionCheck(_testPlayer, _x, _y);

		if (IntersectRect(&temp, &_em->getVBoy()[i]->getRC(), &_punch))
		{
			_punch = RectMakeCenter(0, 0, 0, 0);
			_em->getVBoy()[i]->setOuch(true);
			_em->getVBoy()[i]->setHitCount(1);
		}
	}	

	_testPlayer = RectMakeCenter(_x, _y, 130, 200);

	CAMERAMANAGER->setX(_x);
	CAMERAMANAGER->setY(_y);
}

void testEnemyScene::release()
{
	for (int i = 0; i < _em->getVBoy().size(); ++i)
	{
		_em->getVBoy()[i]->release();
	}
}
