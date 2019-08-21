#include "pch.h"
#include "Door.h"

#include "GameManager.h"

Door::Door(int x, int y) : Object(x, y) {}

Door::~Door() {}

eObjectType Door::GetObjectType() const
{
	return eObjectType::Door;
}

void Door::Init()							//2_�� �⺻�� ����
{
	m_eState = eDoorState::Close;
}

void Door::Interaction(class Hero* a_refHero)	//2_��ȣ�ۿ��Լ�
{
	if (m_eState == eDoorState::Close) { return; }	//2_�� ���������� ������

	GameMng()->StageStart();	//2_�ƴϸ� ������������
}
