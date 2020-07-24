#include "stdafx.h"
#include "titleStage.h"

HRESULT titleStage::init()
{
	IMAGEMANAGER->addImage("start_back", "image/ui/StartScene_Background.bmp", 1600, 900, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start_frame", "image/ui/StartScene_Frame.bmp", 1600, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start_menu", "image/ui/StartScene_Menu.bmp", 150, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start_title", "image/ui/StartScene_Title.bmp", 537, 308, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start_kyoko", "image/ui/StartScene_Kyoko.bmp", 550, 828, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start_misako", "image/ui/StartScene_Misako.bmp", 440, 756, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start_effect", "image/ui/start_effect.bmp", 1600, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("second_ui", "image/ui/second_ui.bmp", 871, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("second_character", "image/ui/second_character.bmp", 1005, 1716, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("second_stage_select", "image/ui/stage_select.bmp", 520, 270, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("second_stage_select_alpha", "image/ui/stage_select_alpha.bmp", 520, 270, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("character_select1", "image/ui/character_select1.bmp", 1600, 900, false , RGB(255, 0, 255));
	IMAGEMANAGER->addImage("character_select2", "image/ui/character_select2.bmp", 1600, 900, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("door_img", "image/ui/UI_UnLocked_Door.bmp", 78, 114, true, RGB(255, 0, 255));

	_titleState = TITLE_FIRST;

	_selectArrow = IMAGEMANAGER->findImage("select_arrow");

	_isStart = true;
	_arrowX = 250;
	_arrowY = 450;

	_misakoX = -300;
	_kyokoX = 1600;
	_titleY = 0;

	_secondX = 1600;
	_stage1X = _stage2X = _stage3X = 1600;
	_stage1Alpha = 0;
	_stage2Alpha = 200;
	_stage3Alpha = 200;

	_selectCount = 1;

	_effectAlpha = 0;

	_stageCount = 0;

	_nextScene = false;
	_selectPlayer = true;

	_isFade = true;
	_fade = true;

	_stage1Str = INIDATA->loadDataString("SELECT_STAGE", "STAGE1", "STAGE");
	_stage2Str = INIDATA->loadDataString("SELECT_STAGE", "STAGE2", "STAGE");
	_stage3Str = INIDATA->loadDataString("SELECT_STAGE", "STAGE3", "STAGE");

	return S_OK;
}

void titleStage::render()
{
	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT font, oldFont;
	RECT rcText1 = RectMake(_stage1X + 50, 200, 1100, 400);
	RECT rcText2 = RectMake(_stage2X + 50, 450, 1100, 400);
	RECT rcText3 = RectMake(_stage3X + 50, 700, 1100, 400);

	switch (_titleState)
	{
	case TITLE_FIRST:
		IMAGEMANAGER->findImage("start_back")->render(getMemDC());
		IMAGEMANAGER->findImage("start_kyoko")->render(getMemDC(), _kyokoX, 100);
		IMAGEMANAGER->findImage("start_misako")->render(getMemDC(), _misakoX, 100);
		IMAGEMANAGER->findImage("start_frame")->render(getMemDC());
		IMAGEMANAGER->findImage("start_menu")->render(getMemDC(), 350, WINSIZEY / 2 + 30);
		IMAGEMANAGER->findImage("start_title")->render(getMemDC(), 180, _titleY);
		if (_isFade)
			IMAGEMANAGER->findImage("start_effect")->alphaRender(getMemDC(), _effectAlpha);

		_selectArrow->render(getMemDC(), _arrowX, _arrowY);
		break;
	case TITLE_SECOND:
		IMAGEMANAGER->findImage("start_back")->render(getMemDC());
		IMAGEMANAGER->findImage("second_ui")->render(getMemDC(), 800,0);
		IMAGEMANAGER->findImage("start_frame")->render(getMemDC());
		IMAGEMANAGER->findImage("second_character")->render(getMemDC(), _secondX,-180);


		IMAGEMANAGER->findImage("second_stage_select")->render(getMemDC(), _stage1X, 70);
		font = CreateFont(40, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY견고딕"));
		oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		DrawText(getMemDC(), TEXT(_stage1Str.c_str()), strlen(_stage1Str.c_str()), &rcText1, DT_LEFT | DT_WORDBREAK);
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		IMAGEMANAGER->findImage("second_stage_select_alpha")->alphaRender(getMemDC(), _stage1X, 70, _stage1Alpha);

		IMAGEMANAGER->findImage("second_stage_select")->render(getMemDC(), _stage2X, 320);
		font = CreateFont(40, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY견고딕"));
		oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		DrawText(getMemDC(), TEXT(_stage2Str.c_str()), strlen(_stage2Str.c_str()), &rcText2, DT_LEFT | DT_WORDBREAK);
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		IMAGEMANAGER->findImage("second_stage_select_alpha")->alphaRender(getMemDC(), _stage2X, 320, _stage2Alpha);

		IMAGEMANAGER->findImage("second_stage_select")->render(getMemDC(), _stage3X, 570);
		font = CreateFont(40, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY견고딕"));
		oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		DrawText(getMemDC(), TEXT(_stage3Str.c_str()), strlen(_stage3Str.c_str()), &rcText3, DT_LEFT | DT_WORDBREAK);
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		IMAGEMANAGER->findImage("second_stage_select_alpha")->alphaRender(getMemDC(), _stage3X, 570, _stage3Alpha);

		break;
	case TITLE_THIRD:
		if (_selectPlayer)
		{
			IMAGEMANAGER->findImage("character_select1")->render(getMemDC());
		}
		else
		{
			IMAGEMANAGER->findImage("character_select2")->render(getMemDC());
		}
		break;
	}
}

void titleStage::update()
{
	switch (_titleState)
	{
	case TITLE_FIRST:
		if (_titleY < 130)
		{
			_titleY += 15;
		}


		if (_misakoX < 700)
		{
			_misakoX += 55;
		}

		if (_kyokoX > 980)
		{
			_kyokoX -= 35;
		}

		if (_isFade)
		{
			if (_effectAlpha > 180)
				_fade = false;

			if (_fade)
				_effectAlpha += 25;
			else
			{
				_effectAlpha -= 25;
				if (_effectAlpha <= 0)
				{
					_isFade = false;
				}
			}
		}

		// 타이틀 화면 조종 키
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			SOUNDMANAGER->play("init", 1.0f);
			if (!_isStart)
				_isStart = true;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			SOUNDMANAGER->play("init", 1.0f);
			if (_isStart)
				_isStart = false;
		}

		// 타이틀 화면 화살표 조정
		if (_isStart)
		{
			_arrowY = 480;

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				SOUNDMANAGER->play("informationSelect", 1.0f);
				// 다음 씬으로 넘기기
				//_nextScene = true;
				_titleState = TITLE_SECOND;
			}
		}
		else
		{
			_arrowY = 530;

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				SOUNDMANAGER->play("informationSelect", 1.0f);
				// 게임 종료
				PostQuitMessage(0);
			}
		}
		break;
	case TITLE_SECOND:

		if (_stageCount == 4)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				SOUNDMANAGER->play("select", 1.0f);
				if (_selectCount > 1)
					_selectCount--;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				SOUNDMANAGER->play("select", 1.0f);
				if (_selectCount < 3)
					_selectCount++;
			}

			switch (_selectCount)
			{
			case 1:
				_stage1Alpha = 0;
				_stage2Alpha = 200;
				_stage3Alpha = 200;

				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					SOUNDMANAGER->play("gameStart", 0.5f);

					if (_stage1Str == "STAGE 1")
					{
						_stage1Start = true;
					}
					else if (_stage1Str == "STAGE 2")
					{
						_stage2Start = true;
					}
					else if (_stage1Str == "STAGE 3")
					{
						_stage3Start = true;
					}
					else
					{
						_titleState = TITLE_THIRD;
					}
				}
				break;
			case 2:
				_stage1Alpha = 200;
				_stage2Alpha = 0;
				_stage3Alpha = 200;

				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					SOUNDMANAGER->play("gameStart", 0.5f);

					if (_stage2Str == "STAGE 1")
					{
						_stage1Start = true;
					}
					else if (_stage2Str == "STAGE 2")
					{
						_stage2Start = true;
					}
					else if (_stage2Str == "STAGE 3")
					{
						_stage3Start = true;
					}
					else
					{
						_titleState = TITLE_THIRD;
					}
				}
				break;
			case 3:
				_stage1Alpha = 200;
				_stage2Alpha = 200;
				_stage3Alpha = 0;

				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					SOUNDMANAGER->play("gameStart", 0.5f);

					if (_stage3Str == "STAGE 1")
					{
						_stage1Start = true;
					}
					else if (_stage3Str == "STAGE 2")
					{
						_stage2Start = true;
					}
					else if (_stage3Str == "STAGE 3")
					{
						_stage3Start = true;
					}
					else
					{
						_titleState = TITLE_THIRD;
					}
				}
				break;
			}

		}

		switch (_stageCount)
		{
		case 0:
			_secondX -= 60;
			if (_secondX < -50)
				_stageCount = 1;
			break;
		case 1:
			_stage1X -= 30;
			if (_stage1X <= 960)
				_stageCount = 2;
			break;
		case 2:
			_stage2X -= 30;
			if (_stage2X <= 910)
				_stageCount = 3;
			break;
		case 3:
			_stage3X -= 30;
			if (_stage3X <= 880)
				_stageCount = 4;
			break;
		}
		break;
	case TITLE_THIRD:
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			SOUNDMANAGER->play("select", 1.0f);
			_selectPlayer = true;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			SOUNDMANAGER->play("select", 1.0f);
			_selectPlayer = false;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_nextScene = true;
		}
		break;
	}
	
}

void titleStage::release()
{
}
