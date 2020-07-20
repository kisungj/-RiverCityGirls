#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	// ------------ �ӽ� ���� ------------ //
	loadImage();
	_x = _y = _jumpPower = _gravity = 0;
	_state = BOSS_LEFT_IDLE;
	_rc = RectMakeCenter(_x, _y, 100, 100);
	_playerX = WINSIZEX / 2;
	_playerY = WINSIZEY / 2;
	_img = IMAGEMANAGER->findImage("boss_walk");
	// ------------ �ӽ� ���� ------------ //
	return S_OK;
}

void boss::release()
{
}

void boss::render()
{
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("�������"));
	CAMERAMANAGER->frameRender(getMemDC(), _img, WINSIZEX / 2, WINSIZEY / 2, _img->getFrameX(), 0);

	_count++;
	if (_count % 7 == 0)
	{
		_count = 0;
		_img->setFrameX(_img->getFrameX() + 1);
		if (_img->getFrameX() >= _img->getMaxFrameX())
		{
			_img->setFrameX(0);
		}

	}


}

void boss::update()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2538 - WINSIZEX, 1000 - WINSIZEY);

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_playerX += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_playerX -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerY -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_playerY += 3;
	}

	CAMERAMANAGER->setX(_playerX + 200);
	CAMERAMANAGER->setY(_playerY + 200);
}

void boss::loadImage()
{
	IMAGEMANAGER->addImage("�������", "image/map/bossMap1.bmp", 2538, 1000, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_idle", "image/boss/boss_idle.bmp", 3792, 776, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit", "image/boss/boss_hit.bmp", 7656, 616, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss/boss_walk.bmp", 2360, 736, 10, 2, true, RGB(255, 0, 255));
}
