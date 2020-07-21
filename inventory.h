#pragma once
#include "gameNode.h"
#include <vector>

class inventory : public gameNode
{
private:
	image		_inImage;				//������ �̹���
	string		_inItemName;			//������ �̸�
	string		_inItemDiscription;		//������ ����
	int		_inHpPortion;				//HP ���� ��ġ
	int		_inPowerPortion;			//���ݷ� ���� ��ġ

public:
	inventory();
	~inventory();

	virtual HRESULT init();
	virtual void release();
	virtual void updatea();
	virtual void render();

	string getInItemName() { return _inItemName; }											//������ �̸� �Ѱ��ֱ�
	void setInItemName(string name) { _inItemName = name; }									//������ �̸� ����
	string getInItemDiscription() { return _inItemDiscription; }							//������ ���� �Ѱ��ֱ�
	void setInItemDiscription(string discription) { _inItemDiscription = discription; }		//������ ���� ����
	int getInHpPortion() { return  _inHpPortion; }											//HP ������ �Ѱ��ֱ�
	void setInHpPortion(int hp) { _inHpPortion = hp; }										//HP ������ ����
	int getInPowerPortion() { return _inPowerPortion; }										//POWER ������ �Ѱ��ֱ�
	void setInPowerPortion(int power) { _inPowerPortion = power; }							//POWER ������ ����
};


