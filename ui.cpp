#include "stdafx.h"
#include "ui.h"

HRESULT ui::init()
{
	_loading = IMAGEMANAGER->findImage("loading_sprite");
	_hpUI = IMAGEMANAGER->findImage("full_hd");

	// 장비창
	_inventory[0].rc = RectMake(250, 300, 110, 110);
	_inventory[1].rc = RectMake(405, 300, 110, 110);

	// 첫번째 줄 인벤토리 
	_inventory[2].rc = RectMake(248, 448, 63, 61);
	_inventory[3].rc = RectMake(317, 448, 63, 61);
	_inventory[4].rc = RectMake(386, 448, 63, 61);
	_inventory[5].rc = RectMake(455, 448, 63, 61);

	// 두번째 줄 인벤토리
	_inventory[6].rc = RectMake(248, 522, 63, 61);
	_inventory[7].rc = RectMake(317, 522, 63, 61);
	_inventory[8].rc = RectMake(386, 522, 63, 61);
	_inventory[9].rc = RectMake(455, 522, 63, 61);


	_hpRC = RectMake(290, 55, _hpUI->getWidth(), _hpUI->getHeight());

	_itemSelectIndex = 0;
	_phoneAlpha = 0;

	_hpWidth = _hpUI->getWidth();

	_isPhone = false;

	for (int i = 0; i < 10; i++)
	{
		_inventory[i].isNull = true;
	}
	return S_OK;
}

void ui::render()
{
	//_loading->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2,_loading->getFrameX(),0);
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 800);
	IMAGEMANAGER->findImage("status_hud_back")->render(getMemDC(), 270, 50);
	IMAGEMANAGER->findImage("full_hd")->render(getMemDC(), _hpRC.left, _hpRC.top, 0, 0, _hpWidth, _hpUI->getHeight());
	IMAGEMANAGER->findImage("status_hud")->render(getMemDC(), 270, 50);
	IMAGEMANAGER->findImage("coin_ui")->render(getMemDC(), 290, 105);
	IMAGEMANAGER->findImage("character_hud")->render(getMemDC(), 140, 0);

	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT font, oldFont;
	RECT itemNameText = RectMake(200, WINSIZEY / 2 + 180, 1100, 400);
	RECT itemDiscriptionText = RectMake(220, WINSIZEY / 2 + 220, 250, 400);

	if (_isPhone)
	{
		IMAGEMANAGER->findImage("phone_active")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("phone_ui")->alphaRender(getMemDC(), 150, 50, _phoneAlpha);

		if (_itemSelectIndex == 0 || _itemSelectIndex == 1)
		{
			IMAGEMANAGER->findImage("equip_select")->alphaRender(getMemDC(), _inventory[_itemSelectIndex].rc.left + 35, _inventory[_itemSelectIndex].rc.top - 27, _phoneAlpha);
		}

		if (_itemSelectIndex > 1 && _itemSelectIndex < 10)
		{
			IMAGEMANAGER->findImage("select_item")->alphaRender(getMemDC(), _inventory[_itemSelectIndex].rc.left, _inventory[_itemSelectIndex].rc.top, _phoneAlpha);
		}

		for (int i = 0; i < 10; i++)
		{
			if (!_inventory[i].isNull)
				_inventory[i].item->getItemImage()->render(getMemDC(), _inventory[i].rc.left, _inventory[i].rc.top);
		}

		if (!_inventory[_itemSelectIndex].isNull)
		{
			font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY얕은샘물M"));
			oldFont = (HFONT)SelectObject(getMemDC(), font);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			DrawText(getMemDC(), TEXT(_inventory[_itemSelectIndex].item->getItemName().c_str()), strlen(_inventory[_itemSelectIndex].item->getItemName().c_str()), &itemNameText, DT_LEFT | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);


			font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY얕은샘물M"));
			oldFont = (HFONT)SelectObject(getMemDC(), font);
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			DrawText(getMemDC(), TEXT(_inventory[_itemSelectIndex].item->getItemDiscription().c_str()), strlen(_inventory[_itemSelectIndex].item->getItemDiscription().c_str()), &itemDiscriptionText, DT_LEFT | DT_WORDBREAK);
			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);
		}
	}

}

void ui::update()
{
	// 로딩 테스트
	_timer++;
	if (_timer > 50)
	{
		if (_loading->getFrameX() >= _loading->getMaxFrameX())
		{
			cout << "들어옴" << endl;
			_loading->setFrameX(-1);
		}
		_loading->setFrameX(_loading->getFrameX() + 1);
		_timer = 0;
	}

	// 인벤토리 UI 띄우기 키
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		!_isPhone ? _isPhone = true : _isPhone = false;
	}

	// 인벤토리 조종키
	if (_isPhone)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_itemSelectIndex--;
			if (_itemSelectIndex < 0)
				_itemSelectIndex = 9;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_itemSelectIndex++;
			if (_itemSelectIndex > 9)
				_itemSelectIndex = 0;
		}
	}

	if (_isPhone)
	{
		if (_phoneAlpha < 255)
			_phoneAlpha += 8.5;
	}
	else
	{
		_itemSelectIndex = 0;
		_phoneAlpha = 0;
	}
}

void ui::release()
{
}

void ui::setHpGauge(float curHp, float maxHp)
{
	_hpWidth = (curHp / maxHp) * _hpUI->getWidth();
}
