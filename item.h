#pragma once
#include "gameNode.h"

enum ITEMSTATE
{
	HP,
	POWER,
	GOLD,
	SILVER
};

class Item : public gameNode
{
private:
	image*		_itemImg;			//������ �̹���
	ITEMSTATE	_itemState;			//������ enum��
	RECT		_itemRc;			//������ ��Ʈ
	string		_name;				//������ �̸�
	string		_discription;		//������ ����

	float _x, _y;					//������ ��ġ��
	float _gravity;					//������ �������� �߷°�

	float _hpAmount;				//HP ������
	float _attackAmount;			//���ݷ� ������

	bool _gravityBool;				//������ �������� �Ұ�

public:
	Item();
	~Item();

	virtual HRESULT init(ITEMSTATE itemstate, POINT position);
	virtual void update();
	virtual void release();
	virtual void render();

	void move();											//������ ����� ��������

	RECT getItemRc() { return _itemRc; }					//������ ��Ʈ�� �ѱ��
	ITEMSTATE getitemstate() { return _itemState; }			//������ enum�� �ѱ��
};