#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	// ------------ 임시 변수 ------------ //
	loadImage();
	loadAnimation();
	_x = _y = _jumpPower = _gravity = 0;
	_state = BOSS_LEFT_IDLE;
	_rc = RectMakeCenter(_x, _y, 100, 100);
	_playerX = WINSIZEX / 2;
	_playerY = WINSIZEY / 2;
	_characterImg = IMAGEMANAGER->findImage("boss_idle");
	_shadowImg = IMAGEMANAGER->findImage("보스그림자");
	// ------------ 임시 변수 ------------ //

	_animPlayer = _anim[BOSS_LEFT_IDLE];
	_animPlayer->start();

	return S_OK;
}

void boss::release()
{
}

void boss::render()
{
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("보스배경"));
	for (int i = 0; i < BOSS_END; i++)
	{
		_anim[i]->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}


	CAMERAMANAGER->render(getMemDC(), _shadowImg, WINSIZEX / 2, WINSIZEY / 2+ 200);
	CAMERAMANAGER->aniRender(getMemDC(), _characterImg, WINSIZEX / 2, WINSIZEY / 2, _animPlayer);

}

void boss::update()
{
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 2538 - WINSIZEX, 1000 - WINSIZEY);

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_playerX += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_playerX -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerY -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_playerY += 3;
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_characterImg = IMAGEMANAGER->findImage("boss_idle");
		_animPlayer = _anim[BOSS_LEFT_IDLE];
		_animPlayer->start();
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_characterImg = IMAGEMANAGER->findImage("boss_jumpAttack");
		_animPlayer = _anim[BOSS_LEFT_JUMP_ATTACK];
		_animPlayer->start();
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_characterImg = IMAGEMANAGER->findImage("boss_death");
		_animPlayer = _anim[BOSS_LEFT_DEATH];
		_animPlayer->start();
	}
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_characterImg = IMAGEMANAGER->findImage("boss_heavyAttack");
		_animPlayer = _anim[BOSS_LEFT_HEAVY_ATTACK];
		_animPlayer->start();
	}

	CAMERAMANAGER->setX(_playerX + 200);
	CAMERAMANAGER->setY(_playerY + 200);
}

void boss::loadImage()
{
	IMAGEMANAGER->addImage("보스배경", "image/map/bossMap1.bmp", 2538, 1000, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스그림자", "image/boss/boss_shadow.bmp", 128, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_idle", "image/boss/boss_idle.bmp", 3792, 776, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit", "image/boss/boss_hit.bmp", 3096, 736, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_jumpAttack", "image/boss/boss_jumpAttack.bmp", 7776, 824, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss/boss_walk.bmp", 2360, 736, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_death", "image/boss/boss_death.bmp", 5772, 720, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_attack_elbow", "image/boss/boss_attack_elbow.bmp", 3652, 800, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_angry", "image/boss/boss_angry.bmp", 5120, 712, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_attack", "image/boss/boss_attack.bmp", 6384, 712, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_dash", "image/boss/boss_dash.bmp", 4368, 704, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_heavyAttack", "image/boss/boss_heavyAttack.bmp", 13936, 728, 26, 2, true, RGB(255, 0, 255));
}

void boss::loadAnimation()
{
	// --------------- LEFT IDLE --------------- //
	_anim[BOSS_LEFT_IDLE] = new animation;
	_anim[BOSS_LEFT_IDLE]->init(IMAGEMANAGER->findImage("boss_idle")->getWidth(), IMAGEMANAGER->findImage("boss_idle")->getHeight()
		,IMAGEMANAGER->findImage("boss_idle")->getFrameWidth(), IMAGEMANAGER->findImage("boss_idle")->getFrameHeight());
	_anim[BOSS_LEFT_IDLE]->setPlayFrame(23, 12, false, true);
	_anim[BOSS_LEFT_IDLE]->setFPS(1);
	// --------------- LEFT IDLE --------------- //

	// --------------- RIGHT IDLE --------------- //
	_anim[BOSS_RIGHT_IDLE] = new animation;
	_anim[BOSS_RIGHT_IDLE]->init(IMAGEMANAGER->findImage("boss_idle")->getWidth(), IMAGEMANAGER->findImage("boss_idle")->getHeight()
		, IMAGEMANAGER->findImage("boss_idle")->getFrameWidth(), IMAGEMANAGER->findImage("boss_idle")->getFrameHeight());
	_anim[BOSS_RIGHT_IDLE]->setPlayFrame(0, 11, false, true);
	_anim[BOSS_RIGHT_IDLE]->setFPS(1);
	// --------------- RIGHT IDLE --------------- //

	// --------------- LEFT WALK --------------- //
	_anim[BOSS_LEFT_WALK] = new animation;
	_anim[BOSS_LEFT_WALK]->init(IMAGEMANAGER->findImage("boss_walk")->getWidth(), IMAGEMANAGER->findImage("boss_walk")->getHeight()
		, IMAGEMANAGER->findImage("boss_walk")->getFrameWidth(), IMAGEMANAGER->findImage("boss_walk")->getFrameHeight());
	_anim[BOSS_LEFT_WALK]->setPlayFrame(19, 10, false, true);
	_anim[BOSS_LEFT_WALK]->setFPS(1);
	// --------------- LEFT WALK --------------- //

	// --------------- RIGHT WALK --------------- //
	_anim[BOSS_RIGHT_WALK] = new animation;
	_anim[BOSS_RIGHT_WALK]->init(IMAGEMANAGER->findImage("boss_walk")->getWidth(), IMAGEMANAGER->findImage("boss_walk")->getHeight()
		, IMAGEMANAGER->findImage("boss_walk")->getFrameWidth(), IMAGEMANAGER->findImage("boss_walk")->getFrameHeight());
	_anim[BOSS_RIGHT_WALK]->setPlayFrame(0, 9, false, true);
	_anim[BOSS_RIGHT_WALK]->setFPS(1);
	// --------------- RIGHT WALK --------------- //

	// --------------- LEFT ATTACK ELBOW --------------- //
	_anim[BOSS_LEFT_ATTACK_ELBOW] = new animation;
	_anim[BOSS_LEFT_ATTACK_ELBOW]->init(IMAGEMANAGER->findImage("boss_attack_elbow")->getWidth(), IMAGEMANAGER->findImage("boss_attack_elbow")->getHeight()
		, IMAGEMANAGER->findImage("boss_attack_elbow")->getFrameWidth(), IMAGEMANAGER->findImage("boss_attack_elbow")->getFrameHeight());
	_anim[BOSS_LEFT_ATTACK_ELBOW]->setPlayFrame(21, 11, false, true);
	_anim[BOSS_LEFT_ATTACK_ELBOW]->setFPS(1);
	// --------------- LEFT ATTACK ELBOW --------------- //

	// --------------- RIGHT ATTACK ELBOW --------------- //
	_anim[BOSS_RIGHT_ATTACK_ELBOW] = new animation;
	_anim[BOSS_RIGHT_ATTACK_ELBOW]->init(IMAGEMANAGER->findImage("boss_attack_elbow")->getWidth(), IMAGEMANAGER->findImage("boss_attack_elbow")->getHeight()
		, IMAGEMANAGER->findImage("boss_attack_elbow")->getFrameWidth(), IMAGEMANAGER->findImage("boss_attack_elbow")->getFrameHeight());
	_anim[BOSS_RIGHT_ATTACK_ELBOW]->setPlayFrame(0, 10, false, true);
	_anim[BOSS_RIGHT_ATTACK_ELBOW]->setFPS(1);
	// --------------- RIGHT ATTACK ELBOW --------------- //

	// --------------- LEFT ATTACK JUMP --------------- //
	_anim[BOSS_LEFT_JUMP_ATTACK] = new animation;
	_anim[BOSS_LEFT_JUMP_ATTACK]->init(IMAGEMANAGER->findImage("boss_jumpAttack")->getWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameHeight());
	_anim[BOSS_LEFT_JUMP_ATTACK]->setPlayFrame(47, 24, false, true);
	_anim[BOSS_LEFT_JUMP_ATTACK]->setFPS(1);
	// --------------- LEFT ATTACK JUMP --------------- //

	// --------------- RIGHT ATTACK JUMP --------------- //
	_anim[BOSS_RIGHT_JUMP_ATTACK] = new animation;
	_anim[BOSS_RIGHT_JUMP_ATTACK]->init(IMAGEMANAGER->findImage("boss_jumpAttack")->getWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameHeight());
	_anim[BOSS_RIGHT_JUMP_ATTACK]->setPlayFrame(0, 23, false, true);
	_anim[BOSS_RIGHT_JUMP_ATTACK]->setFPS(1);
	// --------------- RIGHT ATTACK JUMP --------------- //


	// --------------- LEFT ANGRY --------------- //
	_anim[BOSS_LEFT_ANGRY] = new animation;
	_anim[BOSS_LEFT_ANGRY]->init(IMAGEMANAGER->findImage("boss_angry")->getWidth(), IMAGEMANAGER->findImage("boss_angry")->getHeight()
		, IMAGEMANAGER->findImage("boss_angry")->getFrameWidth(), IMAGEMANAGER->findImage("boss_angry")->getFrameHeight());
	_anim[BOSS_LEFT_ANGRY]->setPlayFrame(31, 16, false, true);
	_anim[BOSS_LEFT_ANGRY]->setFPS(1);
	// --------------- LEFT ANGRY --------------- //

	// --------------- RIGHT ANGRY --------------- //
	_anim[BOSS_RIGHT_ANGRY] = new animation;
	_anim[BOSS_RIGHT_ANGRY]->init(IMAGEMANAGER->findImage("boss_angry")->getWidth(), IMAGEMANAGER->findImage("boss_angry")->getHeight()
		, IMAGEMANAGER->findImage("boss_angry")->getFrameWidth(), IMAGEMANAGER->findImage("boss_angry")->getFrameHeight());
	_anim[BOSS_RIGHT_ANGRY]->setPlayFrame(0, 15, false, true);
	_anim[BOSS_RIGHT_ANGRY]->setFPS(1);
	// --------------- RIGHT ANGRY --------------- //


	// --------------- LEFT ATTACK --------------- //
	_anim[BOSS_LEFT_ATTACK] = new animation;
	_anim[BOSS_LEFT_ATTACK]->init(IMAGEMANAGER->findImage("boss_attack")->getWidth(), IMAGEMANAGER->findImage("boss_attack")->getHeight()
		, IMAGEMANAGER->findImage("boss_attack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_attack")->getFrameHeight());
	_anim[BOSS_LEFT_ATTACK]->setPlayFrame(27, 14, false, true);
	_anim[BOSS_LEFT_ATTACK]->setFPS(1);
	// --------------- LEFT ATTACK --------------- //

	// --------------- RIGHT ATTACK --------------- //
	_anim[BOSS_RIGHT_ATTACK] = new animation;
	_anim[BOSS_RIGHT_ATTACK]->init(IMAGEMANAGER->findImage("boss_attack")->getWidth(), IMAGEMANAGER->findImage("boss_attack")->getHeight()
		, IMAGEMANAGER->findImage("boss_attack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_attack")->getFrameHeight());
	_anim[BOSS_RIGHT_ATTACK]->setPlayFrame(0, 13, false, true);
	_anim[BOSS_RIGHT_ATTACK]->setFPS(1);
	// --------------- RIGHT ATTACK --------------- //

	// --------------- LEFT DASH --------------- //
	_anim[BOSS_LEFT_DASH] = new animation;
	_anim[BOSS_LEFT_DASH]->init(IMAGEMANAGER->findImage("boss_dash")->getWidth(), IMAGEMANAGER->findImage("boss_dash")->getHeight()
		, IMAGEMANAGER->findImage("boss_dash")->getFrameWidth(), IMAGEMANAGER->findImage("boss_dash")->getFrameHeight());
	_anim[BOSS_LEFT_DASH]->setPlayFrame(27, 14, false, true);
	_anim[BOSS_LEFT_DASH]->setFPS(1);
	// --------------- LEFT DASH --------------- //

	// --------------- RIGHT DASH --------------- //
	_anim[BOSS_RIGHT_DASH] = new animation;
	_anim[BOSS_RIGHT_DASH]->init(IMAGEMANAGER->findImage("boss_dash")->getWidth(), IMAGEMANAGER->findImage("boss_dash")->getHeight()
		, IMAGEMANAGER->findImage("boss_dash")->getFrameWidth(), IMAGEMANAGER->findImage("boss_dash")->getFrameHeight());
	_anim[BOSS_RIGHT_DASH]->setPlayFrame(0, 13, false, true);
	_anim[BOSS_RIGHT_DASH]->setFPS(1);
	// --------------- RIGHT DASH --------------- //

	// --------------- LEFT HIT --------------- //
	_anim[BOSS_LEFT_HIT] = new animation;
	_anim[BOSS_LEFT_HIT]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_LEFT_HIT]->setPlayFrame(17, 9, false, true);
	_anim[BOSS_LEFT_HIT]->setFPS(1);
	// --------------- LEFT HIT --------------- //

	// --------------- RIGHT HIT --------------- //
	_anim[BOSS_RIGHT_HIT] = new animation;
	_anim[BOSS_RIGHT_HIT]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_RIGHT_HIT]->setPlayFrame(0, 8, false, true);
	_anim[BOSS_RIGHT_HIT]->setFPS(1);
	// --------------- RIGHT HIT --------------- //

	// --------------- LEFT HIT --------------- //
	_anim[BOSS_LEFT_DEATH] = new animation;
	_anim[BOSS_LEFT_DEATH]->init(IMAGEMANAGER->findImage("boss_death")->getWidth(), IMAGEMANAGER->findImage("boss_death")->getHeight()
		, IMAGEMANAGER->findImage("boss_death")->getFrameWidth(), IMAGEMANAGER->findImage("boss_death")->getFrameHeight());
	_anim[BOSS_LEFT_DEATH]->setPlayFrame(25, 13, false, true);
	_anim[BOSS_LEFT_DEATH]->setFPS(1);
	// --------------- LEFT HIT --------------- //

	// --------------- RIGHT HIT --------------- //
	_anim[BOSS_RIGHT_DEATH] = new animation;
	_anim[BOSS_RIGHT_DEATH]->init(IMAGEMANAGER->findImage("boss_death")->getWidth(), IMAGEMANAGER->findImage("boss_death")->getHeight()
		, IMAGEMANAGER->findImage("boss_death")->getFrameWidth(), IMAGEMANAGER->findImage("boss_death")->getFrameHeight());
	_anim[BOSS_RIGHT_DEATH]->setPlayFrame(0, 12, false, true);
	_anim[BOSS_RIGHT_DEATH]->setFPS(1);
	// --------------- RIGHT HIT --------------- //


	// --------------- LEFT HEAVY ATTACK --------------- //
	_anim[BOSS_LEFT_HEAVY_ATTACK] = new animation;
	_anim[BOSS_LEFT_HEAVY_ATTACK]->init(IMAGEMANAGER->findImage("boss_heavyAttack")->getWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameHeight());
	_anim[BOSS_LEFT_HEAVY_ATTACK]->setPlayFrame(51, 26, false, true);
	_anim[BOSS_LEFT_HEAVY_ATTACK]->setFPS(1);
	// --------------- LEFT HEAVY ATTACK --------------- //

	// --------------- RIGHT HEAVY ATTACK --------------- //
	_anim[BOSS_RIGHT_HEAVY_ATTACK] = new animation;
	_anim[BOSS_RIGHT_HEAVY_ATTACK]->init(IMAGEMANAGER->findImage("boss_heavyAttack")->getWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameHeight());
	_anim[BOSS_RIGHT_HEAVY_ATTACK]->setPlayFrame(0, 25, false, true);
	_anim[BOSS_RIGHT_HEAVY_ATTACK]->setFPS(1);
	// --------------- RIGHT HEAVY ATTACK --------------- //

}
