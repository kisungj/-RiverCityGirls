#pragma once

#define DELAYMAX 200	//´Ù¿îµÆÀ» ¶§ µô·¹ÀÌ½Ã°£

class enemy;

class enemyIdleState;
class enemyMoveState;
class enemyRunState;
class enemyJumpState;
class enemyAttackState;
class enemyHitState;
class enemyDownState;
class enemyDizzyState;
class enemyDeadState;

enum class ENEMYTYPE
{
	BOY, GIRL, CHEER
};

class enemyState
{
public:
	virtual ~enemyState() {}

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) = 0;

public:
	static enemyIdleState* enemyIdle;
	static enemyMoveState* enemyMove;
	static enemyRunState* enemyRun;
	static enemyJumpState* enemyJump;
	static enemyAttackState* enemyAttack;
	static enemyHitState* enemyHit;
	static enemyDownState* enemyDown;
	static enemyDizzyState* enemyDizzy;
	static enemyDeadState* enemyDead;
};

class enemyIdleState : public enemyState
{
private:
	int _searchCount;
	int _delayCount;
	bool _isDiscover;
public:
	enemyIdleState() { _searchCount = 0; _isDiscover = false; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyMoveState : public enemyState
{
private:
	int _randomCount;
	int _rnd;
	int _waitCount;
	int _delayCount;
public:
	enemyMoveState() { _waitCount = 0; _delayCount = 0; }
	~enemyMoveState() {}

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyRunState : public enemyState
{
private:
	RECT _attack;
	int _kickCount;
	int _limitCount;
	int _collisionCount;
	bool _isKick;
public:
	enemyRunState() { _kickCount = 0; _limitCount = 0; _collisionCount = 0; _isKick = false; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyJumpState : public enemyState
{
private:
	int _delayCount;
public:
	enemyJumpState() { _delayCount = 0; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyAttackState : public enemyState
{
private:
	RECT _attack;
	int _comboCount;
	int _strikeCount;
	int  _collisionCount;
	bool _isAttack;
public:
	enemyAttackState() { _comboCount = 0; _strikeCount = 0; _isAttack = false; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyHitState : public enemyState
{
private:
	int _delayCount;
	int _oneCount;
	int _twoCount;
	int _downCount;
	int _frameCount;
public:
	enemyHitState() { _delayCount = 0; _oneCount = 0; _twoCount = 0; _downCount = 0; _frameCount = 0; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyDownState : public enemyState
{
public:
	enemyDownState() {}

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyDizzyState : public enemyState
{
private:
	int _dizzyCount;
	int _frameCount;
public:
	enemyDizzyState() { _dizzyCount = 0; _frameCount = 0; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyDeadState : public enemyState
{
private:
	int _deadCount;
public:
	enemyDeadState() { _deadCount = 0; }
	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};