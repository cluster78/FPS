#include "pch.h"
#include "Box.h"

#include "GameManager.h"

Box::Box(int x, int y) : Object(x, y) {}
Box::~Box() {}

eObjectType Box::GetObjectType() const
{
	return eObjectType::Box;
}

void Box::Explosived(Bomb* a_refBomb)	//������ �� �ڽ��� ��ȣ�ۿ� ������
{
	GameMng()->RemoveObject(this);		//2_������Ʈ ����
	GameMng()->DropItem(this);				//2_������ ����.
}
