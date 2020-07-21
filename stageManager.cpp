#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	_playerScene = new testPlayerScene;
	_enemyScene  = new testEnemyScene;
	_bossScene   = new testBossScene;
	_uiScene     = new testUIScene;

	SCENEMANAGER->addScene("PLAYER_SCENE", _playerScene);
	SCENEMANAGER->addScene("ENEMY_SCENE", _enemyScene);
	SCENEMANAGER->addScene("BOSS_SCENE", _bossScene);
	SCENEMANAGER->addScene("UI_SCENE", _uiScene);

	SCENEMANAGER->changeScene("PLAYER_SCENE");

	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
}

void stageManager::update()
{
	SCENEMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("PLAYER_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->changeScene("ENEMY_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->changeScene("BOSS_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F4)) SCENEMANAGER->changeScene("UI_SCENE");
}

void stageManager::release()
{
	SCENEMANAGER->release();
}
