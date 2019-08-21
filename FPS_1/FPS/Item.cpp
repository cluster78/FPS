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

void Item::Interaction(class Hero* a_refHero)		//2_플레이어와 상호작용
{
	GameMng()->RemoveObject(this);		//2_템 삭제.
	GameMng()->ObtainItem(m_eType);		//2_플레이어 아이템 획득 함수불러옴.
}

void Item::Render()						//3_Render()함수 추가
{

}
