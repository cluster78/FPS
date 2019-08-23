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
	rt.x = (float)(_x * TileSize);			//5_ �����ڿ��� rt������ ����.
	rt.y = (float)(_y * TileSize);
	rt.w = TileSize;
	rt.h = TileSize;

}
Object::~Object() { 
	
	m_pNowAni = nullptr;
	m_refMap = nullptr;		//2_�Ҹ��ڿ��� �ʵ����� ���� �߰�. 3_�ش� ���� ��ġ ����.	6_�ٽ� ����
}	

//void Object::Render() { }
void Object::Init() {}

bool Object::CanMove() const { return false; }
bool Object::Explosived() { return false; }
bool Object::Interaction(class Player* a_refHero) { return false; }
void Object::_PreUpdate(float a_fDelta) {}
bool Object::_Update(float a_fDelta) { return false; }

void Object::SetMap(char** a_refMap)			//5_ cpp�� �����߰�.
{
	assert(a_refMap != nullptr);
	m_refMap = a_refMap;
}

bool Object::Update(float a_fDelta)				//5_ _PreUpdate�� _Update�� fps ����
{
	_PreUpdate(a_fDelta);
	return _Update(a_fDelta);
}

Rect Object::GetRendertRect() const
{
	return rt;
}

void Object::RenderClear()							//5_���� ���� �Լ� �߰�.
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

void Object::Render()					//3_�� ���� �Լ� �߰�.
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