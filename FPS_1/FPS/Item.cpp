#include "pch.h"
#include "Item.h"

#include "GameManager.h"


Item::Item(int x, int y) : Object(x, y) {}
Item::~Item() {}

eObjectType Item::GetObjectType() const
{
	return eObjectType::Item;
}

void Item::Interaction(class Hero* a_refHero)		//2_�÷��̾�� ��ȣ�ۿ�
{
	GameMng()->RemoveObject(this);		//2_�� ����.
	GameMng()->ObtainItem(m_eType);		//2_�÷��̾� ������ ȹ�� �Լ��ҷ���.
}
