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
	//��� �� ��
	if (_obstacleState == PILLARLEFT || _obstacleState == PILLARRIGHT)
	{
		//��հ� �浹������
		if (_alpha)
		{
			_pillarAlpha = 122;
		}
		//�ƴҶ�
		else
		{
			_pillarAlpha = 255;
		}
	}

	//å��
	if (_obstacleState == DESK)
	{
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 515, 705 , 705);
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 810, 705, 705);
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 1125, 705, 705);
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 1435, 705, 705);
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 310, 940 , 940);
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 610, 940, 940);
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 920, 940 , 940);
		ZORDERMANAGER->addRender(getMemDC(), renderType::RENDER, _obstacleImg, 1230, 940 , 940);
	}

	//��� ��
	if (_obstacleState == PILLARLEFT)
	{
		ZORDERMANAGER->addAlphaRender(getMemDC(), renderType::ALPHA_RENDER, _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2, _PillarRc.bottom, _pillarAlpha);
	}

	//��� ��
	if (_obstacleState == PILLARRIGHT)
	{
		ZORDERMANAGER->addAlphaRender(getMemDC(), renderType::ALPHA_RENDER, _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2,  _PillarRc.bottom, _pillarAlpha);
	}

}

void obstacle::render()
{
	//���Ǳ�
	if (_obstacleState == VENDING)
	{
		CAMERAMANAGER->frameRender(getMemDC(), _obstacleImg, (_obstacleRc.left + _obstacleRc.right) / 2, (_obstacleRc.top + _obstacleRc.bottom) / 2, _obstacleImg->getFrameX(), _obstacleImg->getFrameY());
	}

	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel2"), IMAGEMANAGER->findImage("pixel2")->getWidth() * 0.5f, IMAGEMANAGER->findImage("pixel2")->getHeight() * 0.5f);

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