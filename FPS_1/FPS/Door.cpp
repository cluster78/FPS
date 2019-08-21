#include "pch.h"
#include "Door.h"

#include "GameManager.h"

Door::Door(int x, int y) : Object(x, y)
, m_Close{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
}
, m_Open{
			{ ' ', '1', '1', '1', ' ' },
			{ '1', ' ', ' ', ' ', '1' },
			{ '1', ' ', ' ', ' ', '1' },
			{ '1', ' ', ' ', ' ', '1' },
			{ ' ', '1', '1', '1', ' ' },
} {
	m_pNowAni = &m_Close;
}

Door::~Door()
{
}

eObjectType Door::GetObjectType() const
{
	return eObjectType::Door;
}

void Door::Init()							//2_문 기본값 셋팅
{
	m_eState = eDoorState::Close;
}

void Door::Render()
{

}

void Door::Interaction(class Hero* a_refHero)
{
	if (m_eState == eDoorState::Close) { return; }	//2_문 닫혀있으면 걍리턴

	GameMng()->StageStart();	//2_아니면 다음스테이지
}
