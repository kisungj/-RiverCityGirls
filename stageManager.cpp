#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	_loading = IMAGEMANAGER->findImage("loading_sprite");
	// ======================================================== //

	_player = new player;
	_player->init();

	_ui = new ui;
	_ui->init();
	_ui->setPlayerMemoryAddressLink(_player);

	_itemManager = new itemManager;
	_obstacleManager = new obstacleManager;
	_enemyManager = new enemyManager;
	_enemyManager->setPlayerLink(_player);
	_boss	      =	new boss;

	
	_stage1 = new stage1;
	_stage2 = new stage2;	
	_stageBoss = new stageBoss;
	_title = new titleStage;
	_title->init();

	Item* _temp1 = new Item;
	_temp1->init(PANTS);
	_ui->setEquipInventoryUI(_temp1);

	Item* _temp2 = new Item;
	_temp2->init(WEAPON);
	_ui->setEquipInventoryUI(_temp2);

	Item* _temp3 = new Item;
	_temp3->init(HP);
	_ui->setInventoryUI(_temp3);

	Item* _temp4 = new Item;
	_temp4->init(POWER);
	_ui->setInventoryUI(_temp4);

	SCENEMANAGER->addScene("TITLE_SCENE", _title);
	SCENEMANAGER->addScene("STAGE1_SCENE", _stage1);
	SCENEMANAGER->addScene("STAGE2_SCENE", _stage2);
	SCENEMANAGER->addScene("STAGEBOSS_SCENE", _stageBoss);

	_curStageName = "TITLE_SCENE";
	SCENEMANAGER->changeScene(_curStageName);

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

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		ZORDERMANAGER->DebugMod();
	}

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

	//cout << _title->getSelectCount() << endl;

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		saveData();
	}

	if (_curStageName == "STAGEBOSS_SCENE")
	{
		_ui->setBossStage(true);
	}
	else
	{
		_ui->setBossStage(false);
	}
	if (!_isLoading && !_stageBoss->getIsDialog())
	{
		_ui->setBossHpGauge(_boss->getHP(), _boss->getMaxHP());
		_ui->update();
	}
	

	if (!_ui->getIsPhone() && !_isLoading && !_stageBoss->getIsDialog())
	{
		_player->update();

		_itemManager->update();
		_obstacleManager->update();
		_enemyManager->update();

		if (_curStageName == "STAGEBOSS_SCENE")
		{
			_boss->update(_player->getPlayerX(), _player->getShadowY());
		}

	}

	if (_ui->getIsPhone())
	{
		if (_ui->getUseHP())
		{
			_player->setUseHP(30);
			_ui->setUseHP(false);
		}
		if (_ui->getUsePower())
		{
			_usePowerItem = true;
			_player->setPlayerAttackPower(20);
			_ui->setUsePower(false);
		}
	}

	if (_usePowerItem)
	{
		_powerItemTimer++;

		if (_powerItemTimer > 1000)
		{
			_player->setPlayerAttackPower(-20);

			_powerItemTimer = 0;
			_usePowerItem = false;
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
				SOUNDMANAGER->play("communication", 1.0f);
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
			saveData();
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
				_player->setMapStr("pixel2");
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
				_player->setMapStr("stage2pixel");
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
				_player->setMapStr("보스배경pixel");
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
			_player->setShadowX(WINSIZEX / 2 - 230);
			_player->setShadowY(WINSIZEY / 2 + 190);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_START"), IMAGEMANAGER->findImage("PLAYER_START"));
			_player->setState(_player->getStartState());
		}

		if (_title->getStage1())
		{
			_changeStageNum = 1;
			_isLoading = true;
			_player->setShadowX(WINSIZEX / 2 - 230);
			_player->setShadowY(WINSIZEY / 2 + 190);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_START"), IMAGEMANAGER->findImage("PLAYER_START"));
			_player->setState(_player->getStartState());

		}

		if (_title->getStage2())
		{
			_changeStageNum = 2;
			_isLoading = true;
			_player->setShadowX(WINSIZEX / 2 - 440);
			_player->setShadowY(WINSIZEY / 2 + 300);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_START"), IMAGEMANAGER->findImage("PLAYER_START"));
			_player->setState(_player->getStartState());
		}

		if (_title->getStage3())
		{ 
			_changeStageNum = 3;
			_isLoading = true;
			_player->setShadowX(WINSIZEX / 2 - 440);
			_player->setShadowY(WINSIZEY / 2 + 300);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_START"), IMAGEMANAGER->findImage("PLAYER_START"));
			_player->setState(_player->getStartState());
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
	playerDead();

	_ui->setHpGauge(_player->getPlayerHp(), _player->getPlayerMaxHP());
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
			
			//자판기 때릴때는 아이템 무적권 하나만
			if (_itemCount == 0)
			{
				_itemManager->setItemMove(false);
				SOUNDMANAGER->play("vending", 1.0f);
				_itemManager->setItem(_obstacleManager->getVObstacle()[i]->getObsRc());
				_itemCount++;
			}
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

		//책상 Z-Order
		if (_player->getIsDesk() == true)
		{
			_obstacleManager->getVObstacle()[i]->setDeskZOrder(true);
		}
		else
		{
			_obstacleManager->getVObstacle()[i]->setDeskZOrder(false);
		}
	}

	//에너미 죽을때 아이템 뜨는 확률
	int rndItem = RND->getInt(10);
	//boy enemy죽을때
	for (int i = 0; i < _enemyManager->getVBoy().size(); i++)
	{
		if (_enemyManager->getVBoy()[i]->getCondition() == CONDITION::DEAD)
		{
			if (rndItem <= 4)
			{
				_itemManager->setItemMove(true);
				_itemManager->setItem(_enemyManager->getVBoy()[i]->getRC());
			}
			_enemyManager->eraseBoy(i);
		}
	}

	////girl enemy죽을때
	for (int i = 0; i < _enemyManager->getVGirl().size(); i++)
	{
		if (_enemyManager->getVGirl()[i]->getCondition() == CONDITION::DEAD)
		{
			if (rndItem <= 4)
			{
				_itemManager->setItemMove(true);
				_itemManager->setItem(_enemyManager->getVGirl()[i]->getRC());
			}
			_enemyManager->eraseGirl(i);
		}
	}

	////cheer enemy죽을때
	for (int i = 0; i < _enemyManager->getVCheer().size(); i++)
	{
		if(_enemyManager->getVCheer()[i]->getCondition() == CONDITION::DEAD)
		{
			if (rndItem <= 4)
			{
				_itemManager->setItemMove(true);
				_itemManager->setItem(_enemyManager->getVCheer()[i]->getRC());
			}
			_enemyManager->eraseCheer(i);
		}
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
				SOUNDMANAGER->play("item", 0.7f);
				_ui->setInventoryUI(_itemManager->getVItem()[i]);
			}

			//POWER물약 충돌
			if (_itemManager->getVItem()[i]->getitemstate() == POWER)
			{
				SOUNDMANAGER->play("item", 0.7f);
				_ui->setInventoryUI(_itemManager->getVItem()[i]);
			}

			//금동전 충돌
			if (_itemManager->getVItem()[i]->getitemstate() == GOLD)
			{
				SOUNDMANAGER->play("money", 0.7f);
				_player->setMoney(rndGold);
			}

			//은동전 충돌
			if (_itemManager->getVItem()[i]->getitemstate() == SILVER)
			{
				SOUNDMANAGER->play("money", 0.7f);
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
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			_changeStageNum = 2;
			_isLoading = true;
			_player->setIsJumping(false);
			_player->setDirectionX(true);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			_player->setState(_player->getIdleState());
			_player->setShadowX(WINSIZEX / 2 + 1700);
			_player->setShadowY(WINSIZEY / 2 + 270);
		}
	}

	if (IntersectRect(&temp, &_player->getPlayerRect(), &_stage2->getStage2Door()))
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			_changeStageNum = 1;
			_isLoading = true;
			_player->setIsJumping(false);
			_player->setDirectionX(true);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			_player->setState(_player->getIdleState());
			_player->setShadowX(WINSIZEX / 2 + 850);
			_player->setShadowY(WINSIZEY / 2 + 210);
		}
	}
	if (IntersectRect(&temp, &_player->getPlayerRect(), &_stage2->getBossDoor()))
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			_changeStageNum = 3;
			_isLoading = true;
			_player->setIsJumping(false);
			_player->setDirectionX(true);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			_player->setState(_player->getIdleState());
			_player->setShadowX(WINSIZEX / 2 - 440);
			_player->setShadowY(WINSIZEY / 2 + 300);
		}
	}


}

void stageManager::playerDead()
{
	if (_player->getGameOver())
	{
		SOUNDMANAGER->play("gameOver", 0.5f);
		if (_curStageName == "STAGE1_SCENE")
		{
			_player->init();
			_changeStageNum = 1;
			_isLoading = true;
			_player->setShadowX(WINSIZEX / 2 - 230);
			_player->setShadowY(WINSIZEY / 2 + 190);
			_player->setAni(KEYANIMANAGER->findAnimation("P_RIGHT_START"), IMAGEMANAGER->findImage("PLAYER_START"));


		}
		if (_curStageName == "STAGE2_SCENE")
		{
			_player->init();
			_changeStageNum = 2;
			_isLoading = true;
			_player->setShadowX(WINSIZEX / 2 - 440);
			_player->setShadowY(WINSIZEY / 2 + 300);
		}

		if (_curStageName == "STAGEBOSS_SCENE")
		{
			_player->init();
			_changeStageNum = 3;
			_isLoading = true;
			_player->setShadowX(WINSIZEX / 2 - 440);
			_player->setShadowY(WINSIZEY / 2 + 300);

		}
		_player->setGameOver(false);
	}

}

void stageManager::saveData()
{
	switch (_title->getSelectCount())
	{
	case 1:
		switch (_changeStageNum)
		{
		case 1:
			INIDATA->addData("STAGE1", "STAGE", "STAGE 1");
			break;
		case 2:
			INIDATA->addData("STAGE1", "STAGE", "STAGE 2");
			break;
		case 3:
			INIDATA->addData("STAGE1", "STAGE", "STAGE 3");
			break;
		}
		break;
	case 2:
		switch (_changeStageNum)
		{
		case 1:
			INIDATA->addData("STAGE2", "STAGE", "STAGE 1");
			break;
		case 2:
			INIDATA->addData("STAGE2", "STAGE", "STAGE 2");
			break;
		case 3:
			INIDATA->addData("STAGE2", "STAGE", "STAGE 3");
			break;
		}
		break;
	case 3:
		switch (_changeStageNum)
		{
		case 1:
			INIDATA->addData("STAGE3", "STAGE", "STAGE 1");
			break;
		case 2:
			INIDATA->addData("STAGE3", "STAGE", "STAGE 2");
			break;
		case 3:
			INIDATA->addData("STAGE3", "STAGE", "STAGE 3");
			break;
		}
		break;
	}
	INIDATA->iniSave("SELECT_STAGE");
}
