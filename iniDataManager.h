#pragma once
#include "singletonBase.h"
#include <vector>

using namespace std;

struct tagIniData
{
	const char* subject; //�׸�
	const char* title;	 //����
	const char* body;	 //��
};

class iniDataManager : public singletonBase <iniDataManager>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;

	typedef vector<arrIniData> arrIniDatas;
	typedef vector<arrIniData>::iterator arrIniDatasIter;


private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);

	//���� �Լ�
	void addData(const char* subject, const char* title, const char* body);
	void iniSave(const char* fileName);

	//�ε�(�б�)�Լ�
	//���Ͽ��� ���ڿ� �������� �Լ�
	string loadDataString(const char* fileName, const char* subject, const char* title);
	//���Ͽ��� ���� �������� �Լ�
	int loadDataInteger(const char* fileName, const char* subject, const char* title);

	iniDataManager();
	~iniDataManager();
};

