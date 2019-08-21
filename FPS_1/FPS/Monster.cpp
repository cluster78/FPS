#include "pch.h"
#include "Monster.h"


Monster::Monster(int x, int y) : Object(x, y)		//3_몬스터 형태 추가해줌
, m_Data{							
		{ '1', '1', '1', '1', '1' },
		{ '1', 'M', 'M', 'M', '1' },
		{ '1', 'M', ' ', 'M', '1' },
		{ '1', 'M', 'M', 'M', '1' },
		{ '1', '1', '1', '1', '1' }
}
{
	m_pNowAni = &m_Data;
}

Monster::~Monster()
{
}

eObjectType Monster::GetObjectType() const
{
	return eObjectType::Monster;
}

void Monster::Render()
{

}
