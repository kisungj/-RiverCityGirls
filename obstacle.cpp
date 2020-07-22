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
		_obstacleImg = IMAGEMANAGER->findImage("자판기");
		_obstacleRc = RectMakeCenter(_x, _y, _obstacleImg->getFrameWidth(), _obstacleImg->getFrameHeight());
		break;

	case DESK:
		_obstacleImg = IMAGEMANAGER->findImage("책상");
		break;

	case PILLARLEFT:
		_obstacleImg = IMAGEMANAGER->findImage("기둥좌");
		_PillarRc = RectMakeCenter(_x, _y, _obstacleImg->getWidth(), _obstacleImg->getHeight());
		break;

	case PILLARRIGHT:
		_obstacleImg = IMAGEMANAGER->findImage("기둥우");
		_PillarRc = RectMakeCenter(_x, _y, _obstacleImg->getWidth(), _obstacleImg->getHeight());
		break;
	}

	//처음 자판기 상태
	if (_obstacleState == VENDING)
	{
		_obstacleImg->setFrameX(1);
	}

	//처음 알파상태 false
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
	//자판기
	if (_obstacleState == VENDING)
	{
		CAMERAMANAGER->frameRender(getMemDC(), _obstacleImg, (_obstacleRc.left + _obstacleRc.right) / 2, (_obstacleRc.top + _obstacleRc.bottom) / 2, _obstacleImg->getFrameX(), _obstacleImg->getFrameY());
	}

	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("pixel2"), IMAGEMANAGER->findImage("pixel2")->getWidth() * 0.5f, IMAGEMANAGER->findImage("pixel2")->getHeight() * 0.5f);
	//책상
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

	//기둥왼쪽
	if (_obstacleState == PILLARLEFT)
	{
		//충돌됬을때 기둥 알파처리
		if (_alpha)
		{
			CAMERAMANAGER->alphaRender(getMemDC(), _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2, 122);
		}
		//범위 벗어나면 다시 원상태로
		else
		{
			CAMERAMANAGER->render(getMemDC(), _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2);
		}
	}

	//기둥 오른쪽
	if (_obstacleState == PILLARRIGHT)
	{
		//충돌됬을때 기둥 알파처리
		if (_alpha)
		{
			CAMERAMANAGER->alphaRender(getMemDC(), _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2, 122);
		}
		//범위 벗어나면 다시 원상태로
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

//기둥과 충돌했을때
void obstacle::collision()
{
	if (_obstacleState == VENDING)
	{
		_obstacleImg->setFrameX(0);
	}
}