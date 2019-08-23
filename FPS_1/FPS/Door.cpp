#include "pch.h"
#include "Door.h"

#include "GameManager.h"
#include "Player.h"

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

void Door::Init()							//2_�� �⺻�� ����
{
	m_eState = eDoorState::Close;
}

//void Door::Render()
//{
//
//}

bool Door::Interaction(class Player* a_refHero)
{
	if (m_eState == eDoorState::Close) { return false; }	//2_�� ���������� ������

	if (IsCross(a_refHero) == true)
	{
		GameMng()->StageStart();	//2_�ƴϸ� ������������
	}

	return false;
	
}
