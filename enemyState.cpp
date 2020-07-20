#include "stdafx.h"
#include "enemyState.h"
#include "enemy.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


//===================================================���� Ŭ����===================================================//
void enemyMoveState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	_delayCount++;
	enemy.setHitCount(-enemy.getHitCount());

	//==================y�� �̵�==================//

	if (enemy.getY() < y - 100)
	{
		enemy.setY(enemy.getY() + 2);
	}

	if (enemy.getY() > y + 100)
	{
		enemy.setY(enemy.getY() - 2);
	}

	//==================x�� �̵�==================//
	if (enemy.getRight())
	{
		if (enemy.getX() < x - 400)
		{
			enemy.setX(enemy.getX() + 2);
		}
	}

	if (!enemy.getRight())
	{
		if (enemy.getX() > x + 400)
		{
			enemy.setX(enemy.getX() - 2);
		}
	}

	//==================�� Ŭ������ �̵�==================//
	if (enemy.getOuch())
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
			/*if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());*/
		}
		enemy.setState(enemy.getHit());
		_delayCount = 0;
	}

	//==================���� Ŭ������ �̵�==================//
	if (enemy.getCondition() == CONDITION::CLOSE)
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_attack1"));
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		}
		enemy.setState(enemy.getAttack());
		_delayCount = 0;
	}

	//cout << _delayCount << endl;
	//cout << "move class" << endl;
}

//===================================================���� Ŭ����===================================================//
void enemyAttackState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;
	_isAttack = true;

	//==================���� ��Ʈ ����==================//
	if (enemy.getRight())
	{
		if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX() - 1)
		{
			_attack = RectMakeCenter(enemy.getX() + 65, enemy.getY(), 95, 200);
		}

		if (enemy.getFrameX() == 0)
		{
			if (IntersectRect(&temp, &rc, &_attack))
			{
				_comboCount++;
				_attack = RectMakeCenter(0, 0, 0, 0);
			}
		}
	}

	if (!enemy.getRight())
	{
		if (enemy.getFrameX() == 1)
		{
			_attack = RectMakeCenter(enemy.getX() - 65, enemy.getY(), 95, 200);
		}

		if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX())
		{
			if (IntersectRect(&temp, &rc, &_attack))
			{
				_comboCount++;
				_attack = RectMakeCenter(0, 0, 0, 0);
			}
		}
	}

	if (_isAttack)
	{
		if (_comboCount == 0)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_attack1"));
		}

		if (_comboCount == 1)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_attack2"));
		}

		if (_comboCount == 2)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_attack3"));
		}
	}

	if (_comboCount >= 3 || enemy.getCondition() == CONDITION::SEARCH)
	{
		if (enemy.getRight())
		{
			if (enemy.getFrameX() == 0)
			{
				_comboCount = 0;
				_isAttack = false;
			}
		}

		if (!enemy.getRight())
		{
			if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX())
			{
				_comboCount = 0;
				_isAttack = false;
			}
		}
	}

	//==================���� Ŭ������ �̵�==================//
	if (!_isAttack)
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		}
		enemy.setState(enemy.getMove());
	}

	//==================�� Ŭ������ �̵�==================//
	if (enemy.getOuch())
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1")); 
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getHit());
	}

	//cout << "attack class" << endl;
}

//===================================================���� Ŭ����===================================================//
void enemyGuardState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
}

//===================================================�� Ŭ����===================================================//
void enemyHitState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;
	//cout << _damageCount << ", " << enemy.getHitCount() << endl;

	if (enemy.getOuch())
	{
		if (enemy.getHitCount() == 1)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
			_damageCount++;
		}

		if (enemy.getHitCount() == 2)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit2"));
		}

		if (enemy.getHitCount() == 3)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit3"));
		}
	}

	if (_damageCount > 20)
	{
		_damageCount = 0;
		enemy.setHitCount(-enemy.getHitCount());
		enemy.setStop(false);
		enemy.setOuch(false);
	}

	//==================�ٿ� Ŭ������ �̵�==================//
	if (enemy.getHitCount() >= 3)
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_knockdown"));
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		}
		enemy.setState(enemy.getDown());
		enemy.setStop(false);
		_delayCount = 0;
	}

	//==================���� Ŭ������ �̵�==================//
	if (enemy.getCondition() == CONDITION::SEARCH || !enemy.getOuch())
	{
		_delayCount++;
		enemy.setStop(false);

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_idle"));
		}
		
		if (_delayCount > 50)
		{
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getMove());
			_delayCount = 0;
			_damageCount = 0;
		}
	}

	//1�� �±� ������ 0~2, 2�� �±� 3~5, 3�� �±� 6~8 (�ݴ�� 8~6, 5~3, 2~0)
	//cout << "hit class" << endl;

}

//===================================================�ٿ� Ŭ����===================================================//
void enemyDownState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	enemy.setRC(enemy.getX(), enemy.getY(), enemy.getImage()->getFrameWidth(), 100);
	enemy.setOuch(false);

	if (enemy.getRight()) 
	{
		if (enemy.getFrameX() == 24)
		{
			enemy.setStop(true);
			_isDown = true;
			enemy.setHitCount(-enemy.getHitCount());
		}

		if (enemy.getFrameX() <= 1)
		{
			_isDown = false;
		}
	}

	if (!enemy.getRight())
	{
		if (enemy.getFrameX() == 8)
		{
			enemy.setStop(true);
			_isDown = true;
			enemy.setHitCount(-enemy.getHitCount());
		}
		
		if (enemy.getFrameX() >= enemy.getImage()->getMaxFrameX() - 1)
		{
			_isDown = false;
		}
	}

	if (_isDown)
	{
		_downCount++;
	}

	cout << _downCount << endl;

	if (_downCount > 300)
	{
		enemy.setStop(false);
	}

	if (!_isDown && _downCount >= 300)
	{
		//==================���� Ŭ������ �̵�==================//
		if (enemy.getCondition() == CONDITION::SEARCH)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
				if (enemy.getRight()) enemy.setFrameX(0);
				if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			}
			enemy.setState(enemy.getMove());
			_downCount = 0;
		}

		//==================���� Ŭ������ �̵�==================//
		if (enemy.getCondition() == CONDITION::CLOSE)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_attack1"));
				if (enemy.getRight()) enemy.setFrameX(0);
				if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			}
			enemy.setState(enemy.getAttack());
			_downCount = 0;
		}
	}

	//cout << "down class" << endl;
}

//===================================================���� Ŭ����===================================================//
void enemyBegState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	//������

}

//===================================================�������� Ŭ����===================================================//
void enemyDizzyState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{

}
