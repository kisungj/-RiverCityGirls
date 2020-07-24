#include "stdafx.h"
#include "stageBoss.h"
#include "player.h"
#include "boss.h"
HRESULT stageBoss::init(player* player, boss* boss)
{
	_boss = boss;

	_player = player;
	_player->setMapStr("보스배경pixel"); // 픽셀 충돌
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2538 - WINSIZEX, 1000 - WINSIZEY);

	POINTFLOAT temp;
	temp.x = 2538 - 800;
	temp.y = 1000 - 450;
	EVENTMANAGER->addEvent(new iCameraMove(temp, 800.f, &_isTemp));
	EVENTMANAGER->addEvent(new iWaitForSecond(50.f));
	temp.x = 800;
	temp.y = 1000 - 450;
	EVENTMANAGER->addEvent(new iCameraMove(temp, 800.f, &_isDialog));
	
	return S_OK;
}

void stageBoss::render()
{
	_boss->render();
}

void stageBoss::update()
{
	cout << _isDialog << endl;
	if (!EVENTMANAGER->isEvnet())
	{
		CAMERAMANAGER->setX(_player->getPlayerX());
		CAMERAMANAGER->setY(_player->getPlayerY());
	}

}

void stageBoss::release()
{

}
