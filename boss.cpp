#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	loadAnimation();
	_hp = 100;

	_jumpAlphaMax = _jumpAlpha = 200;
	_jumpAlphaMin = 70;

	_blockDistance = 5;
	_blockFriction = 0.01f;
	_x = WINSIZEX / 2 + 800;
	_z = WINSIZEY / 2 + 180;
	_y = _z - 180;
	_jumpPower = 20;
	_gravity = 0.1f;
	_rc = RectMakeCenter(_x, _y, 100, 250);
	_characterImg = IMAGEMANAGER->findImage("boss_idle");
	_shadowImg = IMAGEMANAGER->findImage("보스그림자");

	_state = BOSS_LEFT_TAUNT;
	_characterImg = IMAGEMANAGER->findImage("boss_taunt");
	_animPlayer = _anim[BOSS_LEFT_TAUNT];
	_animPlayer->start();


	return S_OK;
}

void boss::release()
{

}

void boss::render()
{
	CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage("보스배경"), IMAGEMANAGER->findImage("보스배경")->getWidth() / 2, IMAGEMANAGER->findImage("보스배경")->getHeight() / 2);

	//CAMERAMANAGER->alphaRender(getMemDC(), _shadowImg, _x, _z, _jumpAlpha);
	//CAMERAMANAGER->aniRender(getMemDC(), _characterImg, _x, _y, _animPlayer);

	// ================================ 임시 ================================ //
	if (_setActiveAttackRect)
		CAMERAMANAGER->renderRectangle(getMemDC(), _attackRect);
	//CAMERAMANAGER->renderRectangle(getMemDC(), _rc);


	//CAMERAMANAGER->renderRectangle(getMemDC(), _playerRect);

	// ================================ 임시 ================================ //
}

void boss::update(float playerX, float playerZ)
{

	// ------------------ 지워
	_playerRect = RectMakeCenter(playerX, playerZ, 110, 200);
	// ------------------ 지워


	stateUpdate(playerX, playerZ);

	if (_setActiveAttackRect)
		_attackRect = RectMakeCenter(_attackPos.x, _attackPos.y, _attackSize.x, _attackSize.y);


	if (_state != BOSS_LEFT_JUMP && _state != BOSS_RIGHT_JUMP && _state != BOSS_LEFT_JUMP_ATTACK && _state != BOSS_RIGHT_JUMP_ATTACK && _state != BOSS_LEFT_HIT3 && _state != BOSS_RIGHT_HIT3) // 점프 관련 상태일 때는 꺼주기
	{
		_y = _z - 137;
	}
	death(playerX, playerZ);

	hit(playerX, playerZ, 100);// 데미지 임시값

	changePattern(playerX, playerZ);

	_rc = RectMakeCenter(_x, _y, 100, 250);

	ZORDERMANAGER->addAlphaRender(getMemDC(), renderType::ALPHA_RENDER, _shadowImg, _x, _z, _z, _jumpAlpha);
	ZORDERMANAGER->addAniRender(getMemDC(), renderType::ANI_RENDER, _characterImg, _x, _y, _z, _animPlayer);
}

void boss::loadAnimation()
{
	// --------------- LEFT IDLE --------------- //
	_anim[BOSS_LEFT_IDLE] = new animation;
	_anim[BOSS_LEFT_IDLE]->init(IMAGEMANAGER->findImage("boss_idle")->getWidth(), IMAGEMANAGER->findImage("boss_idle")->getHeight()
		, IMAGEMANAGER->findImage("boss_idle")->getFrameWidth(), IMAGEMANAGER->findImage("boss_idle")->getFrameHeight());
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
	_anim[BOSS_LEFT_ATTACK_ELBOW]->setPlayFrame(21, 11, false, false);
	_anim[BOSS_LEFT_ATTACK_ELBOW]->setFPS(1);
	// --------------- LEFT ATTACK ELBOW --------------- //

	// --------------- RIGHT ATTACK ELBOW --------------- //
	_anim[BOSS_RIGHT_ATTACK_ELBOW] = new animation;
	_anim[BOSS_RIGHT_ATTACK_ELBOW]->init(IMAGEMANAGER->findImage("boss_attack_elbow")->getWidth(), IMAGEMANAGER->findImage("boss_attack_elbow")->getHeight()
		, IMAGEMANAGER->findImage("boss_attack_elbow")->getFrameWidth(), IMAGEMANAGER->findImage("boss_attack_elbow")->getFrameHeight());
	_anim[BOSS_RIGHT_ATTACK_ELBOW]->setPlayFrame(0, 10, false, false);
	_anim[BOSS_RIGHT_ATTACK_ELBOW]->setFPS(1);
	// --------------- RIGHT ATTACK ELBOW --------------- //

	// --------------- LEFT JUMP --------------- //
	_anim[BOSS_LEFT_JUMP] = new animation;
	_anim[BOSS_LEFT_JUMP]->init(IMAGEMANAGER->findImage("boss_jumpAttack")->getWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameHeight());
	_anim[BOSS_LEFT_JUMP]->setPlayFrame(47, 38, false, false);
	_anim[BOSS_LEFT_JUMP]->setFPS(1);
	// --------------- LEFT JUMP --------------- //

	// --------------- RIGHT JUMP --------------- //
	_anim[BOSS_RIGHT_JUMP] = new animation;
	_anim[BOSS_RIGHT_JUMP]->init(IMAGEMANAGER->findImage("boss_jumpAttack")->getWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameHeight());
	_anim[BOSS_RIGHT_JUMP]->setPlayFrame(0, 9, false, false);
	_anim[BOSS_RIGHT_JUMP]->setFPS(1);
	// --------------- RIGHT JUMP --------------- //

	// --------------- LEFT ATTACK JUMP --------------- //
	_anim[BOSS_LEFT_JUMP_ATTACK] = new animation;
	_anim[BOSS_LEFT_JUMP_ATTACK]->init(IMAGEMANAGER->findImage("boss_jumpAttack")->getWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameHeight());
	int leftJumpAttack[] = { 37,37,36,35,34,33,32,31,30,29,28,27,26,25,24 };
	_anim[BOSS_LEFT_JUMP_ATTACK]->setPlayFrame(leftJumpAttack, sizeof(leftJumpAttack) / sizeof(leftJumpAttack[0]));
	_anim[BOSS_LEFT_JUMP_ATTACK]->setFPS(1);
	// --------------- LEFT ATTACK JUMP --------------- //

	// --------------- RIGHT ATTACK JUMP --------------- //
	_anim[BOSS_RIGHT_JUMP_ATTACK] = new animation;
	_anim[BOSS_RIGHT_JUMP_ATTACK]->init(IMAGEMANAGER->findImage("boss_jumpAttack")->getWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_jumpAttack")->getFrameHeight());
	int rightJumpAttack[] = { 10,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
	_anim[BOSS_RIGHT_JUMP_ATTACK]->setPlayFrame(rightJumpAttack, sizeof(rightJumpAttack) / sizeof(leftJumpAttack[0]));
	_anim[BOSS_RIGHT_JUMP_ATTACK]->setFPS(1);
	// --------------- RIGHT ATTACK JUMP --------------- //


	// --------------- LEFT ANGRY --------------- //
	_anim[BOSS_LEFT_ANGRY] = new animation;
	_anim[BOSS_LEFT_ANGRY]->init(IMAGEMANAGER->findImage("boss_angry")->getWidth(), IMAGEMANAGER->findImage("boss_angry")->getHeight()
		, IMAGEMANAGER->findImage("boss_angry")->getFrameWidth(), IMAGEMANAGER->findImage("boss_angry")->getFrameHeight());
	_anim[BOSS_LEFT_ANGRY]->setPlayFrame(31, 16, false, false);
	_anim[BOSS_LEFT_ANGRY]->setFPS(1);
	// --------------- LEFT ANGRY --------------- //

	// --------------- RIGHT ANGRY --------------- //
	_anim[BOSS_RIGHT_ANGRY] = new animation;
	_anim[BOSS_RIGHT_ANGRY]->init(IMAGEMANAGER->findImage("boss_angry")->getWidth(), IMAGEMANAGER->findImage("boss_angry")->getHeight()
		, IMAGEMANAGER->findImage("boss_angry")->getFrameWidth(), IMAGEMANAGER->findImage("boss_angry")->getFrameHeight());
	_anim[BOSS_RIGHT_ANGRY]->setPlayFrame(0, 15, false, false);
	_anim[BOSS_RIGHT_ANGRY]->setFPS(1);
	// --------------- RIGHT ANGRY --------------- //


	// --------------- LEFT ATTACK --------------- //
	_anim[BOSS_LEFT_ATTACK] = new animation;
	_anim[BOSS_LEFT_ATTACK]->init(IMAGEMANAGER->findImage("boss_attack")->getWidth(), IMAGEMANAGER->findImage("boss_attack")->getHeight()
		, IMAGEMANAGER->findImage("boss_attack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_attack")->getFrameHeight());
	_anim[BOSS_LEFT_ATTACK]->setPlayFrame(27, 14, false, false);
	_anim[BOSS_LEFT_ATTACK]->setFPS(1);
	// --------------- LEFT ATTACK --------------- //

	// --------------- RIGHT ATTACK --------------- //
	_anim[BOSS_RIGHT_ATTACK] = new animation;
	_anim[BOSS_RIGHT_ATTACK]->init(IMAGEMANAGER->findImage("boss_attack")->getWidth(), IMAGEMANAGER->findImage("boss_attack")->getHeight()
		, IMAGEMANAGER->findImage("boss_attack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_attack")->getFrameHeight());
	_anim[BOSS_RIGHT_ATTACK]->setPlayFrame(0, 13, false, false);
	_anim[BOSS_RIGHT_ATTACK]->setFPS(1);
	// --------------- RIGHT ATTACK --------------- //

	// --------------- LEFT DASH --------------- //
	_anim[BOSS_LEFT_DASH] = new animation;
	_anim[BOSS_LEFT_DASH]->init(IMAGEMANAGER->findImage("boss_dash")->getWidth(), IMAGEMANAGER->findImage("boss_dash")->getHeight()
		, IMAGEMANAGER->findImage("boss_dash")->getFrameWidth(), IMAGEMANAGER->findImage("boss_dash")->getFrameHeight());
	//_anim[BOSS_LEFT_DASH]->setPlayFrame(27, 14, false, false);
	int leftDash[] = { 27,26,25,24,23,22,21,20,19,18,17,16,15,23,22,21,20,19,18,17,16,15,14 };
	_anim[BOSS_LEFT_DASH]->setPlayFrame(leftDash, sizeof(leftDash) / sizeof(leftDash[0]));
	_anim[BOSS_LEFT_DASH]->setFPS(1);
	// --------------- LEFT DASH --------------- //

	// --------------- RIGHT DASH --------------- //
	_anim[BOSS_RIGHT_DASH] = new animation;
	_anim[BOSS_RIGHT_DASH]->init(IMAGEMANAGER->findImage("boss_dash")->getWidth(), IMAGEMANAGER->findImage("boss_dash")->getHeight()
		, IMAGEMANAGER->findImage("boss_dash")->getFrameWidth(), IMAGEMANAGER->findImage("boss_dash")->getFrameHeight());
	int rightDash[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,4,5,6,7,8,9,10,11,12,13 };
	_anim[BOSS_RIGHT_DASH]->setPlayFrame(rightDash, sizeof(rightDash) / sizeof(rightDash[0]));
	_anim[BOSS_RIGHT_DASH]->setFPS(1);
	// --------------- RIGHT DASH --------------- //

	// --------------- LEFT HIT1 --------------- //
	_anim[BOSS_LEFT_HIT1] = new animation;
	_anim[BOSS_LEFT_HIT1]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_LEFT_HIT1]->setPlayFrame(61, 59, false, false);
	_anim[BOSS_LEFT_HIT1]->setFPS(1);
	// --------------- LEFT HIT1 --------------- //

	// --------------- RIGHT HIT1 --------------- //
	_anim[BOSS_RIGHT_HIT1] = new animation;
	_anim[BOSS_RIGHT_HIT1]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_RIGHT_HIT1]->setPlayFrame(0, 3, false, false);
	_anim[BOSS_RIGHT_HIT1]->setFPS(1);
	// --------------- RIGHT HIT1 --------------- //

	// --------------- LEFT HIT2 --------------- //
	_anim[BOSS_LEFT_HIT2] = new animation;
	_anim[BOSS_LEFT_HIT2]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_LEFT_HIT2]->setPlayFrame(58, 56, false, false);
	_anim[BOSS_LEFT_HIT2]->setFPS(1);
	// --------------- LEFT HIT2 --------------- //

	// --------------- RIGHT HIT2 --------------- //
	_anim[BOSS_RIGHT_HIT2] = new animation;
	_anim[BOSS_RIGHT_HIT2]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_RIGHT_HIT2]->setPlayFrame(4, 6, false, false);
	_anim[BOSS_RIGHT_HIT2]->setFPS(1);
	// --------------- RIGHT HIT2 --------------- //

	// --------------- LEFT HIT3 --------------- //
	_anim[BOSS_LEFT_HIT3] = new animation;
	_anim[BOSS_LEFT_HIT3]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_LEFT_HIT3]->setPlayFrame(56, 31, false, false);
	_anim[BOSS_LEFT_HIT3]->setFPS(1);
	// --------------- LEFT HIT3 --------------- //

	// --------------- RIGHT HIT3 --------------- //
	_anim[BOSS_RIGHT_HIT3] = new animation;
	_anim[BOSS_RIGHT_HIT3]->init(IMAGEMANAGER->findImage("boss_hit")->getWidth(), IMAGEMANAGER->findImage("boss_hit")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit")->getFrameHeight());
	_anim[BOSS_RIGHT_HIT3]->setPlayFrame(7, 30, false, false);
	_anim[BOSS_RIGHT_HIT3]->setFPS(1);
	// --------------- RIGHT HIT3 --------------- //


	// --------------- LEFT HIT GETUP --------------- //
	_anim[BOSS_LEFT_HIT_GETUP] = new animation;
	_anim[BOSS_LEFT_HIT_GETUP]->init(IMAGEMANAGER->findImage("boss_hit_getup")->getWidth(), IMAGEMANAGER->findImage("boss_hit_getup")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit_getup")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit_getup")->getFrameHeight());
	_anim[BOSS_LEFT_HIT_GETUP]->setPlayFrame(29, 15, false, false);
	_anim[BOSS_LEFT_HIT_GETUP]->setFPS(1);
	// --------------- LEFT HIT GETUP --------------- //

	// --------------- RIGHT HIT GETUP --------------- //
	_anim[BOSS_RIGHT_HIT_GETUP] = new animation;
	_anim[BOSS_RIGHT_HIT_GETUP]->init(IMAGEMANAGER->findImage("boss_hit_getup")->getWidth(), IMAGEMANAGER->findImage("boss_hit_getup")->getHeight()
		, IMAGEMANAGER->findImage("boss_hit_getup")->getFrameWidth(), IMAGEMANAGER->findImage("boss_hit_getup")->getFrameHeight());
	_anim[BOSS_RIGHT_HIT_GETUP]->setPlayFrame(0, 14, false, false);
	_anim[BOSS_RIGHT_HIT_GETUP]->setFPS(1);
	// --------------- RIGHT HIT GETUP --------------- //

	// --------------- LEFT DEATH --------------- //
	_anim[BOSS_LEFT_DEATH] = new animation;
	_anim[BOSS_LEFT_DEATH]->init(IMAGEMANAGER->findImage("boss_death")->getWidth(), IMAGEMANAGER->findImage("boss_death")->getHeight()
		, IMAGEMANAGER->findImage("boss_death")->getFrameWidth(), IMAGEMANAGER->findImage("boss_death")->getFrameHeight());
	_anim[BOSS_LEFT_DEATH]->setPlayFrame(25, 13, false, false);
	_anim[BOSS_LEFT_DEATH]->setFPS(1);
	// --------------- LEFT DEATH --------------- //

	// --------------- RIGHT DEATH --------------- //
	_anim[BOSS_RIGHT_DEATH] = new animation;
	_anim[BOSS_RIGHT_DEATH]->init(IMAGEMANAGER->findImage("boss_death")->getWidth(), IMAGEMANAGER->findImage("boss_death")->getHeight()
		, IMAGEMANAGER->findImage("boss_death")->getFrameWidth(), IMAGEMANAGER->findImage("boss_death")->getFrameHeight());
	_anim[BOSS_RIGHT_DEATH]->setPlayFrame(0, 12, false, false);
	_anim[BOSS_RIGHT_DEATH]->setFPS(1);
	// --------------- RIGHT DEATH --------------- //

	// --------------- LEFT DEATH LOOP --------------- //
	_anim[BOSS_LEFT_DEATH_LOOP] = new animation;
	_anim[BOSS_LEFT_DEATH_LOOP]->init(IMAGEMANAGER->findImage("boss_death")->getWidth(), IMAGEMANAGER->findImage("boss_death")->getHeight()
		, IMAGEMANAGER->findImage("boss_death")->getFrameWidth(), IMAGEMANAGER->findImage("boss_death")->getFrameHeight());
	_anim[BOSS_LEFT_DEATH_LOOP]->setPlayFrame(16, 13, false, true);
	_anim[BOSS_LEFT_DEATH_LOOP]->setFPS(1);
	// --------------- LEFT DEATH LOOP --------------- //

	// --------------- RIGHT DEATH LOOP --------------- //
	_anim[BOSS_RIGHT_DEATH_LOOP] = new animation;
	_anim[BOSS_RIGHT_DEATH_LOOP]->init(IMAGEMANAGER->findImage("boss_death")->getWidth(), IMAGEMANAGER->findImage("boss_death")->getHeight()
		, IMAGEMANAGER->findImage("boss_death")->getFrameWidth(), IMAGEMANAGER->findImage("boss_death")->getFrameHeight());
	_anim[BOSS_RIGHT_DEATH_LOOP]->setPlayFrame(9, 12, false, true);
	_anim[BOSS_RIGHT_DEATH_LOOP]->setFPS(1);
	// --------------- RIGHT DEATH LOOP --------------- //

	// --------------- LEFT HEAVY ATTACK --------------- //
	_anim[BOSS_LEFT_HEAVY_ATTACK] = new animation;
	_anim[BOSS_LEFT_HEAVY_ATTACK]->init(IMAGEMANAGER->findImage("boss_heavyAttack")->getWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameHeight());
	_anim[BOSS_LEFT_HEAVY_ATTACK]->setPlayFrame(51, 26, false, false);
	_anim[BOSS_LEFT_HEAVY_ATTACK]->setFPS(1);
	// --------------- LEFT HEAVY ATTACK --------------- //

	// --------------- RIGHT HEAVY ATTACK --------------- //
	_anim[BOSS_RIGHT_HEAVY_ATTACK] = new animation;
	_anim[BOSS_RIGHT_HEAVY_ATTACK]->init(IMAGEMANAGER->findImage("boss_heavyAttack")->getWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getHeight()
		, IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameWidth(), IMAGEMANAGER->findImage("boss_heavyAttack")->getFrameHeight());
	_anim[BOSS_RIGHT_HEAVY_ATTACK]->setPlayFrame(0, 25, false, false);
	_anim[BOSS_RIGHT_HEAVY_ATTACK]->setFPS(1);
	// --------------- RIGHT HEAVY ATTACK --------------- //


	// --------------- LEFT TAUNT --------------- //
	_anim[BOSS_LEFT_TAUNT] = new animation;
	_anim[BOSS_LEFT_TAUNT]->init(IMAGEMANAGER->findImage("boss_taunt")->getWidth(), IMAGEMANAGER->findImage("boss_taunt")->getHeight()
		, IMAGEMANAGER->findImage("boss_taunt")->getFrameWidth(), IMAGEMANAGER->findImage("boss_taunt")->getFrameHeight());
	_anim[BOSS_LEFT_TAUNT]->setPlayFrame(43, 22, false, false);
	_anim[BOSS_LEFT_TAUNT]->setFPS(1);
	// --------------- LEFT TAUNT --------------- //

	// --------------- RIGHT TAUNT --------------- //
	_anim[BOSS_RIGHT_TAUNT] = new animation;
	_anim[BOSS_RIGHT_TAUNT]->init(IMAGEMANAGER->findImage("boss_taunt")->getWidth(), IMAGEMANAGER->findImage("boss_taunt")->getHeight()
		, IMAGEMANAGER->findImage("boss_taunt")->getFrameWidth(), IMAGEMANAGER->findImage("boss_taunt")->getFrameHeight());
	_anim[BOSS_RIGHT_TAUNT]->setPlayFrame(0, 21, false, false);
	_anim[BOSS_RIGHT_TAUNT]->setFPS(1);
	// --------------- RIGHT TAUNT --------------- //

	// --------------- LEFT BLOCK --------------- //
	_anim[BOSS_LEFT_BLOCK] = new animation;
	_anim[BOSS_LEFT_BLOCK]->init(IMAGEMANAGER->findImage("boss_block")->getWidth(), IMAGEMANAGER->findImage("boss_block")->getHeight()
		, IMAGEMANAGER->findImage("boss_block")->getFrameWidth(), IMAGEMANAGER->findImage("boss_block")->getFrameHeight());
	int leftBlock[] = { 7,6,6,6,6,5,4 };
	_anim[BOSS_LEFT_BLOCK]->setPlayFrame(leftBlock, sizeof(leftBlock) / sizeof(int));
	_anim[BOSS_LEFT_BLOCK]->setFPS(1);
	// --------------- LEFT BLOCK --------------- //

	// --------------- RIGHT BLOCK --------------- //
	_anim[BOSS_RIGHT_BLOCK] = new animation;
	_anim[BOSS_RIGHT_BLOCK]->init(IMAGEMANAGER->findImage("boss_block")->getWidth(), IMAGEMANAGER->findImage("boss_block")->getHeight()
		, IMAGEMANAGER->findImage("boss_block")->getFrameWidth(), IMAGEMANAGER->findImage("boss_block")->getFrameHeight());
	int rightBlock[] = { 0,1,1,1,1,2,3 };
	_anim[BOSS_RIGHT_BLOCK]->setPlayFrame(rightBlock, sizeof(rightBlock) / sizeof(int));
	_anim[BOSS_RIGHT_BLOCK]->setFPS(1);
	// --------------- RIGHT BLOCK --------------- //


	// --------------- LEFT ROAR --------------- //
	_anim[BOSS_LEFT_ROAR] = new animation;
	_anim[BOSS_LEFT_ROAR]->init(IMAGEMANAGER->findImage("boss_roar")->getWidth(), IMAGEMANAGER->findImage("boss_roar")->getHeight()
		, IMAGEMANAGER->findImage("boss_roar")->getFrameWidth(), IMAGEMANAGER->findImage("boss_roar")->getFrameHeight());
	_anim[BOSS_LEFT_ROAR]->setPlayFrame(23, 12, false, false);
	_anim[BOSS_LEFT_ROAR]->setFPS(1);
	// --------------- LEFT ROAR --------------- //

	// --------------- RIGHT ROAR --------------- //
	_anim[BOSS_RIGHT_ROAR] = new animation;
	_anim[BOSS_RIGHT_ROAR]->init(IMAGEMANAGER->findImage("boss_roar")->getWidth(), IMAGEMANAGER->findImage("boss_roar")->getHeight()
		, IMAGEMANAGER->findImage("boss_roar")->getFrameWidth(), IMAGEMANAGER->findImage("boss_roar")->getFrameHeight());
	_anim[BOSS_RIGHT_ROAR]->setPlayFrame(0, 11, false, false);
	_anim[BOSS_RIGHT_ROAR]->setFPS(1);
	// --------------- RIGHT ROAR --------------- //

}

void boss::stateUpdate(float playerX, float playerZ)
{
	for (int i = 0; i < BOSS_END; i++)
	{
		_anim[i]->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}

	switch (_state)
	{
	case BOSS_LEFT_BLOCK:
		if (_animPlayer->getNowIndex() > 0 && _animPlayer->getNowIndex() < 5)
		{
			_blockDistance -= _blockFriction;
			_blockFriction += 0.01f;
			_x += cosf(_angle) * _blockDistance;
			_z -= sinf(_angle) * _blockDistance;
		}
		if (!_animPlayer->isPlay())
		{
			int rnd = RND->getInt(10);
			if (rnd < 5) // 막고 바로 대쉬 들어오는 경우
			{
				_state = BOSS_LEFT_DASH;
				_animPlayer = _anim[BOSS_LEFT_DASH];
				_characterImg = IMAGEMANAGER->findImage("boss_dash");
				_angle = getAngle(_x, _z, playerX, playerZ);
				_patternNumber = 99;
			}
			else
			{
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_state = BOSS_LEFT_IDLE;
				_animPlayer = _anim[BOSS_LEFT_IDLE];
				_isDelayTime = true;

			}
			_animPlayer->start();
		}
		break;
	case BOSS_RIGHT_BLOCK:
		if (_animPlayer->getNowIndex() > 0 && _animPlayer->getNowIndex() < 5)
		{
			_blockDistance -= _blockFriction;

			_x += cosf(_angle) * _blockDistance;
			_z -= sinf(_angle) * _blockDistance;
		}
		if (!_animPlayer->isPlay())
		{
			int rnd = RND->getInt(10);
			if (rnd < 5) // 막고 바로 대쉬 들어오는 경우
			{
				_characterImg = IMAGEMANAGER->findImage("boss_dash");
				_state = BOSS_RIGHT_DASH;
				_animPlayer = _anim[BOSS_RIGHT_DASH];
				_angle = getAngle(_x, _z, playerX, playerZ);
				_patternNumber = 99;
			}
			else
			{
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_state = BOSS_RIGHT_IDLE;
				_animPlayer = _anim[BOSS_RIGHT_IDLE];
				_isDelayTime = true;
			}
			_animPlayer->start();
		}
		break;

	case BOSS_LEFT_ROAR:
	case BOSS_RIGHT_ROAR:
	{
		if (!_animPlayer->isPlay())
		{
			if (_state == BOSS_LEFT_ROAR)
			{
				_state = BOSS_LEFT_IDLE;
				_animPlayer = _anim[BOSS_LEFT_IDLE];
			}
			else
			{
				_state = BOSS_RIGHT_IDLE;
				_animPlayer = _anim[BOSS_RIGHT_IDLE];
			}
			_characterImg = IMAGEMANAGER->findImage("boss_idle");

			_animPlayer->start();
			_isDelayTime = true;
			_setActiveAttackRect = false;
		}
		else
		{
			if (_animPlayer->getNowIndex() >= 5)
			{
				_setActiveAttackRect = true;

				_attackPos.x = _x;
				_attackPos.y = _y;
				_attackSize.x = 150;
				_attackSize.y = 150;
			}
			else
			{
				_setActiveAttackRect = false;
			}
		}

	}
	break;
	case BOSS_LEFT_TAUNT:
		if (!_animPlayer->isPlay())
		{
			_characterImg = IMAGEMANAGER->findImage("boss_idle");
			_state = BOSS_LEFT_IDLE;
			_animPlayer = _anim[BOSS_LEFT_IDLE];
			_animPlayer->start();
			_isDelayTime = true;
		}
		break;

	case BOSS_RIGHT_TAUNT:
		if (!_animPlayer->isPlay())
		{
			_characterImg = IMAGEMANAGER->findImage("boss_idle");
			_state = BOSS_RIGHT_IDLE;
			_animPlayer = _anim[BOSS_RIGHT_IDLE];
			_animPlayer->start();
			_isDelayTime = true;
		}
		break;

	case BOSS_LEFT_DASH: // 대쉬는 같은값들어감
	case BOSS_RIGHT_DASH:
		_applySpeed = 6;
		if (_animPlayer->getNowIndex() > 3 && _animPlayer->isPlay())
		{
			_x += cosf(_angle) * _applySpeed;
			_z -= sinf(_angle) * _applySpeed;
			_setActiveAttackRect = true;
			if (_state == BOSS_LEFT_DASH) // 왼쪽으로 대쉬 할 경우 공격 범위.
			{
				_attackPos.x = _x - 100;
				_attackPos.y = _y;
				_attackSize.x = 100;
				_attackSize.y = 80;
			}
			else
			{
				_attackPos.x = _x + 100;
				_attackPos.y = _y;
				_attackSize.x = 100;
				_attackSize.y = 80;
			}
		}
		if (!_animPlayer->isPlay())
		{
			_characterImg = IMAGEMANAGER->findImage("boss_idle");
			if (_state == BOSS_LEFT_DASH)
			{
				_state = BOSS_LEFT_IDLE;
				_animPlayer = _anim[BOSS_LEFT_IDLE];

			}
			else
			{
				_state = BOSS_RIGHT_IDLE;
				_animPlayer = _anim[BOSS_RIGHT_IDLE];
			}
			_animPlayer->start();
			_isDelayTime = true;
			_setActiveAttackRect = false;
		}


		break;

	case BOSS_LEFT_HIT1:
		_hitDelay++;
		if (_hitDelay > 100)
		{
			_hitDelay = 0;
			_hitCount = 0;
			_characterImg = IMAGEMANAGER->findImage("boss_roar");
			_state = BOSS_LEFT_ROAR;
			_animPlayer = _anim[BOSS_LEFT_ROAR];
			_animPlayer->start();
		}
		if (_hitCount > 1) // 두방 째 일 때 
		{
			_hitDelay = 0;
			_state = BOSS_LEFT_HIT2;
			_animPlayer = _anim[BOSS_LEFT_HIT2];
			_animPlayer->start();
		}
		if (_animPlayer->getNowIndex() < 2)
		{
			_x += cosf(_angle) * 0.4f;
			_z -= sinf(_angle) * 0.4f;
		}
		break;
	case BOSS_RIGHT_HIT1:
		_hitDelay++;
		if (_hitDelay > 100)
		{
			_hitDelay = 0;
			_hitCount = 0;
			_characterImg = IMAGEMANAGER->findImage("boss_roar");
			_state = BOSS_RIGHT_ROAR;
			_animPlayer = _anim[BOSS_RIGHT_ROAR];
			_animPlayer->start();
		}
		if (_hitCount > 1) // 두방 째 일 때 
		{
			_hitDelay = 0;
			_state = BOSS_RIGHT_HIT2;
			_animPlayer = _anim[BOSS_RIGHT_HIT2];
			_animPlayer->start();
		}
		if (_animPlayer->getNowIndex() < 2)
		{
			_x += cosf(_angle) * 0.4f;
			_z -= sinf(_angle) * 0.4f;
		}

		break;
	case BOSS_LEFT_HIT2:
		_hitDelay++;
		if (_hitDelay > 100)
		{
			_hitDelay = 0;
			_hitCount = 0;
			_characterImg = IMAGEMANAGER->findImage("boss_roar");
			_state = BOSS_LEFT_ROAR;
			_animPlayer = _anim[BOSS_LEFT_ROAR];
			_animPlayer->start();
		}
		if (_hitCount > 2) // 3방째 일 때 
		{
			_hitDelay = 0;
			_hitCount = 0;
			_state = BOSS_LEFT_HIT3;
			_animPlayer = _anim[BOSS_LEFT_HIT3];
			_animPlayer->start();
		}
		if (_animPlayer->getNowIndex() < 2)
		{
			_x += cosf(_angle) * 0.4f;
			_z -= sinf(_angle) * 0.4f;
		}
		break;
	case BOSS_RIGHT_HIT2:
		_hitDelay++;
		if (_hitDelay > 100)
		{
			_hitDelay = 0;
			_hitCount = 0;
			_characterImg = IMAGEMANAGER->findImage("boss_roar");
			_state = BOSS_RIGHT_ROAR;
			_animPlayer = _anim[BOSS_RIGHT_ROAR];
			_animPlayer->start();
		}
		if (_hitCount > 2) // 3방째 일 때 
		{
			_hitDelay = 0;
			_hitCount = 0;
			_state = BOSS_RIGHT_HIT3;
			_animPlayer = _anim[BOSS_RIGHT_HIT3];
			_animPlayer->start();
		}
		if (_animPlayer->getNowIndex() < 2) // 맞았을때 살짝 밀려남
		{
			_x += cosf(_angle) * 0.4f;
			_z -= sinf(_angle) * 0.4f;
		}
		break;
	case BOSS_LEFT_HIT3:
		if (!_animPlayer->isPlay())
		{
			_hitAndWaitCount++;
			if (_hitAndWaitCount % 100 == 0)
			{
				_gravity = 0.1f;
				_hitAndWaitCount = 0;
				_characterImg = IMAGEMANAGER->findImage("boss_hit_getup");
				_state = BOSS_LEFT_HIT_GETUP;
				_animPlayer = _anim[BOSS_LEFT_HIT_GETUP];
				_animPlayer->start();
			}
		}
		else
		{
			// 날아가는 동안 
			if (_y >= _z - 137)
			{
				_x += cosf(_angle) * 0.6f;
				_y -= 1 - _gravity;
				_gravity = 1;
			}
			else
			{
				_x += cosf(_angle) * 2;
				_y -= 5 - _gravity;
			}
			_gravity += 0.1f;
		}
		break;
	case BOSS_RIGHT_HIT3:
		if (!_animPlayer->isPlay())
		{
			_hitAndWaitCount++;
			if (_hitAndWaitCount % 100 == 0)
			{
				_gravity = 0.1f;
				_hitAndWaitCount = 0;
				_characterImg = IMAGEMANAGER->findImage("boss_hit_getup");
				_state = BOSS_RIGHT_HIT_GETUP;
				_animPlayer = _anim[BOSS_RIGHT_HIT_GETUP];
				_animPlayer->start();
			}
		}
		else
		{
			// 날아가는 동안 

			if (_y >= _z - 137)
			{
				_x += cosf(_angle) * 0.6f;
				_y -= 1 - _gravity;
				_gravity = 1;
			}
			else
			{
				_x += cosf(_angle) * 2;
				_y -= 5 - _gravity;
			}
			_gravity += 0.1f;
		}
		break;
	case BOSS_LEFT_HIT_GETUP:
	case BOSS_RIGHT_HIT_GETUP:
		if (!_animPlayer->isPlay())
		{
			if (_state == BOSS_LEFT_HIT_GETUP)
			{
				_state = BOSS_LEFT_IDLE;
				_animPlayer = _anim[BOSS_LEFT_IDLE];
			}
			else
			{
				_state = BOSS_RIGHT_IDLE;
				_animPlayer = _anim[BOSS_RIGHT_IDLE];
			}
			_characterImg = IMAGEMANAGER->findImage("boss_idle");
			_animPlayer->start();
			_isDelayTime = true;
			_setActiveAttackRect = false;
		}
		else
		{
			if (_animPlayer->getNowIndex() == 5 || _animPlayer->getNowIndex() == 6)
			{
				_setActiveAttackRect = true;
				if (_state == BOSS_LEFT_HIT_GETUP)
					_attackPos.x = _x - 50;
				else
					_attackPos.x = _x + 50;

				_attackPos.y = _y + 100;
				_attackSize.x = 80;
				_attackSize.y = 80;
			}
			else
			{
				_setActiveAttackRect = false;
			}
		}
		break;

	case BOSS_LEFT_JUMP:
	case BOSS_RIGHT_JUMP:
		_applySpeed = 4;
		if (_animPlayer->getNowIndex() > 5)
		{
			_x += cosf(_angle) * _applySpeed;
			_y -= sinf(_angle) * _applySpeed + _jumpPower;
			_z -= sinf(_angle) * _applySpeed;

			_jumpAlpha -= 2;
			if (_jumpAlpha <= _jumpAlphaMin)
			{
				_jumpAlpha = _jumpAlphaMin;
			}

			if (_y < -200)
			{
				_y = -200;
				_jumpAndDownAttackCount++; // 플레이어 값을 알수 없기 때문에 jumpAttack쪽에서 확인
			}
			_gravity = 0.1f;
		}
		break;

	case BOSS_LEFT_JUMP_ATTACK:
	case BOSS_RIGHT_JUMP_ATTACK:
		_y += _jumpPower + _gravity;
		_gravity += 0.8f;

		_jumpAlpha += 2;

		if (_jumpAlpha >= _jumpAlphaMax)
		{
			_jumpAlpha = _jumpAlphaMax;
		}

		if (_y >= _z - 137)
		{
			_y = _z - 137;
		}
		break;
	case BOSS_LEFT_HEAVY_ATTACK:
	case BOSS_RIGHT_HEAVY_ATTACK:
		_applySpeed = 10;
		if (_animPlayer->getNowIndex() > 11 && _animPlayer->getNowIndex() < 17 && _animPlayer->isPlay())
		{
			_x += cosf(_angle) * _applySpeed;
			_z -= sinf(_angle) * _applySpeed;
		}
		break;
	case BOSS_LEFT_DEATH:

		if (!_animPlayer->isPlay())
		{
			_state = BOSS_LEFT_DEATH_LOOP;
			_animPlayer = _anim[BOSS_LEFT_DEATH_LOOP];
			_animPlayer->start();

		}
		break;
	case BOSS_RIGHT_DEATH:
		if (!_animPlayer->isPlay())
		{
			_state = BOSS_RIGHT_DEATH_LOOP;
			_animPlayer = _anim[BOSS_RIGHT_DEATH_LOOP];
			_animPlayer->start();
		}
		break;
	}

}

void boss::attack(float playerX, float playerZ)
{
	// ------ 임시 --------
	float tempZ = playerZ + 100;

	if (getDistance(_x, _z, playerX, tempZ) < 3000 && getDistance(_x, _z, playerX, tempZ) > 150) // 플레이어를 찾아다님
	{
		if ((_state == BOSS_LEFT_ATTACK || _state == BOSS_RIGHT_ATTACK))
		{
			if (!_animPlayer->isPlay())
			{
				_isDelayTime = true;
				if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
				{
					_state = BOSS_LEFT_IDLE;
					_characterImg = IMAGEMANAGER->findImage("boss_idle");
					_animPlayer = _anim[BOSS_LEFT_IDLE];
					_animPlayer->start();
				}
				else
				{
					_state = BOSS_RIGHT_IDLE;
					_characterImg = IMAGEMANAGER->findImage("boss_idle");
					_animPlayer = _anim[BOSS_RIGHT_IDLE];
					_animPlayer->start();
				}

			}
		}
		else
		{
			_angle = getAngle(_x, _z, playerX, tempZ);
			if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
			{
				if (_state != BOSS_LEFT_WALK)
				{
					_state = BOSS_LEFT_WALK;
					_characterImg = IMAGEMANAGER->findImage("boss_walk");
					_animPlayer = _anim[BOSS_LEFT_WALK];
					_animPlayer->start();
				}
			}
			else               // 보스가 플레이어 왼쪽에 있는 경우
			{
				if (_state != BOSS_RIGHT_WALK)
				{
					_state = BOSS_RIGHT_WALK;
					_characterImg = IMAGEMANAGER->findImage("boss_walk");
					_animPlayer = _anim[BOSS_RIGHT_WALK];
					_animPlayer->start();
				}
			}

			_x += cosf(_angle) * 2;
			_z -= sinf(_angle) * 2;
		}

	}
	else if (getDistance(_x, _z, playerX, tempZ) <= 150) // 사정거리에 들어왔을 경우
	{
		if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
		{
			if (_state != BOSS_LEFT_ATTACK && _state != BOSS_RIGHT_ATTACK)
			{
				_state = BOSS_LEFT_ATTACK;
				_characterImg = IMAGEMANAGER->findImage("boss_attack");
				_animPlayer = _anim[BOSS_LEFT_ATTACK];
				_animPlayer->start();
			}
		}
		else               // 보스가 플레이어 왼쪽에 있는 경우
		{
			if (_state != BOSS_RIGHT_ATTACK && _state != BOSS_LEFT_ATTACK)
			{
				_state = BOSS_RIGHT_ATTACK;
				_characterImg = IMAGEMANAGER->findImage("boss_attack");
				_animPlayer = _anim[BOSS_RIGHT_ATTACK];
				_animPlayer->start();
			}
		}

		if (!_animPlayer->isPlay())
		{
			_isDelayTime = true;
			if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
			{
				_state = BOSS_LEFT_IDLE;
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_animPlayer = _anim[BOSS_LEFT_IDLE];
				_animPlayer->start();
			}
			else
			{
				_state = BOSS_RIGHT_IDLE;
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_animPlayer = _anim[BOSS_RIGHT_IDLE];
				_animPlayer->start();
			}

		}
	}
}

void boss::heavyAttack(float playerX, float playerZ)
{
	// ------ 임시 --------
	float tempZ = playerZ + 100;

	if (getDistance(_x, _z, playerX, tempZ) < 3000 && getDistance(_x, _z, playerX, tempZ) > 500) // 플레이어를 찾아다님
	{
		if ((_state == BOSS_LEFT_HEAVY_ATTACK || _state == BOSS_RIGHT_HEAVY_ATTACK))
		{
			if (!_animPlayer->isPlay())  // 어택 애니메이션이 
			{
				_isDelayTime = true;
				if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
				{
					_state = BOSS_LEFT_IDLE;
					_characterImg = IMAGEMANAGER->findImage("boss_idle");
					_animPlayer = _anim[BOSS_LEFT_IDLE];
					_animPlayer->start();
				}
				else
				{
					_state = BOSS_RIGHT_IDLE;
					_characterImg = IMAGEMANAGER->findImage("boss_idle");
					_animPlayer = _anim[BOSS_RIGHT_IDLE];
					_animPlayer->start();
				}

			}
		}
		else
		{

			if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
			{
				if (_state != BOSS_LEFT_WALK)
				{
					_state = BOSS_LEFT_WALK;
					_characterImg = IMAGEMANAGER->findImage("boss_walk");
					_animPlayer = _anim[BOSS_LEFT_WALK];
					_animPlayer->start();
				}
			}
			else               // 보스가 플레이어 왼쪽에 있는 경우
			{
				if (_state != BOSS_RIGHT_WALK)
				{
					_state = BOSS_RIGHT_WALK;
					_characterImg = IMAGEMANAGER->findImage("boss_walk");
					_animPlayer = _anim[BOSS_RIGHT_WALK];
					_animPlayer->start();
				}
			}
			_angle = getAngle(_x, _z, playerX, tempZ);
			_x += cosf(_angle) * 2;	// 따로 빼도 되는건가 
			_z -= sinf(_angle) * 2; // 따로 빼도 되는건가 
		}

	}
	else if (getDistance(_x, _z, playerX, tempZ) <= 500) // 사정거리에 들어왔을 경우
	{
		if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
		{
			if (_state != BOSS_LEFT_HEAVY_ATTACK && _state != BOSS_RIGHT_HEAVY_ATTACK)
			{
				_state = BOSS_LEFT_HEAVY_ATTACK;
				_characterImg = IMAGEMANAGER->findImage("boss_heavyAttack");
				_animPlayer = _anim[BOSS_LEFT_HEAVY_ATTACK];
				_animPlayer->start();

				_angle = getAngle(_x, _z, playerX, tempZ);
			}

		}
		else               // 보스가 플레이어 왼쪽에 있는 경우
		{
			if (_state != BOSS_RIGHT_HEAVY_ATTACK && _state != BOSS_LEFT_HEAVY_ATTACK)
			{
				_state = BOSS_RIGHT_HEAVY_ATTACK;
				_characterImg = IMAGEMANAGER->findImage("boss_heavyAttack");
				_animPlayer = _anim[BOSS_RIGHT_HEAVY_ATTACK];
				_animPlayer->start();

				_angle = getAngle(_x, _z, playerX, tempZ);
			}
		}

		if (!_animPlayer->isPlay()) // 애니메이션이 끝난 경우
		{
			_isDelayTime = true;
			if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
			{
				_state = BOSS_LEFT_IDLE;
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_animPlayer = _anim[BOSS_LEFT_IDLE];
				_animPlayer->start();
			}
			else
			{
				_state = BOSS_RIGHT_IDLE;
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_animPlayer = _anim[BOSS_RIGHT_IDLE];
				_animPlayer->start();
			}

		}

	}

} // 강 공격시에는 좋아하는것도 넣기

void boss::dashAttack(float playerX, float playerZ)
{
	// ------ 임시 --------
	float tempZ = playerZ + 100;

	if (getDistance(_x, _z, playerX, tempZ) <= 3000) // 사정거리에 들어왔을 경우
	{
		if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
		{
			if (_state != BOSS_LEFT_DASH && _state != BOSS_RIGHT_DASH)
			{
				_state = BOSS_LEFT_DASH;
				_characterImg = IMAGEMANAGER->findImage("boss_dash");
				_animPlayer = _anim[BOSS_LEFT_DASH];
				_animPlayer->start();
				_angle = getAngle(_x, _z, playerX, tempZ);
			}
		}
		else               // 보스가 플레이어 왼쪽에 있는 경우
		{
			if (_state != BOSS_RIGHT_DASH && _state != BOSS_LEFT_DASH)
			{
				_state = BOSS_RIGHT_DASH;
				_characterImg = IMAGEMANAGER->findImage("boss_dash");
				_animPlayer = _anim[BOSS_RIGHT_DASH];
				_animPlayer->start();
				_angle = getAngle(_x, _z, playerX, tempZ);
			}
		}
	}

}

void boss::jumpAttack(float playerX, float playerZ)
{
	// ------ 임시 --------
	float tempZ = playerZ + 100;

	if (_state != BOSS_LEFT_JUMP && _state != BOSS_RIGHT_JUMP && _state != BOSS_LEFT_JUMP_ATTACK && _state != BOSS_RIGHT_JUMP_ATTACK)
	{
		if (_x >= playerX) // 보스가 오른쪽에있는경우 --> 왼쪽 봐야함
		{
			_state = BOSS_LEFT_JUMP;
			_characterImg = IMAGEMANAGER->findImage("boss_jumpAttack");
			_animPlayer = _anim[BOSS_LEFT_JUMP];
			_animPlayer->start();
		}
		else
		{
			_state = BOSS_RIGHT_JUMP;
			_characterImg = IMAGEMANAGER->findImage("boss_jumpAttack");
			_animPlayer = _anim[BOSS_RIGHT_JUMP];
			_animPlayer->start();
		}

	}
	if (_state == BOSS_LEFT_JUMP || _state == BOSS_RIGHT_JUMP) //점프 상태일 때 각도 구해오기 3초간 유지후 떨어짐
	{
		_angle = getAngle(_x, _z, playerX, tempZ);
	}



	if (_jumpAndDownAttackCount > 300) // changePattern쪽에서 받아옴 
	{
		_jumpAndDownAttackCount = 0;
		if (_x >= playerX) // 보스가 오른쪽에있는경우 --> 왼쪽 봐야함
		{
			_state = BOSS_LEFT_JUMP_ATTACK;
			_characterImg = IMAGEMANAGER->findImage("boss_jumpAttack");
			_animPlayer = _anim[BOSS_LEFT_JUMP_ATTACK];
			_animPlayer->start();
		}
		else
		{
			_state = BOSS_RIGHT_JUMP_ATTACK;
			_characterImg = IMAGEMANAGER->findImage("boss_jumpAttack");
			_animPlayer = _anim[BOSS_RIGHT_JUMP_ATTACK];
			_animPlayer->start();
		}
	}

	if ((_state == BOSS_LEFT_JUMP_ATTACK || _state == BOSS_RIGHT_JUMP_ATTACK) && !_animPlayer->isPlay()) // 다 내려온후
	{
		_isDelayTime = true;
		if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
		{
			_state = BOSS_LEFT_IDLE;
			_characterImg = IMAGEMANAGER->findImage("boss_idle");
			_animPlayer = _anim[BOSS_LEFT_IDLE];
			_animPlayer->start();
		}
		else
		{
			_state = BOSS_RIGHT_IDLE;
			_characterImg = IMAGEMANAGER->findImage("boss_idle");
			_animPlayer = _anim[BOSS_RIGHT_IDLE];
			_animPlayer->start();
		}

	}

}

void boss::elbowAttack(float playerX, float playerZ)
{// ------ 임시 --------
	float tempZ = playerZ + 100;

	if (getDistance(_x, _z, playerX, tempZ) < 3000 && getDistance(_x, _z, playerX, tempZ) > 150) // 플레이어를 찾아다님
	{
		if ((_state == BOSS_LEFT_ATTACK_ELBOW || _state == BOSS_RIGHT_ATTACK_ELBOW)) // 적한테 가까이갔다가 멀리 도망친 경우
		{
			if (!_animPlayer->isPlay())
			{
				_isDelayTime = true;
				if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
				{
					_state = BOSS_LEFT_IDLE;
					_characterImg = IMAGEMANAGER->findImage("boss_idle");
					_animPlayer = _anim[BOSS_LEFT_IDLE];
					_animPlayer->start();
				}
				else
				{
					_state = BOSS_RIGHT_IDLE;
					_characterImg = IMAGEMANAGER->findImage("boss_idle");
					_animPlayer = _anim[BOSS_RIGHT_IDLE];
					_animPlayer->start();
				}

			}
		}
		else // 보스한테 멀리서부터 다가온 경우
		{
			_angle = getAngle(_x, _z, playerX, tempZ);
			if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
			{
				if (_state != BOSS_LEFT_WALK)
				{
					_state = BOSS_LEFT_WALK;
					_characterImg = IMAGEMANAGER->findImage("boss_walk");
					_animPlayer = _anim[BOSS_LEFT_WALK];
					_animPlayer->start();
				}
			}
			else               // 보스가 플레이어 왼쪽에 있는 경우
			{
				if (_state != BOSS_RIGHT_WALK)
				{
					_state = BOSS_RIGHT_WALK;
					_characterImg = IMAGEMANAGER->findImage("boss_walk");
					_animPlayer = _anim[BOSS_RIGHT_WALK];
					_animPlayer->start();
				}
			}

			_x += cosf(_angle) * 2;
			_z -= sinf(_angle) * 2;
		}

	}
	else if (getDistance(_x, _z, playerX, tempZ) <= 150) // 사정거리에 들어왔을 경우
	{
		if (_state != BOSS_LEFT_ATTACK_ELBOW && _state != BOSS_RIGHT_ATTACK_ELBOW)
		{
			if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
			{
				_state = BOSS_LEFT_ATTACK_ELBOW;
				_characterImg = IMAGEMANAGER->findImage("boss_attack_elbow");
				_animPlayer = _anim[BOSS_LEFT_ATTACK_ELBOW];
				_animPlayer->start();
			}
			else               // 보스가 플레이어 왼쪽에 있는 경우
			{
				_state = BOSS_RIGHT_ATTACK_ELBOW;
				_characterImg = IMAGEMANAGER->findImage("boss_attack_elbow");
				_animPlayer = _anim[BOSS_RIGHT_ATTACK_ELBOW];
				_animPlayer->start();
			}
		}

		if (!_animPlayer->isPlay())
		{
			_isDelayTime = true;
			if (_x >= playerX) // 보스가 플레이어 오른쪽에 있는 경우
			{
				_state = BOSS_LEFT_IDLE;
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_animPlayer = _anim[BOSS_LEFT_IDLE];
				_animPlayer->start();
			}
			else
			{
				_state = BOSS_RIGHT_IDLE;
				_characterImg = IMAGEMANAGER->findImage("boss_idle");
				_animPlayer = _anim[BOSS_RIGHT_IDLE];
				_animPlayer->start();
			}

		}
	}
}

void boss::changePattern(float playerX, float playerZ)
{

	// 자동으로 다른 스테이트로 실행되는것들 리턴 시키기
	if (_state == BOSS_LEFT_BLOCK || _state == BOSS_RIGHT_BLOCK) return;
	if (_state == BOSS_LEFT_TAUNT || _state == BOSS_RIGHT_TAUNT || _state == BOSS_LEFT_ROAR || _state == BOSS_RIGHT_ROAR) return;
	if (_state == BOSS_LEFT_DEATH || _state == BOSS_RIGHT_DEATH || _state == BOSS_LEFT_DEATH_LOOP || _state == BOSS_RIGHT_DEATH_LOOP) return;
	if (_state == BOSS_LEFT_HIT1 || _state == BOSS_LEFT_HIT2 || _state == BOSS_LEFT_HIT3 || _state == BOSS_LEFT_HIT_GETUP ||
		_state == BOSS_RIGHT_HIT1 || _state == BOSS_RIGHT_HIT2 || _state == BOSS_RIGHT_HIT3 || _state == BOSS_RIGHT_HIT_GETUP) return;

	if (_isDelayTime) // 딜레이 타임 인 경우.
	{
		_delayTime++;
		if (_delayTime % 100 == 0)
		{
			_delayTime = 0;
			_patternNumber = RND->getInt(5);
			_isDelayTime = false;
		}
	}
	else
	{
		if (_patternNumber == 0)
		{
			attack(playerX, playerZ);
		}
		else if (_patternNumber == 1)
		{
			heavyAttack(playerX, playerZ);
		}
		else if (_patternNumber == 2)
		{
			dashAttack(playerX, playerZ);
		}
		else if (_patternNumber == 3)
		{
			elbowAttack(playerX, playerZ);
		}
		else if (_patternNumber == 4)
		{
			jumpAttack(playerX, playerZ);
		}
	}
}

void boss::death(float playerX, float playerZ)
{
	if (_hp <= 0 && _state != BOSS_LEFT_DEATH && _state != BOSS_RIGHT_DEATH && _state != BOSS_LEFT_DEATH_LOOP && _state != BOSS_RIGHT_DEATH_LOOP)
	{
		if (_x >= playerX)
		{
			_state = BOSS_LEFT_DEATH;
			_characterImg = IMAGEMANAGER->findImage("boss_death");
			_animPlayer = _anim[BOSS_LEFT_DEATH];
			_animPlayer->start();
		}
		else
		{
			_state = BOSS_RIGHT_DEATH;
			_characterImg = IMAGEMANAGER->findImage("boss_death");
			_animPlayer = _anim[BOSS_RIGHT_DEATH];
			_animPlayer->start();
		}

	}
}

void boss::hit(float playerX, float playerZ, int damege)
{
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		if (_state == BOSS_LEFT_HIT3 || _state == BOSS_RIGHT_HIT3 || _state == BOSS_LEFT_HIT_GETUP || _state == BOSS_RIGHT_HIT_GETUP ||
			_state == BOSS_LEFT_BLOCK || _state == BOSS_RIGHT_BLOCK || _state == BOSS_LEFT_ROAR || _state == BOSS_RIGHT_ROAR || _state == BOSS_LEFT_JUMP ||
			_state == BOSS_RIGHT_JUMP || _state == BOSS_LEFT_JUMP_ATTACK || _state == BOSS_RIGHT_JUMP_ATTACK ||
			_state == BOSS_LEFT_DASH || _state == BOSS_RIGHT_DASH) return; // 3타중이면 못들어오게 // 공격 안받는 상황

		_characterImg = IMAGEMANAGER->findImage("boss_hit");
		if (playerX <= _x) //플레이어가 왼쪽에 있는경우 --> 왼쪽을 봐야함 보스가
		{
			// 30퍼 확률로 막기
			if (_hitCount == 0)
			{
				int rndBlock = RND->getInt(10);
				if (rndBlock < 5)
				{
					_characterImg = IMAGEMANAGER->findImage("boss_block");
					_state = BOSS_LEFT_BLOCK;
					_animPlayer = _anim[BOSS_LEFT_BLOCK];
					_animPlayer->start();
					_hitCount = 0;
					_blockDistance = 5;
					_blockFriction = 0.01f;
				}
				else
				{
					_state = BOSS_LEFT_HIT1;
					_animPlayer = _anim[BOSS_LEFT_HIT1];
					_animPlayer->start();
					_hitCount++;
				}

			}
			else if (_hitCount == 1)
			{
				_state = BOSS_LEFT_HIT1;
				_animPlayer = _anim[BOSS_LEFT_HIT1];
				_hitCount++;
			}
			else if (_hitCount == 2)
			{
				_state = BOSS_LEFT_HIT2;
				_animPlayer = _anim[BOSS_LEFT_HIT2];
				_hitCount++;
			}

		}
		else
		{
			if (_hitCount == 0)
			{
				int rndBlock = RND->getInt(10);
				if (rndBlock < 5)
				{
					_characterImg = IMAGEMANAGER->findImage("boss_block");
					_blockDistance = 5;
					_blockFriction = 0.01f;
					_state = BOSS_RIGHT_BLOCK;
					_animPlayer = _anim[BOSS_RIGHT_BLOCK];
					_animPlayer->start();
					_hitCount = 0;
				}
				else
				{
					_state = BOSS_RIGHT_HIT1;
					_animPlayer = _anim[BOSS_RIGHT_HIT1];
					_animPlayer->start();
					_hitCount++;
				}
			}
			else if (_hitCount == 1)
			{
				_state = BOSS_RIGHT_HIT1;
				_animPlayer = _anim[BOSS_RIGHT_HIT1];
				_hitCount++;
			}
			else if (_hitCount == 2)
			{
				_state = BOSS_RIGHT_HIT2;
				_animPlayer = _anim[BOSS_RIGHT_HIT2];
				_hitCount++;

			}
		}
		_angle = getAngle(playerX, playerZ, _x, _z);
	}


}





