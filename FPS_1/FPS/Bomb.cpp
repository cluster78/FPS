#include "pch.h"
#include "Bomb.h"

#include "GameManager.h"


Bomb::Bomb(int x, int y) : Object(x, y) {}
Bomb::~Bomb() {}

eObjectType Bomb::GetObjectType() const
{
	return eObjectType::Bomb;
}

void Bomb::Init()		//2_��ź �ҷ��ö� �۵�.
{
	GameMng()->GetBombData(this);		//2_��ź ������ ���ӸŴ����� ����.
}

void Bomb::Update(float a_fDelta)		//2_�ð��޾ƿͼ� ������ �ð����� �۵��ϴ°�.
{
	m_fLifeTime -= a_fDelta;

	if (m_fLifeTime <= 0.0f)
	{
		//Bomb!
	}
}

void Bomb::Explosived(Bomb* a_refBomb)
{
	if (a_refBomb == this) { return; }
	// Bomb!
}