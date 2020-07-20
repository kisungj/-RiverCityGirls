#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
	
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);

	_stageManager = new stageManager;
	_stageManager->init();

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2016 - WINSIZEX, 672 - WINSIZEY);

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	_stageManager->release();
}

//연산
void playGround::update()
{
	gameNode::update();

	_stageManager->update();
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================



	_stageManager->render();

	
	TIMEMANAGER->render(getMemDC());
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}
