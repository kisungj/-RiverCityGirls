#include "stdafx.h"
#include "testUIScene.h"

HRESULT testUIScene::init()
{
	_ui = new ui;
	_ui->init();

	//INIDATA->addData("TALK", "TALK1", "M미스즈, 방해하지 마!");
	//INIDATA->addData("TALK", "TALK2", "K그래. 널 다치게 하긴 싫어.");
	//INIDATA->addData("TALK", "TALK3", "B날 다치게 해? 하하, 재밌는데 그래. 너희들처럼 비쩍 마른 새끼고양이들은 파리도 못 죽일 걸.");
	//INIDATA->addData("TALK", "TALK4", "M무슨 소리야! 파리 정도는 쉽게 죽일 수 있어!");
	//INIDATA->addData("TALK", "TALK5", "B경비원으로서, 너희들 같은 바보가 수업을 땡땡이치지 않게 감시하는 게 내 일이거든.");
	//INIDATA->addData("TALK", "TALK6", "K그치만 너 이 학교 학생도 아니잖아.");
	//INIDATA->addData("TALK", "TALK7", "B요게...닥쳐! 난 돈이 필요해!!");
	//INIDATA->addData("TALK", "TALK8", "K으아!!");
	//INIDATA->addData("TALK", "TALK9", "B나보다 머리 좋은 척하지 마! 난 고등학교도 7년째 다니고 있다고! 이 미스즈보다 학교를 잘 아는 놈은 없어!");
	//INIDATA->addData("TALK", "TALK10", "M네가 아무리 크고 바보라도 상관없어. 우린 이 학교를 나갈 거니까! 지금 당장!");
	//INIDATA->addData("TALK", "TALK11", "K맞아, 쿠니오랑 리키를 구하러 갈 거야!");
	//INIDATA->addData("TALK", "TALK12", "M너는 벽이나 뚫고 다니면서 놀고 있으란 말야, 문이란 게 뭔지 알 때까지.");
	//INIDATA->addData("TALK", "TALK13", "B이것들이, 더 못 참겠다! 망항 자식들...두들겨 패버리겠어!");


	//INIDATA->iniSave("TALK");

	_index = 1;
	_chatCount = 2;
	


	return S_OK;
}

void testUIScene::render()
{
	_ui->render();

	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT font, oldFont;
	RECT rcText = RectMake(300, WINSIZEY - 100, 1000, 700);

	font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY견고딕"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	DrawText(getMemDC(), TEXT(_test.c_str()), _chatCount, &rcText, DT_LEFT | DT_WORDBREAK);
}

void testUIScene::update()
{
	_ui->update();

	if (_index != 13)
	{
		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_index += 1;
			_chatCount = 0;
		}
	}

	sprintf_s(_indexStr, "TALK%d", _index);
	_test = INIDATA->loadDataString("TALK", "TALK", _indexStr);

	//cout << _test.front() << endl;
	//_test.erase(_test.front());
	cout << _test.substr(1,_test.length()) << endl;


	if (_chatCount < strlen(_test.c_str()))
	{
		_chatCount += 0.5f;
	}
}

void testUIScene::release()
{
	SAFE_DELETE(_ui);
}
