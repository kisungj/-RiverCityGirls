#include "stdafx.h"
#include "ui.h"

HRESULT ui::init()
{
	IMAGEMANAGER->addImage("letter_box", "image/ui/UI_footer.bmp", 1600, 100, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("character_hud", "image/ui/UI_RCG_HUD_portrait_Kyoko_default.bmp", 150, 169, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status_hud", "image/ui/NULL_UHD_BAR.bmp", 414, 94, true, RGB(255, 0, 255));
	return S_OK;
}

void ui::render()
{
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("letter_box")->render(getMemDC(), 0, 800);
	IMAGEMANAGER->findImage("status_hud")->render(getMemDC(), 270, 50);
	IMAGEMANAGER->findImage("character_hud")->render(getMemDC(), 140, 0);
}

void ui::update()
{
}

void ui::release()
{
}
