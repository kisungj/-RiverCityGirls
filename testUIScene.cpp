#include "stdafx.h"
#include "testUIScene.h"

HRESULT testUIScene::init()
{
	_ui = new ui;
	_ui->init();

	//INIDATA->addData("TALK", "TALK1", "M�̽���, �������� ��!");
	//INIDATA->addData("TALK", "TALK2", "K�׷�. �� ��ġ�� �ϱ� �Ⱦ�.");
	//INIDATA->addData("TALK", "TALK3", "B�� ��ġ�� ��? ����, ��մµ� �׷�. �����ó�� ��½ ���� ��������̵��� �ĸ��� �� ���� ��.");
	//INIDATA->addData("TALK", "TALK4", "M���� �Ҹ���! �ĸ� ������ ���� ���� �� �־�!");
	//INIDATA->addData("TALK", "TALK5", "B�������μ�, ����� ���� �ٺ��� ������ ������ġ�� �ʰ� �����ϴ� �� �� ���̰ŵ�.");
	//INIDATA->addData("TALK", "TALK6", "K��ġ�� �� �� �б� �л��� �ƴ��ݾ�.");
	//INIDATA->addData("TALK", "TALK7", "B���...����! �� ���� �ʿ���!!");
	//INIDATA->addData("TALK", "TALK8", "K����!!");
	//INIDATA->addData("TALK", "TALK9", "B������ �Ӹ� ���� ô���� ��! �� ����б��� 7��° �ٴϰ� �ִٰ�! �� �̽���� �б��� �� �ƴ� ���� ����!");
	//INIDATA->addData("TALK", "TALK10", "M�װ� �ƹ��� ũ�� �ٺ��� �������. �츰 �� �б��� ���� �Ŵϱ�! ���� ����!");
	//INIDATA->addData("TALK", "TALK11", "K�¾�, ��Ͽ��� ��Ű�� ���Ϸ� �� �ž�!");
	//INIDATA->addData("TALK", "TALK12", "M�ʴ� ���̳� �հ� �ٴϸ鼭 ��� ������ ����, ���̶� �� ���� �� ������.");
	//INIDATA->addData("TALK", "TALK13", "B�̰͵���, �� �� ���ڴ�! ���� �ڽĵ�...�ε�� �й����ھ�!");


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

	font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY�߰��"));
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
