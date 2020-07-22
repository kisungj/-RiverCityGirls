#include "stdafx.h"
#include "player.h"

void idleState::update(player & player)
{
	//run
	if (player.getRunCount() < 30 && player.getRunCount() > 0)
	{
		if (!player.getDirectionX())
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
				player.setState(player.getRunState());
				player.setRunCount(0);
			}

		}
		if (player.getDirectionX())
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
				player.setState(player.getRunState());
				player.setRunCount(0);
			}
		}
	}

	//왼쪽
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
		player.setState(player.getWalkState());
		player.setDirectionX(false);
	}
	//오른쪽
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
		player.setState(player.getWalkState());
		player.setDirectionX(true);
	}
	//위
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player.setDirectionY(true);
		//오른쪽이라면
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
		}
		//왼쪽이라면
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
		}
	}

	//아래
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player.setDirectionY(false);
		if (WINSIZEY > player.getShadowY() - 100)
		{
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
			}
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
			}
		}
	}
	//점프
	if (!player.getIsJumping())
	{
		player.setIsRun(false);
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			player.setJumpPower(10);
			player.setGravity(0.8f);
			player.setIsJumping(true);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());

			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());
			}
		}
	}

	//기본공격
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setIsAttack(true);
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1"), IMAGEMANAGER->findImage("PLAYER_ATTACK1"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() - 50, player.getPlayerY(), 120, 100);
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1"), IMAGEMANAGER->findImage("PLAYER_ATTACK1"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() + 50, player.getPlayerY(), 120, 100);
		}
	}
	//밟기
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_STOMP"), IMAGEMANAGER->findImage("PLAYER_STOMP"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() , player.getPlayerY() + 100, 120, 20);
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_STOMP"), IMAGEMANAGER->findImage("PLAYER_STOMP"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
		}
	}
	//회오리킥
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_KICK"), IMAGEMANAGER->findImage("PLAYER_KICK"));
		player.setState(player.getAttackState());
		player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
	}

	//가드
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getGuardState());
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getGuardState());
		}
	}

	//강공격
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_STRONG_ATTACK"), IMAGEMANAGER->findImage("PLAYER_STRONG"));
			player.setState(player.getAttackState());
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_STRONG_ATTACK"), IMAGEMANAGER->findImage("PLAYER_STRONG"));
			player.setState(player.getAttackState());
		}
	}

	player.mouseCol();
}

void walkState::update(player & player)
{
	player.setRunCount(player.getRunCount() + 1);
	//왼쪽
	if (!player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				player.setDirectionY(true);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				player.setDirectionY(false);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			}
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				return;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
			}
			if (player.getIsLeft())
			{
				player.setShadowX(player.getShadowX() - 3);
			}
		}
	}

	//오른쪽
	if (player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				player.setDirectionY(true);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				player.setDirectionY(false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			}
			else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				return;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
			}

			if (player.getIsRight())
			{
				player.setShadowX(player.getShadowX() + 3);
			}
		}
	}

	//왼쪽
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(false);
			if (player.getRunCount() > 6)
			{
				player.setRunCount(0);
			}

		}
		else
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(true);
		}
	}

	//오른쪽
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(true);
			if (player.getRunCount() > 6)
			{
				player.setRunCount(0);
			}
		}
		else
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(false);
		}
	}
	

	//위
	if (player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
				if (!player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
			}
			else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				return;
			}

			if (player.getIsTop())
			{
				player.setShadowY(player.getShadowY() - 3);
			}
		}
	}
	if (!player.getDirectionY())
	{
		//아래
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (!player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
				else if (player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
			}
			else if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				return;
			}
			if (player.getIsBottom())
			{
				player.setShadowY(player.getShadowY() + 3);
			}
		}
	}
	
	//위
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setDirectionY(true);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
		}
		else
		{
			player.setDirectionY(false);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			}

		}
	}
	//아래
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setDirectionY(false);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
		}
		else
		{
			player.setDirectionY(true);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			}
		}
	}
	

	//점프
	if (!player.getIsJumping())
	{
		player.setIsRun(false);
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			player.setJumpPower(10);
			player.setGravity(0.8f);
			player.setIsJumping(true);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());

			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());
			}
		}
	}
	//기본 공격
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setIsAttack(true);
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1"), IMAGEMANAGER->findImage("PLAYER_ATTACK1"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() - 50, player.getPlayerY(), 120, 100);
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1"), IMAGEMANAGER->findImage("PLAYER_ATTACK1"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() + 50, player.getPlayerY(), 120, 100);
		}
	}

	//밟기
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_STOMP"), IMAGEMANAGER->findImage("PLAYER_STOMP"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_STOMP"), IMAGEMANAGER->findImage("PLAYER_STOMP"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
		}
	}

	//회오리킥
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_KICK"), IMAGEMANAGER->findImage("PLAYER_KICK"));
		player.setState(player.getAttackState());
		player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
	}


	//가드
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getGuardState());
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getGuardState());
		}
	}

	player.mouseCol();
}


void runState::update(player & player)
{
	//왼쪽
	if (!player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				player.setDirectionY(true);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				player.setDirectionY(false);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			}
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				return;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}
			if (player.getIsLeft())
			{
				player.setShadowX(player.getShadowX() - 7);
			}
		}
	}

	//오른쪽
	if (player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				player.setDirectionY(true);
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				player.setDirectionY(false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			}
			else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				return;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}

			if (player.getIsRight())
			{
				player.setShadowX(player.getShadowX() + 7);
			}
		}
	}

	//왼쪽
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(false);
			if (player.getRunCount() > 21)
			{
				player.setRunCount(0);
			}

		}
		else
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(true);
		}
	}

	//오른쪽
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(true);
			if (player.getRunCount() > 21)
			{
				player.setRunCount(0);
			}
		}
		else
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(false);
		}
	}


	//위
	if (player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				if (player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
				if (!player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
			}
			else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				return;
			}
	
			if (player.getIsTop())
			{
				player.setShadowY(player.getShadowY() - 3);
			}
		}
	}
	if (!player.getDirectionY())
	{
		//아래
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				if (!player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
				else if (player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				}
			}
			else if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				return;
			}
			if (player.getIsBottom())
			{
				player.setShadowY(player.getShadowY() + 3);
			}
		}
	}
	
	//위
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setDirectionY(true);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
		}
		else
		{
			player.setDirectionY(false);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}
	
		}
	}
	//아래
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setDirectionY(false);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
		}
		else
		{
			player.setDirectionY(true);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}
		}
	}
	

	//점프
	if (!player.getIsJumping())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			//player.setJumpPower(player.getJumpPower() + 1);
			player.setIsRun(true);
			player.setJumpPower(10);
			player.setGravity(0.8f);
			player.setIsJumping(true);
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());

			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());
			}
		}
	}

	//기본공격
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setIsAttack(true);
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1"), IMAGEMANAGER->findImage("PLAYER_ATTACK1"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() - 50, player.getPlayerY(), 120, 100);
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1"), IMAGEMANAGER->findImage("PLAYER_ATTACK1"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() + 50, player.getPlayerY(), 120, 100);
		}
	}

	//슬라이딩
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_DIVE"), IMAGEMANAGER->findImage("PLAYER_DIVE"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() - 50, player.getPlayerY(), 120, 100);
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_DIVE"), IMAGEMANAGER->findImage("PLAYER_DIVE"));
			player.setState(player.getAttackState());
			player.setAttack(player.getPlayerX() + 50, player.getPlayerY(), 120, 100);
		}
	}

	//회오리킥
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_KICK"), IMAGEMANAGER->findImage("PLAYER_KICK"));
		player.setState(player.getAttackState());
		player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
	}

	player.mouseCol();
}



HRESULT jumpState::init()
{
	_jumpCount = 0;
	_isJump = false;
	return S_OK;
}

void jumpState::update(player & player)
{
	_jumpCount++;
	//점프 올리기
	if (_jumpCount < 25)
	{
		_isJump = true;
	}
	else _isJump = false;
	

	if (player.getIsJumping())
	{
		player.setPlayerY(player.getPlayerY() - player.getJumpPower());
		player.setJumpPower(player.getJumpPower() - player.getGravity());
		player.setGravity(player.getGravity());
		//떨어질때 위치 바꾸면 바뀌게
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			player.setDirectionX(false);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			player.setDirectionX(true);
		}
	}

	//제일 높게 있는 상태면 떨어지는 자세로 바뀌기
	if (player.getJumpPower() < 0 && !_isJump)
	{
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			}
			if (player.getShadow() <= 200)
			{
				player.setShadow(player.getShadow() + 5);
			}
		}
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			}
			if (player.getShadow() <= 200)
			{
				player.setShadow(player.getShadow() + 5);
			}
		}
		
	}
	if (_isJump)
	{
		if (KEYMANAGER->isStayKeyDown('Z'))
		{
			player.setJumpPower(player.getJumpPower() + 0.8f);
			if (player.getShadow() >= 0)
			{
				player.setShadow(player.getShadow() - 5);
			}
		}
	}
	

	if (player.getPlayerY() >= player.getShadowY() - 110)
	{
		_jumpCount = 0;
		//아무것도 안누르면 아이들로
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			if (!player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
				player.setDirectionX(false);
			}
			if (player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
				player.setDirectionX(true);
			}
		}
		//런상태이면 런으로 가게
		else if (player.getIsRun())
		{
			if (!player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
				player.setState(player.getRunState());
				player.setDirectionX(false);
				player.setIsRun(false);
				//cout << "d" << endl;
			}
			else if (player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
				player.setState(player.getRunState());
				player.setDirectionX(true);
				player.setIsRun(false);
				//cout << "d" << endl;
			}
		}
		//아님 걷기
		else
		{
			if (!player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
				player.setDirectionX(false);
			}
			else if (player.getDirectionX())
			{

				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
				player.setDirectionX(true);
			}
		}
	}
	//런상태 아니면 걸어가게 속도조절
	if (!player.getIsRun())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && player.getIsLeft())
		{
			player.setShadowX(player.getShadowX() - 3);
			player.setPlayerX(player.getPlayerX() - 3);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && player.getIsRight())
		{
			player.setShadowX(player.getShadowX() + 3);
			player.setPlayerX(player.getPlayerX() + 3);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && player.getIsTop())
		{
			player.setShadowY(player.getShadowY() - 3);
			player.setPlayerY(player.getPlayerY() - 3);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && player.getIsBottom())
		{
			player.setShadowY(player.getShadowY() + 3);
			player.setPlayerY(player.getPlayerY() + 3);
		}
	}
	//런상태이면 속도조절
	if (player.getIsRun())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && player.getIsLeft())
		{
			player.setShadowX(player.getShadowX() - 7);
			player.setPlayerX(player.getPlayerX() - 7);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && player.getIsRight())
		{
			player.setShadowX(player.getShadowX() + 7);
			player.setPlayerX(player.getPlayerX() + 7);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && player.getIsTop())
		{
			player.setShadowY(player.getShadowY() - 7);
			player.setPlayerY(player.getPlayerY() - 7);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && player.getIsBottom())
		{
			player.setShadowY(player.getShadowY() + 7);
			player.setPlayerY(player.getPlayerY() + 7);
		}
	}

	////맞기
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{

	//	if (PtInRect(&player.getPlayerRect(), _ptMouse))
	//	{
	//		if (!player.getDirectionX())
	//		{
	//			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
	//			player.setState(player.getHitState());
	//		}
	//		if (player.getDirectionX())
	//		{
	//			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
	//			player.setState(player.getHitState());
	//		}
	//	}

	//}
	player.mouseCol();
}

HRESULT attackState::init()
{
	_diveCount = 0;
	return S_OK;
}

void attackState::update(player & player)
{
	_diveCount++;
	//기본공격
	if (!player.getAttacked())
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setAttacked(true);
		}
	}
	if (player.getIsAttack())
	{
		if (player.getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1") ||
			player.getAni() == KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1"))
		{
			if (!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1")->isPlay())
			{
				if (player.getRunCount() > 6)
				{
					player.setRunCount(0);
				}
				//키 누르면 어택 2로 넘거가게
				if (player.getAttacked())
				{
					player.setIsAttack(true);
					if (!player.getDirectionX())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_ATTACK2"), IMAGEMANAGER->findImage("PLAYER_ATTACK2"));
						player.setAttack(player.getPlayerX() - 60, player.getPlayerY(), 120, 130);
					}
					if (player.getDirectionX())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK2"), IMAGEMANAGER->findImage("PLAYER_ATTACK2"));
						player.setAttack(player.getPlayerX() + 60, player.getPlayerY(), 120, 130);
					}
					player.setAttacked(false);
				}
			}
		}
		if (player.getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK2") ||
			player.getAni() == KEYANIMANAGER->findAnimation("P_LEFT_ATTACK2"))
		{
			if (!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK2")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK2")->isPlay())
			{
				//키 누르면 어택 3으로 넘어가게
				if (player.getAttacked())
				{
					player.setIsAttack(true);
					if (!player.getDirectionX())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_ATTACK3"), IMAGEMANAGER->findImage("PLAYER_ATTACK3"));
						player.setAttack(player.getPlayerX() - 60, player.getPlayerY(), 140, 130);
					}
					if (player.getDirectionX())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK3"), IMAGEMANAGER->findImage("PLAYER_ATTACK3"));
						player.setAttack(player.getPlayerX() + 60, player.getPlayerY(), 140, 130);
					}
					player.setAttacked(false);
				}
			}
			
		}
	}

	//슬라이딩
	if (player.getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_DIVE"))
	{
		if (_diveCount < 30)
		{
			player.setShadowX(player.getShadowX() + 9);
		}
		if (_diveCount >= 30 && _diveCount < 35)
		{
			player.setShadowX(player.getShadowX() + 4);
		}
		player.setAttack(player.getPlayerX() + 60, player.getPlayerY() + 50, 120, 80);
	}
	if (player.getAni() == KEYANIMANAGER->findAnimation("P_LEFT_DIVE"))
	{
		if (_diveCount < 30)
		{
			player.setShadowX(player.getShadowX() - 9);
		}
		if (_diveCount >= 30 && _diveCount < 35)
		{
			player.setShadowX(player.getShadowX() - 4);
		}
		player.setAttack(player.getPlayerX() - 60, player.getPlayerY() + 50, 120, 80);
	}
	//회오리할떄 움직일 수 있게 하려면 이거 주석 풀면 돼
	/*if (player.getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_KICK"))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player.setShadowX(player.getShadowX() - 2);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player.setShadowX(player.getShadowX() + 2);
		}
	}*/

	//애니메이션 재생 안하면
	if (!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK2")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK2")->isPlay() && 
		!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK3")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK3")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_RIGHT_DIVE")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_DIVE")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_RIGHT_STOMP")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_STOMP")->isPlay() && 
		!KEYANIMANAGER->findAnimation("P_RIGHT_KICK")->isPlay()&&
		!KEYANIMANAGER->findAnimation("P_LEFT_STRONG_ATTACK")->isPlay() && !KEYANIMANAGER->findAnimation("P_RIGHT_STRONG_ATTACK")->isPlay())
	{
		player.setAttacked(false);
		//키 누르면 앞으로 걸어가게
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_diveCount = 0;
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(false);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_diveCount = 0;
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(true);
		}
		
		//키 암것도 안누르면 아이들로
		else
		{
			_diveCount = 0;
			if (!player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
				player.setDirectionX(false);
			}
			if (player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
				player.setDirectionX(true);
			}
		}
	}
	player.mouseCol();
} 

HRESULT hitState::init()
{
	_stunCount = 0;
	_hitCount = 0;
	_hitNum = 0;
	_isHit = false;
	return S_OK;
}

void hitState::update(player & player)
{
	_hitCount++;

	//맞기
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		if (PtInRect(&player.getPlayerRect(), _ptMouse))
		{
			_isHit = true;
			if (!player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				_hitCount = 0;
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_HIT"), IMAGEMANAGER->findImage("PLAYER_HIT"));
				_hitCount = 0;
			}
		}
	}
	//player.mouseCol();

	if (_isHit)
	{
		_hitNum++;
		_isHit = false;
	}

	if (_hitNum > 3)
	{
		//cout << "d" << endl;
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
			player.setState(player.getDownState());
			player.setDirectionX(false);
			_hitCount = 0;
			_hitNum = 0;
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_DOWN"), IMAGEMANAGER->findImage("PLAYER_DOWN"));
			player.setState(player.getDownState());
			player.setDirectionX(true);
			_hitCount = 0;
			_hitNum = 0;
		}
	}
	//cout << _hitNum << endl;
	if (_hitCount > 40)
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(false);
			_hitCount = 0;
			_hitNum = 0;
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(true);
			_hitCount = 0;
			_hitNum = 0;
		}
	}
	if (player.getPlayerHp() <= 0)
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_OVER"), IMAGEMANAGER->findImage("PLAYER_OVER"));
			player.setState(player.getOverState());
			player.setDirectionX(false);
			_hitCount = 0;
			_hitNum = 0;
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_OVER"), IMAGEMANAGER->findImage("PLAYER_OVER"));
			player.setState(player.getOverState());
			player.setDirectionX(true);
			_hitCount = 0;
			_hitNum = 0;
		}
	}
}

HRESULT downState::init()
{
	_downCount = 0;
	return S_OK;
}

void downState::update(player & player)
{
	_downCount++;
	//cout << _downCount << endl;
	if (player.getAni() == KEYANIMANAGER->findAnimation("P_LEFT_DOWN") || player.getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_DOWN"))
	{
		if (!KEYANIMANAGER->findAnimation("P_RIGHT_DOWN")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_DOWN")->isPlay())
		{
			if (_downCount > 180)
			{
				if (!player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_STAND_UP"), IMAGEMANAGER->findImage("PLAYER_STAND_UP"));
					player.setDirectionX(false);
				}
				if (player.getDirectionX())
				{
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_STAND_UP"), IMAGEMANAGER->findImage("PLAYER_STAND_UP"));
					player.setDirectionX(true);
				}
			}
		}
	}
	if (player.getAni() == KEYANIMANAGER->findAnimation("P_LEFT_STAND_UP") || player.getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_STAND_UP"))
	{
		if (!KEYANIMANAGER->findAnimation("P_LEFT_STAND_UP")->isPlay() && !KEYANIMANAGER->findAnimation("P_RIGHT_STAND_UP")->isPlay())
		{
			//키 누르면 앞으로 걸어가게
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_downCount = 0;
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
				player.setDirectionX(false);
			}
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_downCount = 0;
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
				player.setDirectionX(true);
			}

			//키 암것도 안누르면 아이들로
			else
			{
				_downCount = 0;
				if (!player.getDirectionX())
				{
					player.setIsJumping(false);
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
					player.setState(player.getIdleState());
					player.setDirectionX(false);
				}
				if (player.getDirectionX())
				{
					player.setIsJumping(false);
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
					player.setState(player.getIdleState());
					player.setDirectionX(true);
				}
			}
		}
	}
}

void startState::update(player & player)
{
	if (!KEYANIMANAGER->findAnimation("P_RIGHT_START")->isPlay())
	{
		//키 누르면 앞으로 걸어가게
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player.setIsJumping(false);
			player.setDirectionX(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(false);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player.setIsJumping(false);
			player.setDirectionX(true);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(true);
		}

		//키 암것도 안누르면 아이들로
		else
		{
			player.setIsJumping(false);
			player.setDirectionX(true);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(true);
		
		}
	}
}
void guardState::update(player & player)
{

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
		}
	}

	if (!KEYANIMANAGER->findAnimation("P_LEFT_GUARD")->isPlay() && !KEYANIMANAGER->findAnimation("P_RIGHT_GUARD")->isPlay())
	{
		//키 누르면 앞으로 걸어가게
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(false);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(true);
		}

		//키 암것도 안누르면 아이들로
		else
		{
			if (!player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
				player.setDirectionX(false);
			}
			if (player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
				player.setDirectionX(true);
			}
		}
	}
}

void overState::update(player & player)
{
	if (!player.getAni() == KEYANIMANAGER->findAnimation("P_RIGHT_OVER")->isPlay() && !player.getAni() == KEYANIMANAGER->findAnimation("P_LEFT_OVER")->isPlay())
	{
		if (!player.getDirectionX())
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(false);
			player.setPlayerHP(100);
		}
		if (player.getDirectionX())
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirectionX(true);
			player.setPlayerHP(100);
		}
	}
}

void stunState::update(player & player)
{
}

