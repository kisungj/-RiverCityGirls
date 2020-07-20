#include "stdafx.h"
#include "player.h"

void idleState::update(player & player)
{
	if (player.getRunCount() < 20 && player.getRunCount() > 0)
	{
		if (!player.getDirectionX())
		{
		//cout << "����" << endl;
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
				player.setState(player.getRunState());
				cout << "����" << endl;
				player.setRunCount(0);
			}

		}
		if (player.getDirectionX())
		{
			//cout << "����" << endl;
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
				player.setState(player.getRunState());
				cout << "����" << endl;
				player.setRunCount(0);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		//player.setY(player.getY() + 5);
		player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
		player.setState(player.getWalkState());
		player.setDirectionX(false);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		//player.setY(player.getY() + 5);
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
		player.setState(player.getWalkState());
		player.setDirectionX(true);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player.setDirectionY(true);
		//�������̶��
		if (player.getDirectionX())
		{
			//player.setY(player.getY() + 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
		}
		//�����̶��
		if (!player.getDirectionX())
		{
			//player.setY(player.getY() + 5);
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
		}
	}


	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		player.setDirectionY(false);
		if (WINSIZEY > player.getShadowY() - 100)
		{
			if (player.getDirectionX())
			{
				//player.setY(player.getY() + 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
			}
			if (!player.getDirectionX())
			{
				//player.setY(player.getY() + 5);
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
				player.setState(player.getWalkState());
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
	//run
}

void walkState::update(player & player)
{
	player.setRunCount(player.getRunCount() + 1);
	//����
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
			}
			if (player.getIsLeft())
			{
				player.setShadowX(player.getShadowX() - 3);
			}
		}
	}

	//������
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
			/*if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				player.setState(player.getWalkState());
				player.setDirectionX(false);
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

			if (player.getIsRight())
			{
				player.setShadowX(player.getShadowX() + 3);
			}
		}
	}

	//����
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
			player.setDirectionX(true);
		}
	}

	//������
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		//cout << " ������ ���̵�� ���ư� " << endl;
		//player.setY(player.getY() - 5);
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
			player.setDirectionX(false);
		}
	}
	

	//��
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
		//�Ʒ�
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
	
	//��
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
	//�Ʒ�
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
				//player.setY(player.getY() - 5);
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
	

	//����
	if (!player.getIsJumping())
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			player.setJumpPower(15);
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


void runState::update(player & player)
{
	cout << "���´�" << endl;
	//����
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

	//������
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
			/*if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				player.setState(player.getWalkState());
				player.setDirectionX(false);
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
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}

			if (player.getIsRight())
			{
				player.setShadowX(player.getShadowX() + 7);
			}
		}
	}

	//����
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
			player.setDirectionX(true);
		}
	}

	//������
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		//cout << " ������ ���̵�� ���ư� " << endl;
		//player.setY(player.getY() - 5);
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
			player.setDirectionX(false);
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

void attackState::update(player & player)
{

}

void hitState::update(player & player)
{

}