#include "pch.h"
#include "Object.h"

Object::Object(int _x, int _y) : x(_x), y(_y) { }
Object::~Object() { /*m_refMap = nullptr;*/ }	//2_소멸자에서 맵데이터 삭제 추가. 3_해당 구문 위치 변경.

//void Object::Render() { }
void Object::Init() {}
void Object::Update(float a_fDelta) { }
void Object::Render()					//3_맵 랜더 함수 추가.
{
	int nX = x * TileSize;
	int nY = y * TileSize;

	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			m_pNowAni[i], TileSize * sizeof(char));
	}
}
void Object::Explosived(class Bomb* a_refBomb) { }
void Object::Interaction(class Hero* a_refHero) { }
