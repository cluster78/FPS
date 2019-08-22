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
	rt.x = _x * TileSize;			//5_ 생성자에서 rt변수들 셋팅.
	rt.y = _y * TileSize;
	rt.w = TileSize;
	rt.h = TileSize;

}
Object::~Object() { /*m_refMap = nullptr;*/ }	//2_소멸자에서 맵데이터 삭제 추가. 3_해당 구문 위치 변경.

//void Object::Render() { }
void Object::Init() {}

void Object::Explosived(class Bomb* a_refBomb) { }
void Object::Interaction(class Hero* a_refHero) { }
void Object::_PreUpdate(float a_fDelta) {}
void Object::_Update(float a_fDelta) {}

void Object::SetMap(char** a_refMap)			//5_ cpp에 정의추가.
{
	assert(a_refMap != nullptr);
	m_refMap = a_refMap;
}

void Object::Update(float a_fDelta)				//5_ _PreUpdate와 _Update에 fps 전달
{
	_PreUpdate(a_fDelta);
	_Update(a_fDelta);
}

Rect Object::GetRendertRect() const
{
	return rt;
}

void Object::Clear()							//5_렌더 삭제 함수 추가.
{
	Rect rt = GetRendertRect();
	int nX = rt.x;
	int nY = rt.y;

	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			Empty[i], TileSize * sizeof(char));
	}
}

void Object::Render()					//3_맵 랜더 함수 추가.
{
	int nX = x * TileSize;
	int nY = y * TileSize;

	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			(*m_pNowAni)[i], TileSize * sizeof(char));
	}
}