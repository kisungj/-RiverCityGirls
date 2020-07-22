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
	string		_itemName;			//������ �̸�
	string		_itemDiscription;	//������ ����

	float _x, _y;					//������ ��ġ��
	float _gravity;					//������ �������� �߷°�

	int _hpPortion;					//HP ������
	int _powerPortion;				//���ݷ� ������

	bool _gravityBool;				//������ �������� �Ұ�

public:
	Item();
	~Item();

	virtual HRESULT init(ITEMSTATE itemstate);
	virtual HRESULT init(ITEMSTATE itemstate, POINT position);
	virtual void update();
	virtual void release();
	virtual void render();

	void move();											 //������ ����� ��������

	image* getItemImage() { return _itemImg; }
	RECT getItemRc() { return _itemRc; }					 //������ ��Ʈ�� �ѱ��
	ITEMSTATE getitemstate() { return _itemState; }			 //������ enum�� �ѱ��
	string getItemName() { return _itemName; }				 //������ �̸��� �ѱ��
	string getItemDiscription() { return _itemDiscription; } //������ ���� �ѱ��
	int getHpPortion() { return _hpPortion; }				 //HP���� �� �ѱ��
	int getPowerPortion() { return _powerPortion; }			 //�Ŀ����� �� �ѱ��

};