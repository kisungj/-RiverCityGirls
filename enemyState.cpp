#include "stdafx.h"
#include "enemyState.h"
#include "enemy.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//===================================================아이들 클래스===================================================//
void enemyIdleState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	_searchCount++;

	if (x > enemy.getX() - 700 && x < enemy.getX() + 700) _isDiscover = true;

	if (_searchCount > 100 && _isDiscover)
	{
		_searchCount = 0;
		_isDiscover = false;

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_walk"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_walk"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getMove());
	}

	if (enemy.getOuch())
	{
		_searchCount = 0;
		_isDiscover = false;

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit1"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getHit());
	}

	//cout << "idle class" << endl;
}

//===================================================무브 클래스===================================================//
void enemyMoveState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{	
	_waitCount++;
	_randomCount++;

	if (_randomCount % 100 == 0)
	{
		_rnd = RND->getInt(3);
	}

	if (_rnd == 0)
	{
		//==================y축 이동==================//

		if (enemy.getZ() < y - 100 && enemy.getPixel() != PIXEL::BOTTOM)
		{
			enemy.setY(enemy.getY() + 2);
		}

		if (enemy.getZ() > y + 100 && enemy.getPixel() != PIXEL::TOP)
		{
			enemy.setY(enemy.getY() - 2);
		}

		enemy.setZ(enemy.getY() + 100);
	}

	if (_rnd == 1)
	{
		//==================x축 이동==================//
		if (enemy.getRight())
		{
			if (enemy.getX() < x - 400 && enemy.getPixel() != PIXEL::RIGHT)
			{
				enemy.setX(enemy.getX() + 2);
			}
		}

		if (!enemy.getRight())
		{
			if (enemy.getX() > x + 400 && enemy.getPixel() != PIXEL::LEFT)
			{
				enemy.setX(enemy.getX() - 2);
			}
		}
	}

	if (_rnd == 2)
	{
		
	}

	if (_waitCount > 200 && enemy.getCondition() == CONDITION::SEARCH)
	{
		if (enemy.getRight() && enemy.getPixel() != PIXEL::RIGHT)
		{
			enemy.setX(enemy.getX() + 2);
		}

		if (!enemy.getRight() && enemy.getPixel() != PIXEL::LEFT)
		{
			enemy.setX(enemy.getX() - 2);
		}

		if (enemy.getZ() < y - 20 && enemy.getPixel() != PIXEL::BOTTOM)
		{
			enemy.setY(enemy.getY() + 1);
		}

		if (enemy.getZ() > y + 20 && enemy.getPixel() != PIXEL::TOP)
		{
			enemy.setY(enemy.getY() - 1);
		}

		enemy.setZ(enemy.getY() + 100);

		
		if (getDistance(x, y, enemy.getX(), enemy.getZ()) > 600)
		{
			int rnd = RND->getInt(2);
			//==================런 클래스로 이동==================//
			if (rnd == 0)
			{
				if (enemyType == ENEMYTYPE::BOY)
				{
					enemy.setImage(IMAGEMANAGER->findImage("boy_run"));
				}
				if (enemyType == ENEMYTYPE::GIRL)
				{
					enemy.setImage(IMAGEMANAGER->findImage("girl_run"));
				}
				if (enemy.getRight()) enemy.setFrameX(0);
				if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
				enemy.setState(enemy.getRun());
				_waitCount = 0;
				_randomCount = 0;
			}
			
			//==================아이들 클래스로 이동==================//
			if (rnd == 1)
			{
				if (enemyType == ENEMYTYPE::BOY)
				{
					enemy.setImage(IMAGEMANAGER->findImage("boy_idle"));
				}
				if (enemyType == ENEMYTYPE::GIRL)
				{
					enemy.setImage(IMAGEMANAGER->findImage("girl_idle"));
				}
				if (enemy.getRight()) enemy.setFrameX(0);
				if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
				enemy.setState(enemy.getIdle());
				_waitCount = 0;
				_randomCount = 0;
			}			
		}
	}

	//==================점프 클래스로 이동==================//
	if (enemy.getCondition() == CONDITION::GREEN && enemyType == ENEMYTYPE::GIRL)
	{
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_jump"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		else enemy.setFrameX(enemy.getImage()->getMaxFrameX());

		_waitCount = 0;
		_randomCount = 0;
	}

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch())
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit1"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getHit());
		_waitCount = 0;
		_randomCount = 0;
	}

	//==================공격 클래스로 이동==================//
	if (enemy.getCondition() == CONDITION::CLOSE)
	{
		_delayCount++;		

		if (_delayCount > 50)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_attack1"));
			}
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_attack1"));
			}
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getAttack());
			_delayCount = 0;
			_waitCount = 0;
			_randomCount = 0;
		}		
	}

	//==================데드 클래스로 이동==================//
	if (enemy.getHP() <= 0)
	{
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_knockdown"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_knockdown"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getDie());
	}

	//cout << "move class" << endl;
}

//===================================================런클래스===================================================//
void enemyRunState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;
	_limitCount++;

	enemy.setZ(enemy.getY() + 100);

	if (!enemy.getStop() && !_isKick)
	{
		if (enemy.getZ() < y - 20 && enemy.getPixel() != PIXEL::BOTTOM)
		{
			enemy.setY(enemy.getY() + 1);
		}

		if (enemy.getZ() > y + 20 && enemy.getPixel() != PIXEL::TOP)
		{
			enemy.setY(enemy.getY() - 1);
		}

		if (enemy.getRight() && enemy.getPixel() != PIXEL::RIGHT)
		{
			enemy.setX(enemy.getX() + 5);
		}

		if (!enemy.getRight() && enemy.getPixel() != PIXEL::LEFT)
		{
			enemy.setX(enemy.getX() - 5);
		}

		if (getDistance(x, y, enemy.getX(), enemy.getZ()) < 100)
		{
			_isKick = true;
			enemy.setCond(CONDITION::STRONG);

			if (enemy.getRight()) enemy.setFrameX(1);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX() - 1);

			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_sidekick"));
			}
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_attack3"));
			}
		}
	}

	if (_isKick)
	{
		if (enemy.getRight())
		{
			if (enemy.getFrameX() >= enemy.getImage()->getMaxFrameX() - 3)
			{
				enemy.setAtk(enemy.getX() + 65, enemy.getY(), 95, 200);
				enemy.setStop(true);
			}

			if (enemy.getFrameX() == 1)
			{
				if (enemy.getStrike())
				{
					enemy.setStrike(false);
				}
				else enemy.setAtk(0, 0, 0, 0);
			}
		}

		if (!enemy.getRight())
		{
			if (enemy.getFrameX() <= 3)
			{
				enemy.setAtk(enemy.getX() - 65, enemy.getY(), 95, 200);
				enemy.setStop(true);
			}

			if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX() - 1)
			{
				if (enemy.getStrike())
				{
					enemy.setStrike(false);
				}
				else enemy.setAtk(0, 0, 0, 0);
			}
		}
	}

	if (enemy.getStop())
	{
		_kickCount++;
	}

	//==================아이들 클래스로 이동==================//
	if (_kickCount > 50 || _limitCount > 150 || (enemy.getX() - x < 50 && x - enemy.getX() < 50 && y - enemy.getY() > 50 && enemy.getY() - y > 50))
	{
		enemy.setStop(false);
		enemy.setStrike(false);
		_isKick = false;

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_idle"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_idle"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getIdle());
		_kickCount = 0;
		_limitCount = 0;
	}

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch())
	{
		enemy.setStop(false);
		enemy.setStrike(false);
		_isKick = false;

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit1"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getHit());
		_kickCount = 0;
		_limitCount = 0;
	}

	//cout << "run class" << endl;
}


//===================================================점프 클래스===================================================//
void enemyJumpState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	_angle = getAngle(x, y, enemy.getX(), enemy.getY());

	enemy.setJump(true);
	enemy.setY(enemy.getY() - enemy.getJumpPower());
//	enemy.setJumpPower(-enemy.getGravity());

	//cout << "jump class" << endl;
}


//===================================================어택 클래스===================================================//
void enemyAttackState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;
	_isAttack = true;

	//==================공격 렉트 생성==================//
	if (enemy.getRight())
	{
		if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX() - 3)
		{
			enemy.setAtk(enemy.getX() + 65, enemy.getY(), 95, 200);
			enemy.setStop(true);
		}

		if (enemy.getFrameX() == 0)
		{
			if (enemy.getStrike())
			{
				_comboCount++; 
				enemy.setStrike(false);
			}
		}
	}

	if (!enemy.getRight())
	{
		if (enemy.getFrameX() == 3)
		{
			enemy.setAtk(enemy.getX() - 65, enemy.getY(), 95, 200);
			enemy.setStop(true);
		}

		if (enemy.getFrameX() == enemy.getImage()->getMaxFrameX())
		{
			if (enemy.getStrike())
			{
				_comboCount++;
				enemy.setStrike(false);
			}
			else enemy.setAtk(0, 0, 0, 0);
		}
	}

	if (_isAttack)
	{
		if (_comboCount == 0)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_attack1"));
			}			
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_attack1"));
			}
		}

		if (_comboCount == 1)
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_attack2"));
			}
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_attack2"));
			}
		}

		if (_comboCount == 2)
		{
			enemy.setCond(CONDITION::STRONG);

			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_attack3"));
			}
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_attack3"));
			}
		}
	}

	if (enemy.getStop())
	{
		_strikeCount++;
	}

	if (_strikeCount > 0)
	{
		enemy.setStop(false);

		if(enemy.getStrike()) _strikeCount = 0;

		if (!enemy.getStrike())
		{
			if (enemy.getRight() && enemy.getFrameX() >= enemy.getImage()->getMaxFrameX() - 1)
			{
				_isAttack = false;
				enemy.setAtk(0, 0, 0, 0);
			}

			if (!enemy.getRight() && enemy.getFrameX() <= 1)
			{
				_isAttack = false;
				enemy.setAtk(0, 0, 0, 0);
			}
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

	//==================아이들 클래스로 이동==================//
	if (!_isAttack)
	{
		_comboCount = 0;
		_strikeCount = 0;
		enemy.setStrike(false);
		enemy.setStop(false);

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_idle"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_idle"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getIdle());
	}

	//==================힛 클래스로 이동==================//
	if (enemy.getOuch())
	{
		_comboCount = 0; 
		_strikeCount = 0;
		
		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1")); 
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit1"));
		}
		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getHit());
		enemy.setStrike(false);
		enemy.setStop(false);
	}

	//cout << "attack class" << endl;
}

//===================================================힛 클래스===================================================//
void enemyHitState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	RECT temp;
	_frameCount++;

	enemy.setZ(enemy.getY() + 100);

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
			if (enemyType == ENEMYTYPE::BOY)
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit1"));
			if (enemyType == ENEMYTYPE::GIRL)
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit1"));

			if (_oneCount == 0)
			{
				if (enemy.getFrameY() == 0) enemy.setFrameX(0);
				else enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			}

			_oneCount++;

			if (_oneCount > 25)
			{
				enemy.setStop(false);
			}
		}

		if (enemy.getHitCount() == 2 && _oneCount <= 30)
		{
			if (enemyType == ENEMYTYPE::BOY)
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit2"));
			if (enemyType == ENEMYTYPE::GIRL)
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit2"));

			if (_twoCount == 0)
			{
				if (enemy.getFrameY() == 0) enemy.setFrameX(0);
				else enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			}

			_twoCount++;

			if (_twoCount > 25)
			{
				enemy.setStop(false);
			}
		}

		if (enemy.getHitCount() == 3 && _twoCount < 30)
		{			
			if (enemyType == ENEMYTYPE::BOY)
			enemy.setImage(IMAGEMANAGER->findImage("boy_hit3"));
			if (enemyType == ENEMYTYPE::GIRL)
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit3"));
		}	

		if (_oneCount > 35)
		{
			_oneCount = 0;
			enemy.setOuch(false);
			enemy.setHitCount(-enemy.getHitCount());
		}

		if (_twoCount > 35)
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

				if(_downCount ==3 || enemy.getLayCount() == DELAYMAX) enemy.setFrameX(24);
			}
		}

		if (!enemy.getRight() && enemy.getLayCount() <= DELAYMAX)
		{
			if (enemy.getFrameX() == 1)
			{
				enemy.setHitCount(-enemy.getHitCount());
				enemy.setStop(true); 

				if (_downCount == 3 || enemy.getLayCount() == DELAYMAX) enemy.setFrameX(8);
			}
		}

		if (enemy.getHitCount() >= 1)
		{
			if (enemyType == ENEMYTYPE::BOY)
			enemy.setImage(IMAGEMANAGER->findImage("boy_groundhit"));
			if(enemyType == ENEMYTYPE::GIRL)
			enemy.setImage(IMAGEMANAGER->findImage("girl_groundhit"));
			enemy.setStop(false);		
		}

		if (enemy.getHitCount() <= 0 && enemy.getStop())
		{
			if (enemyType == ENEMYTYPE::BOY)
			{
				enemy.setImage(IMAGEMANAGER->findImage("boy_knockdown"));

				if (enemy.getFrameY() == 0) enemy.setFrameX(24);
				else enemy.setFrameX(8);
			}
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_knockdown"));

				if (enemy.getFrameY() == 0) enemy.setFrameX(22);
				else enemy.setFrameX(10);
			}
		}			

		if (enemy.getLayCount() >= DELAYMAX || _downCount >= 3)
		{
			if (enemyType == ENEMYTYPE::BOY)
			enemy.setImage(IMAGEMANAGER->findImage("boy_knockdown"));
			if (enemyType == ENEMYTYPE::GIRL)
			enemy.setImage(IMAGEMANAGER->findImage("girl_knockdown"));
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
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_knockdown"));
		}

		if (enemy.getRight()) enemy.setFrameX(0);
		if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		enemy.setState(enemy.getDown());
		enemy.setStop(false);

		enemy.setHitCount(-enemy.getHitCount());
		
	}

	//==================아이들 클래스로 이동==================//
	if ((enemy.getCondition() == CONDITION::SEARCH || !enemy.getOuch()) && !enemy.getLay())
	{
		_oneCount = 0;
		_twoCount = 0;
		_downCount = 0;

		enemy.setStop(false);
		_delayCount++;

		if (enemyType == ENEMYTYPE::BOY)
		{
			enemy.setImage(IMAGEMANAGER->findImage("boy_idle"));
		}
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_idle"));
		}

		if (_delayCount > 50)
		{
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getIdle());

			enemy.setHitCount(-enemy.getHitCount());
			_delayCount = 0;
		}
	}

	//cout << "hit class" << endl;
	//cout << _downCount << endl;
}

//===================================================다운 클래스===================================================//
void enemyDownState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	if (enemy.getRight()) 
	{
		if ((enemyType == ENEMYTYPE::BOY && enemy.getFrameX() == 24) ||
			(enemyType == ENEMYTYPE::GIRL && enemy.getFrameX() == 22))
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
		if ((enemyType == ENEMYTYPE::BOY && enemy.getFrameX() == 8) ||
			(enemyType == ENEMYTYPE::GIRL && enemy.getFrameX() == 10))
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
		if(enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_groundhit"));
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
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_walk"));
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
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_attack1"));
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
			if (enemyType == ENEMYTYPE::GIRL)
			{
				enemy.setImage(IMAGEMANAGER->findImage("girl_dizzy"));
			}
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
			enemy.setState(enemy.getDizzy());
			enemy.setLayCount(-enemy.getLayCount());
		}
	}

	//cout << "down class" << endl;
}

//===================================================어질어질 클래스===================================================//
void enemyDizzyState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	_dizzyCount++;
	_frameCount++;

	enemy.setZ(enemy.getY() + 100);

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
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_hit1"));
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
		if (enemyType == ENEMYTYPE::GIRL)
		{
			enemy.setImage(IMAGEMANAGER->findImage("girl_walk"));
			if (enemy.getRight()) enemy.setFrameX(0);
			if (!enemy.getRight()) enemy.setFrameX(enemy.getImage()->getMaxFrameX());
		}
		enemy.setState(enemy.getMove());
		enemy.setStop(false);
		_dizzyCount = 0;		
	}

	//cout << "dizzy class" << endl;
}

//===================================================데드 클래스===================================================//
void enemyDeadState::update(enemy & enemy, RECT rc, float x, float y, ENEMYTYPE enemyType)
{
	enemy.setZ(enemy.getY() + 100);

	if (enemy.getRight())
	{
		if ((enemyType == ENEMYTYPE::BOY && enemy.getFrameX() == 24) ||
			(enemyType == ENEMYTYPE::GIRL && enemy.getFrameX() == 22))
		{
			enemy.setStop(true);
			enemy.setCond(CONDITION::DEAD);
		}
	}

	if (!enemy.getRight())
	{
		if ((enemyType == ENEMYTYPE::BOY && enemy.getFrameX() == 8) ||
			(enemyType == ENEMYTYPE::GIRL && enemy.getFrameX() == 10))
		{
			enemy.setStop(true);
			enemy.setCond(CONDITION::DEAD);
		}
	}
}
