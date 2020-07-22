#pragma once

#define DELAYMAX 200	//´Ù¿îµÆÀ» ¶§ µô·¹ÀÌ½Ã°£

class enemy;

class enemyMoveState;
class enemyRunState;
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
	static enemyMoveState* enemyMove;
	static enemyRunState* enemyRun;
	static enemyAttackState* enemyAttack;
	static enemyHitState* enemyHit;
	static enemyDownState* enemyDown;
	static enemyDizzyState* enemyDizzy;
	static enemyDeadState* enemyDead;
};

class enemyMoveState : public enemyState
{
private:
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
	bool _isKick;
public:
	enemyRunState() { _kickCount = 0; _limitCount = 0; _isKick = false; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyAttackState : public enemyState
{
private:
	RECT _attack;
	int _comboCount;
	bool _isAttack;
	bool _isStrike;
public:
	enemyAttackState() { _comboCount = 0; _isAttack = false; _isStrike = false; }

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
public:
	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};