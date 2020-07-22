#include "stdafx.h"
#include "ui.h"

HRESULT ui::init()
{
	IMAGEMANAGER->addImage("letter_box", "image/ui/UI_footer.bmp", 1600, 100, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("character_hud", "image/ui/UI_RCG_HUD_portrait_Kyoko_default.bmp", 150, 169, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status_hud", "image/ui/NULL_UHD_BAR2.bmp", 414, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status_hud_back", "image/ui/NULL_UHD_BAR.bmp", 414, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("title_background", "image/ui/titleBackGround.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("coin_ui", "image/ui/coin.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("phone_ui", "image/ui/Phone.bmp", 463, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("phone_active", "image/ui/phone_active.bmp", 1600, 900, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("select_item", "image/ui/select_item.bmp", 63, 61, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("equip_select", "image/ui/equip_select.bmp", 42, 25, true, RGB(255, 0, 255));
	_loading = IMAGEMANAGER->addFrameImage("loading_sprite", "image/ui/loadingSprite4x1.bmp", 1152, 227, 4, 1, false, RGB(0, 0, 0));
	_selectArrow = IMAGEMANAGER->addImage("select_arrow", "image/ui/select_arrow.bmp", 66, 76, true, RGB(255, 0, 255));
	_hpUI = IMAGEMANAGER->addImage("full_hd", "image/ui/hpBar.bmp", 389, 21, true, RGB(255, 0, 255));

	// 장비창
	_inventory[0] = RectMake(250, 300, 110, 110);
	_inventory[1] = RectMake(405, 300, 110, 110);

	// 첫번째 줄 인벤토리 
	_inventory[2] = RectMake(248, 448, 63, 61);
	_inventory[3] = RectMake(317, 448, 63, 61);
	_inventory[4] = RectMake(386, 448, 63, 61);
	_inventory[5] = RectMake(455, 448, 63, 61);

	// 두번째 줄 인벤토리
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
	}
	else
	{
		_arrowY = 660;
	}

	// 인벤토리 UI 띄우기 키
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		!_isPhone ? _isPhone = true : _isPhone = false;
	}

	// 인벤토리 조종키
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
