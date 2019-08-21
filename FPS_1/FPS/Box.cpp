#include "pch.h"
#include "Box.h"

#include "GameManager.h"

Box::Box(int x, int y) : Object(x, y) {}
Box::~Box() {}

eObjectType Box::GetObjectType() const
{
	return eObjectType::Box;
}

void Box::Explosived(Bomb* a_refBomb)	//폭발이 이 박스와 상호작용 했을때
{
	GameMng()->RemoveObject(this);		//2_오브젝트 삭제
	GameMng()->DropItem(this);				//2_아이템 떨굼.
}
