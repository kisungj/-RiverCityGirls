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
	_background = IMAGEMANAGER->addImage("�ε����", "���׿��극����ε�.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);


	//�����带 ����Ϸ���
	CreateThread(
		NULL,				//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�) �ڵ�� �ڽ����� �θ����� �ľ�
		NULL,				//�������� ����ũ��(NULL�� �θ� ���ξ����� ũ��� ����)
		threadfunction,		//������ ����� �Լ� ��
		this,				//�������� �Ű�����(this�� �ϸ� �� Ŭ����)
		NULL,				//�������� Ư��(NULL�� �θ� �ٷ� ����)
		NULL				//�������� ���� �� �������� ID�� �Ѱ��ش� ������ NULL�� ��
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
		SCENEMANAGER->changeScene("�����");
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
		IMAGEMANAGER->addImage("�ΰ���", "����ȭ��.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
		//���� �Ȱɸ� �� ����...
		Sleep(1);

		loadingHelper->_currentCount++;
	}
	
	return 0;
}
