#include "pch.h"
#include "Object.h"

RenderTile Object::Empty = RenderTile{		//5_Empty를 삭제용 변수로 초기화
	{"     "},
	{"     "},
	{"     "},
	{"     "},
	{"     "},
};

Object::Object(int _x, int _y) : x(_x), y(_y)
{ 
	rt.x = (float)(_x * TileSize);			//5_ 생성자에서 rt변수들 셋팅.
	rt.y = (float)(_y * TileSize);
	rt.w = TileSize;
	rt.h = TileSize;

}
Object::~Object() { 
	
	m_pNowAni = nullptr;
	m_refMap = nullptr;		//2_소멸자에서 맵데이터 삭제 추가. 3_해당 구문 위치 변경.	6_다시 복귀
}	

//void Object::Render() { }
void Object::Init() {}

bool Object::CanMove() const { return false; }
bool Object::Explosived() { return false; }
bool Object::Interaction(class Player* a_refHero) { return false; }
void Object::_PreUpdate(float a_fDelta) {}
bool Object::_Update(float a_fDelta) { return false; }

void Object::SetMap(char** a_refMap)			//5_ cpp에 정의추가.
{
	assert(a_refMap != nullptr);
	m_refMap = a_refMap;
}

bool Object::Update(float a_fDelta)				//5_ _PreUpdate와 _Update에 fps 전달
{
	_PreUpdate(a_fDelta);
	return _Update(a_fDelta);
}

Rect Object::GetRendertRect() const
{
	return rt;
}

void Object::RenderClear()							//5_렌더 삭제 함수 추가.
{
	Rect rt = GetRendertRect();
	int nX = (int)rt.x;
	int nY = (int)rt.y;

	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			Empty[i], TileSize * sizeof(char));
	}
}

void Object::Render()					//3_맵 랜더 함수 추가.
{
	Rect rt = GetRendertRect();
	int nX = (int)rt.x;
	int nY = (int)rt.y;

	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			(*m_pNowAni)[i], TileSize * sizeof(char));
	}
}