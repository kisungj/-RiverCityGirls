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

	_loading = IMAGEMANAGER->findImage("loading_sprite");
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

	_changeStageNum = 0;


	_dialogIndex = 1;
	_dialogChatCount = 2;
	_dialogPlayerX = -200;
	_dialogBossX = 1300;
	//참조
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


	if (_isLoading)
	{
		IMAGEMANAGER->findImage("phone_active")->render(getMemDC());
		_loading->frameRender(getMemDC(), WINSIZEX - 300, WINSIZEY - 250, _loading->getFrameX(), 0);
	}

	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT font, oldFont;
	RECT rcText = RectMake(400, WINSIZEY - 75, 1100, 400);

	font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("HY견고딕"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	if (_stageBoss->getIsDialog())
	{
		IMAGEMANAGER->findImage("phone_active")->alphaRender(getMemDC(), 100);
		if (_dialogTypeStr == "B")
		{
			IMAGEMANAGER->findImage("s_boss_name")->render(getMemDC(), 200, WINSIZEY - 80);
			IMAGEMANAGER->findImage("misuzu_img")->render(getMemDC(), _dialogBossX, 200);
		}
		if (_dialogTypeStr == "M")
		{
			IMAGEMANAGER->findImage("s_misako_name")->render(getMemDC(), 200, WINSIZEY - 80);
			IMAGEMANAGER->findImage("misako_img")->render(getMemDC(), _dialogPlayerX, 210);
		}
		if (_dialogTypeStr == "K")
		{
			IMAGEMANAGER->findImage("s_kyoko_name")->render(getMemDC(), 200, WINSIZEY - 80);
			IMAGEMANAGER->findImage("kyoko_img")->render(getMemDC(), _dialogPlayerX, 210);
		}
		DrawText(getMemDC(), TEXT(_dialogTalkStr.c_str()), _dialogChatCount, &rcText, DT_LEFT | DT_WORDBREAK);
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	//ZORDERMANAGER->zOrderClear();
}

void stageManager::update()
{
	EVENTMANAGER->update();
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
	

	if (!_ui->getIsPhone() && !_isLoading && !_stageBoss->getIsDialog())
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

	if (_stageBoss->getIsDialog())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_dialogIndex == 13 && _dialogChatCount == strlen(_dialogTempStr.c_str()))
			{
				_stageBoss->setIsDialog(false);
				return;
			}
			if (_dialogChatCount < strlen(_dialogTempStr.c_str()))
			{
				_dialogChatCount = strlen(_dialogTempStr.c_str());
			}
			else
			{
				_dialogIndex += 1;
				_dialogChatCount = 0;
				_dialogPlayerX = -200;
				_dialogBossX = 1300;
			}
		}

		sprintf_s(_dialogIndexStr, "TALK%d", _dialogIndex);
		_dialogTempStr = INIDATA->loadDataString("TALK", "TALK", _dialogIndexStr);

		_dialogTypeStr = _dialogTempStr.front();
		_dialogTalkStr = _dialogTempStr.substr(1, _dialogTempStr.length());


		if (_dialogChatCount < strlen(_dialogTempStr.c_str()))
		{
			_dialogChatCount += 0.5f;
		}

		if (_dialogPlayerX < 0)
		{
			_dialogPlayerX += 5;
		}
		if (_dialogBossX > 1000)
		{
			_dialogBossX -= 5;
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

	if (_isLoading)
	{	
		_loadingTimer++;

		_loadingFrameTimer++;
		if (_loadingFrameTimer > 10)
		{
			if (_loading->getFrameX() >= _loading->getMaxFrameX())
			{
				_loading->setFrameX(-1);
			}
			_loading->setFrameX(_loading->getFrameX() + 1);
			_loadingFrameTimer = 0;
		}


		if (_loadingTimer > 150)
		{
			switch (_changeStageNum)
			{
			case 1:
				_obstacleManager->release();
				_enemyManager->release();
				_itemManager->release();
				SCENEMANAGER->changeScene("STAGE1_SCENE");
				_stage1->init(_obstacleManager, _itemManager, _enemyManager, _player);
				_title->setNextScene(false);
				_curStageName = "STAGE1_SCENE";
				_loadingTimer = 0;
				_isLoading = false;
				break;
			case 2:
				_obstacleManager->release();
				_enemyManager->release();
				_itemManager->release();
				SCENEMANAGER->changeScene("STAGE2_SCENE");
				_stage2->init(_obstacleManager, _itemManager, _enemyManager, _player);
				_curStageName = "STAGE2_SCENE";
				_loadingTimer = 0;
				_isLoading = false;
				break;
			case 3:
				_obstacleManager->release();
				_enemyManager->release();
				_itemManager->release();
				_boss->init();
				SCENEMANAGER->changeScene("STAGEBOSS_SCENE");
				_stageBoss->init(_player, _boss);
				_curStageName = "STAGEBOSS_SCENE";
				_player->setShadowX(WINSIZEX / 2 - 330);
				_player->setShadowY(WINSIZEY / 2 + 230);
				_loadingTimer = 0;
				_isLoading = false;
				break;
			}
			_loadingTimer = 0;
			_isLoading = false;
		}
	}

	if (_curStageName == "TITLE_SCENE")
	{
		if (_title->getNextScene())
		{
			_changeStageNum = 1;
			_isLoading = true;
		}

		if (_title->getStage1())
		{
			_changeStageNum = 1;
			_isLoading = true;
		}

		if (_title->getStage2())
		{
			_changeStageNum = 2;
			_isLoading = true;
		}

		if (_title->getStage3())
		{ 
			_changeStageNum = 3;
			_isLoading = true;
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
		_player->setShadowX(WINSIZEX / 2 - 330);
		_player->setShadowY(WINSIZEY / 2 + 230);
	}

	

	collision();
	doorCol();

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
	//플레이어와 오브젝트 충돌
	for (int i = 0; i < _obstacleManager->getVObstacle().size(); i++)
	{
		RECT temp;

		//자판기 때릴때
		if (IntersectRect(&temp, &_player->getAttackRect(), &_obstacleManager->getVObstacle()[i]->getObsRc()))
		{
			_obstacleManager->getVObstacle()[i]->collision();
			_itemManager->setItem(_obstacleManager->getVObstacle()[i]->getObsRc());
			_player->setAttack(0, 0, 0, 0);
		}

		//자판기하고 플레이어 충돌
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_obstacleManager->getVObstacle()[i]->getObsRc()))
		{

		}

		//기둥과 충돌할때
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_obstacleManager->getVObstacle()[i]->getPillarRc()))
		{
			_obstacleManager->getVObstacle()[i]->setAlphaValue(true);
		}
		else
		{
			_obstacleManager->getVObstacle()[i]->setAlphaValue(false);
		}
	}

	//에너미 죽을때 아이템 떨어지게?
	for (int i = 0; i < _enemyManager->getVBoy().size(); i++)
	{
		//if (_enemyManager->getVBoy()[i]->getCondition() == CONDITION::DEAD)
		//{
		//	_itemManager->setItem(_enemyManager->getVBoy()[i]->getRC());
		//}

		_itemManager->setItem(_enemyManager->getVBoy()[i]->getRC());
		_enemyManager->eraseBoy(i);
		
	}

	//플레이어와 아이템 충돌
	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		int rndGold = RND->getFromIntTo(51, 100);
		int rndSilver = RND->getFromIntTo(1, 50);

		RECT temp;

		if (IntersectRect(&temp, &_player->getPlayerRect(), &_itemManager->getVItem()[i]->getItemRc()))
		{
			//HP물약 충돌
			if (_itemManager->getVItem()[i]->getitemstate() == HP)
			{
				_ui->setInventoryUI(_itemManager->getVItem()[i]);
			}

			//POWER물약 충돌
			if (_itemManager->getVItem()[i]->getitemstate() == POWER)
			{
				_ui->setInventoryUI(_itemManager->getVItem()[i]);
			}

			//금동전 충돌
			if (_itemManager->getVItem()[i]->getitemstate() == GOLD)
			{
				_player->setMoney(rndGold);
			}

			//은동전 충돌
			if (_itemManager->getVItem()[i]->getitemstate() == SILVER)
			{
				_player->setMoney(rndSilver);
			}

			_itemManager->removeItem(i);
		}
	}
}

void stageManager::doorCol()
{
	RECT temp;
	if (IntersectRect(&temp, &_player->getPlayerRect(), &_stage1->getStage1Door()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_changeStageNum = 2;
			_isLoading = true;
		}
	}
	if (IntersectRect(&temp, &_player->getPlayerRect(), &_stage2->getBossDoor()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_changeStageNum = 3;
			_isLoading = true;
		}
	}


}
