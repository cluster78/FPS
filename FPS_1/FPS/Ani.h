#pragma once

class Ani					//3_�ִ� Ŭ���� �߰�.
{
public:
	Ani() = default;
	virtual ~Ani();

	void Resize(int a_nAniTypeCount);				//3_���� ������ �����Լ�
	void Add(int a_nAniType, const RenderTile& tile);		//3_������ �߰��Լ�	5_����Ÿ�� �����Ϳ��� ���۷����� ����.
	void Add(int a_nAniType, const std::initializer_list<RenderTile>& tiles);	//5_Add�Լ� initializer_list�� ���ڰ����� �޴°� �߰�.

	void SetState(int a_nAni, int a_nFrame = 0);	//3_������ ���� �����Լ�
	void NextCut();									//5_���� �ִϸ��̼��� Ȯ���Լ��߰�.

	void Update(float a_fDeltaTime);				//5_������Ʈ �Լ� �߰�.
	RenderTile* Get();

	std::vector<std::vector<RenderTile>> m_vcAni;	//RenderTile�� ������ ����.
	std::vector<RenderTile>* m_pCurrentAni = nullptr;

	int m_nAniType = 0;
	int m_nNowMaxCut = 0;		//5_Frame -> Cut ���� ��� ����.
	//int m_nFrame = 0;
	int m_nCut = 0;				//5_Frame -> Cut ���� ��� ����.
	float m_fNowTile = 0;		//5_���� Ÿ�� ���� �߰�.

	inline static const float a_fCutTime = 0.2f;	//5_���ƴ� �����ð� ���� �߰�.
};

