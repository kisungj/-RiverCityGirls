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
		_obstacleImg = IMAGEMANAGER->findImage("ÀÚÆÇ±â");
		_obstacleRc = RectMakeCenter(_x, _y, _obstacleImg->getFrameWidth(), _obstacleImg->getFrameHeight());
		break;

	case DESK:
		_obstacleImg = IMAGEMANAGER->findImage("Ã¥»ó");
		break;

	case PILLARLEFT:
		_obstacleImg = IMAGEMANAGER->findImage("±âµÕÁÂ");
		_PillarRc = RectMakeCenter(_x, _y, _obstacleImg->getWidth(), _obstacleImg->getHeight());
		break;

	case PILLARRIGHT:
		_obstacleImg = IMAGEMANAGER->findImage("±âµÕ¿ì");
		_PillarRc = RectMakeCenter(_x, _y, _obstacleImg->getWidth(), _obstacleImg->getHeight());
		break;
	}

	//Ã³À½ ÀÚÆÇ±â »óÅÂ
	if (_obstacleState == VENDING)
	{
		_obstacleImg->setFrameX(1);
	}



	//Ã³À½ ¾ËÆÄ»óÅÂ false
	_alpha = false;

	return S_OK;
}

void obstacle::release()
{
}

void obstacle::update()
{
	//±âµÕ ÁÂ ¿ì
	if (_obstacleState == PILLARLEFT || _obstacleState == PILLARRIGHT)
	{
		//±âµÕ°ú Ãæµ¹ÇßÀ»¶§
		if (_alpha)
		{
			_pillarAlpha = 122;
		}
		//¾Æ´Ò¶§
		else
		{
			_pillarAlpha = 255;
		}
	}

	//Ã¥»ó
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

	//±âµÕ ÁÂ
	if (_obstacleState == PILLARLEFT)
	{
		ZORDERMANAGER->addAlphaRender(getMemDC(), renderType::ALPHA_RENDER, _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2, _PillarRc.bottom, _pillarAlpha);
	}

	//±âµÕ ¿ì
	if (_obstacleState == PILLARRIGHT)
	{
		ZORDERMANAGER->addAlphaRender(getMemDC(), renderType::ALPHA_RENDER, _obstacleImg, (_PillarRc.left + _PillarRc.right) / 2, (_PillarRc.top + _PillarRc.bottom) / 2,  _PillarRc.bottom, _pillarAlpha);
	}

}

void obstacle::render()
{
	//ÀÚÆÇ±â
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

//±âµÕ°ú Ãæµ¹ÇßÀ»¶§
void obstacle::collision()
{
	if (_obstacleState == VENDING)
	{
		_obstacleImg->setFrameX(0);
	}
}