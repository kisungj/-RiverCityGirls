#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	_playerScene = new testPlayerScene;
	_enemyScene = new testEnemyScene;
	_bossScene = new testBossScene;
	_uiScene = new testUIScene;
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
	_ui = new ui;
	_ui->init();
	_itemManager = new itemManager;
	_obstacleManager = new obstacleManager;
	_enemyManager = new enemyManager;
	_boss	      =	new boss;
	_stage1 = new stage1;
	_stage1->init(_obstacleManager, _itemManager, _enemyManager, _player);

	_stage2 = new stage2;
	_stage2->init(_obstacleManager, _itemManager, _enemyManager, _player);

	_stageBoss = new stageBoss;
	_stageBoss->init(_player,_boss);
	SCENEMANAGER->addScene("STAGE1_SCENE", _stage1);
	SCENEMANAGER->changeScene("STAGE1_SCENE");

	SCENEMANAGER->addScene("STAGE2_SCENE", _stage2);

	SCENEMANAGER->addScene("STAGEBOSS_SCENE", _stageBoss);

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

	_ui->render();
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
	_ui->update();
	_player->update();
	// ================================================================
	//if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("PLAYER_SCENE");
	//
	//if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->changeScene("ENEMY_SCENE");
	//
	//if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->changeScene("BOSS_SCENE");
	//
	//if (KEYMANAGER->isOnceKeyDown(VK_F4)) SCENEMANAGER->changeScene("UI_SCENE");
	//
	//if (KEYMANAGER->isOnceKeyDown(VK_F5)) SCENEMANAGER->changeScene("OBSTACLE_SCENE");

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_obstacleManager->release();
		_enemyManager->release();
		_itemManager->release();
		SCENEMANAGER->changeScene("STAGE1_SCENE");
		_obstacleManager->init();
		_enemyManager->init();
		_itemManager->init();
		//---- 임시
		_obstacleManager->setObstacle(DESK);
		_enemyManager->setBoy();
		//---- 임시
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_obstacleManager->release();
		_enemyManager->release();
		_itemManager->release();
		SCENEMANAGER->changeScene("STAGE2_SCENE");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_obstacleManager->release();
		_enemyManager->release();
		_itemManager->release();
		_boss->init();
		SCENEMANAGER->changeScene("STAGEBOSS_SCENE");

	}
}

void stageManager::release()
{
	_player->release();

	SCENEMANAGER->release();
}
