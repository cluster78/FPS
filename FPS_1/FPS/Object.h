#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	virtual void Init();							//2_폭탄이랑 히어로 관련부분 추가.
	virtual void Update(float a_fDelta);
	virtual void Render();							//3_랜더 추가
	virtual void Explosived(class Bomb* a_refBomb);
	virtual void Interaction(class Hero* a_refHero);

	inline void SetPos(int _x, int _y) { x = _x; y = _y; }	//2_이동 함수추가.
	inline void SetMap(char** a_refMap) { assert(a_refMap != nullptr);m_refMap = a_refMap;  }	//2_맵데이터 셋팅함수 추가. 3_소멸자에 있던 구문 여기로 위치 변경.


	//virtual void Render();				2_렌더 제거. 오브젝트라 그닥 필요없어서 삭제하신듯.

public:
	int x;							
	int y;

protected:		//3_private -> protected 로 변경.
	char** m_refMap = nullptr;		//2_맵 데이터 받아옴.
	RenderTile*	m_pNowAni = nullptr;	//3_NowAni변수 추가.
};
