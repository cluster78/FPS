#include "pch.h"
#include "Object.h"

RenderTile Object::Empty = RenderTile{		//5_Empty�� ������ ������ �ʱ�ȭ
	{"     "},
	{"     "},
	{"     "},
	{"     "},
	{"     "},
};

Object::Object(int _x, int _y) : x(_x), y(_y)
{ 
	rt.x = _x * TileSize;			//5_ �����ڿ��� rt������ ����.
	rt.y = _y * TileSize;
	rt.w = TileSize;
	rt.h = TileSize;

}
Object::~Object() { /*m_refMap = nullptr;*/ }	//2_�Ҹ��ڿ��� �ʵ����� ���� �߰�. 3_�ش� ���� ��ġ ����.

//void Object::Render() { }
void Object::Init() {}

void Object::Explosived(class Bomb* a_refBomb) { }
void Object::Interaction(class Hero* a_refHero) { }
void Object::_PreUpdate(float a_fDelta) {}
void Object::_Update(float a_fDelta) {}

void Object::SetMap(char** a_refMap)			//5_ cpp�� �����߰�.
{
	assert(a_refMap != nullptr);
	m_refMap = a_refMap;
}

void Object::Update(float a_fDelta)				//5_ _PreUpdate�� _Update�� fps ����
{
	_PreUpdate(a_fDelta);
	_Update(a_fDelta);
}

Rect Object::GetRendertRect() const
{
	return rt;
}

void Object::Clear()							//5_���� ���� �Լ� �߰�.
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

void Object::Render()					//3_�� ���� �Լ� �߰�.
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