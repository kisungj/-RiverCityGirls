#include "stdafx.h"
#include "ui.h"

HRESULT ui::init()
{
	IMAGEMANAGER->addImage("letter_box", "image/ui/UI_footer.bmp", 1600, 100, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("character_hud", "image/ui/UI_RCG_HUD_portrait_Kyoko_default.bmp", 150, 169, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status_hud", "image/ui/NULL_UHD_BAR2.bmp", 414, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status_hud_back", "image/ui/NULL_UHD_BAR.bmp", 414, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("title_background", "image/ui/titleBackGround.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	_loading = IMAGEMANAGER->addFrameImage("loading_sprite", "image/ui/loadingSprite4x1.bmp", 1152, 227, 4, 1, false, RGB(0, 0, 0));
	_selectArrow = IMAGEMANAGER->addImage("select_arrow", "image/ui/select_arrow.bmp", 66, 76, true, RGB(255, 0, 255));
	_hpUI = IMAGEMANAGER->addImage("full_hd", "image/ui/hpBar.bmp", 389, 21, true, RGB(255, 0, 255));

	_hpRC = RectMake(290, 55, _hpUI->getWidth(), _hpUI->getHeight());

	_testHp = 100;
	_arrowX = 150;

	

	_hpWidth = _hpUI->getWidth();

	_isStart = true;
	return S_OK;
}

void ui::render()
{
	//IMAGEMANAGER->findImage("title_background")->render(getMemDC());
	//_selectArrow->render(getMemDC(),_arrowX, _arrowY);
	//_loading->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2,_loading->getFrameX(),0);
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 800);
	IMAGEMANAGER->findImage("status_hud_back")->render(getMemDC(), 270, 50);
	IMAGEMANAGER->findImage("full_hd")->render(getMemDC(), _hpRC.left, _hpRC.top,0,0,_hpWidth,_hpUI->getHeight());
	IMAGEMANAGER->findImage("status_hud")->render(getMemDC(), 270, 50);
	IMAGEMANAGER->findImage("character_hud")->render(getMemDC(), 140, 0);
}

void ui::update()
{
	_timer++;
	if (_timer > 50)
	{
		if (_loading->getFrameX() >= _loading->getMaxFrameX())
		{
			cout << "µé¾î¿È" << endl;
			_loading->setFrameX(-1);
		}
		_loading->setFrameX(_loading->getFrameX() + 1);
		_timer = 0;
	}

	if (KEYMANAGER->isStayKeyDown('O'))
	{
		if(_testHp > 0)
			_testHp--;
	}
	if (KEYMANAGER->isStayKeyDown('P'))
	{
		if(_testHp < 100)
			_testHp++;
	}

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

	if (_isStart)
	{
		_arrowY = 530;
	}
	else
	{
		_arrowY = 660;
	}

	setHpGauge(_testHp, 100);
}

void ui::release()
{
}

void ui::setHpGauge(float curHp, float maxHp)
{
	_hpWidth = (curHp / maxHp) * _hpUI->getWidth();
}
