#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	_playerScene   = new testPlayerScene;
	_enemyScene    = new testEnemyScene;
	_bossScene     = new testBossScene;
	_uiScene       = new testUIScene;
	_obstacleScene = new testObstcle;
	SCENEMANAGER->addScene("PLAYER_SCENE", _playerScene);
	SCENEMANAGER->addScene("ENEMY_SCENE", _enemyScene);
	SCENEMANAGER->addScene("BOSS_SCENE", _bossScene);
	SCENEMANAGER->addScene("UI_SCENE", _uiScene);
	SCENEMANAGER->addScene("OBSTACLE_SCENE", _obstacleScene);

	SCENEMANAGER->changeScene("PLAYER_SCENE");
	// ======================================================== //
	_player = new player;
	_player->init();

	_itemManager = new itemManager;
	_obstacleManager = new obstacleManager;
	_enemyManager = new enemyManager;


	_stage1 = new stage1;
	_stage1->init(_obstacleManager,_itemManager, _enemyManager, _player);

	_stage2 = new stage2;
	_stage2->init(_obstacleManager, _itemManager, _enemyManager);

	SCENEMANAGER->addScene("STAGE1_SCENE", _stage1);
	SCENEMANAGER->changeScene("STAGE1_SCENE");
	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();
	
	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		_itemManager->getVItem()[i]->render();
	}
	for (int i = 0; i < _obstacleManager->getVObstacle().size(); i++)
	{
		_obstacleManager->getVObstacle()[i]->render();
	}
	for (int i = 0; i < _enemyManager->getVBoy().size(); i++)
	{
		_enemyManager->getVBoy()[i]->render();
	}

	_player->render();
}

void stageManager::update()
{
	SCENEMANAGER->update();

	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		_itemManager->getVItem()[i]->update();
	}
	for (int i = 0; i < _obstacleManager->getVObstacle().size(); i++)
	{
		_obstacleManager->getVObstacle()[i]->update();
	}
	for (int i = 0; i < _enemyManager->getVBoy().size(); i++)
	{
		_enemyManager->getVBoy()[i]->update();
		_enemyManager->getVBoy()[i]->directionCheck(_player->getPlayerRect(), _player->getPlayerX(), _player->getPlayerY());
	}

	_player->update();
	// ================================================================
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("PLAYER_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->changeScene("ENEMY_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->changeScene("BOSS_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F4)) SCENEMANAGER->changeScene("UI_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F5)) SCENEMANAGER->changeScene("OBSTACLE_SCENE");
}

void stageManager::release()
{
	_player->release();

	SCENEMANAGER->release();
}
