#include "stdafx.h"
#include "testObstcle.h"

HRESULT testObstcle::init()
{
	imageLoad();

	_om = new obstacleManager;
	_om->init();
	_im = new itemManager;
	_im->init();

	_om->setObstacle(VENDING);
	_om->setObstacle(PILLAR);

	_x = 500;
	_y = 500;

	_testRc = RectMakeCenter(_x, _y, 50, 50);
	_attackCount = 0;
	_attackbool = false;
	return S_OK;
}

void testObstcle::render()
{
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("stage2"), IMAGEMANAGER->findImage("stage2")->getWidth() / 2, IMAGEMANAGER->findImage("stage2")->getHeight() / 2);
	CAMERAMANAGER->renderRectangle(getMemDC(), _testRc);
	CAMERAMANAGER->renderRectangle(getMemDC(), _testAttack);

	_om->render();
	_im->render();
}

void testObstcle::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 5;
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_attackbool = true;
	}

	if (_attackbool)
	{
		_attackCount++;
		_testAttack = RectMakeCenter(_testRc.right + 30, (_testRc.top + _testRc.bottom) / 2, 50, 100);
		if (_attackCount > 1)
		{
			_testAttack = RectMakeCenter(0, 0, 0, 0);
			_attackCount = 0;
			_attackbool = false;
		}
	}

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 3000 - WINSIZEX, 1000 - WINSIZEY);


	_testRc = RectMakeCenter(_x, _y, 50, 50);
	CAMERAMANAGER->setX(_x);
	CAMERAMANAGER->setY(_y);

	_om->update();
	_im->update();

}

void testObstcle::release()
{
	_om->release();
	_im->release();
}

void testObstcle::imageLoad()
{
	IMAGEMANAGER->addImage("stage2", "image/map/stage2.bmp", 4000, 1200, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("금동전", "image/item/금동전.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("은동전", "image/item/은동전.bmp", 36, 37, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("물약1", "image/item/물약1.bmp", 70, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("물약2", "image/item/물약2.bmp", 70, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기둥", "image/obstacle/기둥.bmp", 228, 950, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("자판기", "image/obstacle/자판기.bmp", 700, 346, 2, 1, true, RGB(255, 0, 255));
}
