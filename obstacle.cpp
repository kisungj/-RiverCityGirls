#include "stdafx.h"
#include "obstacle.h"

obstacle::obstacle()
{
}

obstacle::~obstacle()
{
}

HRESULT obstacle::init(OBSTACLESTATE obstacleState, POINT position)
{
	_obstacleState = obstacleState;

	_x = position.x;
	_y = position.y;

	switch (_obstacleState)
	{
	case VENDING:
		_obstacleImg = IMAGEMANAGER->findImage("���Ǳ�");
		_obstacleRc = RectMakeCenter(_x, _y, _obstacleImg->getFrameWidth(), _obstacleImg->getFrameHeight());
		break;

	case DESK:
		_obstacleImg = IMAGEMANAGER->findImage("å��");
		break;

	case PILLARLEFT:
		_obstacleImg = IMAGEMANAGER->findImage("�����");
		_PillarRc = RectMakeCenter(_x, _y, _obstacleImg->getWidth(), _obstacleImg->getHeight());
		break;

	case PILLARRIGHT:
		_obstacleImg = IMAGEMANAGER->findImage("��տ�");
		_PillarRc = RectMakeCenter(_x, _y, _obstacleImg->getWidth(), _obstacleImg->getHeight());
		break;
	}

	//ó�� ���Ǳ� ����
	if (_obstacleState == VENDING)
	{
		_obstacleImg->setFrameX(1);
	}

	//ó�� ���Ļ��� false
	_alpha = false;

	return S_OK;
}

void obstacle::release()
{
}

void obstacle::update()
{

}

void obstacle::render()
{
	//���Ǳ�
	if (_obstacleState == VENDING)
	{
		CAMERAMANAGER->frameRender(getMemDC(), _obstacleImg, (_obstacleRc.left + _obstacleRc.right) / 2, (_obstacleRc.top + _obstacleRc.bottom) / 2, _obstacleImg->getFrameX(), _obstacleImg->getFrameY());
	}

	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel2"), IMAGEMANAGER->findImage("pixel2")->getWidth() * 0.5f, IMAGEMANAGER->findImage("pixel2")->getHeight() * 0.5f);
	//å��
	if (_obstacleState == DESK)
	{
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 515, 705);
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 810, 705);
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 1125, 705);
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 1435, 705);
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 310, 940);
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 610, 940);
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 920, 940);
		CAMERAMANAGER->render(getMemDC(), _obstacleImg, 1230, 940);
	}

	//��տ���
	if (_obstacleState == PILLARLEFT)
	{
		//�浹������ ��� ����ó��
		if (_alpha)
		{
			CAMERAMANAGER->alphaRender(getMemDC(), _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2, 122);
		}
		//���� ����� �ٽ� �����·�
		else
		{
			CAMERAMANAGER->render(getMemDC(), _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2);
		}
	}

	//��� ������
	if (_obstacleState == PILLARRIGHT)
	{
		//�浹������ ��� ����ó��
		if (_alpha)
		{
			CAMERAMANAGER->alphaRender(getMemDC(), _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2, 122);
		}
		//���� ����� �ٽ� �����·�
		else
		{
			CAMERAMANAGER->render(getMemDC(), _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2);
		}
	}

	if (KEYMANAGER->isToggleKey('V'))
	{
		CAMERAMANAGER->renderRectangle(getMemDC(), _obstacleRc);
		CAMERAMANAGER->renderRectangle(getMemDC(), _PillarRc);
	}

	
}

//��հ� �浹������
void obstacle::collision()
{
	if (_obstacleState == VENDING)
	{
		_obstacleImg->setFrameX(0);
	}
}