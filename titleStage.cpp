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
	// Ÿ��Ʋ ȭ�� ���� Ű
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

	// Ÿ��Ʋ ȭ�� ȭ��ǥ ����
	if (_isStart)
	{
		_arrowY = 530;

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// ���� ������ �ѱ��
			SCENEMANAGER->changeScene("STAGE1_SCENE");
		}
	}
	else
	{
		_arrowY = 660;

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// ���� ����
			PostQuitMessage(0);
		}
	}
}

void titleStage::release()
{
}
