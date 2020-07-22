#include "stdafx.h"
#include "testObstcle.h"

HRESULT testObstcle::init()
{
	imageLoad();

	_om = new obstacleManager;
	_om->init();
	_im = new itemManager;
	_im->init();
	_in = new inventory;
	_in->init();

	_om->setObstacle(VENDING);
	_om->setObstacle(PILLAR);

	_x = 500;
	_y = 500;

	_testRc = RectMakeCenter(_x, _y, 50, 50);
	_attackCount = 0;
	_attackbool = false;
	_moneyCount = 0;

	return S_OK;
}

void testObstcle::render()
{
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("stage2"), IMAGEMANAGER->findImage("stage2")->getWidth() / 2, IMAGEMANAGER->findImage("stage2")->getHeight() / 2);
	CAMERAMANAGER->renderRectangle(getMemDC(), _testRc);
	CAMERAMANAGER->renderRectangle(getMemDC(), _testAttackRc);

	_om->render();
	_im->render();
	_in->render();

	char str[256];
	sprintf_s(str, "�� : %d", _moneyCount);
	TextOut(getMemDC(), 50, 150, str, strlen(str));
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
		_testAttackRc = RectMakeCenter(_testRc.right + 30, (_testRc.top + _testRc.bottom) / 2, 50, 100);
		if (_attackCount > 1)
		{
			_testAttackRc = RectMakeCenter(0, 0, 0, 0);
			_attackCount = 0;
			_attackbool = false;
		}
	}

	collision();

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
	IMAGEMANAGER->addImage("�ݵ���", "image/item/�ݵ���.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/item/������.bmp", 36, 37, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1", "image/item/����1.bmp", 70, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "image/item/����2.bmp", 70, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "image/obstacle/���.bmp", 228, 950, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ǳ�", "image/obstacle/���Ǳ�.bmp", 700, 346, 2, 1, true, RGB(255, 0, 255));
}

//�浹��
void testObstcle::collision()
{
	//�����۰� �÷��̾� �浹
	for (int i = 0; i < _im->getVItem().size(); i++)
	{
		RECT temp;

		if (IntersectRect(&temp, &_testRc, &_im->getVItem()[i]->getItemRc()))
		{
			int rndgold = RND->getFromIntTo(51, 100);
			int rndsilver = RND->getFromIntTo(1, 50);

			//�ݵ��� ȹ���
			if (_im->getVItem()[i]->getitemstate() == GOLD)
			{
				_moneyCount += rndgold;
			}

			//������ ȹ���
			if (_im->getVItem()[i]->getitemstate() == SILVER)
			{
				_moneyCount += rndsilver;
			}

			//HP���� ȹ���
			if (_im->getVItem()[i]->getitemstate() == HP)
			{
				_in->setInItemName(_im->getVItem()[i]->getItemName());
				_in->setInItemDiscription(_im->getVItem()[i]->getItemDiscription());
				_in->setInHpPortion(_im->getVItem()[i]->getHpPortion());
			}

			//�Ŀ����� ȹ���
			if (_im->getVItem()[i]->getitemstate() == POWER)
			{
				_in->setInItemName(_im->getVItem()[i]->getItemName());
				_in->setInItemDiscription(_im->getVItem()[i]->getItemDiscription());
				_in->setInPowerPortion(_im->getVItem()[i]->getPowerPortion());
			}

			_im->removeItem(i);
		}
	}

	//������Ʈ�� �÷��̾� �浹
	for (int i = 0; i < _om->getVObstacle().size(); i++)
	{
		RECT temp;

		//���Ǳ� ������
		if (IntersectRect(&temp, &_testAttackRc, &_om->getVObstacle()[i]->getObsRc()))
		{
			_im->setItem(_om->getVObstacle()[i]->getObsRc());
			_om->getVObstacle()[i]->collision();
		}

		//��� ��������
		if (IntersectRect(&temp, &_testRc, &_om->getVObstacle()[i]->getPillarRc()))
		{
			_om->getVObstacle()[i]->setAlphaValue(true);
		}
		else
		{
			_om->getVObstacle()[i]->setAlphaValue(false);
		}
	}
}
