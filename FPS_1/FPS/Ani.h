#pragma once

class Ani					//3_애니 클래스 추가.
{
public:
	Ani();
	virtual ~Ani();

	void Resize(int a_nAniTypeCount);				//3_랜더 사이즈 조정함수
	void Add(int a_nAniType, RenderTile* tile);		//3_랜더값 추가함수
	void SetState(int a_nAni, int a_nFrame = 0);	//3_랜더의 상태 설정함수
	RenderTile* Get();

	std::vector<std::vector<RenderTile*>> m_vcAni;
	std::vector<RenderTile*>* m_pCurrentAni = nullptr;

	int m_nAniType = 0;
	int m_nNowMaxFrame = 0;
	int m_nFrame = 0;
};

