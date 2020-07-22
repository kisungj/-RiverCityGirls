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
class downState;		//힝
class startState;
class guardState;
class overState;
class stunState;


class player : public gameNode
{
private:
	playerState* _state;
	image* _img;					//플레이어 이미지
	image* _shadowImg;				//쉐도우 이미지
	RECT _shadow;					//플레이어 그림자 이미지 
	RECT _player;					//플레이어
	RECT _attackRc;					//공격렉트

	string _mapStr;					//픽셀충돌 맵 바꾸는용

	int _probeV;					//픽셀충돌 수직
	int _probeH;					//픽셀충돌 수평
	int _playerProbe;				//책상 올라가는용
	int _runCount;					//빠르게 달리기
	int _shadowAlpha;				//그림자 알파

	float _shadowX, _shadowY;		//그림자 중점
	float _playerX, _playerY;		//플레이어 중점
	float _attackX, _attackY;		//어택의 중점
	float _attackSizeX, _attackSizeY;//어택렉트의 사이즈
	float _currentHP, _maxHP;		//체력
	float _jumpPower, _gravity;		//플레이어 점프파워, 중력
	float _deskTimer;

	bool _isBottom;					//아래
	bool _isTop;					//위
	bool _isLeft;					//왼쪽
	bool _isRight;					//오른쪽
	bool _isDesk;					//책상위에 올라갔는지
	bool _isJumping;				//점프하는지
	bool _isDeskFall;				//데스크 충돌 테스트
	bool _isRun;					//뛰는지
	bool _isAttack;					//공격할거?
	bool _attacked;					//공격 3번 이어주기
	bool _directionX;				//left = 0, right = 1
	bool _directionY;				//top = 0, bottom = 1




	animation* _playerMotion;


	playerState* _idle;
	playerState* _walk;
	playerState* _run;
	playerState* _jump;
	playerState* _attack;
	playerState* _hit;
	playerState* _down;
	playerState* _start;
	playerState* _guard;
	playerState* _over;
	playerState* _stun;


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

	void playerDamage(float damage);

	void mouseCol();
	void pixelCol();
	void boolCheck();

public:
	//=====================GET================================
	float getShadowX() { return _shadowX; }
	float getShadowY() { return _shadowY; }
	float getPlayerX() { return _playerX; }
	float getPlayerY() { return _playerY; }
	float getJumpPower() { return _jumpPower; }
	float getGravity() { return _gravity; }
	float getPlayerHp() { return _currentHP; }
	float getPlayerMaxHP() { return _maxHP; }
	int getRunCount() { return _runCount; }
	int getShadow() { return _shadowAlpha; }
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
	bool getIsDeskFall() { return _isDeskFall; }
	RECT getAttackRect() { return _attackRc; }
	RECT getPlayerRect() { return _player; }
	image* getImgge() { return _img; }
	animation* getAni() { return _playerMotion; }



	playerState* getIdleState() { return _idle; }
	playerState* getWalkState() { return _walk; }
	playerState* getRunState() { return _run; }
	playerState* getJumpState() { return _jump; }
	playerState* getAttackState() { return _attack; }
	playerState* getHitState() { return _hit; }
	playerState* getDownState() { return _down; }
	playerState* getStartState() { return _start; }
	playerState* getGuardState() { return _guard; }
	playerState* getOverState() { return _over; }
	playerState* getStunState() { return _stun; }

	//=====================SET================================
	void setShadowX(float x) { _shadowX = x; }
	void setShadowY(float y) { _shadowY = y; }
	void setPlayerX(float playerX) { _playerX = playerX; }
	void setPlayerY(float playerY) { _playerY = playerY; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setPlayerHP(float hp) { _currentHP = hp; }
	void setAttack(float attackX, float attackY, float attackSizeX, float attackSizeY)
	{
		_attackX = attackX; _attackY = attackY; _attackSizeX = attackSizeX; _attackSizeY = attackSizeY;
	}
	void setRunCount(int runCount) { _runCount = runCount; }
	void setShadow(int shadow) { _shadowAlpha = shadow; }
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
	void setIsDeskFall(bool fall) { _isDeskFall = fall; }
	void setAttackRect(RECT attackRc) { _attackRc = attackRc; }
	void setMapStr(string str) { _mapStr = str; }
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
	static downState* down;
	static startState* gameStart;
	static guardState* guard;
	static overState* over;
	static stunState* stun;
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
	int _jumpCount;		//stay키 막아서 점프 그만 올라가게
	bool _isJump;		//이거 또한,. 무스비..
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class attackState : public playerState
{
private:
	int _diveCount;		//다이브 속도 주려구
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class hitState : public playerState
{
private:
	int _hitCount;
	int _stunCount;
	int _hitNum;
	bool _isHit;
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class downState : public playerState
{
private:
	int _downCount;
public:
	HRESULT init();
	virtual void update(player& player) override;
};

class startState : public playerState
{
public:
	virtual void update(player& player) override;
};

class guardState : public playerState
{
public:
	virtual void update(player& player) override;
};

class overState : public playerState
{
public: 
	virtual void update(player& player) override;
};

class stunState : public playerState
{
public:
	virtual void update(player& player) override;
};