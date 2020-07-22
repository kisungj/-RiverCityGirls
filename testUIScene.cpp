#include "stdafx.h"
#include "testUIScene.h"

HRESULT testUIScene::init()
{

	_ui = new ui;
	_ui->init();

	_index = 1;
	_chatCount = 2;
	
	_isTalk = true;

	_playerX = -200;
	_bossX = 1300;

	return S_OK;
}

void testUIScene::render()
{
	_ui->render();

	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT font, oldFont;
	RECT rcText = RectMake(400, WINSIZEY - 75, 1100, 400);

	font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY°ß°íµñ"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	if (_isTalk)
	{
		IMAGEMANAGER->findImage("phone_active")->alphaRender(getMemDC(), 100);
		if (_typeStr == "B")
		{
			IMAGEMANAGER->findImage("s_boss_name")->render(getMemDC(),200, WINSIZEY - 80);
			IMAGEMANAGER->findImage("misuzu_img")->render(getMemDC(), _bossX, 200);
		}
		if (_typeStr == "M")
		{
			IMAGEMANAGER->findImage("s_misako_name")->render(getMemDC(), 200, WINSIZEY - 80);
			IMAGEMANAGER->findImage("misako_img")->render(getMemDC(), _playerX, 210);
		}
		if (_typeStr == "K")
		{
			IMAGEMANAGER->findImage("s_kyoko_name")->render(getMemDC(), 200, WINSIZEY - 80);
			IMAGEMANAGER->findImage("kyoko_img")->render(getMemDC(), _playerX, 210);
		}
		DrawText(getMemDC(), TEXT(_firstNotStr.c_str()), _chatCount, &rcText, DT_LEFT | DT_WORDBREAK);
	}
	SelectObject(getMemDC(),oldFont);
	DeleteObject(font);

}

void testUIScene::update()
{
	if(!_isTalk)
		_ui->update();


	if (_isTalk)
	{
	
		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			if (_index == 13)
			{
				_isTalk = false;
				return;
			}
			_index += 1;
			_chatCount = 0;
			_playerX = -200;
			_bossX = 1300;
		}
		
		//if (_index == 13 && _chatCount == strlen(_test.c_str()))
		//{
		//	_isTalk = false;
		//}

		sprintf_s(_indexStr, "TALK%d", _index);
		_test = INIDATA->loadDataString("TALK", "TALK", _indexStr);

		//cout << _test.front() << endl;
		//_test.erase(_test.front());
		_typeStr = _test.front();
		_firstNotStr = _test.substr(1, _test.length());


		if (_chatCount < strlen(_test.c_str()))
		{
			_chatCount += 0.5f;
		}

		if (_playerX < 0)
		{
			_playerX+= 5;
		}
		if (_bossX > 1000)
		{
			_bossX-= 5;
		}
	}
}

void testUIScene::release()
{
	SAFE_DELETE(_ui);
}
