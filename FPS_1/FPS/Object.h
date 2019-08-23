#pragma once

class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;
	virtual bool CanMove() const;

	bool Update(float a_fDelta);
	void Render();									//3_랜더 추가
	void SetMap(char** a_refMap);							//2_맵데이터 셋팅함수 추가. 3_소멸자에 있던 구문 여기로 위치 변경.	5_인라인 삭제
	void RenderClear();

	virtual void Init();									//2_폭탄이랑 히어로 관련부분 추가.
	virtual bool Explosived();
	virtual bool Interaction(class Player* a_refHero);		//6_bool로 변경하여 리턴값생성.

	inline void SetPos(int _x, int _y) { x = _x; y = _y; rt.x = _x; rt.y = _y; }	//2_이동 함수추가.
	inline bool IsCross(const Object& a_refObj)				//6_겹침 검사함수
	{
		return rt.IsCross(a_refObj.rt);
	}
	inline bool IsCross(Object* a_refObj)
	{
		assert((a_refObj != nullptr) && " arg error");
		return IsCross(*a_refObj);
	}
	virtual Rect GetRendertRect() const;					//5_외형 가져오는함수 추가.

	//virtual void Render();								2_렌더 제거. 오브젝트라 그닥 필요없어서 삭제하신듯.

protected:
	//void Clear();			6_렌더클리어로 명칭 변경.
	virtual void _PreUpdate(float a_fDelta);				//5_이전단계의 글자 지우는 함수 추가.
	virtual bool _Update(float a_fDelta);					//6_void에서 bool값으로 변경.

public:
	int x;							
	int y;
	Rect rt;												//5_실제 찍히는 위치 변수로 저장.

protected:													//3_private -> protected 로 변경.
	static RenderTile Empty;								//5_Empty변수 추가
	char** m_refMap = nullptr;								//2_맵 데이터 받아옴.
	RenderTile*	m_pNowAni = nullptr;						//3_NowAni변수 추가.
};
