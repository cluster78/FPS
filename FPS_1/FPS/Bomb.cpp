#include "pch.h"
#include "Bomb.h"

#include "GameManager.h"

Bomb::Bomb(int x, int y) : Object(x, y) 
	, m_Data{
		{ '1', '1', '1', '1', '1' },
		{ '1', 'B', 'B', 'B', '1' },
		{ '1', 'B', 'B', 'B', '1' },
		{ '1', 'B', 'B', 'B', '1' },
		{ '1', '1', '1', '1', '1' },
	}
{
	m_pNowAni = &m_Data;
}

Bomb::~Bomb() { }

eObjectType Bomb::GetObjectType() const
{
	return eObjectType::Bomb;
}

void Bomb::Init()		//2_폭탄 불려올때 작동.
{
	GameMng()->GetBombData(this);		//2_폭탄 데이터 게임매니져에 전달.
}

void Bomb::Update(float a_fDelta)		//2_시간받아와서 정해진 시간마다 작동하는거.
{
	m_fLifeTime -= a_fDelta;

	if (m_fLifeTime <= 0.0f)
	{
		//Bomb!
	}
}

void Bomb::Render()
{

}

void Bomb::Explosived(Bomb* a_refBomb)
{
	if (a_refBomb == this) { return; }
	// Bomb!
}
