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
	_inventory = new inventory;
	_obstacleManager = new obstacleManager;
	_enemyManager = new enemyManager;
	_enemyManager->setPlayerLink(_player);
	_boss	      =	new boss;

	//Item* tempItem1 = new Item;
	//tempItem1->init(HP);

	//Item* tempItem2 = new Item;
	//tempItem2->init(POWER);
	//_inventory->setInventory(tempItem2);
	//_inventory->setInventory(tempItem1);
	//_inventory->setInventory(tempItem2);
	//_inventory->setInventory(tempItem1);
	//_inventory->setInventory(tempItem2);

	//for (int i = 0; i < _inventory->getInventory().size() ; ++i)
	//{
	//	_ui->setInventoryUI(_inventory->getInventory()[i]);
	//}


	_stage1 = new stage1;
	//_stage1->init(_obstacleManager, _itemManager, _enemyManager, _player);

	_stage2 = new stage2;
	//_stage2->init(_obstacleManager, _itemManager, _enemyManager, _player);
	
	_stageBoss = new stageBoss;
	//_stageBoss->init(_player,_boss);

	_title = new titleStage;
	_title->init();

	SCENEMANAGER->addScene("TITLE_SCENE", _title);
	_curStageName = "TITLE_SCENE";
	SCENEMANAGER->changeScene(_curStageName);

	SCENEMANAGER->addScene("STAGE1_SCENE", _stage1);

	SCENEMANAGER->addScene("STAGE2_SCENE", _stage2);

	SCENEMANAGER->addScene("STAGEBOSS_SCENE", _stageBoss);

	//����
	_player->setBossLink(_boss);
	_player->setEnemyLink(_enemyManager);
	_player->setObsLink(_obstacleManager);
	_boss->setPlayerMemoryAddressLink(_player);
	return S_OK;
}

void stageManager::render()
{
	SCENEMANAGER->render();

	_itemManager->render();
	_obstacleManager->render();
	_enemyManager->render();

	_player->render();

	ZORDERMANAGER->zOrderRender();

	EFFECTMANAGER->render();

	if(_curStageName != "TITLE_SCENE")
		_ui->render();


	//ZORDERMANAGER->zOrderClear();
}

void stageManager::update()
{

	EFFECTMANAGER->update();
	SCENEMANAGER->update();
	if (_curStageName == "STAGEBOSS_SCENE")
	{
		_ui->setBossStage(true);
	}
	else
	{
		_ui->setBossStage(false);
	}
	_ui->setBossHpGauge(_boss->getHP(), _boss->getMaxHP());
	_ui->update();
	

	if (!_ui->getIsPhone())
	{
		_player->update();

		_itemManager->update();
		_obstacleManager->update();
		_enemyManager->update();

		if (_curStageName == "STAGEBOSS_SCENE")
		{
			_boss->update(_player->getPlayerX(), _player->getPlayerY());
		}

	}
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

	if (_curStageName == "TITLE_SCENE")
	{
		if (_title->getNextScene())
		{
			_obstacleManager->release();
			_enemyManager->release();
			_itemManager->release();
			SCENEMANAGER->changeScene("STAGE1_SCENE");
			_stage1->init(_obstacleManager, _itemManager, _enemyManager, _player);
			_title->setNextScene(false);
			_curStageName = "STAGE1_SCENE";
		}
	}
	

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_obstacleManager->release();
		_enemyManager->release();
		_itemManager->release();
		SCENEMANAGER->changeScene("STAGE1_SCENE");
		_stage1->init(_obstacleManager, _itemManager, _enemyManager, _player);
		_curStageName = "STAGE1_SCENE";
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_obstacleManager->release();
		_enemyManager->release();
		_itemManager->release();
		SCENEMANAGER->changeScene("STAGE2_SCENE");
		_stage2->init(_obstacleManager, _itemManager, _enemyManager, _player);
		_curStageName = "STAGE2_SCENE";
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_obstacleManager->release();
		_enemyManager->release();
		_itemManager->release();
		_boss->init();
		SCENEMANAGER->changeScene("STAGEBOSS_SCENE");
		_stageBoss->init(_player, _boss);
		_curStageName = "STAGEBOSS_SCENE";
	}

	

	collision();

	_ui->setHpGauge(_player->getPlayerHp(), _player->getPlayerMaxHP());

	//cout << ZORDERMANAGER->zOrderSize() << endl;

}

void stageManager::release()
{
	_player->release();

	SCENEMANAGER->release();
}

void stageManager::collision()
{
	//�÷��̾�� ������Ʈ �浹
	for (int i = 0; i < _obstacleManager->getVObstacle().size(); i++)
	{
		RECT temp;

		//���Ǳ� ������
		if (IntersectRect(&temp, &_player->getAttackRect(), &_obstacleManager->getVObstacle()[i]->getObsRc()))
		{
			_obstacleManager->getVObstacle()[i]->collision();
			_itemManager->setItem(_obstacleManager->getVObstacle()[i]->getObsRc());
			_player->setAttack(0, 0, 0, 0);
		}

		//���Ǳ��ϰ� �÷��̾� �浹
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_obstacleManager->getVObstacle()[i]->getObsRc()))
		{

		}

		//��հ� �浹�Ҷ�
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_obstacleManager->getVObstacle()[i]->getPillarRc()))
		{
			_obstacleManager->getVObstacle()[i]->setAlphaValue(true);
		}
		else
		{
			_obstacleManager->getVObstacle()[i]->setAlphaValue(false);
		}
	}

	//���ʹ� ������ ������ ��������?
	for (int i = 0; i < _enemyManager->getVBoy().size(); i++)
	{
		//if (_enemyManager->getVBoy()[i]->getCondition() == CONDITION::DEAD)
		//{
		//	_itemManager->setItem(_enemyManager->getVBoy()[i]->getRC());
		//}
		


		_itemManager->setItem(_enemyManager->getVBoy()[i]->getRC());
		_enemyManager->eraseBoy(i);
		
	}

	//�÷��̾�� ������ �浹
	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		int rndGold = RND->getFromIntTo(51, 100);
		int rndSilver = RND->getFromIntTo(1, 50);

		RECT temp;

		if (IntersectRect(&temp, &_player->getPlayerRect(), &_itemManager->getVItem()[i]->getItemRc()))
		{
			//HP���� �浹
			if (_itemManager->getVItem()[i]->getitemstate() == HP)
			{
				_ui->setInventoryUI(_itemManager->getVItem()[i]);
			}

			//POWER���� �浹
			if (_itemManager->getVItem()[i]->getitemstate() == POWER)
			{
				_ui->setInventoryUI(_itemManager->getVItem()[i]);
			}

			//�ݵ��� �浹
			if (_itemManager->getVItem()[i]->getitemstate() == GOLD)
			{
				_player->setMoney(rndGold);
			}

			//������ �浹
			if (_itemManager->getVItem()[i]->getitemstate() == SILVER)
			{
				_player->setMoney(rndSilver);
			}

			_itemManager->removeItem(i);
		}
	}
}
