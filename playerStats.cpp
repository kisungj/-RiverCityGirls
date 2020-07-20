#include "stdafx.h"
#include "player.h"

void idleState::update(player & player)
{
	if (player.getIsMove())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			//player.setY(player.getY() + 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getMoveState());
			player.setDirection(false);
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			//player.setY(player.getY() + 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getMoveState());
			player.setDirection(true);
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			player.setIsUp(true);
			if (player.getDirection())
			{
				//player.setY(player.getY() + 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getMoveState());
			}
			if (!player.getDirection())
			{
				//player.setY(player.getY() + 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getMoveState());
			}
		}


		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			player.setIsUp(false);
			if (WINSIZEY > player.getShadowY() - 100)
			{
				if (player.getDirection())
				{
					//player.setY(player.getY() + 5);
					player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
					player.setState(player.getMoveState());
				}
				if (!player.getDirection())
				{
					//player.setY(player.getY() + 5);
					player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
					player.setState(player.getMoveState());
				}
			}
		}
	}
	if (!player.getIsJumping())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			player.setJumpPower(15);
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

		//����
		if (!player.getDirection())
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				/*if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
				{
					player.setState(player.getMoveState());
					player.setDirection(true);
					return;
				}*/
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
				}

				player.setShadowX(player.getShadowX() - 3);
			}
		}

		//������
		if (player.getDirection())
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				/*if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
				{
					player.setState(player.getMoveState());
					player.setDirection(false);
					return;
				}*/
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
				}

				player.setShadowX(player.getShadowX() + 3);
			}
		}

		//����
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && KEYMANAGER->getKeyUp() == NULL)
		{
			//cout << " ���� ���̵�� ���ư� " << endl;
			//player.setY(player.getY() - 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirection(false);
		}
		//������
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && KEYMANAGER->getKeyUp() == NULL)
		{
			//cout << " ������ ���̵�� ���ư� " << endl;
			//player.setY(player.getY() - 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
			player.setState(player.getIdleState());
			player.setDirection(true);
		}
		//��
		if (player.getIsUp())
		{
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
				{
					if (!player.getDirection())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
					}
					if (player.getDirection())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
					}
				}
				else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					return;
				}
				player.setShadowY(player.getShadowY() - 3);
			}
		}

		//�Ʒ�
		if (!player.getIsUp())
		{
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_UP))
				{
					if (!player.getDirection())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
					}
					if (player.getDirection())
					{
						player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_IDLE"), IMAGEMANAGER->findImage("PLAYER_IDLE"));
					}
				}
				else if (KEYMANAGER->isStayKeyDown(VK_UP))
				{
					return;
				}
				player.setShadowY(player.getShadowY() + 3);
			}
		}
		//��
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
		//�Ʒ�
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

	//����
	if (!player.getIsJumping())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			player.setJumpPower(15);
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


	if (player.getJumpPower() < 0)
	{
		if (player.getDirection())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
		}
		if (!player.getDirection())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_FALL"), IMAGEMANAGER->findImage("PLAYER_JUMP"));
		}
	}

	if (player.getPlayerY() >= player.getShadowY() - 110)
	{
		if (KEYMANAGER->getKeyUp() == NULL)
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
				player.setDirection(true);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getMoveState());
			player.setDirection(false);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			player.setIsJumping(false);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getMoveState());
			player.setDirection(true);
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

void attackState::update(player & player)
{

}

void hitState::update(player & player)
{

}