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
			player.setJumpPower(7);
			player.setGravity(0.5f);
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

	//공격
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
			player.setJumpPower(7);
			player.setGravity(0.5f);
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
		if (KEYMANAGER->isStayKeyDown('Z'))
		{
			//player.setJumpPower(player.getJumpPower() + 1);
			player.setIsRun(true);
			player.setJumpPower(7);
			player.setGravity(0.5f);
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

}



void jumpState::update(player & player)
{
	//점프 올리기
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (player.getJumpPower() < 15)
		{
			player.setJumpPower(player.getJumpPower() + 0.5f);
			//cout << player.getJumpPower() << endl;
		}
	}
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
	if (player.getJumpPower() < 0)
	{
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			}
			
		}
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
			}
		}
		
	}
	

	if (player.getPlayerY() >= player.getShadowY() - 110)
	{
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
			}
			else if (player.getDirectionX())
			{
				player.setIsJumping(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
				player.setState(player.getRunState());
				player.setDirectionX(true);
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

}

void attackState::update(player & player)
{
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
	//애니메이션 재생 안하면
	if (!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK2")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK2")->isPlay() && 
		!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK3")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK3")->isPlay() )
	{
		player.setAttacked(false);
		//아무키도 안누르면 아이들로
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
		//키 누르면 앞으로 걸어가게
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(false);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
			player.setDirectionX(true);
		}
	}

} 

void hitState::update(player & player)
{

}