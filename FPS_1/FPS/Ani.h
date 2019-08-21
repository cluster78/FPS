#pragma once

class Ani					//3_�ִ� Ŭ���� �߰�.
{
public:
	Ani();
	virtual ~Ani();

	void Resize(int a_nAniTypeCount);				//3_���� ������ �����Լ�
	void Add(int a_nAniType, RenderTile* tile);		//3_������ �߰��Լ�
	void SetState(int a_nAni, int a_nFrame = 0);	//3_������ ���� �����Լ�
	RenderTile* Get();

	std::vector<std::vector<RenderTile*>> m_vcAni;
	std::vector<RenderTile*>* m_pCurrentAni = nullptr;

	int m_nAniType = 0;
	int m_nNowMaxFrame = 0;
	int m_nFrame = 0;
};

