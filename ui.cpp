#include "stdafx.h"
#include "ui.h"

HRESULT ui::init()
{
	_loading = IMAGEMANAGER->findImage("loading_sprite");
	_selectArrow = IMAGEMANAGER->findImage("select_arrow");
	_hpUI = IMAGEMANAGER->findImage("full_hd");

	// ���â
	_inventory[0] = RectMake(250, 300, 110, 110);
	_inventory[1] = RectMake(405, 300, 110, 110);

	// ù��° �� �κ��丮 
	_inventory[2] = RectMake(248, 448, 63, 61);
	_inventory[3] = RectMake(317, 448, 63, 61);
	_inventory[4] = RectMake(386, 448, 63, 61);
	_inventory[5] = RectMake(455, 448, 63, 61);

	// �ι�° �� �κ��丮
	_inventory[6] = RectMake(248, 522, 63, 61);
	_inventory[7] = RectMake(317, 522, 63, 61);
	_inventory[8] = RectMake(386, 522, 63, 61);
	_inventory[9] = RectMake(455, 522, 63, 61);


	_hpRC = RectMake(290, 55, _hpUI->getWidth(), _hpUI->getHeight());

	_arrowX = 150;

	_itemSelectIndex = 0;
	_phoneAlpha = 0;

	_hpWidth = _hpUI->getWidth();

	_isStart = true;
	_isPhone = false;
	return S_OK;
}

void ui::render()
{
	//IMAGEMANAGER->findImage("title_background")->render(getMemDC());
	//_selectArrow->render(getMemDC(),_arrowX, _arrowY);
	//_loading->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2,_loading->getFrameX(),0);
	//CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("letter_box"), IMAGEMANAGER->findImage("letter_box")->getWidth() / 2, IMAGEMANAGER->findImage("letter_box")->getHeight() / 2);
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 800);
	IMAGEMANAGER->findImage("status_hud_back")->render(getMemDC(), 270, 50);
	IMAGEMANAGER->findImage("full_hd")->render(getMemDC(), _hpRC.left, _hpRC.top,0,0,_hpWidth,_hpUI->getHeight());
	IMAGEMANAGER->findImage("status_hud")->render(getMemDC(), 270, 50);
	IMAGEMANAGER->findImage("coin_ui")->render(getMemDC(), 290, 105);
	IMAGEMANAGER->findImage("character_hud")->render(getMemDC(), 140, 0);

	if (_isPhone)
	{
		IMAGEMANAGER->findImage("phone_active")->alphaRender(getMemDC(), 100);
		IMAGEMANAGER->findImage("phone_ui")->alphaRender(getMemDC(),150,50, _phoneAlpha);

		if (_itemSelectIndex == 0 || _itemSelectIndex == 1)
		{
			IMAGEMANAGER->findImage("equip_select")->alphaRender(getMemDC(), _inventory[_itemSelectIndex].left + 35 , _inventory[_itemSelectIndex].top - 27, _phoneAlpha);
		}

		if (_itemSelectIndex > 1 && _itemSelectIndex < 10)
		{
			IMAGEMANAGER->findImage("select_item")->alphaRender(getMemDC(), _inventory[_itemSelectIndex].left, _inventory[_itemSelectIndex].top, _phoneAlpha);
		}
	}

}

void ui::update()
{
	// �ε� �׽�Ʈ
	_timer++;
	if (_timer > 50)
	{
		if (_loading->getFrameX() >= _loading->getMaxFrameX())
		{
			cout << "����" << endl;
			_loading->setFrameX(-1);
		}
		_loading->setFrameX(_loading->getFrameX() + 1);
		_timer = 0;
	}


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
	}
	else
	{
		_arrowY = 660;
	}

	// �κ��丮 UI ���� Ű
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		!_isPhone ? _isPhone = true : _isPhone = false;
	}

	// �κ��丮 ����Ű
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

	if (_isPhone)
	{
		if (_phoneAlpha < 255)
			_phoneAlpha+= 8.5;
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
