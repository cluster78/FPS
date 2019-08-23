#pragma once

class Ani					//3_애니 클래스 추가.
{
public:
	Ani() = default;
	virtual ~Ani();

	void Resize(int a_nAniTypeCount);				//3_랜더 사이즈 조정함수
	void Add(int a_nAniType, const RenderTile& tile);		//3_랜더값 추가함수	5_랜더타일 포인터에서 레퍼런스로 변경.
	void Add(int a_nAniType, const std::initializer_list<RenderTile>& tiles);	//5_Add함수 initializer_list를 인자값으로 받는거 추가.

	void SetState(int a_nAni, int a_nFrame = 0);	//3_랜더의 상태 설정함수
	void NextCut();									//5_다음 애니매이션컷 확인함수추가.

	void Update(float a_fDeltaTime);				//5_업데이트 함수 추가.
	RenderTile* Get();

	std::vector<std::vector<RenderTile>> m_vcAni;	//RenderTile에 포인터 없앰.
	std::vector<RenderTile>* m_pCurrentAni = nullptr;

	int m_nAniType = 0;
	int m_nNowMaxCut = 0;		//5_Frame -> Cut 으로 용어 변경.
	//int m_nFrame = 0;
	int m_nCut = 0;				//5_Frame -> Cut 으로 용어 변경.
	float m_fNowTile = 0;		//5_현재 타일 변수 추가.

	inline static const float a_fCutTime = 0.2f;	//5_한컷당 유지시간 변수 추가.
};

