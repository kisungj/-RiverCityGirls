#include "stdafx.h"
#include "enemyState.h"
#include "enemy.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//===================================================무브 클래스===================================================//
void enemyMoveState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{	
	_waitCount++;

	//==================y축 이동==================//

	if (enemy.getY() < y - 100)
	{
		enemy.setY(enemy.getY() + 2);
	}

	if (enemy.getY() > y + 100)
	{
		enemy.setY(enemy.getY() - 2);
	}

	//==================x축 이동==================//
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

	if (_waitCount > 200 && enemy.getCondition() == CONDITION::SEARCH)
	{
		if (enemy.getRight()) enemy.setX(enemy.getX() + 2);
		else enemy.setX(enemy.getX() - 2);

		//==================런 클래스로 이동==================//
		if (getDistance(x, y, enemy.getX(), enemy.getY()) > 500)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_run"));
			}
			enemy.setState(enemy.getRun());
			_waitCount = 0;
		}
	}

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch())
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
		}
		/*if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());*/
		enemy.setState(enemy.getHit());
		_waitCount = 0;
	}

	//==================공격 클래스로 이동==================//
	if (enemy.getCondition() == CONDITION::CLOSE)
	{
		_delayCount++;		

		if (_delayCount > 30)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_attack1"));
			}
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getAttack());
			_delayCount = 0;
			_waitCount = 0;
		}		
	}

	cout << "move class" << endl;
	cout << x - enemy.getX() << endl;
}

//===================================================런클래스===================================================//
void enemyRunState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;

	if (!enemy.getStop())
	{
		if (enemy.getY() < y - 100)
		{
			enemy.setY(enemy.getY() + 1);
		}

		if (enemy.getY() > y + 100)
		{
			enemy.setY(enemy.getY() - 1);
		}

		if (enemy.getRight()) enemy.setX(enemy.getX() + 5);
		else enemy.setX(enemy.getX() - 5);
	}	

	if (enemy.getCondition() == CONDITION::CLOSE)
	{	
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_sidekick"));
		}
		/*if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());*/

		if (enemy.getRight())
		{
			if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX() - 1)
			{
				enemy.setAtk(enemy.getX() + 65, enemy.getY(), 95, 200);
			}

			if (enemy.getFrameX() == 0)
			{
				if (IntersectRect(&temp, &rc, &_attack))
				{
					enemy.setAtk(0, 0, 0, 0);
					enemy.setStop(true);
				}
			}
		}

		if (!enemy.getRight())
		{
			if (enemy.getFrameX() == 1)
			{
				enemy.setAtk(enemy.getX() - 65, enemy.getY(), 95, 200);
			}

			if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX())
			{
				if (IntersectRect(&temp, &rc, &_attack))
				{
					enemy.setAtk(0, 0, 0, 0);
					enemy.setStop(true);
				}
			}
		}
	}

	if (enemy.getStop()) _kickCount++;

	//==================무브 클래스로 이동==================//
	if (_kickCount > 30)
	{
		enemy.setStop(false);

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getMove());
		_kickCount = 0;
	}

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch())
	{		
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getHit());
		_kickCount = 0;
	}

	cout << "run class" << endl;
}

//===================================================어택 클래스===================================================//
void enemyAttackState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;
	_isAttack = true;

	//==================공격 렉트 생성==================//
	if (enemy.getRight())
	{
		if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX() - 1)
		{
			enemy.setAtk(enemy.getX() + 65, enemy.getY(), 95, 200);
		}

		if (enemy.getFrameX() == 0)
		{
			if (IntersectRect(&temp, &rc, &_attack))
			{
				_comboCount++;
				enemy.setAtk(0, 0, 0, 0);
			}
		}
	}

	if (!enemy.getRight())
	{
		if (enemy.getFrameX() == 1)
		{
			enemy.setAtk(enemy.getX() - 65, enemy.getY(), 95, 200);
		}

		if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX())
		{
			if (IntersectRect(&temp, &rc, &_attack))
			{
				_comboCount++;
				enemy.setAtk(0, 0, 0, 0);
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

	//==================무브 클래스로 이동==================//
	if (!_isAttack)
	{
		_comboCount = 0;
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getMove());
	}

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch())
	{
		_comboCount = 0;
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1")); 
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getHit());
	}

	cout << "attack class" << endl;
	cout << enemy.getFrameX() << endl;
}

//===================================================힛 클래스===================================================//
void enemyHitState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;
	_frameCount++;

	if (enemy.getStop())
	{
		if (_frameCount % 7 == 0)
		{
			if (enemy.getFrameY() == 0)
			{
				enemy.setFrameX(enemy.getFrameX() + 1);
				if (enemy.getFrameX() >= enemy.getImage()->getMaxFrameX() - 1) enemy.setFrameX(0);
			}

			if (enemy.getFrameY() == 1)
			{
				if (enemy.getFrameX() <= 1) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
				enemy.setFrameX(enemy.getFrameX() - 1);
			}
			_frameCount = 0;
		}
	}

	//일반적으로 맞았을 때
	if (!enemy.getLay())
	{
		if (enemy.getRight())
		{
			if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX() - 1)
			{
				enemy.setStop(true);
			}
		}

		if (!enemy.getRight())
		{
			if (enemy.getFrameX() == 1)
			{
				enemy.setStop(true);
			}
		}

		if (enemy.getHitCount() == 1)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));

			if (_oneCount == 0)
			{
				if (enemy.getFrameY() == 0) enemy.setFrameX(0);
				else enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			}

			_oneCount++;

			if (_oneCount > 15)
			{
				enemy.setStop(false);
			}
		}

		if (enemy.getHitCount() == 2 && _oneCount <= 20)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit2"));

			if (_twoCount == 0)
			{
				if (enemy.getFrameY() == 0) enemy.setFrameX(0);
				else enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			}

			_twoCount++;

			if (_twoCount > 15)
			{
				enemy.setStop(false);
			}
		}

		if (enemy.getHitCount() == 3 && _twoCount < 20)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit3"));
		}	

		if (_oneCount > 20)
		{
			_oneCount = 0;
			enemy.setOuch(false);
			enemy.setHitCount(-enemy.getHitCount());
		}

		if (_twoCount > 20)
		{
			_twoCount = 0;
			enemy.setOuch(false);
			enemy.setHitCount(-enemy.getHitCount());
		}
	}

	//누워서 맞았을 때
	if (enemy.getLay())
	{		
		if (enemy.getRight() && enemy.getLayCount() <= DELAYMAX)
		{
			if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX() - 1)
			{
				enemy.setHitCount(-enemy.getHitCount());
				enemy.setStop(true);
				_downCount++;

				if(_downCount ==3 || enemy.getLayCount() == DELAYMAX) enemy.setFrameX(24);
			}
		}

		if (!enemy.getRight() && enemy.getLayCount() <= DELAYMAX)
		{
			if (enemy.getFrameX() == 1)
			{
				enemy.setHitCount(-enemy.getHitCount());
				enemy.setStop(true); 
				_downCount++;

				if (_downCount == 3 || enemy.getLayCount() == DELAYMAX) enemy.setFrameX(8);
			}
		}

		if (enemy.getHitCount() >= 1)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_groundhit"));
			enemy.setStop(false);		
		}

		if (enemy.getHitCount() <= 0 && enemy.getStop())
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_knockdown"));
			
			if (enemy.getFrameY() == 0) enemy.setFrameX(24);
			else enemy.setFrameX(8);
		}

		if (enemy.getLayCount() >= DELAYMAX || _downCount >= 3)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_knockdown"));
			enemy.setOuch(false);
			enemy.setStop(false);

			if (enemy.getRight())
			{
				if (enemy.getFrameX() >= enemy.getImage()->getMaxFrameX() - 1)
				{
					enemy.setLay(false);
					enemy.setLayCount(-enemy.getLayCount());
					enemy.setFrameX(0);
				}
			}

			if (!enemy.getRight())
			{
				if (enemy.getFrameX() <= 1)
				{
					enemy.setLay(false);
					enemy.setLayCount(-enemy.getLayCount());
				}
			}
		}	
	}

	//==================다운 클래스로 이동==================//
	if (enemy.getHitCount() >= 3 && !enemy.getLay())
	{
		_oneCount = 0;
		_twoCount = 0;
		_downCount = 0;

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_knockdown"));
		}

		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getDown());
		enemy.setStop(false);

		enemy.setHitCount(-enemy.getHitCount());
		
	}

	//==================무브 클래스로 이동==================//
	if ((enemy.getCondition() == CONDITION::SEARCH || !enemy.getOuch()) && !enemy.getLay())
	{
		_oneCount = 0;
		_twoCount = 0;
		_downCount = 0;

		enemy.setStop(false);
		_delayCount++;

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
		}
		
		if (_delayCount > 50)
		{
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getMove());

			enemy.setHitCount(-enemy.getHitCount());
			_delayCount = 0;
		}
	}

	cout << "hit class" << endl;
	cout << enemy.getLayCount() << ", " << enemy.getStop() << ", " << enemy.getLay() << endl;

}

//===================================================다운 클래스===================================================//
void enemyDownState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	enemy.setRC(enemy.getX(), enemy.getY(), enemy.getImage()->getFrameWidth(), 100);

	if (enemy.getRight()) 
	{
		if (enemy.getFrameX() == 24)
		{
			enemy.setStop(true);
			enemy.setLay(true);
		}

		if (enemy.getFrameX() <= 1)
		{
			enemy.setLay(false);
		}
	}

	if (!enemy.getRight())
	{
		if (enemy.getFrameX() == 8)
		{
			enemy.setStop(true);
			enemy.setLay(true);
		}
		
		if (enemy.getFrameX() >= enemy.getImage()->getMaxFrameX() - 1)
		{
			enemy.setLay(false);
		}
	}

	if (!enemy.getLay())
	{
		enemy.setOuch(false);
	}

	if (enemy.getLayCount() > DELAYMAX)
	{
		enemy.setStop(false);
	}

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch() && enemy.getLay())
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_groundhit"));
		}
		/*if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());*/
		enemy.setState(enemy.getHit());
	}

	if (!enemy.getLay() && enemy.getLayCount() >= DELAYMAX)
	{
		int _rndstun = RND->getInt(100);

		//==================무브 클래스로 이동==================//
		if (enemy.getCondition() == CONDITION::SEARCH && _rndstun > 30 && _rndstun <= 100)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
			}
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getMove());
			enemy.setLayCount(-enemy.getLayCount());
		}

		//==================공격 클래스로 이동==================//
		if (enemy.getCondition() == CONDITION::CLOSE && _rndstun > 30 && _rndstun <= 100)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_attack1"));
			}
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getAttack());
			enemy.setLayCount(-enemy.getLayCount());
		}

		//==================디지 클래스로 이동==================//
		if (_rndstun >= 0 && _rndstun <= 30)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_dizzy"));
			}
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getDizzy());
			enemy.setLayCount(-enemy.getLayCount());
		}
	}

	cout << "down class" << endl;
	cout << enemy.getHitCount() << ", " << enemy.getOuch() << endl;
}

//===================================================어질어질 클래스===================================================//
void enemyDizzyState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	_dizzyCount++;
	_frameCount++;

	enemy.setStop(true);

	if (_frameCount % 7 == 0)
	{
		if (enemy.getFrameY() == 0)
		{
			enemy.setFrameX(enemy.getFrameX() + 1);
			if (enemy.getFrameX() >= enemy.getImage()->getMaxFrameX()) enemy.setFrameX(0);
		}

		if (enemy.getFrameY() == 1)
		{
			enemy.setFrameX(enemy.getFrameX() - 1);
			if (enemy.getFrameX() <= 0) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		}
		_frameCount = 0;
	}	

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch())
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
		}
		/*if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());*/
		enemy.setState(enemy.getHit());
		enemy.setStop(false);
		_dizzyCount = 0;
	}

	//==================무브 클래스로 이동==================//	
	if (_dizzyCount > 300)
	{	
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		}
		enemy.setState(enemy.getMove());
		enemy.setStop(false);
		_dizzyCount = 0;		
	}

	cout << "dizzy class" << endl;
}