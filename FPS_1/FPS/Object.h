#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	virtual void Init();							//2_폭탄이랑 히어로 관련부분 추가.
	virtual void Update(float a_fDelta);
	virtual void Explosived(class Bomb* a_refBomb);		
	virtual void Interaction(class Hero* a_refHero);	//오브젝트 상호작용 함수

	inline void SetPos(int _x, int _y) { x = _x; y = _y; }	//2_이동 함수추가.
	inline void SetMap(char** a_refMap) { assert(a_refMap != nullptr); }	//2_맵데이터 셋팅함수 추가.


	//virtual void Render();				2_렌더 제거. 오브젝트라 그닥 필요없어서 삭제하신듯.

public:
	int x;							
	int y;

private:
	char** m_refMap = nullptr;		//2_맵 데이터 받아옴.
};
