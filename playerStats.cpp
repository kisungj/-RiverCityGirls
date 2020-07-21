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

	//����
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
		player.setState(player.getWalkState());
		player.setDirectionX(false);
	}
	//������
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
		player.setState(player.getWalkState());
		player.setDirectionX(true);
	}
	//��
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		player.setDirectionY(true);
		//�������̶��
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
		}
		//�����̶��
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_WALK"), IMAGEMANAGER->findImage("PLAYER_WALK"));
			player.setState(player.getWalkState());
		}
	}

	//�Ʒ�
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
	//����
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

	//�⺻����
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
	//���
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
	//ȸ����ű
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_KICK"), IMAGEMANAGER->findImage("PLAYER_KICK"));
		player.setState(player.getAttackState());
		player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
	}

	//����
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getInvinState());
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getInvinState());
		}
	}
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
				player.setState(player.getWalkState());
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

	//����
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

	//������
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
	//�⺻ ����
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

	//���
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

	//ȸ����ű
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_KICK"), IMAGEMANAGER->findImage("PLAYER_KICK"));
		player.setState(player.getAttackState());
		player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
	}
}


void runState::update(player & player)
{
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
			player.setState(player.getWalkState());
			player.setDirectionX(true);
		}
	}

	//������
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
				player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
			}
			if (player.getDirectionX())
			{
				player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_RUN"), IMAGEMANAGER->findImage("PLAYER_RUN"));
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
	

	//����
	if (!player.getIsJumping())
	{
		if (KEYMANAGER->isStayKeyDown('Z'))
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

	//�⺻����
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

	//�����̵�
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

	//ȸ����ű
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_KICK"), IMAGEMANAGER->findImage("PLAYER_KICK"));
		player.setState(player.getAttackState());
		player.setAttack(player.getPlayerX(), player.getPlayerY() + 100, 120, 20);
	}
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
	//���� �ø���
	if (_jumpCount < 25)
	{
		_isJump = true;
	}
	else _isJump = false;
	
	cout << _isJump << endl;

	if (player.getIsJumping())
	{
		player.setPlayerY(player.getPlayerY() - player.getJumpPower());
		player.setJumpPower(player.getJumpPower() - player.getGravity());
		player.setGravity(player.getGravity());
		//�������� ��ġ �ٲٸ� �ٲ��
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

	//���� ���� �ִ� ���¸� �������� �ڼ��� �ٲ��
	if (player.getJumpPower() < 0 && !_isJump)
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
	if (_isJump)
	{
		if (KEYMANAGER->isStayKeyDown('Z'))
		{
			player.setJumpPower(player.getJumpPower() + 0.8f);
		}
	}
	

	if (player.getPlayerY() >= player.getShadowY() - 110)
	{
		_jumpCount = 0;
		//�ƹ��͵� �ȴ����� ���̵��
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
		//�������̸� ������ ����
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
		//�ƴ� �ȱ�
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
	//������ �ƴϸ� �ɾ�� �ӵ�����
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
	//�������̸� �ӵ�����
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

HRESULT attackState::init()
{
	_diveCount = 0;
	return S_OK;
}

void attackState::update(player & player)
{
	_diveCount++;
	//�⺻����
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
				//Ű ������ ���� 2�� �ѰŰ���
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
				//Ű ������ ���� 3���� �Ѿ��
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

	//�����̵�
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
	//ȸ�����ҋ� ������ �� �ְ� �Ϸ��� �̰� �ּ� Ǯ�� ��
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

	//�ִϸ��̼� ��� ���ϸ�
	if (!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK1")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK1")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK2")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK2")->isPlay() && 
		!KEYANIMANAGER->findAnimation("P_RIGHT_ATTACK3")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_ATTACK3")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_RIGHT_DIVE")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_DIVE")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_RIGHT_STOMP")->isPlay() && !KEYANIMANAGER->findAnimation("P_LEFT_STOMP")->isPlay() && 
		!KEYANIMANAGER->findAnimation("P_RIGHT_KICK")->isPlay())
	{
		player.setAttacked(false);
		//Ű ������ ������ �ɾ��
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
		
		//Ű �ϰ͵� �ȴ����� ���̵��
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

} 

void hitState::update(player & player)
{

}

void invinState::update(player & player)
{
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if (!player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_LEFT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getInvinState());
		}
		if (player.getDirectionX())
		{
			player.setAni(KEYANIMANAGER->findAnimation("P_RIGHT_GUARD"), IMAGEMANAGER->findImage("PLAYER_GUARD"));
			player.setState(player.getInvinState());
		}
	}

	if (!KEYANIMANAGER->findAnimation("P_RIGHT_START")->isPlay() &&
		!KEYANIMANAGER->findAnimation("P_LEFT_GUARD")->isPlay() && !KEYANIMANAGER->findAnimation("P_RIGHT_GUARD")->isPlay())
	{
		//Ű ������ ������ �ɾ��
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

		//Ű �ϰ͵� �ȴ����� ���̵��
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