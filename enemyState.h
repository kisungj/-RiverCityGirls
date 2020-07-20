#pragma once

class enemy;

class enemyMoveState;
class enemyAttackState;
class enemyGuardState;
class enemyHitState;
class enemyDownState;
class enemyBegState;
class enemyDizzyState;

enum class ENEMYTYPE
{
	BOY, GIRL, CHEER
};

class enemyState
{
public:
	virtual ~enemyState() {}

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) = 0;

	/*virtual void move(enemy& enemy, float x, float y, ENEMYTYPE enemyType) = 0;
	virtual void attack(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) = 0;
	virtual void guard(enemy& enemy, float x, float y, ENEMYTYPE enemyType) = 0;
	virtual void hit(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) = 0;
	virtual void down(enemy& enemy, ENEMYTYPE enemyType) = 0;
	virtual void beg(enemy& enemy, RECT rc, ENEMYTYPE enemyType) = 0;
	virtual void dizzy(enemy& enemy, ENEMYTYPE enemyType) = 0;*/

public:
	static enemyMoveState* enemyMove;
	static enemyAttackState* enemyAttack;
	static enemyGuardState* enemyGuard;
	static enemyHitState* enemyHit;
	static enemyDownState* enemyDown;
	static enemyBegState* enemyBeg;
	static enemyDizzyState* enemyDizzy;
};

class enemyMoveState : public enemyState
{
private:
	int _delayCount;
public:
	enemyMoveState() { _delayCount = 0; }
	~enemyMoveState() {}

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyAttackState : public enemyState
{
private:
	RECT _attack;
	int _comboCount;
	bool _isAttack;
public:
	enemyAttackState() { _comboCount = 0; _isAttack = 0; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyGuardState : public enemyState
{
public:
	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyHitState : public enemyState
{
private:
	int _delayCount;
	int _damageCount;
public:
	enemyHitState() { _delayCount = 0; _damageCount = 0; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyDownState : public enemyState
{
private:
	int _downCount;
	bool _isDown;
public:
	enemyDownState() { _downCount = 0; _isDown = false; }

	virtual void update(enemy& enemy, RECT rc, float x, float y, ENEMYTYPE enemyType) override;
};

class enemyBegState : public enemyState
{
public:
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