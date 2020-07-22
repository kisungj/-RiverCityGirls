#include "stdafx.h"
#include "titleStage.h"

HRESULT titleStage::init()
{
	_selectArrow = IMAGEMANAGER->findImage("select_arrow");

	_isStart = true;
	_arrowX = 150;
	_arrowY = 530;

	return S_OK;
}

void titleStage::render()
{
	IMAGEMANAGER->findImage("title_background")->render(getMemDC());
	_selectArrow->render(getMemDC(),_arrowX, _arrowY);
}

void titleStage::update()
{
	// 타이틀 화면 조종 키
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (!_isStart)
			_isStart = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_isStart)
			_isStart = false;
	}

	// 타이틀 화면 화살표 조정
	if (_isStart)
	{
		_arrowY = 530;

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// 다음 씬으로 넘기기
			SCENEMANAGER->changeScene("STAGE1_SCENE");
		}
	}
	else
	{
		_arrowY = 660;

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// 게임 종료
			PostQuitMessage(0);
		}
	}
}

void titleStage::release()
{
}
