#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class playerState;
class idleState;
class walkState;
class runState;
class jumpState;
class attackState;
class hitState;
class invinState;


class player : public gameNode
{
private:
	playerState* _state;
	image* _img;					//플레이어 이미지
	RECT _shadow;					//플레이어 그림자 이미지 
	RECT _player;					//플레이어
	RECT _attackRc;					//공격렉트

	int _probeV;					//픽셀충돌 수직
	int _probeH;					//픽셀충돌 수평
	bool _isBottom;					//아래
	bool _isTop;					//위
	bool _isLeft;					//왼쪽
	bool _isRight;					//오른쪽
	bool _isJumping;				//점프하는지
	bool _isRun;					//뛰는지
	bool _isAttack;					//공격할거?
	bool _attacked;					//공격 3번 이어주기


	float _shadowX, _shadowY;		//그림자 중점
	float _playerX, _playerY;		//플레이어 중점
	float _attackX, _attackY;		//어택의 중점
	float _attackSizeX, _attackSizeY;//어택렉트의 사이즈

	bool _directionX;				//left = 0, right = 1
	bool _directionY;				//top = 0, bottom = 1

	float _jumpPower, _gravity;		//플레이어 점프파워, 중력

	int _runCount;					//빠르게 달리기


	animation* _playerMotion;


	playerState* _idle;
	playerState* _walk;
	playerState* _run;
	playerState* _jump;
	playerState* _attack;
	playerState* _hit;
	playerState* _invin;


public:
	player() {}
	~player() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

	void setState(playerState* state)
	{
		this->_state = state;
	}

	void keyAnimation();

public:
	//=====================GET================================
	float getShadowX() { return _shadowX; }
	float getShadowY() { return _shadowY; }
	float getPlayerX() { return _playerX; }
	float getPlayerY() { return _playerY; }
	float getJumpPower() { return _jumpPower; }
	float getGravity() { return _gravity; }
	int getRunCount() { return _runCount; }
	bool getDirectionX() { return _directionX; }
	bool getDirectionY() { return _directionY; }
	bool getIsBottom() { return _isBottom; }
	bool getIsTop() { return _isTop; }
	bool getIsRight() { return _isRight; }
	bool getIsLeft() { return _isLeft; }
	bool getIsJumping() { return _isJumping; }
	bool getIsRun() { return _isRun; }
	bool getAttacked() { return _attacked; }
	bool getIsAttack() { return _isAttack; }
	RECT getAttackRect() { return _attackRc; }
	image* getImgge() { return _img; }
	animation* getAni() { return _playerMotion; }



	playerState* getIdleState() { return _idle; }
	playerState* getWalkState() { return _walk; }
	playerState* getRunState() { return _run; }
	playerState* getJumpState() { return _jump; }
	playerState* getAttackState() { return _attack; }
	playerState* getHitState() { return _hit; }
	playerState* getInvinState() { return _invin; }

	//=====================SET================================
	void setShadowX(float x) { _shadowX = x; }
	void setShadowY(float y) { _shadowY = y; }
	void setPlayerX(float playerX) { _playerX = playerX; }
	void setPlayerY(float playerY) { _playerY = playerY; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setAttack(float attackX, float attackY, float attackSizeX, float attackSizeY)
	{
		_attackX = attackX; _attackY = attackY; _attackSizeX = attackSizeX; _attackSizeY = attackSizeY;
	}
	void setRunCount(int runCount) { _runCount = runCount; }
	void setDirectionX(bool direction) { _directionX = direction; }
	void setDirectionY(bool direction) { _directionY = direction; }
	void setIsJumping(bool jumping) { _isJumping = jumping; }
	void setIsBottom(bool isMove) { _isBottom = isMove; }
	void setIsTop(bool isMove) { _isTop = isMove; }
	void setIsRight(bool isMove) { _isRight = isMove; }
	void setIsLeft(bool isMove) { _isLeft = isMove; }
	void setIsRun(bool isRun) { _isRun = isRun; }
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }
	void setAttacked(bool attacked) { _attacked = attacked; }
	void setAttackRect(RECT attackRc) { _attackRc = attackRc; }
	void setAni(animation* ani, image* img) { _img = img;  _playerMotion = ani; _playerMotion->start(); }
};


class playerState
{
public:
	virtual ~playerState() {}
	virtual void update(player& player) {}
public:
	static idleState* idle;
	static walkState* walk;
	static runState* run;
	static jumpState* jump;
	static attackState* attack;
	static hitState* hit;
	static invinState* invin;
};

class idleState : public playerState
{
public:
	virtual void update(player& player) override;
};

class walkState : public playerState
{
public:
	virtual void update(player& player) override;
};

class runState : public playerState
{
public:
	virtual void update(player& player) override;
};

class jumpState : public playerState
{
private:
	int _jumpCount;
	bool _isJump;
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class attackState : public playerState
{
public:
	virtual void update(player& player) override;
};

class hitState : public playerState
{
public:
	virtual void update(player& player) override;
};

class invinState : public playerState
{
public:
	virtual void update(player& player) override;
};