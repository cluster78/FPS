#include "pch.h"
#include "Item.h"

#include "GameManager.h"

Item::Item(int x, int y) : Object(x, y),

m_Item{
	{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
	},

	{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
	},

	{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
	},
}
{
	m_pNowAni = &m_Item[0];
}

Item::~Item() { }

eObjectType Item::GetObjectType() const
{
	return eObjectType::Item;
}

void Item::Interaction(class Hero* a_refHero)		//2_�÷��̾�� ��ȣ�ۿ�
{
	GameMng()->RemoveObject(this);		//2_�� ����.
	GameMng()->ObtainItem(m_eType);		//2_�÷��̾� ������ ȹ�� �Լ��ҷ���.
}

void Item::Render()						//3_Render()�Լ� �߰�
{

}
