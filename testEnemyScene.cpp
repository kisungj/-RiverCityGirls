#include "stdafx.h"
#include "testEnemyScene.h"

HRESULT testEnemyScene::init()
{
	_enemy = new enemy;
	_enemy->init();

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_testPlayer = RectMakeCenter(_x, _y, 130, 200);

	return S_OK;
}

void testEnemyScene::render()
{
	TextOut(getMemDC(), 10, 100, "Enemy Scene", strlen("Enemy Scene"));

	CAMERAMANAGER->renderRectangle(getMemDC(), _punch);
	CAMERAMANAGER->renderRectangle(getMemDC(), _testPlayer);
	_enemy->render();
}

void testEnemyScene::update()
{
	_enemy->update();

	//테스트용
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_right = false;
			_x -= 3;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_right = true;
			_x += 3;
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

		RECT temp;
		if (IntersectRect(&temp, &_enemy->getRC(), &_punch))
		{			
			_punch = RectMakeCenter(0, 0, 0, 0);
			_enemy->setOuch(true);
			_enemy->setHitCount(1);
		}

		if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			_punch = RectMakeCenter(0, 0, 0, 0);
		}
	}

	_testPlayer = RectMakeCenter(_x, _y, 130, 200);
	_enemy->directionCheck(_testPlayer, _x, _y);

	CAMERAMANAGER->setX(_x);
	CAMERAMANAGER->setY(_y);
}

void testEnemyScene::release()
{
	_enemy->release();
}
