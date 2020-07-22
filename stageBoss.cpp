#include "stdafx.h"
#include "stageBoss.h"
#include "player.h"
#include "boss.h"
HRESULT stageBoss::init(player* player, boss* boss)
{
	_boss = boss;
	
	_player = player;
	_player->setMapStr("�������pixel"); // �ȼ� �浹
	return S_OK;
}

void stageBoss::render()
{
	_boss->render();
}

void stageBoss::update()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2538 - WINSIZEX, 1000 - WINSIZEY);
	CAMERAMANAGER->setX(_player->getPlayerX());
	CAMERAMANAGER->setY(_player->getPlayerY());
	_boss->update(_player->getPlayerX(), _player->getPlayerY());
}

void stageBoss::release()
{

}
