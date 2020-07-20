#include "stdafx.h"
#include "player.h"

void idleState::update(player & player)
{
	if (player.getIsMove())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//player.setY(player.getY() + 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getMoveState());
			player.setDirection(false);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			//player.setY(player.getY() + 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getMoveState());
			player.setDirection(true);
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (!player.getDirection())
			{
				//player.setY(player.getY() + 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getMoveState());
			}
			if (player.getDirection())
			{
				//player.setY(player.getY() + 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getMoveState());
			}
		}


		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (WINSIZEY > player.getShadowY() - 100)
			{
				if (!player.getDirection())
				{
					//player.setY(player.getY() + 5);
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
					player.setState(player.getMoveState());
				}
				if (player.getDirection())
				{
					//player.setY(player.getY() + 5);
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
					player.setState(player.getMoveState());
				}
			}
		}
	}
	if (!player.getIsJumping())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			player.setJumpPower(10);
			player.setGravity(0.5f);
			player.setIsJumping(true);
			if (!player.getDirection())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());

			}
			if (player.getDirection())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());
			}
		}
	}

}

void moveState::update(player & player)
{
	if (player.getIsMove())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			player.setShadowX(player.getShadowX() - 3);
			player.setDirection(false);
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				player.setIsMove(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setDirection(false);
			}
		}
		cout << player.getIsMove() << endl;
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			player.setShadowX(player.getShadowX() + 3);
			player.setDirection(true);
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				player.setIsMove(false);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setDirection(true);

			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && KEYMANAGER->getKeyUp() == NULL)
		{
			//cout << " 왼쪽 아이들로 돌아감 " << endl;
			//player.setY(player.getY() - 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirection(false);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && KEYMANAGER->getKeyUp() == NULL)
		{
			//cout << " 오른쪽 아이들로 돌아감 " << endl;
			//player.setY(player.getY() - 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirection(true);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player.setShadowY(player.getShadowY() - 3);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player.setShadowY(player.getShadowY() + 3);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP) && KEYMANAGER->getKeyUp() == NULL)
		{
			if (!player.getDirection())
			{
				//player.setY(player.getY() - 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
			if (player.getDirection())
			{
				//player.setY(player.getY() - 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && KEYMANAGER->getKeyUp() == NULL)
		{
			if (!player.getDirection())
			{
				//player.setY(player.getY() - 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
			if (player.getDirection())
			{
				//player.setY(player.getY() - 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
				player.setState(player.getIdleState());
			}
		}
	}

	if (!player.getIsJumping())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			player.setJumpPower(10);
			player.setGravity(0.5f);
			player.setIsJumping(true);
			if (!player.getDirection())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());

			}
			if (player.getDirection())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_JUMP"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
				player.setState(player.getJumpState());
			}
		}
	}

}



void jumpState::update(player & player)
{
	if (player.getIsJumping())
	{
		player.setPlayerY(player.getPlayerY() - player.getJumpPower());
		player.setJumpPower(player.getJumpPower() - player.getGravity());
		player.setGravity(player.getGravity());
	}


	if (player.getPlayerY() >= player.getShadowY() - 110)
	{
		if (!player.getDirection())
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirection(false);
		}
		if (player.getDirection())
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirection(false);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player.setShadowX(player.getShadowX() - 3);
		player.setPlayerX(player.getPlayerX() - 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player.setShadowX(player.getShadowX() + 3);
		player.setPlayerX(player.getPlayerX() + 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player.setShadowY(player.getShadowY() - 3);
		player.setPlayerY(player.getPlayerY() - 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player.setShadowY(player.getShadowY() + 3);
		player.setPlayerY(player.getPlayerY() + 3);
	}


}

