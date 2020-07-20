#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"


loadingScene::loadingScene()
	: _background(nullptr), _loadingBar(nullptr),
	_currentCount(NULL)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("로딩배경", "리그오브레전드로딩.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);


	//쓰레드를 사용하려면
	CreateThread(
		NULL,				//스레드의 보안속성(자식윈도우가 존재할때) 핸들로 자식인지 부모인지 파악
		NULL,				//스레드의 스택크기(NULL로 두면 메인쓰레드 크기와 동일)
		threadfunction,		//스레드 사용할 함수 명
		this,				//스레드의 매개변수(this로 하면 본 클래스)
		NULL,				//스레드의 특성(NULL로 두면 바로 실행)
		NULL				//스레드의 생성 후 스레드의 ID를 넘겨준다 보통은 NULL로 둠
	);


	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("협곡씬");
	}


}

void loadingScene::render()
{
	_background->render(getMemDC());
	_loadingBar->render();
}

DWORD CALLBACK threadfunction(LPVOID lpParameter)
{
	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		IMAGEMANAGER->addImage("인게임", "시작화면.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
		//슬립 안걸면 넘 빠름...
		Sleep(1);

		loadingHelper->_currentCount++;
	}
	
	return 0;
}
